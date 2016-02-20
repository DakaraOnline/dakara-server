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

#include "stdafx.h"

#include "SecurityIp.h"

#include <fstream>
#include <map>
#include <exception>


namespace {

std::map<std::string, int> IpSecurityTable;

}

void InitIpTables() {

}

void IpSecurityMantenimientoLista() {
	IpSecurityDumpTables();
}

bool IpSecurityAceptarNuevaConexion(std::string ip) {
	bool retval = true;
	auto it = IpSecurityTable.find(ip);

	if (it == IpSecurityTable.end()) {
		IpSecurityTable[ip] = 1;
	} else {
		it->second += 1;
	}

	return retval;
}

bool IPSecuritySuperaLimiteConexiones(std::string ip) {
	bool retval = false;
	auto it = IpSecurityTable.find(ip);

	if (it == IpSecurityTable.end()) {
		retval = false;
	} else {
		retval = (it->second > LimiteConexionesPorIp);
	}

	return retval;
}

void IpRestarConexion(std::string ip) {
	auto it = IpSecurityTable.find(ip);

	if (it == IpSecurityTable.end()) {
		std::string ss = "IpRestarConexion: it == IpSecurityTable.end(); ip='" + ip + "'";
		throw std::runtime_error(ss);
	} else {
		it->second -= 1;
		if (it->second == 0) {
			IpSecurityTable.erase(it);
		}
	}
}

int IpSecurityDumpTables() {
	std::string ArchivoSecurityIp;
	ArchivoSecurityIp = GetDatPath(DATPATH::SecurityIp);
	std::ofstream out;
	out.open(ArchivoSecurityIp);

	for (auto& e : IpSecurityTable) {
		out << e.first << ": " << e.second << std::endl;
	}

	out.close();
	return 0;
}
