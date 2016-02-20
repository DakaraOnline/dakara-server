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

#include "UserRecords.h"

#include <boost/date_time/posix_time/ptime.hpp>
#include <fstream>
#include <iostream>
#include <string>

#include "Declares.h"
#include "FileIO.h"
#include "General.h"
#include "IniManager.h"
#include "vb6compat.h"
#include "Logs.h"

static const int MAX_RECORDS = 100000;
static const int MAX_RECORDS_OBS = 10000;

void LoadRecords() {
	/* '************************************************************** */
	/* 'Author: Amraphen */
	/* 'Last Modify Date: 29/11/2010 */
	/* 'Carga los seguimientos de usuarios. */
	/* '************************************************************** */
	std::shared_ptr<clsIniManager> Reader;
	std::string tmpStr;
	int i;
	int j;

	Reader.reset(new clsIniManager());

	if (!FileExist(GetDatPath(DATPATH::UserRecords))) {
		CreateRecordsFile();
	}

	Reader->Initialize(GetDatPath(DATPATH::UserRecords));

	NumRecords = vb6::CInt(Reader->GetValue("INIT", "NumRecords"));
	Records.redim(0);
	if (NumRecords > 0) {
		NumRecords = vb6::Constrain(NumRecords, 0, MAX_RECORDS);
		Records.redim(1, NumRecords);
	} else {
		return;
	}

	for (i = (1); i <= (NumRecords); i++) {
		Records[i].Usuario = Reader->GetValue("RECORD" + vb6::CStr(i), "Usuario");
		Records[i].Creador = Reader->GetValue("RECORD" + vb6::CStr(i), "Creador");
		Records[i].Fecha = vb6::CDate(Reader->GetValue("RECORD" + vb6::CStr(i), "Fecha"));
		Records[i].Motivo = Reader->GetValue("RECORD" + vb6::CStr(i), "Motivo");

		Records[i].NumObs = vb6::CInt(Reader->GetValue("RECORD" + vb6::CStr(i), "NumObs"));
		Records[i].NumObs = vb6::Constrain(Records[i].NumObs, 0, MAX_RECORDS_OBS);

		if (Records[i].NumObs) {
			Records[i].Obs.redim(0);
			Records[i].Obs.redim(1, Records[i].NumObs);
		}

		for (j = (1); j <= (Records[i].NumObs); j++) {
			tmpStr = Reader->GetValue("RECORD" + vb6::CStr(i), "Obs" + vb6::CStr(j));

			Records[i].Obs[j].Creador = ReadField(1, tmpStr, 45);
			try {
				Records[i].Obs[j].Fecha = vb6::CDate(ReadField(2, tmpStr, 45));
			} catch (std::exception &e) {
				LogError("Error al leer fecha de archivo en LoadRecords() " + std::string(e.what()));
			}
			Records[i].Obs[j].Detalles = ReadField(3, tmpStr, 45);
		}
	}
}

void SaveRecords() {
	/* '************************************************************** */
	/* 'Author: Amraphen */
	/* 'Last Modify Date: 29/11/2010 */
	/* 'Guarda los seguimientos de usuarios. */
	/* '************************************************************** */
	std::shared_ptr<clsIniManager> Writer;
	std::string tmpStr;
	int i;
	int j;

	Writer.reset(new clsIniManager());

	Writer->ChangeValue("INIT", "NumRecords", vb6::CStr(NumRecords));

	for (i = (1); i <= (NumRecords); i++) {
		Writer->ChangeValue("RECORD" + vb6::CStr(i), "Usuario", Records[i].Usuario);
		Writer->ChangeValue("RECORD" + vb6::CStr(i), "Creador", Records[i].Creador);
		Writer->ChangeValue("RECORD" + vb6::CStr(i), "Fecha", vb6::dateToString(Records[i].Fecha));
		Writer->ChangeValue("RECORD" + vb6::CStr(i), "Motivo", Records[i].Motivo);

		Writer->ChangeValue("RECORD" + vb6::CStr(i), "NumObs", vb6::CStr(Records[i].NumObs));

		for (j = (1); j <= (Records[i].NumObs); j++) {
			tmpStr = Records[i].Obs[j].Creador + "-" + vb6::dateToString(Records[i].Obs[j].Fecha) + "-"
					+ Records[i].Obs[j].Detalles;
			Writer->ChangeValue("RECORD" + vb6::CStr(i), "Obs" + vb6::CStr(j), tmpStr);
		}
	}

	Writer->DumpFile(GetDatPath(DATPATH::UserRecords));
}

void AddRecord(int UserIndex, std::string Nickname, std::string Reason) {
	/* '************************************************************** */
	/* 'Author: Amraphen */
	/* 'Last Modify Date: 29/11/2010 */
	/* 'Agrega un seguimiento. */
	/* '************************************************************** */
	NumRecords = NumRecords + 1;
	Records.redim(1, NumRecords);

	Records[NumRecords].Usuario = vb6::UCase(Nickname);
	Records[NumRecords].Fecha = vb6::Now(); //vb6::Format(vb6::Now(), "DD/MM/YYYY hh:mm:ss");
	Records[NumRecords].Creador = vb6::UCase(UserList[UserIndex].Name);
	Records[NumRecords].Motivo = Reason;
	Records[NumRecords].NumObs = 0;
}

void AddObs(int UserIndex, int RecordIndex, std::string Obs) {
	/* '************************************************************** */
	/* 'Author: Amraphen */
	/* 'Last Modify Date: 29/11/2010 */
	/* 'Agrega una observación. */
	/* '************************************************************** */
	Records[RecordIndex].NumObs = Records[RecordIndex].NumObs + 1;
	Records[RecordIndex].Obs.redim(1, Records[RecordIndex].NumObs);

	Records[RecordIndex].Obs[Records[RecordIndex].NumObs].Creador = vb6::UCase(UserList[UserIndex].Name);
	Records[RecordIndex].Obs[Records[RecordIndex].NumObs].Fecha = vb6::Now();
	Records[RecordIndex].Obs[Records[RecordIndex].NumObs].Detalles = Obs;
}

void RemoveRecord(int RecordIndex) {
	/* '************************************************************** */
	/* 'Author: Amraphen */
	/* 'Last Modify Date: 29/11/2010 */
	/* 'Elimina un seguimiento. */
	/* '************************************************************** */
	int i;

	if (RecordIndex == NumRecords) {
		NumRecords = NumRecords - 1;
		if (NumRecords > 0) {
			Records.redim(1, NumRecords);
		}
	} else {
		NumRecords = NumRecords - 1;
		for (i = (RecordIndex); i <= (NumRecords); i++) {
			Records[i] = Records[i + 1];
		}

		Records.redim(1, NumRecords);
	}
}

void CreateRecordsFile() {
	/* '************************************************************** */
	/* 'Author: Amraphen */
	/* 'Last Modify Date: 29/11/2010 */
	/* 'Crea el archivo de seguimientos. */
	/* '************************************************************** */

	std::ofstream f;
	f.open(GetDatPath(DATPATH::UserRecords), std::ios::out | std::ios::trunc);

	f << "[INIT]" << std::endl;
	f << "NumRecords=0" << std::endl;

	f.close();
}
