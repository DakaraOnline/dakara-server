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

#include "Trabajo.h"

static const int GASTO_ENERGIA_TRABAJADOR = 2;
static const int GASTO_ENERGIA_NO_TRABAJADOR = 6;

void DoPermanecerOculto(int UserIndex) {
	/* '******************************************************** */
	/* 'Autor: Nacho (Integer) */
	/* 'Last Modif: 11/19/2009 */
	/* 'Chequea si ya debe mostrarse */
	/* 'Pablo (ToxicWaste): Cambie los ordenes de prioridades porque sino no andaba. */
	/* '13/01/2010: ZaMa - Now hidden on boat pirats recover the proper boat body. */
	/* '13/01/2010: ZaMa - Arreglo condicional para que el bandido camine oculto. */
	/* '******************************************************** */
	UserList[UserIndex].Counters.TiempoOculto = UserList[UserIndex].Counters.TiempoOculto - 1;
	if (UserList[UserIndex].Counters.TiempoOculto <= 0) {
		if (UserList[UserIndex].clase == eClass_Hunter
				&& UserList[UserIndex].Stats.UserSkills[eSkill_Ocultarse] > 90) {
			if (UserList[UserIndex].Invent.ArmourEqpObjIndex == 648
					|| UserList[UserIndex].Invent.ArmourEqpObjIndex == 360) {
				UserList[UserIndex].Counters.TiempoOculto = IntervaloOculto;
				return;
			}
		}
		UserList[UserIndex].Counters.TiempoOculto = 0;
		UserList[UserIndex].flags.Oculto = 0;

		if (UserList[UserIndex].flags.Navegando == 1) {
			if (UserList[UserIndex].clase == eClass_Pirat) {
				/* ' Pierde la apariencia de fragata fantasmal */
				ToggleBoatBody(UserIndex);
				WriteConsoleMsg(UserIndex, "¡Has recuperado tu apariencia normal!",
						FontTypeNames_FONTTYPE_INFO);
				ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
						UserList[UserIndex].Char.heading, NingunArma, NingunEscudo, NingunCasco);
			}
		} else {
			if (UserList[UserIndex].flags.invisible == 0) {
				WriteConsoleMsg(UserIndex, "Has vuelto a ser visible.", FontTypeNames_FONTTYPE_INFO);
				SetInvisible(UserIndex, UserList[UserIndex].Char.CharIndex, false);
			}
		}
	}
}

void DoOcultarse(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 13/01/2010 (ZaMa) */
	/* 'Pablo (ToxicWaste): No olvidar agregar IntervaloOculto=500 al Server.ini. */
	/* 'Modifique la fórmula y ahora anda bien. */
	/* '13/01/2010: ZaMa - El pirata se transforma en galeon fantasmal cuando se oculta en agua. */
	/* '*************************************************** */

	double Suerte;
	int res;
	int Skill;

	Skill = UserList[UserIndex].Stats.UserSkills[eSkill_Ocultarse];

	Suerte = (((0.000002 * Skill - 0.0002) * Skill + 0.0064) * Skill + 0.1124) * 100;

	res = RandomNumber(1, 100);

	if (res <= Suerte) {

		UserList[UserIndex].flags.Oculto = 1;
		Suerte = std::pow(-0.000001 * (100 - Skill), 3);
		Suerte = Suerte + std::pow(0.00009229 * (100 - Skill), 2);
		Suerte = Suerte + (-0.0088 * (100 - Skill));
		Suerte = Suerte + (0.9571);
		Suerte = Suerte * IntervaloOculto;

		if (UserList[UserIndex].clase == eClass_Bandit) {
			UserList[UserIndex].Counters.TiempoOculto = vb6::Int(Suerte / 2);
		} else {
			UserList[UserIndex].Counters.TiempoOculto = Suerte;
		}

		/* ' No es pirata o es uno sin barca */
		if (UserList[UserIndex].flags.Navegando == 0) {
			SetInvisible(UserIndex, UserList[UserIndex].Char.CharIndex, true);

			WriteConsoleMsg(UserIndex, "¡Te has escondido entre las sombras!", FontTypeNames_FONTTYPE_INFO);
			/* ' Es un pirata navegando */
		} else {
			/* ' Le cambiamos el body a galeon fantasmal */
			UserList[UserIndex].Char.body = iFragataFantasmal;
			/* ' Actualizamos clientes */
			ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
					UserList[UserIndex].Char.heading, NingunArma, NingunEscudo, NingunCasco);
		}

		SubirSkill(UserIndex, eSkill_Ocultarse, true);
	} else {
		/* '[CDT 17-02-2004] */
		if (UserList[UserIndex].flags.UltimoMensaje != 4) {
			WriteConsoleMsg(UserIndex, "¡No has logrado esconderte!", FontTypeNames_FONTTYPE_INFO);
			UserList[UserIndex].flags.UltimoMensaje = 4;
		}
		/* '[/CDT] */

		SubirSkill(UserIndex, eSkill_Ocultarse, false);
	}

	UserList[UserIndex].Counters.Ocultando = UserList[UserIndex].Counters.Ocultando + 1;
}

void DoNavega(int UserIndex, struct ObjData & Barco, int Slot) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 13/01/2010 (ZaMa) */
	/* '13/01/2010: ZaMa - El pirata pierde el ocultar si desequipa barca. */
	/* '16/09/2010: ZaMa - Ahora siempre se va el invi para los clientes al equipar la barca (Evita cortes de cabeza). */
	/* '10/12/2010: Pato - Limpio las variables del inventario que hacen referencia a la barca, sino el pirata que la última barca que equipo era el galeón no explotaba(Y capaz no la tenía equipada :P). */
	/* '*************************************************** */

	float ModNave;
	int minSkillBarco;

	ModNave = ModNavegacion(UserList[UserIndex].clase, UserIndex);
	minSkillBarco = ModNave * Barco.MinSkill;

	if (UserList[UserIndex].Stats.UserSkills[eSkill_Navegacion] < minSkillBarco) {
		WriteConsoleMsg(UserIndex, "No tienes suficientes conocimientos para usar este barco.",
				FontTypeNames_FONTTYPE_INFO);
		WriteConsoleMsg(UserIndex,
				"Para usar este barco necesitas " + vb6::CStr(minSkillBarco) + " puntos en navegacion.",
				FontTypeNames_FONTTYPE_INFO);
		return;
	}

	/* ' No estaba navegando */
	if (UserList[UserIndex].flags.Navegando == 0) {
		UserList[UserIndex].Invent.BarcoObjIndex = UserList[UserIndex].Invent.Object[Slot].ObjIndex;
		UserList[UserIndex].Invent.BarcoSlot = Slot;

		UserList[UserIndex].Char.Head = 0;

		/* ' No esta muerto */
		if (UserList[UserIndex].flags.Muerto == 0) {

			ToggleBoatBody(UserIndex);

			/* ' Pierde el ocultar */
			if (UserList[UserIndex].flags.Oculto == 1) {
				UserList[UserIndex].flags.Oculto = 0;
				SetInvisible(UserIndex, UserList[UserIndex].Char.CharIndex, false);
				WriteConsoleMsg(UserIndex, "¡Has vuelto a ser visible!", FontTypeNames_FONTTYPE_INFO);
			}

			/* ' Siempre se ve la barca (Nunca esta invisible), pero solo para el cliente. */
			if (UserList[UserIndex].flags.invisible == 1) {
				SetInvisible(UserIndex, UserList[UserIndex].Char.CharIndex, false);
			}

			/* ' Esta muerto */
		} else {
			UserList[UserIndex].Char.body = iFragataFantasmal;
			UserList[UserIndex].Char.ShieldAnim = NingunEscudo;
			UserList[UserIndex].Char.WeaponAnim = NingunArma;
			UserList[UserIndex].Char.CascoAnim = NingunCasco;
		}

		/* ' Comienza a navegar */
		UserList[UserIndex].flags.Navegando = 1;

		/* ' Estaba navegando */
	} else {
		UserList[UserIndex].Invent.BarcoObjIndex = 0;
		UserList[UserIndex].Invent.BarcoSlot = 0;

		/* ' No esta muerto */
		if (UserList[UserIndex].flags.Muerto == 0) {
			UserList[UserIndex].Char.Head = UserList[UserIndex].OrigChar.Head;

			if (UserList[UserIndex].clase == eClass_Pirat) {
				if (UserList[UserIndex].flags.Oculto == 1) {
					/* ' Al desequipar barca, perdió el ocultar */
					UserList[UserIndex].flags.Oculto = 0;
					UserList[UserIndex].Counters.Ocultando = 0;
					WriteConsoleMsg(UserIndex, "¡Has recuperado tu apariencia normal!",
							FontTypeNames_FONTTYPE_INFO);
				}
			}

			if (UserList[UserIndex].Invent.ArmourEqpObjIndex > 0) {
				UserList[UserIndex].Char.body = ObjData[UserList[UserIndex].Invent.ArmourEqpObjIndex].Ropaje;
			} else {
				DarCuerpoDesnudo(UserIndex);
			}

			if (UserList[UserIndex].Invent.EscudoEqpObjIndex > 0) {
				UserList[UserIndex].Char.ShieldAnim =
						ObjData[UserList[UserIndex].Invent.EscudoEqpObjIndex].ShieldAnim;
			}
			if (UserList[UserIndex].Invent.WeaponEqpObjIndex > 0) {
				UserList[UserIndex].Char.WeaponAnim = GetWeaponAnim(UserIndex,
						UserList[UserIndex].Invent.WeaponEqpObjIndex);
			}
			if (UserList[UserIndex].Invent.CascoEqpObjIndex > 0) {
				UserList[UserIndex].Char.CascoAnim =
						ObjData[UserList[UserIndex].Invent.CascoEqpObjIndex].CascoAnim;
			}

			/* ' Al dejar de navegar, si estaba invisible actualizo los clientes */
			if (UserList[UserIndex].flags.invisible == 1) {
				SetInvisible(UserIndex, UserList[UserIndex].Char.CharIndex, true);
			}

			/* ' Esta muerto */
		} else {
			UserList[UserIndex].Char.body = iCuerpoMuerto;
			UserList[UserIndex].Char.Head = iCabezaMuerto;
			UserList[UserIndex].Char.ShieldAnim = NingunEscudo;
			UserList[UserIndex].Char.WeaponAnim = NingunArma;
			UserList[UserIndex].Char.CascoAnim = NingunCasco;
		}

		/* ' Termina de navegar */
		UserList[UserIndex].flags.Navegando = 0;
	}

	/* ' Actualizo clientes */
	ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
			UserList[UserIndex].Char.heading, UserList[UserIndex].Char.WeaponAnim,
			UserList[UserIndex].Char.ShieldAnim, UserList[UserIndex].Char.CascoAnim);

	WriteNavigateToggle(UserIndex);

}

void FundirMineral(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (UserList[UserIndex].flags.TargetObjInvIndex > 0) {

		if (ObjData[UserList[UserIndex].flags.TargetObjInvIndex].OBJType == eOBJType_otMinerales
				&& ObjData[UserList[UserIndex].flags.TargetObjInvIndex].MinSkill
						<= UserList[UserIndex].Stats.UserSkills[eSkill_Mineria]
								/ ModFundicion(UserList[UserIndex].clase)) {
			DoLingotes(UserIndex);
		} else {
			WriteConsoleMsg(UserIndex,
					"No tienes conocimientos de minería suficientes para trabajar este mineral.",
					FontTypeNames_FONTTYPE_INFO);
		}

	}
}

void FundirArmas(int UserIndex) {
	if (UserList[UserIndex].flags.TargetObjInvIndex > 0) {
		if (ObjData[UserList[UserIndex].flags.TargetObjInvIndex].OBJType == eOBJType_otWeapon) {
			if (ObjData[UserList[UserIndex].flags.TargetObjInvIndex].SkHerreria
					<= UserList[UserIndex].Stats.UserSkills[eSkill_Herreria]
							/ ModHerreriA(UserList[UserIndex].clase)) {
				DoFundir(UserIndex);
			} else {
				WriteConsoleMsg(UserIndex,
						"No tienes los conocimientos suficientes en herrería para fundir este objeto.",
						FontTypeNames_FONTTYPE_INFO);
			}
		}
	}
}

bool TieneObjetos(int ItemIndex, int cant, int UserIndex) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 10/07/2010 */
	/* '10/07/2010: ZaMa - Ahora cant es long para evitar un overflow. */
	/* '*************************************************** */

	int i;
	int Total = 0;
	for (i = (1); i <= (UserList[UserIndex].CurrentInventorySlots); i++) {
		if (UserList[UserIndex].Invent.Object[i].ObjIndex == ItemIndex) {
			Total = Total + UserList[UserIndex].Invent.Object[i].Amount;
		}
	}

	if (cant <= Total) {
		retval = true;
		return retval;
	}

	return retval;
}

void QuitarObjetos(int ItemIndex, int cant, int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 05/08/09 */
	/* '05/08/09: Pato - Cambie la funcion a procedimiento ya que se usa como procedimiento siempre, y fixie el bug 2788199 */
	/* '*************************************************** */

	int i;
	for (i = (1); i <= (UserList[UserIndex].CurrentInventorySlots); i++) {
		if (UserList[UserIndex].Invent.Object[i].ObjIndex == ItemIndex) {
			if (UserList[UserIndex].Invent.Object[i].Amount <= cant
					&& UserList[UserIndex].Invent.Object[i].Equipped == 1) {
				Desequipar(UserIndex, i, true);
			}

			UserList[UserIndex].Invent.Object[i].Amount = UserList[UserIndex].Invent.Object[i].Amount - cant;
			if (UserList[UserIndex].Invent.Object[i].Amount <= 0) {
				cant = vb6::Abs(UserList[UserIndex].Invent.Object[i].Amount);
				UserList[UserIndex].Invent.NroItems = UserList[UserIndex].Invent.NroItems - 1;
				UserList[UserIndex].Invent.Object[i].Amount = 0;
				UserList[UserIndex].Invent.Object[i].ObjIndex = 0;
			} else {
				cant = 0;
			}

			UpdateUserInv(false, UserIndex, i);

			if (cant == 0) {
				return;
			}
		}
	}

}

void HerreroQuitarMateriales(int UserIndex, int ItemIndex, int CantidadItems) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 16/11/2009 */
	/* '16/11/2009: ZaMa - Ahora considera la cantidad de items a construir */
	/* '*************************************************** */
	if (ObjData[ItemIndex].LingH > 0) {
		QuitarObjetos(LingoteHierro, ObjData[ItemIndex].LingH * CantidadItems, UserIndex);
	}
	if (ObjData[ItemIndex].LingP > 0) {
		QuitarObjetos(LingotePlata, ObjData[ItemIndex].LingP * CantidadItems, UserIndex);
	}
	if (ObjData[ItemIndex].LingO > 0) {
		QuitarObjetos(LingoteOro, ObjData[ItemIndex].LingO * CantidadItems, UserIndex);
	}
}

void CarpinteroQuitarMateriales(int UserIndex, int ItemIndex, int CantidadItems) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 16/11/2009 */
	/* '16/11/2009: ZaMa - Ahora quita tambien madera elfica */
	/* '*************************************************** */
	if (ObjData[ItemIndex].Madera > 0) {
		QuitarObjetos(Lena, ObjData[ItemIndex].Madera * CantidadItems, UserIndex);
	}
	if (ObjData[ItemIndex].MaderaElfica > 0) {
		QuitarObjetos(LenaElfica, ObjData[ItemIndex].MaderaElfica * CantidadItems, UserIndex);
	}
}

bool CarpinteroTieneMateriales(int UserIndex, int ItemIndex, int Cantidad, bool ShowMsg) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 16/11/2009 */
	/* '16/11/2009: ZaMa - Agregada validacion a madera elfica. */
	/* '16/11/2009: ZaMa - Ahora considera la cantidad de items a construir */
	/* '*************************************************** */

	if (ObjData[ItemIndex].Madera > 0) {
		if (!TieneObjetos(Lena, ObjData[ItemIndex].Madera * Cantidad, UserIndex)) {
			if (ShowMsg) {
				WriteConsoleMsg(UserIndex, "No tienes suficiente madera.", FontTypeNames_FONTTYPE_INFO);
			}
			retval = false;
			return retval;
		}
	}

	if (ObjData[ItemIndex].MaderaElfica > 0) {
		if (!TieneObjetos(LenaElfica, ObjData[ItemIndex].MaderaElfica * Cantidad, UserIndex)) {
			if (ShowMsg) {
				WriteConsoleMsg(UserIndex, "No tienes suficiente madera élfica.",
						FontTypeNames_FONTTYPE_INFO);
			}
			retval = false;
			return retval;
		}
	}

	retval = true;

	return retval;
}

bool HerreroTieneMateriales(int UserIndex, int ItemIndex, int CantidadItems) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 16/11/2009 */
	/* '16/11/2009: ZaMa - Agregada validacion a madera elfica. */
	/* '*************************************************** */
	if (ObjData[ItemIndex].LingH > 0) {
		if (!TieneObjetos(LingoteHierro, ObjData[ItemIndex].LingH * CantidadItems, UserIndex)) {
			WriteConsoleMsg(UserIndex, "No tienes suficientes lingotes de hierro.",
					FontTypeNames_FONTTYPE_INFO);
			retval = false;
			return retval;
		}
	}
	if (ObjData[ItemIndex].LingP > 0) {
		if (!TieneObjetos(LingotePlata, ObjData[ItemIndex].LingP * CantidadItems, UserIndex)) {
			WriteConsoleMsg(UserIndex, "No tienes suficientes lingotes de plata.",
					FontTypeNames_FONTTYPE_INFO);
			retval = false;
			return retval;
		}
	}
	if (ObjData[ItemIndex].LingO > 0) {
		if (!TieneObjetos(LingoteOro, ObjData[ItemIndex].LingO * CantidadItems, UserIndex)) {
			WriteConsoleMsg(UserIndex, "No tienes suficientes lingotes de oro.", FontTypeNames_FONTTYPE_INFO);
			retval = false;
			return retval;
		}
	}
	retval = true;
	return retval;
}

bool TieneMaterialesUpgrade(int UserIndex, int ItemIndex) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: Torres Patricio (Pato) */
	/* 'Last Modification: 12/08/2009 */
	/* ' */
	/* '*************************************************** */
	int ItemUpgrade;

	ItemUpgrade = ObjData[ItemIndex].Upgrade;

	if (ObjData[ItemUpgrade].LingH > 0) {
		if (!TieneObjetos(LingoteHierro,
				vb6::CInt(
						ObjData[ItemUpgrade].LingH
								- ObjData[ItemIndex].LingH * PORCENTAJE_MATERIALES_UPGRADE), UserIndex)) {
			WriteConsoleMsg(UserIndex, "No tienes suficientes lingotes de hierro.",
					FontTypeNames_FONTTYPE_INFO);
			retval = false;
			return retval;
		}
	}

	if (ObjData[ItemUpgrade].LingP > 0) {
		if (!TieneObjetos(LingotePlata,
				vb6::CInt(
						ObjData[ItemUpgrade].LingP
								- ObjData[ItemIndex].LingP * PORCENTAJE_MATERIALES_UPGRADE), UserIndex)) {
			WriteConsoleMsg(UserIndex, "No tienes suficientes lingotes de plata.",
					FontTypeNames_FONTTYPE_INFO);
			retval = false;
			return retval;
		}
	}

	if (ObjData[ItemUpgrade].LingO > 0) {
		if (!TieneObjetos(LingoteOro,
				vb6::CInt(
						ObjData[ItemUpgrade].LingO
								- ObjData[ItemIndex].LingO * PORCENTAJE_MATERIALES_UPGRADE), UserIndex)) {
			WriteConsoleMsg(UserIndex, "No tienes suficientes lingotes de oro.", FontTypeNames_FONTTYPE_INFO);
			retval = false;
			return retval;
		}
	}

	if (ObjData[ItemUpgrade].Madera > 0) {
		if (!TieneObjetos(Lena,
				vb6::CInt(
						ObjData[ItemUpgrade].Madera
								- ObjData[ItemIndex].Madera * PORCENTAJE_MATERIALES_UPGRADE), UserIndex)) {
			WriteConsoleMsg(UserIndex, "No tienes suficiente madera.", FontTypeNames_FONTTYPE_INFO);
			retval = false;
			return retval;
		}
	}

	if (ObjData[ItemUpgrade].MaderaElfica > 0) {
		if (!TieneObjetos(LenaElfica,
				vb6::CInt(
						ObjData[ItemUpgrade].MaderaElfica
								- ObjData[ItemIndex].MaderaElfica * PORCENTAJE_MATERIALES_UPGRADE),
				UserIndex)) {
			WriteConsoleMsg(UserIndex, "No tienes suficiente madera élfica.", FontTypeNames_FONTTYPE_INFO);
			retval = false;
			return retval;
		}
	}

	retval = true;
	return retval;
}

void QuitarMaterialesUpgrade(int UserIndex, int ItemIndex) {
	/* '*************************************************** */
	/* 'Author: Torres Patricio (Pato) */
	/* 'Last Modification: 12/08/2009 */
	/* ' */
	/* '*************************************************** */
	int ItemUpgrade;

	ItemUpgrade = ObjData[ItemIndex].Upgrade;

	if (ObjData[ItemUpgrade].LingH > 0) {
		QuitarObjetos(LingoteHierro,
				vb6::CInt(
						ObjData[ItemUpgrade].LingH
								- ObjData[ItemIndex].LingH * PORCENTAJE_MATERIALES_UPGRADE), UserIndex);
	}
	if (ObjData[ItemUpgrade].LingP > 0) {
		QuitarObjetos(LingotePlata,
				vb6::CInt(
						ObjData[ItemUpgrade].LingP
								- ObjData[ItemIndex].LingP * PORCENTAJE_MATERIALES_UPGRADE), UserIndex);
	}
	if (ObjData[ItemUpgrade].LingO > 0) {
		QuitarObjetos(LingoteOro,
				vb6::CInt(
						ObjData[ItemUpgrade].LingO
								- ObjData[ItemIndex].LingO * PORCENTAJE_MATERIALES_UPGRADE), UserIndex);
	}
	if (ObjData[ItemUpgrade].Madera > 0) {
		QuitarObjetos(Lena,
				vb6::CInt(
						ObjData[ItemUpgrade].Madera
								- ObjData[ItemIndex].Madera * PORCENTAJE_MATERIALES_UPGRADE), UserIndex);
	}
	if (ObjData[ItemUpgrade].MaderaElfica > 0) {
		QuitarObjetos(LenaElfica,
				vb6::CInt(
						ObjData[ItemUpgrade].MaderaElfica
								- ObjData[ItemIndex].MaderaElfica * PORCENTAJE_MATERIALES_UPGRADE),
				UserIndex);
	}

	QuitarObjetos(ItemIndex, 1, UserIndex);
}

bool PuedeConstruir(int UserIndex, int ItemIndex, int CantidadItems) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 24/08/2009 */
	/* '24/08/2008: ZaMa - Validates if the player has the required skill */
	/* '16/11/2009: ZaMa - Validates if the player has the required amount of materials, depending on the number of items to make */
	/* '*************************************************** */
	retval = HerreroTieneMateriales(UserIndex, ItemIndex, CantidadItems)
			&& vb6::Round(
					UserList[UserIndex].Stats.UserSkills[eSkill_Herreria]
							/ ModHerreriA(UserList[UserIndex].clase), 0) >= ObjData[ItemIndex].SkHerreria;
	return retval;
}

bool PuedeConstruirHerreria(int ItemIndex) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */
	int i;

	for (i = (1); i <= (vb6::UBound(ArmasHerrero)); i++) {
		if (ArmasHerrero[i] == ItemIndex) {
			retval = true;
			return retval;
		}
	}
	for (i = (1); i <= (vb6::UBound(ArmadurasHerrero)); i++) {
		if (ArmadurasHerrero[i] == ItemIndex) {
			retval = true;
			return retval;
		}
	}
	retval = false;
	return retval;
}

void HerreroConstruirItem(int UserIndex, int ItemIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 30/05/2010 */
	/* '16/11/2009: ZaMa - Implementado nuevo sistema de construccion de items. */
	/* '22/05/2010: ZaMa - Los caos ya no suben plebe al trabajar. */
	/* '30/05/2010: ZaMa - Los pks no suben plebe al trabajar. */
	/* '*************************************************** */
	int CantidadItems = 0;
	bool TieneMateriales = false;
	int OtroUserIndex = 0;

	if (UserList[UserIndex].flags.Comerciando) {
		OtroUserIndex = UserList[UserIndex].ComUsu.DestUsu;

		if (OtroUserIndex > 0 && OtroUserIndex <= MaxUsers) {
			WriteConsoleMsg(UserIndex, "¡¡Comercio cancelado, no puedes comerciar mientras trabajas!!",
					FontTypeNames_FONTTYPE_TALK);
			WriteConsoleMsg(OtroUserIndex, "¡¡Comercio cancelado por el otro usuario!!",
					FontTypeNames_FONTTYPE_TALK);

			LimpiarComercioSeguro(UserIndex);
			FlushBuffer(OtroUserIndex);
		}
	}

	CantidadItems = UserList[UserIndex].Construir.PorCiclo;

	if (UserList[UserIndex].Construir.Cantidad < CantidadItems) {
		CantidadItems = UserList[UserIndex].Construir.Cantidad;
	}

	if (UserList[UserIndex].Construir.Cantidad > 0) {
		UserList[UserIndex].Construir.Cantidad = UserList[UserIndex].Construir.Cantidad - CantidadItems;
	}

	if (CantidadItems == 0) {
		WriteStopWorking(UserIndex);
		return;
	}

	if (PuedeConstruirHerreria(ItemIndex)) {

		while (CantidadItems > 0 && !TieneMateriales) {
			if (PuedeConstruir(UserIndex, ItemIndex, CantidadItems)) {
				TieneMateriales = true;
			} else {
				CantidadItems = CantidadItems - 1;
			}
		}

		/* ' Chequeo si puede hacer al menos 1 item */
		if (!TieneMateriales) {
			WriteConsoleMsg(UserIndex, "No tienes suficientes materiales.", FontTypeNames_FONTTYPE_INFO);
			WriteStopWorking(UserIndex);
			return;
		}

		/* 'Sacamos energía */
		if (UserList[UserIndex].clase == eClass_Worker) {
			/* 'Chequeamos que tenga los puntos antes de sacarselos */
			if (UserList[UserIndex].Stats.MinSta >= GASTO_ENERGIA_TRABAJADOR) {
				UserList[UserIndex].Stats.MinSta = UserList[UserIndex].Stats.MinSta
						- GASTO_ENERGIA_TRABAJADOR;
				WriteUpdateSta(UserIndex);
			} else {
				WriteConsoleMsg(UserIndex, "No tienes suficiente energía.", FontTypeNames_FONTTYPE_INFO);
				return;
			}
		} else {
			/* 'Chequeamos que tenga los puntos antes de sacarselos */
			if (UserList[UserIndex].Stats.MinSta >= GASTO_ENERGIA_NO_TRABAJADOR) {
				UserList[UserIndex].Stats.MinSta = UserList[UserIndex].Stats.MinSta
						- GASTO_ENERGIA_NO_TRABAJADOR;
				WriteUpdateSta(UserIndex);
			} else {
				WriteConsoleMsg(UserIndex, "No tienes suficiente energía.", FontTypeNames_FONTTYPE_INFO);
				return;
			}
		}

		HerreroQuitarMateriales(UserIndex, ItemIndex, CantidadItems);
		/* ' AGREGAR FX */

		switch (ObjData[ItemIndex].OBJType) {

		case eOBJType_otWeapon:
			WriteConsoleMsg(UserIndex,
					vb6::CStr("Has construido ") + vb6::IIf(CantidadItems > 1, vb6::CStr(CantidadItems) + " armas!", vb6::CStr("el arma!")),
					FontTypeNames_FONTTYPE_INFO);
			break;

		case eOBJType_otESCUDO:
			WriteConsoleMsg(UserIndex,
					vb6::CStr("Has construido ")
							+ vb6::IIf(CantidadItems > 1, vb6::CStr(CantidadItems) + " escudos!", vb6::CStr("el escudo!")),
					FontTypeNames_FONTTYPE_INFO);
			break;

		case eOBJType_otCASCO:
			WriteConsoleMsg(UserIndex,
					vb6::CStr("Has construido ") + vb6::IIf(CantidadItems > 1, vb6::CStr(CantidadItems) + " cascos!", vb6::CStr("el casco!")),
					FontTypeNames_FONTTYPE_INFO);
			break;

		case eOBJType_otArmadura:
			WriteConsoleMsg(UserIndex,
					vb6::CStr("Has construido ")
							+ vb6::IIf(CantidadItems > 1, vb6::CStr(CantidadItems) + " armaduras", vb6::CStr("la armadura!")),
					FontTypeNames_FONTTYPE_INFO);

			break;

		default:
			break;
		}

		struct Obj MiObj;

		MiObj.Amount = CantidadItems;
		MiObj.ObjIndex = ItemIndex;
		if (!MeterItemEnInventario(UserIndex, MiObj)) {
			TirarItemAlPiso(UserList[UserIndex].Pos, MiObj);
		}

		/* 'Log de construcción de Items. Pablo (ToxicWaste) 10/09/07 */
		if (ObjData[MiObj.ObjIndex].Log == 1) {
			LogDesarrollo(
					vb6::CStr(UserList[UserIndex].Name) + " ha construído " + vb6::CStr(MiObj.Amount) + " "
							+ ObjData[MiObj.ObjIndex].Name);
		}

		SubirSkill(UserIndex, eSkill_Herreria, true);

		SendData(SendTarget_ToPCArea, UserIndex,
				dakara::protocol::server::BuildPlayWave(MARTILLOHERRERO, UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y));

		/*
		SendData(SendTarget_ToPCArea, UserIndex,
				PrepareMessagePlayWave(MARTILLOHERRERO, UserList[UserIndex].Pos.X,
						UserList[UserIndex].Pos.Y));
*/
		if (!criminal(UserIndex)) {
			UserList[UserIndex].Reputacion.PlebeRep = UserList[UserIndex].Reputacion.PlebeRep + vlProleta;
			if (UserList[UserIndex].Reputacion.PlebeRep > MAXREP) {
				UserList[UserIndex].Reputacion.PlebeRep = MAXREP;
			}
		}

		UserList[UserIndex].Counters.Trabajando = UserList[UserIndex].Counters.Trabajando + 1;
	}
}

bool PuedeConstruirCarpintero(int ItemIndex) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */
	int i;

	for (i = (1); i <= (vb6::UBound(ObjCarpintero)); i++) {
		if (ObjCarpintero[i] == ItemIndex) {
			retval = true;
			return retval;
		}
	}
	retval = false;

	return retval;
}

void CarpinteroConstruirItem(int UserIndex, int ItemIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 28/05/2010 */
	/* '24/08/2008: ZaMa - Validates if the player has the required skill */
	/* '16/11/2009: ZaMa - Implementado nuevo sistema de construccion de items */
	/* '22/05/2010: ZaMa - Los caos ya no suben plebe al trabajar. */
	/* '28/05/2010: ZaMa - Los pks no suben plebe al trabajar. */
	/* '*************************************************** */

	int CantidadItems = 0;
	bool TieneMateriales = false;
	int WeaponIndex = 0;
	int OtroUserIndex = 0;

	if (UserList[UserIndex].flags.Comerciando) {
		OtroUserIndex = UserList[UserIndex].ComUsu.DestUsu;

		if (OtroUserIndex > 0 && OtroUserIndex <= MaxUsers) {
			WriteConsoleMsg(UserIndex, "¡¡Comercio cancelado, no puedes comerciar mientras trabajas!!",
					FontTypeNames_FONTTYPE_TALK);
			WriteConsoleMsg(OtroUserIndex, "¡¡Comercio cancelado por el otro usuario!!",
					FontTypeNames_FONTTYPE_TALK);

			LimpiarComercioSeguro(UserIndex);
			FlushBuffer(OtroUserIndex);
		}
	}

	WeaponIndex = UserList[UserIndex].Invent.WeaponEqpObjIndex;

	if (WeaponIndex != SERRUCHO_CARPINTERO && WeaponIndex != SERRUCHO_CARPINTERO_NEWBIE) {
		WriteConsoleMsg(UserIndex, "Debes tener equipado el serrucho para trabajar.",
				FontTypeNames_FONTTYPE_INFO);
		WriteStopWorking(UserIndex);
		return;
	}

	CantidadItems = UserList[UserIndex].Construir.PorCiclo;

	if (UserList[UserIndex].Construir.Cantidad < CantidadItems) {
		CantidadItems = UserList[UserIndex].Construir.Cantidad;
	}

	if (UserList[UserIndex].Construir.Cantidad > 0) {
		UserList[UserIndex].Construir.Cantidad = UserList[UserIndex].Construir.Cantidad - CantidadItems;
	}

	if (CantidadItems == 0) {
		WriteStopWorking(UserIndex);
		return;
	}

	if (vb6::Round(
			UserList[UserIndex].Stats.UserSkills[eSkill_Carpinteria]
					/ ModCarpinteria(UserList[UserIndex].clase), 0) >= ObjData[ItemIndex].SkCarpinteria
			&& PuedeConstruirCarpintero(ItemIndex)) {

		/* ' Calculo cuantos item puede construir */
		while (CantidadItems > 0 && !TieneMateriales) {
			if (CarpinteroTieneMateriales(UserIndex, ItemIndex, CantidadItems)) {
				TieneMateriales = true;
			} else {
				CantidadItems = CantidadItems - 1;
			}
		}

		/* ' No tiene los materiales ni para construir 1 item? */
		if (!TieneMateriales) {
			/* ' Para que muestre el mensaje */
			CarpinteroTieneMateriales(UserIndex, ItemIndex, 1, true);
			WriteStopWorking(UserIndex);
			return;
		}

		/* 'Sacamos energía */
		if (UserList[UserIndex].clase == eClass_Worker) {
			/* 'Chequeamos que tenga los puntos antes de sacarselos */
			if (UserList[UserIndex].Stats.MinSta >= GASTO_ENERGIA_TRABAJADOR) {
				UserList[UserIndex].Stats.MinSta = UserList[UserIndex].Stats.MinSta
						- GASTO_ENERGIA_TRABAJADOR;
				WriteUpdateSta(UserIndex);
			} else {
				WriteConsoleMsg(UserIndex, "No tienes suficiente energía.", FontTypeNames_FONTTYPE_INFO);
				return;
			}
		} else {
			/* 'Chequeamos que tenga los puntos antes de sacarselos */
			if (UserList[UserIndex].Stats.MinSta >= GASTO_ENERGIA_NO_TRABAJADOR) {
				UserList[UserIndex].Stats.MinSta = UserList[UserIndex].Stats.MinSta
						- GASTO_ENERGIA_NO_TRABAJADOR;
				WriteUpdateSta(UserIndex);
			} else {
				WriteConsoleMsg(UserIndex, "No tienes suficiente energía.", FontTypeNames_FONTTYPE_INFO);
				return;
			}
		}

		CarpinteroQuitarMateriales(UserIndex, ItemIndex, CantidadItems);
		WriteConsoleMsg(UserIndex,
				vb6::CStr("Has construido ") + vb6::CStr(CantidadItems) + vb6::IIf(CantidadItems == 1, " objeto!", " objetos!"),
				FontTypeNames_FONTTYPE_INFO);

		struct Obj MiObj;
		MiObj.Amount = CantidadItems;
		MiObj.ObjIndex = ItemIndex;
		if (!MeterItemEnInventario(UserIndex, MiObj)) {
			TirarItemAlPiso(UserList[UserIndex].Pos, MiObj);
		}

		/* 'Log de construcción de Items. Pablo (ToxicWaste) 10/09/07 */
		if (ObjData[MiObj.ObjIndex].Log == 1) {
			LogDesarrollo(
					UserList[UserIndex].Name + " ha construído " + vb6::CStr(MiObj.Amount) + " "
							+ ObjData[MiObj.ObjIndex].Name);
		}

		SubirSkill(UserIndex, eSkill_Carpinteria, true);

		SendData(SendTarget_ToPCArea, UserIndex,
				dakara::protocol::server::BuildPlayWave(LABUROCARPINTERO, UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y));

		/*
		SendData(SendTarget_ToPCArea, UserIndex,
				PrepareMessagePlayWave(LABUROCARPINTERO, UserList[UserIndex].Pos.X,
						UserList[UserIndex].Pos.Y));
						*/

		if (!criminal(UserIndex)) {
			UserList[UserIndex].Reputacion.PlebeRep = UserList[UserIndex].Reputacion.PlebeRep + vlProleta;
			if (UserList[UserIndex].Reputacion.PlebeRep > MAXREP) {
				UserList[UserIndex].Reputacion.PlebeRep = MAXREP;
			}
		}

		UserList[UserIndex].Counters.Trabajando = UserList[UserIndex].Counters.Trabajando + 1;
	}
}

int MineralesParaLingote(iMinerales Lingote) {
	int retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */
	switch (Lingote) {
	case iMinerales_HierroCrudo:
		retval = 14;
		break;

	case iMinerales_PlataCruda:
		retval = 20;
		break;

	case iMinerales_OroCrudo:
		retval = 35;
		break;

	default:
		retval = 10000;
		break;
	}
	return retval;
}

void DoLingotes(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 16/11/2009 */
	/* '16/11/2009: ZaMa - Implementado nuevo sistema de construccion de items */
	/* '*************************************************** */
	/* '    Call LogTarea("Sub DoLingotes") */
	int Slot = 0;
	int obji = 0;
	int CantidadItems = 0;
	bool TieneMinerales = false;
	int OtroUserIndex = 0;

	if (UserList[UserIndex].flags.Comerciando) {
		OtroUserIndex = UserList[UserIndex].ComUsu.DestUsu;

		if (OtroUserIndex > 0 && OtroUserIndex <= MaxUsers) {
			WriteConsoleMsg(UserIndex, "¡¡Comercio cancelado, no puedes comerciar mientras trabajas!!",
					FontTypeNames_FONTTYPE_TALK);
			WriteConsoleMsg(OtroUserIndex, "¡¡Comercio cancelado por el otro usuario!!",
					FontTypeNames_FONTTYPE_TALK);

			LimpiarComercioSeguro(UserIndex);
			FlushBuffer(OtroUserIndex);
		}
	}

	CantidadItems = MaximoInt(1, vb6::CInt((UserList[UserIndex].Stats.ELV - 4) / 5));

	Slot = UserList[UserIndex].flags.TargetObjInvSlot;
	obji = UserList[UserIndex].Invent.Object[Slot].ObjIndex;

	while (CantidadItems > 0 && !TieneMinerales) {
		if (UserList[UserIndex].Invent.Object[Slot].Amount
				>= MineralesParaLingote(static_cast<iMinerales>(obji)) * CantidadItems) {
			TieneMinerales = true;
		} else {
			CantidadItems = CantidadItems - 1;
		}
	}

	if (!TieneMinerales || ObjData[obji].OBJType != eOBJType_otMinerales) {
		WriteConsoleMsg(UserIndex, "No tienes suficientes minerales para hacer un lingote.",
				FontTypeNames_FONTTYPE_INFO);
		return;
	}

	UserList[UserIndex].Invent.Object[Slot].Amount = UserList[UserIndex].Invent.Object[Slot].Amount
			- MineralesParaLingote(static_cast<iMinerales>(obji)) * CantidadItems;
	if (UserList[UserIndex].Invent.Object[Slot].Amount < 1) {
		UserList[UserIndex].Invent.Object[Slot].Amount = 0;
		UserList[UserIndex].Invent.Object[Slot].ObjIndex = 0;
	}

	struct Obj MiObj;
	MiObj.Amount = CantidadItems;
	MiObj.ObjIndex = ObjData[UserList[UserIndex].flags.TargetObjInvIndex].LingoteIndex;
	if (!MeterItemEnInventario(UserIndex, MiObj)) {
		TirarItemAlPiso(UserList[UserIndex].Pos, MiObj);
	}

	UpdateUserInv(false, UserIndex, Slot);
	WriteConsoleMsg(UserIndex,
			vb6::CStr("¡Has obtenido ") + vb6::CStr(CantidadItems) + " lingote" + vb6::IIf(CantidadItems == 1, "", "s") + "!",
			FontTypeNames_FONTTYPE_INFO);

	UserList[UserIndex].Counters.Trabajando = UserList[UserIndex].Counters.Trabajando + 1;
}

void DoFundir(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 03/06/2010 */
	/* '03/06/2010 - Pato: Si es el último ítem a fundir y está equipado lo desequipamos. */
	/* '11/03/2010 - ZaMa: Reemplazo división por producto para uan mejor performanse. */
	/* '*************************************************** */
	int i;
	int num;
	int Slot;
	std::vector<int> Lingotes;
	int OtroUserIndex;
	int ItemIndex;

	Lingotes.resize(3);

	if (UserList[UserIndex].flags.Comerciando) {
		OtroUserIndex = UserList[UserIndex].ComUsu.DestUsu;

		if (OtroUserIndex > 0 && OtroUserIndex <= MaxUsers) {
			WriteConsoleMsg(UserIndex, "¡¡Comercio cancelado, no puedes comerciar mientras trabajas!!",
					FontTypeNames_FONTTYPE_TALK);
			WriteConsoleMsg(OtroUserIndex, "¡¡Comercio cancelado por el otro usuario!!",
					FontTypeNames_FONTTYPE_TALK);

			LimpiarComercioSeguro(UserIndex);
			FlushBuffer(OtroUserIndex);
		}
	}

	Slot = UserList[UserIndex].flags.TargetObjInvSlot;

	ItemIndex = UserList[UserIndex].Invent.Object[Slot].ObjIndex;
	UserList[UserIndex].Invent.Object[Slot].Amount = UserList[UserIndex].Invent.Object[Slot].Amount - 1;

	if (UserList[UserIndex].Invent.Object[Slot].Amount < 1) {
		if (UserList[UserIndex].Invent.Object[Slot].Equipped == 1) {
			Desequipar(UserIndex, Slot, true);
		}

		UserList[UserIndex].Invent.Object[Slot].Amount = 0;
		UserList[UserIndex].Invent.Object[Slot].ObjIndex = 0;
	}

	num = RandomNumber(10, 25);

	Lingotes[0] = (ObjData[UserList[UserIndex].flags.TargetObjInvIndex].LingH * num) * 0.01;
	Lingotes[1] = (ObjData[UserList[UserIndex].flags.TargetObjInvIndex].LingP * num) * 0.01;
	Lingotes[2] = (ObjData[UserList[UserIndex].flags.TargetObjInvIndex].LingO * num) * 0.01;

	std::vector<struct Obj> MiObj;
	MiObj.resize(3);

	for (i = (0); i <= (2); i++) {
		MiObj[i].Amount = Lingotes[i];
		/* 'Una gran negrada pero práctica */
		MiObj[i].ObjIndex = LingoteHierro + i;

		if (MiObj[i].Amount > 0) {
			if (!MeterItemEnInventario(UserIndex, MiObj[i])) {
				TirarItemAlPiso(UserList[UserIndex].Pos, MiObj[i]);
			}
		}
	}

	UpdateUserInv(false, UserIndex, Slot);
	WriteConsoleMsg(UserIndex,
			vb6::CStr("¡Has obtenido el ") + vb6::CStr(num) + "% de los lingotes utilizados para la construcción del objeto!",
			FontTypeNames_FONTTYPE_INFO);

	if (ObjData[ItemIndex].Log == 1) {
		LogDesarrollo(UserList[UserIndex].Name + " ha fundido el ítem " + ObjData[ItemIndex].Name);
	}

	UserList[UserIndex].Counters.Trabajando = UserList[UserIndex].Counters.Trabajando + 1;

}

void DoUpgrade(int UserIndex, int ItemIndex) {
	/* '*************************************************** */
	/* 'Author: Torres Patricio (Pato) */
	/* 'Last Modification: 12/08/2009 */
	/* '12/08/2009: Pato - Implementado nuevo sistema de mejora de items */
	/* '*************************************************** */
	int ItemUpgrade;
	int WeaponIndex;
	int OtroUserIndex;

	ItemUpgrade = ObjData[ItemIndex].Upgrade;

	if (UserList[UserIndex].flags.Comerciando) {
		OtroUserIndex = UserList[UserIndex].ComUsu.DestUsu;

		if (OtroUserIndex > 0 && OtroUserIndex <= MaxUsers) {
			WriteConsoleMsg(UserIndex, "¡¡Comercio cancelado, no puedes comerciar mientras trabajas!!",
					FontTypeNames_FONTTYPE_TALK);
			WriteConsoleMsg(OtroUserIndex, "¡¡Comercio cancelado por el otro usuario!!",
					FontTypeNames_FONTTYPE_TALK);

			LimpiarComercioSeguro(UserIndex);
			FlushBuffer(OtroUserIndex);
		}
	}

	/* 'Sacamos energía */
	if (UserList[UserIndex].clase == eClass_Worker) {
		/* 'Chequeamos que tenga los puntos antes de sacarselos */
		if (UserList[UserIndex].Stats.MinSta >= GASTO_ENERGIA_TRABAJADOR) {
			UserList[UserIndex].Stats.MinSta = UserList[UserIndex].Stats.MinSta - GASTO_ENERGIA_TRABAJADOR;
			WriteUpdateSta(UserIndex);
		} else {
			WriteConsoleMsg(UserIndex, "No tienes suficiente energía.", FontTypeNames_FONTTYPE_INFO);
			return;
		}
	} else {
		/* 'Chequeamos que tenga los puntos antes de sacarselos */
		if (UserList[UserIndex].Stats.MinSta >= GASTO_ENERGIA_NO_TRABAJADOR) {
			UserList[UserIndex].Stats.MinSta = UserList[UserIndex].Stats.MinSta - GASTO_ENERGIA_NO_TRABAJADOR;
			WriteUpdateSta(UserIndex);
		} else {
			WriteConsoleMsg(UserIndex, "No tienes suficiente energía.", FontTypeNames_FONTTYPE_INFO);
			return;
		}
	}

	if (ItemUpgrade <= 0) {
		return;
	}
	if (!TieneMaterialesUpgrade(UserIndex, ItemIndex)) {
		return;
	}

	if (PuedeConstruirHerreria(ItemUpgrade)) {

		WeaponIndex = UserList[UserIndex].Invent.WeaponEqpObjIndex;

		if (WeaponIndex != MARTILLO_HERRERO && WeaponIndex != MARTILLO_HERRERO_NEWBIE) {
			WriteConsoleMsg(UserIndex, "Debes equiparte el martillo de herrero.",
					FontTypeNames_FONTTYPE_INFO);
			return;
		}

		if (vb6::Round(
				UserList[UserIndex].Stats.UserSkills[eSkill_Herreria]
						/ ModHerreriA(UserList[UserIndex].clase), 0) < ObjData[ItemUpgrade].SkHerreria) {
			WriteConsoleMsg(UserIndex, "No tienes suficientes skills.", FontTypeNames_FONTTYPE_INFO);
			return;
		}

		switch (ObjData[ItemIndex].OBJType) {
		case eOBJType_otWeapon:
			WriteConsoleMsg(UserIndex, "Has mejorado el arma!", FontTypeNames_FONTTYPE_INFO);

			/* 'Todavía no hay, pero just in case */
			break;

		case eOBJType_otESCUDO:
			WriteConsoleMsg(UserIndex, "Has mejorado el escudo!", FontTypeNames_FONTTYPE_INFO);

			break;

		case eOBJType_otCASCO:
			WriteConsoleMsg(UserIndex, "Has mejorado el casco!", FontTypeNames_FONTTYPE_INFO);

			break;

		case eOBJType_otArmadura:
			WriteConsoleMsg(UserIndex, "Has mejorado la armadura!", FontTypeNames_FONTTYPE_INFO);
			break;

		default:
			break;
		}

		SubirSkill(UserIndex, eSkill_Herreria, true);

		SendData(SendTarget_ToPCArea, UserIndex,
				dakara::protocol::server::BuildPlayWave(MARTILLOHERRERO, UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y));

		/*
		SendData(SendTarget_ToPCArea, UserIndex,
				PrepareMessagePlayWave(MARTILLOHERRERO, UserList[UserIndex].Pos.X,
						UserList[UserIndex].Pos.Y));
						*/

	} else if (PuedeConstruirCarpintero(ItemUpgrade)) {

		WeaponIndex = UserList[UserIndex].Invent.WeaponEqpObjIndex;
		if (WeaponIndex != SERRUCHO_CARPINTERO && WeaponIndex != SERRUCHO_CARPINTERO_NEWBIE) {
			WriteConsoleMsg(UserIndex, "Debes equiparte un serrucho.", FontTypeNames_FONTTYPE_INFO);
			return;
		}

		if (vb6::Round(
				UserList[UserIndex].Stats.UserSkills[eSkill_Carpinteria]
						/ ModCarpinteria(UserList[UserIndex].clase), 0)
				< ObjData[ItemUpgrade].SkCarpinteria) {
			WriteConsoleMsg(UserIndex, "No tienes suficientes skills.", FontTypeNames_FONTTYPE_INFO);
			return;
		}

		switch (ObjData[ItemIndex].OBJType) {
		case eOBJType_otFlechas:
			WriteConsoleMsg(UserIndex, "Has mejorado la flecha!", FontTypeNames_FONTTYPE_INFO);

			break;

		case eOBJType_otWeapon:
			WriteConsoleMsg(UserIndex, "Has mejorado el arma!", FontTypeNames_FONTTYPE_INFO);

			break;

		case eOBJType_otBarcos:
			WriteConsoleMsg(UserIndex, "Has mejorado el barco!", FontTypeNames_FONTTYPE_INFO);
			break;

		default:
			break;
		}

		SubirSkill(UserIndex, eSkill_Carpinteria, true);

		SendData(SendTarget_ToPCArea, UserIndex,
				dakara::protocol::server::BuildPlayWave(LABUROCARPINTERO, UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y));

		/*
		SendData(SendTarget_ToPCArea, UserIndex,
				PrepareMessagePlayWave(LABUROCARPINTERO, UserList[UserIndex].Pos.X,
						UserList[UserIndex].Pos.Y));
						*/
	} else {
		return;
	}

	QuitarMaterialesUpgrade(UserIndex, ItemIndex);

	struct Obj MiObj;
	MiObj.Amount = 1;
	MiObj.ObjIndex = ItemUpgrade;

	if (!MeterItemEnInventario(UserIndex, MiObj)) {
		TirarItemAlPiso(UserList[UserIndex].Pos, MiObj);
	}

	if (ObjData[ItemIndex].Log == 1) {
		LogDesarrollo(
				UserList[UserIndex].Name + " ha mejorado el ítem " + ObjData[ItemIndex].Name + " a "
						+ ObjData[ItemUpgrade].Name);
	}

	UserList[UserIndex].Reputacion.PlebeRep = UserList[UserIndex].Reputacion.PlebeRep + vlProleta;
	if (UserList[UserIndex].Reputacion.PlebeRep > MAXREP) {
		UserList[UserIndex].Reputacion.PlebeRep = MAXREP;
	}

	UserList[UserIndex].Counters.Trabajando = UserList[UserIndex].Counters.Trabajando + 1;
}

float ModNavegacion(eClass clase, int UserIndex) {
	float retval;
	/* '*************************************************** */
	/* 'Autor: Unknown (orginal version) */
	/* 'Last Modification: 27/11/2009 */
	/* '27/11/2009: ZaMa - A worker can navigate before only if it's an expert fisher */
	/* '12/04/2010: ZaMa - Arreglo modificador de pescador, para que navegue con 60 skills. */
	/* '*************************************************** */
	switch (clase) {
	case eClass_Pirat:
		retval = 1;
		break;

	case eClass_Worker:
		if (UserList[UserIndex].Stats.UserSkills[eSkill_Pesca] == 100) {
			retval = 1.71;
		} else {
			retval = 2;
		}
		break;

	default:
		retval = 2;
		break;
	}

	return retval;
}

float ModFundicion(eClass clase) {
	float retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	switch (clase) {
	case eClass_Worker:
		retval = 1;
		break;

	default:
		retval = 3;
		break;
	}

	return retval;
}

int ModCarpinteria(eClass clase) {
	int retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	switch (clase) {
	case eClass_Worker:
		retval = 1;
		break;

	default:
		retval = 3;
		break;
	}

	return retval;
}

float ModHerreriA(eClass clase) {
	float retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */
	switch (clase) {
	case eClass_Worker:
		retval = 1;
		break;

	default:
		retval = 4;
		break;
	}

	return retval;
}

int ModDomar(eClass clase) {
	int retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */
	switch (clase) {
	case eClass_Druid:
		retval = 6;
		break;

	case eClass_Hunter:
		retval = 6;
		break;

	case eClass_Cleric:
		retval = 7;
		break;

	default:
		retval = 10;
		break;
	}
	return retval;
}

int FreeMascotaIndex(int UserIndex) {
	int retval = 0;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 02/03/09 */
	/* '02/03/09: ZaMa - Busca un indice libre de mascotas, revisando los types y no los indices de los npcs */
	/* '*************************************************** */
	int j;
	for (j = (1); j <= (MAXMASCOTAS); j++) {
		if (UserList[UserIndex].MascotasType[j] == 0) {
			retval = j;
			return retval;
		}
	}
	return retval;
}

void DoDomar(int UserIndex, int NpcIndex) {
	/* '*************************************************** */
	/* 'Author: Nacho (Integer) */
	/* 'Last Modification: 01/05/2010 */
	/* '12/15/2008: ZaMa - Limits the number of the same type of pet to 2. */
	/* '02/03/2009: ZaMa - Las criaturas domadas en zona segura, esperan afuera (desaparecen). */
	/* '01/05/2010: ZaMa - Agrego bonificacion 11% para domar con flauta magica. */
	/* '*************************************************** */

	int puntosDomar;
	int puntosRequeridos;
	bool CanStay = false;
	int petType;
	int NroPets;

	if (Npclist[NpcIndex].MaestroUser == UserIndex) {
		WriteConsoleMsg(UserIndex, "Ya domaste a esa criatura.", FontTypeNames_FONTTYPE_INFO);
		return;
	}

	if (UserList[UserIndex].NroMascotas < MAXMASCOTAS) {

		if (Npclist[NpcIndex].MaestroNpc > 0 || Npclist[NpcIndex].MaestroUser > 0) {
			WriteConsoleMsg(UserIndex, "La criatura ya tiene amo.", FontTypeNames_FONTTYPE_INFO);
			return;
		}

		if (!PuedeDomarMascota(UserIndex, NpcIndex)) {
			WriteConsoleMsg(UserIndex, "No puedes domar más de dos criaturas del mismo tipo.",
					FontTypeNames_FONTTYPE_INFO);
			return;
		}

		puntosDomar = vb6::CInt(UserList[UserIndex].Stats.UserAtributos[eAtributos_Carisma])
				* vb6::CInt(UserList[UserIndex].Stats.UserSkills[eSkill_Domar]);

		/* ' 20% de bonificacion */
		if (UserList[UserIndex].Invent.AnilloEqpObjIndex == FLAUTAELFICA) {
			puntosRequeridos = Npclist[NpcIndex].flags.Domable * 0.8;

			/* ' 11% de bonificacion */
		} else if (UserList[UserIndex].Invent.AnilloEqpObjIndex == FLAUTAMAGICA) {
			puntosRequeridos = Npclist[NpcIndex].flags.Domable * 0.89;

		} else {
			puntosRequeridos = Npclist[NpcIndex].flags.Domable;
		}

		if (puntosRequeridos <= puntosDomar && RandomNumber(1, 5) == 1) {
			int index;
			UserList[UserIndex].NroMascotas = UserList[UserIndex].NroMascotas + 1;
			index = FreeMascotaIndex(UserIndex);
			UserList[UserIndex].MascotasIndex[index] = NpcIndex;
			UserList[UserIndex].MascotasType[index] = Npclist[NpcIndex].Numero;

			Npclist[NpcIndex].MaestroUser = UserIndex;

			FollowAmo(NpcIndex);
			ReSpawnNpc(Npclist[NpcIndex]);

			WriteConsoleMsg(UserIndex, "La criatura te ha aceptado como su amo.",
					FontTypeNames_FONTTYPE_INFO);

			/* ' Es zona segura? */
			CanStay = (MapInfo[UserList[UserIndex].Pos.Map].Pk == true);

			if (!CanStay) {
				petType = Npclist[NpcIndex].Numero;
				NroPets = UserList[UserIndex].NroMascotas;

				QuitarNPC(NpcIndex);

				UserList[UserIndex].MascotasType[index] = petType;
				UserList[UserIndex].NroMascotas = NroPets;

				WriteConsoleMsg(UserIndex,
						"No se permiten mascotas en zona segura. Éstas te esperarán afuera.",
						FontTypeNames_FONTTYPE_INFO);
			}

			SubirSkill(UserIndex, eSkill_Domar, true);

		} else {
			if (UserList[UserIndex].flags.UltimoMensaje != 5) {
				WriteConsoleMsg(UserIndex, "No has logrado domar la criatura.", FontTypeNames_FONTTYPE_INFO);
				UserList[UserIndex].flags.UltimoMensaje = 5;
			}

			SubirSkill(UserIndex, eSkill_Domar, false);
		}
	} else {
		WriteConsoleMsg(UserIndex, "No puedes controlar más criaturas.", FontTypeNames_FONTTYPE_INFO);
	}
}

/* '' */
/* ' Checks if the user can tames a pet. */
/* ' */
/* ' @param integer userIndex The user id from who wants tame the pet. */
/* ' @param integer NPCindex The index of the npc to tome. */
/* ' @return boolean True if can, false if not. */
bool PuedeDomarMascota(int UserIndex, int NpcIndex) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'This function checks how many NPCs of the same type have */
	/* 'been tamed by the user. */
	/* 'Returns True if that amount is less than two. */
	/* '*************************************************** */
	int i;
	int numMascotas = 0;

	for (i = (1); i <= (MAXMASCOTAS); i++) {
		if (UserList[UserIndex].MascotasType[i] == Npclist[NpcIndex].Numero) {
			numMascotas = numMascotas + 1;
		}
	}

	if (numMascotas <= 1) {
		retval = true;
	}

	return retval;
}

void DoAdminInvisible(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 12/01/2010 (ZaMa) */
	/* 'Makes an admin invisible o visible. */
	/* '13/07/2009: ZaMa - Now invisible admins' chars are erased from all clients, except from themselves. */
	/* '12/01/2010: ZaMa - Los druidas pierden la inmunidad de ser atacados cuando pierden el efecto del mimetismo. */
	/* '*************************************************** */

	if (UserList[UserIndex].flags.AdminInvisible == 0) {
		/* ' Sacamos el mimetizmo */
		if (UserList[UserIndex].flags.Mimetizado == 1) {
			UserList[UserIndex].Char.body = UserList[UserIndex].CharMimetizado.body;
			UserList[UserIndex].Char.Head = UserList[UserIndex].CharMimetizado.Head;
			UserList[UserIndex].Char.CascoAnim = UserList[UserIndex].CharMimetizado.CascoAnim;
			UserList[UserIndex].Char.ShieldAnim = UserList[UserIndex].CharMimetizado.ShieldAnim;
			UserList[UserIndex].Char.WeaponAnim = UserList[UserIndex].CharMimetizado.WeaponAnim;
			UserList[UserIndex].Counters.Mimetismo = 0;
			UserList[UserIndex].flags.Mimetizado = 0;
			/* ' Se fue el efecto del mimetismo, puede ser atacado por npcs */
			UserList[UserIndex].flags.Ignorado = false;
		}

		UserList[UserIndex].flags.AdminInvisible = 1;
		UserList[UserIndex].flags.invisible = 1;
		UserList[UserIndex].flags.Oculto = 1;
		UserList[UserIndex].flags.OldBody = UserList[UserIndex].Char.body;
		UserList[UserIndex].flags.OldHead = UserList[UserIndex].Char.Head;
		UserList[UserIndex].Char.body = 0;
		UserList[UserIndex].Char.Head = 0;

		/* ' Solo el admin sabe que se hace invi */

		/*
		EnviarDatosASlot(UserIndex, PrepareMessageSetInvisible(UserList[UserIndex].Char.CharIndex, true));
		*/
		WriteSetInvisible(UserIndex, UserList[UserIndex].Char.CharIndex, true);

		/* 'Le mandamos el mensaje para que borre el personaje a los clientes que estén cerca */

		{
			dakara::protocol::server::CharacterRemove p;
			p.CharIndex = UserList[UserIndex].Char.CharIndex;
			SendData(SendTarget_ToPCAreaButIndex, UserIndex, p);
		}

		/*
		SendData(SendTarget_ToPCAreaButIndex, UserIndex,
				PrepareMessageCharacterRemove(UserList[UserIndex].Char.CharIndex));
				*/
	} else {
		UserList[UserIndex].flags.AdminInvisible = 0;
		UserList[UserIndex].flags.invisible = 0;
		UserList[UserIndex].flags.Oculto = 0;
		UserList[UserIndex].Counters.TiempoOculto = 0;
		UserList[UserIndex].Char.body = UserList[UserIndex].flags.OldBody;
		UserList[UserIndex].Char.Head = UserList[UserIndex].flags.OldHead;

		/* ' Solo el admin sabe que se hace visible */
		/*
		EnviarDatosASlot(UserIndex,
				PrepareMessageCharacterChange(UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
						UserList[UserIndex].Char.heading, UserList[UserIndex].Char.CharIndex,
						UserList[UserIndex].Char.WeaponAnim, UserList[UserIndex].Char.ShieldAnim,
						UserList[UserIndex].Char.FX, UserList[UserIndex].Char.loops,
						UserList[UserIndex].Char.CascoAnim));
		 */
		WriteCharacterChange(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
				UserList[UserIndex].Char.heading, UserList[UserIndex].Char.CharIndex,
				UserList[UserIndex].Char.WeaponAnim, UserList[UserIndex].Char.ShieldAnim,
				UserList[UserIndex].Char.FX, UserList[UserIndex].Char.loops,
				UserList[UserIndex].Char.CascoAnim);

		/*
		EnviarDatosASlot(UserIndex, PrepareMessageSetInvisible(UserList[UserIndex].Char.CharIndex, false));
		*/
		WriteSetInvisible(UserIndex, UserList[UserIndex].Char.CharIndex, false);

		/* 'Le mandamos el mensaje para crear el personaje a los clientes que estén cerca */
		MakeUserChar(true, UserList[UserIndex].Pos.Map, UserIndex, UserList[UserIndex].Pos.Map,
				UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y, true);
	}

}

void TratarDeHacerFogata(int Map, int X, int Y, int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int Suerte;
	int exito;
	struct Obj Obj;
	struct WorldPos posMadera;

	if (!LegalPos(Map, X, Y)) {
		return;
	}

	posMadera.Map = Map;
	posMadera.X = X;
	posMadera.Y = Y;

	if (MapData[Map][X][Y].ObjInfo.ObjIndex != 58) {
		WriteConsoleMsg(UserIndex, "Necesitas clickear sobre lena para hacer ramitas.",
				FontTypeNames_FONTTYPE_INFO);
		return;
	}

	if (Distancia(posMadera, UserList[UserIndex].Pos) > 2) {
		WriteConsoleMsg(UserIndex, "Estás demasiado lejos para prender la fogata.",
				FontTypeNames_FONTTYPE_INFO);
		return;
	}

	if (UserList[UserIndex].flags.Muerto == 1) {
		WriteConsoleMsg(UserIndex, "No puedes hacer fogatas estando muerto.", FontTypeNames_FONTTYPE_INFO);
		return;
	}

	if (MapData[Map][X][Y].ObjInfo.Amount < 3) {
		WriteConsoleMsg(UserIndex, "Necesitas por lo menos tres troncos para hacer una fogata.",
				FontTypeNames_FONTTYPE_INFO);
		return;
	}

	int SupervivenciaSkill;

	SupervivenciaSkill = UserList[UserIndex].Stats.UserSkills[eSkill_Supervivencia];

	if (SupervivenciaSkill < 6) {
		Suerte = 3;
	} else if (SupervivenciaSkill <= 34) {
		Suerte = 2;
	} else {
		Suerte = 1;
	}

	exito = RandomNumber(1, Suerte);

	if (exito == 1) {
		Obj.ObjIndex = FOGATA_APAG;
		Obj.Amount = MapData[Map][X][Y].ObjInfo.Amount / 3;

		WriteConsoleMsg(UserIndex, "Has hecho " + vb6::CStr(Obj.Amount) + " fogatas.", FontTypeNames_FONTTYPE_INFO);

		MakeObj(Obj, Map, X, Y);

		/* 'Seteamos la fogata como el nuevo TargetObj del user */
		UserList[UserIndex].flags.TargetObj = FOGATA_APAG;

		SubirSkill(UserIndex, eSkill_Supervivencia, true);
	} else {
		/* '[CDT 17-02-2004] */
		if (UserList[UserIndex].flags.UltimoMensaje != 10) {
			WriteConsoleMsg(UserIndex, "No has podido hacer la fogata.", FontTypeNames_FONTTYPE_INFO);
			UserList[UserIndex].flags.UltimoMensaje = 10;
		}
		/* '[/CDT] */

		SubirSkill(UserIndex, eSkill_Supervivencia, false);
	}

}

void DoPescar(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 28/05/2010 */
	/* '16/11/2009: ZaMa - Implementado nuevo sistema de extraccion. */
	/* '11/05/2010: ZaMa - Arreglo formula de maximo de items contruibles/extraibles. */
	/* '05/13/2010: Pato - Refix a la formula de maximo de items construibles/extraibles. */
	/* '22/05/2010: ZaMa - Los caos ya no suben plebe al trabajar. */
	/* '28/05/2010: ZaMa - Los pks no suben plebe al trabajar. */
	/* '*************************************************** */

	int Suerte;
	int res;
	int CantidadItems;
	int Skill;

	if (UserList[UserIndex].clase == eClass_Worker) {
		QuitarSta(UserIndex, EsfuerzoPescarPescador);
	} else {
		QuitarSta(UserIndex, EsfuerzoPescarGeneral);
	}

	Skill = UserList[UserIndex].Stats.UserSkills[eSkill_Pesca];
	Suerte = vb6::Int(-0.00125 * Skill * Skill - 0.3 * Skill + 49);

	res = RandomNumber(1, Suerte);

	if (res <= 6) {
		struct Obj MiObj;

		if (UserList[UserIndex].clase == eClass_Worker) {
			CantidadItems = MaxItemsExtraibles(UserList[UserIndex].Stats.ELV);

			MiObj.Amount = RandomNumber(1, CantidadItems);
		} else {
			MiObj.Amount = 1;
		}

		MiObj.ObjIndex = Pescado;

		if (!MeterItemEnInventario(UserIndex, MiObj)) {
			TirarItemAlPiso(UserList[UserIndex].Pos, MiObj);
		}

		WriteConsoleMsg(UserIndex, "¡Has pescado un lindo pez!", FontTypeNames_FONTTYPE_INFO);

		SubirSkill(UserIndex, eSkill_Pesca, true);
	} else {
		/* '[CDT 17-02-2004] */
		if (UserList[UserIndex].flags.UltimoMensaje != 6) {
			WriteConsoleMsg(UserIndex, "¡No has pescado nada!", FontTypeNames_FONTTYPE_INFO);
			UserList[UserIndex].flags.UltimoMensaje = 6;
		}
		/* '[/CDT] */

		SubirSkill(UserIndex, eSkill_Pesca, false);
	}

	if (!criminal(UserIndex)) {
		UserList[UserIndex].Reputacion.PlebeRep = UserList[UserIndex].Reputacion.PlebeRep + vlProleta;
		if (UserList[UserIndex].Reputacion.PlebeRep > MAXREP) {
			UserList[UserIndex].Reputacion.PlebeRep = MAXREP;
		}
	}

	UserList[UserIndex].Counters.Trabajando = UserList[UserIndex].Counters.Trabajando + 1;
}

void DoPescarRed(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int iSkill;
	int Suerte;
	int res;
	bool EsPescador = false;
	int CantidadItems;

	if (UserList[UserIndex].clase == eClass_Worker) {
		QuitarSta(UserIndex, EsfuerzoPescarPescador);
		EsPescador = true;
	} else {
		QuitarSta(UserIndex, EsfuerzoPescarGeneral);
		EsPescador = false;
	}

	iSkill = UserList[UserIndex].Stats.UserSkills[eSkill_Pesca];

	/* ' m = (60-11)/(1-10) */
	/* ' y = mx - m*10 + 11 */

	Suerte = vb6::Int(-0.00125 * iSkill * iSkill - 0.3 * iSkill + 49);

	if (Suerte > 0) {
		res = RandomNumber(1, Suerte);

		if (res <= 6) {

			struct Obj MiObj;

			if (EsPescador) {
				CantidadItems = MaxItemsExtraibles(UserList[UserIndex].Stats.ELV);
				MiObj.Amount = RandomNumber(1, CantidadItems);
			} else {
				MiObj.Amount = 1;
			}

			MiObj.ObjIndex = ListaPeces[RandomNumber(1, NUM_PECES)];

			if (!MeterItemEnInventario(UserIndex, MiObj)) {
				TirarItemAlPiso(UserList[UserIndex].Pos, MiObj);
			}

			WriteConsoleMsg(UserIndex, "¡Has pescado algunos peces!", FontTypeNames_FONTTYPE_INFO);

			SubirSkill(UserIndex, eSkill_Pesca, true);
		} else {
			if (UserList[UserIndex].flags.UltimoMensaje != 6) {
				WriteConsoleMsg(UserIndex, "¡No has pescado nada!", FontTypeNames_FONTTYPE_INFO);
				UserList[UserIndex].flags.UltimoMensaje = 6;
			}

			SubirSkill(UserIndex, eSkill_Pesca, false);
		}
	}

	UserList[UserIndex].Reputacion.PlebeRep = UserList[UserIndex].Reputacion.PlebeRep + vlProleta;
	if (UserList[UserIndex].Reputacion.PlebeRep > MAXREP) {
		UserList[UserIndex].Reputacion.PlebeRep = MAXREP;
	}
}

/* '' */
/* ' Try to steal an item / gold to another character */
/* ' */
/* ' @param LadrOnIndex Specifies reference to user that stoles */
/* ' @param VictimaIndex Specifies reference to user that is being stolen */

void DoRobar(int LadrOnIndex, int VictimaIndex) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 05/04/2010 */
	/* 'Last Modification By: ZaMa */
	/* '24/07/08: Marco - Now it calls to WriteUpdateGold(VictimaIndex and LadrOnIndex) when the thief stoles gold. (MarKoxX) */
	/* '27/11/2009: ZaMa - Optimizacion de codigo. */
	/* '18/12/2009: ZaMa - Los ladrones ciudas pueden robar a pks. */
	/* '01/04/2010: ZaMa - Los ladrones pasan a robar oro acorde a su nivel. */
	/* '05/04/2010: ZaMa - Los armadas no pueden robarle a ciudadanos jamas. */
	/* '23/04/2010: ZaMa - No se puede robar mas sin energia. */
	/* '23/04/2010: ZaMa - El alcance de robo pasa a ser de 1 tile. */
	/* '************************************************* */

	int OtroUserIndex;

	if (!MapInfo[UserList[VictimaIndex].Pos.Map].Pk) {
		return;
	}

	if (UserList[VictimaIndex].flags.EnConsulta) {
		WriteConsoleMsg(LadrOnIndex, "¡¡¡No puedes robar a usuarios en consulta!!!",
				FontTypeNames_FONTTYPE_INFO);
		return;
	}

	if (UserList[LadrOnIndex].flags.Seguro) {
		if (!criminal(VictimaIndex)) {
			WriteConsoleMsg(LadrOnIndex, "Debes quitarte el seguro para robarle a un ciudadano.",
					FontTypeNames_FONTTYPE_FIGHT);
			return;
		}
	} else {
		if (UserList[LadrOnIndex].Faccion.ArmadaReal == 1) {
			if (!criminal(VictimaIndex)) {
				WriteConsoleMsg(LadrOnIndex,
						"Los miembros del ejército real no tienen permitido robarle a ciudadanos.",
						FontTypeNames_FONTTYPE_FIGHT);
				return;
			}
		}
	}

	/* ' Caos robando a caos? */
	if (UserList[VictimaIndex].Faccion.FuerzasCaos == 1 && UserList[LadrOnIndex].Faccion.FuerzasCaos == 1) {
		WriteConsoleMsg(LadrOnIndex, "No puedes robar a otros miembros de la legión oscura.",
				FontTypeNames_FONTTYPE_FIGHT);
		return;
	}

	if (TriggerZonaPelea(LadrOnIndex, VictimaIndex) != eTrigger6_TRIGGER6_AUSENTE) {
		return;
	}

	/* ' Tiene energia? */
	if (UserList[LadrOnIndex].Stats.MinSta < 15) {
		if (UserList[LadrOnIndex].Genero == eGenero_Hombre) {
			WriteConsoleMsg(LadrOnIndex, "Estás muy cansado para robar.", FontTypeNames_FONTTYPE_INFO);
		} else {
			WriteConsoleMsg(LadrOnIndex, "Estás muy cansada para robar.", FontTypeNames_FONTTYPE_INFO);
		}

		return;
	}

	/* ' Quito energia */
	QuitarSta(LadrOnIndex, 15);

	bool GuantesHurto = false;

	if (UserList[LadrOnIndex].Invent.AnilloEqpObjIndex == GUANTE_HURTO) {
		GuantesHurto = true;
	}

	if (UserTienePrivilegio(VictimaIndex, PlayerType_User)) {
		int Suerte;
		int res;
		int RobarSkill;

		RobarSkill = UserList[LadrOnIndex].Stats.UserSkills[eSkill_Robar];

		if (RobarSkill <= 10) {
			Suerte = 35;
		} else if (RobarSkill <= 20) {
			Suerte = 30;
		} else if (RobarSkill <= 30) {
			Suerte = 28;
		} else if (RobarSkill <= 40) {
			Suerte = 24;
		} else if (RobarSkill <= 50) {
			Suerte = 22;
		} else if (RobarSkill <= 60) {
			Suerte = 20;
		} else if (RobarSkill <= 70) {
			Suerte = 18;
		} else if (RobarSkill <= 80) {
			Suerte = 15;
		} else if (RobarSkill <= 90) {
			Suerte = 10;
		} else if (RobarSkill < 100) {
			Suerte = 7;
		} else {
			Suerte = 5;
		}

		res = RandomNumber(1, Suerte);

		/* 'Exito robo */
		if (res < 3) {
			if (UserList[VictimaIndex].flags.Comerciando) {
				OtroUserIndex = UserList[VictimaIndex].ComUsu.DestUsu;

				if (OtroUserIndex > 0 && OtroUserIndex <= MaxUsers) {
					WriteConsoleMsg(VictimaIndex, "¡¡Comercio cancelado, te están robando!!",
							FontTypeNames_FONTTYPE_TALK);
					WriteConsoleMsg(OtroUserIndex, "¡¡Comercio cancelado por el otro usuario!!",
							FontTypeNames_FONTTYPE_TALK);

					LimpiarComercioSeguro(VictimaIndex);
					FlushBuffer(OtroUserIndex);
				}
			}

			if ((RandomNumber(1, 50) < 25) && (UserList[LadrOnIndex].clase == eClass_Thief)) {
				if (TieneObjetosRobables(VictimaIndex)) {
					RobarObjeto(LadrOnIndex, VictimaIndex);
				} else {
					WriteConsoleMsg(LadrOnIndex, UserList[VictimaIndex].Name + " no tiene objetos.",
							FontTypeNames_FONTTYPE_INFO);
				}
				/* 'Roba oro */
			} else {
				if (UserList[VictimaIndex].Stats.GLD > 0) {
					int N;

					if (UserList[LadrOnIndex].clase == eClass_Thief) {
						/* ' Si no tine puestos los guantes de hurto roba un 50% menos. Pablo (ToxicWaste) */
						if (GuantesHurto) {
							N = RandomNumber(UserList[LadrOnIndex].Stats.ELV * 50,
									UserList[LadrOnIndex].Stats.ELV * 100);
						} else {
							N = RandomNumber(UserList[LadrOnIndex].Stats.ELV * 25,
									UserList[LadrOnIndex].Stats.ELV * 50);
						}
					} else {
						N = RandomNumber(1, 100);
					}
					if (N > UserList[VictimaIndex].Stats.GLD) {
						N = UserList[VictimaIndex].Stats.GLD;
					}
					UserList[VictimaIndex].Stats.GLD = UserList[VictimaIndex].Stats.GLD - N;

					UserList[LadrOnIndex].Stats.GLD = UserList[LadrOnIndex].Stats.GLD + N;
					if (UserList[LadrOnIndex].Stats.GLD > MAXORO) {
						UserList[LadrOnIndex].Stats.GLD = MAXORO;
					}

					WriteConsoleMsg(LadrOnIndex,
							vb6::CStr("Le has robado ") + vb6::CStr(N) + " monedas de oro a " + UserList[VictimaIndex].Name,
							FontTypeNames_FONTTYPE_INFO);
					/* 'Le actualizamos la billetera al ladron */
					WriteUpdateGold(LadrOnIndex);

					/* 'Le actualizamos la billetera a la victima */
					WriteUpdateGold(VictimaIndex);
					FlushBuffer(VictimaIndex);
				} else {
					WriteConsoleMsg(LadrOnIndex, UserList[VictimaIndex].Name + " no tiene oro.",
							FontTypeNames_FONTTYPE_INFO);
				}
			}

			SubirSkill(LadrOnIndex, eSkill_Robar, true);
		} else {
			WriteConsoleMsg(LadrOnIndex, "¡No has logrado robar nada!", FontTypeNames_FONTTYPE_INFO);
			WriteConsoleMsg(VictimaIndex, "¡" + UserList[LadrOnIndex].Name + " ha intentado robarte!",
					FontTypeNames_FONTTYPE_INFO);
			FlushBuffer(VictimaIndex);

			SubirSkill(LadrOnIndex, eSkill_Robar, false);
		}

		if (!criminal(LadrOnIndex)) {
			if (!criminal(VictimaIndex)) {
				VolverCriminal(LadrOnIndex);
			}
		}

		/* ' Se pudo haber convertido si robo a un ciuda */
		if (criminal(LadrOnIndex)) {
			UserList[LadrOnIndex].Reputacion.LadronesRep = UserList[LadrOnIndex].Reputacion.LadronesRep
					+ vlLadron;
			if (UserList[LadrOnIndex].Reputacion.LadronesRep > MAXREP) {
				UserList[LadrOnIndex].Reputacion.LadronesRep = MAXREP;
			}
		}
	}
}

/* '' */
/* ' Check if one item is stealable */
/* ' */
/* ' @param VictimaIndex Specifies reference to victim */
/* ' @param Slot Specifies reference to victim's inventory slot */
/* ' @return If the item is stealable */
bool ObjEsRobable(int VictimaIndex, int Slot) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' Agregué los barcos */
	/* ' Esta funcion determina qué objetos son robables. */
	/* ' 22/05/2010: Los items newbies ya no son robables. */
	/* '*************************************************** */

	int OI;

	OI = UserList[VictimaIndex].Invent.Object[Slot].ObjIndex;

	retval = ObjData[OI].OBJType != eOBJType_otLlaves
			&& UserList[VictimaIndex].Invent.Object[Slot].Equipped == 0 && ObjData[OI].Real == 0
			&& ObjData[OI].Caos == 0 && ObjData[OI].OBJType != eOBJType_otBarcos && !ItemNewbie(OI)
			&& ObjData[OI].Intransferible == 0 && ObjData[OI].NoRobable == 0;
	return retval;
}

/* '' */
/* ' Try to steal an item to another character */
/* ' */
/* ' @param LadrOnIndex Specifies reference to user that stoles */
/* ' @param VictimaIndex Specifies reference to user that is being stolen */
void RobarObjeto(int LadrOnIndex, int VictimaIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 02/04/2010 */
	/* '02/04/2010: ZaMa - Modifico la cantidad de items robables por el ladron. */
	/* '*************************************************** */

	bool flag = false;
	int i;

	flag = false;

	/* 'Comenzamos por el principio o el final? */
	if (RandomNumber(1, 12) < 6) {
		i = 1;
		while (!flag && i <= UserList[VictimaIndex].CurrentInventorySlots) {
			/* 'Hay objeto en este slot? */
			if (UserList[VictimaIndex].Invent.Object[i].ObjIndex > 0) {
				if (ObjEsRobable(VictimaIndex, i)) {
					if (RandomNumber(1, 10) < 4) {
						flag = true;
					}
				}
			}
			if (!flag) {
				i = i + 1;
			}
		}
	} else {
		i = UserList[VictimaIndex].CurrentInventorySlots;
		while (!flag && i > 0) {
			/* 'Hay objeto en este slot? */
			if (UserList[VictimaIndex].Invent.Object[i].ObjIndex > 0) {
				if (ObjEsRobable(VictimaIndex, i)) {
					if (RandomNumber(1, 10) < 4) {
						flag = true;
					}
				}
			}
			if (!flag) {
				i = i - 1;
			}
		}
	}

	if (flag) {
		struct Obj MiObj;
		int num;
		int ObjAmount;

		ObjAmount = UserList[VictimaIndex].Invent.Object[i].Amount;

		/* 'Cantidad al azar entre el 5% y el 10% del total, con minimo 1. */
		num = MaximoInt(1, RandomNumber(ObjAmount * 0.05, ObjAmount * 0.1));

		MiObj.Amount = num;
		MiObj.ObjIndex = UserList[VictimaIndex].Invent.Object[i].ObjIndex;

		UserList[VictimaIndex].Invent.Object[i].Amount = ObjAmount - num;

		if (UserList[VictimaIndex].Invent.Object[i].Amount <= 0) {
			QuitarUserInvItem(VictimaIndex, vb6::CByte(i), 1);
		}

		UpdateUserInv(false, VictimaIndex, vb6::CByte(i));

		if (!MeterItemEnInventario(LadrOnIndex, MiObj)) {
			TirarItemAlPiso(UserList[LadrOnIndex].Pos, MiObj);
		}

		if (UserList[LadrOnIndex].clase == eClass_Thief) {
			WriteConsoleMsg(LadrOnIndex, vb6::CStr("Has robado ") + vb6::CStr(MiObj.Amount) + " " + ObjData[MiObj.ObjIndex].Name,
					FontTypeNames_FONTTYPE_INFO);
		} else {
			WriteConsoleMsg(LadrOnIndex, vb6::CStr("Has hurtado ") + vb6::CStr(MiObj.Amount) + " " + ObjData[MiObj.ObjIndex].Name,
					FontTypeNames_FONTTYPE_INFO);
		}
	} else {
		WriteConsoleMsg(LadrOnIndex, "No has logrado robar ningún objeto.", FontTypeNames_FONTTYPE_INFO);
	}

	/* 'If exiting, cancel de quien es robado */
	CancelExit(VictimaIndex);

}

void DoApunalar(int UserIndex, int VictimNpcIndex, int VictimUserIndex, int dano) {
	/* '*************************************************** */
	/* 'Autor: Nacho (Integer) & Unknown (orginal version) */
	/* 'Last Modification: 04/17/08 - (NicoNZ) */
	/* 'Simplifique la cuenta que hacia para sacar la suerte */
	/* 'y arregle la cuenta que hacia para sacar el dano */
	/* '*************************************************** */
	int Suerte;
	int Skill;

	Skill = UserList[UserIndex].Stats.UserSkills[eSkill_Apunalar];

	switch (UserList[UserIndex].clase) {
	case eClass_Assasin:
		Suerte = vb6::Int(((0.00003 * Skill - 0.002) * Skill + 0.098) * Skill + 4.25);

		break;

	case eClass_Cleric:
	case eClass_Paladin:
	case eClass_Pirat:
		Suerte = vb6::Int(((0.000003 * Skill + 0.0006) * Skill + 0.0107) * Skill + 4.93);

		break;

	case eClass_Bard:
		Suerte = vb6::Int(((0.000002 * Skill + 0.0002) * Skill + 0.032) * Skill + 4.81);

		break;

	default:
		Suerte = vb6::Int(0.0361 * Skill + 4.39);
		break;
	}

	if (RandomNumber(0, 100) < Suerte) {
		if (VictimUserIndex != 0) {
			if (UserList[UserIndex].clase == eClass_Assasin) {
				dano = vb6::Round(dano * 1.4, 0);
			} else {
				dano = vb6::Round(dano * 1.5, 0);
			}

			UserList[VictimUserIndex].Stats.MinHp = UserList[VictimUserIndex].Stats.MinHp - dano;
			WriteConsoleMsg(UserIndex, "Has apunalado a " + UserList[VictimUserIndex].Name + " por " + vb6::CStr(dano),
					FontTypeNames_FONTTYPE_FIGHT);
			WriteConsoleMsg(VictimUserIndex, "Te ha apunalado " + UserList[UserIndex].Name + " por " + vb6::CStr(dano),
					FontTypeNames_FONTTYPE_FIGHT);

			FlushBuffer(VictimUserIndex);
		} else {
			Npclist[VictimNpcIndex].Stats.MinHp = Npclist[VictimNpcIndex].Stats.MinHp - vb6::Int(dano * 2);
			WriteConsoleMsg(UserIndex, "Has apunalado la criatura por " + vb6::CStr(dano * 2),
					FontTypeNames_FONTTYPE_FIGHT);
			/* '[Alejo] */
			CalcularDarExp(UserIndex, VictimNpcIndex, dano * 2);
		}

		SubirSkill(UserIndex, eSkill_Apunalar, true);
	} else {
		WriteConsoleMsg(UserIndex, "¡No has logrado apunalar a tu enemigo!", FontTypeNames_FONTTYPE_FIGHT);
		SubirSkill(UserIndex, eSkill_Apunalar, false);
	}

}

void DoAcuchillar(int UserIndex, int VictimNpcIndex, int VictimUserIndex, int dano) {
	/* '*************************************************** */
	/* 'Autor: ZaMa */
	/* 'Last Modification: 12/01/2010 */
	/* '*************************************************** */

	if (RandomNumber(1, 100) <= PROB_ACUCHILLAR) {
		dano = vb6::Int(dano * DANO_ACUCHILLAR);

		if (VictimUserIndex != 0) {

			UserList[VictimUserIndex].Stats.MinHp = UserList[VictimUserIndex].Stats.MinHp - dano;
			WriteConsoleMsg(UserIndex, "Has acuchillado a " + UserList[VictimUserIndex].Name + " por " + vb6::CStr(dano),
					FontTypeNames_FONTTYPE_FIGHT);
			WriteConsoleMsg(VictimUserIndex, UserList[UserIndex].Name + " te ha acuchillado por " + vb6::CStr(dano),
					FontTypeNames_FONTTYPE_FIGHT);

		} else {

			Npclist[VictimNpcIndex].Stats.MinHp = Npclist[VictimNpcIndex].Stats.MinHp - dano;
			WriteConsoleMsg(UserIndex, "Has acuchillado a la criatura por " + vb6::CStr(dano),
					FontTypeNames_FONTTYPE_FIGHT);
			CalcularDarExp(UserIndex, VictimNpcIndex, dano);

		}
	}

}

void DoGolpeCritico(int UserIndex, int VictimNpcIndex, int VictimUserIndex, int dano) {
	/* '*************************************************** */
	/* 'Autor: Pablo (ToxicWaste) */
	/* 'Last Modification: 28/01/2007 */
	/* '01/06/2010: ZaMa - Valido si tiene arma equipada antes de preguntar si es vikinga. */
	/* '*************************************************** */
	int Suerte;
	int Skill;
	int WeaponIndex;

	/* ' Es bandido? */
	if (UserList[UserIndex].clase != eClass_Bandit) {
		return;
	}

	WeaponIndex = UserList[UserIndex].Invent.WeaponEqpObjIndex;

	/* ' Es una espada vikinga? */
	if (WeaponIndex != ESPADA_VIKINGA) {
		return;
	}

	Skill = UserList[UserIndex].Stats.UserSkills[eSkill_Wrestling];

	Suerte = vb6::Int((((0.00000003 * Skill + 0.000006) * Skill + 0.000107) * Skill + 0.0893) * 100);

	if (RandomNumber(1, 100) <= Suerte) {

		dano = vb6::Int(dano * 0.75);

		if (VictimUserIndex != 0) {

			UserList[VictimUserIndex].Stats.MinHp = UserList[VictimUserIndex].Stats.MinHp - dano;
			WriteConsoleMsg(UserIndex,
					"Has golpeado críticamente a " + UserList[VictimUserIndex].Name + " por " + vb6::CStr(dano) + ".",
					FontTypeNames_FONTTYPE_FIGHT);
			WriteConsoleMsg(VictimUserIndex,
					UserList[UserIndex].Name + " te ha golpeado críticamente por " + vb6::CStr(dano) + ".",
					FontTypeNames_FONTTYPE_FIGHT);

		} else {

			Npclist[VictimNpcIndex].Stats.MinHp = Npclist[VictimNpcIndex].Stats.MinHp - dano;
			WriteConsoleMsg(UserIndex, "Has golpeado críticamente a la criatura por " + vb6::CStr(dano) + ".",
					FontTypeNames_FONTTYPE_FIGHT);
			CalcularDarExp(UserIndex, VictimNpcIndex, dano);

		}

	}

}

void QuitarSta(int UserIndex, int Cantidad) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	UserList[UserIndex].Stats.MinSta = UserList[UserIndex].Stats.MinSta - Cantidad;
	if (UserList[UserIndex].Stats.MinSta < 0) {
		UserList[UserIndex].Stats.MinSta = 0;
	}
	WriteUpdateSta(UserIndex);
}

void DoTalar(int UserIndex, bool DarMaderaElfica) {
	/* '*************************************************** */
	/* 'Autor: Unknown */
	/* 'Last Modification: 28/05/2010 */
	/* '16/11/2009: ZaMa - Ahora Se puede dar madera elfica. */
	/* '16/11/2009: ZaMa - Implementado nuevo sistema de extraccion. */
	/* '11/05/2010: ZaMa - Arreglo formula de maximo de items contruibles/extraibles. */
	/* '05/13/2010: Pato - Refix a la formula de maximo de items construibles/extraibles. */
	/* '22/05/2010: ZaMa - Los caos ya no suben plebe al trabajar. */
	/* '28/05/2010: ZaMa - Los pks no suben plebe al trabajar. */
	/* '*************************************************** */

	int Suerte;
	int res;
	int CantidadItems;
	int Skill;

	if (UserList[UserIndex].clase == eClass_Worker) {
		QuitarSta(UserIndex, EsfuerzoTalarLenador);
	} else {
		QuitarSta(UserIndex, EsfuerzoTalarGeneral);
	}

	Skill = UserList[UserIndex].Stats.UserSkills[eSkill_Talar];
	Suerte = vb6::Int(-0.00125 * Skill * Skill - 0.3 * Skill + 49);

	res = RandomNumber(1, Suerte);

	if (res <= 6) {
		struct Obj MiObj;

		if (UserList[UserIndex].clase == eClass_Worker) {
			CantidadItems = MaxItemsExtraibles(UserList[UserIndex].Stats.ELV);

			MiObj.Amount = RandomNumber(1, CantidadItems);
		} else {
			MiObj.Amount = 1;
		}

		MiObj.ObjIndex = vb6::IIf(DarMaderaElfica, LenaElfica, Lena);

		if (!MeterItemEnInventario(UserIndex, MiObj)) {
			TirarItemAlPiso(UserList[UserIndex].Pos, MiObj);
		}

		WriteConsoleMsg(UserIndex, "¡Has conseguido algo de lena!", FontTypeNames_FONTTYPE_INFO);

		SubirSkill(UserIndex, eSkill_Talar, true);
	} else {
		/* '[CDT 17-02-2004] */
		if (UserList[UserIndex].flags.UltimoMensaje != 8) {
			WriteConsoleMsg(UserIndex, "¡No has obtenido lena!", FontTypeNames_FONTTYPE_INFO);
			UserList[UserIndex].flags.UltimoMensaje = 8;
		}
		/* '[/CDT] */
		SubirSkill(UserIndex, eSkill_Talar, false);
	}

	if (!criminal(UserIndex)) {
		UserList[UserIndex].Reputacion.PlebeRep = UserList[UserIndex].Reputacion.PlebeRep + vlProleta;
		if (UserList[UserIndex].Reputacion.PlebeRep > MAXREP) {
			UserList[UserIndex].Reputacion.PlebeRep = MAXREP;
		}
	}

	UserList[UserIndex].Counters.Trabajando = UserList[UserIndex].Counters.Trabajando + 1;
}

void DoMineria(int UserIndex) {
	/* '*************************************************** */
	/* 'Autor: Unknown */
	/* 'Last Modification: 28/05/2010 */
	/* '16/11/2009: ZaMa - Implementado nuevo sistema de extraccion. */
	/* '11/05/2010: ZaMa - Arreglo formula de maximo de items contruibles/extraibles. */
	/* '05/13/2010: Pato - Refix a la formula de maximo de items construibles/extraibles. */
	/* '22/05/2010: ZaMa - Los caos ya no suben plebe al trabajar. */
	/* '28/05/2010: ZaMa - Los pks no suben plebe al trabajar. */
	/* '*************************************************** */

	int Suerte;
	int res;
	int CantidadItems;

	if (UserList[UserIndex].clase == eClass_Worker) {
		QuitarSta(UserIndex, EsfuerzoExcavarMinero);
	} else {
		QuitarSta(UserIndex, EsfuerzoExcavarGeneral);
	}

	int Skill;
	Skill = UserList[UserIndex].Stats.UserSkills[eSkill_Mineria];
	Suerte = vb6::Int(-0.00125 * Skill * Skill - 0.3 * Skill + 49);

	res = RandomNumber(1, Suerte);

	if (res <= 5) {
		struct Obj MiObj;

		if (UserList[UserIndex].flags.TargetObj == 0) {
			return;
		}

		MiObj.ObjIndex = ObjData[UserList[UserIndex].flags.TargetObj].MineralIndex;

		if (UserList[UserIndex].clase == eClass_Worker) {
			CantidadItems = MaxItemsExtraibles(UserList[UserIndex].Stats.ELV);

			MiObj.Amount = RandomNumber(1, CantidadItems);
		} else {
			MiObj.Amount = 1;
		}

		if (!MeterItemEnInventario(UserIndex, MiObj)) {
			TirarItemAlPiso(UserList[UserIndex].Pos, MiObj);
		}

		WriteConsoleMsg(UserIndex, "¡Has extraido algunos minerales!", FontTypeNames_FONTTYPE_INFO);

		SubirSkill(UserIndex, eSkill_Mineria, true);
	} else {
		/* '[CDT 17-02-2004] */
		if (UserList[UserIndex].flags.UltimoMensaje != 9) {
			WriteConsoleMsg(UserIndex, "¡No has conseguido nada!", FontTypeNames_FONTTYPE_INFO);
			UserList[UserIndex].flags.UltimoMensaje = 9;
		}
		/* '[/CDT] */
		SubirSkill(UserIndex, eSkill_Mineria, false);
	}

	if (!criminal(UserIndex)) {
		UserList[UserIndex].Reputacion.PlebeRep = UserList[UserIndex].Reputacion.PlebeRep + vlProleta;
		if (UserList[UserIndex].Reputacion.PlebeRep > MAXREP) {
			UserList[UserIndex].Reputacion.PlebeRep = MAXREP;
		}
	}

	UserList[UserIndex].Counters.Trabajando = UserList[UserIndex].Counters.Trabajando + 1;
}

void DoMeditar(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	UserList[UserIndex].Counters.IdleCount = 0;

	int Suerte;
	int res;
	int cant;
	int MeditarSkill;

	/* 'Barrin 3/10/03 */
	/* 'Esperamos a que se termine de concentrar */
	int TActual;
	TActual = vb6::GetTickCount();

	int iInterval;
	iInterval = vb6::Int(UserList[UserIndex].Stats.ELV / 17) * 1000;
	/* ' [TEMPORAL] TIEMPO_INICIOMEDITAR Then */
	if (getInterval(TActual, UserList[UserIndex].Counters.tInicioMeditar) < iInterval) {
		return;
	}

	if (UserList[UserIndex].Counters.bPuedeMeditar == false) {
		UserList[UserIndex].Counters.bPuedeMeditar = true;
	}

	if (UserList[UserIndex].Stats.MinMAN >= UserList[UserIndex].Stats.MaxMAN) {
		WriteConsoleMsg(UserIndex, "Has terminado de meditar.", FontTypeNames_FONTTYPE_INFO);
		WriteMeditateToggle(UserIndex);
		UserList[UserIndex].flags.Meditando = false;
		UserList[UserIndex].Char.FX = 0;
		UserList[UserIndex].Char.loops = 0;

		/*
		SendData(SendTarget_ToPCArea, UserIndex,
				PrepareMessageCreateFX(UserList[UserIndex].Char.CharIndex, 0, 0));
				*/
		SendData(SendTarget_ToPCArea, UserIndex,
				dakara::protocol::server::BuildCreateFX(UserList[UserIndex].Char.CharIndex, 0, 0));

		return;
	}

	MeditarSkill = UserList[UserIndex].Stats.UserSkills[eSkill_Meditar];

	if (MeditarSkill <= 10) {
		Suerte = 35;
	} else if (MeditarSkill <= 20) {
		Suerte = 30;
	} else if (MeditarSkill <= 30) {
		Suerte = 28;
	} else if (MeditarSkill <= 40) {
		Suerte = 24;
	} else if (MeditarSkill <= 50) {
		Suerte = 22;
	} else if (MeditarSkill <= 60) {
		Suerte = 20;
	} else if (MeditarSkill <= 70) {
		Suerte = 18;
	} else if (MeditarSkill <= 80) {
		Suerte = 15;
	} else if (MeditarSkill <= 90) {
		Suerte = 10;
	} else if (MeditarSkill < 100) {
		Suerte = 7;
	} else {
		Suerte = 5;
	}
	res = RandomNumber(1, Suerte);

	if (res == 1) {

		cant = Porcentaje(UserList[UserIndex].Stats.MaxMAN, PorcentajeRecuperoMana);
		if (cant <= 0) {
			cant = 1;
		}
		UserList[UserIndex].Stats.MinMAN = UserList[UserIndex].Stats.MinMAN + cant;
		if (UserList[UserIndex].Stats.MinMAN > UserList[UserIndex].Stats.MaxMAN) {
			UserList[UserIndex].Stats.MinMAN = UserList[UserIndex].Stats.MaxMAN;
		}

		if (UserList[UserIndex].flags.UltimoMensaje != 22) {
			WriteConsoleMsg(UserIndex, "¡Has recuperado " + vb6::CStr(cant) + " puntos de maná!",
					FontTypeNames_FONTTYPE_INFO);
			UserList[UserIndex].flags.UltimoMensaje = 22;
		}

		WriteUpdateMana(UserIndex);
		SubirSkill(UserIndex, eSkill_Meditar, true);
	} else {
		SubirSkill(UserIndex, eSkill_Meditar, false);
	}
}

void DoDesequipar(int UserIndex, int VictimIndex) {
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modif: 15/04/2010 */
	/* 'Unequips either shield, weapon or helmet from target user. */
	/* '*************************************************** */

	int Probabilidad;
	int Resultado;
	int WrestlingSkill;
	bool AlgoEquipado = false;

	/* ' Si no tiene guantes de hurto no desequipa. */
	if (UserList[UserIndex].Invent.AnilloEqpObjIndex != GUANTE_HURTO) {
		return;
	}

	/* ' Si no esta solo con manos, no desequipa tampoco. */
	if (UserList[UserIndex].Invent.WeaponEqpObjIndex > 0) {
		return;
	}

	WrestlingSkill = UserList[UserIndex].Stats.UserSkills[eSkill_Wrestling];

	Probabilidad = WrestlingSkill * 0.2 + UserList[UserIndex].Stats.ELV * 0.66;

	/* ' Si tiene escudo, intenta desequiparlo */
	if (UserList[VictimIndex].Invent.EscudoEqpObjIndex > 0) {

		Resultado = RandomNumber(1, 100);

		if (Resultado <= Probabilidad) {
			/* ' Se lo desequipo */
			Desequipar(VictimIndex, UserList[VictimIndex].Invent.EscudoEqpSlot, true);

			WriteConsoleMsg(UserIndex, "Has logrado desequipar el escudo de tu oponente!",
					FontTypeNames_FONTTYPE_FIGHT);

			if (UserList[VictimIndex].Stats.ELV < 20) {
				WriteConsoleMsg(VictimIndex, "¡Tu oponente te ha desequipado el escudo!",
						FontTypeNames_FONTTYPE_FIGHT);
			}

			FlushBuffer(VictimIndex);

			return;
		}

		AlgoEquipado = true;
	}

	/* ' No tiene escudo, o fallo desequiparlo, entonces trata de desequipar arma */
	if (UserList[VictimIndex].Invent.WeaponEqpObjIndex > 0) {

		Resultado = RandomNumber(1, 100);

		if (Resultado <= Probabilidad) {
			/* ' Se lo desequipo */
			Desequipar(VictimIndex, UserList[VictimIndex].Invent.WeaponEqpSlot, true);

			WriteConsoleMsg(UserIndex, "Has logrado desarmar a tu oponente!", FontTypeNames_FONTTYPE_FIGHT);

			if (UserList[VictimIndex].Stats.ELV < 20) {
				WriteConsoleMsg(VictimIndex, "¡Tu oponente te ha desarmado!", FontTypeNames_FONTTYPE_FIGHT);
			}

			FlushBuffer(VictimIndex);

			return;
		}

		AlgoEquipado = true;
	}

	/* ' No tiene arma, o fallo desequiparla, entonces trata de desequipar casco */
	if (UserList[VictimIndex].Invent.CascoEqpObjIndex > 0) {

		Resultado = RandomNumber(1, 100);

		if (Resultado <= Probabilidad) {
			/* ' Se lo desequipo */
			Desequipar(VictimIndex, UserList[VictimIndex].Invent.CascoEqpSlot, true);

			WriteConsoleMsg(UserIndex, "Has logrado desequipar el casco de tu oponente!",
					FontTypeNames_FONTTYPE_FIGHT);

			if (UserList[VictimIndex].Stats.ELV < 20) {
				WriteConsoleMsg(VictimIndex, "¡Tu oponente te ha desequipado el casco!",
						FontTypeNames_FONTTYPE_FIGHT);
			}

			FlushBuffer(VictimIndex);

			return;
		}

		AlgoEquipado = true;
	}

	if (AlgoEquipado) {
		WriteConsoleMsg(UserIndex, "Tu oponente no tiene equipado items!", FontTypeNames_FONTTYPE_FIGHT);
	} else {
		WriteConsoleMsg(UserIndex, "No has logrado desequipar ningún item a tu oponente!",
				FontTypeNames_FONTTYPE_FIGHT);
	}

}

void DoHurtar(int UserIndex, int VictimaIndex) {
	/* '*************************************************** */
	/* 'Author: Pablo (ToxicWaste) */
	/* 'Last Modif: 03/03/2010 */
	/* 'Implements the pick pocket skill of the Bandit :) */
	/* '03/03/2010 - Pato: Sólo se puede hurtar si no está en trigger 6 :) */
	/* '*************************************************** */
	int OtroUserIndex;

	if (TriggerZonaPelea(UserIndex, VictimaIndex) != eTrigger6_TRIGGER6_AUSENTE) {
		return;
	}

	if (UserList[UserIndex].clase != eClass_Bandit) {
		return;
	}
	/* 'Esto es precario y feo, pero por ahora no se me ocurrió nada mejor. */
	/* 'Uso el slot de los anillos para "equipar" los guantes. */
	/* 'Y los reconozco porque les puse DefensaMagicaMin y Max = 0 */
	if (UserList[UserIndex].Invent.AnilloEqpObjIndex != GUANTE_HURTO) {
		return;
	}

	int res;
	res = RandomNumber(1, 100);
	if ((res < 20)) {
		if (TieneObjetosRobables(VictimaIndex)) {

			if (UserList[VictimaIndex].flags.Comerciando) {
				OtroUserIndex = UserList[VictimaIndex].ComUsu.DestUsu;

				if (OtroUserIndex > 0 && OtroUserIndex <= MaxUsers) {
					WriteConsoleMsg(VictimaIndex, "¡¡Comercio cancelado, te están robando!!",
							FontTypeNames_FONTTYPE_TALK);
					WriteConsoleMsg(OtroUserIndex, "¡¡Comercio cancelado por el otro usuario!!",
							FontTypeNames_FONTTYPE_TALK);

					LimpiarComercioSeguro(VictimaIndex);
					FlushBuffer(OtroUserIndex);
				}
			}

			RobarObjeto(UserIndex, VictimaIndex);
			WriteConsoleMsg(VictimaIndex, "¡" + UserList[UserIndex].Name + " es un Bandido!",
					FontTypeNames_FONTTYPE_INFO);
		} else {
			WriteConsoleMsg(UserIndex, UserList[VictimaIndex].Name + " no tiene objetos.",
					FontTypeNames_FONTTYPE_INFO);
		}
	}

}

void DoHandInmo(int UserIndex, int VictimaIndex) {
	/* '*************************************************** */
	/* 'Author: Pablo (ToxicWaste) */
	/* 'Last Modif: 17/02/2007 */
	/* 'Implements the special Skill of the Thief */
	/* '*************************************************** */
	if (UserList[VictimaIndex].flags.Paralizado == 1) {
		return;
	}
	if (UserList[UserIndex].clase != eClass_Thief) {
		return;
	}

	if (UserList[UserIndex].Invent.AnilloEqpObjIndex != GUANTE_HURTO) {
		return;
	}

	int res;
	res = RandomNumber(0, 100);
	if (res < (UserList[UserIndex].Stats.UserSkills[eSkill_Wrestling] / 4)) {
		UserList[VictimaIndex].flags.Paralizado = 1;
		UserList[VictimaIndex].Counters.Paralisis = IntervaloParalizado / 2;

		UserList[VictimaIndex].flags.ParalizedByIndex = UserIndex;
		UserList[VictimaIndex].flags.ParalizedBy = UserList[UserIndex].Name;

		WriteParalizeOK(VictimaIndex);
		WriteConsoleMsg(UserIndex, "Tu golpe ha dejado inmóvil a tu oponente", FontTypeNames_FONTTYPE_INFO);
		WriteConsoleMsg(VictimaIndex, "¡El golpe te ha dejado inmóvil!", FontTypeNames_FONTTYPE_INFO);
	}

}

void Desarmar(int UserIndex, int VictimIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 02/04/2010 (ZaMa) */
	/* '02/04/2010: ZaMa - Nueva formula para desarmar. */
	/* '*************************************************** */

	int Probabilidad;
	int Resultado;
	int WrestlingSkill;

	WrestlingSkill = UserList[UserIndex].Stats.UserSkills[eSkill_Wrestling];

	Probabilidad = WrestlingSkill * 0.2 + UserList[UserIndex].Stats.ELV * 0.66;

	Resultado = RandomNumber(1, 100);

	if (Resultado <= Probabilidad) {
		Desequipar(VictimIndex, UserList[VictimIndex].Invent.WeaponEqpSlot, true);
		WriteConsoleMsg(UserIndex, "Has logrado desarmar a tu oponente!", FontTypeNames_FONTTYPE_FIGHT);
		if (UserList[VictimIndex].Stats.ELV < 20) {
			WriteConsoleMsg(VictimIndex, "¡Tu oponente te ha desarmado!", FontTypeNames_FONTTYPE_FIGHT);
		}
		FlushBuffer(VictimIndex);
	}

}

int MaxItemsConstruibles(int UserIndex) {
	int retval;
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 29/01/2010 */
	/* '11/05/2010: ZaMa - Arreglo formula de maximo de items contruibles/extraibles. */
	/* '05/13/2010: Pato - Refix a la formula de maximo de items construibles/extraibles. */
	/* '*************************************************** */

	if (UserList[UserIndex].clase == eClass_Worker) {
		retval = MaximoInt(1, vb6::CInt((UserList[UserIndex].Stats.ELV - 2) * 0.2));
	} else {
		retval = 1;
	}
	return retval;
}

int MaxItemsExtraibles(int UserLevel) {
	int retval;
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 14/05/2010 */
	/* '*************************************************** */
	retval = MaximoInt(1, vb6::CInt((UserLevel - 2) * 0.2)) + 1;
	return retval;
}

void ImitateNpc(int UserIndex, int NpcIndex) {
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 20/11/2010 */
	/* 'Copies body, head and desc from previously clicked npc. */
	/* '*************************************************** */

	/* ' Copy desc */
	UserList[UserIndex].DescRM = Npclist[NpcIndex].Name;

	/* ' Remove Anims (Npcs don't use equipment anims yet) */
	UserList[UserIndex].Char.CascoAnim = NingunCasco;
	UserList[UserIndex].Char.ShieldAnim = NingunEscudo;
	UserList[UserIndex].Char.WeaponAnim = NingunArma;

	/* ' If admin is invisible the store it in old char */
	if (UserList[UserIndex].flags.AdminInvisible == 1 || UserList[UserIndex].flags.invisible == 1
			|| UserList[UserIndex].flags.Oculto == 1) {

		UserList[UserIndex].flags.OldBody = Npclist[NpcIndex].Char.body;
		UserList[UserIndex].flags.OldHead = Npclist[NpcIndex].Char.Head;
	} else {
		UserList[UserIndex].Char.body = Npclist[NpcIndex].Char.body;
		UserList[UserIndex].Char.Head = Npclist[NpcIndex].Char.Head;

		ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
				UserList[UserIndex].Char.heading, UserList[UserIndex].Char.WeaponAnim,
				UserList[UserIndex].Char.ShieldAnim, UserList[UserIndex].Char.CascoAnim);
	}

}
