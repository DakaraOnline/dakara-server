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

#ifndef CONSULTASPOPULARES_H
#define CONSULTASPOPULARES_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

class ConsultasPopulares {
private:
	int pEncuestaActualNum;
	std::string pEncuestaActualTex;
	int pNivelRequerido;
	std::vector<std::string> pOpciones;
	void MarcarPjComoQueYaVoto(int UserIndex);
	bool MailYaVoto(std::string email);
	void MarcarMailComoQueYaVoto(std::string email);
	bool OpcionValida(int opcion);

public:
	ConsultasPopulares();
	void Numero(int NumEncuesta);
	int Numero();
	void texto(std::string Descripcion);
	std::string texto();
	void LoadData();
	std::string doVotar(int UserIndex, int opcion);
	std::string SendInfoEncuesta(int UserIndex);

};
#endif
