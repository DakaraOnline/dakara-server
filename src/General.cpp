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

#include "General.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <sys/types.h>
#include <sys/stat.h>

#ifndef _WIN32
#include <unistd.h>
#include <execinfo.h>
#endif


std::shared_ptr<clsIniManager> LeerNPCs;

void dakara_print_backtrace() {
#ifndef _WIN32
	void *trace_elems[20];
	int trace_elem_count(backtrace(trace_elems, 20));
	char **stack_syms(backtrace_symbols(trace_elems, trace_elem_count));
	for (int i = 0; i < trace_elem_count; ++i) {
		std::cout << stack_syms[i] << "\n";
	}
	free(stack_syms);
#endif
}


void DarCuerpoDesnudo(int UserIndex, bool Mimetizado) {
	/* '*************************************************** */
	/* 'Autor: Nacho (Integer) */
	/* 'Last Modification: 03/14/07 */
	/* 'Da cuerpo desnudo a un usuario */
	/* '23/11/2009: ZaMa - Optimizacion de codigo. */
	/* '*************************************************** */

	int CuerpoDesnudo = 0;

	switch (UserList[UserIndex].Genero) {
	case eGenero_None:
		throw std::runtime_error("UserList[UserIndex].Genero == eGenero_None en DarCuerpoDesnudo");

	case eGenero_Hombre:
		switch (UserList[UserIndex].raza) {
		case eRaza_None:
			throw std::runtime_error("UserList[UserIndex].raza == eRaza_None en DarCuerpoDesnudo");

		case eRaza_Humano:
			CuerpoDesnudo = 21;
			break;

		case eRaza_Drow:
			CuerpoDesnudo = 32;
			break;

		case eRaza_Elfo:
			CuerpoDesnudo = 210;
			break;

		case eRaza_Gnomo:
			CuerpoDesnudo = 222;
			break;

		case eRaza_Enano:
			CuerpoDesnudo = 53;
			break;
		}
		break;

	case eGenero_Mujer:
		switch (UserList[UserIndex].raza) {
		case eRaza_None:
			throw std::runtime_error("UserList[UserIndex].raza == eRaza_None en DarCuerpoDesnudo");

		case eRaza_Humano:
			CuerpoDesnudo = 39;
			break;

		case eRaza_Drow:
			CuerpoDesnudo = 40;
			break;

		case eRaza_Elfo:
			CuerpoDesnudo = 259;
			break;

		case eRaza_Gnomo:
			CuerpoDesnudo = 260;
			break;

		case eRaza_Enano:
			CuerpoDesnudo = 60;
			break;
		}
		break;
	}

	if (Mimetizado) {
		UserList[UserIndex].CharMimetizado.body = CuerpoDesnudo;
	} else {
		UserList[UserIndex].Char.body = CuerpoDesnudo;
	}

	UserList[UserIndex].flags.Desnudo = 1;

}

void Bloquear(bool toMap, int sndIndex, int X, int Y, bool b) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* 'b ahora es boolean, */
	/* 'b=true bloquea el tile en (x,y) */
	/* 'b=false desbloquea el tile en (x,y) */
	/* 'toMap = true -> Envia los datos a todo el mapa */
	/* 'toMap = false -> Envia los datos al user */
	/* 'Unifique los tres parametros (sndIndex,sndMap y map) en sndIndex... pero de todas formas, el mapa jamas se indica.. eso esta bien asi? */
	/* 'Puede llegar a ser, que se quiera mandar el mapa, habria que agregar un nuevo parametro y modificar.. lo quite porque no se usaba ni aca ni en el cliente :s */
	/* '*************************************************** */

	if (toMap) {
		SendData(SendTarget_toMap, sndIndex, dakara::protocol::server::BuildBlockPosition(X, Y, b));
	} else {
		WriteBlockPosition(sndIndex, X, Y, b);
	}

}

bool HayAgua(int Map, int X, int Y) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (Map > 0 && Map < NumMaps + 1 && X > 0 && X < 101 && Y > 0 && Y < 101) {
		if (((MapData[Map][X][Y].Graphic[1] >= 1505 && MapData[Map][X][Y].Graphic[1] <= 1520)
				|| (MapData[Map][X][Y].Graphic[1] >= 5665 && MapData[Map][X][Y].Graphic[1] <= 5680)
				|| (MapData[Map][X][Y].Graphic[1] >= 13547 && MapData[Map][X][Y].Graphic[1] <= 13562))
				&& MapData[Map][X][Y].Graphic[2] == 0) {
			retval = true;
		} else {
			retval = false;
		}
	} else {
		retval = false;
	}

	return retval;
}

bool HayLava(int Map, int X, int Y) {
	bool retval;
	/* '*************************************************** */
	/* 'Autor: Nacho (Integer) */
	/* 'Last Modification: 03/12/07 */
	/* '*************************************************** */
	if (Map > 0 && Map < NumMaps + 1 && X > 0 && X < 101 && Y > 0 && Y < 101) {
		if (MapData[Map][X][Y].Graphic[1] >= 5837 && MapData[Map][X][Y].Graphic[1] <= 5852) {
			retval = true;
		} else {
			retval = false;
		}
	} else {
		retval = false;
	}

	return retval;
}

void LimpiarMundo() {

	for (auto& d : TrashCollector) {
		EraseObj(1, d.Map, d.X, d.Y);
	}
	TrashCollector.clear();

	IpSecurityMantenimientoLista();
}

void EnviarSpawnList(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int k;
	std::vector<std::string> npcNames;

	npcNames.reserve(1 + vb6::UBound(SpawnList));

	for (k = (1); k <= (vb6::UBound(SpawnList)); k++) {
		npcNames.push_back(SpawnList[k].NpcName);
	}

	WriteSpawnList(UserIndex, npcNames);

}


void Main() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 15/03/2011 */
	/* '15/03/2011: ZaMa - Modularice todo, para que quede mas claro. */
	/* '*************************************************** */

	LoadMotd();
	BanIpCargar();

	/* ' Start loading.. */
	std::cout << "Dakara Server v0.0.1" << std::endl;

	/* ' Constants & vars */
	std::cout << "Cargando constantes..." << std::endl;
	LoadConstants();

	/* ' Arrays */
	std::cout << "Iniciando Arrays..." << std::endl;
	LoadArrays();

	/* ' Server.ini & Apuestas.dat */
	std::cout << "Cargando Server.ini" << std::endl;
	LoadSini();
	CargaApuestas();

	/* ' Npcs.dat */
	std::cout << "Cargando NPCs.Dat" << std::endl;
	CargaNpcsDat();

	/* ' Obj.dat */
	std::cout << "Cargando Obj.Dat" << std::endl;
	LoadOBJData();

	/* ' Hechizos.dat */
	std::cout << "Cargando Hechizos.Dat" << std::endl;
	CargarHechizos();

	/* ' Objetos de Herreria */
	std::cout << "Cargando Objetos de Herrería" << std::endl;
	LoadArmasHerreria();
	LoadArmadurasHerreria();

	/* ' Objetos de Capinteria */
	std::cout << "Cargando Objetos de Carpintería" << std::endl;
	LoadObjCarpintero();

	/* ' Balance.dat */
	std::cout << "Cargando Balance.Dat" << std::endl;
	LoadBalance();

	/* ' Armaduras faccionarias */
	std::cout << "Cargando ArmadurasFaccionarias.dat" << std::endl;
	LoadArmadurasFaccion();

	/* ' Pretorianos */
	// std::cout << "Cargando Pretorianos.dat" << std::endl;
	// LoadPretorianData();

	/* ' Mapas */
	if (BootDelBackUp) {
		std::cout << "Cargando BackUp" << std::endl;
		CargarBackUp();
	} else {
		std::cout << "Cargando Mapas" << std::endl;
		LoadMapData();
	}

	/* ' Map Sounds */
	SonidosMapas.reset(new SoundMapInfo());
	SonidosMapas->LoadSoundMapInfo();

	/* ' Home distance */
	generateMatrix();

	/* ' Connections */
	ResetUsersConnections();

	/* ' Sockets */
	SocketConfig();

	/* ' Timers */
	InitMainTimers();

	/* 'Log start time */
	LogServerStartTime();

	/* 'Ocultar */
//	if (HideMe == 1) {
//		frmMain.InitMain[1];
//	} else {
//		frmMain.InitMain[0];
//	}

	tInicioServer = vb6::GetTickCount();
	InicializaEstadisticas();

}

void LoadConstants() {
	/* '***************************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modify Date: 15/03/2011 */
	/* 'Loads all constants and general parameters. */
	/* '***************************************************************** */

//	LastBackup = vb6::Format(vb6::Now(), "Short Time");
//	Minutos = vb6::Format(vb6::Now(), "Short Time");

	/* ' Paths */
//	IniPath = vb6::App().Path + "/";
//	DatPath = vb6::App().Path + "/dat/";
//	CharPath = vb6::App().Path + "/charfile/";

	/* ' Skills by level */
	LevelSkill[1].LevelValue = 3;
	LevelSkill[2].LevelValue = 5;
	LevelSkill[3].LevelValue = 7;
	LevelSkill[4].LevelValue = 10;
	LevelSkill[5].LevelValue = 13;
	LevelSkill[6].LevelValue = 15;
	LevelSkill[7].LevelValue = 17;
	LevelSkill[8].LevelValue = 20;
	LevelSkill[9].LevelValue = 23;
	LevelSkill[10].LevelValue = 25;
	LevelSkill[11].LevelValue = 27;
	LevelSkill[12].LevelValue = 30;
	LevelSkill[13].LevelValue = 33;
	LevelSkill[14].LevelValue = 35;
	LevelSkill[15].LevelValue = 37;
	LevelSkill[16].LevelValue = 40;
	LevelSkill[17].LevelValue = 43;
	LevelSkill[18].LevelValue = 45;
	LevelSkill[19].LevelValue = 47;
	LevelSkill[20].LevelValue = 50;
	LevelSkill[21].LevelValue = 53;
	LevelSkill[22].LevelValue = 55;
	LevelSkill[23].LevelValue = 57;
	LevelSkill[24].LevelValue = 60;
	LevelSkill[25].LevelValue = 63;
	LevelSkill[26].LevelValue = 65;
	LevelSkill[27].LevelValue = 67;
	LevelSkill[28].LevelValue = 70;
	LevelSkill[29].LevelValue = 73;
	LevelSkill[30].LevelValue = 75;
	LevelSkill[31].LevelValue = 77;
	LevelSkill[32].LevelValue = 80;
	LevelSkill[33].LevelValue = 83;
	LevelSkill[34].LevelValue = 85;
	LevelSkill[35].LevelValue = 87;
	LevelSkill[36].LevelValue = 90;
	LevelSkill[37].LevelValue = 93;
	LevelSkill[38].LevelValue = 95;
	LevelSkill[39].LevelValue = 97;
	LevelSkill[40].LevelValue = 100;
	LevelSkill[41].LevelValue = 100;
	LevelSkill[42].LevelValue = 100;
	LevelSkill[43].LevelValue = 100;
	LevelSkill[44].LevelValue = 100;
	LevelSkill[45].LevelValue = 100;
	LevelSkill[46].LevelValue = 100;
	LevelSkill[47].LevelValue = 100;
	LevelSkill[48].LevelValue = 100;
	LevelSkill[49].LevelValue = 100;
	LevelSkill[50].LevelValue = 100;

	/* ' Races */
	ListaRazas[eRaza_Humano] = "Humano";
	ListaRazas[eRaza_Elfo] = "Elfo";
	ListaRazas[eRaza_Drow] = "Drow";
	ListaRazas[eRaza_Gnomo] = "Gnomo";
	ListaRazas[eRaza_Enano] = "Enano";

	/* ' Classes */
	ListaClases[eClass_Mage] = "Mago";
	ListaClases[eClass_Cleric] = "Clerigo";
	ListaClases[eClass_Warrior] = "Guerrero";
	ListaClases[eClass_Assasin] = "Asesino";
	ListaClases[eClass_Thief] = "Ladron";
	ListaClases[eClass_Bard] = "Bardo";
	ListaClases[eClass_Druid] = "Druida";
	ListaClases[eClass_Bandit] = "Bandido";
	ListaClases[eClass_Paladin] = "Paladin";
	ListaClases[eClass_Hunter] = "Cazador";
	ListaClases[eClass_Worker] = "Trabajador";
	ListaClases[eClass_Pirat] = "Pirata";

	/* ' Skills */
	SkillsNames[eSkill_Magia] = "Magia";
	SkillsNames[eSkill_Robar] = "Robar";
	SkillsNames[eSkill_Tacticas] = "Evasión en combate";
	SkillsNames[eSkill_Armas] = "Combate con armas";
	SkillsNames[eSkill_Meditar] = "Meditar";
	SkillsNames[eSkill_Apunalar] = "Apunalar";
	SkillsNames[eSkill_Ocultarse] = "Ocultarse";
	SkillsNames[eSkill_Supervivencia] = "Supervivencia";
	SkillsNames[eSkill_Talar] = "Talar";
	SkillsNames[eSkill_Comerciar] = "Comercio";
	SkillsNames[eSkill_Defensa] = "Defensa con escudos";
	SkillsNames[eSkill_Pesca] = "Pesca";
	SkillsNames[eSkill_Mineria] = "Mineria";
	SkillsNames[eSkill_Carpinteria] = "Carpinteria";
	SkillsNames[eSkill_Herreria] = "Herreria";
	SkillsNames[eSkill_Liderazgo] = "Liderazgo";
	SkillsNames[eSkill_Domar] = "Domar animales";
	SkillsNames[eSkill_Proyectiles] = "Combate a distancia";
	SkillsNames[eSkill_Wrestling] = "Combate sin armas";
	SkillsNames[eSkill_Navegacion] = "Navegacion";

	/* ' Attributes */
	ListaAtributos[eAtributos_Fuerza] = "Fuerza";
	ListaAtributos[eAtributos_Agilidad] = "Agilidad";
	ListaAtributos[eAtributos_Inteligencia] = "Inteligencia";
	ListaAtributos[eAtributos_Carisma] = "Carisma";
	ListaAtributos[eAtributos_Constitucion] = "Constitucion";

	/* ' Fishes */
	ListaPeces[1] = PECES_POSIBLES_PESCADO1;
	ListaPeces[2] = PECES_POSIBLES_PESCADO2;
	ListaPeces[3] = PECES_POSIBLES_PESCADO3;
	ListaPeces[4] = PECES_POSIBLES_PESCADO4;

	/* 'Bordes del mapa */
	MinXBorder = XMinMapSize + (XWindow / 2);
	MaxXBorder = XMaxMapSize - (XWindow / 2);
	MinYBorder = YMinMapSize + (YWindow / 2);
	MaxYBorder = YMaxMapSize - (YWindow / 2);

	Ayuda.clear();
	Denuncias.clear();

	Prision.Map = 66;
	Prision.X = 75;
	Prision.Y = 47;

	Libertad.Map = 66;
	Libertad.X = 75;
	Libertad.Y = 65;

	MaxUsers = 0;

	/* ' Initialize classes */
	// WSAPISock2Usr.reset(new Collection());
	// InitAuxiliarBuffer();
	/* # IF SeguridadAlkon THEN */
	/* # END IF */

	aClon.reset(new clsAntiMassClon());
}

void LoadArrays() {
	/* '***************************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modify Date: 15/03/2011 */
	/* 'Loads all arrays */
	/* '***************************************************************** */

	/* ' Load Records */
	LoadRecords();
	/* ' Load guilds info */
	LoadGuildsDB();
	/* ' Load spawn list */
	CargarSpawnList();
	/* ' Load forbidden words */
	CargarForbidenWords();
}

void ResetUsersConnections() {
	/* '***************************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modify Date: 15/03/2011 */
	/* 'Resets Users Connections. */
	/* '***************************************************************** */

	/* FIXME: Hacer esto de vuelta */

	int LoopC;
	for (LoopC = (1); LoopC <= (MaxUsers); LoopC++) {
        UserList[LoopC].sockctx = nullptr;
		//UserList[LoopC].incomingData.reset(new clsByteQueue);
		//UserList[LoopC].outgoingData.reset(new clsByteQueue);
	}
}

void InitMainTimers() {
	TimersRegisterAll();
}

void SocketConfig() {

	std::cout << "Iniciando sockets ..." << std::endl;

	IniciaWsApi();

}

void LogServerStartTime() {
	/* '***************************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modify Date: 15/03/2011 */
	/* 'Logs Server Start Time. */
	/* '***************************************************************** */

	/* FIXME: OPEN App . Path & "/logs/Main.log" FOR Append Shared AS # N */
	/* FIXME: PRINT # N , Date & " " & time & " server iniciado " & App . Major & "." ; App . Minor & "." & App . Revision */
	/* FIXME: CLOSE # N */

}

bool FileExist(std::string File, int FileType) {
	/* FIXME: Borrar el parametro FileType */
	(void)FileType;
	struct stat buffer;
	return (stat(File.c_str(), &buffer) == 0);
}

std::string ReadField(int Pos, std::string Text, int SepASCII) {
	std::string retval;
	/* '***************************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modify Date: 11/15/2004 */
	/* 'Gets a field from a delimited string */
	/* '***************************************************************** */

	int i;
	int lastPos = 0;
	int CurrentPos = 0;
	std::string delimiter;

	delimiter = vb6::Chr(SepASCII);

	for (i = (1); i <= (Pos); i++) {
		lastPos = CurrentPos;
		CurrentPos = vb6::InStr(lastPos + 1, Text, delimiter);
	}

	if (CurrentPos == 0) {
		retval = vb6::Mid(Text, lastPos + 1, vb6::Len(Text) - lastPos);
	} else {
		retval = vb6::Mid(Text, lastPos + 1, CurrentPos - lastPos - 1);
	}
	return retval;
}

bool MapaValido(int Map) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	retval = Map >= 1 && Map <= NumMaps;
	return retval;
}

void MostrarNumUsers() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

}

bool ValidInputNP(std::string cad) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	std::string Arg;
	int i;

	for (i = (1); i <= (33); i++) {

		Arg = ReadField(i, cad, 44);

		if (vb6::LenB(Arg) == 0) {
			return retval;
		}

	}

	retval = true;

	return retval;
}

#if 0
void Restart() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	/* 'Se asegura de que los sockets estan cerrados e ignora cualquier err */
	/* FIXME: ON ERROR RESUME NEXT */

	if (frmMain.Visible) {
		frmMain.txStatus.Caption = "Reiniciando.";
	}

	int LoopC;

	/* # IF UsarQueSocket = 0 THEN */

	/* # ELSEIF UsarQueSocket = 1 THEN */

	/* 'Cierra el socket de escucha */
	if (SockListen >= 0) {
		apiclosesocket[SockListen];
	}

	/* 'Inicia el socket de escucha */
	SockListen = ListenForConnect[Puerto][hWndMsg][""];

	/* # ELSEIF UsarQueSocket = 2 THEN */

	/* # END IF */

	for (LoopC = (1); LoopC <= (MaxUsers); LoopC++) {
		CloseSocket(LoopC);
	}

	/* 'Initialize statistics!! */
	Initialize;

	for (LoopC = (1); LoopC <= (vb6::UBound(UserList[])); LoopC++
	) {
		UserList[LoopC].incomingData.reset();
		UserList[LoopC].outgoingData.reset();
	}

	UserList.resize(0);
	UserList.resize(1 + MaxUsers);

	for (LoopC = (1); LoopC <= (MaxUsers); LoopC++) {
		UserList[LoopC].ConnID = -1;
		UserList[LoopC].ConnIDValida = false;
		UserList[LoopC].incomingData.reset(new clsByteQueue());
		UserList[LoopC].outgoingData.reset(new clsByteQueue());
	}

	LastUser = 0;
	NumUsers = 0;

	FreeNPCs();
	FreeCharIndexes();

	LoadSini();

	ResetForums();
	LoadOBJData();

	LoadMapData();

	CargarHechizos();

	/* # IF UsarQueSocket = 0 THEN */

	/* # ELSEIF UsarQueSocket = 1 THEN */

	/* # ELSEIF UsarQueSocket = 2 THEN */

	/* # END IF */

	if (frmMain.Visible) {
		frmMain.txStatus.Caption = "Escuchando conexiones entrantes ...";
	}

	/* 'Log it */
	int N;
	N = vb6::FreeFile();
	/* FIXME: OPEN App . Path & "/logs/Main.log" FOR Append Shared AS # N */
	/* FIXME: PRINT # N , Date & " " & time & " servidor reiniciado." */
	/* FIXME: CLOSE # N */

	/* 'Ocultar */

//if (HideMe == 1) {
//frmMain.InitMain[1];
//} else {
//frmMain.InitMain[0];
//}
}
#endif

bool Intemperie(int UserIndex) {
	bool retval = false;
	/* '************************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modify Date: 15/11/2009 */
	/* '15/11/2009: ZaMa - La lluvia no quita stamina en las arenas. */
	/* '23/11/2009: ZaMa - Optimizacion de codigo. */
	/* '************************************************************** */

	if (MapInfo[UserList[UserIndex].Pos.Map].Zona != "DUNGEON") {
		if (MapData[UserList[UserIndex].Pos.Map][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].trigger
				!= 1
				&& MapData[UserList[UserIndex].Pos.Map][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].trigger
						!= 2
				&& MapData[UserList[UserIndex].Pos.Map][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].trigger
						!= 4) {
			retval = true;
		}
	} else {
		retval = false;
	}

	/* 'En las arenas no te afecta la lluvia */
	if (IsArena(UserIndex)) {
		retval = false;
	}
	return retval;
}

void EfectoLluvia(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (UserList[UserIndex].flags.UserLogged) {
		if (Intemperie(UserIndex)) {
			int modifi;
			modifi = Porcentaje(UserList[UserIndex].Stats.MaxSta, 3);
			QuitarSta(UserIndex, modifi);
			FlushBuffer(UserIndex);
		}
	}
}

void TiempoInvocacion(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int i;
	for (i = (1); i <= (MAXMASCOTAS); i++) {
		if (UserList[UserIndex].MascotasIndex[i] > 0) {
			if (Npclist[UserList[UserIndex].MascotasIndex[i]].Contadores.TiempoExistencia > 0) {
				Npclist[UserList[UserIndex].MascotasIndex[i]].Contadores.TiempoExistencia =
						Npclist[UserList[UserIndex].MascotasIndex[i]].Contadores.TiempoExistencia - 1;
				if (Npclist[UserList[UserIndex].MascotasIndex[i]].Contadores.TiempoExistencia == 0) {
					MuereNpc(UserList[UserIndex].MascotasIndex[i], 0);
				}
			}
		}
	}
}

void EfectoFrio(int UserIndex) {
	/* '*************************************************** */
	/* 'Autor: Unkonwn */
	/* 'Last Modification: 23/11/2009 */
	/* 'If user is naked and it's in a cold map, take health points from him */
	/* '23/11/2009: ZaMa - Optimizacion de codigo. */
	/* '*************************************************** */
	int modifi;

	if (UserList[UserIndex].Counters.Frio < IntervaloFrio) {
		UserList[UserIndex].Counters.Frio = UserList[UserIndex].Counters.Frio + 1;
	} else {
		if (MapInfo[UserList[UserIndex].Pos.Map].Terreno == eTerrain_terrain_nieve) {
			WriteConsoleMsg(UserIndex, "¡¡Estás muriendo de frío, abrigate o morirás!!",
					FontTypeNames_FONTTYPE_INFO);
			modifi = MinimoInt(Porcentaje(UserList[UserIndex].Stats.MaxHp, 5), 15);
			UserList[UserIndex].Stats.MinHp = UserList[UserIndex].Stats.MinHp - modifi;

			if (UserList[UserIndex].Stats.MinHp < 1) {
				WriteConsoleMsg(UserIndex, "¡¡Has muerto de frío!!", FontTypeNames_FONTTYPE_INFO);
				UserList[UserIndex].Stats.MinHp = 0;
				UserDie(UserIndex);
			}

			WriteUpdateHP(UserIndex);
		} else {
			modifi = Porcentaje(UserList[UserIndex].Stats.MaxSta, 5);
			QuitarSta(UserIndex, modifi);
			WriteUpdateSta(UserIndex);
		}

		UserList[UserIndex].Counters.Frio = 0;
	}
}

void EfectoLava(int UserIndex) {
	/* '*************************************************** */
	/* 'Autor: Nacho (Integer) */
	/* 'Last Modification: 23/11/2009 */
	/* 'If user is standing on lava, take health points from him */
	/* '23/11/2009: ZaMa - Optimizacion de codigo. */
	/* '*************************************************** */
	/* 'Usamos el mismo intervalo que el del frio */
	if (UserList[UserIndex].Counters.Lava < IntervaloFrio) {
		UserList[UserIndex].Counters.Lava = UserList[UserIndex].Counters.Lava + 1;
	} else {
		if (HayLava(UserList[UserIndex].Pos.Map, UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y)) {
			WriteConsoleMsg(UserIndex, "¡¡Quitate de la lava, te estás quemando!!",
					FontTypeNames_FONTTYPE_INFO);
			UserList[UserIndex].Stats.MinHp = UserList[UserIndex].Stats.MinHp
					- Porcentaje(UserList[UserIndex].Stats.MaxHp, 5);

			if (UserList[UserIndex].Stats.MinHp < 1) {
				WriteConsoleMsg(UserIndex, "¡¡Has muerto quemado!!", FontTypeNames_FONTTYPE_INFO);
				UserList[UserIndex].Stats.MinHp = 0;
				UserDie(UserIndex);
			}

			WriteUpdateHP(UserIndex);

		}

		UserList[UserIndex].Counters.Lava = 0;
	}
}

/* '' */
/* ' Maneja  el efecto del estado atacable */
/* ' */
/* ' @param UserIndex  El index del usuario a ser afectado por el estado atacable */
/* ' */

void EfectoEstadoAtacable(int UserIndex) {
	/* '****************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Update: 18/09/2010 (ZaMa) */
	/* '18/09/2010: ZaMa - Ahora se activa el seguro cuando dejas de ser atacable. */
	/* '****************************************************** */

	/* ' Si ya paso el tiempo de penalizacion */
	if (!IntervaloEstadoAtacable(UserIndex)) {
		/* ' Deja de poder ser atacado */
		UserList[UserIndex].flags.AtacablePor = 0;

		/* ' Activo el seguro si deja de estar atacable */
		if (!UserList[UserIndex].flags.Seguro) {
			WriteMultiMessage(UserIndex, eMessages_SafeModeOn);
		}

		/* ' Send nick normal */
		RefreshCharStatus(UserIndex);
	}

}

/* '' */
/* ' Maneja el tiempo de arrivo al hogar */
/* ' */
/* ' @param UserIndex  El index del usuario a ser afectado por el /hogar */
/* ' */

void TravelingEffect(int UserIndex) {
	/* '****************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Update: 01/06/2010 (ZaMa) */
	/* '****************************************************** */

	/* ' Si ya paso el tiempo de penalizacion */
	if (IntervaloGoHome(UserIndex)) {
		HomeArrival(UserIndex);
	}

}

/* '' */
/* ' Maneja el tiempo y el efecto del mimetismo */
/* ' */
/* ' @param UserIndex  El index del usuario a ser afectado por el mimetismo */
/* ' */

void EfectoMimetismo(int UserIndex) {
	/* '****************************************************** */
	/* 'Author: Unknown */
	/* 'Last Update: 16/09/2010 (ZaMa) */
	/* '12/01/2010: ZaMa - Los druidas pierden la inmunidad de ser atacados cuando pierden el efecto del mimetismo. */
	/* '16/09/2010: ZaMa - Se recupera la apariencia de la barca correspondiente despues de terminado el mimetismo. */
	/* '****************************************************** */
	struct ObjData Barco;

	if (UserList[UserIndex].Counters.Mimetismo < IntervaloInvisible) {
		UserList[UserIndex].Counters.Mimetismo = UserList[UserIndex].Counters.Mimetismo + 1;
	} else {
		/* 'restore old char */
		WriteConsoleMsg(UserIndex, "Recuperas tu apariencia normal.", FontTypeNames_FONTTYPE_INFO);

		if (UserList[UserIndex].flags.Navegando) {
			if (UserList[UserIndex].flags.Muerto == 0) {
				ToggleBoatBody(UserIndex);
			} else {
				UserList[UserIndex].Char.body = iFragataFantasmal;
				UserList[UserIndex].Char.ShieldAnim = NingunEscudo;
				UserList[UserIndex].Char.WeaponAnim = NingunArma;
				UserList[UserIndex].Char.CascoAnim = NingunCasco;
			}
		} else {
			UserList[UserIndex].Char.body = UserList[UserIndex].CharMimetizado.body;
			UserList[UserIndex].Char.Head = UserList[UserIndex].CharMimetizado.Head;
			UserList[UserIndex].Char.CascoAnim = UserList[UserIndex].CharMimetizado.CascoAnim;
			UserList[UserIndex].Char.ShieldAnim = UserList[UserIndex].CharMimetizado.ShieldAnim;
			UserList[UserIndex].Char.WeaponAnim = UserList[UserIndex].CharMimetizado.WeaponAnim;
		}

		ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
				UserList[UserIndex].Char.heading, UserList[UserIndex].Char.WeaponAnim,
				UserList[UserIndex].Char.ShieldAnim, UserList[UserIndex].Char.CascoAnim);

		UserList[UserIndex].Counters.Mimetismo = 0;
		UserList[UserIndex].flags.Mimetizado = 0;
		/* ' Se fue el efecto del mimetismo, puede ser atacado por npcs */
		UserList[UserIndex].flags.Ignorado = false;
	}
}

void EfectoInvisibilidad(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 16/09/2010 (ZaMa) */
	/* '16/09/2010: ZaMa - Al perder el invi cuando navegas, no se manda el mensaje de sacar invi (ya estas visible). */
	/* '*************************************************** */

	if (UserList[UserIndex].Counters.Invisibilidad < IntervaloInvisible) {
		UserList[UserIndex].Counters.Invisibilidad = UserList[UserIndex].Counters.Invisibilidad + 1;
	} else {
		/* ' Invi variable :D */
		UserList[UserIndex].Counters.Invisibilidad = RandomNumber(-100, 100);
		UserList[UserIndex].flags.invisible = 0;
		if (UserList[UserIndex].flags.Oculto == 0) {
			WriteConsoleMsg(UserIndex, "Has vuelto a ser visible.", FontTypeNames_FONTTYPE_INFO);

			/* ' Si navega ya esta visible.. */
			if (UserList[UserIndex].flags.Navegando != 1) {
				SetInvisible(UserIndex, UserList[UserIndex].Char.CharIndex, false);
			}

		}
	}

}

void EfectoParalisisNpc(int NpcIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (Npclist[NpcIndex].Contadores.Paralisis > 0) {
		Npclist[NpcIndex].Contadores.Paralisis = Npclist[NpcIndex].Contadores.Paralisis - 1;
	} else {
		Npclist[NpcIndex].flags.Paralizado = 0;
		Npclist[NpcIndex].flags.Inmovilizado = 0;
	}

}

void EfectoCegueEstu(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (UserList[UserIndex].Counters.Ceguera > 0) {
		UserList[UserIndex].Counters.Ceguera = UserList[UserIndex].Counters.Ceguera - 1;
	} else {
		if (UserList[UserIndex].flags.Ceguera == 1) {
			UserList[UserIndex].flags.Ceguera = 0;
			WriteBlindNoMore(UserIndex);
		}
		if (UserList[UserIndex].flags.Estupidez == 1) {
			UserList[UserIndex].flags.Estupidez = 0;
			WriteDumbNoMore(UserIndex);
		}

	}

}

void EfectoParalisisUser(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 02/12/2010 */
	/* '02/12/2010: ZaMa - Now non-magic clases lose paralisis effect under certain circunstances. */
	/* '*************************************************** */

	if (UserList[UserIndex].Counters.Paralisis > 0) {

		int CasterIndex;
		CasterIndex = UserList[UserIndex].flags.ParalizedByIndex;

		/* ' Only aplies to non-magic clases */
		if (UserList[UserIndex].Stats.MaxMAN == 0) {
			/* ' Paralized by user? */
			if (CasterIndex != 0) {

				/* ' Close? => Remove Paralisis */
				if (UserList[CasterIndex].Name != UserList[UserIndex].flags.ParalizedBy) {
					RemoveParalisis(UserIndex);
					return;

					/* ' Caster dead? => Remove Paralisis */
				} else if (UserList[CasterIndex].flags.Muerto == 1) {
					RemoveParalisis(UserIndex);
					return;

				} else if (UserList[UserIndex].Counters.Paralisis > IntervaloParalizadoReducido) {
					/* ' Out of vision range? => Reduce paralisis counter */
					if (!InVisionRangeAndMap(UserIndex, UserList[CasterIndex].Pos)) {
						/* ' Aprox. 1500 ms */
						UserList[UserIndex].Counters.Paralisis = IntervaloParalizadoReducido;
						return;
					}
				}

				/* ' Npc? */
			} else {
				CasterIndex = UserList[UserIndex].flags.ParalizedByNpcIndex;

				/* ' Paralized by npc? */
				if (CasterIndex != 0) {

					if (UserList[UserIndex].Counters.Paralisis > IntervaloParalizadoReducido) {
						/* ' Out of vision range? => Reduce paralisis counter */
						if (!InVisionRangeAndMap(UserIndex, Npclist[CasterIndex].Pos)) {
							/* ' Aprox. 1500 ms */
							UserList[UserIndex].Counters.Paralisis = IntervaloParalizadoReducido;
							return;
						}
					}
				}

			}
		}

		UserList[UserIndex].Counters.Paralisis = UserList[UserIndex].Counters.Paralisis - 1;

	} else {
		RemoveParalisis(UserIndex);
	}

}

void RemoveParalisis(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 20/11/2010 */
	/* 'Removes paralisis effect from user. */
	/* '*************************************************** */
	UserList[UserIndex].flags.Paralizado = 0;
	UserList[UserIndex].flags.Inmovilizado = 0;
	UserList[UserIndex].flags.ParalizedBy = "";
	UserList[UserIndex].flags.ParalizedByIndex = 0;
	UserList[UserIndex].flags.ParalizedByNpcIndex = 0;
	UserList[UserIndex].Counters.Paralisis = 0;
	WriteParalizeOK(UserIndex);
}

void RecStamina(int UserIndex, bool & EnviarStats, int Intervalo) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (MapData[UserList[UserIndex].Pos.Map][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].trigger
			== 1
			&& MapData[UserList[UserIndex].Pos.Map][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].trigger
					== 2
			&& MapData[UserList[UserIndex].Pos.Map][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].trigger
					== 4) {
		return;
	}

	int massta;
	if (UserList[UserIndex].Stats.MinSta < UserList[UserIndex].Stats.MaxSta) {
		if (UserList[UserIndex].Counters.STACounter < Intervalo) {
			UserList[UserIndex].Counters.STACounter = UserList[UserIndex].Counters.STACounter + 1;
		} else {
			EnviarStats = true;
			UserList[UserIndex].Counters.STACounter = 0;
			/* 'Desnudo no sube energía. (ToxicWaste) */
			if (UserList[UserIndex].flags.Desnudo) {
				return;
			}

			massta = RandomNumber(1, Porcentaje(UserList[UserIndex].Stats.MaxSta, 5));
			UserList[UserIndex].Stats.MinSta = UserList[UserIndex].Stats.MinSta + massta;
			if (UserList[UserIndex].Stats.MinSta > UserList[UserIndex].Stats.MaxSta) {
				UserList[UserIndex].Stats.MinSta = UserList[UserIndex].Stats.MaxSta;
			}
		}
	}

}

void EfectoVeneno(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int N;

	if (UserList[UserIndex].Counters.Veneno < IntervaloVeneno) {
		UserList[UserIndex].Counters.Veneno = UserList[UserIndex].Counters.Veneno + 1;
	} else {
		WriteConsoleMsg(UserIndex, "Estás envenenado, si no te curas morirás.",
				FontTypeNames_FONTTYPE_VENENO);
		UserList[UserIndex].Counters.Veneno = 0;
		N = RandomNumber(1, 5);
		UserList[UserIndex].Stats.MinHp = UserList[UserIndex].Stats.MinHp - N;
		if (UserList[UserIndex].Stats.MinHp < 1) {
			UserDie(UserIndex);
		}
		WriteUpdateHP(UserIndex);
	}

}

void DuracionPociones(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: ?????? */
	/* 'Last Modification: 11/27/09 (Budi) */
	/* 'Cuando se pierde el efecto de la poción updatea fz y agi (No me gusta que ambos atributos aunque se haya modificado solo uno, pero bueno :p) */
	/* '*************************************************** */
	/* 'Controla la duracion de las pociones */
	if (UserList[UserIndex].flags.DuracionEfecto > 0) {
		UserList[UserIndex].flags.DuracionEfecto = UserList[UserIndex].flags.DuracionEfecto - 1;
		if (UserList[UserIndex].flags.DuracionEfecto == 0) {
			UserList[UserIndex].flags.TomoPocion = false;
			UserList[UserIndex].flags.TipoPocion = 0;
			/* 'volvemos los atributos al estado normal */
			int loopX;

			for (loopX = (1); loopX <= (NUMATRIBUTOS); loopX++) {
				UserList[UserIndex].Stats.UserAtributos[loopX] =
						UserList[UserIndex].Stats.UserAtributosBackUP[loopX];
			}

			WriteUpdateStrenghtAndDexterity(UserIndex);
		}
	}

}

void HambreYSed(int UserIndex, bool & fenviarAyS) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (!UserTienePrivilegio(UserIndex, PlayerType_User)) {
		return;
	}

	/* 'Sed */
	if (UserList[UserIndex].Stats.MinAGU > 0) {
		if (UserList[UserIndex].Counters.AGUACounter < IntervaloSed) {
			UserList[UserIndex].Counters.AGUACounter = UserList[UserIndex].Counters.AGUACounter + 1;
		} else {
			UserList[UserIndex].Counters.AGUACounter = 0;
			UserList[UserIndex].Stats.MinAGU = UserList[UserIndex].Stats.MinAGU - 10;

			if (UserList[UserIndex].Stats.MinAGU <= 0) {
				UserList[UserIndex].Stats.MinAGU = 0;
				UserList[UserIndex].flags.Sed = 1;
			}

			fenviarAyS = true;
		}
	}

	/* 'hambre */
	if (UserList[UserIndex].Stats.MinHam > 0) {
		if (UserList[UserIndex].Counters.COMCounter < IntervaloHambre) {
			UserList[UserIndex].Counters.COMCounter = UserList[UserIndex].Counters.COMCounter + 1;
		} else {
			UserList[UserIndex].Counters.COMCounter = 0;
			UserList[UserIndex].Stats.MinHam = UserList[UserIndex].Stats.MinHam - 10;
			if (UserList[UserIndex].Stats.MinHam <= 0) {
				UserList[UserIndex].Stats.MinHam = 0;
				UserList[UserIndex].flags.Hambre = 1;
			}
			fenviarAyS = true;
		}
	}

}

void Sanar(int UserIndex, bool & EnviarStats, int Intervalo) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (MapData[UserList[UserIndex].Pos.Map][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].trigger
			== 1
			&& MapData[UserList[UserIndex].Pos.Map][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].trigger
					== 2
			&& MapData[UserList[UserIndex].Pos.Map][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].trigger
					== 4) {
		return;
	}

	int mashit;
	/* 'con el paso del tiempo va sanando....pero muy lentamente ;-) */
	if (UserList[UserIndex].Stats.MinHp < UserList[UserIndex].Stats.MaxHp) {
		if (UserList[UserIndex].Counters.HPCounter < Intervalo) {
			UserList[UserIndex].Counters.HPCounter = UserList[UserIndex].Counters.HPCounter + 1;
		} else {
			mashit = RandomNumber(2, Porcentaje(UserList[UserIndex].Stats.MaxSta, 5));

			UserList[UserIndex].Counters.HPCounter = 0;
			UserList[UserIndex].Stats.MinHp = UserList[UserIndex].Stats.MinHp + mashit;
			if (UserList[UserIndex].Stats.MinHp > UserList[UserIndex].Stats.MaxHp) {
				UserList[UserIndex].Stats.MinHp = UserList[UserIndex].Stats.MaxHp;
			}
			WriteConsoleMsg(UserIndex, "Has sanado.", FontTypeNames_FONTTYPE_INFO);
			EnviarStats = true;
		}
	}

}

void CargaNpcsDat() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	std::string npcfile;

	npcfile = GetDatPath(DATPATH::NPCs);
	LeerNPCs.reset(new clsIniManager());
	LeerNPCs->Initialize(npcfile);
}

void PasarSegundo() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int i;

	for (i = (1); i <= (LastUser); i++) {
		if (UserList[i].flags.UserLogged) {
			/* 'Cerrar usuario */
			if (UserList[i].Counters.Saliendo) {
				UserList[i].Counters.Salir = UserList[i].Counters.Salir - 1;
				if (UserList[i].Counters.Salir <= 0) {
					if (UserIndexSocketValido(i)) {
						WriteConsoleMsg(i, "Gracias por jugar Argentum Online", FontTypeNames_FONTTYPE_INFO);
						WriteDisconnect(i);
						FlushBuffer(i);
					}
					CloseSocket(i);
				}
			}
		}
	}
}

#if 0
double ReiniciarAutoUpdate() {

}

void ReiniciarServidor(bool EjecutarLauncher) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	/* 'WorldSave */
	DoBackUp;

	/* 'commit experiencias */
	ActualizaExperiencias;

	/* 'Guardar Pjs */
	GuardarUsuarios();

	if (EjecutarLauncher) {
		vb6::Shell(vb6::App().Path + "/launcher.exe");
	}

	/* 'Chauuu */
	Unload (frmMain);

}
#endif

void GuardarUsuarios() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	haciendoBK = true;

	SendData(SendTarget_ToAll, 0,
			dakara::protocol::server::BuildPauseToggle());
	SendData(SendTarget_ToAll, 0,
			dakara::protocol::server::BuildConsoleMsg("Servidor> Grabando Personajes", FontTypeNames_FONTTYPE_SERVER));

	int i;
	for (i = (1); i <= (LastUser); i++) {
		if (UserList[i].flags.UserLogged) {
			SaveUser(i, GetCharPath(UserList[i].Name), false);
		}
	}

	/* 'se guardan los seguimientos */
	SaveRecords();

	SendData(SendTarget_ToAll, 0,
			dakara::protocol::server::BuildConsoleMsg("Servidor> Personajes Grabados", FontTypeNames_FONTTYPE_SERVER));
	SendData(SendTarget_ToAll, 0,
			dakara::protocol::server::BuildPauseToggle());

	haciendoBK = false;
}

void InicializaEstadisticas() {

}

void FreeNPCs() {
	/* '*************************************************** */
	/* 'Autor: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Releases all NPC Indexes */
	/* '*************************************************** */
	int LoopC;

	/* ' Free all NPC indexes */
	for (LoopC = (1); LoopC <= (MAXNPCS); LoopC++) {
		Npclist[LoopC].flags.NPCActive = false;
	}
}

void FreeCharIndexes() {

}
