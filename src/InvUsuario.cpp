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

#include "InvUsuario.h"

bool TieneObjetosRobables(int UserIndex) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' 22/05/2010: Los items newbies ya no son robables. */
	/* '*************************************************** */

	/* '17/09/02 */
	/* 'Agregue que la función se asegure que el objeto no es un barco */

	int i;
	int ObjIndex;

	for (i = (1); i <= (UserList[UserIndex].CurrentInventorySlots); i++) {
		ObjIndex = UserList[UserIndex].Invent.Object[i].ObjIndex;
		if (ObjIndex > 0) {
			if ((ObjData[ObjIndex].OBJType != eOBJType_otLlaves
					&& ObjData[ObjIndex].OBJType != eOBJType_otBarcos && !ItemNewbie(ObjIndex))) {
				retval = true;
				return retval;
			}
		}
	}

	return retval;

}

bool ClasePuedeUsarItem(int UserIndex, int ObjIndex, std::string& sMotivo) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 14/01/2010 (ZaMa) */
	/* '14/01/2010: ZaMa - Agrego el motivo por el que no puede equipar/usar el item. */
	/* '*************************************************** */

	/* FIXME: ON ERROR GOTO manejador */

	/* 'Admins can use ANYTHING! */
	if (UserTienePrivilegio(UserIndex, PlayerType_User)) {
		if (ObjData[ObjIndex].ClaseProhibida[1] != 0) {
			int i;
			for (i = (1); i <= (NUMCLASES); i++) {
				if (ObjData[ObjIndex].ClaseProhibida[i] == UserList[UserIndex].clase) {
					retval = false;
					sMotivo = "Tu clase no puede usar este objeto.";
					return retval;
				}
			}
		}
	}

	retval = true;

	return retval;

}

void QuitarNewbieObj(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int j;

	for (j = (1); j <= (UserList[UserIndex].CurrentInventorySlots); j++) {
		if (UserList[UserIndex].Invent.Object[j].ObjIndex > 0) {

			if (ObjData[UserList[UserIndex].Invent.Object[j].ObjIndex].Newbie == 1) {
				QuitarUserInvItem(UserIndex, j, MAX_INVENTORY_OBJS);
			}
			UpdateUserInv(false, UserIndex, j);

		}
	}

	/* '[Barrin 17-12-03] Si el usuario dejó de ser Newbie, y estaba en el Newbie Dungeon */
	/* 'es transportado a su hogar de origen ;) */
	if (MapInfo[UserList[UserIndex].Pos.Map].Restringir == eRestrict_restrict_newbie) {

		struct WorldPos DeDonde;

		switch (UserList[UserIndex].Hogar) {
		/* 'Vamos a tener que ir por todo el desierto... uff! */
		case eCiudad_cLindos:
			DeDonde = Lindos;
			break;

		case eCiudad_cUllathorpe:
			DeDonde = Ullathorpe;
			break;

		case eCiudad_cBanderbill:
			DeDonde = Banderbill;
			break;

		default:
			DeDonde = Nix;
			break;
		}

		WarpUserChar(UserIndex, DeDonde.Map, DeDonde.X, DeDonde.Y, true);

	}
	/* '[/Barrin] */

}

void LimpiarInventario(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int j;

	for (j = (1); j <= (UserList[UserIndex].CurrentInventorySlots); j++) {
		UserList[UserIndex].Invent.Object[j].ObjIndex = 0;
		UserList[UserIndex].Invent.Object[j].Amount = 0;
		UserList[UserIndex].Invent.Object[j].Equipped = 0;
	}

	UserList[UserIndex].Invent.NroItems = 0;

	UserList[UserIndex].Invent.ArmourEqpObjIndex = 0;
	UserList[UserIndex].Invent.ArmourEqpSlot = 0;

	UserList[UserIndex].Invent.WeaponEqpObjIndex = 0;
	UserList[UserIndex].Invent.WeaponEqpSlot = 0;

	UserList[UserIndex].Invent.CascoEqpObjIndex = 0;
	UserList[UserIndex].Invent.CascoEqpSlot = 0;

	UserList[UserIndex].Invent.EscudoEqpObjIndex = 0;
	UserList[UserIndex].Invent.EscudoEqpSlot = 0;

	UserList[UserIndex].Invent.AnilloEqpObjIndex = 0;
	UserList[UserIndex].Invent.AnilloEqpSlot = 0;

	UserList[UserIndex].Invent.MunicionEqpObjIndex = 0;
	UserList[UserIndex].Invent.MunicionEqpSlot = 0;

	UserList[UserIndex].Invent.BarcoObjIndex = 0;
	UserList[UserIndex].Invent.BarcoSlot = 0;

	UserList[UserIndex].Invent.MochilaEqpObjIndex = 0;
	UserList[UserIndex].Invent.MochilaEqpSlot = 0;

}

void TirarOro(int Cantidad, int UserIndex) {
	/* '*************************************************** */
	/* 'Autor: Unknown (orginal version) */
	/* 'Last Modification: 23/01/2007 */
	/* '23/01/2007 -> Pablo (ToxicWaste): Billetera invertida y explotar oro en el agua. */
	/* '*************************************************** */

	/* 'If Cantidad > 100000 Then Exit Sub */

	/* 'SI EL Pjta TIENE ORO LO TIRAMOS */
	if ((Cantidad > 0) && (Cantidad <= UserList[UserIndex].Stats.GLD)) {
		struct Obj MiObj;
		/* 'info debug */
		int loops = 0;

		/* 'Seguridad Alkon (guardo el oro tirado si supera los 50k) */
		if (Cantidad >= MIN_GOLD_AMOUNT_LOG) {
			int j;
			int k;
			int M;
			std::string Cercanos;
			M = UserList[UserIndex].Pos.Map;
			for (j = (UserList[UserIndex].Pos.X - 10); j <= (UserList[UserIndex].Pos.X + 10); j++) {
				for (k = (UserList[UserIndex].Pos.Y - 10); k <= (UserList[UserIndex].Pos.Y + 10); k++) {
					if (InMapBounds(M, j, k)) {
						if (MapData[M][j][k].UserIndex > 0) {
							Cercanos = Cercanos + UserList[MapData[M][j][k].UserIndex].Name + ",";
						}
					}
				}
			}

			Cercanos = vb6::Left(Cercanos, vb6::Len(Cercanos) - 1);
			LogDesarrollo(
					UserList[UserIndex].Name + " tiró " + vb6::CStr(Cantidad) + " monedas de oro en "
							+ vb6::CStr(UserList[UserIndex].Pos.Map) + ", "
							+ vb6::CStr(UserList[UserIndex].Pos.X) + ", "
							+ vb6::CStr(UserList[UserIndex].Pos.Y) + ". Cercanos: " + Cercanos);
		}
		/* '/Seguridad */
		int Extra = 0;
		int TeniaOro;
		TeniaOro = UserList[UserIndex].Stats.GLD;
		/* 'Para evitar explotar demasiado */
		if (Cantidad > 500000) {
			Extra = Cantidad - 500000;
			Cantidad = 500000;
		}

		while ((Cantidad > 0)) {

			if (Cantidad > MAX_INVENTORY_OBJS && UserList[UserIndex].Stats.GLD > MAX_INVENTORY_OBJS) {
				MiObj.Amount = MAX_INVENTORY_OBJS;
				Cantidad = Cantidad - MiObj.Amount;
			} else {
				MiObj.Amount = Cantidad;
				Cantidad = Cantidad - MiObj.Amount;
			}

			MiObj.ObjIndex = iORO;

			if (EsGm(UserIndex)) {
				LogGM(UserList[UserIndex].Name,
						"Tiró cantidad:" + vb6::CStr(MiObj.Amount) + " Objeto:"
								+ ObjData[MiObj.ObjIndex].Name);
			}
			struct WorldPos AuxPos;

			if (UserList[UserIndex].clase == eClass_Pirat
					&& UserList[UserIndex].Invent.BarcoObjIndex == 476) {
				AuxPos = TirarItemAlPiso(UserList[UserIndex].Pos, MiObj, false);
				if (AuxPos.X != 0 && AuxPos.Y != 0) {
					UserList[UserIndex].Stats.GLD = UserList[UserIndex].Stats.GLD - MiObj.Amount;
				}
			} else {
				AuxPos = TirarItemAlPiso(UserList[UserIndex].Pos, MiObj, true);
				if (AuxPos.X != 0 && AuxPos.Y != 0) {
					UserList[UserIndex].Stats.GLD = UserList[UserIndex].Stats.GLD - MiObj.Amount;
				}
			}

			/* 'info debug */
			loops = loops + 1;
			if (loops > 100) {
				LogError("Error en tiraroro");
				return;
			}

		}
		if (TeniaOro == UserList[UserIndex].Stats.GLD) {
			Extra = 0;
		}
		if (Extra > 0) {
			UserList[UserIndex].Stats.GLD = UserList[UserIndex].Stats.GLD - Extra;
		}

	}
}

void QuitarUserInvItem(int UserIndex, int Slot, int Cantidad) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (Slot < 1 || Slot > UserList[UserIndex].CurrentInventorySlots) {
		return;
	}

	if (UserList[UserIndex].Invent.Object[Slot].Amount <= Cantidad
			&& UserList[UserIndex].Invent.Object[Slot].Equipped == 1) {
		Desequipar(UserIndex, Slot, true);
	}

	/* 'Quita un objeto */
	UserList[UserIndex].Invent.Object[Slot].Amount = UserList[UserIndex].Invent.Object[Slot].Amount
			- Cantidad;
	/* '¿Quedan mas? */
	if (UserList[UserIndex].Invent.Object[Slot].Amount <= 0) {
		UserList[UserIndex].Invent.NroItems = UserList[UserIndex].Invent.NroItems - 1;
		UserList[UserIndex].Invent.Object[Slot].ObjIndex = 0;
		UserList[UserIndex].Invent.Object[Slot].Amount = 0;
	}
}

void UpdateUserInv(bool UpdateAll, int UserIndex, int Slot) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	struct UserOBJ NullObj;
	int LoopC;

	/* 'Actualiza un solo slot */
	if (!UpdateAll) {

		/* 'Actualiza el inventario */
		if (UserList[UserIndex].Invent.Object[Slot].ObjIndex > 0) {
			ChangeUserInv(UserIndex, Slot, UserList[UserIndex].Invent.Object[Slot]);
		} else {
			ChangeUserInv(UserIndex, Slot, NullObj);
		}

	} else {

		/* 'Actualiza todos los slots */
		for (LoopC = (1); LoopC <= (UserList[UserIndex].CurrentInventorySlots); LoopC++) {
			/* 'Actualiza el inventario */
			if (UserList[UserIndex].Invent.Object[LoopC].ObjIndex > 0) {
				ChangeUserInv(UserIndex, LoopC, UserList[UserIndex].Invent.Object[LoopC]);
			} else {
				ChangeUserInv(UserIndex, LoopC, NullObj);
			}
		}
	}
}

void DropObj(int UserIndex, int Slot, int num, int Map, int X, int Y, bool isDrop) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 11/5/2010 */
	/* '11/5/2010 - ZaMa: Arreglo bug que permitia apilar mas de 10k de items. */
	/* '*************************************************** */

	struct Obj DropObj;
	struct Obj MapObj;
	std::string str;

	if (num > 0) {

		DropObj.ObjIndex = UserList[UserIndex].Invent.Object[Slot].ObjIndex;

		if ((ItemNewbie(DropObj.ObjIndex) && (UserTienePrivilegio(UserIndex, PlayerType_User)))) {
			WriteConsoleMsg(UserIndex, "No puedes tirar objetos newbie.", FontTypeNames_FONTTYPE_INFO);
			return;
		}

		/* ' Users can't drop non-transferible items */
		if (ObjData[DropObj.ObjIndex].Intransferible == 1 || ObjData[DropObj.ObjIndex].NoSeTira == 1) {
			if (UserTienePrivilegio(UserIndex, PlayerType_User)) {
				WriteConsoleMsg(UserIndex, "¡¡¡No puedes tirar este tipo de objeto!!!",
						FontTypeNames_FONTTYPE_FIGHT);
				return;
			}
		}

		DropObj.Amount = MinimoInt(num, UserList[UserIndex].Invent.Object[Slot].Amount);

		/* 'Check objeto en el suelo */
		MapObj.ObjIndex = MapData[UserList[UserIndex].Pos.Map][X][Y].ObjInfo.ObjIndex;
		MapObj.Amount = MapData[UserList[UserIndex].Pos.Map][X][Y].ObjInfo.Amount;

		if (MapObj.ObjIndex == 0 || MapObj.ObjIndex == DropObj.ObjIndex) {

			if (MapObj.Amount == MAX_INVENTORY_OBJS) {
				WriteConsoleMsg(UserIndex, "No hay espacio en el piso.", FontTypeNames_FONTTYPE_INFO);
				return;
			}

			if (DropObj.Amount + MapObj.Amount > MAX_INVENTORY_OBJS) {
				DropObj.Amount = MAX_INVENTORY_OBJS - MapObj.Amount;
			}

			MakeObj(DropObj, Map, X, Y);
			QuitarUserInvItem(UserIndex, Slot, DropObj.Amount);
			UpdateUserInv(false, UserIndex, Slot);

			if (ObjData[DropObj.ObjIndex].OBJType == eOBJType_otBarcos) {
				WriteConsoleMsg(UserIndex, "¡¡ATENCIÓN!! ¡ACABAS DE TIRAR TU BARCA!",
						FontTypeNames_FONTTYPE_TALK);
			}

			if (!UserTienePrivilegio(UserIndex, PlayerType_User)) {
				LogGM(UserList[UserIndex].Name,
						"Tiró cantidad:" + vb6::CStr(num) + " Objeto:" + ObjData[DropObj.ObjIndex].Name);
			}

			/* 'Log de Objetos que se tiran al piso. Pablo (ToxicWaste) 07/09/07 */
			/* 'Es un Objeto que tenemos que loguear? */
			if (((ObjData[DropObj.ObjIndex].Log == 1)
					|| (ObjData[DropObj.ObjIndex].OBJType == eOBJType_otLlaves))) {
				LogDesarrollo(
						UserList[UserIndex].Name + " tiró al piso " + vb6::IIf(isDrop, "", "al morir ")
								+ vb6::CStr(DropObj.Amount) + " " + ObjData[DropObj.ObjIndex].Name + " Mapa: "
								+ vb6::CStr(Map) + " X: " + vb6::CStr(X) + " Y: " + vb6::CStr(Y));
				/* 'Es mucha cantidad? > Subí a 5000 el minimo porque si no se llenaba el log de cosas al pedo. (NicoNZ) */
			} else if (DropObj.Amount >= MIN_AMOUNT_LOG) {
				/* 'Si no es de los prohibidos de loguear, lo logueamos. */
				if (ObjData[DropObj.ObjIndex].NoLog != 1) {
					LogDesarrollo(
							UserList[UserIndex].Name + " tiró al piso " + vb6::IIf(isDrop, "", "al morir ")
									+ vb6::CStr(DropObj.Amount) + " " + ObjData[DropObj.ObjIndex].Name
									+ " Mapa: " + vb6::CStr(Map) + " X: " + vb6::CStr(X) + " Y: "
									+ vb6::CStr(Y));
				}
			} else if ((DropObj.Amount * ObjData[DropObj.ObjIndex].Valor) >= MIN_VALUE_LOG) {
				/* 'Si no es de los prohibidos de loguear, lo logueamos. */
				if (ObjData[DropObj.ObjIndex].NoLog != 1) {
					LogDesarrollo(
							UserList[UserIndex].Name + " tiró al piso " + vb6::IIf(isDrop, "", "al morir ")
									+ vb6::CStr(DropObj.Amount) + " " + ObjData[DropObj.ObjIndex].Name
									+ " Mapa: " + vb6::CStr(Map) + " X: " + vb6::CStr(X) + " Y: "
									+ vb6::CStr(Y));
				}
			}
		} else {
			WriteConsoleMsg(UserIndex, "No hay espacio en el piso.", FontTypeNames_FONTTYPE_INFO);
		}
	}
}

void EraseObj(int num, int Map, int X, int Y) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	MapData[Map][X][Y].ObjInfo.Amount = MapData[Map][X][Y].ObjInfo.Amount - num;

	if (MapData[Map][X][Y].ObjInfo.Amount <= 0) {
		MapData[Map][X][Y].ObjInfo.ObjIndex = 0;
		MapData[Map][X][Y].ObjInfo.Amount = 0;

		SendToAreaByPos(Map, X, Y, PacketToString(dakara::protocol::server::BuildObjectDelete(X, Y)));
	}

}

void MakeObj(struct Obj & Obj, int Map, int X, int Y) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (Obj.ObjIndex > 0 && Obj.ObjIndex <= vb6::UBound(ObjData)) {

		if (MapData[Map][X][Y].ObjInfo.ObjIndex == Obj.ObjIndex) {
			MapData[Map][X][Y].ObjInfo.Amount = MapData[Map][X][Y].ObjInfo.Amount + Obj.Amount;
		} else {
			MapData[Map][X][Y].ObjInfo = Obj;

			SendToAreaByPos(Map, X, Y, PacketToString(dakara::protocol::server::BuildObjectCreate(X, Y,ObjData[Obj.ObjIndex].GrhIndex)));
		}
	}

}

bool MeterItemEnInventario(int UserIndex, struct Obj & MiObj) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int Slot;

	/* '¿el user ya tiene un objeto del mismo tipo? */
	Slot = 1;

	while (!(UserList[UserIndex].Invent.Object[Slot].ObjIndex == MiObj.ObjIndex
			&& UserList[UserIndex].Invent.Object[Slot].Amount + MiObj.Amount <= MAX_INVENTORY_OBJS)) {
		Slot = Slot + 1;
		if (Slot > UserList[UserIndex].CurrentInventorySlots) {
			break;
		}
	}

	/* 'Sino busca un slot vacio */
	if (Slot > UserList[UserIndex].CurrentInventorySlots) {
		Slot = 1;
		while (!(UserList[UserIndex].Invent.Object[Slot].ObjIndex == 0)) {
			Slot = Slot + 1;
			if (Slot > UserList[UserIndex].CurrentInventorySlots) {
				WriteConsoleMsg(UserIndex, "No puedes cargar más objetos.", FontTypeNames_FONTTYPE_FIGHT);
				retval = false;
				return retval;
			}
		}
		UserList[UserIndex].Invent.NroItems = UserList[UserIndex].Invent.NroItems + 1;
	}

	if (Slot > MAX_NORMAL_INVENTORY_SLOTS && Slot <= MAX_INVENTORY_SLOTS) {
		if (!ItemSeCae(MiObj.ObjIndex)) {
			WriteConsoleMsg(UserIndex,
					"No puedes contener objetos especiales en tu "
							+ ObjData[UserList[UserIndex].Invent.MochilaEqpObjIndex].Name + ".",
					FontTypeNames_FONTTYPE_FIGHT);
			retval = false;
			return retval;
		}
	}
	/* 'Mete el objeto */
	if (UserList[UserIndex].Invent.Object[Slot].Amount + MiObj.Amount <= MAX_INVENTORY_OBJS) {
		/* 'Menor que MAX_INV_OBJS */
		UserList[UserIndex].Invent.Object[Slot].ObjIndex = MiObj.ObjIndex;
		UserList[UserIndex].Invent.Object[Slot].Amount = UserList[UserIndex].Invent.Object[Slot].Amount
				+ MiObj.Amount;
	} else {
		UserList[UserIndex].Invent.Object[Slot].Amount = MAX_INVENTORY_OBJS;
	}

	retval = true;

	UpdateUserInv(false, UserIndex, Slot);

	return retval;

}

void GetObj(int UserIndex) {
	/* '*************************************************** */
	/* 'Autor: Unknown (orginal version) */
	/* 'Last Modification: 18/12/2009 */
	/* '18/12/2009: ZaMa - Oro directo a la billetera. */
	/* '*************************************************** */

	struct ObjData Obj;
	struct Obj MiObj;
	std::string ObjPos;

	/* '¿Hay algun obj? */
	if (MapData[UserList[UserIndex].Pos.Map][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].ObjInfo.ObjIndex
			> 0) {
		/* '¿Esta permitido agarrar este obj? */
		if (ObjData[MapData[UserList[UserIndex].Pos.Map][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].ObjInfo.ObjIndex].Agarrable
				!= 1) {
			int X;
			int Y;

			X = UserList[UserIndex].Pos.X;
			Y = UserList[UserIndex].Pos.Y;

			Obj =
					ObjData[MapData[UserList[UserIndex].Pos.Map][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].ObjInfo.ObjIndex];
			MiObj.Amount = MapData[UserList[UserIndex].Pos.Map][X][Y].ObjInfo.Amount;
			MiObj.ObjIndex = MapData[UserList[UserIndex].Pos.Map][X][Y].ObjInfo.ObjIndex;

			/* ' Oro directo a la billetera! */
			if (Obj.OBJType == eOBJType_otGuita) {
				UserList[UserIndex].Stats.GLD = UserList[UserIndex].Stats.GLD + MiObj.Amount;
				/* 'Quitamos el objeto */
				EraseObj(MapData[UserList[UserIndex].Pos.Map][X][Y].ObjInfo.Amount,
						UserList[UserIndex].Pos.Map, UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y);

				WriteUpdateGold(UserIndex);

				if (MiObj.Amount >= MIN_GOLD_AMOUNT_LOG) {
					ObjPos = " Mapa: " + vb6::CStr(UserList[UserIndex].Pos.Map) + " X: "
							+ vb6::CStr(UserList[UserIndex].Pos.X) + " Y: "
							+ vb6::CStr(UserList[UserIndex].Pos.Y);
					LogDesarrollo(
							vb6::CStr(UserList[UserIndex].Name) + " juntó del piso " + vb6::CStr(MiObj.Amount)
									+ " monedas de oro" + ObjData[MiObj.ObjIndex].Name + ObjPos);
				}
			} else {
				if (MeterItemEnInventario(UserIndex, MiObj)) {

					/* 'Quitamos el objeto */
					EraseObj(MapData[UserList[UserIndex].Pos.Map][X][Y].ObjInfo.Amount,
							UserList[UserIndex].Pos.Map, UserList[UserIndex].Pos.X,
							UserList[UserIndex].Pos.Y);
					/* 'Si no es un usuario común logueamos */
					if (!UserTienePrivilegio(UserIndex, PlayerType_User)) {
						LogGM(UserList[UserIndex].Name,
								"Agarro:" + vb6::CStr(MiObj.Amount) + " Objeto:"
										+ ObjData[MiObj.ObjIndex].Name);
					}

					/* 'Log de Objetos que se agarran del piso. Pablo (ToxicWaste) 07/09/07 */
					/* 'Es un Objeto que tenemos que loguear? */
					if (((ObjData[MiObj.ObjIndex].Log == 1)
							|| (ObjData[MiObj.ObjIndex].OBJType == eOBJType_otLlaves))) {
						ObjPos = " Mapa: " + vb6::CStr(UserList[UserIndex].Pos.Map) + " X: "
								+ vb6::CStr(UserList[UserIndex].Pos.X) + " Y: "
								+ vb6::CStr(UserList[UserIndex].Pos.Y);
						LogDesarrollo(
								UserList[UserIndex].Name + " juntó del piso " + vb6::CStr(MiObj.Amount) + " "
										+ ObjData[MiObj.ObjIndex].Name + ObjPos);
						/* 'Es mucha cantidad? */
					} else if (MiObj.Amount >= MIN_AMOUNT_LOG) {
						/* 'Si no es de los prohibidos de loguear, lo logueamos. */
						if (ObjData[MiObj.ObjIndex].NoLog != 1) {
							ObjPos = " Mapa: " + vb6::CStr(UserList[UserIndex].Pos.Map) + " X: "
									+ vb6::CStr(UserList[UserIndex].Pos.X) + " Y: "
									+ vb6::CStr(UserList[UserIndex].Pos.Y);
							LogDesarrollo(
									UserList[UserIndex].Name + " juntó del piso " + vb6::CStr(MiObj.Amount)
											+ " " + ObjData[MiObj.ObjIndex].Name + ObjPos);
						}
					} else if ((MiObj.Amount * ObjData[MiObj.ObjIndex].Valor) >= MIN_VALUE_LOG) {
						/* 'Si no es de los prohibidos de loguear, lo logueamos. */
						if (ObjData[MiObj.ObjIndex].NoLog != 1) {
							ObjPos = " Mapa: " + vb6::CStr(UserList[UserIndex].Pos.Map) + " X: "
									+ vb6::CStr(UserList[UserIndex].Pos.X) + " Y: "
									+ vb6::CStr(UserList[UserIndex].Pos.Y);
							LogDesarrollo(
									UserList[UserIndex].Name + " juntó del piso " + vb6::CStr(MiObj.Amount)
											+ " " + ObjData[MiObj.ObjIndex].Name + ObjPos);
						}
					}
				}
			}
		}
	} else {
		WriteConsoleMsg(UserIndex, "No hay nada aquí.", FontTypeNames_FONTTYPE_INFO);
	}

}

void Desequipar(int UserIndex, int Slot, bool RefreshChar) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	/* 'Desequipa el item slot del inventario */
	struct ObjData Obj;

	if ((Slot < vb6::LBound(UserList[UserIndex].Invent.Object))
			|| (Slot > vb6::UBound(UserList[UserIndex].Invent.Object))) {
		return;
	} else if (UserList[UserIndex].Invent.Object[Slot].ObjIndex == 0) {
		return;
	}

	Obj = ObjData[UserList[UserIndex].Invent.Object[Slot].ObjIndex];

	switch (Obj.OBJType) {
	case eOBJType_otWeapon:
		UserList[UserIndex].Invent.Object[Slot].Equipped = 0;
		UserList[UserIndex].Invent.WeaponEqpObjIndex = 0;
		UserList[UserIndex].Invent.WeaponEqpSlot = 0;

		if (UserList[UserIndex].flags.Mimetizado != 1) {
			UserList[UserIndex].Char.WeaponAnim = NingunArma;

			if (RefreshChar && UserList[UserIndex].flags.Navegando != 1) {
				ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
						UserList[UserIndex].Char.heading, UserList[UserIndex].Char.WeaponAnim,
						UserList[UserIndex].Char.ShieldAnim, UserList[UserIndex].Char.CascoAnim);
			}
		}

		break;

	case eOBJType_otFlechas:
		UserList[UserIndex].Invent.Object[Slot].Equipped = 0;
		UserList[UserIndex].Invent.MunicionEqpObjIndex = 0;
		UserList[UserIndex].Invent.MunicionEqpSlot = 0;

		break;

	case eOBJType_otAnillo:
		UserList[UserIndex].Invent.Object[Slot].Equipped = 0;
		UserList[UserIndex].Invent.AnilloEqpObjIndex = 0;
		UserList[UserIndex].Invent.AnilloEqpSlot = 0;

		break;

	case eOBJType_otArmadura:
		UserList[UserIndex].Invent.Object[Slot].Equipped = 0;
		UserList[UserIndex].Invent.ArmourEqpObjIndex = 0;
		UserList[UserIndex].Invent.ArmourEqpSlot = 0;

		if (UserList[UserIndex].flags.Navegando != 1) {
			DarCuerpoDesnudo(UserIndex, UserList[UserIndex].flags.Mimetizado == 1);
		}
		/* '[TEMPORAL] */
		UserList[UserIndex].flags.Desnudo = 1;

		if (RefreshChar) {
			ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
					UserList[UserIndex].Char.heading, UserList[UserIndex].Char.WeaponAnim,
					UserList[UserIndex].Char.ShieldAnim, UserList[UserIndex].Char.CascoAnim);
		}

		break;

	case eOBJType_otCASCO:
		UserList[UserIndex].Invent.Object[Slot].Equipped = 0;
		UserList[UserIndex].Invent.CascoEqpObjIndex = 0;
		UserList[UserIndex].Invent.CascoEqpSlot = 0;

		if (UserList[UserIndex].flags.Mimetizado != 1) {
			UserList[UserIndex].Char.CascoAnim = NingunCasco;

			if (RefreshChar) {
				ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
						UserList[UserIndex].Char.heading, UserList[UserIndex].Char.WeaponAnim,
						UserList[UserIndex].Char.ShieldAnim, UserList[UserIndex].Char.CascoAnim);
			}
		}

		break;

	case eOBJType_otESCUDO:
		UserList[UserIndex].Invent.Object[Slot].Equipped = 0;
		UserList[UserIndex].Invent.EscudoEqpObjIndex = 0;
		UserList[UserIndex].Invent.EscudoEqpSlot = 0;

		if (UserList[UserIndex].flags.Mimetizado != 1) {
			UserList[UserIndex].Char.ShieldAnim = NingunEscudo;

			if (RefreshChar) {
				ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
						UserList[UserIndex].Char.heading, UserList[UserIndex].Char.WeaponAnim,
						UserList[UserIndex].Char.ShieldAnim, UserList[UserIndex].Char.CascoAnim);
			}
		}

		break;

	case eOBJType_otMochilas:
		UserList[UserIndex].Invent.Object[Slot].Equipped = 0;
		UserList[UserIndex].Invent.MochilaEqpObjIndex = 0;
		UserList[UserIndex].Invent.MochilaEqpSlot = 0;

		TirarTodosLosItemsEnMochila(UserIndex);
		UserList[UserIndex].CurrentInventorySlots = MAX_NORMAL_INVENTORY_SLOTS;
		break;

	default:
		break;
	}

	if (RefreshChar) {
		WriteUpdateUserStats(UserIndex);
	}

	UpdateUserInv(false, UserIndex, Slot);

}

bool SexoPuedeUsarItem(int UserIndex, int ObjIndex, std::string& sMotivo) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 14/01/2010 (ZaMa) */
	/* '14/01/2010: ZaMa - Agrego el motivo por el que no puede equipar/usar el item. */
	/* '*************************************************** */

	if (ObjData[ObjIndex].Mujer == 1) {
		retval = UserList[UserIndex].Genero != eGenero_Hombre;
	} else if (ObjData[ObjIndex].Hombre == 1) {
		retval = UserList[UserIndex].Genero != eGenero_Mujer;
	} else {
		retval = true;
	}

	if (!retval) {
		sMotivo = "Tu género no puede usar este objeto.";
	}

	return retval;
}

bool FaccionPuedeUsarItem(int UserIndex, int ObjIndex, std::string& sMotivo) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 14/01/2010 (ZaMa) */
	/* '14/01/2010: ZaMa - Agrego el motivo por el que no puede equipar/usar el item. */
	/* '*************************************************** */

	if (ObjData[ObjIndex].Real == 1) {
		if (!criminal(UserIndex)) {
			retval = esArmada(UserIndex);
		} else {
			retval = false;
		}
	} else if (ObjData[ObjIndex].Caos == 1) {
		if (criminal(UserIndex)) {
			retval = esCaos(UserIndex);
		} else {
			retval = false;
		}
	} else {
		retval = true;
	}

	if (!retval) {
		sMotivo = "Tu alineación no puede usar este objeto.";
	}

	return retval;
}

void EquiparInvItem(int UserIndex, int Slot) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 14/01/2010 (ZaMa) */
	/* '01/08/2009: ZaMa - Now it's not sent any sound made by an invisible admin */
	/* '14/01/2010: ZaMa - Agrego el motivo especifico por el que no puede equipar/usar el item. */
	/* '************************************************* */

	/* 'Equipa un item del inventario */
	struct ObjData Obj;
	int ObjIndex;
	std::string sMotivo;

	ObjIndex = UserList[UserIndex].Invent.Object[Slot].ObjIndex;
	Obj = ObjData[ObjIndex];

	if (Obj.Newbie == 1 && !EsNewbie(UserIndex)) {
		WriteConsoleMsg(UserIndex, "Sólo los newbies pueden usar este objeto.", FontTypeNames_FONTTYPE_INFO);
		return;
	}

	switch (Obj.OBJType) {
	case eOBJType_otWeapon:
		if (ClasePuedeUsarItem(UserIndex, ObjIndex, sMotivo)
				&& FaccionPuedeUsarItem(UserIndex, ObjIndex, sMotivo)) {
			/* 'Si esta equipado lo quita */
			if (UserList[UserIndex].Invent.Object[Slot].Equipped) {
				/* 'Quitamos del inv el item */
				Desequipar(UserIndex, Slot, false);
				/* 'Animacion por defecto */
				if (UserList[UserIndex].flags.Mimetizado == 1) {
					UserList[UserIndex].CharMimetizado.WeaponAnim = NingunArma;
				} else {
					UserList[UserIndex].Char.WeaponAnim = NingunArma;
					ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
							UserList[UserIndex].Char.heading, UserList[UserIndex].Char.WeaponAnim,
							UserList[UserIndex].Char.ShieldAnim, UserList[UserIndex].Char.CascoAnim);
				}
				return;
			}

			/* 'Quitamos el elemento anterior */
			if (UserList[UserIndex].Invent.WeaponEqpObjIndex > 0) {
				Desequipar(UserIndex, UserList[UserIndex].Invent.WeaponEqpSlot, false);
			}

			UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
			UserList[UserIndex].Invent.WeaponEqpObjIndex = ObjIndex;
			UserList[UserIndex].Invent.WeaponEqpSlot = Slot;

			/* 'El sonido solo se envia si no lo produce un admin invisible */
			if (!(UserList[UserIndex].flags.AdminInvisible == 1)) {
				SendData(SendTarget_ToPCArea, UserIndex,
						dakara::protocol::server::BuildPlayWave(SND_SACARARMA, UserList[UserIndex].Pos.X,
								UserList[UserIndex].Pos.Y));
			}

			if (UserList[UserIndex].flags.Mimetizado == 1) {
				UserList[UserIndex].CharMimetizado.WeaponAnim = GetWeaponAnim(UserIndex, ObjIndex);
			} else {
				UserList[UserIndex].Char.WeaponAnim = GetWeaponAnim(UserIndex, ObjIndex);
				ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
						UserList[UserIndex].Char.heading, UserList[UserIndex].Char.WeaponAnim,
						UserList[UserIndex].Char.ShieldAnim, UserList[UserIndex].Char.CascoAnim);
			}
		} else {
			WriteConsoleMsg(UserIndex, sMotivo, FontTypeNames_FONTTYPE_INFO);
		}

		break;

	case eOBJType_otAnillo:
		if (ClasePuedeUsarItem(UserIndex, ObjIndex, sMotivo)
				&& FaccionPuedeUsarItem(UserIndex, ObjIndex, sMotivo)) {
			/* 'Si esta equipado lo quita */
			if (UserList[UserIndex].Invent.Object[Slot].Equipped) {
				/* 'Quitamos del inv el item */
				Desequipar(UserIndex, Slot, true);
				return;
			}

			/* 'Quitamos el elemento anterior */
			if (UserList[UserIndex].Invent.AnilloEqpObjIndex > 0) {
				Desequipar(UserIndex, UserList[UserIndex].Invent.AnilloEqpSlot, true);
			}

			UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
			UserList[UserIndex].Invent.AnilloEqpObjIndex = ObjIndex;
			UserList[UserIndex].Invent.AnilloEqpSlot = Slot;

		} else {
			WriteConsoleMsg(UserIndex, sMotivo, FontTypeNames_FONTTYPE_INFO);
		}

		break;

	case eOBJType_otFlechas:
		if (ClasePuedeUsarItem(UserIndex, ObjIndex, sMotivo)
				&& FaccionPuedeUsarItem(UserIndex, ObjIndex, sMotivo)) {

			/* 'Si esta equipado lo quita */
			if (UserList[UserIndex].Invent.Object[Slot].Equipped) {
				/* 'Quitamos del inv el item */
				Desequipar(UserIndex, Slot, true);
				return;
			}

			/* 'Quitamos el elemento anterior */
			if (UserList[UserIndex].Invent.MunicionEqpObjIndex > 0) {
				Desequipar(UserIndex, UserList[UserIndex].Invent.MunicionEqpSlot, true);
			}

			UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
			UserList[UserIndex].Invent.MunicionEqpObjIndex = ObjIndex;
			UserList[UserIndex].Invent.MunicionEqpSlot = Slot;

		} else {
			WriteConsoleMsg(UserIndex, sMotivo, FontTypeNames_FONTTYPE_INFO);
		}

		break;

	case eOBJType_otArmadura:
		/* ' [TEMPORAL] If .flags.Navegando = 1 Then Exit Sub */

		/* 'Nos aseguramos que puede usarla */
		if (ClasePuedeUsarItem(UserIndex, ObjIndex, sMotivo)
				&& SexoPuedeUsarItem(UserIndex, ObjIndex, sMotivo)
				&& CheckRazaUsaRopa(UserIndex, ObjIndex, sMotivo)
				&& FaccionPuedeUsarItem(UserIndex, ObjIndex, sMotivo)) {

			/* 'Si esta equipado lo quita */
			if (UserList[UserIndex].Invent.Object[Slot].Equipped) {
				Desequipar(UserIndex, Slot, false);
				/* 'Call DarCuerpoDesnudo(UserIndex, .flags.Mimetizado = 1) */
				if (UserList[UserIndex].flags.Mimetizado == 0 && UserList[UserIndex].flags.Navegando == 0) {
					ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
							UserList[UserIndex].Char.heading, UserList[UserIndex].Char.WeaponAnim,
							UserList[UserIndex].Char.ShieldAnim, UserList[UserIndex].Char.CascoAnim);
				}

				WriteUpdateUserStats(UserIndex);

				return;
			}

			/* 'Quita el anterior */
			if (UserList[UserIndex].Invent.ArmourEqpObjIndex > 0) {
				Desequipar(UserIndex, UserList[UserIndex].Invent.ArmourEqpSlot, true);
			}

			/* 'Lo equipa */
			UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
			UserList[UserIndex].Invent.ArmourEqpObjIndex = ObjIndex;
			UserList[UserIndex].Invent.ArmourEqpSlot = Slot;

			if (UserList[UserIndex].flags.Mimetizado == 1) {
				UserList[UserIndex].CharMimetizado.body = Obj.Ropaje;
			} else {
				if (UserList[UserIndex].flags.Navegando == 0) {
					UserList[UserIndex].Char.body = Obj.Ropaje;
					ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
							UserList[UserIndex].Char.heading, UserList[UserIndex].Char.WeaponAnim,
							UserList[UserIndex].Char.ShieldAnim, UserList[UserIndex].Char.CascoAnim);
				}
			}
			UserList[UserIndex].flags.Desnudo = 0;
		} else {
			WriteConsoleMsg(UserIndex, sMotivo, FontTypeNames_FONTTYPE_INFO);
		}

		break;

	case eOBJType_otCASCO:
		/* ' [TEMPORAL] If .flags.Navegando = 1 Then Exit Sub */
		if (ClasePuedeUsarItem(UserIndex, ObjIndex, sMotivo)) {
			/* 'Si esta equipado lo quita */
			if (UserList[UserIndex].Invent.Object[Slot].Equipped) {
				Desequipar(UserIndex, Slot, false);
				if (UserList[UserIndex].flags.Mimetizado == 1) {
					UserList[UserIndex].CharMimetizado.CascoAnim = NingunCasco;

				} else if (UserList[UserIndex].flags.Navegando == 0) {
					UserList[UserIndex].Char.CascoAnim = NingunCasco;
					ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
							UserList[UserIndex].Char.heading, UserList[UserIndex].Char.WeaponAnim,
							UserList[UserIndex].Char.ShieldAnim, UserList[UserIndex].Char.CascoAnim);
				}
				return;
			}

			/* 'Quita el anterior */
			if (UserList[UserIndex].Invent.CascoEqpObjIndex > 0) {
				Desequipar(UserIndex, UserList[UserIndex].Invent.CascoEqpSlot, false);
			}

			/* 'Lo equipa */
			UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
			UserList[UserIndex].Invent.CascoEqpObjIndex = ObjIndex;
			UserList[UserIndex].Invent.CascoEqpSlot = Slot;
			if (UserList[UserIndex].flags.Mimetizado == 1) {
				UserList[UserIndex].CharMimetizado.CascoAnim = Obj.CascoAnim;
			} else if (UserList[UserIndex].flags.Navegando == 0) {
				UserList[UserIndex].Char.CascoAnim = Obj.CascoAnim;
				ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
						UserList[UserIndex].Char.heading, UserList[UserIndex].Char.WeaponAnim,
						UserList[UserIndex].Char.ShieldAnim, UserList[UserIndex].Char.CascoAnim);
			}

			WriteUpdateUserStats(UserIndex);
		} else {
			WriteConsoleMsg(UserIndex, sMotivo, FontTypeNames_FONTTYPE_INFO);
		}

		break;

	case eOBJType_otESCUDO:
		/* ' [TEMPORAL] If .flags.Navegando = 1 Then Exit Sub */

		if (ClasePuedeUsarItem(UserIndex, ObjIndex, sMotivo)
				&& FaccionPuedeUsarItem(UserIndex, ObjIndex, sMotivo)) {

			/* 'Si esta equipado lo quita */
			if (UserList[UserIndex].Invent.Object[Slot].Equipped) {
				Desequipar(UserIndex, Slot, false);
				if (UserList[UserIndex].flags.Mimetizado == 1) {
					UserList[UserIndex].CharMimetizado.ShieldAnim = NingunEscudo;

				} else if (UserList[UserIndex].flags.Navegando == 0) {
					UserList[UserIndex].Char.ShieldAnim = NingunEscudo;
					ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
							UserList[UserIndex].Char.heading, UserList[UserIndex].Char.WeaponAnim,
							UserList[UserIndex].Char.ShieldAnim, UserList[UserIndex].Char.CascoAnim);
				}

				WriteUpdateUserStats(UserIndex);

				return;
			}

			/* 'Quita el anterior */
			if (UserList[UserIndex].Invent.EscudoEqpObjIndex > 0) {
				Desequipar(UserIndex, UserList[UserIndex].Invent.EscudoEqpSlot, false);
			}

			/* 'Lo equipa */
			UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
			UserList[UserIndex].Invent.EscudoEqpObjIndex = ObjIndex;
			UserList[UserIndex].Invent.EscudoEqpSlot = Slot;

			if (UserList[UserIndex].flags.Mimetizado == 1) {
				UserList[UserIndex].CharMimetizado.ShieldAnim = Obj.ShieldAnim;
			} else {
				if (UserList[UserIndex].flags.Navegando == 0) {
					UserList[UserIndex].Char.ShieldAnim = Obj.ShieldAnim;

					ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
							UserList[UserIndex].Char.heading, UserList[UserIndex].Char.WeaponAnim,
							UserList[UserIndex].Char.ShieldAnim, UserList[UserIndex].Char.CascoAnim);
				}
				WriteUpdateUserStats(UserIndex);
			}
		} else {
			WriteConsoleMsg(UserIndex, sMotivo, FontTypeNames_FONTTYPE_INFO);
		}

		break;

	case eOBJType_otMochilas:
		if (UserList[UserIndex].flags.Muerto == 1) {
			WriteConsoleMsg(UserIndex, "¡¡Estas muerto!! Solo podes usar items cuando estas vivo. ",
					FontTypeNames_FONTTYPE_INFO);
			return;
		}
		if (UserList[UserIndex].Invent.Object[Slot].Equipped) {
			Desequipar(UserIndex, Slot, true);
			return;
		}
		if (UserList[UserIndex].Invent.MochilaEqpObjIndex > 0) {
			Desequipar(UserIndex, UserList[UserIndex].Invent.MochilaEqpSlot, true);
		}
		UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
		UserList[UserIndex].Invent.MochilaEqpObjIndex = ObjIndex;
		UserList[UserIndex].Invent.MochilaEqpSlot = Slot;
		UserList[UserIndex].CurrentInventorySlots = MAX_NORMAL_INVENTORY_SLOTS + Obj.MochilaType * 5;
		WriteAddSlots(UserIndex, static_cast<eMochilas>(Obj.MochilaType));
		break;

	default:
		break;
	}

	/* 'Actualiza */
	UpdateUserInv(false, UserIndex, Slot);

}

bool CheckRazaUsaRopa(int UserIndex, int ItemIndex, std::string& sMotivo) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 14/01/2010 (ZaMa) */
	/* '14/01/2010: ZaMa - Agrego el motivo por el que no puede equipar/usar el item. */
	/* '*************************************************** */

	/* 'Verifica si la raza puede usar la ropa */
	if (UserList[UserIndex].raza == eRaza_Humano || UserList[UserIndex].raza == eRaza_Elfo
			|| UserList[UserIndex].raza == eRaza_Drow) {
		retval = (ObjData[ItemIndex].RazaEnana == 0);
	} else {
		retval = (ObjData[ItemIndex].RazaEnana == 1);
	}

	/* 'Solo se habilita la ropa exclusiva para Drows por ahora. Pablo (ToxicWaste) */
	if ((UserList[UserIndex].raza != eRaza_Drow) && ObjData[ItemIndex].RazaDrow) {
		retval = false;
	}

	if (!retval) {
		sMotivo = "Tu raza no puede usar este objeto.";
	}

	return retval;
}

void UseInvItem(int UserIndex, int Slot) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 10/12/2009 */
	/* 'Handels the usage of items from inventory box. */
	/* '24/01/2007 Pablo (ToxicWaste) - Agrego el Cuerno de la Armada y la Legión. */
	/* '24/01/2007 Pablo (ToxicWaste) - Utilización nueva de Barco en lvl 20 por clase Pirata y Pescador. */
	/* '01/08/2009: ZaMa - Now it's not sent any sound made by an invisible admin, except to its own client */
	/* '17/11/2009: ZaMa - Ahora se envia una orientacion de la posicion hacia donde esta el que uso el cuerno. */
	/* '27/11/2009: Budi - Se envia indivualmente cuando se modifica a la Agilidad o la Fuerza del personaje. */
	/* '08/12/2009: ZaMa - Agrego el uso de hacha de madera elfica. */
	/* '10/12/2009: ZaMa - Arreglos y validaciones en todos las herramientas de trabajo. */
	/* '************************************************* */

	struct ObjData Obj;
	int ObjIndex;
	struct ObjData TargObj;
	struct Obj MiObj;
	std::string sMensaje;

	if (UserList[UserIndex].Invent.Object[Slot].Amount == 0) {
		return;
	}

	Obj = ObjData[UserList[UserIndex].Invent.Object[Slot].ObjIndex];

	if (Obj.Newbie == 1 && !EsNewbie(UserIndex)) {
		WriteConsoleMsg(UserIndex, "Sólo los newbies pueden usar estos objetos.",
				FontTypeNames_FONTTYPE_INFO);
		return;
	}

	if (Obj.OBJType == eOBJType_otWeapon) {
		if (Obj.proyectil == 1) {

			/* 'valido para evitar el flood pero no bloqueo. El bloqueo se hace en WLC con proyectiles. */
			if (!IntervaloPermiteUsar(UserIndex, false)) {
				return;
			}
		} else {
			/* 'dagas */
			if (!IntervaloPermiteUsar(UserIndex)) {
				return;
			}
		}
	} else {
		if (!IntervaloPermiteUsar(UserIndex)) {
			return;
		}
	}

	ObjIndex = UserList[UserIndex].Invent.Object[Slot].ObjIndex;
	UserList[UserIndex].flags.TargetObjInvIndex = ObjIndex;
	UserList[UserIndex].flags.TargetObjInvSlot = Slot;

	switch (Obj.OBJType) {
	case eOBJType_otUseOnce:
		if (UserList[UserIndex].flags.Muerto == 1) {
			WriteConsoleMsg(UserIndex, "¡¡Estás muerto!! Sólo puedes usar ítems cuando estás vivo.",
					FontTypeNames_FONTTYPE_INFO);
			return;
		}

		/* 'Usa el item */
		UserList[UserIndex].Stats.MinHam = UserList[UserIndex].Stats.MinHam + Obj.MinHam;
		if (UserList[UserIndex].Stats.MinHam > UserList[UserIndex].Stats.MaxHam) {
			UserList[UserIndex].Stats.MinHam = UserList[UserIndex].Stats.MaxHam;
		}
		UserList[UserIndex].flags.Hambre = 0;
		WriteUpdateHungerAndThirst(UserIndex);
		/* 'Sonido */

		if (ObjIndex == e_ObjetosCriticos_Manzana || ObjIndex == e_ObjetosCriticos_Manzana2
				|| ObjIndex == e_ObjetosCriticos_ManzanaNewbie) {
			SonidosMapas->ReproducirSonido(SendTarget_ToPCArea, UserIndex, e_SoundIndex_MORFAR_MANZANA);
		} else {
			SonidosMapas->ReproducirSonido(SendTarget_ToPCArea, UserIndex, e_SoundIndex_SOUND_COMIDA);
		}

		/* 'Quitamos del inv el item */
		QuitarUserInvItem(UserIndex, Slot, 1);

		UpdateUserInv(false, UserIndex, Slot);

		break;

	case eOBJType_otGuita:
		if (UserList[UserIndex].flags.Muerto == 1) {
			WriteConsoleMsg(UserIndex, "¡¡Estás muerto!! Sólo puedes usar ítems cuando estás vivo.",
					FontTypeNames_FONTTYPE_INFO);
			return;
		}

		UserList[UserIndex].Stats.GLD = UserList[UserIndex].Stats.GLD
				+ UserList[UserIndex].Invent.Object[Slot].Amount;
		UserList[UserIndex].Invent.Object[Slot].Amount = 0;
		UserList[UserIndex].Invent.Object[Slot].ObjIndex = 0;
		UserList[UserIndex].Invent.NroItems = UserList[UserIndex].Invent.NroItems - 1;

		UpdateUserInv(false, UserIndex, Slot);
		WriteUpdateGold(UserIndex);

		break;

	case eOBJType_otWeapon:
		if (UserList[UserIndex].flags.Muerto == 1) {
			WriteConsoleMsg(UserIndex, "¡¡Estás muerto!! Sólo puedes usar ítems cuando estás vivo.",
					FontTypeNames_FONTTYPE_INFO);
			return;
		}

		if (!(UserList[UserIndex].Stats.MinSta > 0)) {
			WriteConsoleMsg(UserIndex,
					vb6::CStr("Estás muy cansad")
							+ vb6::IIf(UserList[UserIndex].Genero == eGenero_Hombre, "o", "a") + ".",
					FontTypeNames_FONTTYPE_INFO);
			return;
		}

		if (ObjData[ObjIndex].proyectil == 1) {
			if (UserList[UserIndex].Invent.Object[Slot].Equipped == 0) {
				WriteConsoleMsg(UserIndex, "Antes de usar la herramienta deberías equipartela.",
						FontTypeNames_FONTTYPE_INFO);
				return;
			}
			/* 'Call WriteWorkRequestTarget(UserIndex, Proyectiles) */
			WriteMultiMessage(UserIndex, eMessages_WorkRequestTarget, eSkill_Proyectiles);
		} else if (UserList[UserIndex].flags.TargetObj == Lena) {
			if (UserList[UserIndex].Invent.Object[Slot].ObjIndex == DAGA) {
				if (UserList[UserIndex].Invent.Object[Slot].Equipped == 0) {
					WriteConsoleMsg(UserIndex, "Antes de usar la herramienta deberías equipartela.",
							FontTypeNames_FONTTYPE_INFO);
					return;
				}

				TratarDeHacerFogata(UserList[UserIndex].flags.TargetObjMap,
						UserList[UserIndex].flags.TargetObjX, UserList[UserIndex].flags.TargetObjY,
						UserIndex);
			}
		} else {

			if (ObjIndex == CANA_PESCA || ObjIndex == RED_PESCA || ObjIndex == CANA_PESCA_NEWBIE) {

				/* ' Lo tiene equipado? */
				if (UserList[UserIndex].Invent.WeaponEqpObjIndex == ObjIndex) {
					/* 'Call WriteWorkRequestTarget(UserIndex, eSkill.Pesca) */
					WriteMultiMessage(UserIndex, eMessages_WorkRequestTarget, eSkill_Pesca);
				} else {
					WriteConsoleMsg(UserIndex, "Debes tener equipada la herramienta para trabajar.",
							FontTypeNames_FONTTYPE_INFO);
				}

			} else if (ObjIndex == HACHA_LENADOR || ObjIndex == HACHA_LENA_ELFICA
					|| ObjIndex == HACHA_LENADOR_NEWBIE) {

				/* ' Lo tiene equipado? */
				if (UserList[UserIndex].Invent.WeaponEqpObjIndex == ObjIndex) {
					WriteMultiMessage(UserIndex, eMessages_WorkRequestTarget, eSkill_Talar);
				} else {
					WriteConsoleMsg(UserIndex, "Debes tener equipada la herramienta para trabajar.",
							FontTypeNames_FONTTYPE_INFO);
				}

			} else if (ObjIndex == PIQUETE_MINERO || ObjIndex == PIQUETE_MINERO_NEWBIE) {

				/* ' Lo tiene equipado? */
				if (UserList[UserIndex].Invent.WeaponEqpObjIndex == ObjIndex) {
					WriteMultiMessage(UserIndex, eMessages_WorkRequestTarget, eSkill_Mineria);
				} else {
					WriteConsoleMsg(UserIndex, "Debes tener equipada la herramienta para trabajar.",
							FontTypeNames_FONTTYPE_INFO);
				}

			} else if (ObjIndex == MARTILLO_HERRERO || ObjIndex == MARTILLO_HERRERO_NEWBIE) {

				/* ' Lo tiene equipado? */
				if (UserList[UserIndex].Invent.WeaponEqpObjIndex == ObjIndex) {
					WriteMultiMessage(UserIndex, eMessages_WorkRequestTarget, eSkill_Herreria);
				} else {
					WriteConsoleMsg(UserIndex, "Debes tener equipada la herramienta para trabajar.",
							FontTypeNames_FONTTYPE_INFO);
				}

			} else if (ObjIndex == SERRUCHO_CARPINTERO || ObjIndex == SERRUCHO_CARPINTERO_NEWBIE) {

				/* ' Lo tiene equipado? */
				if (UserList[UserIndex].Invent.WeaponEqpObjIndex == ObjIndex) {
					EnivarObjConstruibles(UserIndex);
					WriteShowCarpenterForm(UserIndex);
				} else {
					WriteConsoleMsg(UserIndex, "Debes tener equipada la herramienta para trabajar.",
							FontTypeNames_FONTTYPE_INFO);
				}

				/* ' Las herramientas no se pueden fundir */
			} else {

				if (ObjData[ObjIndex].SkHerreria > 0) {
					/* ' Solo objetos que pueda hacer el herrero */
					/* 'Call WriteWorkRequestTarget(UserIndex, FundirMetal) */
					WriteMultiMessage(UserIndex, eMessages_WorkRequestTarget, FundirMetal);
				}
			}
		}
		break;

	case eOBJType_otPociones:
		if (UserList[UserIndex].flags.Muerto == 1) {
			WriteConsoleMsg(UserIndex, "¡¡Estás muerto!! Sólo puedes usar ítems cuando estás vivo. ",
					FontTypeNames_FONTTYPE_INFO);
			return;
		}

		if (!IntervaloPermiteGolpeUsar(UserIndex, false)) {
			WriteConsoleMsg(UserIndex, "¡¡Debes esperar unos momentos para tomar otra poción!!",
					FontTypeNames_FONTTYPE_INFO);
			return;
		}

		UserList[UserIndex].flags.TomoPocion = true;
		UserList[UserIndex].flags.TipoPocion = Obj.TipoPocion;

		switch (UserList[UserIndex].flags.TipoPocion) {

		/* 'Modif la agilidad */
		case 1:
			UserList[UserIndex].flags.DuracionEfecto = Obj.DuracionEfecto;

			/* 'Usa el item */
			UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad] =
					UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad]
							+ RandomNumber(Obj.MinModificador, Obj.MaxModificador);
			if (UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad] > MAXATRIBUTOS) {
				UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad] = MAXATRIBUTOS;
			}
			if (UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad]
					> 2 * UserList[UserIndex].Stats.UserAtributosBackUP[eAtributos_Agilidad]) {
				UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad] = 2
						* UserList[UserIndex].Stats.UserAtributosBackUP[eAtributos_Agilidad];
			}

			/* 'Quitamos del inv el item */
			QuitarUserInvItem(UserIndex, Slot, 1);

			/* ' Los admin invisibles solo producen sonidos a si mismos */
			if (UserList[UserIndex].flags.AdminInvisible == 1) {
				SendData(SendTarget_ToUserIndex, UserIndex,
						dakara::protocol::server::BuildPlayWave(SND_BEBER, UserList[UserIndex].Pos.X,
								UserList[UserIndex].Pos.Y));
			} else {
				SendData(SendTarget_ToPCArea, UserIndex,
						dakara::protocol::server::BuildPlayWave(SND_BEBER, UserList[UserIndex].Pos.X,
								UserList[UserIndex].Pos.Y));
			}
			WriteUpdateDexterity(UserIndex);

			/* 'Modif la fuerza */
			break;

		case 2:
			UserList[UserIndex].flags.DuracionEfecto = Obj.DuracionEfecto;

			/* 'Usa el item */
			UserList[UserIndex].Stats.UserAtributos[eAtributos_Fuerza] =
					UserList[UserIndex].Stats.UserAtributos[eAtributos_Fuerza]
							+ RandomNumber(Obj.MinModificador, Obj.MaxModificador);
			if (UserList[UserIndex].Stats.UserAtributos[eAtributos_Fuerza] > MAXATRIBUTOS) {
				UserList[UserIndex].Stats.UserAtributos[eAtributos_Fuerza] = MAXATRIBUTOS;
			}
			if (UserList[UserIndex].Stats.UserAtributos[eAtributos_Fuerza]
					> 2 * UserList[UserIndex].Stats.UserAtributosBackUP[eAtributos_Fuerza]) {
				UserList[UserIndex].Stats.UserAtributos[eAtributos_Fuerza] = 2
						* UserList[UserIndex].Stats.UserAtributosBackUP[eAtributos_Fuerza];
			}

			/* 'Quitamos del inv el item */
			QuitarUserInvItem(UserIndex, Slot, 1);

			/* ' Los admin invisibles solo producen sonidos a si mismos */
			if (UserList[UserIndex].flags.AdminInvisible == 1) {
				SendData(SendTarget_ToUserIndex, UserIndex,
						dakara::protocol::server::BuildPlayWave(SND_BEBER, UserList[UserIndex].Pos.X,
								UserList[UserIndex].Pos.Y));
			} else {
				SendData(SendTarget_ToPCArea, UserIndex,
						dakara::protocol::server::BuildPlayWave(SND_BEBER, UserList[UserIndex].Pos.X,
								UserList[UserIndex].Pos.Y));
			}
			WriteUpdateStrenght(UserIndex);

			/* 'Pocion roja, restaura HP */
			break;

		case 3:
			/* 'Usa el item */
			UserList[UserIndex].Stats.MinHp = UserList[UserIndex].Stats.MinHp
					+ RandomNumber(Obj.MinModificador, Obj.MaxModificador);
			if (UserList[UserIndex].Stats.MinHp > UserList[UserIndex].Stats.MaxHp) {
				UserList[UserIndex].Stats.MinHp = UserList[UserIndex].Stats.MaxHp;
			}

			/* 'Quitamos del inv el item */
			QuitarUserInvItem(UserIndex, Slot, 1);

			/* ' Los admin invisibles solo producen sonidos a si mismos */
			if (UserList[UserIndex].flags.AdminInvisible == 1) {
				SendData(SendTarget_ToUserIndex, UserIndex,
						dakara::protocol::server::BuildPlayWave(SND_BEBER, UserList[UserIndex].Pos.X,
								UserList[UserIndex].Pos.Y));
			} else {
				SendData(SendTarget_ToPCArea, UserIndex,
						dakara::protocol::server::BuildPlayWave(SND_BEBER, UserList[UserIndex].Pos.X,
								UserList[UserIndex].Pos.Y));
			}

			/* 'Pocion azul, restaura MANA */
			break;

		case 4:
			/* 'Usa el item */
			/* 'nuevo calculo para recargar mana */

			if (Obj.MaxModificador == 0) {
				UserList[UserIndex].Stats.MinMAN = UserList[UserIndex].Stats.MinMAN
						+ Porcentaje(UserList[UserIndex].Stats.MaxMAN, 4) + UserList[UserIndex].Stats.ELV / 2
						+ 40 / UserList[UserIndex].Stats.ELV;
			} else {
				UserList[UserIndex].Stats.MinMAN = UserList[UserIndex].Stats.MinMAN
						+ Porcentaje(UserList[UserIndex].Stats.MaxMAN,
								RandomNumber(Obj.MinModificador, Obj.MaxModificador));
			}

			if (UserList[UserIndex].Stats.MinMAN > UserList[UserIndex].Stats.MaxMAN) {
				UserList[UserIndex].Stats.MinMAN = UserList[UserIndex].Stats.MaxMAN;
			}

			/* 'Quitamos del inv el item */
			QuitarUserInvItem(UserIndex, Slot, 1);

			/* ' Los admin invisibles solo producen sonidos a si mismos */
			if (UserList[UserIndex].flags.AdminInvisible == 1) {
				SendData(SendTarget_ToUserIndex, UserIndex,
						dakara::protocol::server::BuildPlayWave(SND_BEBER, UserList[UserIndex].Pos.X,
								UserList[UserIndex].Pos.Y));
			} else {
				SendData(SendTarget_ToPCArea, UserIndex,
						dakara::protocol::server::BuildPlayWave(SND_BEBER, UserList[UserIndex].Pos.X,
								UserList[UserIndex].Pos.Y));
			}

			/* ' Pocion violeta */
			break;

		case 5:
			if (UserList[UserIndex].flags.Envenenado == 1) {
				UserList[UserIndex].flags.Envenenado = 0;
				WriteConsoleMsg(UserIndex, "Te has curado del envenenamiento.", FontTypeNames_FONTTYPE_INFO);
			}
			/* 'Quitamos del inv el item */
			QuitarUserInvItem(UserIndex, Slot, 1);

			/* ' Los admin invisibles solo producen sonidos a si mismos */
			if (UserList[UserIndex].flags.AdminInvisible == 1) {
				SendData(SendTarget_ToUserIndex, UserIndex,
						dakara::protocol::server::BuildPlayWave(SND_BEBER, UserList[UserIndex].Pos.X,
								UserList[UserIndex].Pos.Y));
			} else {
				SendData(SendTarget_ToPCArea, UserIndex,
						dakara::protocol::server::BuildPlayWave(SND_BEBER, UserList[UserIndex].Pos.X,
								UserList[UserIndex].Pos.Y));
			}

			/* ' Pocion Negra */
			break;

		case 6:
			if (UserTienePrivilegio(UserIndex, PlayerType_User)) {
				QuitarUserInvItem(UserIndex, Slot, 1);
				UserDie(UserIndex);
				WriteConsoleMsg(UserIndex, "Sientes un gran mareo y pierdes el conocimiento.",
						FontTypeNames_FONTTYPE_FIGHT);
			}
			break;
		}
		WriteUpdateUserStats(UserIndex);
		UpdateUserInv(false, UserIndex, Slot);
		break;

	case eOBJType_otBebidas:
		if (UserList[UserIndex].flags.Muerto == 1) {
			WriteConsoleMsg(UserIndex, "¡¡Estás muerto!! Sólo puedes usar ítems cuando estás vivo.",
					FontTypeNames_FONTTYPE_INFO);
			return;
		}
		UserList[UserIndex].Stats.MinAGU = UserList[UserIndex].Stats.MinAGU + Obj.MinSed;
		if (UserList[UserIndex].Stats.MinAGU > UserList[UserIndex].Stats.MaxAGU) {
			UserList[UserIndex].Stats.MinAGU = UserList[UserIndex].Stats.MaxAGU;
		}
		UserList[UserIndex].flags.Sed = 0;
		WriteUpdateHungerAndThirst(UserIndex);

		/* 'Quitamos del inv el item */
		QuitarUserInvItem(UserIndex, Slot, 1);

		/* ' Los admin invisibles solo producen sonidos a si mismos */
		if (UserList[UserIndex].flags.AdminInvisible == 1) {
			SendData(SendTarget_ToUserIndex, UserIndex,
					dakara::protocol::server::BuildPlayWave(SND_BEBER, UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y));
		} else {
			SendData(SendTarget_ToPCArea, UserIndex,
					dakara::protocol::server::BuildPlayWave(SND_BEBER, UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y));
		}

		UpdateUserInv(false, UserIndex, Slot);

		break;

	case eOBJType_otLlaves:
		if (UserList[UserIndex].flags.Muerto == 1) {
			WriteConsoleMsg(UserIndex, "¡¡Estás muerto!! Sólo puedes usar ítems cuando estás vivo.",
					FontTypeNames_FONTTYPE_INFO);
			return;
		}

		if (UserList[UserIndex].flags.TargetObj == 0) {
			return;
		}
		TargObj = ObjData[UserList[UserIndex].flags.TargetObj];
		/* '¿El objeto clickeado es una puerta? */
		if (TargObj.OBJType == eOBJType_otPuertas) {
			/* '¿Esta cerrada? */
			if (TargObj.Cerrada == 1) {
				/* '¿Cerrada con llave? */
				if (TargObj.Llave > 0) {
					if (TargObj.clave == Obj.clave) {

						MapData[UserList[UserIndex].flags.TargetObjMap][UserList[UserIndex].flags.TargetObjX][UserList[UserIndex].flags.TargetObjY].ObjInfo.ObjIndex =
								ObjData[MapData[UserList[UserIndex].flags.TargetObjMap][UserList[UserIndex].flags.TargetObjX][UserList[UserIndex].flags.TargetObjY].ObjInfo.ObjIndex].IndexCerrada;
						UserList[UserIndex].flags.TargetObj =
								MapData[UserList[UserIndex].flags.TargetObjMap][UserList[UserIndex].flags.TargetObjX][UserList[UserIndex].flags.TargetObjY].ObjInfo.ObjIndex;
						WriteConsoleMsg(UserIndex, "Has abierto la puerta.", FontTypeNames_FONTTYPE_INFO);
						return;
					} else {
						WriteConsoleMsg(UserIndex, "La llave no sirve.", FontTypeNames_FONTTYPE_INFO);
						return;
					}
				} else {
					if (TargObj.clave == Obj.clave) {
						MapData[UserList[UserIndex].flags.TargetObjMap][UserList[UserIndex].flags.TargetObjX][UserList[UserIndex].flags.TargetObjY].ObjInfo.ObjIndex =
								ObjData[MapData[UserList[UserIndex].flags.TargetObjMap][UserList[UserIndex].flags.TargetObjX][UserList[UserIndex].flags.TargetObjY].ObjInfo.ObjIndex].IndexCerradaLlave;
						WriteConsoleMsg(UserIndex, "Has cerrado con llave la puerta.",
								FontTypeNames_FONTTYPE_INFO);
						UserList[UserIndex].flags.TargetObj =
								MapData[UserList[UserIndex].flags.TargetObjMap][UserList[UserIndex].flags.TargetObjX][UserList[UserIndex].flags.TargetObjY].ObjInfo.ObjIndex;
						return;
					} else {
						WriteConsoleMsg(UserIndex, "La llave no sirve.", FontTypeNames_FONTTYPE_INFO);
						return;
					}
				}
			} else {
				WriteConsoleMsg(UserIndex, "No está cerrada.", FontTypeNames_FONTTYPE_INFO);
				return;
			}
		}

		break;

	case eOBJType_otBotellaVacia:
		if (UserList[UserIndex].flags.Muerto == 1) {
			WriteConsoleMsg(UserIndex, "¡¡Estás muerto!! Sólo puedes usar ítems cuando estás vivo.",
					FontTypeNames_FONTTYPE_INFO);
			return;
		}
		if (!HayAgua(UserList[UserIndex].Pos.Map, UserList[UserIndex].flags.TargetX,
				UserList[UserIndex].flags.TargetY)) {
			WriteConsoleMsg(UserIndex, "No hay agua allí.", FontTypeNames_FONTTYPE_INFO);
			return;
		}
		MiObj.Amount = 1;
		MiObj.ObjIndex = ObjData[UserList[UserIndex].Invent.Object[Slot].ObjIndex].IndexAbierta;
		QuitarUserInvItem(UserIndex, Slot, 1);
		if (!MeterItemEnInventario(UserIndex, MiObj)) {
			TirarItemAlPiso(UserList[UserIndex].Pos, MiObj);
		}

		UpdateUserInv(false, UserIndex, Slot);

		break;

	case eOBJType_otBotellaLlena:
		if (UserList[UserIndex].flags.Muerto == 1) {
			WriteConsoleMsg(UserIndex, "¡¡Estás muerto!! Sólo puedes usar ítems cuando estás vivo.",
					FontTypeNames_FONTTYPE_INFO);
			return;
		}
		UserList[UserIndex].Stats.MinAGU = UserList[UserIndex].Stats.MinAGU + Obj.MinSed;
		if (UserList[UserIndex].Stats.MinAGU > UserList[UserIndex].Stats.MaxAGU) {
			UserList[UserIndex].Stats.MinAGU = UserList[UserIndex].Stats.MaxAGU;
		}
		UserList[UserIndex].flags.Sed = 0;
		WriteUpdateHungerAndThirst(UserIndex);
		MiObj.Amount = 1;
		MiObj.ObjIndex = ObjData[UserList[UserIndex].Invent.Object[Slot].ObjIndex].IndexCerrada;
		QuitarUserInvItem(UserIndex, Slot, 1);
		if (!MeterItemEnInventario(UserIndex, MiObj)) {
			TirarItemAlPiso(UserList[UserIndex].Pos, MiObj);
		}

		UpdateUserInv(false, UserIndex, Slot);

		break;

	case eOBJType_otPergaminos:
		if (UserList[UserIndex].flags.Muerto == 1) {
			WriteConsoleMsg(UserIndex, "¡¡Estás muerto!! Sólo puedes usar ítems cuando estás vivo.",
					FontTypeNames_FONTTYPE_INFO);
			return;
		}

		if (UserList[UserIndex].Stats.MaxMAN > 0) {
			if (UserList[UserIndex].flags.Hambre == 0 && UserList[UserIndex].flags.Sed == 0) {
				AgregarHechizo(UserIndex, Slot);
				UpdateUserInv(false, UserIndex, Slot);
			} else {
				WriteConsoleMsg(UserIndex, "Estás demasiado hambriento y sediento.",
						FontTypeNames_FONTTYPE_INFO);
			}
		} else {
			WriteConsoleMsg(UserIndex, "No tienes conocimientos de las Artes Arcanas.",
					FontTypeNames_FONTTYPE_INFO);
		}
		break;

	case eOBJType_otMinerales:
		if (UserList[UserIndex].flags.Muerto == 1) {
			WriteConsoleMsg(UserIndex, "¡¡Estás muerto!! Sólo puedes usar ítems cuando estás vivo.",
					FontTypeNames_FONTTYPE_INFO);
			return;
		}
		/* 'Call WriteWorkRequestTarget(UserIndex, FundirMetal) */
		WriteMultiMessage(UserIndex, eMessages_WorkRequestTarget, FundirMetal);

		break;

	case eOBJType_otInstrumentos:
		if (UserList[UserIndex].flags.Muerto == 1) {
			WriteConsoleMsg(UserIndex, "¡¡Estás muerto!! Sólo puedes usar ítems cuando estás vivo.",
					FontTypeNames_FONTTYPE_INFO);
			return;
		}

		/* '¿Es el Cuerno Real? */
		if (Obj.Real) {
			if (FaccionPuedeUsarItem(UserIndex, ObjIndex, sMensaje)) {
				if (MapInfo[UserList[UserIndex].Pos.Map].Pk == false) {
					WriteConsoleMsg(UserIndex, "No hay peligro aquí. Es zona segura.",
							FontTypeNames_FONTTYPE_INFO);
					return;
				}

				/* ' Los admin invisibles solo producen sonidos a si mismos */
				if (UserList[UserIndex].flags.AdminInvisible == 1) {
					SendData(SendTarget_ToUserIndex, UserIndex,
							dakara::protocol::server::BuildPlayWave(Obj.Snd1, UserList[UserIndex].Pos.X,
									UserList[UserIndex].Pos.Y));
				} else {
					AlertarFaccionarios(UserIndex);
					SendData(SendTarget_toMap, UserList[UserIndex].Pos.Map,
							dakara::protocol::server::BuildPlayWave(Obj.Snd1, UserList[UserIndex].Pos.X,
									UserList[UserIndex].Pos.Y));
				}

				return;
			} else {
				WriteConsoleMsg(UserIndex, "Sólo miembros del ejército real pueden usar este cuerno.",
						FontTypeNames_FONTTYPE_INFO);
				return;
			}
			/* '¿Es el Cuerno Legión? */
		} else if (Obj.Caos) {
			if (FaccionPuedeUsarItem(UserIndex, ObjIndex, sMensaje)) {
				if (MapInfo[UserList[UserIndex].Pos.Map].Pk == false) {
					WriteConsoleMsg(UserIndex, "No hay peligro aquí. Es zona segura.",
							FontTypeNames_FONTTYPE_INFO);
					return;
				}

				/* ' Los admin invisibles solo producen sonidos a si mismos */
				if (UserList[UserIndex].flags.AdminInvisible == 1) {
					SendData(SendTarget_ToUserIndex, UserIndex,
							dakara::protocol::server::BuildPlayWave(Obj.Snd1, UserList[UserIndex].Pos.X,
									UserList[UserIndex].Pos.Y));
				} else {
					AlertarFaccionarios(UserIndex);
					SendData(SendTarget_toMap, UserList[UserIndex].Pos.Map,
							dakara::protocol::server::BuildPlayWave(Obj.Snd1, UserList[UserIndex].Pos.X,
									UserList[UserIndex].Pos.Y));
				}

				return;
			} else {
				WriteConsoleMsg(UserIndex, "Sólo miembros de la legión oscura pueden usar este cuerno.",
						FontTypeNames_FONTTYPE_INFO);
				return;
			}
		}
		/* 'Si llega aca es porque es o Laud o Tambor o Flauta */
		/* ' Los admin invisibles solo producen sonidos a si mismos */
		if (UserList[UserIndex].flags.AdminInvisible == 1) {
			SendData(SendTarget_ToUserIndex, UserIndex,
					dakara::protocol::server::BuildPlayWave(Obj.Snd1, UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y));
		} else {
			SendData(SendTarget_ToPCArea, UserIndex,
					dakara::protocol::server::BuildPlayWave(Obj.Snd1, UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y));
		}

		break;

	case eOBJType_otBarcos:
		/* 'Verifica si esta aproximado al agua antes de permitirle navegar */
		if (UserList[UserIndex].Stats.ELV < 25) {
			/* ' Solo pirata y trabajador pueden navegar antes */
			if (UserList[UserIndex].clase != eClass_Worker && UserList[UserIndex].clase != eClass_Pirat) {
				WriteConsoleMsg(UserIndex, "Para recorrer los mares debes ser nivel 25 o superior.",
						FontTypeNames_FONTTYPE_INFO);
				return;
			} else {
				/* ' Pero a partir de 20 */
				if (UserList[UserIndex].Stats.ELV < 20) {

					if (UserList[UserIndex].clase == eClass_Worker
							&& UserList[UserIndex].Stats.UserSkills[eSkill_Pesca] != 100) {
						WriteConsoleMsg(UserIndex,
								"Para recorrer los mares debes ser nivel 20 y además tu skill en pesca debe ser 100.",
								FontTypeNames_FONTTYPE_INFO);
					} else {
						WriteConsoleMsg(UserIndex, "Para recorrer los mares debes ser nivel 20 o superior.",
								FontTypeNames_FONTTYPE_INFO);
					}

					return;
				} else {
					/* ' Esta entre 20 y 25, si es trabajador necesita tener 100 en pesca */
					if (UserList[UserIndex].clase == eClass_Worker) {
						if (UserList[UserIndex].Stats.UserSkills[eSkill_Pesca] != 100) {
							WriteConsoleMsg(UserIndex,
									"Para recorrer los mares debes ser nivel 20 o superior y además tu skill en pesca debe ser 100.",
									FontTypeNames_FONTTYPE_INFO);
							return;
						}
					}

				}
			}
		}

		if (((LegalPos(UserList[UserIndex].Pos.Map, UserList[UserIndex].Pos.X - 1, UserList[UserIndex].Pos.Y,
				true, false)
				|| LegalPos(UserList[UserIndex].Pos.Map, UserList[UserIndex].Pos.X,
						UserList[UserIndex].Pos.Y - 1, true, false)
				|| LegalPos(UserList[UserIndex].Pos.Map, UserList[UserIndex].Pos.X + 1,
						UserList[UserIndex].Pos.Y, true, false)
				|| LegalPos(UserList[UserIndex].Pos.Map, UserList[UserIndex].Pos.X,
						UserList[UserIndex].Pos.Y + 1, true, false))
				&& UserList[UserIndex].flags.Navegando == 0) || UserList[UserIndex].flags.Navegando == 1) {
			DoNavega(UserIndex, Obj, Slot);
		} else {
			WriteConsoleMsg(UserIndex, "¡Debes aproximarte al agua para usar el barco!",
					FontTypeNames_FONTTYPE_INFO);
		}
		break;

	default:
		break;
	}
}

void EnivarArmasConstruibles(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	WriteBlacksmithWeapons(UserIndex);
}

void EnivarObjConstruibles(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	WriteCarpenterObjects(UserIndex);
}

void EnivarArmadurasConstruibles(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	WriteBlacksmithArmors(UserIndex);
}

void TirarTodo(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (MapData[UserList[UserIndex].Pos.Map][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].trigger
			== 6) {
		return;
	}

	TirarTodosLosItems(UserIndex);

	int Cantidad;
	Cantidad = UserList[UserIndex].Stats.GLD - vb6::CLng(UserList[UserIndex].Stats.ELV) * 10000;

	if (Cantidad > 0) {
		TirarOro(Cantidad, UserIndex);
	}

	return;
}

bool ItemSeCae(int index) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	retval = (ObjData[index].Real != 1 || ObjData[index].NoSeCae == 0)
			&& (ObjData[index].Caos != 1 || ObjData[index].NoSeCae == 0)
			&& ObjData[index].OBJType != eOBJType_otLlaves && ObjData[index].OBJType != eOBJType_otBarcos
			&& ObjData[index].NoSeCae == 0 && ObjData[index].Intransferible == 0;

	return retval;
}

void TirarTodosLosItems(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 12/01/2010 (ZaMa) */
	/* '12/01/2010: ZaMa - Ahora los piratas no explotan items solo si estan entre 20 y 25 */
	/* '*************************************************** */

	int i;
	struct WorldPos NuevaPos;
	struct Obj MiObj;
	int ItemIndex;
	bool DropAgua;

	for (i = (1); i <= (UserList[UserIndex].CurrentInventorySlots); i++) {
		ItemIndex = UserList[UserIndex].Invent.Object[i].ObjIndex;
		if (ItemIndex > 0) {
			if (ItemSeCae(ItemIndex)) {
				NuevaPos.X = 0;
				NuevaPos.Y = 0;

				/* 'Creo el Obj */
				MiObj.Amount = UserList[UserIndex].Invent.Object[i].Amount;
				MiObj.ObjIndex = ItemIndex;

				DropAgua = true;
				/* ' Es pirata? */
				if (UserList[UserIndex].clase == eClass_Pirat) {
					/* ' Si tiene galeon equipado */
					if (UserList[UserIndex].Invent.BarcoObjIndex == 476) {
						/* ' Limitación por nivel, después dropea normalmente */
						if (UserList[UserIndex].Stats.ELV == 20) {
							/* ' No dropea en agua */
							DropAgua = false;
						}
					}
				}

				Tilelibre(UserList[UserIndex].Pos, NuevaPos, MiObj, DropAgua, true);

				if (NuevaPos.X != 0 && NuevaPos.Y != 0) {
					DropObj(UserIndex, i, MAX_INVENTORY_OBJS, NuevaPos.Map, NuevaPos.X, NuevaPos.Y);
				}
			}
		}
	}
}

bool ItemNewbie(int ItemIndex) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (ItemIndex < 1 || ItemIndex > vb6::UBound(ObjData)) {
		return retval;
	}

	retval = ObjData[ItemIndex].Newbie == 1;
	return retval;
}

void TirarTodosLosItemsNoNewbies(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 23/11/2009 */
	/* '07/11/09: Pato - Fix bug #2819911 */
	/* '23/11/2009: ZaMa - Optimizacion de codigo. */
	/* '*************************************************** */
	int i;
	struct WorldPos NuevaPos;
	struct Obj MiObj;
	int ItemIndex;

	if (MapData[UserList[UserIndex].Pos.Map][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].trigger
			== 6) {
		return;
	}

	for (i = (1); i <= (UserList[UserIndex].CurrentInventorySlots); i++) {
		ItemIndex = UserList[UserIndex].Invent.Object[i].ObjIndex;
		if (ItemIndex > 0) {
			if (ItemSeCae(ItemIndex) && !ItemNewbie(ItemIndex)) {
				NuevaPos.X = 0;
				NuevaPos.Y = 0;

				/* 'Creo MiObj */
				MiObj.Amount = UserList[UserIndex].Invent.Object[i].Amount;
				MiObj.ObjIndex = ItemIndex;
				/* 'Pablo (ToxicWaste) 24/01/2007 */
				/* 'Tira los Items no newbies en todos lados. */
				Tilelibre(UserList[UserIndex].Pos, NuevaPos, MiObj, true, true);
				if (NuevaPos.X != 0 && NuevaPos.Y != 0) {
					DropObj(UserIndex, i, MAX_INVENTORY_OBJS, NuevaPos.Map, NuevaPos.X, NuevaPos.Y);
				}
			}
		}
	}

}

void TirarTodosLosItemsEnMochila(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 12/01/09 (Budi) */
	/* '*************************************************** */
	int i;
	struct WorldPos NuevaPos;
	struct Obj MiObj;
	int ItemIndex;

	if (MapData[UserList[UserIndex].Pos.Map][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].trigger
			== 6) {
		return;
	}

	for (i = (MAX_NORMAL_INVENTORY_SLOTS + 1); i <= (UserList[UserIndex].CurrentInventorySlots); i++) {
		ItemIndex = UserList[UserIndex].Invent.Object[i].ObjIndex;
		if (ItemIndex > 0) {
			if (ItemSeCae(ItemIndex)) {
				NuevaPos.X = 0;
				NuevaPos.Y = 0;

				/* 'Creo MiObj */
				MiObj.Amount = UserList[UserIndex].Invent.Object[i].Amount;
				MiObj.ObjIndex = ItemIndex;
				Tilelibre(UserList[UserIndex].Pos, NuevaPos, MiObj, true, true);
				if (NuevaPos.X != 0 && NuevaPos.Y != 0) {
					DropObj(UserIndex, i, MAX_INVENTORY_OBJS, NuevaPos.Map, NuevaPos.X, NuevaPos.Y);
				}
			}
		}
	}

}

eOBJType getObjType(int ObjIndex) {
	eOBJType retval = eOBJType_Null;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (ObjIndex > 0) {
		retval = ObjData[ObjIndex].OBJType;
	}

	return retval;
}

void moveItem(int UserIndex, int originalSlot, int newSlot) {

	struct UserOBJ tmpObj;
//	int newObjIndex;
//	int originalObjIndex;
	if ((originalSlot <= 0) || (newSlot <= 0)) {
		return;
	}

	if ((originalSlot > UserList[UserIndex].CurrentInventorySlots)
			|| (newSlot > UserList[UserIndex].CurrentInventorySlots)) {
		return;
	}

	tmpObj = UserList[UserIndex].Invent.Object[originalSlot];
	UserList[UserIndex].Invent.Object[originalSlot] = UserList[UserIndex].Invent.Object[newSlot];
	UserList[UserIndex].Invent.Object[newSlot] = tmpObj;

	/* 'Viva VB6 y sus putas deficiencias. */
	if (UserList[UserIndex].Invent.AnilloEqpSlot == originalSlot) {
		UserList[UserIndex].Invent.AnilloEqpSlot = newSlot;
	} else if (UserList[UserIndex].Invent.AnilloEqpSlot == newSlot) {
		UserList[UserIndex].Invent.AnilloEqpSlot = originalSlot;
	}

	if (UserList[UserIndex].Invent.ArmourEqpSlot == originalSlot) {
		UserList[UserIndex].Invent.ArmourEqpSlot = newSlot;
	} else if (UserList[UserIndex].Invent.ArmourEqpSlot == newSlot) {
		UserList[UserIndex].Invent.ArmourEqpSlot = originalSlot;
	}

	if (UserList[UserIndex].Invent.BarcoSlot == originalSlot) {
		UserList[UserIndex].Invent.BarcoSlot = newSlot;
	} else if (UserList[UserIndex].Invent.BarcoSlot == newSlot) {
		UserList[UserIndex].Invent.BarcoSlot = originalSlot;
	}

	if (UserList[UserIndex].Invent.CascoEqpSlot == originalSlot) {
		UserList[UserIndex].Invent.CascoEqpSlot = newSlot;
	} else if (UserList[UserIndex].Invent.CascoEqpSlot == newSlot) {
		UserList[UserIndex].Invent.CascoEqpSlot = originalSlot;
	}

	if (UserList[UserIndex].Invent.EscudoEqpSlot == originalSlot) {
		UserList[UserIndex].Invent.EscudoEqpSlot = newSlot;
	} else if (UserList[UserIndex].Invent.EscudoEqpSlot == newSlot) {
		UserList[UserIndex].Invent.EscudoEqpSlot = originalSlot;
	}

	if (UserList[UserIndex].Invent.MochilaEqpSlot == originalSlot) {
		UserList[UserIndex].Invent.MochilaEqpSlot = newSlot;
	} else if (UserList[UserIndex].Invent.MochilaEqpSlot == newSlot) {
		UserList[UserIndex].Invent.MochilaEqpSlot = originalSlot;
	}

	if (UserList[UserIndex].Invent.MunicionEqpSlot == originalSlot) {
		UserList[UserIndex].Invent.MunicionEqpSlot = newSlot;
	} else if (UserList[UserIndex].Invent.MunicionEqpSlot == newSlot) {
		UserList[UserIndex].Invent.MunicionEqpSlot = originalSlot;
	}

	if (UserList[UserIndex].Invent.WeaponEqpSlot == originalSlot) {
		UserList[UserIndex].Invent.WeaponEqpSlot = newSlot;
	} else if (UserList[UserIndex].Invent.WeaponEqpSlot == newSlot) {
		UserList[UserIndex].Invent.WeaponEqpSlot = originalSlot;
	}

	UpdateUserInv(false, UserIndex, originalSlot);
	UpdateUserInv(false, UserIndex, newSlot);
}
