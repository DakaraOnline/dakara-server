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

//============================================================================
// Name        : dakara-server.cpp
// Author      : Ale
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "stdafx.h"

#include <iostream>

#include "Declares.h"
#include "General.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include <boost/filesystem.hpp>

using namespace std;

void redimGlobalArrays() {
//	PretorianAIOffset.redim(1, 7); /* XXX */
//	PretorianDatNumbers.redim(0); /* XXX */

	ArmadurasFaccion.redim(1, NUMCLASES); /* XXX MULTIDIMENSIONAL [('1', 'NUMCLASES'), ('1', 'NUMRAZAS')] */
	for (auto& v : ArmadurasFaccion) {
		v.redim(1, NUMRAZAS);
	}

	RecompensaFacciones.redim(0, NUM_RANGOS_FACCION); /* XXX */
	ListaPeces.redim(1, NUM_PECES); /* XXX */
	ListaRazas.redim(1, NUMRAZAS); /* XXX */
	SkillsNames.redim(1, NUMSKILLS); /* XXX */
	ListaClases.redim(1, NUMCLASES); /* XXX */
	ListaAtributos.redim(1, NUMATRIBUTOS); /* XXX */
	HappyHourDays.redim(1, 7); /* XXX */
	UserList.redim(0); /* XXX */
	Npclist.redim(1, MAXNPCS); /* XXX */
	MapData.redim(0); /* XXX */
	MapInfo.redim(0); /* XXX */
	Hechizos.redim(0); /* XXX */
	CharList.redim(1, MAXCHARS); /* XXX */
	ObjData.redim(0); /* XXX */
	//FX.redim(0); /* XXX */
	SpawnList.redim(0); /* XXX */
	LevelSkill.redim(1, 50); /* XXX */
	ForbidenNames.redim(0); /* XXX */
	ArmasHerrero.redim(0); /* XXX */
	ArmadurasHerrero.redim(0); /* XXX */
	ObjCarpintero.redim(0); /* XXX */
	Parties.redim(1, MAX_PARTIES); /* XXX */
	ModClase.redim(1, NUMCLASES); /* XXX */
	ModRaza.redim(1, NUMRAZAS); /* XXX */
	ModVida.redim(1, NUMCLASES); /* XXX */
	DistribucionEnteraVida.redim(1, 5); /* XXX */
	DistribucionSemienteraVida.redim(1, 4); /* XXX */
	Ciudades.redim(1, NUMCIUDADES); /* XXX */
	distanceToCities.redim(0); /* XXX */
	Records.redim(0); /* XXX */
//	ClanPretoriano.redim(0); /* XXX */

	Centinela.redim(1, NRO_CENTINELA); /* XXX */
}

static void atexit_func() {
	cerr << "atexit called" << endl;
}

int main(int argc, char **argv) {
// std::set_terminate(handler);

#ifdef __COVERITY__ 
	try {
#endif

		/*
		 * COVERITY FIXME: Instruct coverity to ignore uncatched exceptions on main. I want then uncatched! 
		 * this way, when there is an exception the process dies and we can see the stack trace.
		 */

		cout << "Dakara Server" << endl; // prints !!!Hello World!!!

		atexit(atexit_func);

		if (argc < 2) {
			DakaraBasePath = boost::filesystem::current_path().string();
		} else {
			DakaraBasePath = argv[1];
		}
		if (DakaraBasePath.substr(DakaraBasePath.length() - 1, 1) != "/") {
			DakaraBasePath += "/";
		}

		vb6::InitializeTickCount();

		redimGlobalArrays();

		Main();

		ServerLoop();

		ServerShutdown();

#ifdef __COVERITY__ 
	} catch (const std::runtime_error& e) {
		std::cerr << "runtime_error: " << e.what() << std::endl;
		return 1;
	} catch (const std::exception& e) {
		std::cerr << "exception: " << e.what() << std::endl;
		return 1;
	} catch (...) {
		std::cerr << "UNKNOWN EXCEPTION !!!" << std::endl;
		return 1;
	}
#endif

	return 0;
}
