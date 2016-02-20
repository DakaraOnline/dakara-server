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

#include "Clan.h"

#include "boost/date_time/posix_time/posix_time_types.hpp"

static const int NEWSLENGTH = 1024;
static const int DESCLENGTH = 256;
static const int CODEXLENGTH = 256;

std::string clsClan::GuildName() {
	std::string retval;
	retval = p_GuildName;
	return retval;
}

/* ' */
/* 'ALINEACION Y ANTIFACCION */
/* ' */

ALINEACION_GUILD clsClan::Alineacion() {
	ALINEACION_GUILD retval;
	retval = p_Alineacion;
	return retval;
}

int clsClan::PuntosAntifaccion() {
	int retval;
	retval = (int) vb6::val(GetVar(GUILDINFOFILE, "GUILD" + vb6::CStr(p_GuildNumber), "Antifaccion"));
	return retval;
}

void clsClan::PuntosAntifaccion(int p) {
	WriteVar(GUILDINFOFILE, "GUILD" + vb6::CStr(p_GuildNumber), "Antifaccion", vb6::CStr(p));
}

bool clsClan::CambiarAlineacion(ALINEACION_GUILD NuevaAlineacion) {
	bool retval = false;
	p_Alineacion = NuevaAlineacion;
	WriteVar(GUILDINFOFILE, "GUILD" + vb6::CStr(p_GuildNumber), "Alineacion", Alineacion2String(p_Alineacion));

	if (p_Alineacion == ALINEACION_GUILD_ALINEACION_NEUTRO) {
		retval = true;
	}
	return retval;
}

/* ' */
/* 'INICIALIZADORES */
/* ' */

clsClan::clsClan() : p_Alineacion(ALINEACION_GUILD_Null), p_GuildNumber(0) {
	// GUILDPATH = GetGuildPath();
	GUILDINFOFILE = GetDatPath(DATPATH::GuildsInfo);
}

clsClan::~clsClan() {

}

void clsClan::Inicializar(std::string GuildName, int GuildNumber, ALINEACION_GUILD Alineacion) {
	int i;

	p_GuildNumber = GuildNumber;
	p_Alineacion = Alineacion;
	p_OnlineMembers.clear();
	p_GMsOnline.clear();
	p_PropuestasDePaz.clear();
	p_PropuestasDeAlianza.clear();

	SetGuildName(GuildName);

	clsIniManager iniRelaciones;
	clsIniManager iniPropuestas;

	try {
		iniRelaciones.Initialize(RELACIONESFILE);
	} catch (std::runtime_error& e) {
		iniRelaciones.DumpFile(RELACIONESFILE);
	}

	try {
		iniPropuestas.Initialize(PROPUESTASFILE);
	} catch (std::runtime_error& e) {
		iniPropuestas.DumpFile(PROPUESTASFILE);
	}

	{
		clsIniManager iniTmp;
		try {
			iniTmp.Initialize(MEMBERSFILE);
		} catch (std::runtime_error& e) {
			iniTmp.DumpFile(MEMBERSFILE);
		}
	}

	{
		clsIniManager iniTmp;
		try {
			iniTmp.Initialize(SOLICITUDESFILE);
		} catch (std::runtime_error& e) {
			iniTmp.DumpFile(SOLICITUDESFILE);
		}
	}

	{
		clsIniManager iniTmp;
		try {
			iniTmp.Initialize(VOTACIONESFILE);
		} catch (std::runtime_error& e) {
			iniTmp.DumpFile(VOTACIONESFILE);
		}
	}

	p_Relaciones.resize(1 + CANTIDADDECLANES);
	for (i = (1); i <= (CANTIDADDECLANES); i++) {
		p_Relaciones[i] = String2Relacion(iniRelaciones.GetValue("RELACIONES", vb6::CStr(i)));
	}
	for (i = (1); i <= (CANTIDADDECLANES); i++) {
		if (vb6::Trim(iniPropuestas.GetValue(vb6::CStr(i), "Pendiente")) == "1") {
			switch (String2Relacion(vb6::Trim(iniPropuestas.GetValue(vb6::CStr(i), "Tipo")))) {
			case RELACIONES_GUILD_ALIADOS:
				p_PropuestasDeAlianza.insert(i);
				break;

			case RELACIONES_GUILD_PAZ:
				p_PropuestasDePaz.insert(i);
				break;

			default:
				break;
			}
		}
	}
}

/* '' */
/* ' esta TIENE QUE LLAMARSE LUEGO DE INICIALIZAR() */
/* ' */
/* ' @param Fundador Nombre del fundador del clan */
/* ' */
void clsClan::InicializarNuevoClan(std::string & Fundador) {
	/* 'string pq al comienzo quizas no hay archivo guildinfo.ini y oldq es "" */
	std::string OldQ;
	int NewQ;
	/* 'para que genere los archivos */
	WriteVar(MEMBERSFILE, "INIT", "NroMembers", "0");
	WriteVar(SOLICITUDESFILE, "INIT", "CantSolicitudes", "0");

	OldQ = GetVar(GUILDINFOFILE, "INIT", "nroguilds");
	if (vb6::IsNumeric(OldQ)) {
		NewQ = vb6::CInt(vb6::Trim(OldQ)) + 1;
	} else {
		NewQ = 1;
	}

	WriteVar(GUILDINFOFILE, "INIT", "NroGuilds", std::to_string(NewQ));

	WriteVar(GUILDINFOFILE, "GUILD" + vb6::CStr(NewQ), "Founder", Fundador);
	WriteVar(GUILDINFOFILE, "GUILD" + vb6::CStr(NewQ), "GuildName", p_GuildName);
	WriteVar(GUILDINFOFILE, "GUILD" + vb6::CStr(NewQ), "Date", vb6::dateToString(vb6::Now()));
	WriteVar(GUILDINFOFILE, "GUILD" + vb6::CStr(NewQ), "Antifaccion", "0");
	WriteVar(GUILDINFOFILE, "GUILD" + vb6::CStr(NewQ), "Alineacion", Alineacion2String(p_Alineacion));

}

void clsClan::ProcesarFundacionDeOtroClan() {
	p_Relaciones.resize(1 + CANTIDADDECLANES);
	p_Relaciones[CANTIDADDECLANES] = RELACIONES_GUILD_PAZ;
}

/* ' */
/* 'MEMBRESIAS */
/* ' */

std::string clsClan::Fundador() {
	std::string retval;
	retval = GetVar(GUILDINFOFILE, "GUILD" + vb6::CStr(p_GuildNumber), "Founder");
	return retval;
}

/* 'Public Property Get JugadoresOnline() As String */
/* 'Dim i As Integer */
/* '    'leve violacion de capas x aqui, je */
/* '    For i = 1 To p_OnlineMembers.Count */
/* '        JugadoresOnline = UserList(p_OnlineMembers.Item(i)).Name & "," & JugadoresOnline */
/* '    Next i */
/* 'End Property */

int clsClan::CantidadDeMiembros() {
	int retval;
	std::string OldQ;
	OldQ = GetVar(MEMBERSFILE, "INIT", "NroMembers");
	retval = vb6::IIf(vb6::IsNumeric(OldQ), vb6::Constrain(vb6::CInt(OldQ), 0, MAXCLANMEMBERS), 0);
	return retval;
}

void clsClan::SetLeader(std::string & leader) {
	WriteVar(GUILDINFOFILE, "GUILD" + vb6::CStr(p_GuildNumber), "Leader", leader);
}

std::string clsClan::GetLeader() {
	std::string retval;
	retval = GetVar(GUILDINFOFILE, "GUILD" + vb6::CStr(p_GuildNumber), "Leader");
	return retval;
}

std::vector<std::string> clsClan::GetMemberList() {
	int OldQ;
	std::vector<std::string> list;
	int i;

	OldQ = CantidadDeMiembros();

	list.resize(OldQ);

	for (i = (1); i <= (OldQ); i++) {
		list[i - 1] = vb6::UCase(GetVar(MEMBERSFILE, "Members", "Member" + vb6::CStr(i)));
	}

	return list;
}

void clsClan::ConectarMiembro(int UserIndex) {
	/* '*************************************************** */
	/* 'Autor: Unknown (orginal version) */
	/* 'Last Modification: 28/05/2010 */
	/* '28/05/2010: ZaMa - No avisa cuando loguea un dios o admin. */
	/* '*************************************************** */
	p_OnlineMembers.insert(UserIndex);

	/* ' No avisa cuando loguea un dios */
	if (UserTienePrivilegio(UserIndex, PlayerType_Admin) || UserTienePrivilegio(UserIndex, PlayerType_Dios)) {
		SendData(SendTarget_ToDiosesYclan, UserList[UserIndex].GuildIndex,
				dakara::protocol::server::BuildGuildChat(UserList[UserIndex].Name + " se ha conectado."));
	}
}

void clsClan::DesConectarMiembro(int UserIndex) {
	/* '*************************************************** */
	/* 'Autor: Unknown (orginal version) */
	/* 'Last Modification: 28/05/2010 */
	/* '28/05/2010: ZaMa - No avisa cuando desloguea un dios o admin. */
	/* '*************************************************** */
	auto it = p_OnlineMembers.find((UserIndex));

	if (it != p_OnlineMembers.end()) {
		p_OnlineMembers.erase(it);

		/* ' No avisa cuando se desconecta un dios */
		if (UserTienePrivilegio(UserIndex, PlayerType_Admin) || UserTienePrivilegio(UserIndex, PlayerType_Dios)) {
			SendData(SendTarget_ToDiosesYclan, UserList[UserIndex].GuildIndex,
					dakara::protocol::server::BuildGuildChat(UserList[UserIndex].Name + " se ha desconectado."));
		}
	}
}

void clsClan::AceptarNuevoMiembro(std::string & Nombre) {
	int OldQ;
	std::string OldQs;
	std::string ruta;

	ruta = GetCharPath(Nombre);
	if (FileExist(ruta)) {
		WriteVar(ruta, "GUILD", "GUILDINDEX", std::to_string(p_GuildNumber));
		WriteVar(ruta, "GUILD", "AspiranteA", "0");
		/* 'CantPs = GetVar(CharPath & Nombre & ".chr", "GUILD", "ClanesParticipo") */
		/* 'If IsNumeric(CantPs) Then */
		/* '    CantP = CInt(CantPs) */
		/* 'Else */
		/* '    CantP = 0 */
		/* 'End If */
		/* 'Call WriteVar(CharPath & Nombre & ".chr", "GUILD", "ClanesParticipo", CantP + 1) */
		OldQs = GetVar(MEMBERSFILE, "INIT", "NroMembers");
		if (vb6::IsNumeric(OldQs)) {
			OldQ = vb6::Constrain(vb6::CInt(OldQs), 0, MAXCLANMEMBERS);
		} else {
			OldQ = 0;
		}
		WriteVar(MEMBERSFILE, "INIT", "NroMembers", std::to_string(OldQ + 1));
		WriteVar(MEMBERSFILE, "Members", "Member" + std::to_string(OldQ + 1), Nombre);
	}

}

bool clsClan::EsMiembro(std::string Nombre) {
	int i;
	int OldQ;
	if (FileExist(GetCharPath(Nombre))) {
		OldQ = vb6::CInt(GetVar(MEMBERSFILE, "INIT", "NroMembers"));
		i = 1;
		Nombre = vb6::UCase(Nombre);
		while (i <= OldQ
				&& vb6::UCase(vb6::Trim(GetVar(MEMBERSFILE, "Members", "Member" + std::to_string(i))))
						!= Nombre) {
			i = i + 1;
		}
		return i <= OldQ;
	}
	return false;
}

void clsClan::ExpulsarMiembro(const std::string & Nombre) {
	std::string Temps;
	std::string MiembroDe;

	RemoveMemberName(Nombre);

	/* 'lo echo a el */
	MiembroDe = GetVar(GetCharPath(Nombre), "GUILD", "Miembro");
	if (vb6::InStr(1, vb6::UCase(MiembroDe), vb6::UCase(p_GuildName)) == 0) {
		if (vb6::LenB(MiembroDe) != 0) {
			MiembroDe = MiembroDe + ",";
		}
		MiembroDe = MiembroDe + p_GuildName;
		WriteVar(GetCharPath(Nombre), "GUILD", "Miembro", MiembroDe);
	}
}

void clsClan::RemoveMemberName(std::string Nombre) {
	int OldQ;
	std::string Temps;
	int i;
	bool EsMiembro;

	OldQ = vb6::CInt(GetVar(MEMBERSFILE, "INIT", "NroMembers"));
	OldQ = vb6::Constrain(OldQ, 0, MAXCLANMEMBERS);

	i = 1;
	Nombre = vb6::UCase(Nombre);
	while (i <= OldQ && vb6::UCase(vb6::Trim(GetVar(MEMBERSFILE, "Members", "Member" + vb6::CStr(i)))) != Nombre) {
		i = i + 1;
	}
	EsMiembro = (i <= OldQ);

	if (EsMiembro) {
		while (i < OldQ) {
			Temps = GetVar(MEMBERSFILE, "Members", "Member" + std::to_string(i + 1));
			WriteVar(MEMBERSFILE, "Members", "Member" + std::to_string(i), Temps);
			i = i + 1;
		}

		WriteVar(MEMBERSFILE, "Members", "Member" + std::to_string(OldQ), "");
		/* 'seteo la cantidad de miembros nueva */
		WriteVar(MEMBERSFILE, "INIT", "NroMembers", std::to_string(OldQ - 1));
	}
}

/* ' */
/* 'ASPIRANTES */
/* ' */

std::vector<std::string> clsClan::GetAspirantes() {
	int OldQ;
	std::vector<std::string> list;
	int i;

	OldQ = CantidadAspirantes();

	list.resize(OldQ);

	for (i = (1); i <= (OldQ); i++) {
		list[i - 1] = GetVar(SOLICITUDESFILE, "SOLICITUD" + vb6::CStr(i), "Nombre");
	}

	return list;
}

int clsClan::CantidadAspirantes() {
	int retval;
	std::string Temps;

	retval = 0;
	Temps = GetVar(SOLICITUDESFILE, "INIT", "CantSolicitudes");
	if (!vb6::IsNumeric(Temps)) {
		return retval;
	}
	retval = vb6::Constrain(vb6::CInt(Temps), 0, INT_MAX);

	return retval;
}

std::string clsClan::DetallesSolicitudAspirante(int NroAspirante) {
	std::string retval;
	retval = GetVar(SOLICITUDESFILE, "SOLICITUD" + vb6::CStr(NroAspirante), "Detalle");
	return retval;
}

int clsClan::NumeroDeAspirante(std::string Nombre) {
	int retval;
	int i;

	retval = 0;

	for (i = (1); i <= (MAXASPIRANTES); i++) {
		std::string solicitudi = "SOLICITUD" + std::to_string(i);
		if (vb6::UCase(vb6::Trim(GetVar(SOLICITUDESFILE, solicitudi, "Nombre"))) == vb6::UCase(Nombre)) {
			retval = i;
			return retval;
		}
	}
	return retval;
}

void clsClan::NuevoAspirante(std::string Nombre, std::string Peticion) {
	int i;
	std::string OldQ;
	int OldQI;

	OldQ = GetVar(SOLICITUDESFILE, "INIT", "CantSolicitudes");
	if (vb6::IsNumeric(OldQ)) {
		OldQI = vb6::CInt(OldQ);
	} else {
		OldQI = 0;
	}
	for (i = (1); i <= (MAXASPIRANTES); i++) {
		std::string solicitudi = "SOLICITUD" + std::to_string(i);
		if (GetVar(SOLICITUDESFILE, solicitudi, "Nombre") == "") {
			WriteVar(SOLICITUDESFILE, solicitudi, "Nombre", Nombre);
			WriteVar(SOLICITUDESFILE, solicitudi, "Detalle",
					vb6::IIf(vb6::Trim(Peticion).size() == 0, std::string("Peticion vacia"), Peticion));
			WriteVar(SOLICITUDESFILE, "INIT", "CantSolicitudes", std::to_string(OldQI + 1));
			WriteVar(GetCharPath(Nombre), "GUILD", "ASPIRANTEA", std::to_string(p_GuildNumber));
			return;
		}
	}
}

void clsClan::RetirarAspirante(std::string Nombre, int NroAspirante) {
	std::string OldQ;
	int OldQI;
	std::string Pedidos;
	int i;

	OldQ = GetVar(SOLICITUDESFILE, "INIT", "CantSolicitudes");
	if (vb6::IsNumeric(OldQ)) {
		OldQI = vb6::CInt(OldQ);
	} else {
		OldQI = 1;
	}
	/* 'Call WriteVar(SOLICITUDESFILE, "SOLICITUD" & NroAspirante, "Nombre", vbNullString) */
	/* 'Call WriteVar(SOLICITUDESFILE, "SOLICITUD" & NroAspirante, "Detalle", vbNullString) */
	WriteVar(GetCharPath(Nombre), "GUILD", "ASPIRANTEA", "0");
	Pedidos = GetVar(GetCharPath(Nombre), "GUILD", "Pedidos");
	if (vb6::InStr(1, vb6::UCase(Pedidos), vb6::UCase(p_GuildName)) == 0) {
		if (vb6::LenB(Pedidos) != 0) {
			Pedidos = Pedidos + ",";
		}
		Pedidos = Pedidos + p_GuildName;
		WriteVar(GetCharPath(Nombre), "GUILD", "Pedidos", Pedidos);
	}

	WriteVar(SOLICITUDESFILE, "INIT", "CantSolicitudes", std::to_string(OldQI - 1));
	for (i = (NroAspirante); i <= (MAXASPIRANTES - 1); i++) {
		std::string solicitudi = "SOLICITUD" + std::to_string(i);
		WriteVar(SOLICITUDESFILE, solicitudi, "Nombre",
				GetVar(SOLICITUDESFILE, "SOLICITUD" + std::to_string(i + 1), "Nombre"));
		WriteVar(SOLICITUDESFILE, "SOLICITUD" + vb6::CStr(i), "Detalle",
				GetVar(SOLICITUDESFILE, "SOLICITUD" + std::to_string(i + 1), "Detalle"));
	}

	WriteVar(SOLICITUDESFILE, "SOLICITUD" + std::to_string(MAXASPIRANTES), "Nombre", "");
	WriteVar(SOLICITUDESFILE, "SOLICITUD" + std::to_string(MAXASPIRANTES), "Detalle", "");
}

void clsClan::InformarRechazoEnChar(std::string Nombre, std::string Detalles) {
	WriteVar(GetCharPath(Nombre), "GUILD", "MotivoRechazo", Detalles);
}

/* ' */
/* 'DEFINICION DEL CLAN (CODEX Y NOTICIAS) */
/* ' */

std::string clsClan::GetFechaFundacion() {
	return GetVar(GUILDINFOFILE, "GUILD" + std::to_string(p_GuildNumber), "Date");
}

void clsClan::SetCodex(int CodexNumber, std::string codex) {
	ReplaceInvalidChars(codex);
	codex = vb6::Left(codex, CODEXLENGTH);
	WriteVar(GUILDINFOFILE, "GUILD" + std::to_string(p_GuildNumber), "Codex" + std::to_string(CodexNumber), codex);
}

std::string clsClan::GetCodex(int CodexNumber) {
	return GetVar(GUILDINFOFILE, "GUILD" + std::to_string(p_GuildNumber), "Codex" + std::to_string(CodexNumber));
}

void clsClan::SetURL(const std::string & URL) {
	WriteVar(GUILDINFOFILE, "GUILD" + std::to_string(p_GuildNumber), "URL", vb6::Left(URL, 40));
}

std::string clsClan::GetURL() {
	return GetVar(GUILDINFOFILE, "GUILD" + std::to_string(p_GuildNumber), "URL");
}

void clsClan::SetGuildNews(std::string News) {
	ReplaceInvalidChars(News);

	News = vb6::Left(News, NEWSLENGTH);

	WriteVar(GUILDINFOFILE, "GUILD" +  std::to_string(p_GuildNumber), "GuildNews", News);
}

std::string clsClan::GetGuildNews() {
	return GetVar(GUILDINFOFILE, "GUILD" +  std::to_string(p_GuildNumber), "GuildNews");
}

void clsClan::SetDesc(std::string desc) {
	ReplaceInvalidChars(desc);
	desc = vb6::Left(desc, DESCLENGTH);

	WriteVar(GUILDINFOFILE, "GUILD" +  std::to_string(p_GuildNumber), "Desc", desc);
}

std::string clsClan::GetDesc() {
	return GetVar(GUILDINFOFILE, "GUILD" +  std::to_string(p_GuildNumber), "Desc");
}

/* ' */
/* ' */
/* 'ELECCIONES */
/* ' */
/* ' */

bool clsClan::EleccionesAbiertas() {
	bool retval;
	std::string ee;
	ee = GetVar(GUILDINFOFILE, "GUILD" +  std::to_string(p_GuildNumber), "EleccionesAbiertas");
	/* 'cualquier otra cosa da falso */
	retval = (ee == "1");
	return retval;
}

void clsClan::AbrirElecciones() {
	WriteVar(GUILDINFOFILE, "GUILD" +  std::to_string(p_GuildNumber), "EleccionesAbiertas", "1");
	WriteVar(GUILDINFOFILE, "GUILD" +  std::to_string(p_GuildNumber), "EleccionesFinalizan", vb6::DateAdd("d", 1, vb6::Now()));
	WriteVar(VOTACIONESFILE, "INIT", "NumVotos", "0");
}

/* 'solo pueden cerrarse mediante recuento de votos */
void clsClan::CerrarElecciones() {
	WriteVar(GUILDINFOFILE, "GUILD" +  std::to_string(p_GuildNumber), "EleccionesAbiertas", "0");
	WriteVar(GUILDINFOFILE, "GUILD" +  std::to_string(p_GuildNumber), "EleccionesFinalizan", "");
}

void clsClan::ContabilizarVoto(std::string Votante, std::string Votado) {
	int q;
	std::string Temps;

	Temps = GetVar(VOTACIONESFILE, "INIT", "NumVotos");
	q = vb6::IIf(vb6::IsNumeric(Temps), vb6::CInt(Temps), 0);
	WriteVar(VOTACIONESFILE, "VOTOS", Votante, Votado);
	WriteVar(VOTACIONESFILE, "INIT", "NumVotos", vb6::CStr(q + 1));
}

bool clsClan::YaVoto(std::string Votante) {
	bool retval;
	auto a = GetVar(VOTACIONESFILE, "VOTOS", Votante);
	retval = ((vb6::LenB(vb6::Trim(a))) != 0);
	return retval;
}

std::string clsClan::ContarVotos(int & CantGanadores) {
	std::string retval;
	int q;
	int i;
	std::string Temps;
	std::string tempV;
	std::map<std::string, int> d;

	retval = "";
	CantGanadores = 0;
	Temps = GetVar(MEMBERSFILE, "INIT", "NroMembers");
	q = vb6::IsNumeric(Temps) ? vb6::Constrain(vb6::CInt(Temps), 0, MAXCLANMEMBERS) : 0;
	if (q > 0) {
		for (i = (1); i <= (q); i++) {
			/* 'miembro del clan */
			Temps = GetVar(MEMBERSFILE, "MEMBERS", "Member" + vb6::CStr(i));

			/* 'a quienvoto */
			tempV = GetVar(VOTACIONESFILE, "VOTOS", Temps);

			/* 'si voto a alguien contabilizamos el voto */
			if (vb6::LenB(tempV) != 0) {
				if (d.find(tempV) != d.end()) {
					d[tempV] = d[tempV] + 1;
				} else {
					d[tempV] = 1;
				}
			}
		}

		int maxVotos = 0;
		for (auto& e : d) {
			if (e.second > maxVotos) {
				maxVotos = e.second;
			}
		}
		for (auto& e : d) {
			if (e.second == maxVotos) {
				CantGanadores++;
				if (retval.size() > 0)
					retval += ",";
				retval += e.first;
			}
		}
	}

	return retval;
}

bool clsClan::RevisarElecciones() {
	bool retval;
	boost::posix_time::ptime FechaSufragio;
	std::string Temps;
	std::string Ganador;
	int CantGanadores;
	std::vector<std::string> list;
	int i;

	retval = false;
	Temps = vb6::Trim(GetVar(GUILDINFOFILE, "GUILD" + vb6::CStr(p_GuildNumber), "EleccionesFinalizan"));

	if (Temps == "") {
		return retval;
	}

	if (Temps.size() > 0) {
		try{
		FechaSufragio = vb6::CDate(Temps);
		}
		catch (std::exception &e){
			LogError(std::string("Error al leer fecha de archivo en RevisarElecciones()") + e.what());
			return false;
		}
		/* 'toca! */
		if (FechaSufragio < vb6::Now()) {
			Ganador = ContarVotos(CantGanadores);

			if (CantGanadores > 1) {
				/* 'empate en la votacion */
				SetGuildNews(
						"*Empate en la votación. " + Ganador + " con " + std::to_string(CantGanadores)
								+ " votos ganaron las elecciones del clan.");
			} else if (CantGanadores == 1) {
				list = GetMemberList();

				for (i = (0); i <= (vb6::UBound(list)); i++) {
					if (Ganador == list[i]) {
						break;
					}
				}

				if (i<=vb6::UBound(list)) {
					SetGuildNews("*" + Ganador + " ganó la elección del clan*");
					SetLeader(Ganador);
					retval = true;
				} else {
					SetGuildNews("*" + Ganador + " ganó la elección del clan pero abandonó las filas por lo que la votación queda desierta*");
				}
			} else {
				SetGuildNews("*El período de votación se cerró sin votos*");
			}

			CerrarElecciones();

		}
	} else {
		LogError("clsClan.RevisarElecciones: tempS is not Date");
	}

	return retval;
}

/* '/VOTACIONES */

/* ' */
/* 'RELACIONES */
/* ' */

int clsClan::CantidadPropuestas(RELACIONES_GUILD Tipo) {
	int retval = 0;
	switch (Tipo) {
	case RELACIONES_GUILD_ALIADOS:
		retval = p_PropuestasDeAlianza.size();
		break;

	case RELACIONES_GUILD_GUERRA:

		break;

	case RELACIONES_GUILD_PAZ:
		retval = p_PropuestasDePaz.size();
		break;

	default:
		break;
	}
	return retval;
}

int clsClan::CantidadEnemys() {
	int retval = 0;
	int i;
	for (i = (1); i <= (CANTIDADDECLANES); i++) {
		retval = retval + vb6::IIf(p_Relaciones[i] == RELACIONES_GUILD_GUERRA, 1, 0);
	}
	return retval;
}

int clsClan::CantidadAllies() {
	int retval = 0;
	int i;
	for (i = (1); i <= (CANTIDADDECLANES); i++) {
		retval = retval + vb6::IIf(p_Relaciones[i] == RELACIONES_GUILD_ALIADOS, 1, 0);
	}
	return retval;
}

RELACIONES_GUILD clsClan::GetRelacion(int OtroGuild) {
	RELACIONES_GUILD retval;
	retval = p_Relaciones[OtroGuild];
	return retval;
}

void clsClan::SetRelacion(int GuildIndex, RELACIONES_GUILD Relacion) {
	p_Relaciones[GuildIndex] = Relacion;
	WriteVar(RELACIONESFILE, "RELACIONES", vb6::CStr(GuildIndex), Relacion2String(Relacion));
}

void clsClan::SetPropuesta(RELACIONES_GUILD Tipo, int OtroGuild, std::string & Detalle) {
	WriteVar(PROPUESTASFILE, vb6::CStr(OtroGuild), "Detalle", Detalle);
	WriteVar(PROPUESTASFILE, vb6::CStr(OtroGuild), "Tipo", Relacion2String(Tipo));
	WriteVar(PROPUESTASFILE, vb6::CStr(OtroGuild), "Pendiente", "1");
	switch (Tipo) {
	case RELACIONES_GUILD_ALIADOS:
		p_PropuestasDeAlianza.insert(OtroGuild);
		break;

	case RELACIONES_GUILD_PAZ:
		p_PropuestasDePaz.insert(OtroGuild);
		break;

	default:
		break;
	}
}

void clsClan::AnularPropuestas(int OtroGuild) {
	WriteVar(PROPUESTASFILE, vb6::CStr(OtroGuild), "Detalle", "");
	WriteVar(PROPUESTASFILE, vb6::CStr(OtroGuild), "Pendiente", "0");

	auto it = p_PropuestasDePaz.find(OtroGuild);
	if (it != p_PropuestasDePaz.end()) {
		p_PropuestasDePaz.erase(it);
	}

	it = p_PropuestasDeAlianza.find(OtroGuild);
	if (it != p_PropuestasDeAlianza.end()) {
		p_PropuestasDeAlianza.erase(it);
	}
}

std::string clsClan::GetPropuesta(int OtroGuild, RELACIONES_GUILD & Tipo) {
	std::string retval;
	/* 'trae la solicitd que haya, no valida si es actual o de que tipo es */
	retval = GetVar(PROPUESTASFILE, vb6::CStr(OtroGuild), "Detalle");
	Tipo = String2Relacion(GetVar(PROPUESTASFILE, vb6::CStr(OtroGuild), "Tipo"));
	return retval;
}

bool clsClan::HayPropuesta(int OtroGuild, RELACIONES_GUILD Tipo) {
	bool retval;

	retval = false;
	switch (Tipo) {
	case RELACIONES_GUILD_ALIADOS:
		if (p_PropuestasDeAlianza.find(OtroGuild) != p_PropuestasDeAlianza.end()) {
			retval = true;
		}
		break;

	case RELACIONES_GUILD_PAZ:
		if (p_PropuestasDePaz.find(OtroGuild) != p_PropuestasDePaz.end()) {
			retval = true;
		}
		break;

	case RELACIONES_GUILD_GUERRA:

		break;

	default:
		break;
	}

	return retval;
}

/* 'Public Function GetEnemy(ByVal EnemyIndex As Integer) As String */
/* '    GetEnemy = GetVar(ENEMIESFILE, "ENEMYS", "ENEMY" & EnemyIndex) */
/* 'End Function */

/* 'Public Function GetAllie(ByVal AllieIndex As Integer) As String */
/* '    GetAllie = GetVar(ALLIESFILE, "ALLIES", "ALLIE" & AllieIndex) */
/* 'End Function */

/* ' */
/* 'ITERADORES */
/* ' */

const std::set<int>& clsClan::Iterador_ProximaPropuesta(RELACIONES_GUILD Tipo) {
	switch (Tipo) {
	case RELACIONES_GUILD_ALIADOS:
		return p_PropuestasDeAlianza;

	case RELACIONES_GUILD_PAZ:
		return p_PropuestasDePaz;

	default:
		throw std::runtime_error("unknown RELACIONES_GUILD " + std::to_string(Tipo));
	}
}

const std::set<int>& clsClan::m_Iterador_ProximoUserIndex() {
	return p_OnlineMembers;
}

const std::set<int>& clsClan::Iterador_ProximoGM() {
	return p_GMsOnline;
}

const std::vector<RELACIONES_GUILD>& clsClan::Iterador_ProximaRelacion() {
	return p_Relaciones;
}

/* ' */
/* ' */
/* ' */

/* ' */
/* 'ADMINISTRATIVAS */
/* ' */

void clsClan::ConectarGM(int UserIndex) {
	p_GMsOnline.insert(UserIndex);
}

void clsClan::DesconectarGM(int UserIndex) {
	auto it = p_GMsOnline.find(UserIndex);
	if (it != p_GMsOnline.end()) {
		p_GMsOnline.erase(it);
	}
}

/* ' */
/* 'VARIAS, EXTRAS Y DEMASES */
/* ' */

void clsClan::ReplaceInvalidChars(std::string & S) {
	if (vb6::InStrB(S, vb6::Chr(13)) != 0) {
		S = vb6::Replace(S, vb6::Chr(13), "");
	}
	if (vb6::InStrB(S, vb6::Chr(10)) != 0) {
		S = vb6::Replace(S, vb6::Chr(10), "");
	}
	if (vb6::InStrB(S, "¬") != 0) {
		/* 'morgo usaba esto como "separador" */
		S = vb6::Replace(S, "¬", "");
	}
}

void clsClan::SetGuildName(std::string newGuildName) {
	/* '*************************************************** */
	/* 'Author: Lex! */
	/* 'Last Modification: 14/05/2012 */
	/* 'Setea GuildName */
	/* '*************************************************** */
	p_GuildName = newGuildName;

	RELACIONESFILE = GetGuildsPath(p_GuildName, EGUILDPATH::Relaciones);
	MEMBERSFILE = GetGuildsPath(p_GuildName, EGUILDPATH::Members);
	PROPUESTASFILE = GetGuildsPath(p_GuildName, EGUILDPATH::Propositions);
	SOLICITUDESFILE = GetGuildsPath(p_GuildName, EGUILDPATH::Solicitudes);
	VOTACIONESFILE = GetGuildsPath(p_GuildName, EGUILDPATH::Votaciones);

//	RELACIONESFILE = GUILDPATH + p_GuildName + "-relaciones.rel";
//	MEMBERSFILE = GUILDPATH + p_GuildName + "-members.mem";
//	PROPUESTASFILE = GUILDPATH + p_GuildName + "-propositions.pro";
//	SOLICITUDESFILE = GUILDPATH + p_GuildName + "-solicitudes.sol";
//	VOTACIONESFILE = GUILDPATH + p_GuildName + "-votaciones.vot";
}
