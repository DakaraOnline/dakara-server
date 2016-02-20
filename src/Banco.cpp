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

#include "Banco.h"

void IniciarDeposito(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	/* 'Hacemos un Update del inventario del usuario */
	UpdateBanUserInv(true, UserIndex, 0);
	/* 'Actualizamos el dinero */
	WriteUpdateUserStats(UserIndex);
	/* 'Mostramos la ventana pa' comerciar y ver ladear la osamenta. jajaja */
	WriteBankInit(UserIndex);
	UserList[UserIndex].flags.Comerciando = true;

}

void SendBanObj(int UserIndex, int Slot, struct UserOBJ Object) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	UserList[UserIndex].BancoInvent.Object[Slot] = Object;

	WriteChangeBankSlot(UserIndex, Slot);

}

void UpdateBanUserInv(bool UpdateAll, int UserIndex, int Slot) {
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
		if (UserList[UserIndex].BancoInvent.Object[Slot].ObjIndex > 0) {
			SendBanObj(UserIndex, Slot, UserList[UserIndex].BancoInvent.Object[Slot]);
		} else {
			SendBanObj(UserIndex, Slot, NullObj);
		}
	} else {
		/* 'Actualiza todos los slots */
		for (LoopC = (1); LoopC <= (MAX_BANCOINVENTORY_SLOTS); LoopC++) {
			/* 'Actualiza el inventario */
			if (UserList[UserIndex].BancoInvent.Object[LoopC].ObjIndex > 0) {
				SendBanObj(UserIndex, LoopC, UserList[UserIndex].BancoInvent.Object[LoopC]);
			} else {
				SendBanObj(UserIndex, LoopC, NullObj);
			}
		}
	}

}

void UserRetiraItem(int UserIndex, int i, int Cantidad) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int ObjIndex;

	if (Cantidad < 1) {
		return;
	}

	WriteUpdateUserStats(UserIndex);

	if (UserList[UserIndex].BancoInvent.Object[i].Amount > 0) {

		if (Cantidad > UserList[UserIndex].BancoInvent.Object[i].Amount) {
			Cantidad = UserList[UserIndex].BancoInvent.Object[i].Amount;
		}

		ObjIndex = UserList[UserIndex].BancoInvent.Object[i].ObjIndex;

		/* 'Agregamos el obj que compro al inventario */
		UserReciveObj(UserIndex, vb6::CInt(i), Cantidad);

		if (ObjData[ObjIndex].Log == 1) {
			LogDesarrollo(
					UserList[UserIndex].Name + " retiró " + vb6::CStr(Cantidad) + " " + ObjData[ObjIndex].Name + "["
							+ vb6::CStr(ObjIndex) + "]");
		}

		/* 'Actualizamos el inventario del usuario */
		UpdateUserInv(true, UserIndex, 0);
		/* 'Actualizamos el banco */
		UpdateBanUserInv(true, UserIndex, 0);
	}

	/* 'Actualizamos la ventana de comercio */
	UpdateVentanaBanco(UserIndex);

}

void UserReciveObj(int UserIndex, int ObjIndex, int Cantidad) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int Slot;
	int obji;

	if (UserList[UserIndex].BancoInvent.Object[ObjIndex].Amount <= 0) {
		return;
	}

	obji = UserList[UserIndex].BancoInvent.Object[ObjIndex].ObjIndex;

	/* '¿Ya tiene un objeto de este tipo? */
	Slot = 1;
	while (!(UserList[UserIndex].Invent.Object[Slot].ObjIndex == obji
			&& UserList[UserIndex].Invent.Object[Slot].Amount + Cantidad <= MAX_INVENTORY_OBJS)) {

		Slot = Slot + 1;
		if (Slot > UserList[UserIndex].CurrentInventorySlots) {
			break;
		}
	}

	/* 'Sino se fija por un slot vacio */
	if (Slot > UserList[UserIndex].CurrentInventorySlots) {
		Slot = 1;
		while (!(UserList[UserIndex].Invent.Object[Slot].ObjIndex == 0)) {
			Slot = Slot + 1;

			if (Slot > UserList[UserIndex].CurrentInventorySlots) {
				WriteConsoleMsg(UserIndex, "No podés tener mas objetos.", FontTypeNames_FONTTYPE_INFO);
				return;
			}
		}
		UserList[UserIndex].Invent.NroItems = UserList[UserIndex].Invent.NroItems + 1;
	}

	/* 'Mete el obj en el slot */
	if (UserList[UserIndex].Invent.Object[Slot].Amount + Cantidad <= MAX_INVENTORY_OBJS) {
		/* 'Menor que MAX_INV_OBJS */
		UserList[UserIndex].Invent.Object[Slot].ObjIndex = obji;
		UserList[UserIndex].Invent.Object[Slot].Amount = UserList[UserIndex].Invent.Object[Slot].Amount
				+ Cantidad;

		QuitarBancoInvItem(UserIndex, vb6::CByte(ObjIndex), Cantidad);
	} else {
		WriteConsoleMsg(UserIndex, "No podés tener mas objetos.", FontTypeNames_FONTTYPE_INFO);
	}

}

void QuitarBancoInvItem(int UserIndex, int Slot, int Cantidad) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

//	int ObjIndex;
//
//	ObjIndex = UserList[UserIndex].BancoInvent.Object[Slot].ObjIndex;

	/* 'Quita un Obj */

	UserList[UserIndex].BancoInvent.Object[Slot].Amount = UserList[UserIndex].BancoInvent.Object[Slot].Amount
			- Cantidad;

	if (UserList[UserIndex].BancoInvent.Object[Slot].Amount <= 0) {
		UserList[UserIndex].BancoInvent.NroItems = UserList[UserIndex].BancoInvent.NroItems - 1;
		UserList[UserIndex].BancoInvent.Object[Slot].ObjIndex = 0;
		UserList[UserIndex].BancoInvent.Object[Slot].Amount = 0;
	}

}

void UpdateVentanaBanco(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	WriteBankOK(UserIndex);
}

void UserDepositaItem(int UserIndex, int Item, int Cantidad) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int ObjIndex;

	if (UserList[UserIndex].Invent.Object[Item].Amount > 0 && Cantidad > 0) {

		if (Cantidad > UserList[UserIndex].Invent.Object[Item].Amount) {
			Cantidad = UserList[UserIndex].Invent.Object[Item].Amount;
		}

		ObjIndex = UserList[UserIndex].Invent.Object[Item].ObjIndex;

		/* 'Agregamos el obj que deposita al banco */
		UserDejaObj(UserIndex, vb6::CInt(Item), Cantidad);

		if (ObjData[ObjIndex].Log == 1) {
			LogDesarrollo(
					UserList[UserIndex].Name + " depositó " + vb6::CStr(Cantidad) + " "
							+ ObjData[ObjIndex].Name + "[" + vb6::CStr(ObjIndex) + "]");
		}

		/* 'Actualizamos el inventario del usuario */
		UpdateUserInv(true, UserIndex, 0);

		/* 'Actualizamos el inventario del banco */
		UpdateBanUserInv(true, UserIndex, 0);
	}

	/* 'Actualizamos la ventana del banco */
	UpdateVentanaBanco(UserIndex);
}

void UserDejaObj(int UserIndex, int ObjIndex, int Cantidad) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int Slot;
	int obji;

	if (Cantidad < 1) {
		return;
	}

	obji = UserList[UserIndex].Invent.Object[ObjIndex].ObjIndex;

	/* '¿Ya tiene un objeto de este tipo? */
	Slot = 1;
	while (!(UserList[UserIndex].BancoInvent.Object[Slot].ObjIndex == obji
			&& UserList[UserIndex].BancoInvent.Object[Slot].Amount + Cantidad <= MAX_INVENTORY_OBJS)) {
		Slot = Slot + 1;

		if (Slot > MAX_BANCOINVENTORY_SLOTS) {
			break;
		}
	}

	/* 'Sino se fija por un slot vacio antes del slot devuelto */
	if (Slot > MAX_BANCOINVENTORY_SLOTS) {
		Slot = 1;
		while (!(UserList[UserIndex].BancoInvent.Object[Slot].ObjIndex == 0)) {
			Slot = Slot + 1;

			if (Slot > MAX_BANCOINVENTORY_SLOTS) {
				WriteConsoleMsg(UserIndex, "No tienes mas espacio en el banco!!",
						FontTypeNames_FONTTYPE_INFO);
				return;
			}
		}

		UserList[UserIndex].BancoInvent.NroItems = UserList[UserIndex].BancoInvent.NroItems + 1;
	}

	/* 'Slot valido */
	if (Slot <= MAX_BANCOINVENTORY_SLOTS) {
		/* 'Mete el obj en el slot */
		if (UserList[UserIndex].BancoInvent.Object[Slot].Amount + Cantidad <= MAX_INVENTORY_OBJS) {

			/* 'Menor que MAX_INV_OBJS */
			UserList[UserIndex].BancoInvent.Object[Slot].ObjIndex = obji;
			UserList[UserIndex].BancoInvent.Object[Slot].Amount =
					UserList[UserIndex].BancoInvent.Object[Slot].Amount + Cantidad;

			QuitarUserInvItem(UserIndex, vb6::CByte(ObjIndex), Cantidad);
		} else {
			WriteConsoleMsg(UserIndex, "El banco no puede cargar tantos objetos.",
					FontTypeNames_FONTTYPE_INFO);
		}
	}
}

void SendUserBovedaTxt(int sendIndex, int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int j;

	WriteConsoleMsg(sendIndex, UserList[UserIndex].Name, FontTypeNames_FONTTYPE_INFO);
	WriteConsoleMsg(sendIndex, "Tiene " + vb6::CStr(UserList[UserIndex].BancoInvent.NroItems) + " objetos.",
			FontTypeNames_FONTTYPE_INFO);

	for (j = (1); j <= (MAX_BANCOINVENTORY_SLOTS); j++) {
		if (UserList[UserIndex].BancoInvent.Object[j].ObjIndex > 0) {
			WriteConsoleMsg(sendIndex,
					"Objeto " + vb6::CStr(j) + " " + ObjData[UserList[UserIndex].BancoInvent.Object[j].ObjIndex].Name
							+ " Cantidad:" + vb6::CStr(UserList[UserIndex].BancoInvent.Object[j].Amount),
					FontTypeNames_FONTTYPE_INFO);
		}
	}
}

void SendUserBovedaTxtFromChar(int sendIndex, std::string charName) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int j;
	std::string CharFile;
	std::string Tmp;
	int ObjInd;
	int ObjCant;

	CharFile = GetCharPath(charName);

	if (FileExist(CharFile, 0)) {
		WriteConsoleMsg(sendIndex, charName, FontTypeNames_FONTTYPE_INFO);
		WriteConsoleMsg(sendIndex,
				"Tiene " + GetVar(CharFile, "BancoInventory", "CantidadItems") + " objetos.",
				FontTypeNames_FONTTYPE_INFO);
		for (j = (1); j <= (MAX_BANCOINVENTORY_SLOTS); j++) {
			Tmp = GetVar(CharFile, "BancoInventory", "Obj" + vb6::CStr(j));
			ObjInd = vb6::CInt(ReadField(1, Tmp, vb6::Asc("-")));
			ObjCant = vb6::CInt(ReadField(2, Tmp, vb6::Asc("-")));
			if (ObjInd > 0) {
				WriteConsoleMsg(sendIndex,
						"Objeto " + vb6::CStr(j) + " " + ObjData[ObjInd].Name + " Cantidad:" + vb6::CStr(ObjCant),
						FontTypeNames_FONTTYPE_INFO);
			}
		}
	} else {
		WriteConsoleMsg(sendIndex, "Usuario inexistente: " + charName, FontTypeNames_FONTTYPE_INFO);
	}
}
