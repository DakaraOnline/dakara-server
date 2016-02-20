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

static const int MaximoPersonajesPorIP = 15;

bool clsAntiMassClon::MaxPersonajes(std::string sIp) {
	bool retval;

	auto it = m_coleccion.find(sIp);

	if (it != m_coleccion.end()) {
		UserIpAdress& ipa = it->second;
		if (ipa.PersonajesCreados >= MaximoPersonajesPorIP) {
			return true;
		} else {
			ipa.PersonajesCreados++;
			return false;
		}
	} else {
		UserIpAdress ipa;
		ipa.ip = sIp;
		ipa.PersonajesCreados = 1;
		m_coleccion[sIp] = ipa;
	}

	retval = false;
	return retval;
}

int clsAntiMassClon::VaciarColeccion() {
	int retval = 0;

	m_coleccion.clear();

	return retval;
}

