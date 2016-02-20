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

#include "Invisibles.h"

/* ' 0 = viejo */
/* ' 1 = nuevo */
/* # CONST MODO_INVISIBILIDAD = 0 */
const int MODO_INVISIBILIDAD = 0;

/* ' cambia el estado de invisibilidad a 1 o 0 dependiendo del modo: true o false */
/* ' */
void PonerInvisible(int UserIndex, bool estado) {
	/* # IF MODO_INVISIBILIDAD = 0 THEN */

	UserList[UserIndex].flags.invisible = vb6::IIf(estado, 1, 0);
	UserList[UserIndex].flags.Oculto = vb6::IIf(estado, 1, 0);
	UserList[UserIndex].Counters.Invisibilidad = 0;

	SetInvisible(UserIndex, UserList[UserIndex].Char.CharIndex, !estado);
	/* 'Call SendData(SendTarget.ToPCArea, UserIndex, PrepareMessageSetInvisible(UserList(UserIndex).Char.CharIndex, Not estado)) */

	/* # ELSE */

	/* # END IF */
}
