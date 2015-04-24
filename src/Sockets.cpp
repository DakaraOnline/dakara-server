/******************************************************************************
    Copyright (C) 2002-2015 Argentum Online & Dakara Online Developers

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#include "Sockets.h"
#include "allheaders.h"

#include <sys/types.h>
#include <sys/stat.h>

#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#ifndef S_ISDIR
#define S_ISDIR(x) (((x) & S_IFMT) == S_IFDIR)
#endif
#else
#include <sys/stat.h>
#include <sys/socket.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#endif

#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>

#ifdef _EVENT_HAVE_NETINET_IN_H
#include <netinet/in.h>
# ifdef _XOPEN_SOURCE_EXTENDED
#  include <arpa/inet.h>
# endif
#endif

#include <cstdint>
#include <iomanip>
#include <iostream>

#define DAKARA_DEBUG_SOCKETS 0

#define MAX_OUTPUT_BUFFER_SIZE 75000
#define MAX_INPUT_BUFFER_SIZE 75000

static evutil_socket_t listener;
static struct sockaddr_in sockin;
static struct event_base *base;
static struct event *listener_event;


void DakaraBeginCloseSocket(socket_ctx* sctx);
void DakaraRealCloseSocket(socket_ctx* sctx);


static void timer_callback(evutil_socket_t fd, short what, void * arg) {
	(void)fd;
	(void)what;
	Timer* t = reinterpret_cast<Timer*>(arg);

	try {
		t->callback();
	} catch (std::exception& ex) {
		std::cerr << "Unhandled error on timer_callback: " << ex.what() << std::endl;
		LogApiSock("Unhandled error on timer_callback, " + std::string(ex.what()));
	} catch (...) {
		std::cerr << "UNKNOWN error on timer_callback!" << std::endl;
		LogApiSock("UNKNOWN error on timer_callback!");
	}
}

Timer::Timer(bool persist) : ev(0), persist_(persist) {}

Timer::~Timer() {}

void Timer::register_timer(struct timeval* tv) {
	if (!ev) {
		ev = event_new(base, -1, persist_ ? EV_PERSIST : 0, timer_callback, this);
	} else {
		event_del(ev);
	}

	event_add(ev, tv);
}

void Timer::register_timer(double seconds) {
	struct timeval tv;
	tv.tv_sec = (int) seconds;
	tv.tv_usec = (int) (seconds * 1e6) % (int)1e6;
	register_timer(&tv);
}

namespace {

std::set<socket_ctx*> sockets_all;

std::set<socket_ctx*> sockets_to_delete;

}

socket_ctx::socket_ctx(const std::string& ip) : ip_(ip) {
	//std::cerr << this << " socket_ctx ip=" << ip_ << std::endl;
}

socket_ctx::~socket_ctx() {
	//std::cerr << this << " ~socket_ctx ip=" << ip_ << std::endl;
}

static void readcb(struct bufferevent *bev, void *ctx) {
	socket_ctx *sctx = reinterpret_cast<socket_ctx*>(ctx);

	struct evbuffer *input;
	input = bufferevent_get_input(bev);

	try {

		const int num_of_vecs = 16;
		evbuffer_iovec v[num_of_vecs];
		while (evbuffer_get_length(input)) {
			int n = evbuffer_peek(input, -1, 0, v, num_of_vecs);
			if (n >= num_of_vecs)
				n = num_of_vecs;
			for (int k = 0; k < n; ++k) {
				uint8_t* p = reinterpret_cast<uint8_t*>(v[k].iov_base);

				sctx->incomingData->WriteBlock(p, v[k].iov_len);
				evbuffer_drain(input, v[k].iov_len);

				if (sctx->incomingData->length() > MAX_INPUT_BUFFER_SIZE) {
                    LogApiSock("WsApiEnviar MAX_INPUT_BUFFER_SIZE UserIndex=" + vb6::CStr(sctx->UserIndex()));
					DakaraBeginCloseSocket(sctx);
					return;
				}
			}
		}

		sctx->incomingDataAvailable = true;

		if (sctx->firstTime) {
			sctx->firstTime = false;

			std::size_t UserIndex = NextOpenUser();

			// if ((int)UserIndex > MaxUsers || UserIndex < 1) {
			if (UserIndexSocketValido(UserIndex)) {
				DakaraBeginCloseSocket(sctx);
				return;
			}

			if ((int)UserIndex > LastUser) {
				LastUser = UserIndex;
			}

			sctx->setUserIndex(UserIndex);
			sctx->ConnIgnoreIncomingData = false;

			UserList[UserIndex].ConnID = sctx->getFd();
			UserList[UserIndex].ConnIDValida = true;
			UserList[UserIndex].sockctx = sctx;
			UserList[UserIndex].ip = sctx->IP();

			/*
			 * El codigo esta plagado de lugares donde se intentan agregar datos
			 * a la cola de salida de una conexion cerrada. En Dakara una conexion
			 * cerrada significa que sockctx == nullptr, por lo que hay
			 * potenciales segfaults, ya paso una vez al menos, bug #74.
			 *
			 * La agrego tambien al struct User para que se use como buffer dummy
			 * en una conexion ya cerrada.
			 *
			 */
			UserList[UserIndex].incomingData = sctx->incomingData;
			UserList[UserIndex].outgoingData = sctx->outgoingData;
		}

		std::size_t UserIndex = sctx->UserIndex();
		if (!UserIndexSocketValido(UserIndex)) {
			CloseSocket(sctx);
			return;
		}
		if (!sctx->ConnIgnoreIncomingData) {
			HandleIncomingData(UserIndex);
		}
	} catch (std::exception& ex) {
		std::cerr << "Unhandled error on HandleIncomingData: " << ex.what() << std::endl;
		LogApiSock("Unhandled error on HandleIncomingData, " + std::string(ex.what()));
		CloseSocket(sctx);
	} catch (...) {
		std::cerr << "UNKNOWN error on HandleIncomingData!" << std::endl;
		LogApiSock("UNKNOWN error on HandleIncomingData!");
		CloseSocket(sctx);
	}
}

static void writecb(struct bufferevent *bev, void *ctx) {
	socket_ctx *sctx = reinterpret_cast<socket_ctx*>(ctx);
	std::size_t UserIndex = sctx->UserIndex();

	(void)UserIndex;

	struct evbuffer *output;
	output = bufferevent_get_output(bev);

	if (sctx->isClosing()) {
		if (evbuffer_get_length(output) == 0) {
			DakaraRealCloseSocket(sctx);
		}
	}
}

static void errorcb(struct bufferevent *bev, short error, void *ctx) {
	(void)bev;
	(void)error;

	socket_ctx *sctx = reinterpret_cast<socket_ctx*>(ctx);
	//std::size_t UserIndex = sctx->UserIndex();

#if 0
	if (error & BEV_EVENT_EOF) {
		/* connection has been closed, do any clean up here */
		/* ... */
	} else if (error & BEV_EVENT_ERROR) {
		/* check errno to see what error occurred */
		/* ... */
	} else if (error & BEV_EVENT_TIMEOUT) {
		/* must be a timeout event handle, handle it */
		/* ... */
	}
#endif

	try {
		sctx->ConnIdCerrada = true;
		CloseSocket(sctx);
	} catch (std::exception& ex) {
		std::cerr << "Unhandled error on errorcb: " << ex.what() << std::endl;
		LogApiSock("Unhandled error on errorcb, " + std::string(ex.what()));
	} catch (...) {
		std::cerr << "UNKNOWN error on errorcb!" << std::endl;
		LogApiSock("UNKNOWN error on errorcb!");
	}
}

static void do_accept(evutil_socket_t listener, short event, void *arg) {
	(void)event;

	try {
		struct event_base *base = (struct event_base *)arg;
		struct sockaddr_storage ss;
		socklen_t slen = sizeof(ss);
		int fd = accept(listener, (struct sockaddr*) &ss, &slen);
		if (fd < 0) {
			perror("accept");
			LogApiSock("error en accept");
			return;
		}

		struct sockaddr_in *sin = (struct sockaddr_in *)&ss;

		std::string ip(inet_ntoa(sin->sin_addr));

		// std::cout << "New connection from " << ip << std::endl;

		if (BanIpBuscar(ip)) {
			EVUTIL_CLOSESOCKET(fd);
			return;
		}

		if (!IpSecurityAceptarNuevaConexion(ip)) {
			EVUTIL_CLOSESOCKET(fd);
			return;
		}

		if (IPSecuritySuperaLimiteConexiones(ip)) {
			IpRestarConexion(ip);
			EVUTIL_CLOSESOCKET(fd);
			return;
		}

		struct bufferevent *bev;
		socket_ctx *sctx = new socket_ctx(ip);

		sockets_all.insert(sctx);

		void *cbarg = reinterpret_cast<void*>( sctx );

		evutil_make_socket_nonblocking(fd);
		bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
		bufferevent_setcb(bev, readcb, writecb, errorcb, cbarg);
		// bufferevent_setwatermark(bev, EV_READ, 0, MAX_LINE);
		bufferevent_enable(bev, EV_READ | EV_WRITE);

		sctx->setBufferEvent(bev);

		sctx->incomingData.reset(new clsByteQueue());
		sctx->outgoingData.reset(new clsByteQueue());
		sctx->ConnIdCerrada = false;
		sctx->ConnIgnoreIncomingData = false;
	} catch (std::exception& ex) {
		std::cerr << "Unhandled error on do_accept: " << ex.what() << std::endl;
		LogApiSock("Unhandled error on do_accept, " + std::string(ex.what()));
	} catch (...) {
		std::cerr << "UNKNOWN error on do_accept!" << std::endl;
		LogApiSock("UNKNOWN error on do_accept!");
	}
}

static void break_signal_handler(evutil_socket_t fd, short event, void *arg) {
	(void)fd;
	(void)event;
	(void)arg;
	std::cerr << "Recibido el break, deteniendo... " << std::endl;
	event_base_loopbreak(base);
}

static void signal_handler(evutil_socket_t fd, short event, void *arg) {
	(void)fd;
	(void)event;
	(void)arg;
	std::cerr << "signal handler for " << fd << " event " << event << " arg " << arg << std::endl;
}

void IniciaWsApi() {
	LogApiSock("IniciaWsApi");

#ifdef WIN32
	WSADATA WSAData;
	if (WSAStartup(MAKEWORD( 2, 2 ), &WSAData) != 0) {
		perror("WSAStartup");
		LogApiSock("error en WSAStartup");
		return;
	} else { 
		std::string msg = ("Iniciado Winsock v " + std::to_string(LOBYTE( WSAData.wVersion )) + "." + std::to_string(HIBYTE( WSAData.wVersion )));
		LogApiSock(msg);
		std::cerr << msg << std::endl;
	}
#endif

	base = event_base_new();
	if (!base) {
		perror("event_base_new");
		LogApiSock("error en event_base_new");
		return;
	}

#ifndef WIN32
	struct event *sig;
//	sig = evsignal_new(base, SIGABRT, signal_handler, NULL);
//	event_add(sig, 0);
//	sig = evsignal_new(base, SIGFPE , signal_handler, NULL);
//	event_add(sig, 0);
//	sig = evsignal_new(base, SIGILL , signal_handler, NULL);
//	event_add(sig, 0);
	sig = evsignal_new(base, SIGINT , break_signal_handler, NULL);
	event_add(sig, 0);
	sig = evsignal_new(base, SIGPIPE, signal_handler, NULL);
	event_add(sig, 0);
//	sig = evsignal_new(base, SIGSEGV , signal_handler, NULL);
//	event_add(sig, 0);
//	sig = evsignal_new(base, SIGTERM , signal_handler, NULL);
//	event_add(sig, 0);
#else
	(void)break_signal_handler;
	(void)signal_handler;
#endif

	sockin.sin_family = AF_INET;
	sockin.sin_addr.s_addr = 0;
	sockin.sin_port = htons(Puerto);

	listener = socket(AF_INET, SOCK_STREAM, 0);
	evutil_make_socket_nonblocking(listener);

#ifndef WIN32
	{
		int one = 1;
		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
	}
#endif

	if (bind(listener, (struct sockaddr*) &sockin, sizeof(struct sockaddr_in)) < 0) {
		perror("bind");
		LogApiSock("error en bind");
		return;
	}

	if (listen(listener, 250) < 0) {
		perror("listen");
		LogApiSock("error en listen");
		return;
	}

	listener_event = event_new(base, listener, EV_READ | EV_PERSIST, do_accept, (void*) base);
	/*XXX check it */
	event_add(listener_event, NULL);

}

void ServerLoop() {
	std::cout << "Server iniciado." << std::endl;
	event_base_dispatch(base);
//	event_base_free(base);
	std::cout << "Cerrando..." << std::endl;
}

void LimpiaWsApi() {
	LogApiSock("LimpiaWsApi");

	event_base_free(base);

	/* FIXME */
}

void FlushBuffer(socket_ctx* sctx) {
	if (sctx->outgoingData->length() == 0) {
			return;
	}

#if 1
	std::vector<std::int8_t> sndData;
	sctx->outgoingData->swapAndCleanRawBuffer(sndData);
#else
	std::string sndData = sctx->outgoingData->ReadBinaryFixed(sctx->outgoingData->length());
#endif

	WsApiEnviar(sctx, sndData);
}

void CloseSocket(socket_ctx* sctx) {
	if (sctx->UserIndex() > 0) {
		CerrarUserIndex(sctx->UserIndex());
	} else {
		DakaraBeginCloseSocket(sctx);
	}
}

int WsApiEnviar(int UserIndex, const char* str, std::size_t str_len) {
	if (!UserList[UserIndex].ConnIDValida) {
		throw std::runtime_error("WsApiEnviar: ConnIDValida = False, UserIndex = " + std::to_string(UserIndex));
	}

	return WsApiEnviar(UserList[UserIndex].sockctx, str, str_len);
}

int WsApiEnviar(socket_ctx* sctx, const char* str, std::size_t str_len) {
	int retval = -1;
	struct evbuffer* output;

	if (sctx->ConnIdCerrada) {
		return 0;
	}

	if (sctx->outgoingData->length() > 0) {
		FlushBuffer(sctx);
	}

	output = bufferevent_get_output(sctx->BufferEvent());
	retval = evbuffer_add(output, str, str_len);

	/* FIXME */
	if (evbuffer_get_length(output) > MAX_OUTPUT_BUFFER_SIZE) {
        LogApiSock("WsApiEnviar MAX_OUTPUT_BUFFER_SIZE UserIndex=" + vb6::CStr(sctx->UserIndex()));
		std::cerr << "WsApiEnviar MAX_OUTPUT_BUFFER_SIZE" << std::endl;
		return 1;
	}

	if (retval != 0) {
		sctx->ConnIdCerrada = true;
		std::cerr << "WsApiEnviar error evbuffer_add" << std::endl;
		throw std::runtime_error("WsApiEnviar: evbuffer_add ");
	}

	return retval;
}

void WSApiReiniciarSockets() {
	throw std::runtime_error("WSApiReiniciarSockets not implemented");
}

bool UserIndexSocketValido(int UserIndex) {
	return UserIndex >= 1 && UserIndex <= MaxUsers && UserList[UserIndex].ConnID != -1 && UserList[UserIndex].ConnIDValida && UserList[UserIndex].sockctx != nullptr;
}

void DakaraBeginCloseSocket(socket_ctx* sctx) {
	int UserIndex = sctx->UserIndex();

    if (UserIndex > 0) {
	    IpRestarConexion (UserList[UserIndex].ip);

		UserList[UserIndex].ConnID = -1;
		UserList[UserIndex].ConnIDValida = false;
		UserList[UserIndex].sockctx = nullptr;
		sctx->setUserIndex(0);
    }

	if (sctx->BufferEvent()) {
		sctx->setUserIndex(0);
		sctx->ConnIdCerrada = true;
		sctx->ConnIgnoreIncomingData = false;

		sctx->setClosing();
		writecb(sctx->BufferEvent(), reinterpret_cast<void*>(sctx));
    }
}

void DakaraRealCloseSocket(socket_ctx* sctx) {
	if (sctx->BufferEvent()) {
		bufferevent_free(sctx->BufferEvent());
		sctx->setBufferEvent(0);
	}

	auto it = sockets_all.find(sctx);
	if (it == sockets_all.end()) {
		std::string ss{"it == sockets_all.end(), ip="};
		ss += sctx->IP();
		throw std::runtime_error(ss);
	}

	sctx->incomingData.reset();
	sctx->outgoingData.reset();

	sockets_all.erase(it);
	sockets_to_delete.insert(sctx);
}

void WSApiCloseSocket(int UserIndex) {
	if (!UserList[UserIndex].ConnIDValida) {
		throw std::runtime_error("WSApiCloseSocket: ConnIDValida = False, UserIndex = " + std::to_string(UserIndex));
	}

	socket_ctx* sctx = UserList[UserIndex].sockctx;

	DakaraBeginCloseSocket(sctx);
}

void WSApiGarbageCollectSockets() {

	while (sockets_to_delete.size()) {
		socket_ctx *sctx = *sockets_to_delete.begin();
		sockets_to_delete.erase(sockets_to_delete.begin());
		delete sctx;
	}
}

