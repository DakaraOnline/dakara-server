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

#ifndef CLSPARTY_H
#define CLSPARTY_H
#include <vector>
#include <memory>
#include <string>

#include <boost/noncopyable.hpp>

#include "vb6compat.h"
#include "enums.h"

class clsParty: private boost::noncopyable {

private:
	vb6::array<struct tPartyMember> p_members;
	/* 'miembros */

private:
	int p_expTotal;
	/* 'Estadistica :D */

private:
	int p_Fundador;
	/* 'el creador */

private:
	int p_CantMiembros;
	/* 'cantidad de miembros */

private:
	float p_SumaNivelesElevados;
	/* 'suma de todos los niveles elevados a la ExponenteNivelParty > Esta variable se usa para calcular la experiencia repartida en la Party. */

	/* 'datos en los pjs: | indexParty(indice en p_members), partyLeader(userindex del lider) | */

	/* 'Constructor de clase */
public:
	clsParty();
	~clsParty();

	/* '' */
	/* ' Sets the new p_sumaniveleselevados to the party. */
	/* ' */
	/* ' @param lvl Specifies reference to user level */
	/* ' @remarks When a user level up and he is in a party, we update p_sumaNivelesElavados so the formula still works. */
public:
	void UpdateSumaNivelesElevados(int Lvl);

public:
	int MiExperiencia(int UserIndex);

public:
	void ObtenerExito(int ExpGanada, int mapa, int X, int Y);

public:
	void MandarMensajeAConsola(std::string texto, std::string Sender);

public:
	bool EsPartyLeader(int UserIndex);

public:
	bool NuevoMiembro(int UserIndex);

public:
	bool SaleMiembro(int UserIndex);

public:
	bool HacerLeader(int UserIndex);

public:
	void ObtenerMiembrosOnline(std::vector<int> & MemberList);

public:
	int ObtenerExperienciaTotal();

public:
	bool PuedeEntrar(int UserIndex, std::string razon);

public:
	void FlushExperiencia();

private:
	void CompactMemberList();

public:
	int CantMiembros();

};
#endif
