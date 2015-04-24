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

#ifndef SOUNDMAPINFO_H
#define SOUNDMAPINFO_H
#include <vector>
#include <memory>
#include <string>

#include <boost/noncopyable.hpp>

#include "vb6compat.h"
#include "enums.h"

class SoundMapInfo : private boost::noncopyable {

private:
	struct p_tSoundMapInfo {
		int Cantidad;
		std::vector<int> SoundIndex;
		std::vector<int> flags;
		std::vector<float> Probabilidad;
	};

private:

private:
	std::vector<struct p_tSoundMapInfo> p_Mapas;

	/* 'sonidos conocidos, pasados a enum para intelisense */
public:

private:
	void Class_Initialize();

public:
	void LoadSoundMapInfo();

public:
	void ReproducirSonidosDeMapas();

public:
	void ReproducirSonido(SendTarget Destino, int index, int SoundIndex);

};
#endif
