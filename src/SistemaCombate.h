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

#ifndef SISTEMACOMBATE_H
#define SISTEMACOMBATE_H

#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

extern const int MAXDISTANCIAARCO;
extern const int MAXDISTANCIAMAGIA;

int MinimoInt(int a, int b);

int MaximoInt(int a, int b);

int PoderEvasionEscudo(int UserIndex);

int PoderEvasion(int UserIndex);

int PoderAtaqueArma(int UserIndex);

int PoderAtaqueProyectil(int UserIndex);

int PoderAtaqueWrestling(int UserIndex);

bool UserImpactoNpc(int UserIndex, int NpcIndex);

bool NpcImpacto(int NpcIndex, int UserIndex);

int CalcularDano(int UserIndex, int NpcIndex = 0);

void UserDanoNpc(int UserIndex, int NpcIndex);

void NpcDano(int NpcIndex, int UserIndex);

void RestarCriminalidad(int UserIndex);

void CheckPets(int NpcIndex, int UserIndex, bool CheckElementales = true);

void AllFollowAmo(int UserIndex);

bool NpcAtacaUser(int NpcIndex, int UserIndex);

bool NpcImpactoNpc(int Atacante, int Victima);

void NpcDanoNpc(int Atacante, int Victima);

void NpcAtacaNpc(int Atacante, int Victima, bool cambiarMOvimiento = true);

bool UsuarioAtacaNpc(int UserIndex, int NpcIndex);

void UsuarioAtaca(int UserIndex);

bool UsuarioImpacto(int AtacanteIndex, int VictimaIndex);

bool UsuarioAtacaUsuario(int AtacanteIndex, int VictimaIndex);

void UserDanoUser(int AtacanteIndex, int VictimaIndex);

void UsuarioAtacadoPorUsuario(int AttackerIndex, int VictimIndex);

void AllMascotasAtacanUser(int victim, int Maestro);

bool PuedeAtacar(int AttackerIndex, int VictimIndex);

bool PuedeAtacarNPC(int AttackerIndex, int NpcIndex, bool Paraliza = false, bool IsPet = false);

bool SameClan(int UserIndex, int OtherUserIndex);

bool SameParty(int UserIndex, int OtherUserIndex);

void CalcularDarExp(int UserIndex, int NpcIndex, int ElDano);

eTrigger6 TriggerZonaPelea(int Origen, int Destino);

void UserEnvenena(int AtacanteIndex, int VictimaIndex);

void LanzarProyectil(int UserIndex, int X, int Y);

#endif
