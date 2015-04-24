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

#ifndef MODHECHIZOS_H
#define MODHECHIZOS_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

extern const int HELEMENTAL_FUEGO;
extern const int HELEMENTAL_TIERRA;

void NpcLanzaSpellSobreUser(int NpcIndex, int UserIndex, int Spell, bool DecirPalabras = false,
		bool IgnoreVisibilityCheck = false);

void SendSpellEffects(int UserIndex, int NpcIndex, int Spell, bool DecirPalabras);

void NpcLanzaSpellSobreNpc(int NpcIndex, int TargetNPC, int SpellIndex, bool DecirPalabras = false);

bool TieneHechizo(int i, int UserIndex);

void AgregarHechizo(int UserIndex, int Slot);

void DecirPalabrasMagicas(std::string SpellWords, int UserIndex);

/* '' */
/* ' Check if an user can cast a certain spell */
/* ' */
/* ' @param UserIndex Specifies reference to user */
/* ' @param HechizoIndex Specifies reference to spell */
/* ' @return   True if the user can cast the spell, otherwise returns false */
bool PuedeLanzar(int UserIndex, int HechizoIndex);

void HechizoTerrenoEstado(int UserIndex, bool & b);

/* '' */
/* ' Le da propiedades al nuevo npc */
/* ' */
/* ' @param UserIndex  Indice del usuario que invoca. */
/* ' @param b  Indica si se termino la operación. */

void HechizoInvocacion(int UserIndex, bool & HechizoCasteado);

void HandleHechizoTerreno(int UserIndex, int SpellIndex);

void HandleHechizoUsuario(int UserIndex, int SpellIndex);

void HandleHechizoNPC(int UserIndex, int HechizoIndex);

void LanzarHechizo(int SpellIndex, int UserIndex);

void HechizoEstadoUsuario(int UserIndex, bool & HechizoCasteado);

void HechizoEstadoNPC(int NpcIndex, int SpellIndex, bool & HechizoCasteado, int UserIndex);

void HechizoPropNPC(int SpellIndex, int NpcIndex, int UserIndex, bool & HechizoCasteado);

void InfoHechizo(int UserIndex);

bool HechizoPropUsuario(int UserIndex);

bool CanSupportUser(int CasterIndex, int TargetIndex, bool DoCriminal = false);

void UpdateUserHechizos(bool UpdateAll, int UserIndex, int Slot);

bool CanSupportNpc(int CasterIndex, int TargetIndex);

void ChangeUserHechizo(int UserIndex, int Slot, int Hechizo);

void DesplazarHechizo(int UserIndex, int Dire, int HechizoDesplazado);

void DisNobAuBan(int UserIndex, int NoblePts, int BandidoPts);

#endif
