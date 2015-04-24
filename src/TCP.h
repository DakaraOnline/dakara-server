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

#ifndef TCP_H
#define TCP_H

#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

void DarCuerpo(int UserIndex);

bool ValidarCabeza(int UserRaza, int UserGenero, int Head);

bool AsciiValidos(const std::string& cad);

bool Numeric(std::string cad);

bool NombrePermitido(std::string Nombre);

bool ValidateSkills(int UserIndex);

void ConnectNewUser(int UserIndex, const std::string& Name, const std::string& Password, eRaza UserRaza,
		eGenero UserSexo, eClass UserClase, const std::string& UserEmail, eCiudad Hogar, int Head);

void CloseSocket(int UserIndex);

/* '[Alejo-21-5]: Cierra un socket sin limpiar el slot */
void CloseSocketSL(int UserIndex);

void CerrarUserIndex(int UserIndex);

/* '' */
/* ' Send an string to a Slot */
/* ' */
/* ' @param userIndex The index of the User */
/* ' @param Datos The string that will be send */
/* ' @remarks If UsarQueSocket is 3 it won`t use the clsByteQueue */

int EnviarDatosASlot(int UserIndex, const std::string & Datos);

int EnviarDatosASlot(int UserIndex, const std::vector<std::int8_t>& sndData);

int EnviarDatosASlot(int UserIndex, const char* datos, std::size_t datos_len);

bool EstaPCarea(int index, int Index2);

bool HayPCarea(struct WorldPos Pos);

bool HayOBJarea(struct WorldPos Pos, int ObjIndex);

bool ValidateChr(int UserIndex);

bool ConnectUser(int UserIndex, const std::string & Name, const std::string & Password);

void SendMOTD(int UserIndex);

void ResetFacciones(int UserIndex);

void ResetContadores(int UserIndex);

void ResetCharInfo(int UserIndex);

void ResetBasicUserInfo(int UserIndex);

void ResetReputacion(int UserIndex);

void ResetGuildInfo(int UserIndex);

void ResetUserFlags(int UserIndex);

void ResetUserSpells(int UserIndex);

void ResetUserPets(int UserIndex);

void ResetUserBanco(int UserIndex);

void LimpiarComercioSeguro(int UserIndex);

void ResetUserSlot(int UserIndex);

void CloseUser(int UserIndex);

void ReloadSokcet();

void EnviarNoche(int UserIndex);

void EcharPjsNoPrivilegiados();

#endif
