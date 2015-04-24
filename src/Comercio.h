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

#ifndef MODSISTEMACOMERCIO_H
#define MODSISTEMACOMERCIO_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

extern const int REDUCTOR_PRECIOVENTA;

/* '' */
/* ' Makes a trade. (Buy or Sell) */
/* ' */
/* ' @param Modo The trade type (sell or buy) */
/* ' @param UserIndex Specifies the index of the user */
/* ' @param NpcIndex specifies the index of the npc */
/* ' @param Slot Specifies which slot are you trying to sell / buy */
/* ' @param Cantidad Specifies how many items in that slot are you trying to sell / buy */
void Comercio(eModoComercio Modo, int UserIndex, int NpcIndex, int Slot, int Cantidad);

void IniciarComercioNPC(int UserIndex);

int SlotEnNPCInv(int NpcIndex, int Objeto, int Cantidad);

float Descuento(int UserIndex);

/* '' */
/* ' Send the inventory of the Npc to the user */
/* ' */
/* ' @param userIndex The index of the User */
/* ' @param npcIndex The index of the NPC */

void EnviarNpcInv(int UserIndex, int NpcIndex);

/* '' */
/* ' Devuelve el valor de venta del objeto */
/* ' */
/* ' @param ObjIndex  El número de objeto al cual le calculamos el precio de venta */

float SalePrice(int ObjIndex);

#endif
