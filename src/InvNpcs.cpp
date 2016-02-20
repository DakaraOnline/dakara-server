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

#include "stdafx.h"

#include "InvNpcs.h"

struct WorldPos TirarItemAlPiso(struct WorldPos Pos, struct Obj Obj, bool NotPirata) {
	struct WorldPos retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	struct WorldPos NuevaPos;
	NuevaPos.X = 0;
	NuevaPos.Y = 0;

	Tilelibre(Pos, NuevaPos, Obj, NotPirata, true);
	if (NuevaPos.X != 0 && NuevaPos.Y != 0) {
		MakeObj(Obj, Pos.Map, NuevaPos.X, NuevaPos.Y);
	}
	retval = NuevaPos;

	return retval;
}

void NPC_TIRAR_ITEMS(struct npc & npc, bool IsPretoriano) {
	/* '*************************************************** */
	/* 'Autor: Unknown (orginal version) */
	/* 'Last Modification: 28/11/2009 */
	/* 'Give away npc's items. */
	/* '28/11/2009: ZaMa - Implementado drops complejos */
	/* '02/04/2010: ZaMa - Los pretos vuelven a tirar oro. */
	/* '10/04/2011: ZaMa - Logueo los objetos logueables dropeados. */
	/* '*************************************************** */

	int i;
	struct Obj MiObj;
	int NroDrop;
	int Random;
	int ObjIndex;

	/* ' Tira todo el inventario */
	if (IsPretoriano) {
		for (i = (1); i <= (MAX_INVENTORY_SLOTS); i++) {
			if (npc.Invent.Object[i].ObjIndex > 0) {
				MiObj.Amount = npc.Invent.Object[i].Amount;
				MiObj.ObjIndex = npc.Invent.Object[i].ObjIndex;
				TirarItemAlPiso(npc.Pos, MiObj);
			}
		}

		/* ' Dropea oro? */
		if (npc.GiveGLD > 0) {
			TirarOroNpc(npc.GiveGLD, npc.Pos);
		}

		return;
	}

	Random = RandomNumber(1, 100);

	/* ' Tiene 10% de prob de no tirar nada */
	if (Random <= 90) {
		NroDrop = 1;

		if (Random <= 10) {
			NroDrop = NroDrop + 1;

			for (i = (1); i <= (3); i++) {
				/* ' 10% de ir pasando de etapas */
				if (RandomNumber(1, 100) <= 10) {
					NroDrop = NroDrop + 1;
				} else {
					break;
				}
			}

		}

		ObjIndex = npc.Drop[NroDrop].ObjIndex;
		if (ObjIndex > 0) {

			if (ObjIndex == iORO) {
				TirarOroNpc(npc.Drop[NroDrop].Amount, npc.Pos);
			} else {
				MiObj.Amount = npc.Drop[NroDrop].Amount;
				MiObj.ObjIndex = ObjIndex;

				TirarItemAlPiso(npc.Pos, MiObj);

				if (ObjData[ObjIndex].Log == 1) {
					LogDesarrollo(
							npc.Name + " dropeó " + vb6::CStr(MiObj.Amount) + " " + ObjData[ObjIndex].Name + "["
									+ vb6::CStr(ObjIndex) + "]");
				}
			}
		}
	}
}

bool QuedanItems(int NpcIndex, int ObjIndex) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int i;
	if (Npclist[NpcIndex].Invent.NroItems > 0) {
		for (i = (1); i <= (MAX_INVENTORY_SLOTS); i++) {
			if (Npclist[NpcIndex].Invent.Object[i].ObjIndex == ObjIndex) {
				retval = true;
				return retval;
			}
		}
	}
	retval = false;
	return retval;
}

/* '' */
/* ' Gets the amount of a certain item that an npc has. */
/* ' */
/* ' @param npcIndex Specifies reference to npcmerchant */
/* ' @param ObjIndex Specifies reference to object */
/* ' @return   The amount of the item that the npc has */
/* ' @remarks This function reads the Npc.dat file */
int EncontrarCant(int NpcIndex, int ObjIndex) {
	int retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 03/09/08 */
	/* 'Last Modification By: Marco Vanotti (Marco) */
	/* ' - 03/09/08 EncontrarCant now returns 0 if the npc doesn't have it (Marco) */
	/* '*************************************************** */

	/* 'Devuelve la cantidad original del obj de un npc */

	std::string ln;
	std::string npcfile;
	int i;

	npcfile = GetDatPath(DATPATH::NPCs);

	for (i = (1); i <= (MAX_INVENTORY_SLOTS); i++) {
		ln = GetVar(npcfile, "NPC" + vb6::CStr(Npclist[NpcIndex].Numero), "Obj" + vb6::CStr(i));
		if (ObjIndex == vb6::val(ReadField(1, ln, 45))) {
			retval = (int) vb6::val(ReadField(2, ln, 45));
			return retval;
		}
	}

	retval = 0;

	return retval;
}

void ResetNpcInv(int NpcIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int i;

	Npclist[NpcIndex].Invent.NroItems = 0;

	for (i = (1); i <= (MAX_INVENTORY_SLOTS); i++) {
		Npclist[NpcIndex].Invent.Object[i].ObjIndex = 0;
		Npclist[NpcIndex].Invent.Object[i].Amount = 0;
	}

	Npclist[NpcIndex].InvReSpawn = 0;

}

/* '' */
/* ' Removes a certain amount of items from a slot of an npc's inventory */
/* ' */
/* ' @param npcIndex Specifies reference to npcmerchant */
/* ' @param Slot Specifies reference to npc's inventory's slot */
/* ' @param antidad Specifies amount of items that will be removed */
void QuitarNpcInvItem(int NpcIndex, int Slot, int Cantidad) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 23/11/2009 */
	/* 'Last Modification By: Marco Vanotti (Marco) */
	/* ' - 03/09/08 Now this sub checks that te npc has an item before respawning it (Marco) */
	/* '23/11/2009: ZaMa - Optimizacion de codigo. */
	/* '*************************************************** */
	int ObjIndex;
	int iCant;

	ObjIndex = Npclist[NpcIndex].Invent.Object[Slot].ObjIndex;

	/* 'Quita un Obj */
	if (ObjData[Npclist[NpcIndex].Invent.Object[Slot].ObjIndex].Crucial == 0) {
		Npclist[NpcIndex].Invent.Object[Slot].Amount = Npclist[NpcIndex].Invent.Object[Slot].Amount
				- Cantidad;

		if (Npclist[NpcIndex].Invent.Object[Slot].Amount <= 0) {
			Npclist[NpcIndex].Invent.NroItems = Npclist[NpcIndex].Invent.NroItems - 1;
			Npclist[NpcIndex].Invent.Object[Slot].ObjIndex = 0;
			Npclist[NpcIndex].Invent.Object[Slot].Amount = 0;
			if (Npclist[NpcIndex].Invent.NroItems == 0 && Npclist[NpcIndex].InvReSpawn != 1) {
				/* 'Reponemos el inventario */
				CargarInvent(NpcIndex);
			}
		}
	} else {
		Npclist[NpcIndex].Invent.Object[Slot].Amount = Npclist[NpcIndex].Invent.Object[Slot].Amount
				- Cantidad;

		if (Npclist[NpcIndex].Invent.Object[Slot].Amount <= 0) {
			Npclist[NpcIndex].Invent.NroItems = Npclist[NpcIndex].Invent.NroItems - 1;
			Npclist[NpcIndex].Invent.Object[Slot].ObjIndex = 0;
			Npclist[NpcIndex].Invent.Object[Slot].Amount = 0;

			if (!QuedanItems(NpcIndex, ObjIndex)) {
				/* 'Check if the item is in the npc's dat. */
				iCant = EncontrarCant(NpcIndex, ObjIndex);
				if (iCant) {
					Npclist[NpcIndex].Invent.Object[Slot].ObjIndex = ObjIndex;
					Npclist[NpcIndex].Invent.Object[Slot].Amount = iCant;
					Npclist[NpcIndex].Invent.NroItems = Npclist[NpcIndex].Invent.NroItems + 1;
				}
			}

			if (Npclist[NpcIndex].Invent.NroItems == 0 && Npclist[NpcIndex].InvReSpawn != 1) {
				/* 'Reponemos el inventario */
				CargarInvent(NpcIndex);
			}
		}
	}
}

void CargarInvent(int NpcIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	/* 'Vuelve a cargar el inventario del npc NpcIndex */
	int LoopC;
	std::string ln;
	std::string npcfile;

	npcfile = GetDatPath(DATPATH::NPCs);

	Npclist[NpcIndex].Invent.NroItems = vb6::val(
			GetVar(npcfile, "NPC" + vb6::CStr(Npclist[NpcIndex].Numero), "NROITEMS"));
	Npclist[NpcIndex].Invent.NroItems = vb6::Constrain(Npclist[NpcIndex].Invent.NroItems, 0, MAX_INVENTORY_SLOTS);

	for (LoopC = (1); LoopC <= (Npclist[NpcIndex].Invent.NroItems); LoopC++) {
		ln = GetVar(npcfile, "NPC" + vb6::CStr(Npclist[NpcIndex].Numero), "Obj" + vb6::CStr(LoopC));
		Npclist[NpcIndex].Invent.Object[LoopC].ObjIndex = vb6::val(ReadField(1, ln, 45));
		Npclist[NpcIndex].Invent.Object[LoopC].Amount = vb6::val(ReadField(2, ln, 45));

	}

}

void TirarOroNpc(int Cantidad, struct WorldPos & Pos) {
	/* '*************************************************** */
	/* 'Autor: ZaMa */
	/* 'Last Modification: 13/02/2010 */
	/* '*************************************************** */

	if (Cantidad > 0) {
		struct Obj MiObj;
		int RemainingGold;

		RemainingGold = Cantidad;

		while ((RemainingGold > 0)) {

			/* ' Tira pilon de 10k */
			if (RemainingGold > MAX_INVENTORY_OBJS) {
				MiObj.Amount = MAX_INVENTORY_OBJS;
				RemainingGold = RemainingGold - MAX_INVENTORY_OBJS;

				/* ' Tira lo que quede */
			} else {
				MiObj.Amount = RemainingGold;
				RemainingGold = 0;
			}

			MiObj.ObjIndex = iORO;

			TirarItemAlPiso(Pos, MiObj);
		}
	}
}
