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

#ifndef MODINVISIBLES_H
#define MODINVISIBLES_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

/* ' 0 = viejo */
/* ' 1 = nuevo */
/* # CONST MODO_INVISIBILIDAD = 0 */
extern const int MODO_INVISIBILIDAD;

/* ' cambia el estado de invisibilidad a 1 o 0 dependiendo del modo: true o false */
/* ' */
void PonerInvisible(int UserIndex, bool estado);

#endif
