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

#ifndef MODSENDDATA_H
#define MODSENDDATA_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"
#include "ProtocolNew.h"


/* '' */
/* ' Contains all methods to send data to different user groups. */
/* ' Makes use of the modAreas module. */
/* ' */
/* ' @author Juan Martín Sotuyo Dodero (Maraxus) juansotuyo@gmail.com */
/* ' @version 1.0.0 */
/* ' @date 20070107 */

std::string PacketToString(const dakara::protocol::Packet& p);

void SendData(SendTarget sndRoute, int sndIndex, std::string sndData, bool IsDenounce = false);

void SendData(SendTarget sndRoute, int sndIndex, const dakara::protocol::Packet& p, bool IsDenounce = false);

void SendToUserArea(int UserIndex, std::string sdData);

void SendToUserAreaButindex(int UserIndex, std::string sdData);

void SendToDeadUserArea(int UserIndex, std::string sdData);

void SendToUserGuildArea(int UserIndex, std::string sdData);

void SendToUserPartyArea(int UserIndex, std::string sdData);

void SendToAdminsButConsejerosArea(int UserIndex, std::string sdData);

void SendToNpcArea(int NpcIndex, std::string sdData);

void SendToAreaByPos(int Map, int AreaX, int AreaY, std::string sdData);

void SendToMap(int Map, std::string sdData);

void SendToMapButIndex(int UserIndex, std::string sdData);

void SendToGMsAreaButRmsOrCounselors(int UserIndex, std::string sdData);

void SendToUsersAreaButGMs(int UserIndex, std::string sdData);

void SendToUsersAndRmsAndCounselorsAreaButGMs(int UserIndex, std::string sdData);

void AlertarFaccionarios(int UserIndex);

#endif
