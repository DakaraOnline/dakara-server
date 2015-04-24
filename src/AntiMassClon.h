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

#ifndef CLSANTIMASSCLON_H
#define CLSANTIMASSCLON_H
#include <vector>
#include <memory>
#include <string>
#include <map>

#include <boost/noncopyable.hpp>

#include "vb6compat.h"
#include "enums.h"

struct UserIpAdress {
	std::string ip;
	int PersonajesCreados;
};

class clsAntiMassClon : private boost::noncopyable {

private:
	std::map<std::string, UserIpAdress> m_coleccion;

public:
	bool MaxPersonajes(std::string sIp);

public:
	int VaciarColeccion();

};
#endif
