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

#ifndef INVUSUARIO_H
#define INVUSUARIO_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

bool TieneObjetosRobables(int UserIndex);

bool ClasePuedeUsarItem(int UserIndex, int ObjIndex, std::string& sMotivo);

void QuitarNewbieObj(int UserIndex);

void LimpiarInventario(int UserIndex);

void TirarOro(int Cantidad, int UserIndex);

void QuitarUserInvItem(int UserIndex, int Slot, int Cantidad);

void UpdateUserInv(bool UpdateAll, int UserIndex, int Slot);

void DropObj(int UserIndex, int Slot, int num, int Map, int X, int Y, bool isDrop = false);

void EraseObj(int num, int Map, int X, int Y);

void MakeObj(struct Obj & Obj, int Map, int X, int Y);

bool MeterItemEnInventario(int UserIndex, struct Obj & MiObj);

void GetObj(int UserIndex);

void Desequipar(int UserIndex, int Slot, bool RefreshChar);

bool SexoPuedeUsarItem(int UserIndex, int ObjIndex, std::string& sMotivo);

bool FaccionPuedeUsarItem(int UserIndex, int ObjIndex, std::string& sMotivo);

void EquiparInvItem(int UserIndex, int Slot);

bool CheckRazaUsaRopa(int UserIndex, int ItemIndex, std::string& sMotivo);

void UseInvItem(int UserIndex, int Slot);

void EnivarArmasConstruibles(int UserIndex);

void EnivarObjConstruibles(int UserIndex);

void EnivarArmadurasConstruibles(int UserIndex);

void TirarTodo(int UserIndex);

bool ItemSeCae(int index);

void TirarTodosLosItems(int UserIndex);

bool ItemNewbie(int ItemIndex);

void TirarTodosLosItemsNoNewbies(int UserIndex);

void TirarTodosLosItemsEnMochila(int UserIndex);

eOBJType getObjType(int ObjIndex);

void moveItem(int UserIndex, int originalSlot, int newSlot);

#endif
