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

#include "Admin.h"

#include <fstream>

vb6::array<struct tMotd> MOTD;
bool EnviarPopupOfTheDay = false;
std::string PopupOfTheDayMessage;

struct tAPuestas Apuestas;

int tInicioServer;

/* 'INTERVALOS */
int SanaIntervaloSinDescansar;
int StaminaIntervaloSinDescansar;
int SanaIntervaloDescansar;
int StaminaIntervaloDescansar;
int IntervaloSed;
int IntervaloHambre;
int IntervaloVeneno;
int IntervaloParalizado;
const int IntervaloParalizadoReducido = 37;
int IntervaloInvisible;
int IntervaloFrio;
int IntervaloWavFx;
int IntervaloLanzaHechizo;
int IntervaloNPCPuedeAtacar;
int IntervaloNPCAI;
int IntervaloInvocacion;
/* '[Nacho] */
int IntervaloOculto;
int IntervaloUserPuedeAtacar;
int IntervaloGolpeUsar;
int IntervaloMagiaGolpe;
int IntervaloGolpeMagia;
int IntervaloUserPuedeCastear;
int IntervaloUserPuedeTrabajar;
int IntervaloParaConexion;
/* '[Gonzalo] */
int IntervaloCerrarConexion;
int IntervaloUserPuedeUsar;
int IntervaloFlechasCazadores;
int IntervaloPuedeSerAtacado;
int IntervaloAtacable;
int IntervaloOwnedNpc;
int IntervaloImprimirEnConsola = 1;

/* 'BALANCE */

int PorcentajeRecuperoMana;

int MinutosWs;
int MinutosGuardarUsuarios;
int MinutosMotd;
int Puerto;
int MAX_PACKETS_PER_ITER = 5;

int BootDelBackUp;
bool Lloviendo;
bool DeNoche;

bool VersionOK(std::string Ver) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	retval = (Ver == ULTIMAVERSION);
	return retval;
}

void ReSpawnOrigPosNpcs() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	/* FIXME: ON ERROR RESUME NEXT */

	int i;
	struct npc MiNPC;

	for (i = (1); i <= (LastNPC); i++) {
		/* 'OJO */
		if (Npclist[i].flags.NPCActive) {

			if (InMapBounds(Npclist[i].Orig.Map, Npclist[i].Orig.X,
					Npclist[i].Orig.Y) && Npclist[i].Numero == Guardias) {
				MiNPC = Npclist[i];
				QuitarNPC(i);
				ReSpawnNpc(MiNPC);
			}

			/* 'tildada por sugerencia de yind */
			/* 'If Npclist(i).Contadores.TiempoExistencia > 0 Then */
			/* '        Call MuereNpc(i, 0) */
			/* 'End If */
		}

	}

}

void WorldSave() {
	int loopX;

	SendData(SendTarget_ToAll, 0,
			dakara::protocol::server::BuildConsoleMsg("Servidor> Iniciando WorldSave",
					FontTypeNames_FONTTYPE_SERVER));

	/* 'respawn de los guardias en las pos originales */
	ReSpawnOrigPosNpcs();

	int j;
	int k = 0;

	for (j = (1); j <= (NumMaps); j++) {
		if (MapInfo[j].BackUp == 1) {
			k = k + 1;
		}
	}

	for (loopX = (1); loopX <= (NumMaps); loopX++) {
		if (MapInfo[loopX].BackUp == 1) {
			GrabarMapa(loopX, true);
		}
	}

	if (FileExist(GetDatPath(DATPATH::bkNpcs))) {
		vb6::Kill(GetDatPath(DATPATH::bkNpcs));
	}

	std::ofstream npcfile;
	npcfile.open(GetDatPath(DATPATH::bkNpcs), std::ios::out | std::ios::trunc);

	for (loopX = (1); loopX <= (LastNPC); loopX++) {
		if (Npclist[loopX].flags.BackUp == 1) {
			BackUPnPc(loopX, npcfile);
		}
	}

	SaveForums();

	SendData(SendTarget_ToAll, 0,
			dakara::protocol::server::BuildConsoleMsg("Servidor> WorldSave ha concluído.",
					FontTypeNames_FONTTYPE_SERVER));

	Logger::getInstance().flushAll();
}

void ServerShutdown() {
	std::cerr << "Server Shutdown!" << std::endl;

	haciendoBK = true;
//	SendData(SendTarget_ToAll, 0, PrepareMessagePauseToggle());
//	SendData(SendTarget_ToAll, 0,
//				PrepareMessageConsoleMsg("Servidor> Cerrando servidor...", FontTypeNames_FONTTYPE_SERVER));

	for (int i = 1; i<LastUser; ++i) {
		if (UserIndexSocketValido(i)) {
			FlushBuffer(i);
			CloseSocketSL(i);
		}
	}

	std::cerr << "Experiencias... " << std::endl;
	ActualizaExperiencias();

	std::cerr << "Guardando usuarios... " << std::endl;
	GuardarUsuarios();

	std::cerr << "WorldSave... " << std::endl;
	WorldSave();

	LimpiaWsApi();
}

void PurgarPenas() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int i;

	for (i = (1); i <= (LastUser); i++) {
		if (UserList[i].flags.UserLogged) {
			if (UserList[i].Counters.Pena > 0) {
				UserList[i].Counters.Pena = UserList[i].Counters.Pena - 1;

				if (UserList[i].Counters.Pena < 1) {
					UserList[i].Counters.Pena = 0;
					WarpUserChar(i, Libertad.Map, Libertad.X, Libertad.Y, true);
					WriteConsoleMsg(i, "¡Has sido liberado!",
							FontTypeNames_FONTTYPE_INFO);

					FlushBuffer(i);
				}
			}
		}
	}
}

void Encarcelar(int UserIndex, int Minutos, std::string GmName) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	UserList[UserIndex].Counters.Pena = Minutos;

	WarpUserChar(UserIndex, Prision.Map, Prision.X, Prision.Y, true);

	if (vb6::LenB(GmName) == 0) {
		WriteConsoleMsg(UserIndex,
				"Has sido encarcelado, deberás permanecer en la cárcel "
						+ std::to_string(Minutos) + " minutos.",
				FontTypeNames_FONTTYPE_INFO);
	} else {
		WriteConsoleMsg(UserIndex,
				GmName + " te ha encarcelado, deberás permanecer en la cárcel "
						+ std::to_string(Minutos) + " minutos.",
				FontTypeNames_FONTTYPE_INFO);
	}
	if (UserList[UserIndex].flags.Traveling == 1) {
		UserList[UserIndex].flags.Traveling = 0;
		UserList[UserIndex].Counters.goHome = 0;
		WriteMultiMessage(UserIndex, eMessages_CancelHome);
	}
}

void BorrarUsuario(std::string UserName) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (FileExist(GetCharPath(UserName), 0)) {
		vb6::Kill(GetCharPath(UserName));
	}
}

bool BANCheck(std::string Name) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	retval = (vb6::val(GetVar(GetCharPath(Name), "FLAGS", "Ban")) == 1);

	return retval;
}

bool PersonajeExiste(std::string Name) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	retval = FileExist(GetCharPath(Name), 0);

	return retval;
}

bool UnBan(std::string Name) {
	bool retval = true;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	/* 'Unban the character */
	WriteVar(GetCharPath(Name), "FLAGS", "Ban", "0");

	/* 'Remove it from the banned people database */
	WriteVar(GetLogFileName("BanDetail"), Name, "BannedBy", "NOBODY");
	WriteVar(GetLogFileName("BanDetail"), Name, "Reason", "NO REASON");
	return retval;
}

bool MD5ok(std::string md5formateado) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int i;

	if (MD5ClientesActivado == 1) {
		for (i = (0); i <= (vb6::UBound(MD5s)); i++) {
			if ((md5formateado == MD5s[i])) {
				retval = true;
				return retval;
			}
		}
		retval = false;
	} else {
		retval = true;
	}

	return retval;
}

void MD5sCarga(clsIniManager& leerSini) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int LoopC;

	MD5ClientesActivado = vb6::CInt(leerSini.GetValue("MD5Hush", "Activado"));

	if (MD5ClientesActivado == 1) {
		int count = vb6::Constrain(vb6::CInt(leerSini.GetValue("MD5Hush", "MD5Aceptados")), 0, 10000);

		if (count < 1) {
			std::cerr << "ATENCION: No hay MD5s cargados en server.ini" << std::endl;
			count = 1;
		}

		MD5s.resize(count);
		for (LoopC = (0); LoopC < count; LoopC++) {
			MD5s[LoopC] = vb6::LCase(leerSini.GetValue("MD5Hush", "MD5Aceptado" + vb6::CStr(LoopC + 1)));

			if (MD5s[LoopC].size() != 32) {
				std::cerr << "MD5 " << (LoopC + 1) << " invalido." << std::endl;
			}
		}
	} else {
		std::cerr << "ATENCION: MD5 desactivado en server.ini" << std::endl;
	}
}

void BanIpAgrega(std::string ip) {
	BanIps.insert(ip);
	BanIpGuardar();
}

bool BanIpBuscar(std::string ip) {
	return BanIps.find(ip) != BanIps.end();
}

bool BanIpQuita(std::string ip) {
	auto it = BanIps.find(ip);
	if (it == BanIps.end())
		return false;
	BanIps.erase(it);
	return true;
}

void BanIpGuardar() {
	std::string ArchivoBanIp;
	ArchivoBanIp = GetDatPath(DATPATH::BanIps);
	std::ofstream out;
	out.open(ArchivoBanIp);

	for (auto& e : BanIps) {
		out << e << std::endl;
	}

	out.close();
}

void BanIpCargar() {
	std::string Tmp;
	std::string ArchivoBanIp;
	std::ifstream in;

	ArchivoBanIp = GetDatPath(DATPATH::BanIps);
	in.open(ArchivoBanIp);

	while (in >> Tmp) {
		BanIps.insert(Tmp);
	}

	in.close();
}

void ActualizaEstadisticasWeb() {
	// FIXME
}

PlayerType UserDarPrivilegioLevel(std::string Name) {
	PlayerType retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 03/02/07 */
	/* 'Last Modified By: Juan Martín Sotuyo Dodero (Maraxus) */
	/* '*************************************************** */

	if (EsAdmin(Name)) {
		retval = PlayerType_Admin;
	} else if (EsDios(Name)) {
		retval = PlayerType_Dios;
	} else if (EsSemiDios(Name)) {
		retval = PlayerType_SemiDios;
	} else if (EsConsejero(Name)) {
		retval = PlayerType_Consejero;
	} else {
		retval = PlayerType_User;
	}
	return retval;
}

bool UserTieneMasPrivilegiosQue(int UserIndexIzquierdo, int UserIndexDerecho) {
	/* FIXME: REVISAR ESTO */
	return UserList[UserIndexIzquierdo].flags.Privilegios2 > UserList[UserIndexDerecho].flags.Privilegios2;
}

bool UserTieneMasPrivilegiosQue(std::string UserNameIzquierdo, int UserIndexDerecho) {
	/* FIXME: REVISAR ESTO */
	return UserDarPrivilegioLevel(UserNameIzquierdo) > UserList[UserIndexDerecho].flags.Privilegios2;
}

bool UserTieneIgualPrivilegiosQue(int UserIndexIzquierdo, int UserIndexDerecho) {
	/* FIXME: REVISAR ESTO */
	return UserList[UserIndexIzquierdo].flags.Privilegios2 & UserList[UserIndexDerecho].flags.Privilegios2;
}

bool UserTieneIgualPrivilegiosQue(std::string UserNameIzquierdo, int UserIndexDerecho) {
	/* FIXME: REVISAR ESTO */
	return UserDarPrivilegioLevel(UserNameIzquierdo) & UserList[UserIndexDerecho].flags.Privilegios2;
}

void UserAsignarPrivilegios(int UserIndex, PlayerType p) {
	UserList[UserIndex].flags.Privilegios2 |= p;
}

void UserQuitarPrivilegios(int UserIndex, PlayerType p) {
	UserList[UserIndex].flags.Privilegios2 &= ~p;
}

void UserResetPrivilegios(int UserIndex) {
	UserList[UserIndex].flags.Privilegios2 = 0;
}

void BanCharacter(int bannerUserIndex, std::string UserName,
		std::string Reason) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 03/02/07 */
	/* '22/05/2010: Ya no se peude banear admins de mayor rango si estan online. */
	/* '*************************************************** */

	int tUser = 0;
	int cantPenas = 0;

	if (vb6::InStrB(UserName, "+")) {
		UserName = vb6::Replace(UserName, "+", " ");
	}

	tUser = NameIndex(UserName);

	if (tUser <= 0) {
		WriteConsoleMsg(bannerUserIndex, "El usuario no está online.",
				FontTypeNames_FONTTYPE_TALK);

		if (FileExist(GetCharPath(UserName), 0)) {
			if (UserTieneMasPrivilegiosQue(UserName, bannerUserIndex)) {
				WriteConsoleMsg(bannerUserIndex,
						"No puedes banear a al alguien de mayor jerarquía.",
						FontTypeNames_FONTTYPE_INFO);
			} else {
				if (GetVar(GetCharPath(UserName), "FLAGS", "Ban")
						!= "0") {
					WriteConsoleMsg(bannerUserIndex,
							"El personaje ya se encuentra baneado.",
							FontTypeNames_FONTTYPE_INFO);
				} else {
					LogBanFromName(UserName, bannerUserIndex, Reason);
					SendData(SendTarget_ToAdminsButCounselorsAndRms, 0,
							dakara::protocol::server::BuildConsoleMsg(
									"Servidor> "
											+ UserList[bannerUserIndex].Name
											+ " ha baneado a " + UserName + ".",
									FontTypeNames_FONTTYPE_SERVER));

					/* 'ponemos el flag de ban a 1 */
					WriteVar(GetCharPath(UserName), "FLAGS", "Ban", "1");
					/* 'ponemos la pena */
					cantPenas = vb6::val(
							GetVar(GetCharPath(UserName), "PENAS",
									"Cant"));
					WriteVar(GetCharPath(UserName), "PENAS", "Cant",
							std::to_string(cantPenas + 1));
					WriteVar(GetCharPath(UserName), "PENAS",
							"P" + std::to_string(cantPenas + 1),
							vb6::LCase(UserList[bannerUserIndex].Name)
									+ ": BAN POR " + vb6::LCase(Reason) + " "
									+ vb6::dateToString(vb6::Now()));

					if (UserTieneIgualPrivilegiosQue(UserName, bannerUserIndex)) {
						UserList[bannerUserIndex].flags.Ban = 1;
						SendData(SendTarget_ToAdmins, 0,
								dakara::protocol::server::BuildConsoleMsg(
										UserList[bannerUserIndex].Name
												+ " banned by the server por bannear un Administrador.",
										FontTypeNames_FONTTYPE_FIGHT));
						CloseSocket(bannerUserIndex);
					}

					LogGM(UserList[bannerUserIndex].Name,
							"BAN a " + UserName + ". Razón: " + Reason);
				}
			}
		} else {
			WriteConsoleMsg(bannerUserIndex,
					"El pj " + UserName + " no existe.",
					FontTypeNames_FONTTYPE_INFO);
		}
	} else {
		if (UserTieneMasPrivilegiosQue(tUser, bannerUserIndex)) {
			WriteConsoleMsg(bannerUserIndex,
					"No puedes banear a al alguien de mayor jerarquía.",
					FontTypeNames_FONTTYPE_INFO);
		} else {

			LogBan(tUser, bannerUserIndex, Reason);
			SendData(SendTarget_ToAdminsButCounselorsAndRms, 0,
					dakara::protocol::server::BuildConsoleMsg(
							"Servidor> " + UserList[bannerUserIndex].Name
									+ " ha baneado a " + UserList[tUser].Name
									+ ".", FontTypeNames_FONTTYPE_SERVER));

			/* 'Ponemos el flag de ban a 1 */
			UserList[tUser].flags.Ban = 1;

			if (UserTieneIgualPrivilegiosQue(tUser, bannerUserIndex)) {
				UserList[bannerUserIndex].flags.Ban = 1;
				SendData(SendTarget_ToAdminsButCounselorsAndRms, 0,
						dakara::protocol::server::BuildConsoleMsg(
								UserList[bannerUserIndex].Name
										+ " banned by the server por bannear un Administrador.",
								FontTypeNames_FONTTYPE_FIGHT));
				CloseSocket(bannerUserIndex);
			}

			LogGM(UserList[bannerUserIndex].Name,
					"BAN a " + UserName + ". Razón: " + Reason);

			/* 'ponemos el flag de ban a 1 */
			WriteVar(GetCharPath(UserName), "FLAGS", "Ban", "1");
			/* 'ponemos la pena */
			cantPenas = vb6::val(
					GetVar(GetCharPath(UserName), "PENAS", "Cant"));
			WriteVar(GetCharPath(UserName), "PENAS", "Cant",
					std::to_string(cantPenas + 1));
			WriteVar(GetCharPath(UserName), "PENAS", "P" + vb6::CStr(cantPenas + 1),
					vb6::LCase(UserList[bannerUserIndex].Name) + ": BAN POR "
							+ vb6::LCase(Reason) + " "
							+ vb6::dateToString(vb6::Now()));

			CloseSocket(tUser);
		}
	}
}
