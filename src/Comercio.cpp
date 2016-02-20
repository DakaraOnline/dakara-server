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

#include "Comercio.h"

const int REDUCTOR_PRECIOVENTA = 3;

/* '' */
/* ' Makes a trade. (Buy or Sell) */
/* ' */
/* ' @param Modo The trade type (sell or buy) */
/* ' @param UserIndex Specifies the index of the user */
/* ' @param NpcIndex specifies the index of the npc */
/* ' @param Slot Specifies which slot are you trying to sell / buy */
/* ' @param Cantidad Specifies how many items in that slot are you trying to sell / buy */
void Comercio(eModoComercio Modo, int UserIndex, int NpcIndex, int Slot, int Cantidad) {
	/* '************************************************* */
	/* 'Author: Nacho (Integer) */
	/* 'Last modified: 07/06/2010 */
	/* '27/07/08 (MarKoxX) | New changes in the way of trading (now when you buy it rounds to ceil and when you sell it rounds to floor) */
	/* '  - 06/13/08 (NicoNZ) */
	/* '07/06/2010: ZaMa - Los objetos se loguean si superan la cantidad de 1k (antes era solo si eran 1k). */
	/* '************************************************* */
	int Precio;
	struct Obj Objeto;

	if (Cantidad < 1 || Slot < 1) {
		return;
	}

	if (Modo == eModoComercio_Compra) {
		if (Slot > MAX_INVENTORY_SLOTS) {
			return;
		} else if (Cantidad > MAX_INVENTORY_OBJS) {
			SendData(SendTarget_ToAll, 0,
					dakara::protocol::server::BuildConsoleMsg(
							UserList[UserIndex].Name + " ha sido baneado por el sistema anti-cheats.",
							FontTypeNames_FONTTYPE_FIGHT));
			Ban(UserList[UserIndex].Name, "Sistema Anti Cheats",
					"Intentar hackear el sistema de comercio. Quiso comprar demasiados ítems:" + vb6::CStr(Cantidad));
			UserList[UserIndex].flags.Ban = 1;
			WriteErrorMsg(UserIndex, "Has sido baneado por el Sistema AntiCheat.");
			FlushBuffer(UserIndex);
			CloseSocket(UserIndex);
			return;
		} else if (!(Npclist[NpcIndex].Invent.Object[Slot].Amount > 0)) {
			return;
		}

		if (Cantidad > Npclist[NpcIndex].Invent.Object[Slot].Amount) {
			Cantidad = Npclist[UserList[UserIndex].flags.TargetNPC].Invent.Object[Slot].Amount;
		}

		Objeto.Amount = Cantidad;
		Objeto.ObjIndex = Npclist[NpcIndex].Invent.Object[Slot].ObjIndex;

		/* 'El precio, cuando nos venden algo, lo tenemos que redondear para arriba. */
		/* 'Es decir, 1.1 = 2, por lo cual se hace de la siguiente forma Precio = Clng(PrecioFinal + 0.5) Siempre va a darte el proximo numero. O el "Techo" (MarKoxX) */

		Precio = vb6::CLng(
				(ObjData[Npclist[NpcIndex].Invent.Object[Slot].ObjIndex].Valor / Descuento(UserIndex)
						* Cantidad) + 0.5);

		if (UserList[UserIndex].Stats.GLD < Precio) {
			WriteConsoleMsg(UserIndex, "No tienes suficiente dinero.", FontTypeNames_FONTTYPE_INFO);
			return;
		}

		if (MeterItemEnInventario(UserIndex, Objeto) == false) {
			/* 'Call WriteConsoleMsg(UserIndex, "No puedes cargar mas objetos.", FontTypeNames.FONTTYPE_INFO) */
			EnviarNpcInv(UserIndex, UserList[UserIndex].flags.TargetNPC);
			WriteTradeOK(UserIndex);
			return;
		}

		UserList[UserIndex].Stats.GLD = UserList[UserIndex].Stats.GLD - Precio;

		QuitarNpcInvItem(UserList[UserIndex].flags.TargetNPC, vb6::CByte(Slot), Cantidad);

		/* 'Bien, ahora logueo de ser necesario. Pablo (ToxicWaste) 07/09/07 */
		/* 'Es un Objeto que tenemos que loguear? */
		if (ObjData[Objeto.ObjIndex].Log == 1) {
			LogDesarrollo(
					UserList[UserIndex].Name + " compró del NPC " + std::to_string(Objeto.Amount) + " "
							+ ObjData[Objeto.ObjIndex].Name);
			/* 'Es mucha cantidad? */
		} else if (Objeto.Amount >= 1000) {
			/* 'Si no es de los prohibidos de loguear, lo logueamos. */
			if (ObjData[Objeto.ObjIndex].NoLog != 1) {
				LogDesarrollo(
						UserList[UserIndex].Name + " compró del NPC " + std::to_string(Objeto.Amount) + " "
								+ ObjData[Objeto.ObjIndex].Name);
			}
		}

		/* 'Agregado para que no se vuelvan a vender las llaves si se recargan los .dat. */
		if (ObjData[Objeto.ObjIndex].OBJType == eOBJType_otLlaves) {
			WriteVar(GetDatPath(DATPATH::NPCs),
					"NPC" + vb6::CStr(Npclist[NpcIndex].Numero),
					"obj" + vb6::CStr(Slot),
					vb6::CStr(Objeto.ObjIndex) + "-0");
			logVentaCasa(UserList[UserIndex].Name + " compró " + ObjData[Objeto.ObjIndex].Name);
		}

	} else if (Modo == eModoComercio_Venta) {

		if (Cantidad > UserList[UserIndex].Invent.Object[Slot].Amount) {
			Cantidad = UserList[UserIndex].Invent.Object[Slot].Amount;
		}

		Objeto.Amount = Cantidad;
		Objeto.ObjIndex = UserList[UserIndex].Invent.Object[Slot].ObjIndex;

		if (Objeto.ObjIndex == 0) {
			return;

		} else if (ObjData[Objeto.ObjIndex].Intransferible == 1
				|| ObjData[Objeto.ObjIndex].NoComerciable == 1) {
			WriteConsoleMsg(UserIndex, "No puedes vender este tipo de objeto.", FontTypeNames_FONTTYPE_INFO);
			return;
		} else if ((Npclist[NpcIndex].TipoItems != ObjData[Objeto.ObjIndex].OBJType
				&& Npclist[NpcIndex].TipoItems != eOBJType_otCualquiera) || Objeto.ObjIndex == iORO) {
			WriteConsoleMsg(UserIndex, "Lo siento, no estoy interesado en este tipo de objetos.",
					FontTypeNames_FONTTYPE_INFO);
			EnviarNpcInv(UserIndex, UserList[UserIndex].flags.TargetNPC);
			WriteTradeOK(UserIndex);
			return;
		} else if (ObjData[Objeto.ObjIndex].Real == 1) {
			if (Npclist[NpcIndex].Name != "SR") {
				WriteConsoleMsg(UserIndex,
						"Las armaduras del ejército real sólo pueden ser vendidas a los sastres reales.",
						FontTypeNames_FONTTYPE_INFO);
				EnviarNpcInv(UserIndex, UserList[UserIndex].flags.TargetNPC);
				WriteTradeOK(UserIndex);
				return;
			}
		} else if (ObjData[Objeto.ObjIndex].Caos == 1) {
			if (Npclist[NpcIndex].Name != "SC") {
				WriteConsoleMsg(UserIndex,
						"Las armaduras de la legión oscura sólo pueden ser vendidas a los sastres del demonio.",
						FontTypeNames_FONTTYPE_INFO);
				EnviarNpcInv(UserIndex, UserList[UserIndex].flags.TargetNPC);
				WriteTradeOK(UserIndex);
				return;
			}
		} else if (UserList[UserIndex].Invent.Object[Slot].Amount < 0 || Cantidad == 0) {
			return;
		} else if (Slot<vb6::LBound(UserList[UserIndex].Invent.Object) || Slot>vb6::UBound(UserList[UserIndex].Invent.Object)) {
			EnviarNpcInv(UserIndex, UserList[UserIndex].flags.TargetNPC);
			return;
		} else if (UserTienePrivilegio(UserIndex, PlayerType_Consejero)) {
			WriteConsoleMsg(UserIndex, "No puedes vender ítems.", FontTypeNames_FONTTYPE_WARNING);
			EnviarNpcInv(UserIndex, UserList[UserIndex].flags.TargetNPC);
			WriteTradeOK(UserIndex);
			return;
		}

		QuitarUserInvItem(UserIndex, Slot, Cantidad);

		/* 'Precio = Round(ObjData(Objeto.ObjIndex).valor / REDUCTOR_PRECIOVENTA * Cantidad, 0) */
		Precio = vb6::Fix(SalePrice(Objeto.ObjIndex) * Cantidad);
		UserList[UserIndex].Stats.GLD = UserList[UserIndex].Stats.GLD + Precio;

		if (UserList[UserIndex].Stats.GLD > MAXORO) {
			UserList[UserIndex].Stats.GLD = MAXORO;
		}

		int NpcSlot;
		NpcSlot = SlotEnNPCInv(NpcIndex, Objeto.ObjIndex, Objeto.Amount);

		/* 'Slot valido */
		if (NpcSlot <= MAX_INVENTORY_SLOTS) {
			/* 'Mete el obj en el slot */
			Npclist[NpcIndex].Invent.Object[NpcSlot].ObjIndex = Objeto.ObjIndex;
			Npclist[NpcIndex].Invent.Object[NpcSlot].Amount = Npclist[NpcIndex].Invent.Object[NpcSlot].Amount
					+ Objeto.Amount;
			if (Npclist[NpcIndex].Invent.Object[NpcSlot].Amount > MAX_INVENTORY_OBJS) {
				Npclist[NpcIndex].Invent.Object[NpcSlot].Amount = MAX_INVENTORY_OBJS;
			}
		}

		/* 'Bien, ahora logueo de ser necesario. Pablo (ToxicWaste) 07/09/07 */
		/* 'Es un Objeto que tenemos que loguear? */
		if (ObjData[Objeto.ObjIndex].Log == 1) {
			LogDesarrollo(
					UserList[UserIndex].Name + " vendió al NPC " + std::to_string(Objeto.Amount) + " "
							+ ObjData[Objeto.ObjIndex].Name);
			/* 'Es mucha cantidad? */
		} else if (Objeto.Amount >= 1000) {
			/* 'Si no es de los prohibidos de loguear, lo logueamos. */
			if (ObjData[Objeto.ObjIndex].NoLog != 1) {
				LogDesarrollo(
						UserList[UserIndex].Name + " vendió al NPC " + std::to_string(Objeto.Amount) + " "
								+ ObjData[Objeto.ObjIndex].Name);
			}
		}

	}

	UpdateUserInv(true, UserIndex, 0);
	WriteUpdateUserStats(UserIndex);
	EnviarNpcInv(UserIndex, UserList[UserIndex].flags.TargetNPC);
	WriteTradeOK(UserIndex);

	SubirSkill(UserIndex, eSkill_Comerciar, true);
}

void IniciarComercioNPC(int UserIndex) {
	/* '************************************************* */
	/* 'Author: Nacho (Integer) */
	/* 'Last modified: 2/8/06 */
	/* '************************************************* */
	EnviarNpcInv(UserIndex, UserList[UserIndex].flags.TargetNPC);
	UserList[UserIndex].flags.Comerciando = true;
	WriteCommerceInit(UserIndex);
}

int SlotEnNPCInv(int NpcIndex, int Objeto, int Cantidad) {
	int retval;
	/* '************************************************* */
	/* 'Author: Nacho (Integer) */
	/* 'Last modified: 2/8/06 */
	/* '************************************************* */
	retval = 1;
	while (!(Npclist[NpcIndex].Invent.Object[retval].ObjIndex == Objeto
			&& Npclist[NpcIndex].Invent.Object[retval].Amount + Cantidad <= MAX_INVENTORY_OBJS)) {

		retval = retval + 1;
		if (retval > MAX_INVENTORY_SLOTS) {
			break;
		}

	}

	if (retval > MAX_INVENTORY_SLOTS) {

		retval = 1;

		while (!(Npclist[NpcIndex].Invent.Object[retval].ObjIndex == 0)) {

			retval = retval + 1;
			if (retval > MAX_INVENTORY_SLOTS) {
				break;
			}

		}

		if (retval <= MAX_INVENTORY_SLOTS) {
			Npclist[NpcIndex].Invent.NroItems = Npclist[NpcIndex].Invent.NroItems + 1;
		}

	}

	return retval;
}

float Descuento(int UserIndex) {
	float retval;
	/* '************************************************* */
	/* 'Author: Nacho (Integer) */
	/* 'Last modified: 2/8/06 */
	/* '************************************************* */
	retval = 1 + UserList[UserIndex].Stats.UserSkills[eSkill_Comerciar] / 100;
	return retval;
}

/* '' */
/* ' Send the inventory of the Npc to the user */
/* ' */
/* ' @param userIndex The index of the User */
/* ' @param npcIndex The index of the NPC */

void EnviarNpcInv(int UserIndex, int NpcIndex) {
	/* '************************************************* */
	/* 'Author: Nacho (Integer) */
	/* 'Last Modified: 06/14/08 */
	/* 'Last Modified By: Nicolás Ezequiel Bouhid (NicoNZ) */
	/* '************************************************* */
	int Slot;
	float val;

	for (Slot = (1); Slot <= (MAX_NORMAL_INVENTORY_SLOTS); Slot++) {
		if (Npclist[NpcIndex].Invent.Object[Slot].ObjIndex > 0) {
			struct Obj thisObj;

			thisObj.ObjIndex = Npclist[NpcIndex].Invent.Object[Slot].ObjIndex;
			thisObj.Amount = Npclist[NpcIndex].Invent.Object[Slot].Amount;

			val = (ObjData[thisObj.ObjIndex].Valor) / Descuento(UserIndex);

			WriteChangeNPCInventorySlot(UserIndex, Slot, thisObj, val);
		} else {
			struct Obj DummyObj;
			WriteChangeNPCInventorySlot(UserIndex, Slot, DummyObj, 0);
		}
	}
}

/* '' */
/* ' Devuelve el valor de venta del objeto */
/* ' */
/* ' @param ObjIndex  El número de objeto al cual le calculamos el precio de venta */

float SalePrice(int ObjIndex) {
	float retval = 0.0f;
	/* '************************************************* */
	/* 'Author: Nicolás (NicoNZ) */
	/* ' */
	/* '************************************************* */
	if (ObjIndex < 1 || ObjIndex > vb6::UBound(ObjData)) {
		return retval;
	}
	if (ItemNewbie(ObjIndex)) {
		return retval;
	}

	retval = ObjData[ObjIndex].Valor / REDUCTOR_PRECIOVENTA;
	return retval;
}
