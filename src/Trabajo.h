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

#ifndef TRABAJO_H
#define TRABAJO_H

#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

void DoPermanecerOculto(int UserIndex);

void DoOcultarse(int UserIndex);

void DoNavega(int UserIndex, struct ObjData & Barco, int Slot);

void FundirMineral(int UserIndex);

void FundirArmas(int UserIndex);

bool TieneObjetos(int ItemIndex, int cant, int UserIndex);

void QuitarObjetos(int ItemIndex, int cant, int UserIndex);

void HerreroQuitarMateriales(int UserIndex, int ItemIndex, int CantidadItems);

void CarpinteroQuitarMateriales(int UserIndex, int ItemIndex, int CantidadItems);

bool CarpinteroTieneMateriales(int UserIndex, int ItemIndex, int Cantidad, bool ShowMsg = false);

bool HerreroTieneMateriales(int UserIndex, int ItemIndex, int CantidadItems);

bool TieneMaterialesUpgrade(int UserIndex, int ItemIndex);

void QuitarMaterialesUpgrade(int UserIndex, int ItemIndex);

bool PuedeConstruir(int UserIndex, int ItemIndex, int CantidadItems);

bool PuedeConstruirHerreria(int ItemIndex);

void HerreroConstruirItem(int UserIndex, int ItemIndex);

bool PuedeConstruirCarpintero(int ItemIndex);

void CarpinteroConstruirItem(int UserIndex, int ItemIndex);

int MineralesParaLingote(iMinerales Lingote);

void DoLingotes(int UserIndex);

void DoFundir(int UserIndex);

void DoUpgrade(int UserIndex, int ItemIndex);

float ModNavegacion(eClass clase, int UserIndex);

float ModFundicion(eClass clase);

int ModCarpinteria(eClass clase);

float ModHerreriA(eClass clase);

int ModDomar(eClass clase);

int FreeMascotaIndex(int UserIndex);

void DoDomar(int UserIndex, int NpcIndex);

/* '' */
/* ' Checks if the user can tames a pet. */
/* ' */
/* ' @param integer userIndex The user id from who wants tame the pet. */
/* ' @param integer NPCindex The index of the npc to tome. */
/* ' @return boolean True if can, false if not. */
bool PuedeDomarMascota(int UserIndex, int NpcIndex);

void DoAdminInvisible(int UserIndex);

void TratarDeHacerFogata(int Map, int X, int Y, int UserIndex);

void DoPescar(int UserIndex);

void DoPescarRed(int UserIndex);

/* '' */
/* ' Try to steal an item / gold to another character */
/* ' */
/* ' @param LadrOnIndex Specifies reference to user that stoles */
/* ' @param VictimaIndex Specifies reference to user that is being stolen */

void DoRobar(int LadrOnIndex, int VictimaIndex);

/* '' */
/* ' Check if one item is stealable */
/* ' */
/* ' @param VictimaIndex Specifies reference to victim */
/* ' @param Slot Specifies reference to victim's inventory slot */
/* ' @return If the item is stealable */
bool ObjEsRobable(int VictimaIndex, int Slot);

/* '' */
/* ' Try to steal an item to another character */
/* ' */
/* ' @param LadrOnIndex Specifies reference to user that stoles */
/* ' @param VictimaIndex Specifies reference to user that is being stolen */
void RobarObjeto(int LadrOnIndex, int VictimaIndex);

void DoApunalar(int UserIndex, int VictimNpcIndex, int VictimUserIndex, int dano);

void DoAcuchillar(int UserIndex, int VictimNpcIndex, int VictimUserIndex, int dano);

void DoGolpeCritico(int UserIndex, int VictimNpcIndex, int VictimUserIndex, int dano);

void QuitarSta(int UserIndex, int Cantidad);

void DoTalar(int UserIndex, bool DarMaderaElfica = false);

void DoMineria(int UserIndex);

void DoMeditar(int UserIndex);

void DoDesequipar(int UserIndex, int VictimIndex);

void DoHurtar(int UserIndex, int VictimaIndex);

void DoHandInmo(int UserIndex, int VictimaIndex);

void Desarmar(int UserIndex, int VictimIndex);

int MaxItemsConstruibles(int UserIndex);

int MaxItemsExtraibles(int UserLevel);

void ImitateNpc(int UserIndex, int NpcIndex);

#endif
