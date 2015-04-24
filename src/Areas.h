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

#ifndef MODAREAS_H
#define MODAREAS_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

/* ' Modulo de envio por areas compatible con la versión 9.10.x ... By DuNga */

/* '>>>>>>AREAS>>>>>AREAS>>>>>>>>AREAS>>>>>>>AREAS>>>>>>>>>> */
struct AreaInfo {
	int AreaPerteneceX{};
	int AreaPerteneceY{};

	int AreaReciveX{};
	int AreaReciveY{};

	/* '-!!! */
	int MinX{};
	/* '-!!! */
	int MinY{};

	int AreaID{};
};

struct ConnGroup {
	int CountEntrys{};
	int OptValue{};
	vb6::array<int> UserEntrys;
};

extern const int USER_NUEVO;

/* 'Cuidado: */
/* ' ¡¡¡LAS AREAS ESTÁN HARDCODEADAS!!! */

extern vb6::array<struct ConnGroup> ConnGroups;

void InitAreas();

void AreasOptimizacion();

void CheckUpdateNeededUser(int UserIndex, int Head, bool ButIndex = false);

void CheckUpdateNeededNpc(int NpcIndex, int Head);

void QuitarUser(int UserIndex, int Map);

void AgregarUser(int UserIndex, int Map, bool ButIndex = false);

void AgregarNpc(int NpcIndex);

#endif
