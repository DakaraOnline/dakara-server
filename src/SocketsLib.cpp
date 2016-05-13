/******************************************************************************
    Copyright (C) 2015 Alejandro Santos

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

/*
 * Dakara Sockets Library.
 *
 * This is a wrapper around both Libevent and boost::asio, to allow the
 * selection of any backend for the server. Libevent is a bit faster on Linux,
 * boost::asio is easier to compile against and a bit better on Windows. We
 * can also have other backends in the future, like libev and libuv.
 *
 * The backend strings are: "libevent".
 *
 * FIXME: IMPLEMENT ASIO
 */

#include "stdafx.h"

#include "SocketsLib.h"

/* LIBEVENT */

#include <sys/types.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#ifndef S_ISDIR
#define S_ISDIR(x) (((x) & S_IFMT) == S_IFDIR)
#endif
#else
#include <arpa/inet.h>
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
#include <cstring>
#include <memory>
#include <vector>
#include <deque>

#define MAX_OUTPUT_BUFFER_SIZE (86000)

namespace dakara {

class Socket;
class SocketBase;

class SocketServer;
class SocketServerBase;

SocketEvents::~SocketEvents() { }

SocketServer::SocketServer() { }

SocketServer::~SocketServer() { }

class SocketServerBase : public SocketServer {
public:
	SocketServerBase();

	typedef std::pair<SignalHandler, void*> SignalInfo;

	size_t getNextSocketIndex();
	void freeSocketIndex(size_t idx);

protected:
	std::vector<std::unique_ptr<SignalInfo> > signal_handlers;
	std::vector<std::unique_ptr<SocketBase > > sockets;
	std::deque<size_t> sockets_free_idx_;
};

Socket::Socket() { }

Socket::~Socket() { }

class SocketBase : public Socket {
public:
	SocketBase(size_t idx, SocketServerBase* sp) : idx_(idx), sp_(sp) {}

	virtual size_t getId();
public:
	size_t idx_;
	SocketServerBase* sp_;
};

size_t SocketBase::getId() {
	return idx_;
}

SocketServerBase::SocketServerBase() {
	/* the ID starts in 1 */
	sockets.resize(1);
}

size_t SocketServerBase::getNextSocketIndex() {
	size_t e;

	if (sockets_free_idx_.size()) {
		e = sockets_free_idx_.front();
		sockets_free_idx_.pop_front();
	} else {
		e = sockets.size();
		sockets.resize(e + 1);
	}

	return e;
}

void SocketServerBase::freeSocketIndex(size_t idx) {
	sockets[idx].reset();
	sockets_free_idx_.push_back(idx);
}

Timer::Timer() {}
Timer::~Timer() {}

/*****************************************************************************/
/* LIBEVENT */

class SocketLibEvent;
class SocketServerLibEvent;
class SocketListenerLibEvent;
class TimerLibEvent;

class SocketLibEvent : public SocketBase {
public:
	SocketLibEvent(size_t idx, SocketListenerLibEvent* sl);
	virtual ~SocketLibEvent();

	virtual void write(const char* data, size_t data_len);
	virtual size_t getOutputLength();
	virtual void close(bool force);
	virtual std::string getIP() {
		return ip_;
	}

	void closeReal();

	void onSocketClose(bool error);

public:
	evutil_socket_t fd_{0};
	struct bufferevent *bev_{nullptr};
	bool closing_{false};
	bool closed_{false};
	SocketListenerLibEvent* sl_{nullptr};
	std::string ip_;
};

class SocketListenerLibEvent {
public:
	evutil_socket_t listener;
	std::string addr;
	int port;
	SocketEvents* sev;
	SocketServerLibEvent* ssle;
};

class SocketServerLibEvent : public SocketServerBase {
public:
	SocketServerLibEvent();
	virtual ~SocketServerLibEvent();

	virtual void addListener(std::string addr, int port, SocketEvents* sev) override;
	virtual void addSignalHandler(int signal, SignalHandler f, void* arg) override;
	virtual std::unique_ptr<Timer> addTimer(size_t milliseconds, TimerHandler f, bool persist) override;
	virtual void loop() override;
	virtual void stop() override;

	void doAccept(evutil_socket_t listener, short event, SocketListenerLibEvent* sl);

public:
	std::vector<std::unique_ptr<SocketListenerLibEvent> > listeners;
	struct sockaddr_in sockin;
	struct event_base *base{nullptr};
	struct event *listener_event{nullptr};
};

class TimerLibEvent : public Timer {
public:
	TimerLibEvent(struct event_base *base, size_t milliseconds, TimerHandler h, bool persist);
	virtual ~TimerLibEvent();
	void timerEvent();
	virtual void registerTimer(size_t milliseconds) override;

public:
	TimerHandler handler;
	struct event *ev;
};

static void ssle_timer_callback(evutil_socket_t fd, short what, void * arg) {
	(void)fd;
	(void)what;
	auto t = reinterpret_cast<TimerLibEvent*>(arg);
	t->timerEvent();
}

TimerLibEvent::TimerLibEvent(struct event_base *base, size_t milliseconds, TimerHandler h, bool persist) : handler(h) {
	ev = event_new(base, -1, persist ? EV_PERSIST : 0, ssle_timer_callback, this);
	registerTimer(milliseconds);
}

TimerLibEvent::~TimerLibEvent() {
	event_del(ev);
}

void TimerLibEvent::registerTimer(size_t milliseconds) {
	struct timeval tv;

	tv.tv_sec = milliseconds / 1000;
	tv.tv_usec = (milliseconds % 1000) * 1000;

	event_add(ev, &tv);
}

void TimerLibEvent::timerEvent() {
	handler();
}

SocketLibEvent::SocketLibEvent(size_t idx, SocketListenerLibEvent* sl) : SocketBase(idx, sl->ssle), sl_(sl)
{
}

SocketLibEvent::~SocketLibEvent() {
	closeReal();
}

void SocketLibEvent::write(const char* data, size_t data_len) {
	if (closing_) return;

	auto output = bufferevent_get_output(bev_);
	auto retval = evbuffer_add(output, data, data_len);

	if (retval != 0) {
		onSocketClose(true);
		return;
	}

	if (evbuffer_get_length(output) > MAX_OUTPUT_BUFFER_SIZE) {
        /* LogApiSock("WsApiEnviar MAX_OUTPUT_BUFFER_SIZE"); */
        onSocketClose(true);
		return;
	}
}

size_t SocketLibEvent::getOutputLength() {
	if (bev_) {
		auto output = bufferevent_get_output(bev_);
		return evbuffer_get_length(output);
	}

	return 0;
}

void SocketLibEvent::closeReal() {
	if (closed_) return;
    closed_ = true;

	auto sel = sl_->sev;
	if (sel) {
		sel->onSocketClose(this);
	}

	sp_->freeSocketIndex(getId());

	if (bev_) {
		/* FIXME: Gracefully shutdown(fd, SHUT_WR) the socket, unless forced or destroyed. */
		/* evutil_closesocket(fd_); */
		bufferevent_free(bev_);
		bev_ = nullptr;
	}
}

void SocketLibEvent::onSocketClose(bool error) {
	close(error);
}


void SocketLibEvent::close(bool force) {
	if (closing_) return;
	closing_ = true;

	if (force || getOutputLength() == 0) {
		closeReal();
	}
}

SocketServerLibEvent::SocketServerLibEvent() {
	std::memset(&sockin, 0, sizeof(sockin));

#ifdef WIN32
	WSADATA WSAData;
	if (WSAStartup(MAKEWORD( 2, 2 ), &WSAData) != 0) {
		perror("WSAStartup");
		return;
	}
#endif

	base = event_base_new();
	if (!base) {
		perror("event_base_new");
		return;
	}
}

SocketServerLibEvent::~SocketServerLibEvent() {
	if (base) {
		event_base_free(base);
	}
}

static void ssle_my_signal_handler(evutil_socket_t fd, short event, void *arg) {
	(void)fd;
	SocketServerBase::SignalInfo* info = reinterpret_cast<SocketServerBase::SignalInfo*>(arg);
	info->first(event, info->second);
}

static void ssle_do_accept(evutil_socket_t listener, short event, void *arg) {
	(void)event;
	auto sl = reinterpret_cast<SocketListenerLibEvent*>(arg);
	sl->ssle->doAccept(listener, event, sl);
}

static void ssle_readcb(struct bufferevent *bev, void *ctx) {
	SocketLibEvent* s = reinterpret_cast<SocketLibEvent*>(ctx);
	struct evbuffer *input = bufferevent_get_input(bev);
	SocketEvents* sev = s->sl_->sev;

	if (s->closing_) {
		auto n = evbuffer_get_length(input);
		evbuffer_drain(input, n);
	} else if (sev) {
		const int num_of_vecs = 16;
		evbuffer_iovec v[num_of_vecs];
		while (evbuffer_get_length(input)) {
			int n = evbuffer_peek(input, -1, 0, v, num_of_vecs);
			if (n >= num_of_vecs)
				n = num_of_vecs;
			for (int k = 0; k < n; ++k) {
				auto p = reinterpret_cast<const char*>(v[k].iov_base);

				sev->onSocketRead(s, p, v[k].iov_len);

				evbuffer_drain(input, v[k].iov_len);
			}
		}
	}
}

static void ssle_writecb(struct bufferevent *bev, void *ctx) {
	(void)bev;
	SocketLibEvent* s = reinterpret_cast<SocketLibEvent*>(ctx);

	SocketEvents* sev = s->sl_->sev;

	if (sev) {
		sev->onSocketWrite(s);
	}

	if (s->closing_ && s->getOutputLength() == 0) {
		s->closeReal();
	}
}

static void ssle_errorcb(struct bufferevent *bev, short events, void *ctx) {
	(void)bev;
	(void)events;
	SocketLibEvent* s = reinterpret_cast<SocketLibEvent*>(ctx);
	//if (events & (BEV_EVENT_ERROR|BEV_EVENT_EOF))
	{
		s->onSocketClose(true);
	}
}

void SocketServerLibEvent::doAccept(evutil_socket_t listener, short event, SocketListenerLibEvent* sl) {
	(void)event;

	struct sockaddr_storage ss;
	socklen_t slen = sizeof(ss);

	evutil_socket_t fd = accept(listener, (struct sockaddr*) &ss, &slen);

	if (fd < 0) {
		perror("accept");
		return;
	}

	evutil_make_socket_nonblocking(fd);

	/* FIXME: <<< IP FILTERING HERE >>> */
	size_t idx = getNextSocketIndex();
	sockets[idx].reset( new SocketLibEvent(idx, sl) );
	SocketLibEvent* s = reinterpret_cast<SocketLibEvent*>( sockets[idx].get() );

	struct sockaddr_in *sin = (struct sockaddr_in *)&ss;
	char tmpipaddr[INET_ADDRSTRLEN];
	//s->ip_ = (inet_ntoa(sin->sin_addr));
	s->ip_ = inet_ntop(AF_INET, &(sin->sin_addr), tmpipaddr, INET_ADDRSTRLEN);

	struct bufferevent *bev;
	void *cbarg = reinterpret_cast<void*>( s );

	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE); /*  */
	bufferevent_setcb(bev, ssle_readcb, ssle_writecb, ssle_errorcb, cbarg);
	// bufferevent_setwatermark(bev, EV_READ, 0, MAX_LINE);
	bufferevent_enable(bev, EV_READ | EV_WRITE);

	s->fd_ = fd;
	s->idx_ = idx;
	s->bev_ = bev;

	sl->sev->onSocketNew(s);
}

void SocketServerLibEvent::addListener(std::string addr, int port, SocketEvents* sev) {

	sockin.sin_family = AF_INET;
	//sockin.sin_addr.s_addr = inet_addr(addr.c_str());
	inet_pton(AF_INET, addr.c_str(), &(sockin.sin_addr));
	sockin.sin_port = htons(port);

	listeners.push_back(std::unique_ptr<SocketListenerLibEvent>( new SocketListenerLibEvent() ));

	SocketListenerLibEvent* listener = listeners.back().get();

	listener->addr = addr;
	listener->port = port;
	listener->sev = sev;
	listener->ssle = this;

	listener->listener = socket(AF_INET, SOCK_STREAM, 0);

	if (listener->listener < 0) {
		perror("socket");
		throw std::runtime_error("socket del listener");
	}

	if (evutil_make_socket_nonblocking(listener->listener) != 0) {
		throw std::runtime_error("evutil_make_socket_nonblocking del listener");
	}

	if (evutil_make_listen_socket_reuseable(listener->listener) != 0) {
		throw std::runtime_error("evutil_make_listen_socket_reuseable del listener");
	}

	if (bind(listener->listener, (struct sockaddr*) &sockin, sizeof(struct sockaddr_in)) < 0) {
		throw std::runtime_error("bind del listener");
	}

	if (listen(listener->listener, 250) < 0) {
		throw std::runtime_error("listen del listener");
	}

	listener_event = event_new(
			base,
			listener->listener,
			EV_READ | EV_PERSIST,
			ssle_do_accept,
			(void*) listener);

	event_add(listener_event, NULL);
}

void SocketServerLibEvent::addSignalHandler(int signal, SignalHandler f, void* arg) {
	struct event *sig;
	signal_handlers.emplace_back(std::unique_ptr<SignalInfo>(new SignalInfo(f, arg)));
	SignalInfo* info = signal_handlers.rbegin()->get();
	sig = evsignal_new(base, signal , ssle_my_signal_handler, reinterpret_cast<void*>(info));
	event_add(sig, 0);
}

std::unique_ptr<Timer> SocketServerLibEvent::addTimer(size_t milliseconds, TimerHandler f, bool persist) {
	return std::unique_ptr<Timer>(new TimerLibEvent(base, milliseconds, f, persist));
}

void SocketServerLibEvent::loop() {
	event_base_dispatch(base);
}

void SocketServerLibEvent::stop() {
	event_base_loopbreak(base);
}


/*****************************************************************************/

std::unique_ptr<SocketServer> BuildSocketServer(std::string backend) {
	if (backend == "libevent")
		return std::unique_ptr<SocketServer>(new SocketServerLibEvent());

	/* FIXME: ADD DUMMY BACKEND FOR TESTING */
	if (backend == "dummy")
		return nullptr;

	return nullptr;
}


} /* namespace dakara */
