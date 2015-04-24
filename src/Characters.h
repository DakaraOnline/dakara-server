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

#ifndef CHARACTERS_H
#define CHARACTERS_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

/* '' */
/* ' Value representing invalid indexes. */
extern const int INVALID_INDEX;

/* '' */
/* ' Retrieves the UserList index of the user with the give char index. */
/* ' */
/* ' @param    CharIndex   The char index being used by the user to be retrieved. */
/* ' @return   The index of the user with the char placed in CharIndex or INVALID_INDEX if it's not a user or valid char index. */
/* ' @see      INVALID_INDEX */

int CharIndexToUserIndex(int CharIndex);

#endif
