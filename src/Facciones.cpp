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

#include "Facciones.h"

int ArmaduraImperial1;
int ArmaduraImperial2;
int ArmaduraImperial3;
int TunicaMagoImperial;
int TunicaMagoImperialEnanos;
int ArmaduraCaos1;
int ArmaduraCaos2;
int ArmaduraCaos3;
int TunicaMagoCaos;
int TunicaMagoCaosEnanos;

int VestimentaImperialHumano;
int VestimentaImperialEnano;
int TunicaConspicuaHumano;
int TunicaConspicuaEnano;
int ArmaduraNobilisimaHumano;
int ArmaduraNobilisimaEnano;
int ArmaduraGranSacerdote;

int VestimentaLegionHumano;
int VestimentaLegionEnano;
int TunicaLobregaHumano;
int TunicaLobregaEnano;
int TunicaEgregiaHumano;
int TunicaEgregiaEnano;
int SacerdoteDemoniaco;

const int NUM_RANGOS_FACCION = 15;
const int NUM_DEF_FACCION_ARMOURS = 3;

/* ' Matriz que contiene las armaduras faccionarias segun raza, clase, faccion y defensa de armadura */
vb6::array<vb6::array<struct tFaccionArmaduras> > ArmadurasFaccion;

/* ' Contiene la cantidad de exp otorgada cada vez que aumenta el rango */
vb6::array<int> RecompensaFacciones;

int GetArmourAmount(int Rango, eTipoDefArmors TipoDef) {
	int retval = 0;
	/* '*************************************************** */
	/* 'Autor: ZaMa */
	/* 'Last Modification: 15/04/2010 */
	/* 'Returns the amount of armours to give, depending on the specified rank */
	/* '*************************************************** */

	switch (TipoDef) {

	case eTipoDefArmors_ieBaja:
		retval = 20 / (Rango + 1);

		break;

	case eTipoDefArmors_ieMedia:
		retval = Rango * 2 / MaximoInt((Rango - 4), 1);

		break;

	case eTipoDefArmors_ieAlta:
		retval = Rango * 1.35;

		break;
	}

	return retval;
}

void GiveFactionArmours(int UserIndex, bool IsCaos) {
	/* '*************************************************** */
	/* 'Autor: ZaMa */
	/* 'Last Modification: 15/04/2010 */
	/* 'Gives faction armours to user */
	/* '*************************************************** */

	struct Obj ObjArmour;
	int Rango;

	Rango = (vb6::IIf(IsCaos, UserList[UserIndex].Faccion.RecompensasCaos,
			UserList[UserIndex].Faccion.RecompensasReal)) + 1;

	/* ' Entrego armaduras de defensa baja */
	ObjArmour.Amount = GetArmourAmount(Rango, eTipoDefArmors_ieBaja);

	if (IsCaos) {
		ObjArmour.ObjIndex =
				ArmadurasFaccion[UserList[UserIndex].clase][UserList[UserIndex].raza].Caos[eTipoDefArmors_ieBaja];
	} else {
		ObjArmour.ObjIndex =
				ArmadurasFaccion[UserList[UserIndex].clase][UserList[UserIndex].raza].Armada[eTipoDefArmors_ieBaja];
	}

	if (!MeterItemEnInventario(UserIndex, ObjArmour)) {
		TirarItemAlPiso(UserList[UserIndex].Pos, ObjArmour);
	}

	/* ' Entrego armaduras de defensa media */
	ObjArmour.Amount = GetArmourAmount(Rango, eTipoDefArmors_ieMedia);

	if (IsCaos) {
		ObjArmour.ObjIndex =
				ArmadurasFaccion[UserList[UserIndex].clase][UserList[UserIndex].raza].Caos[eTipoDefArmors_ieMedia];
	} else {
		ObjArmour.ObjIndex =
				ArmadurasFaccion[UserList[UserIndex].clase][UserList[UserIndex].raza].Armada[eTipoDefArmors_ieMedia];
	}

	if (!MeterItemEnInventario(UserIndex, ObjArmour)) {
		TirarItemAlPiso(UserList[UserIndex].Pos, ObjArmour);
	}

	/* ' Entrego armaduras de defensa alta */
	ObjArmour.Amount = GetArmourAmount(Rango, eTipoDefArmors_ieAlta);

	if (IsCaos) {
		ObjArmour.ObjIndex =
				ArmadurasFaccion[UserList[UserIndex].clase][UserList[UserIndex].raza].Caos[eTipoDefArmors_ieAlta];
	} else {
		ObjArmour.ObjIndex =
				ArmadurasFaccion[UserList[UserIndex].clase][UserList[UserIndex].raza].Armada[eTipoDefArmors_ieAlta];
	}

	if (!MeterItemEnInventario(UserIndex, ObjArmour)) {
		TirarItemAlPiso(UserList[UserIndex].Pos, ObjArmour);
	}

}

void GiveExpReward(int UserIndex, int Rango) {
	/* '*************************************************** */
	/* 'Autor: ZaMa */
	/* 'Last Modification: 15/04/2010 */
	/* 'Gives reward exp to user */
	/* '*************************************************** */

	int GivenExp;

	GivenExp = RecompensaFacciones[Rango];

	UserList[UserIndex].Stats.Exp = UserList[UserIndex].Stats.Exp + GivenExp;

	if (UserList[UserIndex].Stats.Exp > MAXEXP) {
		UserList[UserIndex].Stats.Exp = MAXEXP;
	}

	WriteConsoleMsg(UserIndex, "Has sido recompensado con " + vb6::CStr(GivenExp) + " puntos de experiencia.",
			FontTypeNames_FONTTYPE_FIGHT);

	CheckUserLevel(UserIndex);

}

void EnlistarArmadaReal(int UserIndex) {
	/* '*************************************************** */
	/* 'Autor: Pablo (ToxicWaste) & Unknown (orginal version) */
	/* 'Last Modification: 15/04/2010 */
	/* 'Handles the entrance of users to the "Armada Real" */
	/* '15/03/2009: ZaMa - No se puede enlistar el fundador de un clan con alineación neutral. */
	/* '27/11/2009: ZaMa - Ahora no se puede enlistar un miembro de un clan neutro, por ende saque la antifaccion. */
	/* '15/04/2010: ZaMa - Cambio en recompensas iniciales. */
	/* '*************************************************** */

	if (UserList[UserIndex].Faccion.ArmadaReal == 1) {
		WriteChatOverHead(UserIndex, "¡¡¡Ya perteneces a las tropas reales!!! Ve a combatir criminales.",
				(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
		return;
	}

	if (UserList[UserIndex].Faccion.FuerzasCaos == 1) {
		WriteChatOverHead(UserIndex, "¡¡¡Maldito insolente!!! Vete de aquí seguidor de las sombras.",
				(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
		return;
	}

	if (criminal(UserIndex)) {
		WriteChatOverHead(UserIndex, "¡¡¡No se permiten criminales en el ejército real!!!",
				(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
		return;
	}

	if (UserList[UserIndex].Faccion.CriminalesMatados < 30) {
		WriteChatOverHead(UserIndex,
				"Para unirte a nuestras fuerzas debes matar al menos 30 criminales, sólo has matado "
						+ vb6::CStr(UserList[UserIndex].Faccion.CriminalesMatados) + ".",
				(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
		return;
	}

	if (UserList[UserIndex].Stats.ELV < 25) {
		WriteChatOverHead(UserIndex, "¡¡¡Para unirte a nuestras fuerzas debes ser al menos de nivel 25!!!",
				(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
		return;
	}

	if (UserList[UserIndex].Faccion.CiudadanosMatados > 0) {
		WriteChatOverHead(UserIndex,
				"¡Has asesinado gente inocente, no aceptamos asesinos en las tropas reales!",
				(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
		return;
	}

	if (UserList[UserIndex].Faccion.Reenlistadas > 4) {
		WriteChatOverHead(UserIndex, "¡Has sido expulsado de las fuerzas reales demasiadas veces!",
				(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
		return;
	}

	if (UserList[UserIndex].Reputacion.NobleRep < 1000000) {
		WriteChatOverHead(UserIndex,
				"Necesitas ser aún más noble para integrar el ejército real, sólo tienes "
						+ vb6::CStr(UserList[UserIndex].Reputacion.NobleRep) + "/1.000.000 puntos de nobleza",
				(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
		return;
	}

	if (UserList[UserIndex].GuildIndex > 0) {
		if (GuildAlignment(UserList[UserIndex].GuildIndex) == "Neutral") {
			WriteChatOverHead(UserIndex,
					"¡¡¡Perteneces a un clan neutro, sal de él si quieres unirte a nuestras fuerzas!!!",
					(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
			return;
		}
	}

	UserList[UserIndex].Faccion.ArmadaReal = 1;
	UserList[UserIndex].Faccion.Reenlistadas = UserList[UserIndex].Faccion.Reenlistadas + 1;

	WriteChatOverHead(UserIndex,
			"¡¡¡Bienvenido al ejército real!!! Aquí tienes tus vestimentas. Cumple bien tu labor exterminando criminales y me encargaré de recompensarte.",
			(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);

	/* ' TODO: Dejo esta variable por ahora, pero con chequear las reenlistadas deberia ser suficiente :S */
	if (UserList[UserIndex].Faccion.RecibioArmaduraReal == 0) {

		GiveFactionArmours(UserIndex, false);
		GiveExpReward(UserIndex, 0);

		UserList[UserIndex].Faccion.RecibioArmaduraReal = 1;
		UserList[UserIndex].Faccion.NivelIngreso = UserList[UserIndex].Stats.ELV;
		UserList[UserIndex].Faccion.FechaIngreso = vb6::dateToString(vb6::Now());
		/* 'Esto por ahora es inútil, siempre va a ser cero, pero bueno, despues va a servir. */
		UserList[UserIndex].Faccion.MatadosIngreso = UserList[UserIndex].Faccion.CiudadanosMatados;

		UserList[UserIndex].Faccion.RecibioExpInicialReal = 1;
		UserList[UserIndex].Faccion.RecompensasReal = 0;
		UserList[UserIndex].Faccion.NextRecompensa = 70;

	}

	/* 'Actualizamos la barca si esta navegando (NicoNZ) */
	if (UserList[UserIndex].flags.Navegando) {
		RefreshCharStatus(UserIndex);
	}

	LogEjercitoReal(
			UserList[UserIndex].Name + " ingresó el " + UserList[UserIndex].Faccion.FechaIngreso + " cuando era nivel "
					+ vb6::CStr(UserList[UserIndex].Stats.ELV));
}

void RecompensaArmadaReal(int UserIndex) {
	/* '*************************************************** */
	/* 'Autor: Pablo (ToxicWaste) & Unknown (orginal version) */
	/* 'Last Modification: 15/04/2010 */
	/* 'Handles the way of gaining new ranks in the "Armada Real" */
	/* '15/04/2010: ZaMa - Agrego recompensas de oro y armaduras */
	/* '*************************************************** */
	int Crimis;
	int Lvl;
	int NextRecom;
	int Nobleza;

	Lvl = UserList[UserIndex].Stats.ELV;
	Crimis = UserList[UserIndex].Faccion.CriminalesMatados;
	NextRecom = UserList[UserIndex].Faccion.NextRecompensa;
	Nobleza = UserList[UserIndex].Reputacion.NobleRep;

	if (Crimis < NextRecom) {
		WriteChatOverHead(UserIndex,
				"Mata " + vb6::CStr(NextRecom - Crimis)
						+ " criminales más para recibir la próxima recompensa.",
				(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
		return;
	}

	switch (NextRecom) {
	case 70:
		UserList[UserIndex].Faccion.RecompensasReal = 1;
		UserList[UserIndex].Faccion.NextRecompensa = 130;

		break;

	case 130:
		UserList[UserIndex].Faccion.RecompensasReal = 2;
		UserList[UserIndex].Faccion.NextRecompensa = 210;

		break;

	case 210:
		UserList[UserIndex].Faccion.RecompensasReal = 3;
		UserList[UserIndex].Faccion.NextRecompensa = 320;

		break;

	case 320:
		UserList[UserIndex].Faccion.RecompensasReal = 4;
		UserList[UserIndex].Faccion.NextRecompensa = 460;

		break;

	case 460:
		UserList[UserIndex].Faccion.RecompensasReal = 5;
		UserList[UserIndex].Faccion.NextRecompensa = 640;

		break;

	case 640:
		if (Lvl < 27) {
			WriteChatOverHead(UserIndex,
					"Mataste suficientes criminales, pero te faltan " + vb6::CStr(27 - Lvl)
							+ " niveles para poder recibir la próxima recompensa.",
					(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
			return;
		}
		UserList[UserIndex].Faccion.RecompensasReal = 6;
		UserList[UserIndex].Faccion.NextRecompensa = 870;

		break;

	case 870:
		UserList[UserIndex].Faccion.RecompensasReal = 7;
		UserList[UserIndex].Faccion.NextRecompensa = 1160;

		break;

	case 1160:
		UserList[UserIndex].Faccion.RecompensasReal = 8;
		UserList[UserIndex].Faccion.NextRecompensa = 2000;

		break;

	case 2000:
		if (Lvl < 30) {
			WriteChatOverHead(UserIndex,
					"Mataste suficientes criminales, pero te faltan " + vb6::CStr(30 - Lvl)
							+ " niveles para poder recibir la próxima recompensa.",
					(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
			return;
		}
		UserList[UserIndex].Faccion.RecompensasReal = 9;
		UserList[UserIndex].Faccion.NextRecompensa = 2500;

		break;

	case 2500:
		if (Nobleza < 2000000) {
			WriteChatOverHead(UserIndex,
					"Mataste suficientes criminales, pero te faltan " + vb6::CStr(2000000 - Nobleza)
							+ " puntos de nobleza para poder recibir la próxima recompensa.",
					(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
			return;
		}
		UserList[UserIndex].Faccion.RecompensasReal = 10;
		UserList[UserIndex].Faccion.NextRecompensa = 3000;

		break;

	case 3000:
		if (Nobleza < 3000000) {
			WriteChatOverHead(UserIndex,
					"Mataste suficientes criminales, pero te faltan " + vb6::CStr(3000000 - Nobleza)
							+ " puntos de nobleza para poder recibir la próxima recompensa.",
					(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
			return;
		}
		UserList[UserIndex].Faccion.RecompensasReal = 11;
		UserList[UserIndex].Faccion.NextRecompensa = 3500;

		break;

	case 3500:
		if (Lvl < 35) {
			WriteChatOverHead(UserIndex,
					"Mataste suficientes criminales, pero te faltan " + vb6::CStr(35 - Lvl)
							+ " niveles para poder recibir la próxima recompensa.",
					(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
			return;
		}
		if (Nobleza < 4000000) {
			WriteChatOverHead(UserIndex,
					"Mataste suficientes criminales, pero te faltan " + vb6::CStr(4000000 - Nobleza)
							+ " puntos de nobleza para poder recibir la próxima recompensa.",
					(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
			return;
		}
		UserList[UserIndex].Faccion.RecompensasReal = 12;
		UserList[UserIndex].Faccion.NextRecompensa = 4000;

		break;

	case 4000:
		if (Lvl < 36) {
			WriteChatOverHead(UserIndex,
					"Mataste suficientes criminales, pero te faltan " + vb6::CStr(36 - Lvl)
							+ " niveles para poder recibir la próxima recompensa.",
					(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
			return;
		}
		if (Nobleza < 5000000) {
			WriteChatOverHead(UserIndex,
					"Mataste suficientes criminales, pero te faltan " + vb6::CStr(000000 - Nobleza)
							+ " puntos de nobleza para poder recibir la próxima recompensa.",
					(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
			return;
		}
		UserList[UserIndex].Faccion.RecompensasReal = 13;
		UserList[UserIndex].Faccion.NextRecompensa = 5000;

		break;

	case 5000:
		if (Lvl < 37) {
			WriteChatOverHead(UserIndex,
					"Mataste suficientes criminales, pero te faltan " + vb6::CStr(37 - Lvl)
							+ " niveles para poder recibir la próxima recompensa.",
					(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
			return;
		}
		if (Nobleza < 6000000) {
			WriteChatOverHead(UserIndex,
					"Mataste suficientes criminales, pero te faltan " + vb6::CStr(6000000 - Nobleza)
							+ " puntos de nobleza para poder recibir la próxima recompensa.",
					(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
			return;
		}
		UserList[UserIndex].Faccion.RecompensasReal = 14;
		UserList[UserIndex].Faccion.NextRecompensa = 10000;

		break;

	case 10000:
		WriteChatOverHead(UserIndex,
				"Eres uno de mis mejores soldados. Mataste " + vb6::CStr(Crimis)
						+ " criminales, sigue así. Ya no tengo más recompensa para darte que mi agradecimiento. ¡Felicidades!",
				(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
		return;

		break;

	default:
		return;
		break;
	}

	WriteChatOverHead(UserIndex, "¡¡¡Aquí tienes tu recompensa " + TituloReal(UserIndex) + "!!!",
			(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);

	/* ' Recompensas de armaduras y exp */
	GiveFactionArmours(UserIndex, false);
	GiveExpReward(UserIndex, UserList[UserIndex].Faccion.RecompensasReal);

}

void ExpulsarFaccionReal(int UserIndex, bool Expulsado) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' 09/28/2010 C4b3z0n - Arreglado RT6 Overflow, el Desequipar() del escudo, ponía de parametro el ObjIndex del escudo en vez del EqpSlot. */
	/* '*************************************************** */

	UserList[UserIndex].Faccion.ArmadaReal = 0;
	/* 'Call PerderItemsFaccionarios(UserIndex) */
	if (Expulsado) {
		WriteConsoleMsg(UserIndex, "¡¡¡Has sido expulsado del ejército real!!!",
				FontTypeNames_FONTTYPE_FIGHT);
	} else {
		WriteConsoleMsg(UserIndex, "¡¡¡Te has retirado del ejército real!!!", FontTypeNames_FONTTYPE_FIGHT);
	}

	bool bRefresh = false;

	if (UserList[UserIndex].Invent.ArmourEqpObjIndex != 0) {
		/* 'Desequipamos la armadura real si está equipada */
		if (ObjData[UserList[UserIndex].Invent.ArmourEqpObjIndex].Real == 1) {
			Desequipar(UserIndex, UserList[UserIndex].Invent.ArmourEqpSlot, false);
			bRefresh = true;
		}
	}

	if (UserList[UserIndex].Invent.EscudoEqpObjIndex != 0) {
		/* 'Desequipamos el escudo de caos si está equipado */
		if (ObjData[UserList[UserIndex].Invent.EscudoEqpObjIndex].Real == 1) {
			Desequipar(UserIndex, UserList[UserIndex].Invent.EscudoEqpSlot, false);
			bRefresh = true;
		}
	}

	if (bRefresh) {
		ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
				UserList[UserIndex].Char.heading, UserList[UserIndex].Char.WeaponAnim,
				UserList[UserIndex].Char.ShieldAnim, UserList[UserIndex].Char.CascoAnim);
		WriteUpdateUserStats(UserIndex);
	}

	/* 'Actualizamos la barca si esta navegando (NicoNZ) */
	if (UserList[UserIndex].flags.Navegando) {
		RefreshCharStatus(UserIndex);
	}

}

void ExpulsarFaccionCaos(int UserIndex, bool Expulsado) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' 09/28/2010 C4b3z0n - Arreglado RT6 Overflow, el Desequipar() del escudo, ponía de parametro el ObjIndex del escudo en vez del EqpSlot. */
	/* '*************************************************** */

	UserList[UserIndex].Faccion.FuerzasCaos = 0;
	/* 'Call PerderItemsFaccionarios(UserIndex) */
	if (Expulsado) {
		WriteConsoleMsg(UserIndex, "¡¡¡Has sido expulsado de la Legión Oscura!!!",
				FontTypeNames_FONTTYPE_FIGHT);
	} else {
		WriteConsoleMsg(UserIndex, "¡¡¡Te has retirado de la Legión Oscura!!!", FontTypeNames_FONTTYPE_FIGHT);
	}

	bool bRefresh = false;

	if (UserList[UserIndex].Invent.ArmourEqpObjIndex != 0) {
		/* 'Desequipamos la armadura de caos si está equipada */
		if (ObjData[UserList[UserIndex].Invent.ArmourEqpObjIndex].Caos == 1) {
			Desequipar(UserIndex, UserList[UserIndex].Invent.ArmourEqpSlot, false);
			bRefresh = true;
		}
	}

	if (UserList[UserIndex].Invent.EscudoEqpObjIndex != 0) {
		/* 'Desequipamos el escudo de caos si está equipado */
		if (ObjData[UserList[UserIndex].Invent.EscudoEqpObjIndex].Caos == 1) {
			Desequipar(UserIndex, UserList[UserIndex].Invent.EscudoEqpSlot, false);
			bRefresh = true;
		}
	}

	if (bRefresh) {
		ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
				UserList[UserIndex].Char.heading, UserList[UserIndex].Char.WeaponAnim,
				UserList[UserIndex].Char.ShieldAnim, UserList[UserIndex].Char.CascoAnim);
		WriteUpdateUserStats(UserIndex);
	}

	/* 'Actualizamos la barca si esta navegando (NicoNZ) */
	if (UserList[UserIndex].flags.Navegando) {
		RefreshCharStatus(UserIndex);
	}

}

std::string TituloReal(int UserIndex) {
	std::string retval;
	/* '*************************************************** */
	/* 'Autor: Unknown */
	/* 'Last Modification: 23/01/2007 Pablo (ToxicWaste) */
	/* 'Handles the titles of the members of the "Armada Real" */
	/* '*************************************************** */

	switch (UserList[UserIndex].Faccion.RecompensasReal) {
	/* 'Rango 1: Aprendiz (30 Criminales) */
	/* 'Rango 2: Escudero (70 Criminales) */
	/* 'Rango 3: Soldado (130 Criminales) */
	/* 'Rango 4: Sargento (210 Criminales) */
	/* 'Rango 5: Caballero (320 Criminales) */
	/* 'Rango 6: Comandante (460 Criminales) */
	/* 'Rango 7: Capitán (640 Criminales + > lvl 27) */
	/* 'Rango 8: Senescal (870 Criminales) */
	/* 'Rango 9: Mariscal (1160 Criminales) */
	/* 'Rango 10: Condestable (2000 Criminales + > lvl 30) */
	/* 'Rangos de Honor de la Armada Real: (Consejo de Bander) */
	/* 'Rango 11: Ejecutor Imperial (2500 Criminales + 2.000.000 Nobleza) */
	/* 'Rango 12: Protector del Reino (3000 Criminales + 3.000.000 Nobleza) */
	/* 'Rango 13: Avatar de la Justicia (3500 Criminales + 4.000.000 Nobleza + > lvl 35) */
	/* 'Rango 14: Guardián del Bien (4000 Criminales + 5.000.000 Nobleza + > lvl 36) */
	/* 'Rango 15: Campeón de la Luz (5000 Criminales + 6.000.000 Nobleza + > lvl 37) */

	case 0:
		retval = "Aprendiz";
		break;

	case 1:
		retval = "Escudero";
		break;

	case 2:
		retval = "Soldado";
		break;

	case 3:
		retval = "Sargento";
		break;

	case 4:
		retval = "Teniente";
		break;

	case 5:
		retval = "Comandante";
		break;

	case 6:
		retval = "Capitán";
		break;

	case 7:
		retval = "Senescal";
		break;

	case 8:
		retval = "Mariscal";
		break;

	case 9:
		retval = "Condestable";
		break;

	case 10:
		retval = "Ejecutor Imperial";
		break;

	case 11:
		retval = "Protector del Reino";
		break;

	case 12:
		retval = "Avatar de la Justicia";
		break;

	case 13:
		retval = "Guardián del Bien";
		break;

	default:
		retval = "Campeón de la Luz";
		break;
	}

	return retval;
}

void EnlistarCaos(int UserIndex) {
	/* '*************************************************** */
	/* 'Autor: Pablo (ToxicWaste) & Unknown (orginal version) */
	/* 'Last Modification: 27/11/2009 */
	/* '15/03/2009: ZaMa - No se puede enlistar el fundador de un clan con alineación neutral. */
	/* '27/11/2009: ZaMa - Ahora no se puede enlistar un miembro de un clan neutro, por ende saque la antifaccion. */
	/* 'Handles the entrance of users to the "Legión Oscura" */
	/* '*************************************************** */

	if (!criminal(UserIndex)) {
		WriteChatOverHead(UserIndex, "¡¡¡Lárgate de aquí, bufón!!!",
				(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
		return;
	}

	if (UserList[UserIndex].Faccion.FuerzasCaos == 1) {
		WriteChatOverHead(UserIndex, "¡¡¡Ya perteneces a la legión oscura!!!",
				(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
		return;
	}

	if (UserList[UserIndex].Faccion.ArmadaReal == 1) {
		WriteChatOverHead(UserIndex, "Las sombras reinarán en Argentum. ¡¡¡Fuera de aquí insecto real!!!",
				(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
		return;
	}

	/* '[Barrin 17-12-03] Si era miembro de la Armada Real no se puede enlistar */
	/* 'Tomamos el valor de ahí: ¿Recibio la experiencia para entrar? */
	if (UserList[UserIndex].Faccion.RecibioExpInicialReal == 1) {
		WriteChatOverHead(UserIndex, "No permitiré que ningún insecto real ingrese a mis tropas.",
				(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
		return;
	}
	/* '[/Barrin] */

	if (!criminal(UserIndex)) {
		WriteChatOverHead(UserIndex, "¡¡Ja ja ja!! Tú no eres bienvenido aquí asqueroso ciudadano.",
				(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
		return;
	}

	if (UserList[UserIndex].Faccion.CiudadanosMatados < 70) {
		WriteChatOverHead(UserIndex,
				"Para unirte a nuestras fuerzas debes matar al menos 70 ciudadanos, sólo has matado "
						+ vb6::CStr(UserList[UserIndex].Faccion.CiudadanosMatados) + ".",
				(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
		return;
	}

	if (UserList[UserIndex].Stats.ELV < 25) {
		WriteChatOverHead(UserIndex, "¡¡¡Para unirte a nuestras fuerzas debes ser al menos nivel 25!!!",
				(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
		return;
	}

	if (UserList[UserIndex].GuildIndex > 0) {
		if (GuildAlignment(UserList[UserIndex].GuildIndex) == "Neutral") {
			WriteChatOverHead(UserIndex,
					"¡¡¡Perteneces a un clan neutro, sal de él si quieres unirte a nuestras fuerzas!!!",
					(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
			return;
		}
	}

	if (UserList[UserIndex].Faccion.Reenlistadas > 4) {
		if (UserList[UserIndex].Faccion.Reenlistadas == 200) {
			WriteChatOverHead(UserIndex,
					"Has sido expulsado de las fuerzas oscuras y durante tu rebeldía has atacado a mi ejército. ¡Vete de aquí!",
					(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
		} else {
			WriteChatOverHead(UserIndex, "¡Has sido expulsado de las fuerzas oscuras demasiadas veces!",
					(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
		}
		return;
	}

	UserList[UserIndex].Faccion.Reenlistadas = UserList[UserIndex].Faccion.Reenlistadas + 1;
	UserList[UserIndex].Faccion.FuerzasCaos = 1;

	WriteChatOverHead(UserIndex,
			"¡¡¡Bienvenido al lado oscuro!!! Aquí tienes tus armaduras. Derrama sangre ciudadana y real, y serás recompensado, lo prometo.",
			(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);

	if (UserList[UserIndex].Faccion.RecibioArmaduraCaos == 0) {

		GiveFactionArmours(UserIndex, true);
		GiveExpReward(UserIndex, 0);

		UserList[UserIndex].Faccion.RecibioArmaduraCaos = 1;
		UserList[UserIndex].Faccion.NivelIngreso = UserList[UserIndex].Stats.ELV;
		UserList[UserIndex].Faccion.FechaIngreso = vb6::dateToString(vb6::Now());

		UserList[UserIndex].Faccion.RecibioExpInicialCaos = 1;
		UserList[UserIndex].Faccion.RecompensasCaos = 0;
		UserList[UserIndex].Faccion.NextRecompensa = 160;
	}

	/* 'Actualizamos la barca si esta navegando (NicoNZ) */
	if (UserList[UserIndex].flags.Navegando) {
		RefreshCharStatus(UserIndex);
	}

	LogEjercitoCaos(
			UserList[UserIndex].Name + " ingresó el " + UserList[UserIndex].Faccion.FechaIngreso
					+ " cuando era nivel " + vb6::CStr(UserList[UserIndex].Stats.ELV));
}

void RecompensaCaos(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Pablo (ToxicWaste) & Unknown (orginal version) */
	/* 'Last Modification: 15/04/2010 */
	/* 'Handles the way of gaining new ranks in the "Legión Oscura" */
	/* '15/04/2010: ZaMa - Agrego recompensas de oro y armaduras */
	/* '*************************************************** */
	int Ciudas;
	int Lvl;
	int NextRecom;

	Lvl = UserList[UserIndex].Stats.ELV;
	Ciudas = UserList[UserIndex].Faccion.CiudadanosMatados;
	NextRecom = UserList[UserIndex].Faccion.NextRecompensa;

	if (Ciudas < NextRecom) {
		WriteChatOverHead(UserIndex,
				"Mata " + vb6::CStr(NextRecom - Ciudas)
						+ " cuidadanos más para recibir la próxima recompensa.",
				(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
		return;
	}

	switch (NextRecom) {
	case 160:
		UserList[UserIndex].Faccion.RecompensasCaos = 1;
		UserList[UserIndex].Faccion.NextRecompensa = 300;

		break;

	case 300:
		UserList[UserIndex].Faccion.RecompensasCaos = 2;
		UserList[UserIndex].Faccion.NextRecompensa = 490;

		break;

	case 490:
		UserList[UserIndex].Faccion.RecompensasCaos = 3;
		UserList[UserIndex].Faccion.NextRecompensa = 740;

		break;

	case 740:
		UserList[UserIndex].Faccion.RecompensasCaos = 4;
		UserList[UserIndex].Faccion.NextRecompensa = 1100;

		break;

	case 1100:
		UserList[UserIndex].Faccion.RecompensasCaos = 5;
		UserList[UserIndex].Faccion.NextRecompensa = 1500;

		break;

	case 1500:
		if (Lvl < 27) {
			WriteChatOverHead(UserIndex,
					"Mataste suficientes ciudadanos, pero te faltan " + vb6::CStr(27 - Lvl)
							+ " niveles para poder recibir la próxima recompensa.",
					(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
			return;
		}
		UserList[UserIndex].Faccion.RecompensasCaos = 6;
		UserList[UserIndex].Faccion.NextRecompensa = 2010;

		break;

	case 2010:
		UserList[UserIndex].Faccion.RecompensasCaos = 7;
		UserList[UserIndex].Faccion.NextRecompensa = 2700;

		break;

	case 2700:
		UserList[UserIndex].Faccion.RecompensasCaos = 8;
		UserList[UserIndex].Faccion.NextRecompensa = 4600;

		break;

	case 4600:
		if (Lvl < 30) {
			WriteChatOverHead(UserIndex,
					"Mataste suficientes ciudadanos, pero te faltan " + vb6::CStr(30 - Lvl)
							+ " niveles para poder recibir la próxima recompensa.",
					(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
			return;
		}
		UserList[UserIndex].Faccion.RecompensasCaos = 9;
		UserList[UserIndex].Faccion.NextRecompensa = 5800;

		break;

	case 5800:
		if (Lvl < 31) {
			WriteChatOverHead(UserIndex,
					"Mataste suficientes ciudadanos, pero te faltan " + vb6::CStr(31 - Lvl)
							+ " niveles para poder recibir la próxima recompensa.",
					(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
			return;
		}
		UserList[UserIndex].Faccion.RecompensasCaos = 10;
		UserList[UserIndex].Faccion.NextRecompensa = 6990;

		break;

	case 6990:
		if (Lvl < 33) {
			WriteChatOverHead(UserIndex,
					"Mataste suficientes ciudadanos, pero te faltan " + vb6::CStr(33 - Lvl)
							+ " niveles para poder recibir la próxima recompensa.",
					(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
			return;
		}
		UserList[UserIndex].Faccion.RecompensasCaos = 11;
		UserList[UserIndex].Faccion.NextRecompensa = 8100;

		break;

	case 8100:
		if (Lvl < 35) {
			WriteChatOverHead(UserIndex,
					"Mataste suficientes ciudadanos, pero te faltan " + vb6::CStr(35 - Lvl)
							+ " niveles para poder recibir la próxima recompensa.",
					(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
			return;
		}
		UserList[UserIndex].Faccion.RecompensasCaos = 12;
		UserList[UserIndex].Faccion.NextRecompensa = 9300;

		break;

	case 9300:
		if (Lvl < 36) {
			WriteChatOverHead(UserIndex,
					"Mataste suficientes ciudadanos, pero te faltan " + vb6::CStr(36 - Lvl)
							+ " niveles para poder recibir la próxima recompensa.",
					(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
			return;
		}
		UserList[UserIndex].Faccion.RecompensasCaos = 13;
		UserList[UserIndex].Faccion.NextRecompensa = 11500;

		break;

	case 11500:
		if (Lvl < 37) {
			WriteChatOverHead(UserIndex,
					"Mataste suficientes ciudadanos, pero te faltan " + vb6::CStr(37 - Lvl)
							+ " niveles para poder recibir la próxima recompensa.",
					(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
			return;
		}
		UserList[UserIndex].Faccion.RecompensasCaos = 14;
		UserList[UserIndex].Faccion.NextRecompensa = 23000;

		break;

	case 23000:
		WriteChatOverHead(UserIndex,
				"Eres uno de mis mejores soldados. Mataste " + vb6::CStr(Ciudas)
						+ " ciudadanos . Tu única recompensa será la sangre derramada. ¡¡Continúa así!!",
				(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);
		return;

		break;

	default:
		return;

		break;
	}

	WriteChatOverHead(UserIndex, "¡¡¡Bien hecho " + TituloCaos(UserIndex) + ", aquí tienes tu recompensa!!!",
			(Npclist[UserList[UserIndex].flags.TargetNPC].Char.CharIndex), 0x00ffffff);

	/* ' Recompensas de armaduras y exp */
	GiveFactionArmours(UserIndex, true);
	GiveExpReward(UserIndex, UserList[UserIndex].Faccion.RecompensasCaos);

}

std::string TituloCaos(int UserIndex) {
	std::string retval;
	/* '*************************************************** */
	/* 'Autor: Unknown (orginal version) */
	/* 'Last Modification: 23/01/2007 Pablo (ToxicWaste) */
	/* 'Handles the titles of the members of the "Legión Oscura" */
	/* '*************************************************** */
	/* 'Rango 1: Acólito (70) */
	/* 'Rango 2: Alma Corrupta (160) */
	/* 'Rango 3: Paria (300) */
	/* 'Rango 4: Condenado (490) */
	/* 'Rango 5: Esbirro (740) */
	/* 'Rango 6: Sanguinario (1100) */
	/* 'Rango 7: Corruptor (1500 + lvl 27) */
	/* 'Rango 8: Heraldo Impio (2010) */
	/* 'Rango 9: Caballero de la Oscuridad (2700) */
	/* 'Rango 10: Senor del Miedo (4600 + lvl 30) */
	/* 'Rango 11: Ejecutor Infernal (5800 + lvl 31) */
	/* 'Rango 12: Protector del Averno (6990 + lvl 33) */
	/* 'Rango 13: Avatar de la Destrucción (8100 + lvl 35) */
	/* 'Rango 14: Guardián del Mal (9300 + lvl 36) */
	/* 'Rango 15: Campeón de la Oscuridad (11500 + lvl 37) */

	switch (UserList[UserIndex].Faccion.RecompensasCaos) {
	case 0:
		retval = "Acólito";
		break;

	case 1:
		retval = "Alma Corrupta";
		break;

	case 2:
		retval = "Paria";
		break;

	case 3:
		retval = "Condenado";
		break;

	case 4:
		retval = "Esbirro";
		break;

	case 5:
		retval = "Sanguinario";
		break;

	case 6:
		retval = "Corruptor";
		break;

	case 7:
		retval = "Heraldo Impío";
		break;

	case 8:
		retval = "Caballero de la Oscuridad";
		break;

	case 9:
		retval = "Senor del Miedo";
		break;

	case 10:
		retval = "Ejecutor Infernal";
		break;

	case 11:
		retval = "Protector del Averno";
		break;

	case 12:
		retval = "Avatar de la Destrucción";
		break;

	case 13:
		retval = "Guardián del Mal";
		break;

	default:
		retval = "Campeón de la Oscuridad";
		break;
	}

	return retval;
}
