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

#ifndef MDPARTY_H
#define MDPARTY_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

/* '' */
/* ' SOPORTES PARA LAS PARTIES */
/* ' (Ver este modulo como una clase abstracta "PartyManager") */
/* ' */

/* '' */
/* 'cantidad maxima de parties en el servidor */
extern const int MAX_PARTIES;

/* '' */
/* 'nivel minimo para crear party */
extern const int MINPARTYLEVEL;

/* '' */
/* 'Cantidad maxima de gente en la party */
extern const int PARTY_MAXMEMBERS;

/* '' */
/* 'Si esto esta en True, la exp sale por cada golpe que le da */
/* 'Si no, la exp la recibe al salirse de la party (pq las partys, floodean) */
extern const bool PARTY_EXPERIENCIAPORGOLPE;

/* '' */
/* 'maxima diferencia de niveles permitida en una party */
extern const int MAXPARTYDELTALEVEL;

/* '' */
/* 'distancia al leader para que este acepte el ingreso */
extern const int MAXDISTANCIAINGRESOPARTY;

/* '' */
/* 'maxima distancia a un exito para obtener su experiencia */
extern const int PARTY_MAXDISTANCIA;

/* '' */
/* 'restan las muertes de los miembros? */
extern const bool CASTIGOS;

/* '' */
/* 'Numero al que elevamos el nivel de cada miembro de la party */
/* 'Esto es usado para calcular la distribución de la experiencia entre los miembros */
/* 'Se lee del archivo de balance */
extern float ExponenteNivelParty;

/* '' */
/* 'tPartyMember */
/* ' */
/* ' @param UserIndex UserIndex */
/* ' @param Experiencia Experiencia */
/* ' */
struct tPartyMember {
	int UserIndex;
	double Experiencia;
};

int NextParty();

bool PuedeCrearParty(int UserIndex);

void CrearParty(int UserIndex);

void SolicitarIngresoAParty(int UserIndex);

void SalirDeParty(int UserIndex);

void ExpulsarDeParty(int leader, int OldMember);

/* '' */
/* ' Determines if a user can use party commands like /acceptparty or not. */
/* ' */
/* ' @param User Specifies reference to user */
/* ' @return  True if the user can use party commands, false if not. */
bool UserPuedeEjecutarComandos(int User);

void AprobarIngresoAParty(int leader, int NewMember);

// int IsPartyMember(int UserIndex, int PartyIndex);

void BroadCastParty(int UserIndex, std::string & texto);

void OnlineParty(int UserIndex);

void TransformarEnLider(int OldLeader, int NewLeader);

void ActualizaExperiencias();

void ObtenerExito(int UserIndex, int Exp, int mapa, int X, int Y);

int CantMiembros(int UserIndex);

/* '' */
/* ' Sets the new p_sumaniveleselevados to the party. */
/* ' */
/* ' @param UserInidex Specifies reference to user */
/* ' @remarks When a user level up and he is in a party, we call this sub to don't desestabilice the party exp formula */
void ActualizarSumaNivelesElevados(int UserIndex);

#endif
