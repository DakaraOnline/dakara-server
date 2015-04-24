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

#ifndef AI_H
#define AI_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

extern const int ELEMENTALFUEGO;
extern const int ELEMENTALTIERRA;
extern const int ELEMENTALAGUA;

/* 'Damos a los NPCs el mismo rango de visiï¿½n que un PJ */
extern const int RANGO_VISION_X;
extern const int RANGO_VISION_Y;

void GuardiasAI(int NpcIndex, bool DelCaos);

/* '' */
/* ' Handles the evil npcs' artificial intelligency. */
/* ' */
/* ' @param NpcIndex Specifies reference to the npc */
void HostilMalvadoAI(int NpcIndex);

void HostilBuenoAI(int NpcIndex);

void IrUsuarioCercano(int NpcIndex);

/* '' */
/* ' Makes a Pet / Summoned Npc to Follow an enemy */
/* ' */
/* ' @param NpcIndex Specifies reference to the npc */
void SeguirAgresor(int NpcIndex);

void RestoreOldMovement(int NpcIndex);

void PersigueCiudadano(int NpcIndex);

void PersigueCriminal(int NpcIndex);

void SeguirAmo(int NpcIndex);

void AiNpcAtacaNpc(int NpcIndex);

void AiNpcObjeto(int NpcIndex);

void NPCAI(int NpcIndex);

bool UserNear(int NpcIndex);

bool ReCalculatePath(int NpcIndex);

bool PathEnd(int NpcIndex);

bool FollowPath(int NpcIndex);

bool PathFindingAI(int NpcIndex);

void NpcLanzaUnSpell(int NpcIndex, int UserIndex);

void NpcLanzaUnSpellSobreNpc(int NpcIndex, int TargetNPC);

#endif
