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

#include "ConsultasPopulares.h"

#include <fstream>

static const int MAX_ENCUESTAS_OPCIONES = 1000;

ConsultasPopulares :: ConsultasPopulares() {
	pEncuestaActualNum=0;
	pNivelRequerido=0;
}

void ConsultasPopulares::Numero(int NumEncuesta) {
	pEncuestaActualNum = NumEncuesta;
}

int ConsultasPopulares::Numero() {
	int retval;
	retval = pEncuestaActualNum;
	return retval;
}

void ConsultasPopulares::texto(std::string Descripcion) {
	pEncuestaActualTex = Descripcion;
}

std::string ConsultasPopulares::texto() {
	std::string retval;
	retval = pEncuestaActualTex;
	return retval;
}

void ConsultasPopulares::LoadData() {
	int CantOpciones;
	int i;

	pEncuestaActualNum = vb6::val(GetVar(GetDatPath(DATPATH::Consultas), "INIT", "ConsultaActual"));
	pEncuestaActualTex = GetVar(GetDatPath(DATPATH::Consultas), "INIT", "ConsultaActualTexto");
	pNivelRequerido = vb6::val(GetVar(GetDatPath(DATPATH::Consultas), "INIT", "NivelRequerido"));

	if (pEncuestaActualNum > 0) {
		/* 'cargo todas las opciones */
		CantOpciones = vb6::CInt(
				GetVar(GetDatPath(DATPATH::Consultas), "ENCUESTA" + vb6::CStr(pEncuestaActualNum), "CANTOPCIONES"));
		CantOpciones = vb6::Constrain(CantOpciones, 0, MAX_ENCUESTAS_OPCIONES);
		pOpciones.resize(0);
		pOpciones.resize(1 + CantOpciones);
		for (i = (1); i <= (CantOpciones); i++) {
			pOpciones[i] = GetVar(GetDatPath(DATPATH::Consultas), "ENCUESTA" + vb6::CStr(pEncuestaActualNum),
					"OPCION" + vb6::CStr(i));
		}
	}
}

std::string ConsultasPopulares::doVotar(int UserIndex, int opcion) {
	std::string retval;

	bool YaVoto;
	std::string CharFile;
	int sufragio;

	/* 'revisar q no haya votado */
	/* 'grabar en el charfile el numero de encuesta */
	/* 'actualizar resultados encuesta */
	if (pEncuestaActualNum == 0) {
		retval = "No hay consultas populares abiertas";
		return retval;
	}

	CharFile = GetCharPath(UserList[UserIndex].Name);

	if ((UserList[UserIndex].Stats.ELV >= pNivelRequerido)) {
		if ((OpcionValida(opcion))) {
			YaVoto = vb6::val(GetVar(CharFile, "CONSULTAS", "Voto")) >= pEncuestaActualNum;
			if (!YaVoto) {
				if (!MailYaVoto(UserList[UserIndex].email)) {
					/* 'pj apto para votar */
					sufragio = vb6::CLng(
							vb6::val(
									GetVar(GetDatPath(DATPATH::Consultas), "RESULTADOS" + vb6::CStr(pEncuestaActualNum),
											"V" + vb6::CStr(opcion))));
					sufragio = sufragio + 1;
					WriteVar(GetDatPath(DATPATH::Consultas), "RESULTADOS" + vb6::CStr(pEncuestaActualNum), "V" + vb6::CStr(opcion),
							vb6::str(sufragio));
					retval = "Tu voto ha sido computado. Opcion: " + vb6::CStr(opcion);
					MarcarPjComoQueYaVoto(UserIndex);
					MarcarMailComoQueYaVoto(UserList[UserIndex].email);
				} else {
					MarcarPjComoQueYaVoto(UserIndex);
					retval = "Este email ya voto en la consulta: " + vb6::CStr(pEncuestaActualTex);
				}
			} else {
				retval = "Este personaje ya voto en la consulta: " + vb6::CStr(pEncuestaActualTex);
			}
		} else {
			retval = "Esa no es una opcion para votar";
		}
	} else {
		retval = "Para votar en esta consulta debes ser nivel " + vb6::CStr(pNivelRequerido) + " o superior";
	}

	return retval;
}

std::string ConsultasPopulares::SendInfoEncuesta(int UserIndex) {
	std::string retval;
	int i;
	WriteConsoleMsg(UserIndex, "CONSULTA POPULAR NUMERO " + vb6::CStr(pEncuestaActualNum), FontTypeNames_FONTTYPE_GUILD);
	WriteConsoleMsg(UserIndex, pEncuestaActualTex, FontTypeNames_FONTTYPE_GUILD);
	WriteConsoleMsg(UserIndex, " Opciones de voto: ", FontTypeNames_FONTTYPE_GUILDMSG);
	for (i = (1); i <= (vb6::UBound(pOpciones)); i++) {
		WriteConsoleMsg(UserIndex,
				"(Opcion " + vb6::CStr(i) + "): "
						+ GetVar(GetDatPath(DATPATH::Consultas), "ENCUESTA" + vb6::CStr(pEncuestaActualNum),
								"OPCION" + vb6::CStr(i)), FontTypeNames_FONTTYPE_GUILDMSG);
	}
	WriteConsoleMsg(UserIndex,
			" Para votar una opcion, escribe /encuesta NUMERODEOPCION, por ejemplo para votar la opcion 1, escribe /encuesta 1. Tu voto no podra ser cambiado.",
			FontTypeNames_FONTTYPE_VENENO);
	return retval;
}

void ConsultasPopulares::MarcarPjComoQueYaVoto(int UserIndex) {
	WriteVar(GetCharPath(UserList[UserIndex].Name), "CONSULTAS", "Voto", vb6::str(pEncuestaActualNum));
}

bool ConsultasPopulares::MailYaVoto(std::string email) {
	bool retval;
	/* 'abro el archivo, while not eof levnato 1 linea y comparo. Si da true, cierro */
	std::string Tmp;

	retval = false;

	/* ' Si no existe no voto. */
	if (!FileExist(GetLogFileName("votaron"))) {
		return retval;
	}

	std::ifstream fin;
	fin.open(GetLogFileName("votaron"));

	while (std::getline(fin, Tmp)) {
		if (email == Tmp) {
			return true;
		}
	}

	return retval;
}

void ConsultasPopulares::MarcarMailComoQueYaVoto(std::string email) {
	std::ofstream out;
	out.open(GetLogFileName("votaron"), std::ios::out | std::ios::app);
	out << email << std::endl;
	out.close();
}

bool ConsultasPopulares::OpcionValida(int opcion) {
	bool retval;
	retval = opcion > 0 && opcion <= vb6::UBound(pOpciones);
	return retval;
}
