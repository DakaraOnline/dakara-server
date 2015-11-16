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

#ifndef MODGUILDS_H
#define MODGUILDS_H

#include <vector>
#include <memory>
#include <string>
#include <set>

#include "vb6compat.h"
#include "enums.h"

/* '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''' */
/* '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''' */
/* 'DECLARACIOENS PUBLICAS CONCERNIENTES AL JUEGO */
/* 'Y CONFIGURACION DEL SISTEMA DE CLANES */
/* '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''' */
/* 'archivo .\guilds\guildinfo.ini o similar */

/* 'cantidad maxima de guilds en el servidor */

extern int CANTIDADDECLANES;
/* 'cantidad actual de clanes en el servidor */

/* 'array global de guilds, se indexa por userlist().guildindex */

/* 'cantidad maxima de codecs que se pueden definir */

extern const int MAXASPIRANTES;
/* 'cantidad maxima de aspirantes que puede tener un clan acumulados a la vez */

extern const int MAXCLANMEMBERS;

/* 'puntos maximos de antifaccion que un clan tolera antes de ser cambiada su alineacion */

/* 'alineaciones permitidas */

/* 'numero de .wav del cliente */

/* 'estado entre clanes */
/* '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''' */
/* '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''' */
/* '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''' */

void LoadGuildsDB();

bool m_ConectarMiembroAClan(int UserIndex, int GuildIndex);

bool m_ValidarPermanencia(int UserIndex, bool SumaAntifaccion, bool & CambioAlineacion);

void UpdateGuildMembers(int GuildIndex);

ALINEACION_GUILD BajarGrado(int GuildIndex);

void m_DesconectarMiembroDelClan(int UserIndex, int GuildIndex);

bool m_EsGuildLeader(const std::string & PJ, int GuildIndex);

bool m_EsGuildFounder(const std::string & PJ, int GuildIndex);

int m_EcharMiembroDeClan(int Expulsador, std::string Expulsado);

void ActualizarWebSite(int UserIndex, const std::string & Web);

void ChangeCodexAndDesc(std::string & desc, std::vector<std::string> & codex, int GuildIndex);

void ActualizarNoticias(int UserIndex, std::string Datos);

bool CrearNuevoClan(int FundadorIndex, std::string & desc, std::string & GuildName, std::string & URL,
		std::vector<std::string> & codex, ALINEACION_GUILD Alineacion, std::string & refError);

void SendGuildNews(int UserIndex);

bool m_PuedeSalirDeClan(std::string & Nombre, int GuildIndex, int QuienLoEchaUI);

bool PuedeFundarUnClan(int UserIndex, ALINEACION_GUILD Alineacion, std::string & refError);

bool m_EstadoPermiteEntrarChar(std::string & Personaje, int GuildIndex);

bool m_EstadoPermiteEntrar(int UserIndex, int GuildIndex);

ALINEACION_GUILD String2Alineacion(std::string S);

std::string Alineacion2String(ALINEACION_GUILD Alineacion);

std::string Relacion2String(RELACIONES_GUILD Relacion);

RELACIONES_GUILD String2Relacion(std::string S);

bool GuildNameValido(std::string cad);

bool YaExiste(std::string GuildName);

bool HasFound(std::string & UserName);

bool v_AbrirElecciones(int UserIndex, std::string & refError);

bool v_UsuarioVota(int UserIndex, std::string & Votado, std::string & refError);

void v_RutinaElecciones();

int GetGuildIndexFromChar(std::string & PlayerName);

int GetGuildIndex(std::string GuildName);

std::string m_ListaDeMiembrosOnline(int UserIndex, int GuildIndex);

std::vector<std::string> PrepareGuildsList();

void SendGuildDetails(int UserIndex, std::string GuildName);

void SendGuildLeaderInfo(int UserIndex);

const std::set<int>& guild_Iterador_ProximoUserIndex(int GuildIndex);

const std::set<int>& guild_Iterador_ProximoGM(int GuildIndex);

// int m_Iterador_ProximoUserIndex(int GuildIndex);

// int Iterador_ProximoGM(int GuildIndex);

int r_Iterador_ProximaPropuesta(int GuildIndex, RELACIONES_GUILD Tipo);

int GMEscuchaClan(int UserIndex, std::string GuildName);

void GMDejaDeEscucharClan(int UserIndex, int GuildIndex);

int r_DeclararGuerra(int UserIndex, std::string & GuildGuerra, std::string & refError);

int r_AceptarPropuestaDePaz(int UserIndex, std::string & GuildPaz, std::string & refError);

int r_RechazarPropuestaDeAlianza(int UserIndex, std::string & GuildPro, std::string & refError);

int r_RechazarPropuestaDePaz(int UserIndex, std::string & GuildPro, std::string & refError);

int r_AceptarPropuestaDeAlianza(int UserIndex, std::string & GuildAllie, std::string & refError);

bool r_ClanGeneraPropuesta(int UserIndex, std::string & OtroClan, RELACIONES_GUILD Tipo,
		std::string & Detalle, std::string & refError);

std::string r_VerPropuesta(int UserIndex, std::string & OtroGuild, RELACIONES_GUILD Tipo,
		std::string & refError);

std::vector<std::string> r_ListaDePropuestas(int UserIndex, RELACIONES_GUILD Tipo);

void a_RechazarAspiranteChar(std::string & Aspirante, int guild, std::string & Detalles);

std::string a_ObtenerRechazoDeChar(std::string & Aspirante);

bool a_RechazarAspirante(int UserIndex, std::string & Nombre, std::string & refError);

std::string a_DetallesAspirante(int UserIndex, std::string & Nombre);

void SendDetallesPersonaje(int UserIndex, std::string Personaje);

bool a_NuevoAspirante(int UserIndex, std::string & clan, std::string & Solicitud, std::string & refError);

bool a_AceptarAspirante(int UserIndex, std::string & Aspirante, std::string & refError);

std::string GuildName(int GuildIndex);

std::string GuildLeader(int GuildIndex);

std::string GuildAlignment(int GuildIndex);

std::string GuildFounder(int GuildIndex);

void SetNewGuildName(int GuildIndex, std::string & newGuildName);

#endif
