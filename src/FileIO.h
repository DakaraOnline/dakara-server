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

#ifndef ES_H
#define ES_H

#include <vector>
#include <memory>
#include <string>
#include <iosfwd>

#include "vb6compat.h"
#include "enums.h"

enum class EGUILDPATH {
	Members,
	Relaciones,
	Propositions,
	Solicitudes,
	Votaciones
};

enum class DATPATH {
	apuestas,
	AreasStats,
	NPCs,
	UserRecords,
	bkNpcs,
	NombresInvalidos,
	Hechizos,
	ArmasHerrero,
	ArmadurasHerrero,
	ArmadurasFaccionarias,
	Balance,
	Ciudades,
	ObjCarpintero,
	Map,
	Obj,
	Help,
	BanIps,
	Invokar,
	MOTD,
	Consultas,
	GuildsInfo,
	SecurityIp,
	EmailsHabilitados,
	Stats
};

std::string GetAppPath();

std::string GetGuildsPath(std::string guildName, EGUILDPATH fileType);

std::string GetIniPath(std::string baseName);

std::string GetCharPath(std::string baseName);

std::string GetMapPath(int mapNum, MAPPATH fileType, bool backup = false);

std::string GetLogFileName(const std::string& baseName);

std::string GetForumPath(std::string ForoID);

std::string GetForumMsgPath(std::string ForoID, int PostIndex, bool post);

std::string GetDatPath(DATPATH fileType);

void CargarSpawnList();

bool EsAdmin(const std::string & Name);

bool EsDios(const std::string & Name);

bool EsSemiDios(const std::string & Name);

bool EsGmEspecial(const std::string & Name);

bool EsConsejero(const std::string & Name);

bool EsRolesMaster(const std::string & Name);

bool EsGmChar(const std::string & Name);

void loadAdministrativeUsers();

PlayerType GetCharPrivs(const std::string & UserName);

int TxtDimension(const std::string & Name);

void CargarForbidenWords();

void CargarHechizos();

void LoadMotd();

void DoBackUp();

void GrabarMapa(int Map, bool loadFromBackup);

void LoadArmasHerreria();

void LoadArmadurasHerreria();

void LoadBalance();

void LoadObjCarpintero();

void LoadOBJData();

void LoadUserStats(int UserIndex, std::shared_ptr<clsIniManager> & UserFile);

void LoadUserReputacion(int UserIndex, std::shared_ptr<clsIniManager> & UserFile);

void LoadUserInit(int UserIndex, std::shared_ptr<clsIniManager> & UserFile);

/* # IF ConUpTime THEN */
/* # END IF */

std::string GetVar(std::string File, std::string Main, std::string Var, int EmptySpaces = 1024);

void CargarBackUp();

void LoadMapData();

void CargarMapa(int Map, bool loadFromBackup);

void LoadSini();

/* # IF SeguridadAlkon THEN */

/* # END IF */

/* # IF SeguridadAlkon THEN */
/* # END IF */

void WriteVar(std::string File, std::string Main, std::string Var, int value);

void WriteVar(std::string File, std::string Main, std::string Var, std::string value);

void WriteSaltedPasswordUserRAW(const std::string& Name, const std::string& Salt, const std::string& HashedPassword);

void WriteSaltedPasswordUserCopyFrom(const std::string& UserName, const std::string& copyFrom);

void WriteSaltedPasswordUser(const std::string& Name, const std::string& Password);

bool CheckPasswordUser(const std::string& Name, const std::string& Password);

void SaveUser(int UserIndex, std::string UserFile, bool SaveTimeOnline = true);

/* # IF ConUpTime THEN */

/* # END IF */

bool criminal(int UserIndex);

void BackUPnPc(int NpcIndex, std::ofstream& npcfile);

void CargarNpcBackUp(int NpcIndex, int NpcNumber);

void Ban(std::string BannedName, std::string Baneador, std::string Motivo);

void CargaApuestas();

void generateMatrix();

void setDistance(int mapa, int city, int side, int X = 0, int Y = 0);

int getLimit(int mapa, eHeading side);

void LoadArmadurasFaccion();

#endif
