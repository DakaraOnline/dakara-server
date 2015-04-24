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

#ifndef MODBANCO_H
#define MODBANCO_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

void IniciarDeposito(int UserIndex);

void SendBanObj(int UserIndex, int Slot, struct UserOBJ Object);

void UpdateBanUserInv(bool UpdateAll, int UserIndex, int Slot);

void UserRetiraItem(int UserIndex, int i, int Cantidad);

void UserReciveObj(int UserIndex, int ObjIndex, int Cantidad);

void QuitarBancoInvItem(int UserIndex, int Slot, int Cantidad);

void UpdateVentanaBanco(int UserIndex);

void UserDepositaItem(int UserIndex, int Item, int Cantidad);

void UserDejaObj(int UserIndex, int ObjIndex, int Cantidad);

void SendUserBovedaTxt(int sendIndex, int UserIndex);

void SendUserBovedaTxtFromChar(int sendIndex, std::string charName);

#endif
