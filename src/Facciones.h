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

#ifndef MODFACCIONES_H
#define MODFACCIONES_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

extern int ArmaduraImperial1;
extern int ArmaduraImperial2;
extern int ArmaduraImperial3;
extern int TunicaMagoImperial;
extern int TunicaMagoImperialEnanos;
extern int ArmaduraCaos1;
extern int ArmaduraCaos2;
extern int ArmaduraCaos3;
extern int TunicaMagoCaos;
extern int TunicaMagoCaosEnanos;

extern int VestimentaImperialHumano;
extern int VestimentaImperialEnano;
extern int TunicaConspicuaHumano;
extern int TunicaConspicuaEnano;
extern int ArmaduraNobilisimaHumano;
extern int ArmaduraNobilisimaEnano;
extern int ArmaduraGranSacerdote;

extern int VestimentaLegionHumano;
extern int VestimentaLegionEnano;
extern int TunicaLobregaHumano;
extern int TunicaLobregaEnano;
extern int TunicaEgregiaHumano;
extern int TunicaEgregiaEnano;
extern int SacerdoteDemoniaco;

extern const int NUM_RANGOS_FACCION;
extern const int NUM_DEF_FACCION_ARMOURS;

struct tFaccionArmaduras {
	tFaccionArmaduras() {
		Armada.redim(NUM_DEF_FACCION_ARMOURS);
		Caos.redim(NUM_DEF_FACCION_ARMOURS);
	}

	vb6::array<int> Armada;
	vb6::array<int> Caos;
};

/* ' Matriz que contiene las armaduras faccionarias segun raza, clase, faccion y defensa de armadura */
extern vb6::array<vb6::array<struct tFaccionArmaduras> > ArmadurasFaccion;

/* ' Contiene la cantidad de exp otorgada cada vez que aumenta el rango */
extern vb6::array<int> RecompensaFacciones;

int GetArmourAmount(int Rango, eTipoDefArmors TipoDef);

void GiveFactionArmours(int UserIndex, bool IsCaos);

void GiveExpReward(int UserIndex, int Rango);

void EnlistarArmadaReal(int UserIndex);

void RecompensaArmadaReal(int UserIndex);

void ExpulsarFaccionReal(int UserIndex, bool Expulsado = true);

void ExpulsarFaccionCaos(int UserIndex, bool Expulsado = true);

std::string TituloReal(int UserIndex);

void EnlistarCaos(int UserIndex);

void RecompensaCaos(int UserIndex);

std::string TituloCaos(int UserIndex);

#endif
