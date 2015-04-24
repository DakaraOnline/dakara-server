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

#ifndef WSKAPIAO_H
#define WSKAPIAO_H

#include <vector>
#include <memory>
#include <string>
#include <boost/intrusive/list.hpp>
#include "vb6compat.h"
#include "enums.h"

#include "Crypto.h"


struct event;
struct timeval;

class Timer {
public:
	explicit Timer(bool persist = true);
	virtual ~Timer();

	void register_timer(struct timeval* tv);

	void register_timer(double seconds);

	virtual void callback() = 0;

private:
	struct event *ev;
	bool persist_;
};

void TimerRegister(Timer* t, struct timeval* tv);

/** A Dakara Socket.
 *
 */
class socket_ctx : public boost::intrusive::list_base_hook<> {
public:
	socket_ctx(const std::string& ip);
	virtual ~socket_ctx();

	// Noncopyable
	socket_ctx(const socket_ctx&) = delete;
	socket_ctx& operator=(const socket_ctx&) = delete;

	inline std::size_t UserIndex() const {
		return UserIndex_;
	}

	inline struct bufferevent* BufferEvent() const {
		return bev_;
	}

	inline bool isClosing() const {
		return closing_;
	}

	inline void setUserIndex(std::size_t ui) {
		UserIndex_ = ui;
	}

	inline void setBufferEvent(struct bufferevent *bev) {
		bev_ = bev;
	}

	inline void setClosing() {
		closing_ = true;
	}

	inline const std::string& IP() const {
		return ip_;
	}

	inline void setFd(int fd) {
		fd_ = fd;
	}

	inline int getFd() const {
		return fd_;
	}

private:
	std::size_t UserIndex_ = 0;
	struct bufferevent *bev_ = 0;
	bool closing_ = false;
	std::string ip_;
	int fd_{};

public:
	/* 'Outgoing and incoming messages */
	std::shared_ptr<clsByteQueue> outgoingData;
	std::shared_ptr<clsByteQueue> incomingData;

	bool ConnIdCerrada = true;
	bool ConnIgnoreIncomingData = false;
	bool incomingDataAvailable = false;
	bool firstTime = true;
};

void IniciaWsApi();

void ServerLoop();

void LimpiaWsApi();

void FlushBuffer(socket_ctx* sctx);

void CloseSocket(socket_ctx* sctx);

int WsApiEnviar(int UserIndex, const char* str, std::size_t str_len);

int WsApiEnviar(socket_ctx* sctx, const char* str, std::size_t str_len);

inline int WsApiEnviar(socket_ctx* sctx, std::vector<std::int8_t> data) {
	return WsApiEnviar(sctx, reinterpret_cast<const char*>(data.data()), data.size());
}

inline int WsApiEnviar(socket_ctx* sctx, std::vector<std::uint8_t> data) {
	return WsApiEnviar(sctx, reinterpret_cast<const char*>(data.data()), data.size());
}

void WSApiReiniciarSockets();

bool UserIndexSocketValido(int UserIndex);

void WSApiCloseSocket(int UserIndex);

void WSApiGarbageCollectSockets();

#endif
