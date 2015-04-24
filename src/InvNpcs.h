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

#ifndef INVNPC_H
#define INVNPC_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

struct WorldPos TirarItemAlPiso(struct WorldPos Pos, struct Obj Obj, bool NotPirata = true);

void NPC_TIRAR_ITEMS(struct npc & npc, bool IsPretoriano);

bool QuedanItems(int NpcIndex, int ObjIndex);

/* '' */
/* ' Gets the amount of a certain item that an npc has. */
/* ' */
/* ' @param npcIndex Specifies reference to npcmerchant */
/* ' @param ObjIndex Specifies reference to object */
/* ' @return   The amount of the item that the npc has */
/* ' @remarks This function reads the Npc.dat file */
int EncontrarCant(int NpcIndex, int ObjIndex);

void ResetNpcInv(int NpcIndex);

/* '' */
/* ' Removes a certain amount of items from a slot of an npc's inventory */
/* ' */
/* ' @param npcIndex Specifies reference to npcmerchant */
/* ' @param Slot Specifies reference to npc's inventory's slot */
/* ' @param antidad Specifies amount of items that will be removed */
void QuitarNpcInvItem(int NpcIndex, int Slot, int Cantidad);

void CargarInvent(int NpcIndex);

void TirarOroNpc(int Cantidad, struct WorldPos & Pos);

#endif
