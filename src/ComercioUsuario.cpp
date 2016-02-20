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

#include "ComercioUsuario.h"

/* '[Alejo] */

const int MAX_OFFER_SLOTS = 20;
const int GOLD_OFFER_SLOT = /* FANCY EXPRESSION */MAX_OFFER_SLOTS + 1;

/* 'origen: origen de la transaccion, originador del comando */
/* 'destino: receptor de la transaccion */
void IniciarComercioConUsuario(int Origen, int Destino) {
	/* '*************************************************** */
	/* 'Autor: Unkown */
	/* 'Last Modification: 25/11/2009 */
	/* ' */
	/* '*************************************************** */

	/* 'Si ambos pusieron /comerciar entonces */
	if (UserList[Origen].ComUsu.DestUsu == Destino && UserList[Destino].ComUsu.DestUsu == Origen) {

		if (UserList[Origen].flags.Comerciando || UserList[Destino].flags.Comerciando) {
			WriteConsoleMsg(Origen, "No puedes comerciar en este momento", FontTypeNames_FONTTYPE_TALK);
			WriteConsoleMsg(Destino, "No puedes comerciar en este momento", FontTypeNames_FONTTYPE_TALK);
			return;
		}

		/* 'Actualiza el inventario del usuario */
		UpdateUserInv(true, Origen, 0);
		/* 'Decirle al origen que abra la ventanita. */
		WriteUserCommerceInit(Origen);
		UserList[Origen].flags.Comerciando = true;

		/* 'Actualiza el inventario del usuario */
		UpdateUserInv(true, Destino, 0);
		/* 'Decirle al origen que abra la ventanita. */
		WriteUserCommerceInit(Destino);
		UserList[Destino].flags.Comerciando = true;

		/* 'Call EnviarObjetoTransaccion(Origen) */
	} else {
		/* 'Es el primero que comercia ? */
		WriteConsoleMsg(Destino,
				UserList[Origen].Name + " desea comerciar. Si deseas aceptar, escribe /COMERCIAR.",
				FontTypeNames_FONTTYPE_TALK);
		UserList[Destino].flags.TargetUser = Origen;

	}

	FlushBuffer(Destino);
}

void EnviarOferta(int UserIndex, int OfferSlot) {
	/* '*************************************************** */
	/* 'Autor: Unkown */
	/* 'Last Modification: 25/11/2009 */
	/* 'Sends the offer change to the other trading user */
	/* '25/11/2009: ZaMa - Implementado nuevo sistema de comercio con ofertas variables. */
	/* '*************************************************** */
	int ObjIndex;
	int ObjAmount;
	int OtherUserIndex;

	OtherUserIndex = UserList[UserIndex].ComUsu.DestUsu;

	if (OfferSlot == GOLD_OFFER_SLOT) {
		ObjIndex = iORO;
		ObjAmount = UserList[OtherUserIndex].ComUsu.GoldAmount;
	} else {
		ObjIndex = UserList[OtherUserIndex].ComUsu.Objeto[OfferSlot];
		ObjAmount = UserList[OtherUserIndex].ComUsu.cant[OfferSlot];
	}

	WriteChangeUserTradeSlot(UserIndex, OfferSlot, ObjIndex, ObjAmount);
	FlushBuffer(UserIndex);
}

void FinComerciarUsu(int UserIndex) {
	/* '*************************************************** */
	/* 'Autor: Unkown */
	/* 'Last Modification: 25/11/2009 */
	/* '25/11/2009: ZaMa - Limpio los arrays (por el nuevo sistema) */
	/* '*************************************************** */
	int i;

	if (UserList[UserIndex].ComUsu.DestUsu > 0 && UserList[UserIndex].ComUsu.DestUsu < MaxUsers) {
		WriteUserCommerceEnd(UserIndex);
	}

	UserList[UserIndex].ComUsu.Acepto = false;
	UserList[UserIndex].ComUsu.Confirmo = false;
	UserList[UserIndex].ComUsu.DestUsu = 0;

	for (i = (1); i <= (MAX_OFFER_SLOTS); i++) {
		UserList[UserIndex].ComUsu.cant[i] = 0;
		UserList[UserIndex].ComUsu.Objeto[i] = 0;
	}

	UserList[UserIndex].ComUsu.GoldAmount = 0;
	UserList[UserIndex].ComUsu.DestNick = "";
	UserList[UserIndex].flags.Comerciando = false;
}

void AceptarComercioUsu(int UserIndex) {
	/* '*************************************************** */
	/* 'Autor: Unkown */
	/* 'Last Modification: 06/05/2010 */
	/* '25/11/2009: ZaMa - Ahora se traspasan hasta 5 items + oro al comerciar */
	/* '06/05/2010: ZaMa - Ahora valida si los usuarios tienen los items que ofertan. */
	/* '*************************************************** */
	struct Obj TradingObj;
	int OtroUserIndex;
	int OfferSlot;

	UserList[UserIndex].ComUsu.Acepto = true;

	OtroUserIndex = UserList[UserIndex].ComUsu.DestUsu;

	/* ' User valido? */
	if (OtroUserIndex <= 0 || OtroUserIndex > MaxUsers) {
		FinComerciarUsu(UserIndex);
		return;
	}

	/* ' Acepto el otro? */
	if (UserList[OtroUserIndex].ComUsu.Acepto == false) {
		return;
	}

	/* ' Aceptaron ambos, chequeo que tengan los items que ofertaron */
	if (!HasOfferedItems(UserIndex)) {

		WriteConsoleMsg(UserIndex, "¡¡¡El comercio se canceló porque no posees los ítems que ofertaste!!!",
				FontTypeNames_FONTTYPE_FIGHT);
		WriteConsoleMsg(OtroUserIndex,
				"¡¡¡El comercio se canceló porque " + UserList[UserIndex].Name
						+ " no posee los ítems que ofertó!!!", FontTypeNames_FONTTYPE_FIGHT);

		FinComerciarUsu(UserIndex);
		FinComerciarUsu(OtroUserIndex);
		FlushBuffer(OtroUserIndex);

		return;

	} else if (!HasOfferedItems(OtroUserIndex)) {

		WriteConsoleMsg(UserIndex,
				"¡¡¡El comercio se canceló porque " + UserList[OtroUserIndex].Name
						+ " no posee los ítems que ofertó!!!", FontTypeNames_FONTTYPE_FIGHT);
		WriteConsoleMsg(OtroUserIndex,
				"¡¡¡El comercio se canceló porque no posees los ítems que ofertaste!!!",
				FontTypeNames_FONTTYPE_FIGHT);

		FinComerciarUsu(UserIndex);
		FinComerciarUsu(OtroUserIndex);
		FlushBuffer(OtroUserIndex);

		return;

	}

	/* ' Envio los items a quien corresponde */
	for (OfferSlot = (1); OfferSlot <= (MAX_OFFER_SLOTS + 1); OfferSlot++) {

		/* ' Items del 1er usuario */
		/* ' Le pasa el oro */
		if (OfferSlot == GOLD_OFFER_SLOT) {
			/* ' Quito la cantidad de oro ofrecida */
			UserList[UserIndex].Stats.GLD = UserList[UserIndex].Stats.GLD
					- UserList[UserIndex].ComUsu.GoldAmount;
			/* ' Log */
			if (UserList[UserIndex].ComUsu.GoldAmount >= MIN_GOLD_AMOUNT_LOG) {
				LogDesarrollo(
						UserList[UserIndex].Name + " soltó oro en comercio seguro con "
								+ UserList[OtroUserIndex].Name + ". Cantidad: "
								+ vb6::CStr(UserList[UserIndex].ComUsu.GoldAmount));
			}
			/* ' Update Usuario */
			WriteUpdateGold(UserIndex);
			/* ' Se la doy al otro */
			UserList[OtroUserIndex].Stats.GLD = UserList[OtroUserIndex].Stats.GLD
					+ UserList[UserIndex].ComUsu.GoldAmount;
			/* ' Update Otro Usuario */
			WriteUpdateGold(OtroUserIndex);

			/* ' Le pasa lo ofertado de los slots con items */
		} else if (UserList[UserIndex].ComUsu.Objeto[OfferSlot] > 0) {
			TradingObj.ObjIndex = UserList[UserIndex].ComUsu.Objeto[OfferSlot];
			TradingObj.Amount = UserList[UserIndex].ComUsu.cant[OfferSlot];

			/* 'Quita el objeto y se lo da al otro */
			if (!MeterItemEnInventario(OtroUserIndex, TradingObj)) {
				TirarItemAlPiso(UserList[OtroUserIndex].Pos, TradingObj);
			}

			QuitarObjetos(TradingObj.ObjIndex, TradingObj.Amount, UserIndex);

			/* 'Es un Objeto que tenemos que loguear? Pablo (ToxicWaste) 07/09/07 */
			if (((ObjData[TradingObj.ObjIndex].Log == 1)
					|| (ObjData[TradingObj.ObjIndex].OBJType == eOBJType_otLlaves))) {
				LogDesarrollo(
						UserList[UserIndex].Name + " le pasó en comercio seguro a "
								+ UserList[OtroUserIndex].Name + " " + vb6::CStr(TradingObj.Amount) + " "
								+ ObjData[TradingObj.ObjIndex].Name);
				/* 'Es mucha cantidad? */
			} else if (TradingObj.Amount >= MIN_AMOUNT_LOG) {
				/* 'Si no es de los prohibidos de loguear, lo logueamos. */
				if (ObjData[TradingObj.ObjIndex].NoLog != 1) {
					LogDesarrollo(
							UserList[UserIndex].Name + " le pasó en comercio seguro a "
									+ UserList[OtroUserIndex].Name + " " + vb6::CStr(TradingObj.Amount) + " "
									+ ObjData[TradingObj.ObjIndex].Name);
				}
			} else if ((TradingObj.Amount * ObjData[TradingObj.ObjIndex].Valor) >= MIN_VALUE_LOG) {
				/* 'Si no es de los prohibidos de loguear, lo logueamos. */
				if (ObjData[TradingObj.ObjIndex].NoLog != 1) {
					LogDesarrollo(
							UserList[UserIndex].Name + " le pasó en comercio seguro a "
									+ UserList[OtroUserIndex].Name + " " + vb6::CStr(TradingObj.Amount) + " "
									+ ObjData[TradingObj.ObjIndex].Name);
				}
			}
		}

		/* ' Items del 2do usuario */
		/* ' Le pasa el oro */
		if (OfferSlot == GOLD_OFFER_SLOT) {
			/* ' Quito la cantidad de oro ofrecida */
			UserList[OtroUserIndex].Stats.GLD = UserList[OtroUserIndex].Stats.GLD
					- UserList[OtroUserIndex].ComUsu.GoldAmount;
			/* ' Log */
			if (UserList[OtroUserIndex].ComUsu.GoldAmount >= MIN_GOLD_AMOUNT_LOG) {
				LogDesarrollo(
						UserList[OtroUserIndex].Name + " soltó oro en comercio seguro con "
								+ UserList[UserIndex].Name + ". Cantidad: "
								+ vb6::CStr(UserList[OtroUserIndex].ComUsu.GoldAmount));
			}
			/* ' Update Usuario */
			WriteUpdateGold(OtroUserIndex);
			/* 'y se la doy al otro */
			UserList[UserIndex].Stats.GLD = UserList[UserIndex].Stats.GLD
					+ UserList[OtroUserIndex].ComUsu.GoldAmount;

			/* ' Update Otro Usuario */
			WriteUpdateGold(UserIndex);

			/* ' Le pasa la oferta de los slots con items */
		} else if (UserList[OtroUserIndex].ComUsu.Objeto[OfferSlot] > 0) {
			TradingObj.ObjIndex = UserList[OtroUserIndex].ComUsu.Objeto[OfferSlot];
			TradingObj.Amount = UserList[OtroUserIndex].ComUsu.cant[OfferSlot];

			/* 'Quita el objeto y se lo da al otro */
			if (!MeterItemEnInventario(UserIndex, TradingObj)) {
				TirarItemAlPiso(UserList[UserIndex].Pos, TradingObj);
			}

			QuitarObjetos(TradingObj.ObjIndex, TradingObj.Amount, OtroUserIndex);

			/* 'Es un Objeto que tenemos que loguear? Pablo (ToxicWaste) 07/09/07 */
			if (((ObjData[TradingObj.ObjIndex].Log == 1)
					|| (ObjData[TradingObj.ObjIndex].OBJType == eOBJType_otLlaves))) {
				LogDesarrollo(
						UserList[OtroUserIndex].Name + " le pasó en comercio seguro a "
								+ UserList[UserIndex].Name + " " + vb6::CStr(TradingObj.Amount) + " "
								+ ObjData[TradingObj.ObjIndex].Name);
				/* 'Es mucha cantidad? */
			} else if (TradingObj.Amount >= MIN_AMOUNT_LOG) {
				/* 'Si no es de los prohibidos de loguear, lo logueamos. */
				if (ObjData[TradingObj.ObjIndex].NoLog != 1) {
					LogDesarrollo(
							UserList[OtroUserIndex].Name + " le pasó en comercio seguro a "
									+ UserList[UserIndex].Name + " " + vb6::CStr(TradingObj.Amount) + " "
									+ ObjData[TradingObj.ObjIndex].Name);
				}
			} else if ((TradingObj.Amount * ObjData[TradingObj.ObjIndex].Valor) >= MIN_VALUE_LOG) {
				/* 'Si no es de los prohibidos de loguear, lo logueamos. */
				if (ObjData[TradingObj.ObjIndex].NoLog != 1) {
					LogDesarrollo(
							UserList[OtroUserIndex].Name + " le pasó en comercio seguro a "
									+ UserList[UserIndex].Name + " " + vb6::CStr(TradingObj.Amount) + " "
									+ ObjData[TradingObj.ObjIndex].Name);
				}
			}
		}

	}

	/* ' End Trade */
	FinComerciarUsu(UserIndex);
	FinComerciarUsu(OtroUserIndex);
	FlushBuffer(OtroUserIndex);

}

void AgregarOferta(int UserIndex, int OfferSlot, int ObjIndex, int Amount, bool IsGold) {
	/* '*************************************************** */
	/* 'Autor: ZaMa */
	/* 'Last Modification: 24/11/2009 */
	/* 'Adds gold or items to the user's offer */
	/* '*************************************************** */

	/* ' Si ya confirmo su oferta, no puede cambiarla! */
	if (!UserList[UserIndex].ComUsu.Confirmo) {
		if (IsGold) {
			/* ' Agregamos (o quitamos) mas oro a la oferta */
			UserList[UserIndex].ComUsu.GoldAmount = UserList[UserIndex].ComUsu.GoldAmount + Amount;

			/* ' Imposible que pase, pero por las dudas.. */
			if (UserList[UserIndex].ComUsu.GoldAmount < 0) {
				UserList[UserIndex].ComUsu.GoldAmount = 0;
			}
		} else {
			/* ' Agreamos (o quitamos) el item y su cantidad en el slot correspondiente */
			/* ' Si es 0 estoy modificando la cantidad, no agregando */
			if (ObjIndex > 0) {
				UserList[UserIndex].ComUsu.Objeto[OfferSlot] = ObjIndex;
			}
			UserList[UserIndex].ComUsu.cant[OfferSlot] = UserList[UserIndex].ComUsu.cant[OfferSlot] + Amount;

			/* 'Quitó todos los items de ese tipo */
			if (UserList[UserIndex].ComUsu.cant[OfferSlot] <= 0) {
				/* ' Removemos el objeto para evitar conflictos */
				UserList[UserIndex].ComUsu.Objeto[OfferSlot] = 0;
				UserList[UserIndex].ComUsu.cant[OfferSlot] = 0;
			}
		}
	}
}

bool PuedeSeguirComerciando(int UserIndex) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Autor: ZaMa */
	/* 'Last Modification: 24/11/2009 */
	/* 'Validates wether the conditions for the commerce to keep going are satisfied */
	/* '*************************************************** */
	int OtroUserIndex;
	bool ComercioInvalido = false;

	OtroUserIndex = UserList[UserIndex].ComUsu.DestUsu;

	/* ' Usuario valido? */
	if (OtroUserIndex <= 0 || OtroUserIndex > MaxUsers) {
		ComercioInvalido = true;
	}

	if (!ComercioInvalido) {
		/* ' Estan logueados? */
		if (UserList[OtroUserIndex].flags.UserLogged == false
				|| UserList[UserIndex].flags.UserLogged == false) {
			ComercioInvalido = true;
		}
	}

	if (!ComercioInvalido) {
		/* ' Se estan comerciando el uno al otro? */
		if (UserList[OtroUserIndex].ComUsu.DestUsu != UserIndex) {
			ComercioInvalido = true;
		}
	}

	if (!ComercioInvalido) {
		/* ' El nombre del otro es el mismo que al que le comercio? */
		if (UserList[OtroUserIndex].Name != UserList[UserIndex].ComUsu.DestNick) {
			ComercioInvalido = true;
		}
	}

	if (!ComercioInvalido) {
		/* ' Mi nombre  es el mismo que al que el le comercia? */
		if (UserList[UserIndex].Name != UserList[OtroUserIndex].ComUsu.DestNick) {
			ComercioInvalido = true;
		}
	}

	if (!ComercioInvalido) {
		/* ' Esta vivo? */
		if (UserList[OtroUserIndex].flags.Muerto == 1) {
			ComercioInvalido = true;
		}
	}

	/* ' Fin del comercio */
	if (ComercioInvalido == true) {
		FinComerciarUsu(UserIndex);

		if (OtroUserIndex > 0 && OtroUserIndex <= MaxUsers) {
			FinComerciarUsu(OtroUserIndex);
			FlushBuffer(OtroUserIndex);
		}

		return retval;
	}

	retval = true;

	return retval;
}

bool HasOfferedItems(int UserIndex) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Autor: ZaMa */
	/* 'Last Modification: 05/06/2010 */
	/* 'Checks whether the user has the offered items in his inventory or not. */
	/* '*************************************************** */

	std::vector<struct tOfferItem> OfferedItems;
	int Slot;
	int SlotAux;
	int SlotCount = 0;
	int ObjIndex;

	OfferedItems.resize(MAX_OFFER_SLOTS);

	/* ' Agrupo los items que son iguales */
	for (Slot = (1); Slot <= (MAX_OFFER_SLOTS); Slot++) {

		ObjIndex = UserList[UserIndex].ComUsu.Objeto[Slot];

		if (ObjIndex > 0) {

			for (SlotAux = (0); SlotAux <= (SlotCount - 1); SlotAux++) {

				if (ObjIndex == OfferedItems[SlotAux].ObjIndex) {
					/* ' Son iguales, aumento la cantidad */
					OfferedItems[SlotAux].Amount = OfferedItems[SlotAux].Amount
							+ UserList[UserIndex].ComUsu.cant[Slot];
					break;
				}

			}

			/* ' No encontro otro igual, lo agrego */
			if (SlotAux == SlotCount) {
				OfferedItems[SlotCount].ObjIndex = ObjIndex;
				OfferedItems[SlotCount].Amount = UserList[UserIndex].ComUsu.cant[Slot];

				SlotCount = SlotCount + 1;
			}

		}

	}

	/* ' Chequeo que tengan la cantidad en el inventario */
	for (Slot = (0); Slot <= (SlotCount - 1); Slot++) {
		if (!HasEnoughItems(UserIndex, OfferedItems[Slot].ObjIndex, OfferedItems[Slot].Amount)) {
			return retval;
		}
	}

	/* ' Compruebo que tenga el oro que oferta */
	if (UserList[UserIndex].Stats.GLD < UserList[UserIndex].ComUsu.GoldAmount) {
		return retval;
	}

	retval = true;

	return retval;
}
