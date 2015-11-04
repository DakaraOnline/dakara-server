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

#ifndef NPCS_H
#define NPCS_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

void QuitarMascota(int UserIndex, int NpcIndex);

void QuitarMascotaNpc(int Maestro);

void MuereNpc(int NpcIndex, int UserIndex);

void ResetNpcFlags(int NpcIndex);

void ResetNpcCounters(int NpcIndex);

void ResetNpcCharInfo(int NpcIndex);

void ResetNpcCriatures(int NpcIndex);

void ResetExpresiones(int NpcIndex);

void ResetNpcMainInfo(int NpcIndex);

void QuitarNPC(int NpcIndex);

void QuitarPet(int UserIndex, int NpcIndex);

bool TestSpawnTrigger(struct WorldPos Pos, bool PuedeAgua = false);

int CrearNPC(int NroNPC, int mapa, struct WorldPos OrigPos, int CustomHead = int());

void MakeNPCChar(bool toMap, int sndIndex, int NpcIndex, int Map, int X, int Y);

void ChangeNPCChar(int NpcIndex, int body, int Head, eHeading heading);

void EraseNPCChar(int NpcIndex);

bool MoveNPCChar(int NpcIndex, int nHeading);

int NextOpenNPC();

void NpcEnvenenarUser(int UserIndex);

int SpawnNpc(int NpcIndex, struct WorldPos Pos, bool FX, bool Respawn);

void ReSpawnNpc(const struct npc &MiNPC);

void NPCTirarOro(struct npc & MiNPC);

int OpenNPC(int NpcNumber, bool Respawn = true);

void DoFollow(int NpcIndex, std::string UserName);

void FollowAmo(int NpcIndex);

void ValidarPermanenciaNpc(int NpcIndex);

#endif
