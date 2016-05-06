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

#include "SocketsLib.h"

extern std::unique_ptr<dakara::SocketServer> DakaraSocketServer;

void IniciaWsApi();

void ServerLoop();

void LimpiaWsApi();

void FlushBuffer(dakara::Socket* sctx);

void CloseSocket(dakara::Socket* sctx);

void WsApiEnviar(int UserIndex, const char* str, std::size_t str_len);

void WsApiEnviar(dakara::Socket* sctx, const char* str, std::size_t str_len);

inline void WsApiEnviar(dakara::Socket* sctx, std::vector<std::int8_t> data) {
	return WsApiEnviar(sctx, reinterpret_cast<const char*>(data.data()), data.size());
}

void WSApiReiniciarSockets();

bool UserIndexSocketValido(int UserIndex);

void WSApiCloseSocket(int UserIndex);

#endif
