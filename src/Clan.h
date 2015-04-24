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

#ifndef CLSCLAN_H
#define CLSCLAN_H
#include <vector>
#include <memory>
#include <string>
#include <set>
#include "vb6compat.h"
#include "enums.h"

class clsClan {

private:
	std::string p_GuildName;
private:
	ALINEACION_GUILD p_Alineacion;
	/* 'Array de UserIndexes! */
private:
	std::set<int> p_OnlineMembers;
private:
	std::set<int> p_GMsOnline;
private:
	std::set<int> p_PropuestasDePaz;
private:
	std::set<int> p_PropuestasDeAlianza;
	/* 'Numero de guild en el mundo */
private:
	int p_GuildNumber;
	/* 'array de relaciones con los otros clanes */
private:
	std::vector<RELACIONES_GUILD> p_Relaciones;
private:
	std::string GUILDINFOFILE;
	/* 'aca pq me es mas comodo setearlo y pq en ningun disenio */
private:
	//std::string GUILDPATH;
	/* 'decente la capa de arriba se entera donde estan */
private:
	std::string MEMBERSFILE;
	/* 'los datos fisicamente */
private:
	std::string SOLICITUDESFILE;
private:
	std::string PROPUESTASFILE;
private:
	std::string RELACIONESFILE;
private:
	std::string VOTACIONESFILE;

public:
	std::string GuildName();

	/* ' */
	/* 'ALINEACION Y ANTIFACCION */
	/* ' */

public:
	ALINEACION_GUILD Alineacion();

public:
	int PuntosAntifaccion();

public:
	void PuntosAntifaccion(int p);

public:
	bool CambiarAlineacion(ALINEACION_GUILD NuevaAlineacion);

	/* ' */
	/* 'INICIALIZADORES */
	/* ' */

public:
	clsClan();
	~clsClan();

public:
	void Inicializar(std::string GuildName, int GuildNumber,
			ALINEACION_GUILD Alineacion);

	/* '' */
	/* ' esta TIENE QUE LLAMARSE LUEGO DE INICIALIZAR() */
	/* ' */
	/* ' @param Fundador Nombre del fundador del clan */
	/* ' */
public:
	void InicializarNuevoClan(std::string & Fundador);

public:
	void ProcesarFundacionDeOtroClan();

	/* ' */
	/* 'MEMBRESIAS */
	/* ' */

public:
	std::string Fundador();

	/* 'Public Property Get JugadoresOnline() As String */
	/* 'Dim i As Integer */
	/* '    'leve violacion de capas x aqui, je */
	/* '    For i = 1 To p_OnlineMembers.Count */
	/* '        JugadoresOnline = UserList(p_OnlineMembers.Item(i)).Name & "," & JugadoresOnline */
	/* '    Next i */
	/* 'End Property */

public:
	int CantidadDeMiembros();

public:
	void SetLeader(std::string & leader);

public:
	std::string GetLeader();

public:
	std::vector<std::string> GetMemberList();

public:
	void ConectarMiembro(int UserIndex);

public:
	void DesConectarMiembro(int UserIndex);

public:
	bool EsMiembro(std::string Nombre);

public:
	void AceptarNuevoMiembro(std::string & Nombre);

public:
	void ExpulsarMiembro(const std::string & Nombre);

public:
	void RemoveMemberName(std::string Nombre);

	/* ' */
	/* 'ASPIRANTES */
	/* ' */

public:
	std::vector<std::string> GetAspirantes();

public:
	int CantidadAspirantes();

public:
	std::string DetallesSolicitudAspirante(int NroAspirante);

public:
	int NumeroDeAspirante(std::string Nombre);

public:
	void NuevoAspirante(std::string Nombre, std::string Peticion);

public:
	void RetirarAspirante(std::string Nombre, int NroAspirante);

public:
	void InformarRechazoEnChar(std::string Nombre, std::string Detalles);

	/* ' */
	/* 'DEFINICION DEL CLAN (CODEX Y NOTICIAS) */
	/* ' */

public:
	std::string GetFechaFundacion();

public:
	void SetCodex(int CodexNumber, std::string codex);

public:
	std::string GetCodex(int CodexNumber);

public:
	void SetURL(const std::string & URL);

public:
	std::string GetURL();

public:
	void SetGuildNews(std::string News);

public:
	std::string GetGuildNews();

public:
	void SetDesc(std::string desc);

public:
	std::string GetDesc();

	/* ' */
	/* ' */
	/* 'ELECCIONES */
	/* ' */
	/* ' */

public:
	bool EleccionesAbiertas();

public:
	void AbrirElecciones();

	/* 'solo pueden cerrarse mediante recuento de votos */
private:
	void CerrarElecciones();

public:
	void ContabilizarVoto(std::string Votante, std::string Votado);

public:
	bool YaVoto(std::string Votante);

private:
	std::string ContarVotos(int & CantGanadores);

public:
	bool RevisarElecciones();

	/* '/VOTACIONES */

	/* ' */
	/* 'RELACIONES */
	/* ' */

public:
	int CantidadPropuestas(RELACIONES_GUILD Tipo);

public:
	int CantidadEnemys();

public:
	int CantidadAllies();

public:
	RELACIONES_GUILD GetRelacion(int OtroGuild);

public:
	void SetRelacion(int GuildIndex, RELACIONES_GUILD Relacion);

public:
	void SetPropuesta(RELACIONES_GUILD Tipo, int OtroGuild,
			std::string & Detalle);

public:
	void AnularPropuestas(int OtroGuild);

public:
	std::string GetPropuesta(int OtroGuild, RELACIONES_GUILD & Tipo);

public:
	bool HayPropuesta(int OtroGuild, RELACIONES_GUILD Tipo);

	/* 'Public Function GetEnemy(ByVal EnemyIndex As Integer) As String */
	/* '    GetEnemy = GetVar(ENEMIESFILE, "ENEMYS", "ENEMY" & EnemyIndex) */
	/* 'End Function */

	/* 'Public Function GetAllie(ByVal AllieIndex As Integer) As String */
	/* '    GetAllie = GetVar(ALLIESFILE, "ALLIES", "ALLIE" & AllieIndex) */
	/* 'End Function */

	/* ' */
	/* 'ITERADORES */
	/* ' */

public:
	const std::set<int>& Iterador_ProximaPropuesta(RELACIONES_GUILD Tipo);

public:
	const std::set<int>& m_Iterador_ProximoUserIndex();

public:
	const std::set<int>& Iterador_ProximoGM();

public:
	const std::vector<RELACIONES_GUILD>& Iterador_ProximaRelacion();

	/* ' */
	/* ' */
	/* ' */

	/* ' */
	/* 'ADMINISTRATIVAS */
	/* ' */

public:
	void ConectarGM(int UserIndex);

public:
	void DesconectarGM(int UserIndex);

	/* ' */
	/* 'VARIAS, EXTRAS Y DEMASES */
	/* ' */

private:
	void ReplaceInvalidChars(std::string & S);

public:
	void SetGuildName(std::string newGuildName);

};
#endif
