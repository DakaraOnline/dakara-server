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
 */

#include "SocketsLib.h"

/* LIBEVENT */

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
#include <vector>
#include <deque>


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
	typedef std::pair<SignalHandler, void*> SignalInfo;

protected:
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

size_t SocketServerBase::getNextSocketIndex() {
	size_t e;
	if (sockets_free_idx_.size()) {
		e = sockets_free_idx_.front();
		sockets_free_idx_.pop_front();
	} else {
		e = sockets.size();
		sockets.push_back(nullptr);
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

class SocketLibEvent : public SocketBase {
public:
	SocketLibEvent(size_t idx, SocketServerBase* sp);
	virtual ~SocketLibEvent();

	virtual void write(const char* data, size_t data_len);
	virtual size_t getOutputLength();
	virtual void close(bool force = false);

	void closeReal();

	void onSocketClose(bool error);
	void fireCloseEvent();

public:
	struct bufferevent *bev_{nullptr};
	struct event *evclose_{nullptr};
	bool evclosefired_{false};
	bool closing_{false};
};

class SocketServerLibEvent : public SocketServerBase {
public:
	SocketServerLibEvent();
	virtual ~SocketServerLibEvent();

	virtual void addListener(std::string addr, int port) override;
	virtual void addSignalHandler(int signal, SignalHandler f, void* arg) override;
	virtual std::unique_ptr<Timer> addTimer(size_t milliseconds, TimerHandler f) override;
	virtual void loop() override;

	void doAccept(evutil_socket_t listener, short event);

public:
	evutil_socket_t listener{0};
	struct sockaddr_in sockin;
	struct event_base *base{nullptr};
	struct event *listener_event{nullptr};
};

class TimerLibEvent : public Timer {
public:
	TimerLibEvent(struct event_base *base, size_t milliseconds, TimerHandler h);
	virtual ~TimerLibEvent();
	void timerEvent();

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

TimerLibEvent::TimerLibEvent(struct event_base *base, size_t milliseconds, TimerHandler h) : handler(h) {
	struct timeval tv;

	tv.tv_sec = milliseconds / 1000;
	tv.tv_usec = (milliseconds % 1000) * 1000;

	ev = event_new(base, -1, EV_PERSIST, ssle_timer_callback, this);
	event_add(ev, &tv);
}

TimerLibEvent::~TimerLibEvent() {
	event_del(ev);
}

void TimerLibEvent::timerEvent() {
	handler();
}

static void ssle_close_event(evutil_socket_t fd, short what, void *arg) {
	(void)fd;
	(void)what;

	SocketLibEvent* s = reinterpret_cast<SocketLibEvent*>(arg);
	auto sel = s->sp_->getSocketEventsListener();

	s->evclosefired_ = true;

	if (sel) {
		sel->onSocketClose(s);
	}

	event_del(s->evclose_);
	s->evclose_ = nullptr;
}

SocketLibEvent::SocketLibEvent(size_t idx, SocketServerBase* sp) : SocketBase(idx, sp) {
	auto p = reinterpret_cast<SocketServerLibEvent*>(sp);
	evclose_ = event_new(p->base, -1, 0, ssle_close_event, reinterpret_cast<void*>(this));
}

SocketLibEvent::~SocketLibEvent() {
	if (evclose_) {
		event_del(evclose_);
	}
	closeReal();
}

void SocketLibEvent::write(const char* data, size_t data_len) {
	if (closing_) return;

	auto output = bufferevent_get_output(bev_);
	auto retval = evbuffer_add(output, data, data_len);

	/*
	if (evbuffer_get_length(output) > MAX_OUTPUT_BUFFER_SIZE) {
        LogApiSock("WsApiEnviar MAX_OUTPUT_BUFFER_SIZE UserIndex=" + vb6::CStr(sctx->UserIndex()));
		std::cerr << "WsApiEnviar MAX_OUTPUT_BUFFER_SIZE" << std::endl;
		return 1;
	}*/

	if (retval != 0) {
		onSocketClose(true);
	}
}

size_t SocketLibEvent::getOutputLength() {
	auto output = bufferevent_get_output(bev_);
	return evbuffer_get_length(output);
}

void SocketLibEvent::closeReal() {
	if (bev_) {
		bufferevent_free(bev_);
		bev_ = nullptr;
	}
}

void SocketLibEvent::onSocketClose(bool error) {
	close(error);
}

void SocketLibEvent::fireCloseEvent() {
	if (evclose_ && !evclosefired_) {
		event_active(evclose_, 0, 0);
	}
}

void SocketLibEvent::close(bool force) {
	if (closing_) return;
	closing_ = true;

	if (force) {
		closeReal();
		fireCloseEvent();
	} else {
		struct timeval close_timeout = { 10, 0 };
		event_add(evclose_, &close_timeout);
	}
}

SocketServerLibEvent::SocketServerLibEvent() {

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
	auto p = reinterpret_cast<SocketServerLibEvent*>(arg);
	p->doAccept(listener, event);
}

static void ssle_readcb(struct bufferevent *bev, void *ctx) {
	SocketLibEvent* s = reinterpret_cast<SocketLibEvent*>(ctx);
	struct evbuffer *input = bufferevent_get_input(bev);

	SocketEvents* sev = s->sp_->getSocketEventsListener();

	if (sev) {
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

	SocketEvents* sev = s->sp_->getSocketEventsListener();
	if (sev) {
		sev->onSocketWrite(s);
	}

	if (s->closing_ && s->getOutputLength() == 0) {
		s->fireCloseEvent();
		s->closeReal();
	}
}

static void ssle_errorcb(struct bufferevent *bev, short events, void *ctx) {
	(void)bev;
	(void)events;
	SocketLibEvent* s = reinterpret_cast<SocketLibEvent*>(ctx);
	if (events & (BEV_EVENT_ERROR|BEV_EVENT_EOF)) {
		s->onSocketClose(true);
	}
}

void SocketServerLibEvent::doAccept(evutil_socket_t listener, short event) {
	(void)event;

	struct sockaddr_storage ss;
	socklen_t slen = sizeof(ss);
	int fd = accept(listener, (struct sockaddr*) &ss, &slen);
	if (fd < 0) {
		perror("accept");
		return;
	}

	size_t idx = getNextSocketIndex();
	sockets[idx].reset( new SocketLibEvent(idx, this) );
	SocketLibEvent* s = reinterpret_cast<SocketLibEvent*>( sockets[idx].get() );

	struct sockaddr_in *sin = (struct sockaddr_in *)&ss;
	std::string ip(inet_ntoa(sin->sin_addr));
	struct bufferevent *bev;
	void *cbarg = reinterpret_cast<void*>( s );

	evutil_make_socket_nonblocking(fd);
	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	bufferevent_setcb(bev, ssle_readcb, ssle_writecb, ssle_errorcb, cbarg);
	// bufferevent_setwatermark(bev, EV_READ, 0, MAX_LINE);
	bufferevent_enable(bev, EV_READ | EV_WRITE);

	s->idx_ = idx;
	s->bev_ = bev;
}

void SocketServerLibEvent::addListener(std::string addr, int port) {

	sockin.sin_family = AF_INET;
	sockin.sin_addr.s_addr = inet_addr(addr.c_str());
	sockin.sin_port = htons(port);

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
		return;
	}

	if (listen(listener, 250) < 0) {
		perror("listen");
		return;
	}

	listener_event = event_new(base, listener, EV_READ | EV_PERSIST, ssle_do_accept, (void*) base);
	/*XXX check it */
	event_add(listener_event, NULL);
}

void SocketServerLibEvent::addSignalHandler(int signal, SignalHandler f, void* arg) {
	struct event *sig;
	signal_handlers.emplace_back(std::unique_ptr<SignalInfo>(new SignalInfo(f, arg)));
	SignalInfo* info = signal_handlers.rbegin()->get();
	sig = evsignal_new(base, signal , ssle_my_signal_handler, reinterpret_cast<void*>(info));
	event_add(sig, 0);
}

std::unique_ptr<Timer> SocketServerLibEvent::addTimer(size_t milliseconds, TimerHandler f) {
	return std::unique_ptr<Timer>(new TimerLibEvent(base, milliseconds, f));
}

void SocketServerLibEvent::loop() {
	event_base_dispatch(base);
}


/*****************************************************************************/

std::unique_ptr<SocketServer> BuildSocketServer(std::string backend) {
	if (backend == "libevent")
		return std::unique_ptr<SocketServer>(new SocketServerLibEvent());

	return nullptr;
}


} /* namespace dakara */
