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

#include "TCP.h"
#include <fstream>
#include "Crypto.h"

void DarCuerpo(int UserIndex) {
	/* '************************************************* */
	/* 'Author: Nacho (Integer) */
	/* 'Last modified: 14/03/2007 */
	/* 'Elije una cabeza para el usuario y le da un body */
	/* '************************************************* */
	int NewBody = 0;
	int UserRaza = 0;
	int UserGenero = 0;

	UserGenero = UserList[UserIndex].Genero;
	UserRaza = UserList[UserIndex].raza;

	switch (UserGenero) {
	case eGenero_Hombre:
		switch (UserRaza) {
		case eRaza_Humano:
			NewBody = 1;
			break;

		case eRaza_Elfo:
			NewBody = 2;
			break;

		case eRaza_Drow:
			NewBody = 3;
			break;

		case eRaza_Enano:
			NewBody = 300;
			break;

		case eRaza_Gnomo:
			NewBody = 300;
			break;
		}
		break;

	case eGenero_Mujer:
		switch (UserRaza) {
		case eRaza_Humano:
			NewBody = 1;
			break;

		case eRaza_Elfo:
			NewBody = 2;
			break;

		case eRaza_Drow:
			NewBody = 3;
			break;

		case eRaza_Gnomo:
			NewBody = 300;
			break;

		case eRaza_Enano:
			NewBody = 300;
			break;
		}
	}

	UserList[UserIndex].Char.body = NewBody;
}

bool ValidarCabeza(int UserRaza, int UserGenero, int Head) {
	bool retval = false;

	switch (UserGenero) {
	case eGenero_Hombre:
		switch (UserRaza) {
		case eRaza_Humano:
			retval = (Head >= HUMANO_H_PRIMER_CABEZA && Head <= HUMANO_H_ULTIMA_CABEZA);
			break;

		case eRaza_Elfo:
			retval = (Head >= ELFO_H_PRIMER_CABEZA && Head <= ELFO_H_ULTIMA_CABEZA);
			break;

		case eRaza_Drow:
			retval = (Head >= DROW_H_PRIMER_CABEZA && Head <= DROW_H_ULTIMA_CABEZA);
			break;

		case eRaza_Enano:
			retval = (Head >= ENANO_H_PRIMER_CABEZA && Head <= ENANO_H_ULTIMA_CABEZA);
			break;

		case eRaza_Gnomo:
			retval = (Head >= GNOMO_H_PRIMER_CABEZA && Head <= GNOMO_H_ULTIMA_CABEZA);
			break;
		}
		break;

	case eGenero_Mujer:
		switch (UserRaza) {
		case eRaza_Humano:
			retval = (Head >= HUMANO_M_PRIMER_CABEZA && Head <= HUMANO_M_ULTIMA_CABEZA);
			break;

		case eRaza_Elfo:
			retval = (Head >= ELFO_M_PRIMER_CABEZA && Head <= ELFO_M_ULTIMA_CABEZA);
			break;

		case eRaza_Drow:
			retval = (Head >= DROW_M_PRIMER_CABEZA && Head <= DROW_M_ULTIMA_CABEZA);
			break;

		case eRaza_Enano:
			retval = (Head >= ENANO_M_PRIMER_CABEZA && Head <= ENANO_M_ULTIMA_CABEZA);
			break;

		case eRaza_Gnomo:
			retval = (Head >= GNOMO_M_PRIMER_CABEZA && Head <= GNOMO_M_ULTIMA_CABEZA);
			break;
		}
	}

	return retval;
}

bool AsciiValidos(const std::string& cad) {
	for (auto car : cad) {
		car = std::tolower(car);
		if ((car < 97 || car > 122) && (car != 32)) {
			return false;
		}
	}
	return true;
}

bool Numeric(std::string cad) {
	for (auto car : cad) {
		if ((car < 48 || car > 57)) {
			return false;
		}
	}
	return true;
}

bool NombrePermitido(std::string Nombre) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int i;

	for (i = (1); i <= (vb6::UBound(ForbidenNames)); i++) {
		if (vb6::InStr(Nombre, ForbidenNames[i])) {
			retval = false;
			return retval;
		}
	}

	retval = true;

	return retval;
}

bool ValidateSkills(int UserIndex) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int LoopC;

	for (LoopC = (1); LoopC <= (NUMSKILLS); LoopC++) {
		if (UserList[UserIndex].Stats.UserSkills[LoopC] < 0) {
			if (UserList[UserIndex].Stats.UserSkills[LoopC] > 100) {
				UserList[UserIndex].Stats.UserSkills[LoopC] = 100;
			}
		}
	}

	retval = true;

	return retval;
}

void ConnectNewUser(int UserIndex, const std::string& Name, const std::string& Password, eRaza UserRaza,
		eGenero UserSexo, eClass UserClase, const std::string& UserEmail, eCiudad Hogar, int Head) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 3/12/2009 */
	/* 'Conecta un nuevo Usuario */
	/* '23/01/2007 Pablo (ToxicWaste) - Agregué ResetFaccion al crear usuario */
	/* '24/01/2007 Pablo (ToxicWaste) - Agregué el nuevo mana inicial de los magos. */
	/* '12/02/2007 Pablo (ToxicWaste) - Puse + 1 de const al Elfo normal. */
	/* '20/04/2007 Pablo (ToxicWaste) - Puse -1 de fuerza al Elfo. */
	/* '09/01/2008 Pablo (ToxicWaste) - Ahora los modificadores de Raza se controlan desde Balance.dat */
	/* '11/19/2009: Pato - Modifico la maná inicial del bandido. */
	/* '11/19/2009: Pato - Asigno los valores iniciales de ExpSkills y EluSkills. */
	/* '03/12/2009: Budi - Optimización del código. */
	/* '************************************************* */
	int i;

	if (!AsciiValidos(Name) || vb6::LenB(Name) == 0) {
		WriteErrorMsg(UserIndex, "Nombre inválido.");
		return;
	}

	if (RegistroListaBlancaEmails) {
		std::string cad = vb6::LCase(vb6::Trim(UserEmail));
		if (RegistroEmailsHabilitados.find(cad) == RegistroEmailsHabilitados.end()) {
			WriteErrorMsg(UserIndex, "Servidor en Beta cerrada, registro de personajes deshabilitado. Ingrese al sitio web www.dakara.com.ar para detalles.");
			CerrarUserIndex(UserIndex);
			return ;
		}
	}

	if (UserList[UserIndex].flags.UserLogged) {
		LogCheating(
				"El usuario " + UserList[UserIndex].Name + " ha intentado crear a " + Name + " desde la IP "
						+ UserList[UserIndex].ip);

		/* 'Kick player ( and leave character inside :D )! */
		CloseSocketSL(UserIndex);
		CerrarUserIndexIniciar(UserIndex);

		return;
	}

	/* '¿Existe el personaje? */
	if (FileExist(GetCharPath(Name), 0) == true) {
		WriteErrorMsg(UserIndex, "Ya existe el personaje.");
		return;
	}

	/* 'Tiró los dados antes de llegar acá?? */
	if (UserList[UserIndex].Stats.UserAtributos[eAtributos_Fuerza] == 0) {
		WriteErrorMsg(UserIndex, "Debe tirar los dados antes de poder crear un personaje.");
		return;
	}

	if (!ValidarCabeza(UserRaza, UserSexo, Head)) {
		LogCheating(
				"El usuario " + Name + " ha seleccionado la cabeza " + vb6::CStr(Head) + " desde la IP "
						+ UserList[UserIndex].ip);

		WriteErrorMsg(UserIndex, "Cabeza inválida, elija una cabeza seleccionable.");
		return;
	}

	UserList[UserIndex].flags.Muerto = 0;
	UserList[UserIndex].flags.Escondido = 0;

	UserList[UserIndex].Reputacion.AsesinoRep = 0;
	UserList[UserIndex].Reputacion.BandidoRep = 0;
	UserList[UserIndex].Reputacion.BurguesRep = 0;
	UserList[UserIndex].Reputacion.LadronesRep = 0;
	UserList[UserIndex].Reputacion.NobleRep = 1000;
	UserList[UserIndex].Reputacion.PlebeRep = 30;

	UserList[UserIndex].Reputacion.Promedio = 30 / 6;

	UserList[UserIndex].Name = Name;
	UserList[UserIndex].clase = UserClase;
	UserList[UserIndex].raza = UserRaza;
	UserList[UserIndex].Genero = UserSexo;
	UserList[UserIndex].email = UserEmail;
	UserList[UserIndex].Hogar = Hogar;

	/* '[Pablo (Toxic Waste) 9/01/08] */
	UserList[UserIndex].Stats.UserAtributos[eAtributos_Fuerza] =
			UserList[UserIndex].Stats.UserAtributos[eAtributos_Fuerza] + ModRaza[UserRaza].Fuerza;
	UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad] =
			UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad] + ModRaza[UserRaza].Agilidad;
	UserList[UserIndex].Stats.UserAtributos[eAtributos_Inteligencia] =
			UserList[UserIndex].Stats.UserAtributos[eAtributos_Inteligencia] + ModRaza[UserRaza].Inteligencia;
	UserList[UserIndex].Stats.UserAtributos[eAtributos_Carisma] =
			UserList[UserIndex].Stats.UserAtributos[eAtributos_Carisma] + ModRaza[UserRaza].Carisma;
	UserList[UserIndex].Stats.UserAtributos[eAtributos_Constitucion] =
			UserList[UserIndex].Stats.UserAtributos[eAtributos_Constitucion] + ModRaza[UserRaza].Constitucion;
	/* '[/Pablo (Toxic Waste)] */

	for (i = (1); i <= (NUMSKILLS); i++) {
		UserList[UserIndex].Stats.UserSkills[i] = 0;
		CheckEluSkill(UserIndex, i, true);
	}

	UserList[UserIndex].Stats.SkillPts = 10;

	UserList[UserIndex].Char.heading = eHeading_SOUTH;

	DarCuerpo(UserIndex);
	UserList[UserIndex].Char.Head = Head;

	UserList[UserIndex].OrigChar = UserList[UserIndex].Char;

	int MiInt;
	MiInt = RandomNumber(1, UserList[UserIndex].Stats.UserAtributos[eAtributos_Constitucion] / 3);

	UserList[UserIndex].Stats.MaxHp = 15 + MiInt;
	UserList[UserIndex].Stats.MinHp = 15 + MiInt;

	MiInt = RandomNumber(1, UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad] / 6);
	if (MiInt == 1) {
		MiInt = 2;
	}

	UserList[UserIndex].Stats.MaxSta = 20 * MiInt;
	UserList[UserIndex].Stats.MinSta = 20 * MiInt;

	UserList[UserIndex].Stats.MaxAGU = 100;
	UserList[UserIndex].Stats.MinAGU = 100;

	UserList[UserIndex].Stats.MaxHam = 100;
	UserList[UserIndex].Stats.MinHam = 100;

	/* '<-----------------MANA-----------------------> */
	/* 'Cambio en mana inicial (ToxicWaste) */
	if (UserClase == eClass_Mage) {
		MiInt = UserList[UserIndex].Stats.UserAtributos[eAtributos_Inteligencia] * 3;
		UserList[UserIndex].Stats.MaxMAN = MiInt;
		UserList[UserIndex].Stats.MinMAN = MiInt;
	} else if (UserClase == eClass_Cleric || UserClase == eClass_Druid || UserClase == eClass_Bard
			|| UserClase == eClass_Assasin) {
		UserList[UserIndex].Stats.MaxMAN = 50;
		UserList[UserIndex].Stats.MinMAN = 50;
		/* 'Mana Inicial del Bandido (ToxicWaste) */
	} else if (UserClase == eClass_Bandit) {
		UserList[UserIndex].Stats.MaxMAN = 50;
		UserList[UserIndex].Stats.MinMAN = 50;
	} else {
		UserList[UserIndex].Stats.MaxMAN = 0;
		UserList[UserIndex].Stats.MinMAN = 0;
	}

	if (UserClase == eClass_Mage || UserClase == eClass_Cleric || UserClase == eClass_Druid
			|| UserClase == eClass_Bard || UserClase == eClass_Assasin) {
		UserList[UserIndex].Stats.UserHechizos[1] = 2;

		if (UserClase == eClass_Druid) {
			UserList[UserIndex].Stats.UserHechizos[2] = 46;
		}
	}

	UserList[UserIndex].Stats.MaxHIT = 2;
	UserList[UserIndex].Stats.MinHIT = 1;

	UserList[UserIndex].Stats.GLD = 0;

	UserList[UserIndex].Stats.Exp = 0;
	UserList[UserIndex].Stats.ELU = 300;
	UserList[UserIndex].Stats.ELV = 1;

	/* '???????????????? INVENTARIO ¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿ */
	int Slot;
	bool IsPaladin;

	IsPaladin = UserClase == eClass_Paladin;

	/* 'Pociones Rojas (Newbie) */
	Slot = 1;
	UserList[UserIndex].Invent.Object[Slot].ObjIndex = 857;
	UserList[UserIndex].Invent.Object[Slot].Amount = 200;

	/* 'Pociones azules (Newbie) */
	if (UserList[UserIndex].Stats.MaxMAN > 0 || IsPaladin) {
		Slot = Slot + 1;
		UserList[UserIndex].Invent.Object[Slot].ObjIndex = 856;
		UserList[UserIndex].Invent.Object[Slot].Amount = 200;

	} else {
		/* 'Pociones amarillas (Newbie) */
		Slot = Slot + 1;
		UserList[UserIndex].Invent.Object[Slot].ObjIndex = 855;
		UserList[UserIndex].Invent.Object[Slot].Amount = 100;

		/* 'Pociones verdes (Newbie) */
		Slot = Slot + 1;
		UserList[UserIndex].Invent.Object[Slot].ObjIndex = 858;
		UserList[UserIndex].Invent.Object[Slot].Amount = 50;

	}

	/* ' Ropa (Newbie) */
	Slot = Slot + 1;
	switch (UserRaza) {
	case eRaza_Humano:
		UserList[UserIndex].Invent.Object[Slot].ObjIndex = 463;
		break;

	case eRaza_Elfo:
		UserList[UserIndex].Invent.Object[Slot].ObjIndex = 464;
		break;

	case eRaza_Drow:
		UserList[UserIndex].Invent.Object[Slot].ObjIndex = 465;
		break;

	case eRaza_Enano:
		UserList[UserIndex].Invent.Object[Slot].ObjIndex = 466;
		break;

	case eRaza_Gnomo:
		UserList[UserIndex].Invent.Object[Slot].ObjIndex = 466;
		break;

	default:
		break;
	}

	/* ' Equipo ropa */
	UserList[UserIndex].Invent.Object[Slot].Amount = 1;
	UserList[UserIndex].Invent.Object[Slot].Equipped = 1;

	UserList[UserIndex].Invent.ArmourEqpSlot = Slot;
	UserList[UserIndex].Invent.ArmourEqpObjIndex = UserList[UserIndex].Invent.Object[Slot].ObjIndex;

	/* 'Arma (Newbie) */
	Slot = Slot + 1;
	switch (UserClase) {
	case eClass_Hunter:
		/* ' Arco (Newbie) */
		UserList[UserIndex].Invent.Object[Slot].ObjIndex = 859;
		break;

	case eClass_Worker:
		/* ' Herramienta (Newbie) */
		UserList[UserIndex].Invent.Object[Slot].ObjIndex = RandomNumber(561, 565);
		break;

	default:
		/* ' Daga (Newbie) */
		UserList[UserIndex].Invent.Object[Slot].ObjIndex = 460;
		break;
	}

	/* ' Equipo arma */
	UserList[UserIndex].Invent.Object[Slot].Amount = 1;
	UserList[UserIndex].Invent.Object[Slot].Equipped = 1;

	UserList[UserIndex].Invent.WeaponEqpObjIndex = UserList[UserIndex].Invent.Object[Slot].ObjIndex;
	UserList[UserIndex].Invent.WeaponEqpSlot = Slot;

	UserList[UserIndex].Char.WeaponAnim = GetWeaponAnim(UserIndex,
			UserList[UserIndex].Invent.WeaponEqpObjIndex);

	/* ' Municiones (Newbie) */
	if (UserClase == eClass_Hunter) {
		Slot = Slot + 1;
		UserList[UserIndex].Invent.Object[Slot].ObjIndex = 860;
		UserList[UserIndex].Invent.Object[Slot].Amount = 150;

		/* ' Equipo flechas */
		UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
		UserList[UserIndex].Invent.MunicionEqpSlot = Slot;
		UserList[UserIndex].Invent.MunicionEqpObjIndex = 860;
	}

	/* ' Manzanas (Newbie) */
	Slot = Slot + 1;
	UserList[UserIndex].Invent.Object[Slot].ObjIndex = 467;
	UserList[UserIndex].Invent.Object[Slot].Amount = 100;

	/* ' Jugos (Nwbie) */
	Slot = Slot + 1;
	UserList[UserIndex].Invent.Object[Slot].ObjIndex = 468;
	UserList[UserIndex].Invent.Object[Slot].Amount = 100;

	/* ' Sin casco y escudo */
	UserList[UserIndex].Char.ShieldAnim = NingunEscudo;
	UserList[UserIndex].Char.CascoAnim = NingunCasco;

	/* ' Total Items */
	UserList[UserIndex].Invent.NroItems = Slot;

	/* # IF ConUpTime THEN */
	UserList[UserIndex].LogOnTime = vb6::Now();
	UserList[UserIndex].UpTime = 0;
	/* # END IF */

	/* 'Valores Default de facciones al Activar nuevo usuario */
	ResetFacciones(UserIndex);

	WriteSaltedPasswordUser(Name, Password);

	SaveUser(UserIndex, GetCharPath(Name));

	LogMain("Se ha creado el personaje " + Name + " desde IP=" + UserList[UserIndex].ip);

	/* 'Open User */
	ConnectUser(UserIndex, Name, Password);

}

/* # IF UsarQueSocket = 1 OR UsarQueSocket = 2 THEN */

void CloseSocket(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */
	
	// std::cerr << "CloseSocket" << std::endl;
	
	if (UserIndexSocketValido(UserIndex)) {
		CloseSocketSL(UserIndex);
	}

	/* 'Es el mismo user al que está revisando el centinela?? */
	/* 'IMPORTANTE!!! hacerlo antes de resetear así todavía sabemos el nombre del user */
	/* ' y lo podemos loguear */
	int CentinelaIndex;
	CentinelaIndex = UserList[UserIndex].flags.CentinelaIndex;

	if (CentinelaIndex != 0) {
		CentinelaUserLogout(CentinelaIndex);
	}

	/* 'mato los comercios seguros */
	if (UserList[UserIndex].ComUsu.DestUsu > 0) {
		if (UserList[UserList[UserIndex].ComUsu.DestUsu].flags.UserLogged) {
			if (UserList[UserList[UserIndex].ComUsu.DestUsu].ComUsu.DestUsu == UserIndex) {
				WriteConsoleMsg(UserList[UserIndex].ComUsu.DestUsu, "Comercio cancelado por el otro usuario",
						FontTypeNames_FONTTYPE_TALK);
				FinComerciarUsu(UserList[UserIndex].ComUsu.DestUsu);
				FlushBuffer(UserList[UserIndex].ComUsu.DestUsu);
			}
		}
	}

	/* 'Empty buffer for reuse */
	// UserList[UserIndex].incomingData->ReadBinaryFixed(UserList[UserIndex].incomingData->length());

	if (UserList[UserIndex].flags.UserLogged) {
		if (NumUsers > 0) {
			NumUsers = NumUsers - 1;
		}
		CloseUser(UserIndex);

		// EstadisticasWeb->Informar(EstaNotificaciones_CANTIDAD_ONLINE, NumUsers);
	} else {
		ResetUserSlot(UserIndex);
	}

//	UserList[UserIndex].ConnID = -1;
//	UserList[UserIndex].ConnIDValida = false;

	if (UserIndex == LastUser) {
		LastUser--;
		while (!UserIndexSocketValido(LastUser) && (LastUser >0)) {
			LastUser = LastUser - 1;
		}
	}
}

/* '[Alejo-21-5]: Cierra un socket sin limpiar el slot */
void CloseSocketSL(int UserIndex) {
	if (UserIndexSocketValido(UserIndex)) {
		WSApiCloseSocket(UserIndex);
	}
}

void CerrarUserIndex(int UserIndex) {
	if (UserList[UserIndex].flags.UserLogged) {
		CerrarUserIndexIniciar(UserIndex);
	} else {
		CloseSocket(UserIndex);
	}
}

/* '' */
/* ' Send an string to a Slot */
/* ' */
/* ' @param userIndex The index of the User */
/* ' @param Datos The string that will be send */
/* ' @remarks If UsarQueSocket is 3 it won`t use the clsByteQueue */

int EnviarDatosASlot(int UserIndex, const std::string & Datos) {
	return EnviarDatosASlot(UserIndex, Datos.c_str(), Datos.length());
}

int EnviarDatosASlot(int UserIndex, const std::vector<std::int8_t>& sndData) {
	return EnviarDatosASlot(UserIndex, reinterpret_cast<const char*>(sndData.data()), sndData.size());
}

int EnviarDatosASlot(int UserIndex, const char* datos, std::size_t datos_len) {
	int retval = 0;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 01/10/07 */
	/* 'Last Modified By: Lucas Tavolaro Ortiz (Tavo) */
	/* 'Now it uses the clsByteQueue class and don`t make a FIFO Queue of String */
	/* '*************************************************** */

	/* '********************************************** */
	/* # IF UsarQueSocket = 1 THEN */

	if (!UserIndexSocketValido(UserIndex)) {
		return 0;
	}

	WsApiEnviar(UserIndex, datos, datos_len);

	return retval;
}

bool EstaPCarea(int index, int Index2) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int X;
	int Y;
	for (Y = (UserList[index].Pos.Y - MinYBorder + 1); Y <= (UserList[index].Pos.Y + MinYBorder - 1); Y++) {
		for (X = (UserList[index].Pos.X - MinXBorder + 1); X <= (UserList[index].Pos.X + MinXBorder - 1);
				X++) {

			if (MapData[UserList[index].Pos.Map][X][Y].UserIndex == Index2) {
				retval = true;
				return retval;
			}

		}
	}
	retval = false;
	return retval;
}

bool HayPCarea(struct WorldPos Pos) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int X;
	int Y;
	for (Y = (Pos.Y - MinYBorder + 1); Y <= (Pos.Y + MinYBorder - 1); Y++) {
		for (X = (Pos.X - MinXBorder + 1); X <= (Pos.X + MinXBorder - 1); X++) {
			if (X > 0 && Y > 0 && X < 101 && Y < 101) {
				if (MapData[Pos.Map][X][Y].UserIndex > 0) {
					retval = true;
					return retval;
				}
			}
		}
	}
	retval = false;
	return retval;
}

bool HayOBJarea(struct WorldPos Pos, int ObjIndex) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int X;
	int Y;
	for (Y = (Pos.Y - MinYBorder + 1); Y <= (Pos.Y + MinYBorder - 1); Y++) {
		for (X = (Pos.X - MinXBorder + 1); X <= (Pos.X + MinXBorder - 1); X++) {
			if (MapData[Pos.Map][X][Y].ObjInfo.ObjIndex == ObjIndex) {
				retval = true;
				return retval;
			}

		}
	}
	retval = false;
	return retval;
}
bool ValidateChr(int UserIndex) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	retval = UserList[UserIndex].Char.Head != 0 && UserList[UserIndex].Char.body != 0
			&& ValidateSkills(UserIndex);

	return retval;
}

bool ConnectUser(int UserIndex, const std::string & Name, const std::string & Password) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Autor: Unknown (orginal version) */
	/* 'Last Modification: 24/07/2010 (ZaMa) */
	/* '26/03/2009: ZaMa - Agrego por default que el color de dialogo de los dioses, sea como el de su nick. */
	/* '12/06/2009: ZaMa - Agrego chequeo de nivel al loguear */
	/* '14/09/2009: ZaMa - Ahora el usuario esta protegido del ataque de npcs al loguear */
	/* '11/27/2009: Budi - Se envian los InvStats del personaje y su Fuerza y Agilidad */
	/* '03/12/2009: Budi - Optimización del código */
	/* '24/07/2010: ZaMa - La posicion de comienzo es namehuak, como se habia definido inicialmente. */
	/* '*************************************************** */
	std::string tStr;

	if (UserList[UserIndex].flags.UserLogged) {
		LogCheating(
				"El usuario " + UserList[UserIndex].Name + " ha intentado loguear a " + Name + " desde la IP "
						+ UserList[UserIndex].ip);
		/* 'Kick player ( and leave character inside :D )! */
		CloseSocketSL(UserIndex);
		CerrarUserIndexIniciar(UserIndex);
		return retval;
	}

	/* 'Reseteamos los FLAGS */
	UserList[UserIndex].flags.Escondido = 0;
	UserList[UserIndex].flags.TargetNPC = 0;
	UserList[UserIndex].flags.TargetNpcTipo = eNPCType_Comun;
	UserList[UserIndex].flags.TargetObj = 0;
	UserList[UserIndex].flags.TargetUser = 0;
	UserList[UserIndex].Char.FX = 0;

	/* 'Controlamos no pasar el maximo de usuarios */
	if (NumUsers >= MaxUsers) {
		WriteErrorMsg(UserIndex,
				"El servidor ha alcanzado el máximo de usuarios soportado, por favor vuelva a intertarlo más tarde.");
		FlushBuffer(UserIndex);
		CloseSocket(UserIndex);
		return retval;
	}

	/* '¿Este IP ya esta conectado? */
	if (AllowMultiLogins == 0) {
		if (CheckForSameIP(UserIndex, UserList[UserIndex].ip) == true) {
			WriteErrorMsg(UserIndex, "No es posible usar más de un personaje al mismo tiempo.");
			FlushBuffer(UserIndex);
			CloseSocket(UserIndex);
			return retval;
		}
	}

	/* '¿Existe el personaje? */
	if (!FileExist(GetCharPath(Name), 0)) {
		WriteErrorMsg(UserIndex, "El personaje no existe.");
		FlushBuffer(UserIndex);
		CloseSocket(UserIndex);
		return retval;
	}

	/* La primera vez que el pj se logea le salteamos la password */
	std::string FilePasswordPlain = GetVar(GetCharPath(Name), "INIT", "Password");

	if (FilePasswordPlain.size() > 0) {
		WriteSaltedPasswordUser(Name, FilePasswordPlain);
	}

	if (!CheckPasswordUser(Name, Password)) {
		WriteErrorMsg(UserIndex, "Password incorrecto.");
		FlushBuffer(UserIndex);
		CloseSocket(UserIndex);
		return retval;
	}

#if 0
	/* '¿Ya esta conectado el personaje? */
	if (CheckForSameName(Name)) {
		if (UserList[NameIndex(Name)].Counters.Saliendo) {
			WriteErrorMsg(UserIndex, "El usuario está saliendo.");
		} else {
			WriteErrorMsg(UserIndex, "Perdón, un usuario con el mismo nombre se ha logueado.");
		}
		FlushBuffer(UserIndex);
		CloseSocket(UserIndex);
		return retval;
	}
#else
	/* '¿Ya esta conectado el personaje? */
	int OtherUserIndex;
	if (CheckForSameName(Name, OtherUserIndex)) {
		WriteErrorMsg(UserIndex, "Tu personaje ya estaba logeado desde otra ubicacion, fue echado.");
		FlushBuffer(UserIndex);

		CloseSocket(OtherUserIndex);
		return retval;
	}
#endif

	/* 'Reseteamos los privilegios */
	UserResetPrivilegios(UserIndex);

	/* 'Vemos que clase de user es (se lo usa para setear los privilegios al loguear el PJ) */
	if (EsAdmin(Name)) {
		UserAsignarPrivilegios(UserIndex, PlayerType_Admin);
		LogGM(Name, "Se conecto con ip:" + UserList[UserIndex].ip);
	} else if (EsDios(Name)) {
		UserAsignarPrivilegios(UserIndex, PlayerType_Dios);
		LogGM(Name, "Se conecto con ip:" + UserList[UserIndex].ip);
	} else if (EsSemiDios(Name)) {
		UserAsignarPrivilegios(UserIndex, PlayerType_SemiDios);
		UserList[UserIndex].flags.PrivEspecial = EsGmEspecial(Name);
		LogGM(Name, "Se conecto con ip:" + UserList[UserIndex].ip);
	} else if (EsConsejero(Name)) {
		UserAsignarPrivilegios(UserIndex, PlayerType_Consejero);
		LogGM(Name, "Se conecto con ip:" + UserList[UserIndex].ip);
	} else {
		UserAsignarPrivilegios(UserIndex, PlayerType_User);

		UserList[UserIndex].flags.AdminPerseguible = true;
	}

	/* 'Add RM flag if needed */
	if (EsRolesMaster(Name)) {
		UserAsignarPrivilegios(UserIndex, PlayerType_RoleMaster);
	}

	if (ServerSoloGMs > 0) {
		if (!EsGm(UserIndex)) {
			WriteErrorMsg(UserIndex,
					"Servidor restringido a administradores. Por favor reintente en unos momentos.");
			FlushBuffer(UserIndex);
			CloseSocket(UserIndex);
			return retval;
		}
	}

	/* 'Cargamos el personaje */
	std::shared_ptr<clsIniManager> Leer;
	Leer.reset(new clsIniManager());

	Leer->Initialize(GetCharPath(Name));

	/* 'Cargamos los datos del personaje */
	LoadUserInit(UserIndex, Leer);

	LoadUserStats(UserIndex, Leer);

	if (!ValidateChr(UserIndex)) {
		WriteErrorMsg(UserIndex, "Error en el personaje.");
		CloseSocket(UserIndex);
		return retval;
	}

	LoadUserReputacion(UserIndex, Leer);

	Leer.reset();

	if (UserList[UserIndex].Invent.EscudoEqpSlot == 0) {
		UserList[UserIndex].Char.ShieldAnim = NingunEscudo;
	}
	if (UserList[UserIndex].Invent.CascoEqpSlot == 0) {
		UserList[UserIndex].Char.CascoAnim = NingunCasco;
	}
	if (UserList[UserIndex].Invent.WeaponEqpSlot == 0) {
		UserList[UserIndex].Char.WeaponAnim = NingunArma;
	}

	if (UserList[UserIndex].Invent.MochilaEqpSlot > 0) {
		UserList[UserIndex].CurrentInventorySlots =
				MAX_NORMAL_INVENTORY_SLOTS
						+ ObjData[UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.MochilaEqpSlot].ObjIndex].MochilaType
								* 5;
	} else {
		UserList[UserIndex].CurrentInventorySlots = MAX_NORMAL_INVENTORY_SLOTS;
	}
	if (UserList[UserIndex].flags.Muerto == 0) {
		UserList[UserIndex].flags.SeguroResu = false;
		WriteMultiMessage(UserIndex, eMessages_ResuscitationSafeOff);
	} else {
		UserList[UserIndex].flags.SeguroResu = true;
		WriteMultiMessage(UserIndex, eMessages_ResuscitationSafeOn);
	}

	UpdateUserInv(true, UserIndex, 0);
	UpdateUserHechizos(true, UserIndex, 0);

	if (UserList[UserIndex].flags.Paralizado) {
		WriteParalizeOK(UserIndex);
	}

	int mapa;
	mapa = UserList[UserIndex].Pos.Map;

	/* 'Posicion de comienzo */
	if (mapa == 0) {
		UserList[UserIndex].Pos = Nemahuak;
		mapa = Nemahuak.Map;
	} else {

		if (!MapaValido(mapa)) {
			WriteErrorMsg(UserIndex, "El PJ se encuenta en un mapa inválido.");
			CloseSocket(UserIndex);
			return retval;
		}

		/* ' If map has different initial coords, update it */
		int StartMap;
		StartMap = MapInfo[mapa].StartPos.Map;
		if (StartMap != 0) {
			if (MapaValido(StartMap)) {
				UserList[UserIndex].Pos = MapInfo[mapa].StartPos;
				mapa = StartMap;
			}
		}

	}

	/* 'Tratamos de evitar en lo posible el "Telefrag". Solo 1 intento de loguear en pos adjacentes. */
	/* 'Codigo por Pablo (ToxicWaste) y revisado por Nacho (Integer), corregido para que realmetne ande y no tire el server por Juan Martín Sotuyo Dodero (Maraxus) */
	if (MapData[mapa][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].UserIndex != 0
			|| MapData[mapa][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].NpcIndex != 0) {
		bool FoundPlace;
		bool esAgua;
		int tX;
		int tY;

		FoundPlace = false;
		esAgua = HayAgua(mapa, UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y);

		for (tY = (UserList[UserIndex].Pos.Y - 1); tY <= (UserList[UserIndex].Pos.Y + 1); tY++) {
			for (tX = (UserList[UserIndex].Pos.X - 1); tX <= (UserList[UserIndex].Pos.X + 1); tX++) {
				if (esAgua) {
					/* 'reviso que sea pos legal en agua, que no haya User ni NPC para poder loguear. */
					if (LegalPos(mapa, tX, tY, true, false)) {
						FoundPlace = true;
						break;
					}
				} else {
					/* 'reviso que sea pos legal en tierra, que no haya User ni NPC para poder loguear. */
					if (LegalPos(mapa, tX, tY, false, true)) {
						FoundPlace = true;
						break;
					}
				}
			}

			if (FoundPlace) {
				break;
			}
		}

		/* 'Si encontramos un lugar, listo, nos quedamos ahi */
		if (FoundPlace) {
			UserList[UserIndex].Pos.X = tX;
			UserList[UserIndex].Pos.Y = tY;
		} else {
			/* 'Si no encontramos un lugar, sacamos al usuario que tenemos abajo, y si es un NPC, lo pisamos. */
			if (MapData[mapa][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].UserIndex != 0) {
				/* 'Si no encontramos lugar, y abajo teniamos a un usuario, lo pisamos y cerramos su comercio seguro */
				if (UserList[MapData[mapa][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].UserIndex].ComUsu.DestUsu
						> 0) {
					/* 'Le avisamos al que estaba comerciando que se tuvo que ir. */
					if (UserList[UserList[MapData[mapa][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].UserIndex].ComUsu.DestUsu].flags.UserLogged) {
						FinComerciarUsu(
								UserList[MapData[mapa][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].UserIndex].ComUsu.DestUsu);
						WriteConsoleMsg(
								UserList[MapData[mapa][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].UserIndex].ComUsu.DestUsu,
								"Comercio cancelado. El otro usuario se ha desconectado.",
								FontTypeNames_FONTTYPE_TALK);
						FlushBuffer(
								UserList[MapData[mapa][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].UserIndex].ComUsu.DestUsu);
					}
					/* 'Lo sacamos. */
					if (UserList[MapData[mapa][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].UserIndex].flags.UserLogged) {
						FinComerciarUsu(
								MapData[mapa][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].UserIndex);
						WriteErrorMsg(
								MapData[mapa][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].UserIndex,
								"Alguien se ha conectado donde te encontrabas, por favor reconéctate...");
						FlushBuffer(
								MapData[mapa][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].UserIndex);
					}
				}

				CloseSocket(MapData[mapa][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].UserIndex);
			}
		}
	}

	/* 'Nombre de sistema */
	UserList[UserIndex].Name = Name;

	/* 'Por default los nombres son visibles */
	UserList[UserIndex].showName = true;

	/* 'If in the water, and has a boat, equip it! */
	if (UserList[UserIndex].Invent.BarcoObjIndex > 0
			&& (HayAgua(mapa, UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y)
					|| BodyIsBoat(UserList[UserIndex].Char.body))) {

		UserList[UserIndex].Char.Head = 0;
		if (UserList[UserIndex].flags.Muerto == 0) {
			ToggleBoatBody(UserIndex);
		} else {
			UserList[UserIndex].Char.body = iFragataFantasmal;
			UserList[UserIndex].Char.ShieldAnim = NingunEscudo;
			UserList[UserIndex].Char.WeaponAnim = NingunArma;
			UserList[UserIndex].Char.CascoAnim = NingunCasco;
		}

		UserList[UserIndex].flags.Navegando = 1;
	}

	/* 'Info */
	/* 'Enviamos el User index */
	WriteUserIndexInServer(UserIndex);
	/* 'Carga el mapa */
	WriteChangeMap(UserIndex, UserList[UserIndex].Pos.Map, MapInfo[UserList[UserIndex].Pos.Map].MapVersion);
	WritePlayMidi(UserIndex, MapInfo[UserList[UserIndex].Pos.Map].Music);

	if (UserTienePrivilegio(UserIndex, PlayerType_Dios)) {
		UserList[UserIndex].flags.ChatColor = vb6::RGBtoInt(250, 250, 150);
	} else if (!UserTieneAlgunPrivilegios(UserIndex, PlayerType_User, PlayerType_ChaosCouncil, PlayerType_RoyalCouncil)) {
		UserList[UserIndex].flags.ChatColor = vb6::RGBtoInt(0, 255, 0);
	} else if (UserTienePrivilegio(UserIndex, PlayerType_RoyalCouncil)) {
		UserList[UserIndex].flags.ChatColor = vb6::RGBtoInt(0, 255, 255);
	} else if (UserTienePrivilegio(UserIndex, PlayerType_ChaosCouncil)) {
		UserList[UserIndex].flags.ChatColor = vb6::RGBtoInt(255, 128, 64);
	} else {
		UserList[UserIndex].flags.ChatColor = 0x00ffffff;
	}

	/* ''[EL OSO]: TRAIGO ESTO ACA ARRIBA PARA DARLE EL IP! */
	/* # IF ConUpTime THEN */
	UserList[UserIndex].LogOnTime = vb6::Now();
	/* # END IF */

	/* 'Crea  el personaje del usuario (hubo algun error) */
	if (!MakeUserChar(true, UserList[UserIndex].Pos.Map, UserIndex, UserList[UserIndex].Pos.Map,
			UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y)) {
		return retval;
	}

	if (!UserTieneAlgunPrivilegios(UserIndex, PlayerType_User, PlayerType_RoleMaster)) {
		DoAdminInvisible(UserIndex);
		UserList[UserIndex].flags.SendDenounces = true;
	}

	WriteUserCharIndexInServer(UserIndex);
	/* ''[/el oso] */

	DoTileEvents(UserIndex, UserList[UserIndex].Pos.Map, UserList[UserIndex].Pos.X,
			UserList[UserIndex].Pos.Y);

	CheckUserLevel(UserIndex);
	WriteUpdateUserStats(UserIndex);

	WriteUpdateHungerAndThirst(UserIndex);
	WriteUpdateStrenghtAndDexterity(UserIndex);

	SendMOTD(UserIndex);

    if (EnviarPopupOfTheDay) {
        SendData(SendTarget_ToUserIndex, UserIndex, dakara::protocol::server::BuildShowMessageBox(PopupOfTheDayMessage));
    }

	if (haciendoBK) {
		WritePauseToggle(UserIndex);
		WriteConsoleMsg(UserIndex,
				"Servidor> Por favor espera algunos segundos, el WorldSave está ejecutándose.",
				FontTypeNames_FONTTYPE_SERVER);
	}

	if (EnPausa) {
		WritePauseToggle(UserIndex);
		WriteConsoleMsg(UserIndex,
				"Servidor> Lo sentimos mucho pero el servidor se encuentra actualmente detenido. Intenta ingresar más tarde.",
				FontTypeNames_FONTTYPE_SERVER);
	}

	if (EnTesting && UserList[UserIndex].Stats.ELV >= 18) {
		WriteErrorMsg(UserIndex,
				"Servidor en Testing por unos minutos, conectese con PJs de nivel menor a 18. No se conecte con Pjs que puedan resultar importantes por ahora pues pueden arruinarse.");
		FlushBuffer(UserIndex);
		CloseSocket(UserIndex);
		return retval;
	}

	/* 'Actualiza el Num de usuarios */
	/* 'DE ACA EN ADELANTE GRABA EL CHARFILE, OJO! */
	NumUsers = NumUsers + 1;
	UserList[UserIndex].flags.UserLogged = true;

	/* 'usado para borrar Pjs */
	WriteVar(GetCharPath(UserList[UserIndex].Name), "INIT", "Logged", "1");

	//EstadisticasWeb->Informar(EstaNotificaciones_CANTIDAD_ONLINE, NumUsers);

	MapInfo[UserList[UserIndex].Pos.Map].NumUsers = MapInfo[UserList[UserIndex].Pos.Map].NumUsers + 1;

	if (UserList[UserIndex].Stats.SkillPts > 0) {
		WriteSendSkills(UserIndex);
		WriteLevelUp(UserIndex, UserList[UserIndex].Stats.SkillPts);
	}

	if (NumUsers > RECORDusuarios) {
		SendData(SendTarget_ToAll, 0,
				dakara::protocol::server::BuildConsoleMsg(
						vb6::CStr("RECORD de usuarios conectados simultaneamente. Hay ") + vb6::CStr(NumUsers) + " usuarios.",
						FontTypeNames_FONTTYPE_INFO));
		RECORDusuarios = NumUsers;
		WriteVar(GetDatPath(DATPATH::Stats), "INIT", "RECORD", vb6::str(RECORDusuarios));

		//EstadisticasWeb->Informar(EstaNotificaciones_RECORD_USUARIOS, RECORDusuarios);
	}

	if (UserList[UserIndex].NroMascotas > 0 && MapInfo[UserList[UserIndex].Pos.Map].Pk) {
		int i;
		for (i = (1); i <= (MAXMASCOTAS); i++) {
			if (UserList[UserIndex].MascotasType[i] > 0) {
				UserList[UserIndex].MascotasIndex[i] = SpawnNpc(UserList[UserIndex].MascotasType[i],
						UserList[UserIndex].Pos, true, true);

				if (UserList[UserIndex].MascotasIndex[i] > 0) {
					Npclist[UserList[UserIndex].MascotasIndex[i]].MaestroUser = UserIndex;
					FollowAmo(UserList[UserIndex].MascotasIndex[i]);
				} else {
					UserList[UserIndex].MascotasIndex[i] = 0;
				}
			}
		}
	}

	if (UserList[UserIndex].flags.Navegando == 1) {
		WriteNavigateToggle(UserIndex);
	}

	if (criminal(UserIndex)) {
		/* 'Call WriteSafeModeOff(UserIndex) */
		WriteMultiMessage(UserIndex, eMessages_SafeModeOff);
		UserList[UserIndex].flags.Seguro = false;
	} else {
		UserList[UserIndex].flags.Seguro = true;
		/* 'Call WriteSafeModeOn(UserIndex) */
		WriteMultiMessage(UserIndex, eMessages_SafeModeOn);
	}

	if (UserList[UserIndex].GuildIndex > 0) {
		/* 'welcome to the show baby... */
		if (!m_ConectarMiembroAClan(UserIndex, UserList[UserIndex].GuildIndex)) {
			WriteConsoleMsg(UserIndex, "Tu estado no te permite entrar al clan.",
					FontTypeNames_FONTTYPE_GUILD);
		}
	}

	SendData(SendTarget_ToPCArea, UserIndex,
			dakara::protocol::server::BuildCreateFX(UserList[UserIndex].Char.CharIndex, FXIDs_FXWARP, 0));

	WriteLoggedMessage(UserIndex);

	SendGuildNews(UserIndex);

	/* ' Esta protegido del ataque de npcs por 5 segundos, si no realiza ninguna accion */
	IntervaloPermiteSerAtacado(UserIndex, true);

	if (Lloviendo) {
		WriteRainToggle(UserIndex);
	}

	tStr = a_ObtenerRechazoDeChar(UserList[UserIndex].Name);

	if (vb6::LenB(tStr) != 0) {
		WriteShowMessageBox(UserIndex,
				"Tu solicitud de ingreso al clan ha sido rechazada. El clan te explica que: " + tStr);
	}

	/* 'Load the user statistics */
	UserConnected(UserIndex);

	MostrarNumUsers();

	LogConnect(UserIndex, true);

	retval = true;

	return retval;
}

void SendMOTD(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int j;

	WriteGuildChat(UserIndex, "Mensajes de entrada:");
	for (j = (1); j <= (int)MOTD.ubound(); j++) {
		WriteGuildChat(UserIndex, MOTD[j].texto);
	}
}

void ResetFacciones(int UserIndex) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 23/01/2007 */
	/* 'Resetea todos los valores generales y las stats */
	/* '03/15/2006 Maraxus - Uso de With para mayor performance y claridad. */
	/* '23/01/2007 Pablo (ToxicWaste) - Agrego NivelIngreso, FechaIngreso, MatadosIngreso y NextRecompensa. */
	/* '************************************************* */
	UserList[UserIndex].Faccion.ArmadaReal = 0;
	UserList[UserIndex].Faccion.CiudadanosMatados = 0;
	UserList[UserIndex].Faccion.CriminalesMatados = 0;
	UserList[UserIndex].Faccion.FuerzasCaos = 0;
	UserList[UserIndex].Faccion.FechaIngreso = "No ingresó a ninguna Facción";
	UserList[UserIndex].Faccion.RecibioArmaduraCaos = 0;
	UserList[UserIndex].Faccion.RecibioArmaduraReal = 0;
	UserList[UserIndex].Faccion.RecibioExpInicialCaos = 0;
	UserList[UserIndex].Faccion.RecibioExpInicialReal = 0;
	UserList[UserIndex].Faccion.RecompensasCaos = 0;
	UserList[UserIndex].Faccion.RecompensasReal = 0;
	UserList[UserIndex].Faccion.Reenlistadas = 0;
	UserList[UserIndex].Faccion.NivelIngreso = 0;
	UserList[UserIndex].Faccion.MatadosIngreso = 0;
	UserList[UserIndex].Faccion.NextRecompensa = 0;
}

void ResetContadores(int UserIndex) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 10/07/2010 */
	/* 'Resetea todos los valores generales y las stats */
	/* '03/15/2006 Maraxus - Uso de With para mayor performance y claridad. */
	/* '05/20/2007 Integer - Agregue todas las variables que faltaban. */
	/* '10/07/2010: ZaMa - Agrego los counters que faltaban. */
	/* '************************************************* */
	UserList[UserIndex].Counters.AGUACounter = 0;
	UserList[UserIndex].Counters.AsignedSkills = 0;
	UserList[UserIndex].Counters.AttackCounter = 0;
	UserList[UserIndex].Counters.bPuedeMeditar = true;
	UserList[UserIndex].Counters.Ceguera = 0;
	UserList[UserIndex].Counters.COMCounter = 0;
	UserList[UserIndex].Counters.Estupidez = 0;
	UserList[UserIndex].Counters.failedUsageAttempts = 0;
	UserList[UserIndex].Counters.Frio = 0;
	UserList[UserIndex].Counters.goHome = 0;
	UserList[UserIndex].Counters.HPCounter = 0;
	UserList[UserIndex].Counters.IdleCount = 0;
	UserList[UserIndex].Counters.Invisibilidad = 0;
	UserList[UserIndex].Counters.Lava = 0;
	UserList[UserIndex].Counters.Mimetismo = 0;
	UserList[UserIndex].Counters.Ocultando = 0;
	UserList[UserIndex].Counters.Paralisis = 0;
	UserList[UserIndex].Counters.Pena = 0;
	UserList[UserIndex].Counters.PiqueteC = 0;
	UserList[UserIndex].Counters.Saliendo = false;
	UserList[UserIndex].Counters.Salir = 0;
	UserList[UserIndex].Counters.STACounter = 0;
	UserList[UserIndex].Counters.TiempoOculto = 0;
	UserList[UserIndex].Counters.TimerEstadoAtacable = 0;
	UserList[UserIndex].Counters.TimerGolpeMagia = 0;
	UserList[UserIndex].Counters.TimerGolpeUsar = 0;
	UserList[UserIndex].Counters.TimerLanzarSpell = 0;
	UserList[UserIndex].Counters.TimerMagiaGolpe = 0;
	UserList[UserIndex].Counters.TimerPerteneceNpc = 0;
	UserList[UserIndex].Counters.TimerPuedeAtacar = 0;
	UserList[UserIndex].Counters.TimerPuedeSerAtacado = 0;
	UserList[UserIndex].Counters.TimerPuedeTrabajar = 0;
	UserList[UserIndex].Counters.TimerPuedeUsarArco = 0;
	UserList[UserIndex].Counters.TimerUsar = 0;
	UserList[UserIndex].Counters.Trabajando = 0;
	UserList[UserIndex].Counters.Veneno = 0;
}

void ResetCharInfo(int UserIndex) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 03/15/2006 */
	/* 'Resetea todos los valores generales y las stats */
	/* '03/15/2006 Maraxus - Uso de With para mayor performance y claridad. */
	/* '************************************************* */
	UserList[UserIndex].Char.body = 0;
	UserList[UserIndex].Char.CascoAnim = 0;
	UserList[UserIndex].Char.CharIndex = 0;
	UserList[UserIndex].Char.FX = 0;
	UserList[UserIndex].Char.Head = 0;
	UserList[UserIndex].Char.loops = 0;
	UserList[UserIndex].Char.heading = eHeading_None;
	UserList[UserIndex].Char.loops = 0;
	UserList[UserIndex].Char.ShieldAnim = 0;
	UserList[UserIndex].Char.WeaponAnim = 0;
}

void ResetBasicUserInfo(int UserIndex) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 03/15/2006 */
	/* 'Resetea todos los valores generales y las stats */
	/* '03/15/2006 Maraxus - Uso de With para mayor performance y claridad. */
	/* '************************************************* */
	UserList[UserIndex].Name = "";
	UserList[UserIndex].desc = "";
	UserList[UserIndex].DescRM = "";
	UserList[UserIndex].Pos.Map = 0;
	UserList[UserIndex].Pos.X = 0;
	UserList[UserIndex].Pos.Y = 0;
	UserList[UserIndex].ip = "";
	UserList[UserIndex].clase = eClass_None;
	UserList[UserIndex].email = "";
	UserList[UserIndex].Genero = eGenero_None;
	UserList[UserIndex].Hogar = eCiudad_None;
	UserList[UserIndex].raza = eRaza_None;

	UserList[UserIndex].PartyIndex = 0;
	UserList[UserIndex].PartySolicitud = 0;

	UserList[UserIndex].Stats.Banco = 0;
	UserList[UserIndex].Stats.ELV = 0;
	UserList[UserIndex].Stats.ELU = 0;
	UserList[UserIndex].Stats.Exp = 0;
	UserList[UserIndex].Stats.def = 0;
	/* '.CriminalesMatados = 0 */
	UserList[UserIndex].Stats.NPCsMuertos = 0;
	UserList[UserIndex].Stats.UsuariosMatados = 0;
	UserList[UserIndex].Stats.SkillPts = 0;
	UserList[UserIndex].Stats.GLD = 0;
	UserList[UserIndex].Stats.UserAtributos[1] = 0;
	UserList[UserIndex].Stats.UserAtributos[2] = 0;
	UserList[UserIndex].Stats.UserAtributos[3] = 0;
	UserList[UserIndex].Stats.UserAtributos[4] = 0;
	UserList[UserIndex].Stats.UserAtributos[5] = 0;
	UserList[UserIndex].Stats.UserAtributosBackUP[1] = 0;
	UserList[UserIndex].Stats.UserAtributosBackUP[2] = 0;
	UserList[UserIndex].Stats.UserAtributosBackUP[3] = 0;
	UserList[UserIndex].Stats.UserAtributosBackUP[4] = 0;
	UserList[UserIndex].Stats.UserAtributosBackUP[5] = 0;

}

void ResetReputacion(int UserIndex) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 03/15/2006 */
	/* 'Resetea todos los valores generales y las stats */
	/* '03/15/2006 Maraxus - Uso de With para mayor performance y claridad. */
	/* '************************************************* */
	UserList[UserIndex].Reputacion.AsesinoRep = 0;
	UserList[UserIndex].Reputacion.BandidoRep = 0;
	UserList[UserIndex].Reputacion.BurguesRep = 0;
	UserList[UserIndex].Reputacion.LadronesRep = 0;
	UserList[UserIndex].Reputacion.NobleRep = 0;
	UserList[UserIndex].Reputacion.PlebeRep = 0;
	UserList[UserIndex].Reputacion.NobleRep = 0;
	UserList[UserIndex].Reputacion.Promedio = 0;
}

void ResetGuildInfo(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (UserList[UserIndex].EscucheClan > 0) {
		GMDejaDeEscucharClan(UserIndex, UserList[UserIndex].EscucheClan);
		UserList[UserIndex].EscucheClan = 0;
	}
	if (UserList[UserIndex].GuildIndex > 0) {
		m_DesconectarMiembroDelClan(UserIndex, UserList[UserIndex].GuildIndex);
	}
	UserList[UserIndex].GuildIndex = 0;
}

void ResetUserFlags(int UserIndex) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 06/28/2008 */
	/* 'Resetea todos los valores generales y las stats */
	/* '03/15/2006 Maraxus - Uso de With para mayor performance y claridad. */
	/* '03/29/2006 Maraxus - Reseteo el CentinelaOK también. */
	/* '06/28/2008 NicoNZ - Agrego el flag Inmovilizado */
	/* '************************************************* */
	UserList[UserIndex].flags.Comerciando = false;
	UserList[UserIndex].flags.Ban = 0;
	UserList[UserIndex].flags.Escondido = 0;
	UserList[UserIndex].flags.DuracionEfecto = 0;
	UserList[UserIndex].flags.NpcInv = 0;
	UserList[UserIndex].flags.StatsChanged = 0;
	UserList[UserIndex].flags.TargetNPC = 0;
	UserList[UserIndex].flags.TargetNpcTipo = eNPCType_Comun;
	UserList[UserIndex].flags.TargetObj = 0;
	UserList[UserIndex].flags.TargetObjMap = 0;
	UserList[UserIndex].flags.TargetObjX = 0;
	UserList[UserIndex].flags.TargetObjY = 0;
	UserList[UserIndex].flags.TargetUser = 0;
	UserList[UserIndex].flags.TipoPocion = 0;
	UserList[UserIndex].flags.TomoPocion = false;
	UserList[UserIndex].flags.Descuento = "";
	UserList[UserIndex].flags.Hambre = 0;
	UserList[UserIndex].flags.Sed = 0;
	UserList[UserIndex].flags.Descansar = false;
	UserList[UserIndex].flags.Vuela = 0;
	UserList[UserIndex].flags.Navegando = 0;
	UserList[UserIndex].flags.Oculto = 0;
	UserList[UserIndex].flags.Envenenado = 0;
	UserList[UserIndex].flags.invisible = 0;
	UserList[UserIndex].flags.Paralizado = 0;
	UserList[UserIndex].flags.Inmovilizado = 0;
	UserList[UserIndex].flags.Maldicion = 0;
	UserList[UserIndex].flags.Bendicion = 0;
	UserList[UserIndex].flags.Meditando = 0;
	UserList[UserIndex].flags.Privilegios2 = 0;
	UserList[UserIndex].flags.PrivEspecial = false;
	UserList[UserIndex].flags.PuedeMoverse = 0;
	UserList[UserIndex].flags.OldBody = 0;
	UserList[UserIndex].flags.OldHead = 0;
	UserList[UserIndex].flags.AdminInvisible = 0;
	UserList[UserIndex].flags.ValCoDe = 0;
	UserList[UserIndex].flags.Hechizo = 0;
	UserList[UserIndex].flags.TimesWalk = 0;
	UserList[UserIndex].flags.StartWalk = 0;
	UserList[UserIndex].flags.CountSH = 0;
	UserList[UserIndex].flags.Silenciado = 0;
	UserList[UserIndex].flags.CentinelaOK = false;
	UserList[UserIndex].flags.CentinelaIndex = 0;
	UserList[UserIndex].flags.AdminPerseguible = false;
	UserList[UserIndex].flags.lastMap = 0;
	UserList[UserIndex].flags.Traveling = 0;
	UserList[UserIndex].flags.AtacablePor = 0;
	UserList[UserIndex].flags.AtacadoPorNpc = 0;
	UserList[UserIndex].flags.AtacadoPorUser = 0;
	UserList[UserIndex].flags.NoPuedeSerAtacado = false;
	UserList[UserIndex].flags.ShareNpcWith = 0;
	UserList[UserIndex].flags.EnConsulta = false;
	UserList[UserIndex].flags.Ignorado = false;
	UserList[UserIndex].flags.SendDenounces = false;
	UserList[UserIndex].flags.ParalizedBy = "";
	UserList[UserIndex].flags.ParalizedByIndex = 0;
	UserList[UserIndex].flags.ParalizedByNpcIndex = 0;

	if (UserList[UserIndex].flags.OwnedNpc != 0) {
		PerdioNpc(UserIndex);
	}

}

void ResetUserSpells(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int LoopC;
	for (LoopC = (1); LoopC <= (MAXUSERHECHIZOS); LoopC++) {
		UserList[UserIndex].Stats.UserHechizos[LoopC] = 0;
	}
}

void ResetUserPets(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int LoopC;

	UserList[UserIndex].NroMascotas = 0;

	for (LoopC = (1); LoopC <= (MAXMASCOTAS); LoopC++) {
		UserList[UserIndex].MascotasIndex[LoopC] = 0;
		UserList[UserIndex].MascotasType[LoopC] = 0;
	}
}

void ResetUserBanco(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int LoopC;

	for (LoopC = (1); LoopC <= (MAX_BANCOINVENTORY_SLOTS); LoopC++) {
		UserList[UserIndex].BancoInvent.Object[LoopC].Amount = 0;
		UserList[UserIndex].BancoInvent.Object[LoopC].Equipped = 0;
		UserList[UserIndex].BancoInvent.Object[LoopC].ObjIndex = 0;
	}

	UserList[UserIndex].BancoInvent.NroItems = 0;
}

void LimpiarComercioSeguro(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (UserList[UserIndex].ComUsu.DestUsu > 0) {
		FinComerciarUsu(UserList[UserIndex].ComUsu.DestUsu);
		FinComerciarUsu(UserIndex);
	}
}

void ResetUserSlot(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int i;

	LimpiarComercioSeguro(UserIndex);
	ResetFacciones(UserIndex);
	ResetContadores(UserIndex);
	ResetGuildInfo(UserIndex);
	ResetCharInfo(UserIndex);
	ResetBasicUserInfo(UserIndex);
	ResetReputacion(UserIndex);
	ResetUserFlags(UserIndex);
	LimpiarInventario(UserIndex);
	ResetUserSpells(UserIndex);
	ResetUserPets(UserIndex);
	ResetUserBanco(UserIndex);

	UserList[UserIndex].ComUsu.Acepto = false;

	for (i = (1); i <= (MAX_OFFER_SLOTS); i++) {
		UserList[UserIndex].ComUsu.cant[i] = 0;
		UserList[UserIndex].ComUsu.Objeto[i] = 0;
	}

	UserList[UserIndex].ComUsu.GoldAmount = 0;
	UserList[UserIndex].ComUsu.DestNick = "";
	UserList[UserIndex].ComUsu.DestUsu = 0;

	/* # IF SeguridadAlkon THEN */
	/* # END IF */
}

void CloseUser(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int Map;
	std::string Name;
	int i;

	int aN;

	aN = UserList[UserIndex].flags.AtacadoPorNpc;
	if (aN > 0) {
		Npclist[aN].Movement = Npclist[aN].flags.OldMovement;
		Npclist[aN].Hostile = Npclist[aN].flags.OldHostil;
		Npclist[aN].flags.AttackedBy = "";
	}

	aN = UserList[UserIndex].flags.NPCAtacado;
	if (aN > 0) {
		if (Npclist[aN].flags.AttackedFirstBy == UserList[UserIndex].Name) {
			Npclist[aN].flags.AttackedFirstBy = "";
		}
	}
	UserList[UserIndex].flags.AtacadoPorNpc = 0;
	UserList[UserIndex].flags.NPCAtacado = 0;

	Map = UserList[UserIndex].Pos.Map;
	Name = vb6::UCase(UserList[UserIndex].Name);

	UserList[UserIndex].Char.FX = 0;
	UserList[UserIndex].Char.loops = 0;
	SendData(SendTarget_ToPCArea, UserIndex,
			dakara::protocol::server::BuildCreateFX(UserList[UserIndex].Char.CharIndex, 0, 0));

	UserList[UserIndex].flags.UserLogged = false;
	UserList[UserIndex].Counters.Saliendo = false;

	/* 'Le devolvemos el body y head originales */
	if (UserList[UserIndex].flags.AdminInvisible == 1) {
		UserList[UserIndex].Char.body = UserList[UserIndex].flags.OldBody;
		UserList[UserIndex].Char.Head = UserList[UserIndex].flags.OldHead;
		UserList[UserIndex].flags.AdminInvisible = 0;
	}

	/* 'si esta en party le devolvemos la experiencia */
	if (UserList[UserIndex].PartyIndex > 0) {
		SalirDeParty(UserIndex);
	}

	/* 'Save statistics */
	UserDisconnected(UserIndex);

	/* ' Grabamos el personaje del usuario */
	SaveUser(UserIndex, GetCharPath(Name));

	/* 'usado para borrar Pjs */
	WriteVar(GetCharPath(UserList[UserIndex].Name), "INIT", "Logged", "0");

	/* 'Quitar el dialogo */
	/* 'If MapInfo(Map).NumUsers > 0 Then */
	/* '    Call SendToUserArea(UserIndex, "QDL" & .Char.charindex) */
	/* 'End If */

	if (MapaValido(Map)) {
		if (MapInfo[Map].NumUsers > 0) {
			SendData(SendTarget_ToPCAreaButIndex, UserIndex,
					dakara::protocol::server::BuildRemoveCharDialog(UserList[UserIndex].Char.CharIndex));
		}

		/* 'Update Map Users */
		MapInfo[Map].NumUsers = MapInfo[Map].NumUsers - 1;

		if (MapInfo[Map].NumUsers < 0) {
			MapInfo[Map].NumUsers = 0;
		}
	}

	/* 'Borrar el personaje */
	if (UserList[UserIndex].Char.CharIndex > 0) {
		EraseUserChar(UserIndex, UserList[UserIndex].flags.AdminInvisible == 1);
	}

	/* 'Borrar mascotas */
	for (i = (1); i <= (MAXMASCOTAS); i++) {
		if (UserList[UserIndex].MascotasIndex[i] > 0) {
			if (Npclist[UserList[UserIndex].MascotasIndex[i]].flags.NPCActive) {
				QuitarNPC(UserList[UserIndex].MascotasIndex[i]);
			}
		}
	}

	/* ' Si el usuario habia dejado un msg en la gm's queue lo borramos */
	{
		auto it = std::find(Ayuda.begin(), Ayuda.end(), UserList[UserIndex].Name);
		if (it != Ayuda.end()) {
			Ayuda.erase(it);
		}
	}

	LogConnect(UserIndex, false);

	ResetUserSlot(UserIndex);

	MostrarNumUsers();
}

void ReloadSokcet() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	LogApiSock("ReloadSokcet() " + vb6::CStr(NumUsers) + " " + vb6::CStr(LastUser) + " " + vb6::CStr(MaxUsers));

	if (NumUsers <= 0) {
		WSApiReiniciarSockets();
	} else {
		/* '       Call apiclosesocket(SockListen) */
		/* '       SockListen = ListenForConnect(Puerto, hWndMsg, "") */
	}

}

void EnviarNoche(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	WriteSendNight(UserIndex,
			vb6::IIf(
					DeNoche
							&& (MapInfo[UserList[UserIndex].Pos.Map].Zona == Campo
									|| MapInfo[UserList[UserIndex].Pos.Map].Zona == Ciudad), true, false));
	WriteSendNight(UserIndex, vb6::IIf(DeNoche, true, false));
}

void EcharPjsNoPrivilegiados() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int LoopC;

	for (LoopC = (1); LoopC <= (LastUser); LoopC++) {
		if (UserList[LoopC].flags.UserLogged) {
			if (UserTienePrivilegio(LoopC, PlayerType_User)) {
				CloseSocket(LoopC);
			}
		}
	}

}
