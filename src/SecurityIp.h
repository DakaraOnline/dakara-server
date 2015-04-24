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

#ifndef SECURITYIP_H
#define SECURITYIP_H

#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

void InitIpTables();

void IpSecurityMantenimientoLista();

bool IpSecurityAceptarNuevaConexion(std::string ip);

bool IPSecuritySuperaLimiteConexiones(std::string ip);

void IpRestarConexion(std::string ip);

int IpSecurityDumpTables();

#endif
