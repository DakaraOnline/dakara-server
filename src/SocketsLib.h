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

#ifndef SRC_SOCKETSLIB_H_
#define SRC_SOCKETSLIB_H_

#include <string>
#include <cstdint>
#include <memory>
#include <functional>


namespace dakara {

class Socket;
class SocketServer;
class SocketEvents;

std::unique_ptr<SocketServer> BuildSocketServer(std::string backend);

class SocketEvents {
public:
	virtual ~SocketEvents();
	virtual void onSocketNew(Socket* s) = 0;
	virtual void onSocketRead(Socket* s, const char* data, size_t data_len) = 0;
	virtual void onSocketWrite(Socket* s) = 0;
	virtual void onSocketClose(Socket* s) = 0;
};

class Socket {
public:
	Socket();
	virtual ~Socket();

	// Noncopyable
	Socket(const Socket&) = delete;
	Socket& operator=(const Socket&) = delete;

	virtual void write(const char* data, size_t data_len) = 0;
	virtual void close(bool force) = 0;
	virtual size_t getId() = 0;
	virtual std::string getIP() = 0;
	virtual size_t getOutputLength() = 0;

	size_t userData{};
};

class Timer {
public:
	Timer();
	virtual ~Timer();

	virtual void registerTimer(size_t milliseconds) = 0;

	// Noncopyable
	Timer(const Timer&) = delete;
	Timer& operator=(const Timer&) = delete;
};

typedef std::function<void(short event, void* arg)> SignalHandler;
typedef std::function<void()> TimerHandler;

class SocketServer {
public:
	SocketServer();
	virtual ~SocketServer();

	// Noncopyable
	SocketServer(const SocketServer&) = delete;
	SocketServer& operator=(const SocketServer&) = delete;

	virtual void addListener(std::string addr, int port, SocketEvents* sev) = 0;
	virtual std::unique_ptr<Timer> addTimer(size_t milliseconds, TimerHandler f, bool persist) = 0;
	virtual void addSignalHandler(int signal, SignalHandler f, void* arg) = 0;
	virtual void loop() = 0;
	virtual void stop() = 0;
};


} /* namespace dakara */

#endif /* SRC_SOCKETSLIB_H_ */
