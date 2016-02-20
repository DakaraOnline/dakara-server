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

#include "FileIO.h"
#include "Crypto.h"

std::string GetAppPath() {
	return DakaraBasePath;
}

std::string GetGuildsPath(std::string guildName, EGUILDPATH fileType) {
	std::string ext;

	switch (fileType) {
	case EGUILDPATH::Members:
		ext = "-Members.ini";
		break;

	case EGUILDPATH::Propositions:
		ext = "-Propositions.ini";
		break;

	case EGUILDPATH::Relaciones:
		ext = "-Relaciones.ini";
		break;

	case EGUILDPATH::Solicitudes:
		ext = "-Solicitudes.ini";
		break;

	case EGUILDPATH::Votaciones:
		ext = "-Votaciones.ini";
		break;

	default:
		throw std::runtime_error("unknown fileType");
	}

	return DakaraBasePath + "guilds/" + guildName + ext;
}

std::string GetIniPath(std::string baseName) {
	return DakaraBasePath + baseName;
}

std::string GetCharPath(std::string baseName) {
	return DakaraBasePath + "Charfile/" + vb6::UCase(baseName) + ".chr";
}

std::string GetMapPath(int mapNum, MAPPATH filetype, bool backup) {
	std::string base = backup ? "WorldBackup/mapa" : "Maps/mapa";

	switch (filetype) {
	case MAPPATH::DAT:
		return DakaraBasePath + base + std::to_string(mapNum) + ".dat";

	case MAPPATH::INF:
		return DakaraBasePath + base + std::to_string(mapNum) + ".inf";

	case MAPPATH::MAP:
		return DakaraBasePath + base + std::to_string(mapNum) + ".map";

	default:
		throw std::runtime_error("unknown fileType");
	}
}

std::string GetDatPath(DATPATH fileType) {
	std::string datpath = DakaraBasePath + "dat/";

	switch (fileType) {
	case DATPATH::apuestas:
		return datpath + "apuestas.dat";
	case DATPATH::AreasStats:
		return datpath + "AreasStats.dat";
	case DATPATH::NPCs:
		return datpath + "NPCs.dat";
	case DATPATH::UserRecords:
		return datpath + "UserRecords.dat";
	case DATPATH::bkNpcs:
		return datpath + "bkNpcs.dat";
	case DATPATH::NombresInvalidos:
		return datpath + "NombresInvalidos.dat";
	case DATPATH::Hechizos:
		return datpath + "Hechizos.dat";
	case DATPATH::ArmasHerrero:
		return datpath + "ArmasHerrero.dat";
	case DATPATH::ArmadurasHerrero:
		return datpath + "ArmadurasHerrero.dat";
	case DATPATH::ArmadurasFaccionarias:
		return datpath + "ArmadurasFaccionarias.dat";
	case DATPATH::Balance:
		return datpath + "Balance.dat";
	case DATPATH::Ciudades:
		return datpath + "Ciudades.dat";
	case DATPATH::ObjCarpintero:
		return datpath + "ObjCarpintero.dat";
	case DATPATH::Map:
		return datpath + "Map.dat";
	case DATPATH::Obj:
		return datpath + "Obj.dat";
	case DATPATH::Help:
		return datpath + "Help.dat";
	case DATPATH::BanIps:
		return datpath + "BanIps.dat";
	case DATPATH::Invokar:
		return datpath + "Invokar.dat";
	case DATPATH::MOTD:
		return datpath + "MOTD.dat";
	case DATPATH::Consultas:
		return datpath + "Consultas.dat";
	case DATPATH::GuildsInfo:
		return datpath + "GuildsInfo.dat";
	case DATPATH::SecurityIp:
		return datpath + "SecurityIp.dat";
	case DATPATH::EmailsHabilitados:
		return datpath + "EmailsHabilitados.dat";
	case DATPATH::Stats:
		return datpath + "stats.dat";
	default:
		throw std::runtime_error("unknown fileType");
	}
}

std::string GetLogFileName(const std::string& baseName) {
	return DakaraBasePath + "logs/" + baseName + ".log";
}

std::string GetForumPath(std::string ForoID) {
	// vb6::App().Path + "/foros/" + sForoID + ".for";
	return DakaraBasePath + "foros/" + (ForoID) + ".for";
}

std::string GetForumMsgPath(std::string ForoID, int PostIndex, bool post) {
	// PostPath = vb6::App().Path + "/foros/" + vb6::CStr(sForoID) + "-" + vb6::CStr(PostIndex) + ".for";
	// vb6::App().Path + "/Foros/" + vb6::CStr(Foros[ForumIndex].ID) + "-" + vb6::CStr(PostIndex) + "a.for"
	return DakaraBasePath + "foros/" + (ForoID) + "-" + std::to_string(PostIndex) + (post ? "" : "a") + ".for";
}


void CargarSpawnList() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int N;
	int LoopC;
	clsIniManager leerSp;
	leerSp.Initialize(GetDatPath(DATPATH::Invokar));

	N = vb6::val(leerSp.GetValue("INIT", "NumNPCs"));
	N = vb6::Constrain(N, 0, MAXNPCS);

	SpawnList.redim(0);
	SpawnList.redim(1, N);

	for (LoopC = (1); LoopC <= (N); LoopC++) {
		SpawnList[LoopC].NpcIndex = vb6::val(
				leerSp.GetValue("LIST", "NI" + vb6::CStr(LoopC)));
		SpawnList[LoopC].NpcName = leerSp.GetValue("LIST", "NN" + vb6::CStr(LoopC));
	}

}

bool EsAdmin(const std::string & Name) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 27/03/2011 */
	/* '27/03/2011 - ZaMa: Utilizo la clase para saber los datos. */
	/* '*************************************************** */
	retval = (vb6::val(Administradores->GetValue("Admin", vb6::Replace(Name, "+", " "))) == 1);
	return retval;
}

bool EsDios(const std::string & Name) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 27/03/2011 */
	/* '27/03/2011 - ZaMa: Utilizo la clase para saber los datos. */
	/* '*************************************************** */
	retval = (vb6::val(Administradores->GetValue("Dios", vb6::Replace(Name, "+", " "))) == 1);
	return retval;
}

bool EsSemiDios(const std::string & Name) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 27/03/2011 */
	/* '27/03/2011 - ZaMa: Utilizo la clase para saber los datos. */
	/* '*************************************************** */
	retval = (vb6::val(Administradores->GetValue("SemiDios", vb6::Replace(Name, "+", " "))) == 1);
	return retval;
}

bool EsGmEspecial(const std::string & Name) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 27/03/2011 */
	/* '27/03/2011 - ZaMa: Utilizo la clase para saber los datos. */
	/* '*************************************************** */
	retval = (vb6::val(Administradores->GetValue("Especial", vb6::Replace(Name, "+", " "))) == 1);
	return retval;
}

bool EsConsejero(const std::string & Name) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 27/03/2011 */
	/* '27/03/2011 - ZaMa: Utilizo la clase para saber los datos. */
	/* '*************************************************** */
	retval = (vb6::val(Administradores->GetValue("Consejero", vb6::Replace(Name, "+", " "))) == 1);
	return retval;
}

bool EsRolesMaster(const std::string & Name) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 27/03/2011 */
	/* '27/03/2011 - ZaMa: Utilizo la clase para saber los datos. */
	/* '*************************************************** */
	retval = (vb6::val(Administradores->GetValue("RM", vb6::Replace(Name, "+", " "))) == 1);
	return retval;
}

bool EsGmChar(const std::string & Name) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 27/03/2011 */
	/* 'Returns true if char is administrative user. */
	/* '*************************************************** */

	bool EsGm;

	/* ' Admin? */
	EsGm = EsAdmin(Name);
	/* ' Dios? */
	if (!EsGm) {
		EsGm = EsDios(Name);
	}
	/* ' Semidios? */
	if (!EsGm) {
		EsGm = EsSemiDios(Name);
	}
	/* ' Consejero? */
	if (!EsGm) {
		EsGm = EsConsejero(Name);
	}

	retval = EsGm;

	return retval;
}

void loadAdministrativeUsers() {
	/* 'Admines     => Admin */
	/* 'Dioses      => Dios */
	/* 'SemiDioses  => SemiDios */
	/* 'Especiales  => Especial */
	/* 'Consejeros  => Consejero */
	/* 'RoleMasters => RM */

	/* 'Si esta mierda tuviese array asociativos el código sería tan lindo. */
	int buf;
	int i;
	std::string Name;

	/* ' Public container */
	Administradores.reset(new clsIniManager());

	/* ' Server ini info file */
	std::shared_ptr<clsIniManager> ServerIni;
	ServerIni.reset(new clsIniManager());

	ServerIni->Initialize(GetIniPath("server.ini"));

	/* ' Admines */
	buf = vb6::val(ServerIni->GetValue("INIT", "Admines"));
	buf = vb6::Constrain(buf, 0, MAX_SPECIAL_USERS);

	for (i = (1); i <= (buf); i++) {
		Name = vb6::UCase(ServerIni->GetValue("Admines", "Admin" + vb6::CStr(i)));

		if (vb6::Left(Name, 1) == "*" || vb6::Left(Name, 1) == "+") {
			Name = vb6::Right(Name, vb6::Len(Name) - 1);
		}

		/* ' Add key */
		Administradores->ChangeValue("Admin", Name, "1");

	}

	/* ' Dioses */
	buf = vb6::val(ServerIni->GetValue("INIT", "Dioses"));
	buf = vb6::Constrain(buf, 0, MAX_SPECIAL_USERS);

	for (i = (1); i <= (buf); i++) {
		Name = vb6::UCase(ServerIni->GetValue("Dioses", "Dios" + vb6::CStr(i)));

		if (vb6::Left(Name, 1) == "*" || vb6::Left(Name, 1) == "+") {
			Name = vb6::Right(Name, vb6::Len(Name) - 1);
		}

		/* ' Add key */
		Administradores->ChangeValue("Dios", Name, "1");

	}

	/* ' Especiales */
	buf = vb6::val(ServerIni->GetValue("INIT", "Especiales"));
	buf = vb6::Constrain(buf, 0, MAX_SPECIAL_USERS);

	for (i = (1); i <= (buf); i++) {
		Name = vb6::UCase(ServerIni->GetValue("Especiales", "Especial" + vb6::CStr(i)));

		if (vb6::Left(Name, 1) == "*" || vb6::Left(Name, 1) == "+") {
			Name = vb6::Right(Name, vb6::Len(Name) - 1);
		}

		/* ' Add key */
		Administradores->ChangeValue("Especial", Name, "1");

	}

	/* ' SemiDioses */
	buf = vb6::val(ServerIni->GetValue("INIT", "SemiDioses"));
	buf = vb6::Constrain(buf, 0, MAX_SPECIAL_USERS);

	for (i = (1); i <= (buf); i++) {
		Name = vb6::UCase(ServerIni->GetValue("SemiDioses", "SemiDios" + vb6::CStr(i)));

		if (vb6::Left(Name, 1) == "*" || vb6::Left(Name, 1) == "+") {
			Name = vb6::Right(Name, vb6::Len(Name) - 1);
		}

		/* ' Add key */
		Administradores->ChangeValue("SemiDios", Name, "1");

	}

	/* ' Consejeros */
	buf = vb6::val(ServerIni->GetValue("INIT", "Consejeros"));
	buf = vb6::Constrain(buf, 0, MAX_SPECIAL_USERS);

	for (i = (1); i <= (buf); i++) {
		Name = vb6::UCase(ServerIni->GetValue("Consejeros", "Consejero" + vb6::CStr(i)));

		if (vb6::Left(Name, 1) == "*" || vb6::Left(Name, 1) == "+") {
			Name = vb6::Right(Name, vb6::Len(Name) - 1);
		}

		/* ' Add key */
		Administradores->ChangeValue("Consejero", Name, "1");

	}

	/* ' RolesMasters */
	buf = vb6::val(ServerIni->GetValue("INIT", "RolesMasters"));
	buf = vb6::Constrain(buf, 0, MAX_SPECIAL_USERS);

	for (i = (1); i <= (buf); i++) {
		Name = vb6::UCase(ServerIni->GetValue("RolesMasters", "RM" + vb6::CStr(i)));

		if (vb6::Left(Name, 1) == "*" || vb6::Left(Name, 1) == "+") {
			Name = vb6::Right(Name, vb6::Len(Name) - 1);
		}

		/* ' Add key */
		Administradores->ChangeValue("RM", Name, "1");
	}

	ServerIni.reset();

}

PlayerType GetCharPrivs(const std::string & UserName) {
	PlayerType retval;
	/* '**************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 18/11/2010 */
	/* 'Reads the user's charfile and retrieves its privs. */
	/* '*************************************************** */

	PlayerType Privs;

	if (EsAdmin(UserName)) {
		Privs = PlayerType_Admin;

	} else if (EsDios(UserName)) {
		Privs = PlayerType_Dios;

	} else if (EsSemiDios(UserName)) {
		Privs = PlayerType_SemiDios;

	} else if (EsConsejero(UserName)) {
		Privs = PlayerType_Consejero;

	} else {
		Privs = PlayerType_User;
	}

	retval = Privs;

	return retval;
}

int TxtDimension(const std::string & Name) {
	int retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	std::string cad;
	int Tam = 0;

	std::ifstream in;
	in.open(Name);
	while (std::getline(in, cad)) {
		Tam++;
	}
	retval = Tam;
	return retval;
}

void CargarForbidenWords() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	ForbidenNames.redim(0);
	ForbidenNames.redim(1, TxtDimension(GetDatPath(DATPATH::NombresInvalidos)));
	int i;

	std::ifstream in;
	in.open(GetDatPath(DATPATH::NombresInvalidos));

	for (i = (1); i <= (vb6::UBound(ForbidenNames)); i++) {
		std::getline(in, ForbidenNames[i]);
	}

	in.close();

}

void CargarHechizos() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	std::cout << "Cargando Hechizos." << std::endl;

	int Hechizo;
	std::shared_ptr<clsIniManager> Leer;
	Leer.reset(new clsIniManager());

	Leer->Initialize(GetDatPath(DATPATH::Hechizos));

	/* 'obtiene el numero de hechizos */
	NumeroHechizos = vb6::val(Leer->GetValue("INIT", "NumeroHechizos"));

	Hechizos.redim(0);
	Hechizos.redim(1, NumeroHechizos);

	/* 'Llena la lista */
	for (Hechizo = (1); Hechizo <= (NumeroHechizos); Hechizo++) {
		std::string hechizostr = "HECHIZO" + vb6::CStr(Hechizo);
		Hechizos[Hechizo].Nombre = Leer->GetValue(hechizostr, "Nombre");
		Hechizos[Hechizo].desc = Leer->GetValue(hechizostr, "Desc");
		Hechizos[Hechizo].PalabrasMagicas = Leer->GetValue(hechizostr, "PalabrasMagicas");

		Hechizos[Hechizo].HechizeroMsg = Leer->GetValue(hechizostr, "HechizeroMsg");
		Hechizos[Hechizo].TargetMsg = Leer->GetValue(hechizostr, "TargetMsg");
		Hechizos[Hechizo].PropioMsg = Leer->GetValue(hechizostr, "PropioMsg");

		Hechizos[Hechizo].Tipo = static_cast<enum TipoHechizo>(vb6::CInt(Leer->GetValue(hechizostr, "Tipo")));
		Hechizos[Hechizo].WAV = vb6::val(Leer->GetValue(hechizostr, "WAV"));
		Hechizos[Hechizo].FXgrh = vb6::val(Leer->GetValue(hechizostr, "Fxgrh"));

		Hechizos[Hechizo].loops = vb6::val(Leer->GetValue(hechizostr, "Loops"));

		/* '    .Resis = val(Leer.GetValue("Hechizo" & Hechizo, "Resis")) */

		Hechizos[Hechizo].SubeHP = vb6::val(Leer->GetValue(hechizostr, "SubeHP"));
		Hechizos[Hechizo].MinHp = vb6::val(Leer->GetValue(hechizostr, "MinHP"));
		Hechizos[Hechizo].MaxHp = vb6::val(Leer->GetValue(hechizostr, "MaxHP"));

		Hechizos[Hechizo].SubeMana = vb6::val(Leer->GetValue(hechizostr, "SubeMana"));
		Hechizos[Hechizo].MiMana = vb6::val(Leer->GetValue(hechizostr, "MinMana"));
		Hechizos[Hechizo].MaMana = vb6::val(Leer->GetValue(hechizostr, "MaxMana"));

		Hechizos[Hechizo].SubeSta = vb6::val(Leer->GetValue(hechizostr, "SubeSta"));
		Hechizos[Hechizo].MinSta = vb6::val(Leer->GetValue(hechizostr, "MinSta"));
		Hechizos[Hechizo].MaxSta = vb6::val(Leer->GetValue(hechizostr, "MaxSta"));

		Hechizos[Hechizo].SubeHam = vb6::val(Leer->GetValue(hechizostr, "SubeHam"));
		Hechizos[Hechizo].MinHam = vb6::val(Leer->GetValue(hechizostr, "MinHam"));
		Hechizos[Hechizo].MaxHam = vb6::val(Leer->GetValue(hechizostr, "MaxHam"));

		Hechizos[Hechizo].SubeSed = vb6::val(Leer->GetValue(hechizostr, "SubeSed"));
		Hechizos[Hechizo].MinSed = vb6::val(Leer->GetValue(hechizostr, "MinSed"));
		Hechizos[Hechizo].MaxSed = vb6::val(Leer->GetValue(hechizostr, "MaxSed"));

		Hechizos[Hechizo].SubeAgilidad = vb6::val(Leer->GetValue(hechizostr, "SubeAG"));
		Hechizos[Hechizo].MinAgilidad = vb6::val(Leer->GetValue(hechizostr, "MinAG"));
		Hechizos[Hechizo].MaxAgilidad = vb6::val(Leer->GetValue(hechizostr, "MaxAG"));

		Hechizos[Hechizo].SubeFuerza = vb6::val(Leer->GetValue(hechizostr, "SubeFU"));
		Hechizos[Hechizo].MinFuerza = vb6::val(Leer->GetValue(hechizostr, "MinFU"));
		Hechizos[Hechizo].MaxFuerza = vb6::val(Leer->GetValue(hechizostr, "MaxFU"));

		Hechizos[Hechizo].SubeCarisma = vb6::val(Leer->GetValue(hechizostr, "SubeCA"));
		Hechizos[Hechizo].MinCarisma = vb6::val(Leer->GetValue(hechizostr, "MinCA"));
		Hechizos[Hechizo].MaxCarisma = vb6::val(Leer->GetValue(hechizostr, "MaxCA"));

		Hechizos[Hechizo].Invisibilidad = vb6::val(Leer->GetValue(hechizostr, "Invisibilidad"));
		Hechizos[Hechizo].Paraliza = vb6::val(Leer->GetValue(hechizostr, "Paraliza"));
		Hechizos[Hechizo].Inmoviliza = vb6::val(Leer->GetValue(hechizostr, "Inmoviliza"));
		Hechizos[Hechizo].RemoverParalisis = vb6::val(Leer->GetValue(hechizostr, "RemoverParalisis"));
		Hechizos[Hechizo].RemoverEstupidez = vb6::val(Leer->GetValue(hechizostr, "RemoverEstupidez"));
		Hechizos[Hechizo].RemueveInvisibilidadParcial = vb6::val(
				Leer->GetValue(hechizostr, "RemueveInvisibilidadParcial"));

		Hechizos[Hechizo].CuraVeneno = vb6::val(Leer->GetValue(hechizostr, "CuraVeneno"));
		Hechizos[Hechizo].Envenena = vb6::val(Leer->GetValue(hechizostr, "Envenena"));
		Hechizos[Hechizo].Maldicion = vb6::val(Leer->GetValue(hechizostr, "Maldicion"));
		Hechizos[Hechizo].RemoverMaldicion = vb6::val(Leer->GetValue(hechizostr, "RemoverMaldicion"));
		Hechizos[Hechizo].Bendicion = vb6::val(Leer->GetValue(hechizostr, "Bendicion"));
		Hechizos[Hechizo].Revivir = vb6::val(Leer->GetValue(hechizostr, "Revivir"));

		Hechizos[Hechizo].Ceguera = vb6::val(Leer->GetValue(hechizostr, "Ceguera"));
		Hechizos[Hechizo].Estupidez = vb6::val(Leer->GetValue(hechizostr, "Estupidez"));

		Hechizos[Hechizo].Warp = vb6::val(Leer->GetValue(hechizostr, "Warp"));

		Hechizos[Hechizo].Invoca = vb6::val(Leer->GetValue(hechizostr, "Invoca"));
		Hechizos[Hechizo].NumNpc = vb6::val(Leer->GetValue(hechizostr, "NumNpc"));
		Hechizos[Hechizo].cant = vb6::val(Leer->GetValue(hechizostr, "Cant"));
		Hechizos[Hechizo].Mimetiza = vb6::val(Leer->GetValue(hechizostr, "Mimetiza"));

		/* '    .Materializa = val(Leer.GetValue("Hechizo" & Hechizo, "Materializa")) */
		/* '    .ItemIndex = val(Leer.GetValue("Hechizo" & Hechizo, "ItemIndex")) */

		Hechizos[Hechizo].MinSkill = vb6::val(Leer->GetValue(hechizostr, "MinSkill"));
		Hechizos[Hechizo].ManaRequerido = vb6::val(Leer->GetValue(hechizostr, "ManaRequerido"));

		/* 'Barrin 30/9/03 */
		Hechizos[Hechizo].StaRequerido = vb6::val(Leer->GetValue(hechizostr, "StaRequerido"));

		Hechizos[Hechizo].Target =
				static_cast<enum TargetType>(vb6::CInt(Leer->GetValue(hechizostr, "Target")));

		Hechizos[Hechizo].NeedStaff = vb6::val(Leer->GetValue(hechizostr, "NeedStaff"));
		Hechizos[Hechizo].StaffAffected = vb6::CBool(vb6::val(Leer->GetValue(hechizostr, "StaffAffected")));
	}

	Leer.reset();

	return;
}

void LoadMotd() {
	int i;
	int MaxLines = vb6::CInt(GetVar(GetDatPath(DATPATH::MOTD), "INIT", "NumLines"));
	MaxLines = vb6::Constrain(MaxLines, 0, MAX_HELP_LINES);

	MOTD.redim(1, MaxLines);
	for (i = (1); i <= (MaxLines); i++) {
		MOTD[i].texto = GetVar(GetDatPath(DATPATH::MOTD), "Motd", "Line" + vb6::CStr(i));
		MOTD[i].Formato = "";
	}

    PopupOfTheDayMessage = vb6::Trim(GetVar(GetDatPath(DATPATH::MOTD), "POTD", "Message"));
    EnviarPopupOfTheDay = PopupOfTheDayMessage.size() > 0;
}

void DoBackUp() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	haciendoBK = true;

	/* ' Lo saco porque elimina elementales y mascotas - Maraxus */
	/* ''''''''''''''lo pongo aca x sugernecia del yind */
	/* 'For i = 1 To LastNPC */
	/* '    If Npclist(i).flags.NPCActive Then */
	/* '        If Npclist(i).Contadores.TiempoExistencia > 0 Then */
	/* '            Call MuereNpc(i, 0) */
	/* '        End If */
	/* '    End If */
	/* 'Next i */
	/* '''''''''''/'lo pongo aca x sugernecia del yind */

	SendData(SendTarget_ToAll, 0,
			dakara::protocol::server::BuildPauseToggle());

	LimpiarMundo();
	WorldSave();
	v_RutinaElecciones();
	/* 'Call ResetCentinelaInfo     'Reseteamos al centinela 'Lo saco porque ahora el reset lo maneja el modCentinela [C4b3z0n] */

	SendData(SendTarget_ToAll, 0,
			dakara::protocol::server::BuildPauseToggle());

	/* 'Call EstadisticasWeb.Informar(EVENTO_NUEVO_CLAN, 0) */

	haciendoBK = false;

	/* 'Log */
	LogBackUp();
}

void GrabarMapa(int Map, bool loadFromBackup) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 12/01/2011 */
	/* '10/08/2010 - Pato: Implemento el clsByteBuffer para el grabado de mapas */
	/* '28/10/2010:ZaMa - Ahora no se hace backup de los pretorianos. */
	/* '12/01/2011 - Amraphen: Ahora no se hace backup de NPCs prohibidos (Pretorianos, Mascotas, Invocados y Centinela) */
	/* '*************************************************** */

	int Y;
	int X;
	int ByFlags;
	int LoopC;
	std::shared_ptr<clsByteBuffer> MapWriter;
	std::shared_ptr<clsByteBuffer> InfWriter;
	std::shared_ptr<clsIniManager> IniManager;
	bool NpcInvalido;

	MapWriter.reset(new clsByteBuffer());
	InfWriter.reset(new clsByteBuffer());
	IniManager.reset(new clsIniManager());

	MapWriter->initializeWriter();
	InfWriter->initializeWriter();

	/* 'map Header */
	MapWriter->putInteger(MapInfo[Map].MapVersion);

	MiCabecera.desc = std::string(255, ' ');

	MapWriter->putString(MiCabecera.desc, false);
	MapWriter->putLong(MiCabecera.crc);
	MapWriter->putLong(MiCabecera.MagicWord);

	MapWriter->putDouble(0);

	/* 'inf Header */
	InfWriter->putDouble(0);
	InfWriter->putInteger(0);

	/* 'Write .map file */
	for (Y = (YMinMapSize); Y <= (YMaxMapSize); Y++) {
		for (X = (XMinMapSize); X <= (XMaxMapSize); X++) {
			ByFlags = 0;

			if (MapData[Map][X][Y].Blocked) {
				ByFlags = ByFlags | 1;
			}
			if (MapData[Map][X][Y].Graphic[2]) {
				ByFlags = ByFlags | 2;
			}
			if (MapData[Map][X][Y].Graphic[3]) {
				ByFlags = ByFlags | 4;
			}
			if (MapData[Map][X][Y].Graphic[4]) {
				ByFlags = ByFlags | 8;
			}
			if (MapData[Map][X][Y].trigger) {
				ByFlags = ByFlags | 16;
			}

			MapWriter->putByte(ByFlags);

			MapWriter->putInteger(MapData[Map][X][Y].Graphic[1]);

			for (LoopC = (2); LoopC <= (4); LoopC++) {
				if (MapData[Map][X][Y].Graphic[LoopC]) {
					MapWriter->putInteger(MapData[Map][X][Y].Graphic[LoopC]);
				}
			}

			if (MapData[Map][X][Y].trigger) {
				MapWriter->putInteger(vb6::CInt(MapData[Map][X][Y].trigger));
			}

			/* '.inf file */
			ByFlags = 0;

			if (MapData[Map][X][Y].ObjInfo.ObjIndex > 0) {
				if (ObjData[MapData[Map][X][Y].ObjInfo.ObjIndex].OBJType == eOBJType_otFogata) {
					MapData[Map][X][Y].ObjInfo.ObjIndex = 0;
					MapData[Map][X][Y].ObjInfo.Amount = 0;
				}
			}

			if (MapData[Map][X][Y].TileExit.Map) {
				ByFlags = ByFlags | 1;
			}

			/* ' No hacer backup de los NPCs inválidos (Pretorianos, Mascotas, Invocados y Centinela) */
			if (MapData[Map][X][Y].NpcIndex) {
				NpcInvalido = (Npclist[MapData[Map][X][Y].NpcIndex].NPCtype == eNPCType_Pretoriano)
						|| (Npclist[MapData[Map][X][Y].NpcIndex].MaestroUser > 0)
						|| EsCentinela(MapData[Map][X][Y].NpcIndex);

				if (!NpcInvalido) {
					ByFlags = ByFlags | 2;
				}
			}

			if (MapData[Map][X][Y].ObjInfo.ObjIndex) {
				ByFlags = ByFlags | 4;
			}

			InfWriter->putByte(ByFlags);

			if (MapData[Map][X][Y].TileExit.Map) {
				InfWriter->putInteger(MapData[Map][X][Y].TileExit.Map);
				InfWriter->putInteger(MapData[Map][X][Y].TileExit.X);
				InfWriter->putInteger(MapData[Map][X][Y].TileExit.Y);
			}

			if (MapData[Map][X][Y].NpcIndex && !NpcInvalido) {
				InfWriter->putInteger(Npclist[MapData[Map][X][Y].NpcIndex].Numero);
			}

			if (MapData[Map][X][Y].ObjInfo.ObjIndex) {
				InfWriter->putInteger(MapData[Map][X][Y].ObjInfo.ObjIndex);
				InfWriter->putInteger(MapData[Map][X][Y].ObjInfo.Amount);
			}

			NpcInvalido = false;
		}
	}

	/* 'Open .map file */
	std::ofstream mapfile;
	mapfile.open(GetMapPath(Map, MAPPATH::MAP, loadFromBackup), std::ios::binary | std::ios::out | std::ios::trunc);

	/* 'Open .inf file */
	std::ofstream inffile;
	inffile.open(GetMapPath(Map, MAPPATH::INF, loadFromBackup), std::ios::binary | std::ios::out | std::ios::trunc);

	mapfile.write(reinterpret_cast<const char*>(MapWriter->getBuffer().data()),
			MapWriter->getBuffer().size());
	inffile.write(reinterpret_cast<const char*>(InfWriter->getBuffer().data()),
			InfWriter->getBuffer().size());

	/* 'Close .map file */
	mapfile.close();

	/* 'Close .inf file */
	inffile.close();

	MapWriter.reset();
	InfWriter.reset();

	/* 'write .dat file */
	IniManager->ChangeValue("Mapa" + vb6::CStr(Map), "Name", MapInfo[Map].Name);
	IniManager->ChangeValue("Mapa" + vb6::CStr(Map), "MusicNum", vb6::CStr(MapInfo[Map].Music));
	IniManager->ChangeValue("Mapa" + vb6::CStr(Map), "MagiaSinefecto", vb6::CStr(MapInfo[Map].MagiaSinEfecto));
	IniManager->ChangeValue("Mapa" + vb6::CStr(Map), "InviSinEfecto", vb6::CStr(MapInfo[Map].InviSinEfecto));
	IniManager->ChangeValue("Mapa" + vb6::CStr(Map), "ResuSinEfecto", vb6::CStr(MapInfo[Map].ResuSinEfecto));
	IniManager->ChangeValue("Mapa" + vb6::CStr(Map), "StartPos",
			vb6::CStr(MapInfo[Map].StartPos.Map) + "-" + vb6::CStr(MapInfo[Map].StartPos.X) + "-"
					+ vb6::CStr(MapInfo[Map].StartPos.Y));
	IniManager->ChangeValue("Mapa" + vb6::CStr(Map), "OnDeathGoTo",
			vb6::CStr(MapInfo[Map].OnDeathGoTo.Map) + "-" + vb6::CStr(MapInfo[Map].OnDeathGoTo.X) + "-"
					+ vb6::CStr(MapInfo[Map].OnDeathGoTo.Y));

	IniManager->ChangeValue("Mapa" + vb6::CStr(Map), "Terreno", TerrainByteToString(MapInfo[Map].Terreno));
	IniManager->ChangeValue("Mapa" + vb6::CStr(Map), "Zona", MapInfo[Map].Zona);
	IniManager->ChangeValue("Mapa" + vb6::CStr(Map), "Restringir", RestrictByteToString(MapInfo[Map].Restringir));
	IniManager->ChangeValue("Mapa" + vb6::CStr(Map), "BackUp", vb6::str(MapInfo[Map].BackUp));

	if (MapInfo[Map].Pk) {
		IniManager->ChangeValue("Mapa" + vb6::CStr(Map), "Pk", "0");
	} else {
		IniManager->ChangeValue("Mapa" + vb6::CStr(Map), "Pk", "1");
	}

	IniManager->ChangeValue("Mapa" + vb6::CStr(Map), "OcultarSinEfecto", std::to_string(MapInfo[Map].OcultarSinEfecto));
	IniManager->ChangeValue("Mapa" + vb6::CStr(Map), "InvocarSinEfecto", std::to_string(MapInfo[Map].InvocarSinEfecto));
	IniManager->ChangeValue("Mapa" + vb6::CStr(Map), "NoEncriptarMP", std::to_string(MapInfo[Map].NoEncriptarMP));
	IniManager->ChangeValue("Mapa" + vb6::CStr(Map), "RoboNpcsPermitido",
			std::to_string(MapInfo[Map].RoboNpcsPermitido));

	IniManager->DumpFile(GetMapPath(Map, MAPPATH::DAT, loadFromBackup));

	IniManager.reset();
}

void LoadArmasHerreria() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int N;
	int lc;
	clsIniManager leerArm;
	leerArm.Initialize(GetDatPath(DATPATH::ArmasHerrero));

	N = vb6::val(leerArm.GetValue("INIT", "NumArmas"));
	N = vb6::Constrain(N, 0, MAX_DAT_ITEMS);

	ArmasHerrero.redim(1, N);

	for (lc = (1); lc <= (N); lc++) {
		ArmasHerrero[lc] = vb6::val(leerArm.GetValue("Arma" + vb6::CStr(lc), "Index"));
	}

}

void LoadArmadurasHerreria() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int N;
	int lc;
	clsIniManager leerArm;
	leerArm.Initialize(GetDatPath(DATPATH::ArmadurasHerrero));

	N = vb6::val(leerArm.GetValue("INIT", "NumArmaduras"));
	N = vb6::Constrain(N, 0, MAX_DAT_ITEMS);

	ArmadurasHerrero.redim(1, N);

	for (lc = (1); lc <= (N); lc++) {
		ArmadurasHerrero[lc] = vb6::val(leerArm.GetValue("Armadura" + vb6::CStr(lc), "Index"));
	}

}

void LoadBalance() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 15/04/2010 */
	/* '15/04/2010: ZaMa - Agrego recompensas faccionarias. */
	/* '*************************************************** */

	int i;
	clsIniManager leerBal;
	leerBal.Initialize(GetDatPath(DATPATH::Balance));

	/* 'Modificadores de Clase */
	for (i = (1); i <= (NUMCLASES); i++) {
		ModClase[i].Evasion = vb6::val(leerBal.GetValue("MODEVASION", ListaClases[i]));
		ModClase[i].AtaqueArmas = vb6::val(leerBal.GetValue("MODATAQUEARMAS", ListaClases[i]));
		ModClase[i].AtaqueProyectiles = vb6::val(
				leerBal.GetValue("MODATAQUEPROYECTILES", ListaClases[i]));
		ModClase[i].AtaqueWrestling = vb6::val(
				leerBal.GetValue("MODATAQUEWRESTLING", ListaClases[i]));
		ModClase[i].DanoArmas = vb6::val(leerBal.GetValue("MODDANOARMAS", ListaClases[i]));
		ModClase[i].DanoProyectiles = vb6::val(
				leerBal.GetValue("MODDANOPROYECTILES", ListaClases[i]));
		ModClase[i].DanoWrestling = vb6::val(
				leerBal.GetValue("MODDANOWRESTLING", ListaClases[i]));
		ModClase[i].Escudo = vb6::val(leerBal.GetValue("MODESCUDO", ListaClases[i]));
	}

	/* 'Modificadores de Raza */
	for (i = (1); i <= (NUMRAZAS); i++) {
		ModRaza[i].Fuerza = vb6::val(leerBal.GetValue("MODRAZA", ListaRazas[i] + "Fuerza"));
		ModRaza[i].Agilidad = vb6::val(
				leerBal.GetValue("MODRAZA", ListaRazas[i] + "Agilidad"));
		ModRaza[i].Inteligencia = vb6::val(
				leerBal.GetValue("MODRAZA", ListaRazas[i] + "Inteligencia"));
		ModRaza[i].Carisma = vb6::val(leerBal.GetValue("MODRAZA", ListaRazas[i] + "Carisma"));
		ModRaza[i].Constitucion = vb6::val(
				leerBal.GetValue("MODRAZA", ListaRazas[i] + "Constitucion"));
	}

	/* 'Modificadores de Vida */
	for (i = (1); i <= (NUMCLASES); i++) {
		ModVida[i] = vb6::val(leerBal.GetValue("MODVIDA", ListaClases[i]));
	}

	/* 'Distribución de Vida */
	for (i = (1); i <= (5); i++) {
		DistribucionEnteraVida[i] = vb6::val(
				leerBal.GetValue("DISTRIBUCION", "E" + vb6::CStr(i)));
	}
	for (i = (1); i <= (4); i++) {
		DistribucionSemienteraVida[i] = vb6::val(
				leerBal.GetValue("DISTRIBUCION", "S" + vb6::CStr(i)));
	}

	/* 'Extra */
	PorcentajeRecuperoMana = vb6::val(leerBal.GetValue("EXTRA", "PorcentajeRecuperoMana"));

	/* 'Party */
	ExponenteNivelParty = vb6::val(leerBal.GetValue("PARTY", "ExponenteNivelParty"));

	/* ' Recompensas faccionarias */
	for (i = (1); i <= (NUM_RANGOS_FACCION); i++) {
		RecompensaFacciones[i - 1] = vb6::val(
				leerBal.GetValue("RECOMPENSAFACCION", "Rango" + vb6::CStr(i)));
	}

}

void LoadObjCarpintero() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int N;
	int lc;

	clsIniManager leerCarp;
	leerCarp.Initialize(GetDatPath(DATPATH::ObjCarpintero));

	N = vb6::val(leerCarp.GetValue("INIT", "NumObjs"));
	N = vb6::Constrain(N, 0, MAX_DAT_ITEMS);

	ObjCarpintero.redim(1, N);

	for (lc = (1); lc <= (N); lc++) {
		ObjCarpintero[lc] = vb6::val(leerCarp.GetValue("Obj" + vb6::CStr(lc), "Index"));
	}

}

void LoadOBJData() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	/* 'Call LogTarea("Sub LoadOBJData") */

	std::cout << "Cargando base de datos de los objetos." << std::endl;

	/* '***************************************************************** */
	/* 'Carga la lista de objetos */
	/* '***************************************************************** */
	int Object;
	std::shared_ptr<clsIniManager> Leer;
	Leer.reset(new clsIniManager());

	Leer->Initialize(GetDatPath(DATPATH::Obj));

	/* 'obtiene el numero de obj */
	NumObjDatas = vb6::val(Leer->GetValue("INIT", "NumObjs"));
	NumObjDatas = vb6::Constrain(NumObjDatas, 0, MAX_DAT_ITEMS);

	ObjData.redim(1, NumObjDatas);

	/* 'Llena la lista */
	for (Object = (1); Object <= (NumObjDatas); Object++) {
		std::string objidxstr = "OBJ" + std::to_string(Object);
		ObjData[Object].Name = Leer->GetValue(objidxstr, "Name");

		/* 'Pablo (ToxicWaste) Log de Objetos. */
		ObjData[Object].Log = vb6::val(Leer->GetValue(objidxstr, "Log"));
		ObjData[Object].NoLog = vb6::val(Leer->GetValue(objidxstr, "NoLog"));
		/* '07/09/07 */

		ObjData[Object].GrhIndex = vb6::val(Leer->GetValue(objidxstr, "GrhIndex"));
//    if (ObjData[Object].GrhIndex == 0) {
//    ObjData[Object].GrhIndex = ObjData[Object].GrhIndex;
//   }

		ObjData[Object].OBJType = static_cast<eOBJType>(vb6::CInt(Leer->GetValue(objidxstr, "ObjType")));

		ObjData[Object].Newbie = vb6::val(Leer->GetValue(objidxstr, "Newbie"));

		switch (ObjData[Object].OBJType) {
		case eOBJType_otArmadura:
			ObjData[Object].Real = vb6::val(Leer->GetValue(objidxstr, "Real"));
			ObjData[Object].Caos = vb6::val(Leer->GetValue(objidxstr, "Caos"));
			ObjData[Object].LingH = vb6::val(Leer->GetValue(objidxstr, "LingH"));
			ObjData[Object].LingP = vb6::val(Leer->GetValue(objidxstr, "LingP"));
			ObjData[Object].LingO = vb6::val(Leer->GetValue(objidxstr, "LingO"));
			ObjData[Object].SkHerreria = vb6::val(Leer->GetValue(objidxstr, "SkHerreria"));

			break;

		case eOBJType_otESCUDO:
			ObjData[Object].ShieldAnim = vb6::val(Leer->GetValue(objidxstr, "Anim"));
			ObjData[Object].LingH = vb6::val(Leer->GetValue(objidxstr, "LingH"));
			ObjData[Object].LingP = vb6::val(Leer->GetValue(objidxstr, "LingP"));
			ObjData[Object].LingO = vb6::val(Leer->GetValue(objidxstr, "LingO"));
			ObjData[Object].SkHerreria = vb6::val(Leer->GetValue(objidxstr, "SkHerreria"));
			ObjData[Object].Real = vb6::val(Leer->GetValue(objidxstr, "Real"));
			ObjData[Object].Caos = vb6::val(Leer->GetValue(objidxstr, "Caos"));

			break;

		case eOBJType_otCASCO:
			ObjData[Object].CascoAnim = vb6::val(Leer->GetValue(objidxstr, "Anim"));
			ObjData[Object].LingH = vb6::val(Leer->GetValue(objidxstr, "LingH"));
			ObjData[Object].LingP = vb6::val(Leer->GetValue(objidxstr, "LingP"));
			ObjData[Object].LingO = vb6::val(Leer->GetValue(objidxstr, "LingO"));
			ObjData[Object].SkHerreria = vb6::val(Leer->GetValue(objidxstr, "SkHerreria"));
			ObjData[Object].Real = vb6::val(Leer->GetValue(objidxstr, "Real"));
			ObjData[Object].Caos = vb6::val(Leer->GetValue(objidxstr, "Caos"));

			break;

		case eOBJType_otWeapon:
			ObjData[Object].WeaponAnim = vb6::val(Leer->GetValue(objidxstr, "Anim"));
			ObjData[Object].Apunala = vb6::val(Leer->GetValue(objidxstr, "Apunala"));
			ObjData[Object].Envenena = vb6::val(Leer->GetValue(objidxstr, "Envenena"));
			ObjData[Object].MaxHIT = vb6::val(Leer->GetValue(objidxstr, "MaxHIT"));
			ObjData[Object].MinHIT = vb6::val(Leer->GetValue(objidxstr, "MinHIT"));
			ObjData[Object].proyectil = vb6::val(Leer->GetValue(objidxstr, "Proyectil"));
			ObjData[Object].Municion = vb6::val(Leer->GetValue(objidxstr, "Municiones"));
			ObjData[Object].StaffPower = vb6::val(Leer->GetValue(objidxstr, "StaffPower"));
			ObjData[Object].StaffDamageBonus = vb6::val(Leer->GetValue(objidxstr, "StaffDamageBonus"));
			ObjData[Object].Refuerzo = vb6::val(Leer->GetValue(objidxstr, "Refuerzo"));

			ObjData[Object].LingH = vb6::val(Leer->GetValue(objidxstr, "LingH"));
			ObjData[Object].LingP = vb6::val(Leer->GetValue(objidxstr, "LingP"));
			ObjData[Object].LingO = vb6::val(Leer->GetValue(objidxstr, "LingO"));
			ObjData[Object].SkHerreria = vb6::val(Leer->GetValue(objidxstr, "SkHerreria"));
			ObjData[Object].Real = vb6::val(Leer->GetValue(objidxstr, "Real"));
			ObjData[Object].Caos = vb6::val(Leer->GetValue(objidxstr, "Caos"));

			ObjData[Object].WeaponRazaEnanaAnim = vb6::val(Leer->GetValue(objidxstr, "RazaEnanaAnim"));

			break;

		case eOBJType_otInstrumentos:
			ObjData[Object].Snd1 = vb6::val(Leer->GetValue(objidxstr, "SND1"));
			ObjData[Object].Snd2 = vb6::val(Leer->GetValue(objidxstr, "SND2"));
			ObjData[Object].Snd3 = vb6::val(Leer->GetValue(objidxstr, "SND3"));
			/* 'Pablo (ToxicWaste) */
			ObjData[Object].Real = vb6::val(Leer->GetValue(objidxstr, "Real"));
			ObjData[Object].Caos = vb6::val(Leer->GetValue(objidxstr, "Caos"));

			break;

		case eOBJType_otMinerales:
			ObjData[Object].MinSkill = vb6::val(Leer->GetValue(objidxstr, "MinSkill"));

			break;

		case eOBJType_otPuertas:
		case eOBJType_otBotellaVacia:
		case eOBJType_otBotellaLlena:
			ObjData[Object].IndexAbierta = vb6::val(Leer->GetValue(objidxstr, "IndexAbierta"));
			ObjData[Object].IndexCerrada = vb6::val(Leer->GetValue(objidxstr, "IndexCerrada"));
			ObjData[Object].IndexCerradaLlave = vb6::val(Leer->GetValue(objidxstr, "IndexCerradaLlave"));

			break;

		case eOBJType_otPociones:
			ObjData[Object].TipoPocion = vb6::val(Leer->GetValue(objidxstr, "TipoPocion"));
			ObjData[Object].MaxModificador = vb6::val(Leer->GetValue(objidxstr, "MaxModificador"));
			ObjData[Object].MinModificador = vb6::val(Leer->GetValue(objidxstr, "MinModificador"));
			ObjData[Object].DuracionEfecto = vb6::val(Leer->GetValue(objidxstr, "DuracionEfecto"));

			break;

		case eOBJType_otBarcos:
			ObjData[Object].MinSkill = vb6::val(Leer->GetValue(objidxstr, "MinSkill"));
			ObjData[Object].MaxHIT = vb6::val(Leer->GetValue(objidxstr, "MaxHIT"));
			ObjData[Object].MinHIT = vb6::val(Leer->GetValue(objidxstr, "MinHIT"));

			break;

		case eOBJType_otFlechas:
			ObjData[Object].MaxHIT = vb6::val(Leer->GetValue(objidxstr, "MaxHIT"));
			ObjData[Object].MinHIT = vb6::val(Leer->GetValue(objidxstr, "MinHIT"));
			ObjData[Object].Envenena = vb6::val(Leer->GetValue(objidxstr, "Envenena"));
			ObjData[Object].Paraliza = vb6::val(Leer->GetValue(objidxstr, "Paraliza"));

			/* 'Pablo (ToxicWaste) */
			break;

		case eOBJType_otAnillo:
			ObjData[Object].LingH = vb6::val(Leer->GetValue(objidxstr, "LingH"));
			ObjData[Object].LingP = vb6::val(Leer->GetValue(objidxstr, "LingP"));
			ObjData[Object].LingO = vb6::val(Leer->GetValue(objidxstr, "LingO"));
			ObjData[Object].SkHerreria = vb6::val(Leer->GetValue(objidxstr, "SkHerreria"));
			ObjData[Object].MaxHIT = vb6::val(Leer->GetValue(objidxstr, "MaxHIT"));
			ObjData[Object].MinHIT = vb6::val(Leer->GetValue(objidxstr, "MinHIT"));

			break;

		case eOBJType_otTeleport:
			ObjData[Object].Radio = vb6::val(Leer->GetValue(objidxstr, "Radio"));

			break;

		case eOBJType_otMochilas:
			ObjData[Object].MochilaType = vb6::val(Leer->GetValue(objidxstr, "MochilaType"));

			break;

		case eOBJType_otForos:
			AddForum(Leer->GetValue(objidxstr, "ID"));

			break;

		default:
			break;
		}

		ObjData[Object].Ropaje = vb6::val(Leer->GetValue(objidxstr, "NumRopaje"));
		ObjData[Object].HechizoIndex = vb6::val(Leer->GetValue(objidxstr, "HechizoIndex"));

		ObjData[Object].LingoteIndex = vb6::val(Leer->GetValue(objidxstr, "LingoteIndex"));

		ObjData[Object].MineralIndex = vb6::val(Leer->GetValue(objidxstr, "MineralIndex"));

		ObjData[Object].MaxHp = vb6::val(Leer->GetValue(objidxstr, "MaxHP"));
		ObjData[Object].MinHp = vb6::val(Leer->GetValue(objidxstr, "MinHP"));

		ObjData[Object].Mujer = vb6::val(Leer->GetValue(objidxstr, "Mujer"));
		ObjData[Object].Hombre = vb6::val(Leer->GetValue(objidxstr, "Hombre"));

		ObjData[Object].MinHam = vb6::val(Leer->GetValue(objidxstr, "MinHam"));
		ObjData[Object].MinSed = vb6::val(Leer->GetValue(objidxstr, "MinAgu"));

		ObjData[Object].MinDef = vb6::val(Leer->GetValue(objidxstr, "MINDEF"));
		ObjData[Object].MaxDef = vb6::val(Leer->GetValue(objidxstr, "MAXDEF"));
		ObjData[Object].def = (ObjData[Object].MinDef + ObjData[Object].MaxDef) / 2;

		ObjData[Object].RazaEnana = vb6::val(Leer->GetValue(objidxstr, "RazaEnana"));
		ObjData[Object].RazaDrow = vb6::val(Leer->GetValue(objidxstr, "RazaDrow"));
		ObjData[Object].RazaElfa = vb6::val(Leer->GetValue(objidxstr, "RazaElfa"));
		ObjData[Object].RazaGnoma = vb6::val(Leer->GetValue(objidxstr, "RazaGnoma"));
		ObjData[Object].RazaHumana = vb6::val(Leer->GetValue(objidxstr, "RazaHumana"));

		ObjData[Object].Valor = vb6::val(Leer->GetValue(objidxstr, "Valor"));

		ObjData[Object].Crucial = vb6::val(Leer->GetValue(objidxstr, "Crucial"));

		ObjData[Object].Cerrada = vb6::val(Leer->GetValue(objidxstr, "abierta"));
		if (ObjData[Object].Cerrada == 1) {
			ObjData[Object].Llave = vb6::val(Leer->GetValue(objidxstr, "Llave"));
			ObjData[Object].clave = vb6::val(Leer->GetValue(objidxstr, "Clave"));
		}

		/* 'Puertas y llaves */
		ObjData[Object].clave = vb6::val(Leer->GetValue(objidxstr, "Clave"));

		ObjData[Object].texto = Leer->GetValue(objidxstr, "Texto");
		ObjData[Object].GrhSecundario = vb6::val(Leer->GetValue(objidxstr, "VGrande"));

		ObjData[Object].Agarrable = vb6::val(Leer->GetValue(objidxstr, "Agarrable"));
		ObjData[Object].ForoID = Leer->GetValue(objidxstr, "ID");

		ObjData[Object].Acuchilla = vb6::val(Leer->GetValue(objidxstr, "Acuchilla"));

		ObjData[Object].Guante = vb6::val(Leer->GetValue(objidxstr, "Guante"));

		ObjData[Object].ClaseProhibida.redim(1, NUMCLASES);

		/* 'CHECK: !!! Esto es provisorio hasta que los de Dateo cambien los valores de string a numerico */
		int i;
		int N;
		std::string S;
		for (i = (1); i <= (NUMCLASES); i++) {
			S = vb6::UCase(Leer->GetValue(objidxstr, "CP" + vb6::CStr(i)));
			N = 1;
			while (vb6::LenB(S) > 0 && vb6::UCase(ListaClases[N]) != S) {
				N = N + 1;
			}
			ObjData[Object].ClaseProhibida[i] = static_cast<eClass>(vb6::IIf(vb6::LenB(S) > 0, N, 0));
		}

		ObjData[Object].DefensaMagicaMax = vb6::val(Leer->GetValue(objidxstr, "DefensaMagicaMax"));
		ObjData[Object].DefensaMagicaMin = vb6::val(Leer->GetValue(objidxstr, "DefensaMagicaMin"));

		ObjData[Object].SkCarpinteria = vb6::val(Leer->GetValue(objidxstr, "SkCarpinteria"));

		if (ObjData[Object].SkCarpinteria > 0) {
			ObjData[Object].Madera = vb6::val(Leer->GetValue(objidxstr, "Madera"));
		}
		ObjData[Object].MaderaElfica = vb6::val(Leer->GetValue(objidxstr, "MaderaElfica"));

		/* 'Bebidas */
		ObjData[Object].MinSta = vb6::val(Leer->GetValue(objidxstr, "MinST"));

		ObjData[Object].NoSeCae = vb6::val(Leer->GetValue(objidxstr, "NoSeCae"));
		ObjData[Object].NoSeTira = vb6::val(Leer->GetValue(objidxstr, "NoSeTira"));
		ObjData[Object].NoRobable = vb6::val(Leer->GetValue(objidxstr, "NoRobable"));
		ObjData[Object].NoComerciable = vb6::val(Leer->GetValue(objidxstr, "NoComerciable"));
		ObjData[Object].Intransferible = vb6::val(Leer->GetValue(objidxstr, "Intransferible"));

		ObjData[Object].ImpideParalizar = vb6::CByte(vb6::val(Leer->GetValue(objidxstr, "ImpideParalizar")));
		ObjData[Object].ImpideInmobilizar = vb6::CByte(
				vb6::val(Leer->GetValue(objidxstr, "ImpideInmobilizar")));
		ObjData[Object].ImpideAturdir = vb6::CByte(vb6::val(Leer->GetValue(objidxstr, "ImpideAturdir")));
		ObjData[Object].ImpideCegar = vb6::CByte(vb6::val(Leer->GetValue(objidxstr, "ImpideCegar")));

		ObjData[Object].Upgrade = vb6::val(Leer->GetValue(objidxstr, "Upgrade"));
	}

	Leer.reset();

	/* Para evitar problemas con la EÑE en los dats */
	/* El servidor espera que los DAT NO TENGAN EÑE */

	if (!ObjData[460].Apunala) {
		throw std::runtime_error("La daga newbie no apuniala, VERIFICAR QUE EL OBJ.DAT *NO* TENGA ENIES");
	}

	bool algunoApunala = false;

	for (Object = 1; Object <= NumObjDatas && !algunoApunala; ++Object) {
		if (ObjData[Object].Apunala) {
			algunoApunala = true;
		}
	}

	if (!algunoApunala) {
		throw std::runtime_error("Ningun objeto en OBJ.DAT apuniala, VERIFICAR QUE EL OBJ.DAT *NO* TENGA ENIES");
	}

	/* ' Inicializo los foros faccionarios */
	AddForum(FORO_CAOS_ID);
	AddForum(FORO_REAL_ID);

	return;
}

void LoadUserStats(int UserIndex, std::shared_ptr<clsIniManager> & UserFile) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 11/19/2009 */
	/* '11/19/2009: Pato - Load the EluSkills and ExpSkills */
	/* '************************************************* */
	int LoopC;

	for (LoopC = (1); LoopC <= (NUMATRIBUTOS); LoopC++) {
		UserList[UserIndex].Stats.UserAtributos[LoopC] = vb6::CInt(
				UserFile->GetValue("ATRIBUTOS", "AT" + vb6::CStr(LoopC)));
		UserList[UserIndex].Stats.UserAtributosBackUP[LoopC] = UserList[UserIndex].Stats.UserAtributos[LoopC];
	}

	for (LoopC = (1); LoopC <= (NUMSKILLS); LoopC++) {
		UserList[UserIndex].Stats.UserSkills[LoopC] = vb6::val(UserFile->GetValue("SKILLS", "SK" + vb6::CStr(LoopC)));
		UserList[UserIndex].Stats.EluSkills[LoopC] = vb6::val(UserFile->GetValue("SKILLS", "ELUSK" + vb6::CStr(LoopC)));
		UserList[UserIndex].Stats.ExpSkills[LoopC] = vb6::val(UserFile->GetValue("SKILLS", "EXPSK" + vb6::CStr(LoopC)));
	}

	for (LoopC = (1); LoopC <= (MAXUSERHECHIZOS); LoopC++) {
		UserList[UserIndex].Stats.UserHechizos[LoopC] = vb6::val(UserFile->GetValue("Hechizos", "H" + vb6::CStr(LoopC)));
	}

	UserList[UserIndex].Stats.GLD = vb6::CLng(UserFile->GetValue("STATS", "GLD"));
	UserList[UserIndex].Stats.Banco = vb6::CLng(UserFile->GetValue("STATS", "BANCO"));

	UserList[UserIndex].Stats.MaxHp = vb6::CInt(UserFile->GetValue("STATS", "MaxHP"));
	UserList[UserIndex].Stats.MinHp = vb6::CInt(UserFile->GetValue("STATS", "MinHP"));

	UserList[UserIndex].Stats.MinSta = vb6::CInt(UserFile->GetValue("STATS", "MinSTA"));
	UserList[UserIndex].Stats.MaxSta = vb6::CInt(UserFile->GetValue("STATS", "MaxSTA"));

	UserList[UserIndex].Stats.MaxMAN = vb6::CInt(UserFile->GetValue("STATS", "MaxMAN"));
	UserList[UserIndex].Stats.MinMAN = vb6::CInt(UserFile->GetValue("STATS", "MinMAN"));

	UserList[UserIndex].Stats.MaxHIT = vb6::CInt(UserFile->GetValue("STATS", "MaxHIT"));
	UserList[UserIndex].Stats.MinHIT = vb6::CInt(UserFile->GetValue("STATS", "MinHIT"));

	UserList[UserIndex].Stats.MaxAGU = vb6::CByte(UserFile->GetValue("STATS", "MaxAGU"));
	UserList[UserIndex].Stats.MinAGU = vb6::CByte(UserFile->GetValue("STATS", "MinAGU"));

	UserList[UserIndex].Stats.MaxHam = vb6::CByte(UserFile->GetValue("STATS", "MaxHAM"));
	UserList[UserIndex].Stats.MinHam = vb6::CByte(UserFile->GetValue("STATS", "MinHAM"));

	UserList[UserIndex].Stats.SkillPts = vb6::CInt(UserFile->GetValue("STATS", "SkillPtsLibres"));

	UserList[UserIndex].Stats.Exp = vb6::CDbl(UserFile->GetValue("STATS", "EXP"));
	UserList[UserIndex].Stats.ELU = vb6::CLng(UserFile->GetValue("STATS", "ELU"));
	UserList[UserIndex].Stats.ELV = vb6::CByte(UserFile->GetValue("STATS", "ELV"));

	UserList[UserIndex].Stats.UsuariosMatados = vb6::CLng(UserFile->GetValue("MUERTES", "UserMuertes"));
	UserList[UserIndex].Stats.NPCsMuertos = vb6::CInt(UserFile->GetValue("MUERTES", "NpcsMuertes"));

	if (vb6::CByte(UserFile->GetValue("CONSEJO", "PERTENECE"))) {
		UserAsignarPrivilegios(UserIndex, PlayerType_RoyalCouncil);
	}

	if (vb6::CByte(UserFile->GetValue("CONSEJO", "PERTENECECAOS"))) {
		UserAsignarPrivilegios(UserIndex, PlayerType_ChaosCouncil);
	}
}

void LoadUserReputacion(int UserIndex, std::shared_ptr<clsIniManager> & UserFile) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	UserList[UserIndex].Reputacion.AsesinoRep = vb6::val(UserFile->GetValue("REP", "Asesino"));
	UserList[UserIndex].Reputacion.BandidoRep = vb6::val(UserFile->GetValue("REP", "Bandido"));
	UserList[UserIndex].Reputacion.BurguesRep = vb6::val(UserFile->GetValue("REP", "Burguesia"));
	UserList[UserIndex].Reputacion.LadronesRep = vb6::val(UserFile->GetValue("REP", "Ladrones"));
	UserList[UserIndex].Reputacion.NobleRep = vb6::val(UserFile->GetValue("REP", "Nobles"));
	UserList[UserIndex].Reputacion.PlebeRep = vb6::val(UserFile->GetValue("REP", "Plebe"));
	UserList[UserIndex].Reputacion.Promedio = vb6::val(UserFile->GetValue("REP", "Promedio"));

}

void LoadUserInit(int UserIndex, std::shared_ptr<clsIniManager> & UserFile) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 19/11/2006 */
	/* 'Loads the Users RECORDs */
	/* '23/01/2007 Pablo (ToxicWaste) - Agrego NivelIngreso, FechaIngreso, MatadosIngreso y NextRecompensa. */
	/* '23/01/2007 Pablo (ToxicWaste) - Quito CriminalesMatados de Stats porque era redundante. */
	/* '************************************************* */
	int LoopC;
	std::string ln;

	UserList[UserIndex].Faccion.ArmadaReal = vb6::CByte(UserFile->GetValue("FACCIONES", "EjercitoReal"));
	UserList[UserIndex].Faccion.FuerzasCaos = vb6::CByte(UserFile->GetValue("FACCIONES", "EjercitoCaos"));
	UserList[UserIndex].Faccion.CiudadanosMatados = vb6::CLng(UserFile->GetValue("FACCIONES", "CiudMatados"));
	UserList[UserIndex].Faccion.CriminalesMatados = vb6::CLng(UserFile->GetValue("FACCIONES", "CrimMatados"));
	UserList[UserIndex].Faccion.RecibioArmaduraCaos = vb6::CByte(UserFile->GetValue("FACCIONES", "rArCaos"));
	UserList[UserIndex].Faccion.RecibioArmaduraReal = vb6::CByte(UserFile->GetValue("FACCIONES", "rArReal"));
	UserList[UserIndex].Faccion.RecibioExpInicialCaos = vb6::CByte(
			UserFile->GetValue("FACCIONES", "rExCaos"));
	UserList[UserIndex].Faccion.RecibioExpInicialReal = vb6::CByte(
			UserFile->GetValue("FACCIONES", "rExReal"));
	UserList[UserIndex].Faccion.RecompensasCaos = vb6::CLng(UserFile->GetValue("FACCIONES", "recCaos"));
	UserList[UserIndex].Faccion.RecompensasReal = vb6::CLng(UserFile->GetValue("FACCIONES", "recReal"));
	UserList[UserIndex].Faccion.Reenlistadas = vb6::CByte(UserFile->GetValue("FACCIONES", "Reenlistadas"));
	UserList[UserIndex].Faccion.NivelIngreso = vb6::CInt(UserFile->GetValue("FACCIONES", "NivelIngreso"));
	UserList[UserIndex].Faccion.FechaIngreso = UserFile->GetValue("FACCIONES", "FechaIngreso");
	UserList[UserIndex].Faccion.MatadosIngreso = vb6::CInt(UserFile->GetValue("FACCIONES", "MatadosIngreso"));
	UserList[UserIndex].Faccion.NextRecompensa = vb6::CInt(UserFile->GetValue("FACCIONES", "NextRecompensa"));

	UserList[UserIndex].flags.Muerto = vb6::CByte(UserFile->GetValue("FLAGS", "Muerto"));
	UserList[UserIndex].flags.Escondido = vb6::CByte(UserFile->GetValue("FLAGS", "Escondido"));

	UserList[UserIndex].flags.Hambre = vb6::CByte(UserFile->GetValue("FLAGS", "Hambre"));
	UserList[UserIndex].flags.Sed = vb6::CByte(UserFile->GetValue("FLAGS", "Sed"));
	UserList[UserIndex].flags.Desnudo = vb6::CByte(UserFile->GetValue("FLAGS", "Desnudo"));
	UserList[UserIndex].flags.Navegando = vb6::CByte(UserFile->GetValue("FLAGS", "Navegando"));
	UserList[UserIndex].flags.Envenenado = vb6::CByte(UserFile->GetValue("FLAGS", "Envenenado"));
	UserList[UserIndex].flags.Paralizado = vb6::CByte(UserFile->GetValue("FLAGS", "Paralizado"));

	/* 'Matrix */
	UserList[UserIndex].flags.lastMap = vb6::val(UserFile->GetValue("FLAGS", "LastMap"));

	if (UserList[UserIndex].flags.Paralizado == 1) {
		UserList[UserIndex].Counters.Paralisis = IntervaloParalizado;
	}

	UserList[UserIndex].Counters.Pena = vb6::CLng(UserFile->GetValue("COUNTERS", "Pena"));
	UserList[UserIndex].Counters.AsignedSkills = vb6::CByte(
			vb6::val(UserFile->GetValue("COUNTERS", "SkillsAsignados")));

	UserList[UserIndex].email = UserFile->GetValue("CONTACTO", "Email");

	UserList[UserIndex].Genero = static_cast<eGenero>(vb6::CInt(UserFile->GetValue("INIT", "Genero")));
	UserList[UserIndex].clase = static_cast<eClass>(vb6::CInt(UserFile->GetValue("INIT", "Clase")));
	UserList[UserIndex].raza = static_cast<eRaza>(vb6::CInt(UserFile->GetValue("INIT", "Raza")));
	UserList[UserIndex].Hogar = static_cast<eCiudad>(vb6::CInt(UserFile->GetValue("INIT", "Hogar")));
	UserList[UserIndex].Char.heading =
			static_cast<eHeading>(vb6::CInt(UserFile->GetValue("INIT", "Heading")));

	UserList[UserIndex].OrigChar.Head = vb6::CInt(UserFile->GetValue("INIT", "Head"));
	UserList[UserIndex].OrigChar.body = vb6::CInt(UserFile->GetValue("INIT", "Body"));
	UserList[UserIndex].OrigChar.WeaponAnim = vb6::CInt(UserFile->GetValue("INIT", "Arma"));
	UserList[UserIndex].OrigChar.ShieldAnim = vb6::CInt(UserFile->GetValue("INIT", "Escudo"));
	UserList[UserIndex].OrigChar.CascoAnim = vb6::CInt(UserFile->GetValue("INIT", "Casco"));

	UserList[UserIndex].OrigChar.heading = eHeading_SOUTH;

	/* # IF ConUpTime THEN */
	UserList[UserIndex].UpTime = vb6::CLng(UserFile->GetValue("INIT", "UpTime"));
	/* # END IF */

	if (UserList[UserIndex].flags.Muerto == 0) {
		UserList[UserIndex].Char = UserList[UserIndex].OrigChar;
	} else {
		UserList[UserIndex].Char.body = iCuerpoMuerto;
		UserList[UserIndex].Char.Head = iCabezaMuerto;
		UserList[UserIndex].Char.WeaponAnim = NingunArma;
		UserList[UserIndex].Char.ShieldAnim = NingunEscudo;
		UserList[UserIndex].Char.CascoAnim = NingunCasco;
	}

	UserList[UserIndex].desc = UserFile->GetValue("INIT", "Desc");

	UserList[UserIndex].Pos.Map = vb6::CInt(ReadField(1, UserFile->GetValue("INIT", "Position"), 45));
	UserList[UserIndex].Pos.X = vb6::CInt(ReadField(2, UserFile->GetValue("INIT", "Position"), 45));
	UserList[UserIndex].Pos.Y = vb6::CInt(ReadField(3, UserFile->GetValue("INIT", "Position"), 45));

	UserList[UserIndex].Invent.NroItems = vb6::CInt(UserFile->GetValue("Inventory", "CantidadItems"));

	/* '[KEVIN]-------------------------------------------------------------------- */
	/* '*********************************************************************************** */
	UserList[UserIndex].BancoInvent.NroItems = vb6::CInt(
			UserFile->GetValue("BancoInventory", "CantidadItems"));
	/* 'Lista de objetos del banco */
	for (LoopC = (1); LoopC <= (MAX_BANCOINVENTORY_SLOTS); LoopC++) {
		ln = UserFile->GetValue("BancoInventory", "Obj" + vb6::CStr(LoopC));
		UserList[UserIndex].BancoInvent.Object[LoopC].ObjIndex = vb6::CInt(ReadField(1, ln, 45));
		UserList[UserIndex].BancoInvent.Object[LoopC].Amount = vb6::CInt(ReadField(2, ln, 45));
	}
	/* '------------------------------------------------------------------------------------ */
	/* '[/KEVIN]***************************************************************************** */

	/* 'Lista de objetos */
	for (LoopC = (1); LoopC <= (MAX_INVENTORY_SLOTS); LoopC++) {
		ln = UserFile->GetValue("Inventory", "Obj" + vb6::CStr(LoopC));
		UserList[UserIndex].Invent.Object[LoopC].ObjIndex = vb6::val(ReadField(1, ln, 45));
		UserList[UserIndex].Invent.Object[LoopC].Amount = vb6::val(ReadField(2, ln, 45));
		UserList[UserIndex].Invent.Object[LoopC].Equipped = vb6::val(ReadField(3, ln, 45));
	}

	/* 'Obtiene el indice-objeto del arma */
	UserList[UserIndex].Invent.WeaponEqpSlot = vb6::CByte(UserFile->GetValue("Inventory", "WeaponEqpSlot"));
	if (UserList[UserIndex].Invent.WeaponEqpSlot > 0) {
		UserList[UserIndex].Invent.WeaponEqpObjIndex =
				UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.WeaponEqpSlot].ObjIndex;
	}

	/* 'Obtiene el indice-objeto del armadura */
	UserList[UserIndex].Invent.ArmourEqpSlot = vb6::CByte(UserFile->GetValue("Inventory", "ArmourEqpSlot"));
	if (UserList[UserIndex].Invent.ArmourEqpSlot > 0) {
		UserList[UserIndex].Invent.ArmourEqpObjIndex =
				UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.ArmourEqpSlot].ObjIndex;
		UserList[UserIndex].flags.Desnudo = 0;
	} else {
		UserList[UserIndex].flags.Desnudo = 1;
	}

	/* 'Obtiene el indice-objeto del escudo */
	UserList[UserIndex].Invent.EscudoEqpSlot = vb6::CByte(UserFile->GetValue("Inventory", "EscudoEqpSlot"));
	if (UserList[UserIndex].Invent.EscudoEqpSlot > 0) {
		UserList[UserIndex].Invent.EscudoEqpObjIndex =
				UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.EscudoEqpSlot].ObjIndex;
	}

	/* 'Obtiene el indice-objeto del casco */
	UserList[UserIndex].Invent.CascoEqpSlot = vb6::CByte(UserFile->GetValue("Inventory", "CascoEqpSlot"));
	if (UserList[UserIndex].Invent.CascoEqpSlot > 0) {
		UserList[UserIndex].Invent.CascoEqpObjIndex =
				UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.CascoEqpSlot].ObjIndex;
	}

	/* 'Obtiene el indice-objeto barco */
	UserList[UserIndex].Invent.BarcoSlot = vb6::CByte(UserFile->GetValue("Inventory", "BarcoSlot"));
	if (UserList[UserIndex].Invent.BarcoSlot > 0) {
		UserList[UserIndex].Invent.BarcoObjIndex =
				UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.BarcoSlot].ObjIndex;
	}

	/* 'Obtiene el indice-objeto municion */
	UserList[UserIndex].Invent.MunicionEqpSlot = vb6::CByte(UserFile->GetValue("Inventory", "MunicionSlot"));
	if (UserList[UserIndex].Invent.MunicionEqpSlot > 0) {
		UserList[UserIndex].Invent.MunicionEqpObjIndex =
				UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.MunicionEqpSlot].ObjIndex;
	}

	/* '[Alejo] */
	/* 'Obtiene el indice-objeto anilo */
	UserList[UserIndex].Invent.AnilloEqpSlot = vb6::CByte(UserFile->GetValue("Inventory", "AnilloSlot"));
	if (UserList[UserIndex].Invent.AnilloEqpSlot > 0) {
		UserList[UserIndex].Invent.AnilloEqpObjIndex =
				UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.AnilloEqpSlot].ObjIndex;
	}

	UserList[UserIndex].Invent.MochilaEqpSlot = vb6::val(UserFile->GetValue("Inventory", "MochilaSlot"));
	if (UserList[UserIndex].Invent.MochilaEqpSlot > 0) {
		UserList[UserIndex].Invent.MochilaEqpObjIndex =
				UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.MochilaEqpSlot].ObjIndex;
	}

	UserList[UserIndex].NroMascotas = vb6::CInt(UserFile->GetValue("MASCOTAS", "NroMascotas"));
	for (LoopC = (1); LoopC <= (MAXMASCOTAS); LoopC++) {
		UserList[UserIndex].MascotasType[LoopC] = vb6::val(UserFile->GetValue("MASCOTAS", "MAS" + vb6::CStr(LoopC)));
	}

	ln = UserFile->GetValue("Guild", "GUILDINDEX");
	if (vb6::IsNumeric(ln)) {
		UserList[UserIndex].GuildIndex = vb6::CInt(ln);
	} else {
		UserList[UserIndex].GuildIndex = 0;
	}

}

std::string GetVar(std::string File, std::string Main, std::string Var, int EmptySpaces) {
	(void)EmptySpaces;

	clsIniManager iniReader;
	iniReader.Initialize(File);

	return iniReader.GetValue(Main, Var);
}

void CargarBackUp() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	std::cout << "Cargando backup." << std::endl;

	int Map;
	std::string tFileName;

	NumMaps = vb6::val(GetVar(GetDatPath(DATPATH::Map), "INIT", "NumMaps"));
	NumMaps = vb6::Constrain(NumMaps, 0, MAX_MAPS);

	InitAreas();

	//MapPath = GetVar(GetDatPath(DATPATH::Map), "INIT", "MapPath");

	MapData.redim(1, NumMaps);
	/* FIXME: REDIM MULTIDIMENSIONAL: REDIM MapData ( 1 TO NumMaps , XMinMapSize TO XMaxMapSize , YMinMapSize TO YMaxMapSize ) AS MapBlock */
	for (int m = 1; m <= NumMaps; ++m) {
		MapData[m].redim(XMinMapSize, XMaxMapSize);
		for (int x = XMinMapSize; x <= XMaxMapSize; ++x) {
			MapData[m][x].redim(YMinMapSize, YMaxMapSize);
		}
	}

//	MapData.redim(0);
//	/* FIXME: REDIM MULTIDIMENSIONAL: REDIM MapData ( 1 TO NumMaps , XMinMapSize TO XMaxMapSize , YMinMapSize TO YMaxMapSize ) AS MapBlock */
//	for (auto& m : MapData) {
//		m.redim(XMinMapSize, XMaxMapSize);
//		for (auto& q : m) {
//			q.redim(YMinMapSize, YMaxMapSize);
//		}
//	}

	MapInfo.redim(0);
	MapInfo.redim(1, NumMaps);

	for (Map = (1); Map <= (NumMaps); Map++) {
		bool loadFromBackup;
		if (vb6::val(
				GetVar(GetMapPath(Map, MAPPATH::DAT), "Mapa" + vb6::CStr(Map),
						"BackUp")) != 0) {
			tFileName = GetMapPath(Map, MAPPATH::INF, true);
			loadFromBackup = true;
			/* 'Miramos que exista al menos uno de los 3 archivos, sino lo cargamos de la carpeta de los mapas */
			if (!FileExist(tFileName)) {
				loadFromBackup = false;
			}
		} else {
			loadFromBackup = false;
		}

		CargarMapa(Map, loadFromBackup);
	}

	return;
}

void LoadMapData() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	std::cout << "Cargando mapas..." << std::endl;

	LogMain("Cargando mapas...");

	int Map;

	NumMaps = vb6::val(GetVar(GetDatPath(DATPATH::Map), "INIT", "NumMaps"));
	NumMaps = vb6::Constrain(NumMaps, 0, MAX_MAPS);

	InitAreas();

	//MapPath = GetVar(GetDatPath(DATPATH::Map), "INIT", "MapPath");

	MapData.redim(1, NumMaps);
	/* FIXME: REDIM MULTIDIMENSIONAL: REDIM MapData ( 1 TO NumMaps , XMinMapSize TO XMaxMapSize , YMinMapSize TO YMaxMapSize ) AS MapBlock */
	for (int m = 1; m <= NumMaps; ++m) {
		MapData[m].redim(XMinMapSize, XMaxMapSize);
		for (int x = XMinMapSize; x <= XMaxMapSize; ++x) {
			MapData[m][x].redim(YMinMapSize, YMaxMapSize);
		}
	}

//	for (auto& m : MapData) {
//		m.redim(XMinMapSize, XMaxMapSize);
//		for (auto& q : m) {
//			q.redim(YMinMapSize, YMaxMapSize);
//		}
//	}

	MapInfo.redim(0);
	MapInfo.redim(1, NumMaps);

	for (Map = (1); Map <= (NumMaps); Map++) {
		CargarMapa(Map, false);
	}

	return;
}

void CargarMapa(int Map, bool loadFromBackup) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 10/08/2010 */
	/* '10/08/2010 - Pato: Implemento el clsByteBuffer y el clsIniManager para la carga de mapa */
	/* '*************************************************** */

	int X;
	int Y;
	int ByFlags;
	std::shared_ptr<clsIniManager> Leer;
	std::shared_ptr<clsByteBuffer> MapReader;
	std::shared_ptr<clsByteBuffer> InfReader;
	std::vector<std::int8_t> Buff;

	MapReader.reset(new clsByteBuffer());
	InfReader.reset(new clsByteBuffer());
	Leer.reset(new clsIniManager());

	//std::string npcfile = GetDatPath(DATPATH::NPCs);

	{
		std::ifstream mapfile;
		mapfile.open(GetMapPath(Map, MAPPATH::MAP, loadFromBackup), std::ios::in | std::ios::binary | std::ios::ate);
		Buff.resize(0);
		Buff.resize(mapfile.tellg());
		mapfile.seekg(0, std::ios::beg);
		mapfile.read(reinterpret_cast<char*>(Buff.data()), Buff.size());
		mapfile.close();
	}

	MapReader->initializeReader(Buff);

	{
		std::ifstream inffile;
		inffile.open(GetMapPath(Map, MAPPATH::INF, loadFromBackup), std::ios::in | std::ios::binary | std::ios::ate);
		Buff.resize(0);
		Buff.resize(inffile.tellg());
		inffile.seekg(0, std::ios::beg);
		inffile.read(reinterpret_cast<char*>(Buff.data()), Buff.size());
		inffile.close();
	}

	InfReader->initializeReader(Buff);

	/* 'map Header */
	MapInfo[Map].MapVersion = MapReader->getInteger();

	MiCabecera.desc = MapReader->getString(255);
	MiCabecera.crc = MapReader->getLong();
	MiCabecera.MagicWord = MapReader->getLong();

	MapReader->getDouble();

	/* 'inf Header */
	InfReader->getDouble();
	InfReader->getInteger();


	for (Y = (YMinMapSize); Y <= (YMaxMapSize); Y++) {
		for (X = (XMinMapSize); X <= (XMaxMapSize); X++) {
			/* '.map file */
			ByFlags = MapReader->getByte();

			if (ByFlags & 1) {
				MapData[Map][X][Y].Blocked = 1;
			}

			MapData[Map][X][Y].Graphic[1] = MapReader->getInteger();

			/* 'Layer 2 used? */
			if (ByFlags & 2) {
				MapData[Map][X][Y].Graphic[2] = MapReader->getInteger();
			}

			/* 'Layer 3 used? */
			if (ByFlags & 4) {
				MapData[Map][X][Y].Graphic[3] = MapReader->getInteger();
			}

			/* 'Layer 4 used? */
			if (ByFlags & 8) {
				MapData[Map][X][Y].Graphic[4] = MapReader->getInteger();
			}

			/* 'Trigger used? */
			if (ByFlags & 16) {
				MapData[Map][X][Y].trigger = static_cast<eTrigger>(MapReader->getInteger());
			}

			/* '.inf file */
			ByFlags = InfReader->getByte();

			if (ByFlags & 1) {
				MapData[Map][X][Y].TileExit.Map = InfReader->getInteger();
				MapData[Map][X][Y].TileExit.X = InfReader->getInteger();
				MapData[Map][X][Y].TileExit.Y = InfReader->getInteger();
			}

			if (ByFlags & 2) {
				/* 'Get and make NPC */
				MapData[Map][X][Y].NpcIndex = InfReader->getInteger();

				if (MapData[Map][X][Y].NpcIndex > 0) {
					/* 'Si el npc debe hacer respawn en la pos */
					/* 'original la guardamos */
					if (vb6::val(LeerNPCs->GetValue("NPC" + vb6::CStr(MapData[Map][X][Y].NpcIndex), "PosOrig")) == 1) {
						MapData[Map][X][Y].NpcIndex = OpenNPC(MapData[Map][X][Y].NpcIndex);
						Npclist[MapData[Map][X][Y].NpcIndex].Orig.Map = Map;
						Npclist[MapData[Map][X][Y].NpcIndex].Orig.X = X;
						Npclist[MapData[Map][X][Y].NpcIndex].Orig.Y = Y;
					} else {
						MapData[Map][X][Y].NpcIndex = OpenNPC(MapData[Map][X][Y].NpcIndex);
					}

					Npclist[MapData[Map][X][Y].NpcIndex].Pos.Map = Map;
					Npclist[MapData[Map][X][Y].NpcIndex].Pos.X = X;
					Npclist[MapData[Map][X][Y].NpcIndex].Pos.Y = Y;

					MakeNPCChar(true, 0, MapData[Map][X][Y].NpcIndex, Map, X, Y);
				}
			}

			if (ByFlags & 4) {
				/* 'Get and make Object */
				MapData[Map][X][Y].ObjInfo.ObjIndex = InfReader->getInteger();
				MapData[Map][X][Y].ObjInfo.Amount = InfReader->getInteger();
			}
		}
	}

	Leer->Initialize(GetMapPath(Map, MAPPATH::DAT, loadFromBackup));

	MapInfo[Map].Name = Leer->GetValue("Mapa" + vb6::CStr(Map), "Name");
	MapInfo[Map].Music = vb6::CInt(Leer->GetValue("Mapa" + vb6::CStr(Map), "MusicNum"));
	MapInfo[Map].StartPos.Map = vb6::val(
			ReadField(1, Leer->GetValue("Mapa" + vb6::CStr(Map), "StartPos"), vb6::Asc("-")));
	MapInfo[Map].StartPos.X = vb6::val(ReadField(2, Leer->GetValue("Mapa" + vb6::CStr(Map), "StartPos"), vb6::Asc("-")));
	MapInfo[Map].StartPos.Y = vb6::val(ReadField(3, Leer->GetValue("Mapa" + vb6::CStr(Map), "StartPos"), vb6::Asc("-")));

	MapInfo[Map].OnDeathGoTo.Map = vb6::val(
			ReadField(1, Leer->GetValue("Mapa" + vb6::CStr(Map), "OnDeathGoTo"), vb6::Asc("-")));
	MapInfo[Map].OnDeathGoTo.X = vb6::val(
			ReadField(2, Leer->GetValue("Mapa" + vb6::CStr(Map), "OnDeathGoTo"), vb6::Asc("-")));
	MapInfo[Map].OnDeathGoTo.Y = vb6::val(
			ReadField(3, Leer->GetValue("Mapa" + vb6::CStr(Map), "OnDeathGoTo"), vb6::Asc("-")));

	MapInfo[Map].MagiaSinEfecto = vb6::val(Leer->GetValue("Mapa" + vb6::CStr(Map), "MagiaSinEfecto"));
	MapInfo[Map].InviSinEfecto = vb6::val(Leer->GetValue("Mapa" + vb6::CStr(Map), "InviSinEfecto"));
	MapInfo[Map].ResuSinEfecto = vb6::val(Leer->GetValue("Mapa" + vb6::CStr(Map), "ResuSinEfecto"));
	MapInfo[Map].OcultarSinEfecto = vb6::val(Leer->GetValue("Mapa" + vb6::CStr(Map), "OcultarSinEfecto"));
	MapInfo[Map].InvocarSinEfecto = vb6::val(Leer->GetValue("Mapa" + vb6::CStr(Map), "InvocarSinEfecto"));

	MapInfo[Map].NoEncriptarMP = vb6::val(Leer->GetValue("Mapa" + vb6::CStr(Map), "NoEncriptarMP"));

	MapInfo[Map].RoboNpcsPermitido = vb6::val(Leer->GetValue("Mapa" + vb6::CStr(Map), "RoboNpcsPermitido"));

	if (vb6::val(Leer->GetValue("Mapa" + vb6::CStr(Map), "Pk")) == 0) {
		MapInfo[Map].Pk = true;
	} else {
		MapInfo[Map].Pk = false;
	}

	MapInfo[Map].Terreno = TerrainStringToByte(Leer->GetValue("Mapa" + vb6::CStr(Map), "Terreno"));
	MapInfo[Map].Zona = Leer->GetValue("Mapa" + vb6::CStr(Map), "Zona");
	MapInfo[Map].Restringir = RestrictStringToByte(Leer->GetValue("Mapa" + vb6::CStr(Map), "Restringir"));
	MapInfo[Map].BackUp = vb6::val(Leer->GetValue("Mapa" + vb6::CStr(Map), "BACKUP"));

	MapReader.reset();
	InfReader.reset();
	Leer.reset();

	return;
}

void LoadSini() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int Temporal;
	clsIniManager leerSini;
	leerSini.Initialize(GetIniPath("server.ini"));

	std::cout << "Cargando info de inicio del server." << std::endl;

	BootDelBackUp = vb6::val(leerSini.GetValue("INIT", "IniciarDesdeBackUp"));


	/* 'TODO:Esto es temporal, hay que volarlo!! */
	//GUILDPATH = GetGuildsPath();
	//GUILDINFOFILE = GUILDPATH + "guildsinfo.inf";

	Puerto = vb6::val(leerSini.GetValue("INIT", "StartPort"));
	HideMe = vb6::val(leerSini.GetValue("INIT", "Hide"));
	AllowMultiLogins = vb6::val(leerSini.GetValue("INIT", "AllowMultiLogins"));
	IdleLimit = vb6::val(leerSini.GetValue("INIT", "IdleLimit"));
	/* 'Lee la version correcta del cliente */
	ULTIMAVERSION = leerSini.GetValue("INIT", "Version");
	LimiteConexionesPorIp = vb6::val(leerSini.GetValue("INIT", "LimiteConexionesPorIp", "10"));

	MAX_PACKETS_PER_ITER = vb6::CInt(leerSini.GetValue("INIT", "MAX_PACKETS_PER_ITER", "5"));
	PuedeCrearPersonajes = vb6::val(leerSini.GetValue("INIT", "PuedeCrearPersonajes"));
	ServerSoloGMs = vb6::val(leerSini.GetValue("init", "ServerSoloGMs"));

	// Lista blanca de emails
	RegistroListaBlancaEmails = vb6::val(leerSini.GetValue("init", "RegistroListaBlancaEmails", "0"));
	if (RegistroListaBlancaEmails) {
		std::ifstream fin;
		std::string cad;
		fin.open(GetDatPath(DATPATH::EmailsHabilitados));
		while (std::getline(fin, cad)) {
			cad = vb6::LCase(vb6::Trim(cad));
			if (cad.size()) {
				RegistroEmailsHabilitados.insert(cad);
			}
		}
	}

	/* ' HappyHour */
	int lDay;
	for (lDay = (1); lDay <= (7); lDay++) {
		HappyHourDays[lDay] = vb6::val(leerSini.GetValue("HappyHour", "Day" + vb6::CStr(lDay)));
		if (HappyHourDays[lDay] <= 0) {
			HappyHourDays[lDay] = 1;
		}
	}

	ArmaduraImperial1 = vb6::val(leerSini.GetValue("INIT", "ArmaduraImperial1"));
	ArmaduraImperial2 = vb6::val(leerSini.GetValue("INIT", "ArmaduraImperial2"));
	ArmaduraImperial3 = vb6::val(leerSini.GetValue("INIT", "ArmaduraImperial3"));
	TunicaMagoImperial = vb6::val(leerSini.GetValue("INIT", "TunicaMagoImperial"));
	TunicaMagoImperialEnanos = vb6::val(leerSini.GetValue("INIT", "TunicaMagoImperialEnanos"));
	ArmaduraCaos1 = vb6::val(leerSini.GetValue("INIT", "ArmaduraCaos1"));
	ArmaduraCaos2 = vb6::val(leerSini.GetValue("INIT", "ArmaduraCaos2"));
	ArmaduraCaos3 = vb6::val(leerSini.GetValue("INIT", "ArmaduraCaos3"));
	TunicaMagoCaos = vb6::val(leerSini.GetValue("INIT", "TunicaMagoCaos"));
	TunicaMagoCaosEnanos = vb6::val(leerSini.GetValue("INIT", "TunicaMagoCaosEnanos"));

	VestimentaImperialHumano = vb6::val(leerSini.GetValue("INIT", "VestimentaImperialHumano"));
	VestimentaImperialEnano = vb6::val(leerSini.GetValue("INIT", "VestimentaImperialEnano"));
	TunicaConspicuaHumano = vb6::val(leerSini.GetValue("INIT", "TunicaConspicuaHumano"));
	TunicaConspicuaEnano = vb6::val(leerSini.GetValue("INIT", "TunicaConspicuaEnano"));
	ArmaduraNobilisimaHumano = vb6::val(leerSini.GetValue("INIT", "ArmaduraNobilisimaHumano"));
	ArmaduraNobilisimaEnano = vb6::val(leerSini.GetValue("INIT", "ArmaduraNobilisimaEnano"));
	ArmaduraGranSacerdote = vb6::val(leerSini.GetValue("INIT", "ArmaduraGranSacerdote"));

	VestimentaLegionHumano = vb6::val(leerSini.GetValue("INIT", "VestimentaLegionHumano"));
	VestimentaLegionEnano = vb6::val(leerSini.GetValue("INIT", "VestimentaLegionEnano"));
	TunicaLobregaHumano = vb6::val(leerSini.GetValue("INIT", "TunicaLobregaHumano"));
	TunicaLobregaEnano = vb6::val(leerSini.GetValue("INIT", "TunicaLobregaEnano"));
	TunicaEgregiaHumano = vb6::val(leerSini.GetValue("INIT", "TunicaEgregiaHumano"));
	TunicaEgregiaEnano = vb6::val(leerSini.GetValue("INIT", "TunicaEgregiaEnano"));
	SacerdoteDemoniaco = vb6::val(leerSini.GetValue("INIT", "SacerdoteDemoniaco"));

	// MAPA_PRETORIANO = vb6::val(leerSini.GetValue("INIT", "MapaPretoriano"));

	EnTesting = vb6::val(leerSini.GetValue("INIT", "Testing"));

	/* 'Intervalos */
	SanaIntervaloSinDescansar = vb6::val(
			leerSini.GetValue("INTERVALOS", "SanaIntervaloSinDescansar"));

	StaminaIntervaloSinDescansar = vb6::val(
			leerSini.GetValue("INTERVALOS", "StaminaIntervaloSinDescansar"));

	SanaIntervaloDescansar = vb6::val(leerSini.GetValue("INTERVALOS", "SanaIntervaloDescansar"));

	StaminaIntervaloDescansar = vb6::val(
			leerSini.GetValue("INTERVALOS", "StaminaIntervaloDescansar"));

	IntervaloSed = vb6::val(leerSini.GetValue("INTERVALOS", "IntervaloSed"));

	IntervaloHambre = vb6::val(leerSini.GetValue("INTERVALOS", "IntervaloHambre"));

	IntervaloVeneno = vb6::val(leerSini.GetValue("INTERVALOS", "IntervaloVeneno"));

	IntervaloParalizado = vb6::val(leerSini.GetValue("INTERVALOS", "IntervaloParalizado"));

	IntervaloInvisible = vb6::val(leerSini.GetValue("INTERVALOS", "IntervaloInvisible"));

	IntervaloFrio = vb6::val(leerSini.GetValue("INTERVALOS", "IntervaloFrio"));

	IntervaloWavFx = vb6::val(leerSini.GetValue("INTERVALOS", "IntervaloWAVFX"));

	IntervaloInvocacion = vb6::val(leerSini.GetValue("INTERVALOS", "IntervaloInvocacion"));

	IntervaloParaConexion = vb6::val(leerSini.GetValue("INTERVALOS", "IntervaloParaConexion"));

	IntervaloImprimirEnConsola = vb6::val(leerSini.GetValue("INTERVALOS", "IntervaloImprimirEnConsola", "15"));

	/* '&&&&&&&&&&&&&&&&&&&&& TIMERS &&&&&&&&&&&&&&&&&&&&&&& */

	/* ' Cargar desde balance.dat */
	IntervaloPuedeSerAtacado = 5000;
	/* ' Cargar desde balance.dat */
	IntervaloAtacable = 60000;
	/* ' Cargar desde balance.dat */
	IntervaloOwnedNpc = 18000;

	IntervaloUserPuedeCastear = vb6::val(
			leerSini.GetValue("INTERVALOS", "IntervaloLanzaHechizo"));

	IntervaloNPCAI = vb6::val(leerSini.GetValue("INTERVALOS", "IntervaloNpcAI"));
	IntervaloNPCPuedeAtacar = vb6::val(leerSini.GetValue("INTERVALOS", "IntervaloNpcPuedeAtacar"));

	IntervaloUserPuedeTrabajar = vb6::val(leerSini.GetValue("INTERVALOS", "IntervaloTrabajo"));

	IntervaloUserPuedeAtacar = vb6::val(
			leerSini.GetValue("INTERVALOS", "IntervaloUserPuedeAtacar"));

	/* 'TODO : Agregar estos intervalos al form!!! */
	IntervaloMagiaGolpe = vb6::val(leerSini.GetValue("INTERVALOS", "IntervaloMagiaGolpe"));
	IntervaloGolpeMagia = vb6::val(leerSini.GetValue("INTERVALOS", "IntervaloGolpeMagia"));
	IntervaloGolpeUsar = vb6::val(leerSini.GetValue("INTERVALOS", "IntervaloGolpeUsar"));

	/* FIXME
	 frmMain.tLluvia.interval = vb6::val(
	 leerSini.GetValue("INTERVALOS", "IntervaloPerdidaStaminaLluvia"));
	 */

	MinutosWs = vb6::val(leerSini.GetValue("INTERVALOS", "IntervaloWS"));
	if (MinutosWs < 60) {
		MinutosWs = 180;
	}

	MinutosMotd = vb6::val(leerSini.GetValue("INTERVALOS", "MinutosMotd"));
	if (MinutosMotd < 20) {
		MinutosMotd = 20;
	}

	MinutosGuardarUsuarios = vb6::val(
			leerSini.GetValue("INTERVALOS", "IntervaloGuardarUsuarios"));

	IntervaloCerrarConexion = vb6::val(
			leerSini.GetValue("INTERVALOS", "IntervaloCerrarConexion"));
	IntervaloUserPuedeUsar = vb6::val(leerSini.GetValue("INTERVALOS", "IntervaloUserPuedeUsar"));
	IntervaloFlechasCazadores = vb6::val(
			leerSini.GetValue("INTERVALOS", "IntervaloFlechasCazadores"));

	IntervaloOculto = vb6::val(leerSini.GetValue("INTERVALOS", "IntervaloOculto"));

	/* '&&&&&&&&&&&&&&&&&&&&& FIN TIMERS &&&&&&&&&&&&&&&&&&&&&&& */

	RECORDusuarios = std::stoi(GetVar(GetDatPath(DATPATH::Stats), "INIT", "RECORD"));

	/* 'Max users */
	Temporal = vb6::val(leerSini.GetValue("INIT", "MaxUsers"));
	if (MaxUsers == 0) {
		MaxUsers = Temporal;
		UserList.redim(0);
		UserList.redim(1, MaxUsers);
	}

	/* '&&&&&&&&&&&&&&&&&&&&& BALANCE &&&&&&&&&&&&&&&&&&&&&&& */
	/* 'Se agregó en LoadBalance y en el Balance.dat */
	/* 'PorcentajeRecuperoMana = val(GetVar(IniPath & "Server.ini", "BALANCE", "PorcentajeRecuperoMana")) */

	/* ''&&&&&&&&&&&&&&&&&&&&& FIN BALANCE &&&&&&&&&&&&&&&&&&&&&&& */
	InitializeStatistics();

	clsIniManager leerCiudad;
	leerCiudad.Initialize(GetDatPath(DATPATH::Ciudades));

	Ullathorpe.Map = vb6::CInt(leerCiudad.GetValue("Ullathorpe", "Mapa"));
	Ullathorpe.X = vb6::CInt(leerCiudad.GetValue("Ullathorpe", "X"));
	Ullathorpe.Y = vb6::CInt(leerCiudad.GetValue("Ullathorpe", "Y"));

	Nix.Map = vb6::CInt(leerCiudad.GetValue("Nix", "Mapa"));
	Nix.X = vb6::CInt(leerCiudad.GetValue("Nix", "X"));
	Nix.Y = vb6::CInt(leerCiudad.GetValue("Nix", "Y"));

	Banderbill.Map = vb6::CInt(leerCiudad.GetValue("Banderbill", "Mapa"));
	Banderbill.X = vb6::CInt(leerCiudad.GetValue("Banderbill", "X"));
	Banderbill.Y = vb6::CInt(leerCiudad.GetValue("Banderbill", "Y"));

	Lindos.Map = vb6::CInt(leerCiudad.GetValue("Lindos", "Mapa"));
	Lindos.X = vb6::CInt(leerCiudad.GetValue("Lindos", "X"));
	Lindos.Y = vb6::CInt(leerCiudad.GetValue("Lindos", "Y"));

	Arghal.Map = vb6::CInt(leerCiudad.GetValue("Arghal", "Mapa"));
	Arghal.X = vb6::CInt(leerCiudad.GetValue("Arghal", "X"));
	Arghal.Y = vb6::CInt(leerCiudad.GetValue("Arghal", "Y"));

	Arkhein.Map = vb6::CInt(leerCiudad.GetValue("Arkhein", "Mapa"));
	Arkhein.X = vb6::CInt(leerCiudad.GetValue("Arkhein", "X"));
	Arkhein.Y = vb6::CInt(leerCiudad.GetValue("Arkhein", "Y"));

	Nemahuak.Map = vb6::CInt(leerCiudad.GetValue("Nemahuak", "Mapa"));
	Nemahuak.X = vb6::CInt(leerCiudad.GetValue("Nemahuak", "X"));
	Nemahuak.Y = vb6::CInt(leerCiudad.GetValue("Nemahuak", "Y"));

	Ciudades[eCiudad_cUllathorpe] = Ullathorpe;
	Ciudades[eCiudad_cNix] = Nix;
	Ciudades[eCiudad_cBanderbill] = Banderbill;
	Ciudades[eCiudad_cLindos] = Lindos;
	Ciudades[eCiudad_cArghal] = Arghal;
	Ciudades[eCiudad_cArkhein] = Arkhein;

	MD5sCarga(leerSini);

	ConsultaPopular.reset(new ConsultasPopulares());
	ConsultaPopular->LoadData();

	/* ' Admins */
	loadAdministrativeUsers();

}

void WriteVar(std::string File, std::string Main, std::string Var, int value) {
	WriteVar(File, Main, Var, std::to_string(value));
}

void WriteVar(std::string File, std::string Main, std::string Var, std::string value) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* 'Escribe VAR en un archivo */
	/* '*************************************************** */

	// writeprivateprofilestring(Main, Var, value, File);

	/* FIXME */

	clsIniManager iniReader;

	if (FileExist(File)) {
		iniReader.Initialize(File);
	}
	
	iniReader.ChangeValue(Main, Var, value);

	iniReader.DumpFile(File);
}

void WriteSaltedPasswordUserRAW(const std::string& Name, const std::string& Salt, const std::string& HashedPassword) {
	WriteVar(GetCharPath(Name), "INIT", "PasswordSalt", Salt);
	WriteVar(GetCharPath(Name), "INIT", "PasswordHash", HashedPassword);
	WriteVar(GetCharPath(Name), "INIT", "Password", "");
}

void WriteSaltedPasswordUserCopyFrom(const std::string& UserName, const std::string& copyFrom) {
	std::string Salt = GetVar(GetCharPath(copyFrom), "INIT", "PasswordSalt");
	std::string HashedPassword = GetVar(GetCharPath(copyFrom), "INIT", "PasswordHash");
	WriteSaltedPasswordUserRAW(UserName, Salt, HashedPassword);
}

void WriteSaltedPasswordUser(const std::string& Name, const std::string& Password) {
	std::string Salt = CryptoMakeRandomString(20);
	std::string HashedPassword = SHA1_HexString(Salt + ":" + Password);
	WriteSaltedPasswordUserRAW(Name, Salt, HashedPassword);
}

bool CheckPasswordUser(const std::string& Name, const std::string& Password) {
	std::string Salt = GetVar(GetCharPath(Name), "INIT", "PasswordSalt");
	std::string FileHashedPassword = GetVar(GetCharPath(Name), "INIT", "PasswordHash");
	std::string UserHashedPassword = SHA1_HexString(Salt + ":" + Password);

	/* '¿Es el passwd valido? */
	return FileHashedPassword == UserHashedPassword;
}

void SaveUser(int UserIndex, std::string UserFile, bool SaveTimeOnline) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 10/10/2010 (Pato) */
	/* 'Saves the Users RECORDs */
	/* '23/01/2007 Pablo (ToxicWaste) - Agrego NivelIngreso, FechaIngreso, MatadosIngreso y NextRecompensa. */
	/* '11/19/2009: Pato - Save the EluSkills and ExpSkills */
	/* '12/01/2010: ZaMa - Los druidas pierden la inmunidad de ser atacados cuando pierden el efecto del mimetismo. */
	/* '10/10/2010: Pato - Saco el WriteVar e implemento la clase clsIniManager */
	/* '************************************************* */


	std::shared_ptr<clsIniManager> Manager;
	bool Existe = false;
	(void)Existe;

	/* 'ESTO TIENE QUE EVITAR ESE BUGAZO QUE NO SE POR QUE GRABA USUARIOS NULOS */
	/* 'clase=0 es el error, porq el enum empieza de 1!! */
	if (UserList[UserIndex].clase == 0 || UserList[UserIndex].Stats.ELV == 0) {
		LogCriticEvent("Estoy intentantdo guardar un usuario nulo de nombre: " + UserList[UserIndex].Name);
		return;
	}

	Manager.reset(new clsIniManager());

	if (FileExist(UserFile)) {
		Manager->Initialize(UserFile);

		if (FileExist(UserFile + ".bk")) {
			vb6::Kill(UserFile + ".bk");
		}
		vb6::Name(UserFile, UserFile + ".bk");

		Existe = true;
	}

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

	int LoopC;

	Manager->ChangeValue("FLAGS", "Muerto", vb6::CStr(UserList[UserIndex].flags.Muerto));
	Manager->ChangeValue("FLAGS", "Escondido", vb6::CStr(UserList[UserIndex].flags.Escondido));
	Manager->ChangeValue("FLAGS", "Hambre", vb6::CStr(UserList[UserIndex].flags.Hambre));
	Manager->ChangeValue("FLAGS", "Sed", vb6::CStr(UserList[UserIndex].flags.Sed));
	Manager->ChangeValue("FLAGS", "Desnudo", vb6::CStr(UserList[UserIndex].flags.Desnudo));
	Manager->ChangeValue("FLAGS", "Ban", vb6::CStr(UserList[UserIndex].flags.Ban));
	Manager->ChangeValue("FLAGS", "Navegando", vb6::CStr(UserList[UserIndex].flags.Navegando));
	Manager->ChangeValue("FLAGS", "Envenenado", vb6::CStr(UserList[UserIndex].flags.Envenenado));
	Manager->ChangeValue("FLAGS", "Paralizado", vb6::CStr(UserList[UserIndex].flags.Paralizado));
	/* 'Matrix */
	Manager->ChangeValue("FLAGS", "LastMap", vb6::CStr(UserList[UserIndex].flags.lastMap));

	Manager->ChangeValue("CONSEJO", "PERTENECE",
			vb6::IIf(UserTienePrivilegio(UserIndex, PlayerType_RoyalCouncil), "1", "0"));
	Manager->ChangeValue("CONSEJO", "PERTENECECAOS",
			vb6::IIf(UserTienePrivilegio(UserIndex, PlayerType_ChaosCouncil), "1", "0"));

	Manager->ChangeValue("COUNTERS", "Pena", vb6::CStr(UserList[UserIndex].Counters.Pena));
	Manager->ChangeValue("COUNTERS", "SkillsAsignados",
			vb6::CStr(UserList[UserIndex].Counters.AsignedSkills));

	Manager->ChangeValue("FACCIONES", "EjercitoReal", vb6::CStr(UserList[UserIndex].Faccion.ArmadaReal));
	Manager->ChangeValue("FACCIONES", "EjercitoCaos", vb6::CStr(UserList[UserIndex].Faccion.FuerzasCaos));
	Manager->ChangeValue("FACCIONES", "CiudMatados",
			vb6::CStr(UserList[UserIndex].Faccion.CiudadanosMatados));
	Manager->ChangeValue("FACCIONES", "CrimMatados",
			vb6::CStr(UserList[UserIndex].Faccion.CriminalesMatados));
	Manager->ChangeValue("FACCIONES", "rArCaos", vb6::CStr(UserList[UserIndex].Faccion.RecibioArmaduraCaos));
	Manager->ChangeValue("FACCIONES", "rArReal", vb6::CStr(UserList[UserIndex].Faccion.RecibioArmaduraReal));
	Manager->ChangeValue("FACCIONES", "rExCaos",
			vb6::CStr(UserList[UserIndex].Faccion.RecibioExpInicialCaos));
	Manager->ChangeValue("FACCIONES", "rExReal",
			vb6::CStr(UserList[UserIndex].Faccion.RecibioExpInicialReal));
	Manager->ChangeValue("FACCIONES", "recCaos", vb6::CStr(UserList[UserIndex].Faccion.RecompensasCaos));
	Manager->ChangeValue("FACCIONES", "recReal", vb6::CStr(UserList[UserIndex].Faccion.RecompensasReal));
	Manager->ChangeValue("FACCIONES", "Reenlistadas", vb6::CStr(UserList[UserIndex].Faccion.Reenlistadas));
	Manager->ChangeValue("FACCIONES", "NivelIngreso", vb6::CStr(UserList[UserIndex].Faccion.NivelIngreso));
	Manager->ChangeValue("FACCIONES", "FechaIngreso", UserList[UserIndex].Faccion.FechaIngreso);
	Manager->ChangeValue("FACCIONES", "MatadosIngreso",
			vb6::CStr(UserList[UserIndex].Faccion.MatadosIngreso));
	Manager->ChangeValue("FACCIONES", "NextRecompensa",
			vb6::CStr(UserList[UserIndex].Faccion.NextRecompensa));

	/* '¿Fueron modificados los atributos del usuario? */
	if (!UserList[UserIndex].flags.TomoPocion) {
		for (LoopC = (1); LoopC <= (vb6::UBound(UserList[UserIndex].Stats.UserAtributos)); LoopC++) {
			Manager->ChangeValue("ATRIBUTOS", "AT" + vb6::CStr(LoopC),
					vb6::CStr(UserList[UserIndex].Stats.UserAtributos[LoopC]));
		}
	} else {
		for (LoopC = (1); LoopC <= (vb6::UBound(UserList[UserIndex].Stats.UserAtributos)); LoopC++) {
			/* '.Stats.UserAtributos(LoopC) = .Stats.UserAtributosBackUP(LoopC) */
			Manager->ChangeValue("ATRIBUTOS", "AT" + vb6::CStr(LoopC),
					vb6::CStr(UserList[UserIndex].Stats.UserAtributosBackUP[LoopC]));
		}
	}

	for (LoopC = (1); LoopC <= (vb6::UBound(UserList[UserIndex].Stats.UserSkills)); LoopC++) {
		Manager->ChangeValue("SKILLS", "SK" + vb6::CStr(LoopC), vb6::CStr(UserList[UserIndex].Stats.UserSkills[LoopC]));
		Manager->ChangeValue("SKILLS", "ELUSK" + vb6::CStr(LoopC),
				vb6::CStr(UserList[UserIndex].Stats.EluSkills[LoopC]));
		Manager->ChangeValue("SKILLS", "EXPSK" + vb6::CStr(LoopC),
				vb6::CStr(UserList[UserIndex].Stats.ExpSkills[LoopC]));
	}

	Manager->ChangeValue("CONTACTO", "Email", UserList[UserIndex].email);

	Manager->ChangeValue("INIT", "Genero", std::to_string(UserList[UserIndex].Genero));
	Manager->ChangeValue("INIT", "Raza", std::to_string(UserList[UserIndex].raza));
	Manager->ChangeValue("INIT", "Hogar", std::to_string(UserList[UserIndex].Hogar));
	Manager->ChangeValue("INIT", "Clase", std::to_string(UserList[UserIndex].clase));
	Manager->ChangeValue("INIT", "Desc", UserList[UserIndex].desc);

	Manager->ChangeValue("INIT", "Heading", vb6::CStr(UserList[UserIndex].Char.heading));
	Manager->ChangeValue("INIT", "Head", vb6::CStr(UserList[UserIndex].OrigChar.Head));

	if (UserList[UserIndex].flags.Muerto == 0) {
		if (UserList[UserIndex].Char.body != 0) {
			Manager->ChangeValue("INIT", "Body", vb6::CStr(UserList[UserIndex].Char.body));
		}
	}

	Manager->ChangeValue("INIT", "Arma", vb6::CStr(UserList[UserIndex].Char.WeaponAnim));
	Manager->ChangeValue("INIT", "Escudo", vb6::CStr(UserList[UserIndex].Char.ShieldAnim));
	Manager->ChangeValue("INIT", "Casco", vb6::CStr(UserList[UserIndex].Char.CascoAnim));

	/* # IF ConUpTime THEN */

	if (SaveTimeOnline) {
		boost::posix_time::time_duration TempDate;
		TempDate = vb6::Now() - UserList[UserIndex].LogOnTime;
		UserList[UserIndex].LogOnTime = vb6::Now();
		UserList[UserIndex].UpTime = UserList[UserIndex].UpTime + TempDate.minutes();
		//UserList[UserIndex].UpTime = UserList[UserIndex].UpTime;
		Manager->ChangeValue("INIT", "UpTime", std::to_string(UserList[UserIndex].UpTime));
	}
	/* # END IF */

	/* 'First time around? */
	if (Manager->GetValue("INIT", "LastIP1") == "") {
		Manager->ChangeValue("INIT", "LastIP1", UserList[UserIndex].ip + " - " + vb6::dateToString(vb6::Now()));
		/* 'Is it a different ip from last time? */
	} else if (UserList[UserIndex].ip
			!= vb6::Left(Manager->GetValue("INIT", "LastIP1"),
					vb6::InStr(1, Manager->GetValue("INIT", "LastIP1"), " ") - 1)) {
		int i;
		for (i = (5); ((-1) > 0) ? (i <= (2)) : (i >= (2)); i = i + (-1)) {
			Manager->ChangeValue("INIT", "LastIP" + vb6::CStr(i),
					Manager->GetValue("INIT", "LastIP" + vb6::CStr(i - 1)));
		}
		Manager->ChangeValue("INIT", "LastIP1", UserList[UserIndex].ip + " - " + vb6::dateToString(vb6::Now()));
		/* 'Same ip, just update the date */
	} else {
		Manager->ChangeValue("INIT", "LastIP1", UserList[UserIndex].ip + " - " + vb6::dateToString(vb6::Now()));
	}

	Manager->ChangeValue("INIT", "Position",
			vb6::CStr(UserList[UserIndex].Pos.Map) + "-" + vb6::CStr(UserList[UserIndex].Pos.X) + "-"
					+ vb6::CStr(UserList[UserIndex].Pos.Y));

	Manager->ChangeValue("STATS", "GLD", vb6::CStr(UserList[UserIndex].Stats.GLD));
	Manager->ChangeValue("STATS", "BANCO", vb6::CStr(UserList[UserIndex].Stats.Banco));

	Manager->ChangeValue("STATS", "MaxHP", vb6::CStr(UserList[UserIndex].Stats.MaxHp));
	Manager->ChangeValue("STATS", "MinHP", vb6::CStr(UserList[UserIndex].Stats.MinHp));

	Manager->ChangeValue("STATS", "MaxSTA", vb6::CStr(UserList[UserIndex].Stats.MaxSta));
	Manager->ChangeValue("STATS", "MinSTA", vb6::CStr(UserList[UserIndex].Stats.MinSta));

	Manager->ChangeValue("STATS", "MaxMAN", vb6::CStr(UserList[UserIndex].Stats.MaxMAN));
	Manager->ChangeValue("STATS", "MinMAN", vb6::CStr(UserList[UserIndex].Stats.MinMAN));

	Manager->ChangeValue("STATS", "MaxHIT", vb6::CStr(UserList[UserIndex].Stats.MaxHIT));
	Manager->ChangeValue("STATS", "MinHIT", vb6::CStr(UserList[UserIndex].Stats.MinHIT));

	Manager->ChangeValue("STATS", "MaxAGU", vb6::CStr(UserList[UserIndex].Stats.MaxAGU));
	Manager->ChangeValue("STATS", "MinAGU", vb6::CStr(UserList[UserIndex].Stats.MinAGU));

	Manager->ChangeValue("STATS", "MaxHAM", vb6::CStr(UserList[UserIndex].Stats.MaxHam));
	Manager->ChangeValue("STATS", "MinHAM", vb6::CStr(UserList[UserIndex].Stats.MinHam));

	Manager->ChangeValue("STATS", "SkillPtsLibres", vb6::CStr(UserList[UserIndex].Stats.SkillPts));

	Manager->ChangeValue("STATS", "EXP", vb6::CStr(UserList[UserIndex].Stats.Exp));
	Manager->ChangeValue("STATS", "ELV", vb6::CStr(UserList[UserIndex].Stats.ELV));

	Manager->ChangeValue("STATS", "ELU", vb6::CStr(UserList[UserIndex].Stats.ELU));
	Manager->ChangeValue("MUERTES", "UserMuertes", vb6::CStr(UserList[UserIndex].Stats.UsuariosMatados));
	/* 'Call Manager.ChangeValue( "MUERTES", "CrimMuertes", CStr(.Stats.CriminalesMatados)) */
	Manager->ChangeValue("MUERTES", "NpcsMuertes", vb6::CStr(UserList[UserIndex].Stats.NPCsMuertos));

	/* '[KEVIN]---------------------------------------------------------------------------- */
	/* '******************************************************************************************* */
	Manager->ChangeValue("BancoInventory", "CantidadItems",
			vb6::CStr(UserList[UserIndex].BancoInvent.NroItems));
	int loopd;
	for (loopd = (1); loopd <= (MAX_BANCOINVENTORY_SLOTS); loopd++) {
		Manager->ChangeValue("BancoInventory", "Obj" + vb6::CStr(loopd),
				vb6::string_format("%d-%d", UserList[UserIndex].BancoInvent.Object[loopd].ObjIndex,
											UserList[UserIndex].BancoInvent.Object[loopd].Amount));
	}
	/* '******************************************************************************************* */
	/* '[/KEVIN]----------- */

	/* 'Save Inv */
	Manager->ChangeValue("Inventory", "CantidadItems", vb6::CStr(UserList[UserIndex].Invent.NroItems));

	for (LoopC = (1); LoopC <= (MAX_INVENTORY_SLOTS); LoopC++) {
		Manager->ChangeValue("Inventory", "Obj" + vb6::CStr(LoopC),
				vb6::string_format("%d-%d-%d", UserList[UserIndex].Invent.Object[LoopC].ObjIndex,
						UserList[UserIndex].Invent.Object[LoopC].Amount,
						UserList[UserIndex].Invent.Object[LoopC].Equipped));
	}

	Manager->ChangeValue("Inventory", "WeaponEqpSlot", vb6::CStr(UserList[UserIndex].Invent.WeaponEqpSlot));
	Manager->ChangeValue("Inventory", "ArmourEqpSlot", vb6::CStr(UserList[UserIndex].Invent.ArmourEqpSlot));
	Manager->ChangeValue("Inventory", "CascoEqpSlot", vb6::CStr(UserList[UserIndex].Invent.CascoEqpSlot));
	Manager->ChangeValue("Inventory", "EscudoEqpSlot", vb6::CStr(UserList[UserIndex].Invent.EscudoEqpSlot));
	Manager->ChangeValue("Inventory", "BarcoSlot", vb6::CStr(UserList[UserIndex].Invent.BarcoSlot));
	Manager->ChangeValue("Inventory", "MunicionSlot", vb6::CStr(UserList[UserIndex].Invent.MunicionEqpSlot));
	Manager->ChangeValue("Inventory", "MochilaSlot", vb6::CStr(UserList[UserIndex].Invent.MochilaEqpSlot));
	/* '/Nacho */

	Manager->ChangeValue("Inventory", "AnilloSlot", vb6::CStr(UserList[UserIndex].Invent.AnilloEqpSlot));

	/* 'Reputacion */
	Manager->ChangeValue("REP", "Asesino", vb6::CStr(UserList[UserIndex].Reputacion.AsesinoRep));
	Manager->ChangeValue("REP", "Bandido", vb6::CStr(UserList[UserIndex].Reputacion.BandidoRep));
	Manager->ChangeValue("REP", "Burguesia", vb6::CStr(UserList[UserIndex].Reputacion.BurguesRep));
	Manager->ChangeValue("REP", "Ladrones", vb6::CStr(UserList[UserIndex].Reputacion.LadronesRep));
	Manager->ChangeValue("REP", "Nobles", vb6::CStr(UserList[UserIndex].Reputacion.NobleRep));
	Manager->ChangeValue("REP", "Plebe", vb6::CStr(UserList[UserIndex].Reputacion.PlebeRep));

	int L;
	L = (-UserList[UserIndex].Reputacion.AsesinoRep) + (-UserList[UserIndex].Reputacion.BandidoRep)
			+ UserList[UserIndex].Reputacion.BurguesRep + (-UserList[UserIndex].Reputacion.LadronesRep)
			+ UserList[UserIndex].Reputacion.NobleRep + UserList[UserIndex].Reputacion.PlebeRep;
	L = L / 6;
	Manager->ChangeValue("REP", "Promedio", vb6::CStr(L));

	std::string cad;

	for (LoopC = (1); LoopC <= (MAXUSERHECHIZOS); LoopC++) {
		cad = vb6::CStr(UserList[UserIndex].Stats.UserHechizos[LoopC]);
		Manager->ChangeValue("HECHIZOS", "H" + vb6::CStr(LoopC), cad);
	}

	int NroMascotas;
	NroMascotas = UserList[UserIndex].NroMascotas;

	for (LoopC = (1); LoopC <= (MAXMASCOTAS); LoopC++) {
		/* ' Mascota valida? */
		if (UserList[UserIndex].MascotasIndex[LoopC] > 0) {
			/* ' Nos aseguramos que la criatura no fue invocada */
			if (Npclist[UserList[UserIndex].MascotasIndex[LoopC]].Contadores.TiempoExistencia == 0) {
				cad = vb6::CStr(UserList[UserIndex].MascotasType[LoopC]);
				/* 'Si fue invocada no la guardamos */
			} else {
				cad = "0";
				NroMascotas = NroMascotas - 1;
			}
			Manager->ChangeValue("MASCOTAS", "MAS" + vb6::CStr(LoopC), cad);
		} else {
			cad = vb6::CStr(UserList[UserIndex].MascotasType[LoopC]);
			Manager->ChangeValue("MASCOTAS", "MAS" + vb6::CStr(LoopC), cad);
		}
	}

	Manager->ChangeValue("MASCOTAS", "NroMascotas", vb6::CStr(NroMascotas));

	/* 'Devuelve el head de muerto */
	if (UserList[UserIndex].flags.Muerto == 1) {
		UserList[UserIndex].Char.Head = iCabezaMuerto;
	}

	Manager->DumpFile(UserFile, true);

	Manager.reset();

#if 0
	if (Existe) {
		vb6::Kill(UserFile + ".bk");
	}
#endif

	return;
}

bool criminal(int UserIndex) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int L;

	L = (-UserList[UserIndex].Reputacion.AsesinoRep) + (-UserList[UserIndex].Reputacion.BandidoRep)
			+ UserList[UserIndex].Reputacion.BurguesRep + (-UserList[UserIndex].Reputacion.LadronesRep)
			+ UserList[UserIndex].Reputacion.NobleRep + UserList[UserIndex].Reputacion.PlebeRep;
	L = L / 6;
	retval = (L < 0);

	return retval;
}

void BackUPnPc(int NpcIndex, std::ofstream& npcfile) {

	int LoopC;

	npcfile << "[NPC" << Npclist[NpcIndex].Numero << "]" << std::endl;

	/* 'General */
	npcfile << "Name=" << Npclist[NpcIndex].Name << std::endl;
	npcfile << "Desc=" << Npclist[NpcIndex].desc << std::endl;
	npcfile << "Head=" << Npclist[NpcIndex].Char.Head << std::endl;
	npcfile << "Body=" << Npclist[NpcIndex].Char.body << std::endl;
	npcfile << "Heading=" << Npclist[NpcIndex].Char.heading << std::endl;
	npcfile << "Movement=" << Npclist[NpcIndex].Movement << std::endl;
	npcfile << "Attackable=" << Npclist[NpcIndex].Attackable << std::endl;
	npcfile << "Comercia=" << Npclist[NpcIndex].Comercia << std::endl;
	npcfile << "TipoItems=" << Npclist[NpcIndex].TipoItems << std::endl;
	npcfile << "Hostil=" << Npclist[NpcIndex].Hostile << std::endl;
	npcfile << "GiveEXP=" << Npclist[NpcIndex].GiveEXP << std::endl;
	npcfile << "GiveGLD=" << Npclist[NpcIndex].GiveGLD << std::endl;
	npcfile << "InvReSpawn=" << Npclist[NpcIndex].InvReSpawn << std::endl;
	npcfile << "NpcType=" << Npclist[NpcIndex].NPCtype << std::endl;

	/* 'Stats */
	npcfile << "Alineacion=" << Npclist[NpcIndex].Stats.Alineacion << std::endl;
	npcfile << "DEF=" << Npclist[NpcIndex].Stats.def << std::endl;
	npcfile << "MaxHit=" << Npclist[NpcIndex].Stats.MaxHIT << std::endl;
	npcfile << "MaxHp=" << Npclist[NpcIndex].Stats.MaxHp << std::endl;
	npcfile << "MinHit=" << Npclist[NpcIndex].Stats.MinHIT << std::endl;
	npcfile << "MinHp=" << Npclist[NpcIndex].Stats.MinHp << std::endl;

	/* 'Flags */
	npcfile << "ReSpawn=" << Npclist[NpcIndex].flags.Respawn << std::endl;
	npcfile << "BackUp=" << Npclist[NpcIndex].flags.BackUp << std::endl;
	npcfile << "Domable=" << Npclist[NpcIndex].flags.Domable << std::endl;

	/* 'Inventario */
	npcfile << "NroItems=" << Npclist[NpcIndex].Invent.NroItems << std::endl;
	if (Npclist[NpcIndex].Invent.NroItems > 0) {
		for (LoopC = (1); LoopC <= (Npclist[NpcIndex].Invent.NroItems); LoopC++) {
			npcfile << "Obj" << LoopC << "=" << Npclist[NpcIndex].Invent.Object[LoopC].ObjIndex << "-" << Npclist[NpcIndex].Invent.Object[LoopC].Amount << std::endl;
		}
	}

	npcfile << std::endl;
}

void CargarNpcBackUp(int NpcIndex, int NpcNumber) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	/* 'Status */
	std::cout << "Cargando backup Npc" << std::endl;

	std::string npcfile;

	/* 'If NpcNumber > 499 Then */
	/* '    npcfile = DatPath & "bkNPCs-HOSTILES.dat" */
	/* 'Else */
	npcfile = GetDatPath(DATPATH::bkNpcs);
	/* 'End If */

	std::string npcNumberStr = "NPC" + std::to_string(NpcNumber);

	Npclist[NpcIndex].Numero = NpcNumber;
	Npclist[NpcIndex].Name = GetVar(npcfile, npcNumberStr, "Name");
	Npclist[NpcIndex].desc = GetVar(npcfile, npcNumberStr, "Desc");
	Npclist[NpcIndex].Movement = static_cast<TipoAI>(vb6::CInt(GetVar(npcfile, npcNumberStr, "Movement")));
	Npclist[NpcIndex].NPCtype = static_cast<eNPCType>(vb6::CInt(GetVar(npcfile, npcNumberStr, "NpcType")));

	Npclist[NpcIndex].Char.body = vb6::val(GetVar(npcfile, npcNumberStr, "Body"));
	Npclist[NpcIndex].Char.Head = vb6::val(GetVar(npcfile, npcNumberStr, "Head"));
	Npclist[NpcIndex].Char.heading =
			static_cast<eHeading>(vb6::CInt(GetVar(npcfile, npcNumberStr, "Heading")));

	Npclist[NpcIndex].Attackable = vb6::val(GetVar(npcfile, npcNumberStr, "Attackable"));
	Npclist[NpcIndex].Comercia = vb6::val(GetVar(npcfile, npcNumberStr, "Comercia"));
	Npclist[NpcIndex].Hostile = vb6::val(GetVar(npcfile, npcNumberStr, "Hostile"));
	Npclist[NpcIndex].GiveEXP = vb6::val(GetVar(npcfile, npcNumberStr, "GiveEXP"));

	Npclist[NpcIndex].GiveGLD = vb6::val(GetVar(npcfile, npcNumberStr, "GiveGLD"));

	Npclist[NpcIndex].InvReSpawn = vb6::val(GetVar(npcfile, npcNumberStr, "InvReSpawn"));

	Npclist[NpcIndex].Stats.MaxHp = vb6::val(GetVar(npcfile, npcNumberStr, "MaxHP"));
	Npclist[NpcIndex].Stats.MinHp = vb6::val(GetVar(npcfile, npcNumberStr, "MinHP"));
	Npclist[NpcIndex].Stats.MaxHIT = vb6::val(GetVar(npcfile, npcNumberStr, "MaxHIT"));
	Npclist[NpcIndex].Stats.MinHIT = vb6::val(GetVar(npcfile, npcNumberStr, "MinHIT"));
	Npclist[NpcIndex].Stats.def = vb6::val(GetVar(npcfile, npcNumberStr, "DEF"));
	Npclist[NpcIndex].Stats.Alineacion = vb6::val(GetVar(npcfile, npcNumberStr, "Alineacion"));

	int LoopC;
	std::string ln;
	Npclist[NpcIndex].Invent.NroItems = vb6::val(GetVar(npcfile, npcNumberStr, "NROITEMS"));
	if (Npclist[NpcIndex].Invent.NroItems > 0) {
		for (LoopC = (1); LoopC <= (MAX_INVENTORY_SLOTS); LoopC++) {
			ln = GetVar(npcfile, npcNumberStr, "Obj" + std::to_string(LoopC));
			Npclist[NpcIndex].Invent.Object[LoopC].ObjIndex = vb6::val(ReadField(1, ln, 45));
			Npclist[NpcIndex].Invent.Object[LoopC].Amount = vb6::val(ReadField(2, ln, 45));

		}
	} else {
		for (LoopC = (1); LoopC <= (MAX_INVENTORY_SLOTS); LoopC++) {
			Npclist[NpcIndex].Invent.Object[LoopC].ObjIndex = 0;
			Npclist[NpcIndex].Invent.Object[LoopC].Amount = 0;
		}
	}

	for (LoopC = (1); LoopC <= (MAX_NPC_DROPS); LoopC++) {
		ln = GetVar(npcfile, npcNumberStr, "Drop" + std::to_string(LoopC));
		Npclist[NpcIndex].Drop[LoopC].ObjIndex = vb6::val(ReadField(1, ln, 45));
		Npclist[NpcIndex].Drop[LoopC].Amount = vb6::val(ReadField(2, ln, 45));
	}

	Npclist[NpcIndex].flags.NPCActive = true;
	Npclist[NpcIndex].flags.Respawn = vb6::val(GetVar(npcfile, npcNumberStr, "ReSpawn"));
	Npclist[NpcIndex].flags.BackUp = vb6::val(GetVar(npcfile, npcNumberStr, "BackUp"));
	Npclist[NpcIndex].flags.Domable = vb6::val(GetVar(npcfile, npcNumberStr, "Domable"));
	Npclist[NpcIndex].flags.RespawnOrigPos = vb6::val(GetVar(npcfile, npcNumberStr, "OrigPos"));

	/* 'Tipo de items con los que comercia */
	Npclist[NpcIndex].TipoItems = vb6::val(GetVar(npcfile, npcNumberStr, "TipoItems"));

}

void Ban(std::string BannedName, std::string Baneador, std::string Motivo) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	WriteVar(GetLogFileName("BanDetail"), BannedName, "BannedBy", Baneador);
	WriteVar(GetLogFileName("BanDetail"), BannedName, "Reason", Motivo);

	/* 'Log interno del servidor, lo usa para hacer un UNBAN general de toda la gente banned */
	LogGenteBanned(BannedName);
}

void CargaApuestas() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	Apuestas.Ganancias = vb6::val(GetVar(GetDatPath(DATPATH::apuestas), "Main", "Ganancias"));
	Apuestas.Perdidas = vb6::val(GetVar(GetDatPath(DATPATH::apuestas), "Main", "Perdidas"));
	Apuestas.Jugadas = vb6::val(GetVar(GetDatPath(DATPATH::apuestas), "Main", "Jugadas"));

}

void generateMatrix() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int i;
	int j;

	distanceToCities.redim(0);
	distanceToCities.redim(1, NumMaps);

	for (j = (1); j <= (NUMCIUDADES); j++) {
		for (i = (1); i <= (NumMaps); i++) {
			distanceToCities[i].distanceToCity[j] = -1;
		}
	}

	for (j = (1); j <= (NUMCIUDADES); j++) {
		for (i = (1); i <= (4); i++) {
			switch (i) {
			case eHeading_NORTH:
				setDistance(getLimit(Ciudades[j].Map, eHeading_NORTH), j, i, 0, 1);
				break;

			case eHeading_EAST:
				setDistance(getLimit(Ciudades[j].Map, eHeading_EAST), j, i, 1, 0);
				break;

			case eHeading_SOUTH:
				setDistance(getLimit(Ciudades[j].Map, eHeading_SOUTH), j, i, 0, 1);
				break;

			case eHeading_WEST:
				setDistance(getLimit(Ciudades[j].Map, eHeading_WEST), j, i, -1, 0);
				break;
			}
		}
	}

}

void setDistance(int mapa, int city, int side, int X, int Y) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */
	(void)side;

	int i;
	int lim;

	if (mapa <= 0 || mapa > NumMaps) {
		return;
	}

	if (distanceToCities[mapa].distanceToCity[city] >= 0) {
		return;
	}

	if (mapa == Ciudades[city].Map) {
		distanceToCities[mapa].distanceToCity[city] = 0;
	} else {
		distanceToCities[mapa].distanceToCity[city] = vb6::Abs(X) + vb6::Abs(Y);
	}

	for (i = (1); i <= (4); i++) {
		lim = getLimit(mapa, static_cast<eHeading>(i));
		if (lim > 0) {
			switch (i) {
			case eHeading_NORTH:
				setDistance(lim, city, i, X, Y + 1);
				break;

			case eHeading_EAST:
				setDistance(lim, city, i, X + 1, Y);
				break;

			case eHeading_SOUTH:
				setDistance(lim, city, i, X, Y - 1);
				break;

			case eHeading_WEST:
				setDistance(lim, city, i, X - 1, Y);
				break;

			case eHeading_None:
				break;
			}
		}
	}
}

int getLimit(int mapa, eHeading side) {
	int retval = 0;
	/* '*************************************************** */
	/* 'Author: Budi */
	/* 'Last Modification: 31/01/2010 */
	/* 'Retrieves the limit in the given side in the given map. */
	/* 'TODO: This should be set in the .inf map file. */
	/* '*************************************************** */
	int X;
	int Y;

	if (mapa <= 0) {
		return retval;
	}

	for (X = (15); X <= (87); X++) {
		for (Y = (0); Y <= (3); Y++) {
			switch (side) {
			case eHeading_NORTH:
				retval = MapData[mapa][X][7 + Y].TileExit.Map;
				break;

			case eHeading_EAST:
				retval = MapData[mapa][92 - Y][X].TileExit.Map;
				break;

			case eHeading_SOUTH:
				retval = MapData[mapa][X][94 - Y].TileExit.Map;
				break;

			case eHeading_WEST:
				retval = MapData[mapa][9 + Y][X].TileExit.Map;
				break;

			default:
				break;
			}
			if (retval > 0) {
				return retval;
			}
		}
	}
	return retval;
}

void LoadArmadurasFaccion() {
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 15/04/2010 */
	/* ' */
	/* '*************************************************** */
	int ClassIndex;

	int ArmaduraIndex;

	clsIniManager leerArm;
	leerArm.Initialize(GetDatPath(DATPATH::ArmadurasFaccionarias));


	for (ClassIndex = (1); ClassIndex <= (NUMCLASES); ClassIndex++) {

		/* ' Defensa minima para armadas altos */
		ArmaduraIndex = vb6::val(
				leerArm.GetValue("CLASE" + vb6::CStr(ClassIndex), "DefMinArmyAlto"));

		ArmadurasFaccion[ClassIndex][eRaza_Drow].Armada[eTipoDefArmors_ieBaja] = ArmaduraIndex;
		ArmadurasFaccion[ClassIndex][eRaza_Elfo].Armada[eTipoDefArmors_ieBaja] = ArmaduraIndex;
		ArmadurasFaccion[ClassIndex][eRaza_Humano].Armada[eTipoDefArmors_ieBaja] = ArmaduraIndex;

		/* ' Defensa minima para armadas bajos */
		ArmaduraIndex = vb6::val(
				leerArm.GetValue("CLASE" + vb6::CStr(ClassIndex), "DefMinArmyBajo"));

		ArmadurasFaccion[ClassIndex][eRaza_Enano].Armada[eTipoDefArmors_ieBaja] = ArmaduraIndex;
		ArmadurasFaccion[ClassIndex][eRaza_Gnomo].Armada[eTipoDefArmors_ieBaja] = ArmaduraIndex;

		/* ' Defensa minima para caos altos */
		ArmaduraIndex = vb6::val(
				leerArm.GetValue("CLASE" + vb6::CStr(ClassIndex), "DefMinCaosAlto"));

		ArmadurasFaccion[ClassIndex][eRaza_Drow].Caos[eTipoDefArmors_ieBaja] = ArmaduraIndex;
		ArmadurasFaccion[ClassIndex][eRaza_Elfo].Caos[eTipoDefArmors_ieBaja] = ArmaduraIndex;
		ArmadurasFaccion[ClassIndex][eRaza_Humano].Caos[eTipoDefArmors_ieBaja] = ArmaduraIndex;

		/* ' Defensa minima para caos bajos */
		ArmaduraIndex = vb6::val(
				leerArm.GetValue("CLASE" + vb6::CStr(ClassIndex), "DefMinCaosBajo"));

		ArmadurasFaccion[ClassIndex][eRaza_Enano].Caos[eTipoDefArmors_ieBaja] = ArmaduraIndex;
		ArmadurasFaccion[ClassIndex][eRaza_Gnomo].Caos[eTipoDefArmors_ieBaja] = ArmaduraIndex;

		/* ' Defensa media para armadas altos */
		ArmaduraIndex = vb6::val(
				leerArm.GetValue("CLASE" + vb6::CStr(ClassIndex), "DefMedArmyAlto"));

		ArmadurasFaccion[ClassIndex][eRaza_Drow].Armada[eTipoDefArmors_ieMedia] = ArmaduraIndex;
		ArmadurasFaccion[ClassIndex][eRaza_Elfo].Armada[eTipoDefArmors_ieMedia] = ArmaduraIndex;
		ArmadurasFaccion[ClassIndex][eRaza_Humano].Armada[eTipoDefArmors_ieMedia] = ArmaduraIndex;

		/* ' Defensa media para armadas bajos */
		ArmaduraIndex = vb6::val(
				leerArm.GetValue("CLASE" + vb6::CStr(ClassIndex), "DefMedArmyBajo"));

		ArmadurasFaccion[ClassIndex][eRaza_Enano].Armada[eTipoDefArmors_ieMedia] = ArmaduraIndex;
		ArmadurasFaccion[ClassIndex][eRaza_Gnomo].Armada[eTipoDefArmors_ieMedia] = ArmaduraIndex;

		/* ' Defensa media para caos altos */
		ArmaduraIndex = vb6::val(
				leerArm.GetValue("CLASE" + vb6::CStr(ClassIndex), "DefMedCaosAlto"));

		ArmadurasFaccion[ClassIndex][eRaza_Drow].Caos[eTipoDefArmors_ieMedia] = ArmaduraIndex;
		ArmadurasFaccion[ClassIndex][eRaza_Elfo].Caos[eTipoDefArmors_ieMedia] = ArmaduraIndex;
		ArmadurasFaccion[ClassIndex][eRaza_Humano].Caos[eTipoDefArmors_ieMedia] = ArmaduraIndex;

		/* ' Defensa media para caos bajos */
		ArmaduraIndex = vb6::val(
				leerArm.GetValue("CLASE" + vb6::CStr(ClassIndex), "DefMedCaosBajo"));

		ArmadurasFaccion[ClassIndex][eRaza_Enano].Caos[eTipoDefArmors_ieMedia] = ArmaduraIndex;
		ArmadurasFaccion[ClassIndex][eRaza_Gnomo].Caos[eTipoDefArmors_ieMedia] = ArmaduraIndex;

		/* ' Defensa alta para armadas altos */
		ArmaduraIndex = vb6::val(
				leerArm.GetValue("CLASE" + vb6::CStr(ClassIndex), "DefAltaArmyAlto"));

		ArmadurasFaccion[ClassIndex][eRaza_Drow].Armada[eTipoDefArmors_ieAlta] = ArmaduraIndex;
		ArmadurasFaccion[ClassIndex][eRaza_Elfo].Armada[eTipoDefArmors_ieAlta] = ArmaduraIndex;
		ArmadurasFaccion[ClassIndex][eRaza_Humano].Armada[eTipoDefArmors_ieAlta] = ArmaduraIndex;

		/* ' Defensa alta para armadas bajos */
		ArmaduraIndex = vb6::val(
				leerArm.GetValue("CLASE" + vb6::CStr(ClassIndex), "DefAltaArmyBajo"));

		ArmadurasFaccion[ClassIndex][eRaza_Enano].Armada[eTipoDefArmors_ieAlta] = ArmaduraIndex;
		ArmadurasFaccion[ClassIndex][eRaza_Gnomo].Armada[eTipoDefArmors_ieAlta] = ArmaduraIndex;

		/* ' Defensa alta para caos altos */
		ArmaduraIndex = vb6::val(
				leerArm.GetValue("CLASE" + vb6::CStr(ClassIndex), "DefAltaCaosAlto"));

		ArmadurasFaccion[ClassIndex][eRaza_Drow].Caos[eTipoDefArmors_ieAlta] = ArmaduraIndex;
		ArmadurasFaccion[ClassIndex][eRaza_Elfo].Caos[eTipoDefArmors_ieAlta] = ArmaduraIndex;
		ArmadurasFaccion[ClassIndex][eRaza_Humano].Caos[eTipoDefArmors_ieAlta] = ArmaduraIndex;

		/* ' Defensa alta para caos bajos */
		ArmaduraIndex = vb6::val(
				leerArm.GetValue("CLASE" + vb6::CStr(ClassIndex), "DefAltaCaosBajo"));

		ArmadurasFaccion[ClassIndex][eRaza_Enano].Caos[eTipoDefArmors_ieAlta] = ArmaduraIndex;
		ArmadurasFaccion[ClassIndex][eRaza_Gnomo].Caos[eTipoDefArmors_ieAlta] = ArmaduraIndex;

	}

}
