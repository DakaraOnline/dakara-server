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

#include "MapSoundManager.h"

/* 'sonidos conocidos, pasados a enum para intelisense */

void SoundMapInfo::Class_Initialize() {
	/* 'armar el array */
	p_Mapas.resize(0);
	p_Mapas.resize(1 + NumMaps);
	LoadSoundMapInfo();
}

void SoundMapInfo::LoadSoundMapInfo() {
	int i;
	int j;
	std::string Temps;

	//MAPFILE = vb6::App().Path + MapPath + "MAPA";

	/* 'Usage of Val() prevents errors when dats are corrputed or incomplete. All invalid values are assumed to be zero. */

	/* 'TODO : Log the error in the dat for correction. */
	for (i = (1); i <= (vb6::UBound(p_Mapas)); i++) {
		std::string datfile = GetMapPath(i, MAPPATH::DAT);
		Temps = GetVar(datfile, "SONIDOS", "Cantidad");

		if (vb6::IsNumeric(Temps)) {
			p_Mapas[i].Cantidad = vb6::Constrain(vb6::CInt(Temps), 0, MAX_SONIDOS);

			p_Mapas[i].flags.resize(0);
			p_Mapas[i].flags.resize(1 + p_Mapas[i].Cantidad);
			p_Mapas[i].Probabilidad.resize(0);
			p_Mapas[i].Probabilidad.resize(1 + p_Mapas[i].Cantidad);
			p_Mapas[i].SoundIndex.resize(0);
			p_Mapas[i].SoundIndex.resize(1 + p_Mapas[i].Cantidad);

			for (j = (1); j <= (p_Mapas[i].Cantidad); j++) {
				p_Mapas[i].flags[j] = vb6::val(GetVar(datfile, "SONIDO" + std::to_string(j), "Flags"));
				p_Mapas[i].Probabilidad[j] = vb6::val(
						GetVar(datfile, "SONIDO" + vb6::CStr(j), "Probabilidad"));
				p_Mapas[i].SoundIndex[j] = vb6::val(GetVar(datfile, "SONIDO" + std::to_string(j), "Sonido"));
			}
		} else {
			p_Mapas[i].Cantidad = 0;
		}
	}
}

void SoundMapInfo::ReproducirSonidosDeMapas() {
	int i;
	int SonidoMapa;
	int posX;
	int posY;

	/* 'Sounds are played at a random position */
	posX = RandomNumber(XMinMapSize, XMaxMapSize);
	posY = RandomNumber(YMinMapSize, YMaxMapSize);

	for (i = (1); i <= (vb6::UBound(p_Mapas)); i++) {
		if (p_Mapas[i].Cantidad > 0) {
			SonidoMapa = RandomNumber(1, p_Mapas[i].Cantidad);
			if (RandomNumber(1, 100) <= p_Mapas[i].Probabilidad[SonidoMapa]) {
				/* 'tocarlo */
				if (Lloviendo) {
					if (p_Mapas[i].flags[SonidoMapa] ^ p_eSoundFlags_Lluvia) {
						SendData(SendTarget_toMap, i,
								dakara::protocol::server::BuildPlayWave(p_Mapas[i].SoundIndex[SonidoMapa], posX, posY));
					}
				} else {
					if (p_Mapas[i].flags[SonidoMapa] ^ p_eSoundFlags_ninguna) {
						SendData(SendTarget_toMap, i,
								dakara::protocol::server::BuildPlayWave(p_Mapas[i].SoundIndex[SonidoMapa], posX, posY));
					}
				}
			}
		}
	}
}

void SoundMapInfo::ReproducirSonido(SendTarget Destino, int index, int SoundIndex) {
	SendData(Destino, index,
			dakara::protocol::server::BuildPlayWave(SoundIndex, UserList[index].Pos.X, UserList[index].Pos.Y));
}
