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

#ifndef MODHEXASTRINGS_H
#define MODHEXASTRINGS_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"


/* 'Modulo realizado por Gonzalo Larralde(CDT) <gonzalolarralde@yahoo.com.ar> */
/* 'Para la conversion a caracteres de cadenas MD5 y de */
/* 'semi encriptación de cadenas por ascii table offset */

 std::string hexMd52Asc(std::string MD5);
 
 int hexHex2Dec(std::string hex);
 
 std::string txtOffset(std::string Text, int off);
 
#endif
