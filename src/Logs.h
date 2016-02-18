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



#ifndef LOGS_H_
#define LOGS_H_

#include <iostream> // sacar
#include <map>
#include <string>
#include <utility>
#include <fstream>
#include <memory>

class Logger {
public:
	Logger() {}

	~Logger() {
		this->closeAll();
	}

	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	static Logger& getInstance() {
		static Logger instance;
		return instance;
	}

	void log(const std::string& file, const std::string& msg);
	void flush(const std::string& file);
	void reset(const std::string& file);
	void flushAll();

private:
	std::map<std::string,std::shared_ptr< std::ofstream > >logStreams;
	void closeAll();
};



void LogApiSock(std::string str);

void LogBugReport(int UserIndex, const std::string& s);

void LogMain(const std::string& s);

void LogConnect(int UserIndex, bool Join);

void LogBackUp();

void LogNumUsers();

void LogCriticEvent(std::string desc);

void LogEjercitoReal(std::string desc);

void LogEjercitoCaos(std::string desc);

void LogIndex(int index, std::string desc);

void LogError(std::string desc);

void LogStatic(std::string desc);

void LogTarea(std::string desc);

void LogClanes(std::string str);

void LogIP(std::string str);

void LogDesarrollo(std::string str);

void LogGM(std::string Nombre, std::string texto);

void LogAsesinato(std::string texto);

void logVentaCasa(std::string texto);

void LogHackAttemp(std::string texto);

void LogCheating(std::string texto);

void LogCriticalHackAttemp(std::string texto);

void LogAntiCheat(std::string texto);

void LogBan(int BannedIndex, int UserIndex, std::string Motivo);

void LogBanFromName(std::string BannedName, int UserIndex, std::string Motivo);

void LogGenteBanned(std::string BannedName);

void LogCentinela(std::string texto);

#endif /* LOGS_H_ */
