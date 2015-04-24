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

#ifndef EXTRA_H
#define EXTRA_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

bool EsNewbie(int UserIndex);

bool esArmada(int UserIndex);

bool esCaos(int UserIndex);

bool EsGm(int UserIndex);

void DoTileEvents(int UserIndex, int Map, int X, int Y);

bool InRangoVision(int UserIndex, int X, int Y);

bool InVisionRangeAndMap(int UserIndex, struct WorldPos & OtherUserPos);

bool InRangoVisionNPC(int NpcIndex, int X, int Y);

bool InMapBounds(int Map, int X, int Y);

bool RhombLegalPos(struct WorldPos & Pos, int & vX, int & vY, int Distance, bool PuedeAgua = false,
		bool PuedeTierra = true, bool CheckExitTile = false);

bool RhombLegalTilePos(struct WorldPos & Pos, int & vX, int & vY, int Distance, int ObjIndex, int ObjAmount,
		bool PuedeAgua, bool PuedeTierra);

bool HayObjeto(int mapa, int X, int Y, int ObjIndex, int ObjAmount);

void ClosestLegalPos(struct WorldPos Pos, struct WorldPos & nPos, bool PuedeAgua = false, bool PuedeTierra =
		true, bool CheckExitTile = false);

void ClosestStablePos(struct WorldPos Pos, struct WorldPos & nPos);

int NameIndex(std::string Name);

bool CheckForSameIP(int UserIndex, std::string UserIP);

bool CheckForSameName(std::string Name, int& OtherUserIndex);

void HeadtoPos(eHeading Head, struct WorldPos & Pos);

void HeadtoPos(eHeading Head, struct Position & Pos);

bool LegalPos(int Map, int X, int Y, bool PuedeAgua = false, bool PuedeTierra = true, bool CheckExitTile =
		false);

bool MoveToLegalPos(int Map, int X, int Y, bool PuedeAgua = false, bool PuedeTierra = true);

void FindLegalPos(int UserIndex, int Map, int & X, int & Y);

bool LegalPosNPC(int Map, int X, int Y, int AguaValida, bool IsPet = false);

void SendHelp(int index);

void Expresar(int NpcIndex, int UserIndex);

void LookatTile(int UserIndex, int Map, int X, int Y);

eHeading FindDirection(struct WorldPos Pos, struct WorldPos Target);

bool ItemNoEsDeMapa(int index, bool bIsExit);

bool MostrarCantidad(int index);

bool EsObjetoFijo(eOBJType OBJType);

int RestrictStringToByte(std::string x);

std::string RestrictByteToString(int x);

int TerrainStringToByte(std::string x);

std::string TerrainByteToString(int x);

#endif
