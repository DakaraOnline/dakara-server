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



#include <fstream>

#include "Logs.h"
#include "Declares.h"
#include "FileIO.h"
#include "vb6compat.h"

void LogApiSock(std::string str) {
	std::ofstream f;
	f.open(GetLogFileName("sockets"), std::ios::app | std::ios::ate);
	f << vb6::Now() << " " << str << std::endl;
	f.close();
}

void LogBugReport(int UserIndex, const std::string& s) {
	std::ofstream f;
	f.open(GetLogFileName("bugs"), std::ios::app | std::ios::ate);
	f << "[" << vb6::Now() << "] Ususario: " << UserList[UserIndex].Name << std::endl;
	f << s << std::endl;
	f << std::endl;
	f.close();
}

void LogMain(const std::string& s) {
	std::ofstream f;
	f.open(GetLogFileName("main"), std::ios::app | std::ios::ate);
	f << vb6::Now() << s << std::endl;
	f.close();
}

void LogConnect(int UserIndex, bool Join) {
	std::ofstream f;
	f.open(GetLogFileName("connect"), std::ios::app | std::ios::ate);
	f << vb6::Now() << " " << UserList[UserIndex].Name << " ha " << (Join ? "entrado al" : "salido del") << " juego. NumUsers:" << NumUsers << " UserIndex:" << UserIndex << std::endl;
	f.close();
}

void LogBackUp() {
	std::ofstream out;
	out.open(GetLogFileName("BackUps"), std::ios::app | std::ios::ate);
	out << vb6::Now() << std::endl;
	out.close();
}

void LogNumUsers() {
	std::ofstream f;
	f.open(GetLogFileName("numusers"), std::ios::out | std::ios::trunc);
	f << NumUsers << std::endl;
	f.close();
}

void LogCriticEvent(std::string desc) {
	std::ofstream f;
	f.open(GetLogFileName("eventos"), std::ios::app | std::ios::ate);
	f << vb6::Now() << " " << desc << std::endl;
	f.close();
}

void LogEjercitoReal(std::string desc) {
	std::ofstream f;
	f.open(GetLogFileName("ejercito_real"), std::ios::app | std::ios::ate);
	f << vb6::Now() << " " << desc << std::endl;
	f.close();
}

void LogEjercitoCaos(std::string desc) {
	std::ofstream f;
	f.open(GetLogFileName("ejercito_caos"), std::ios::app | std::ios::ate);
	f << vb6::Now() << " " << desc << std::endl;
	f.close();
}

void LogIndex(int index, std::string desc) {
	std::ofstream f;
	f.open(GetLogFileName("index_" + vb6::CStr(index)), std::ios::app | std::ios::ate);
	f << vb6::Now() << " " << desc << std::endl;
	f.close();
}

void LogError(std::string desc) {
	std::ofstream f;
	f.open(GetLogFileName("errores"), std::ios::app | std::ios::ate);
	f << vb6::Now() << " " << desc << std::endl;
	f.close();
}

void LogStatic(std::string desc) {
	std::ofstream f;
	f.open(GetLogFileName("stats"), std::ios::app | std::ios::ate);
	f << vb6::Now() << " " << desc << std::endl;
	f.close();
}

void LogTarea(std::string desc) {
	std::ofstream f;
	f.open(GetLogFileName("haciendo"), std::ios::app | std::ios::ate);
	f << vb6::Now() << " " << desc << std::endl;
	f.close();
}

void LogClanes(std::string desc) {
	std::ofstream f;
	f.open(GetLogFileName("clanes"), std::ios::app | std::ios::ate);
	f << vb6::Now() << " " << desc << std::endl;
	f.close();
}

void LogIP(std::string str) {
	std::ofstream f;
	f.open(GetLogFileName("ip"), std::ios::app | std::ios::ate);
	f << vb6::Now() << " " << str << std::endl;
	f.close();
}

void LogDesarrollo(std::string str) {
	std::ofstream f;
	f.open(GetLogFileName("desarrollo"), std::ios::app | std::ios::ate);
	f << vb6::Now() << " " << str << std::endl;
	f.close();
}

void LogGM(std::string Nombre, std::string texto) {
	std::ofstream f;
	f.open(GetLogFileName("gm_" + vb6::UCase(Nombre)), std::ios::app | std::ios::ate);
	f << vb6::Now() << " " << texto << std::endl;
	f.close();
}

void LogAsesinato(std::string texto) {
	std::ofstream f;
	f.open(GetLogFileName("asesinatos"), std::ios::app | std::ios::ate);
	f << vb6::Now() << " " << texto << std::endl;
	f.close();
}

void logVentaCasa(std::string texto) {
	std::ofstream f;
	f.open(GetLogFileName("propiedades"), std::ios::app | std::ios::ate);
	f << vb6::Now() << " " << texto << std::endl;
	f.close();
}

void LogHackAttemp(std::string texto) {
	std::ofstream f;
	f.open(GetLogFileName("hackattempt"), std::ios::app | std::ios::ate);
	f << vb6::Now() << " " << texto << std::endl;
	f.close();
}

void LogCheating(std::string texto) {
	std::ofstream f;
	f.open(GetLogFileName("cheat"), std::ios::app | std::ios::ate);
	f << vb6::Now() << " " << texto << std::endl;
	f.close();
}

void LogCriticalHackAttemp(std::string texto) {
	std::ofstream f;
	f.open(GetLogFileName("criticalhack"), std::ios::app | std::ios::ate);
	f << vb6::Now() << " " << texto << std::endl;
	f.close();
}

void LogAntiCheat(std::string texto) {
	std::ofstream f;
	f.open(GetLogFileName("anticheat"), std::ios::app | std::ios::ate);
	f << vb6::Now() << " " << texto << std::endl;
	f.close();
}

void LogGenteBanned(std::string Nombre) {
	std::ofstream f;
	f.open(GetLogFileName("GenteBanned"), std::ios::app | std::ios::ate);
	f << Nombre << std::endl;
	f.close();
}

void LogBan(int BannedIndex, int UserIndex, std::string Motivo) {
	WriteVar(GetLogFileName("BanDetail"), UserList[BannedIndex].Name, "BannedBy",
			UserList[UserIndex].Name);
	WriteVar(GetLogFileName("BanDetail"), UserList[BannedIndex].Name, "Reason", Motivo);

	LogGenteBanned(UserList[UserIndex].Name);
}

void LogBanFromName(std::string BannedName, int UserIndex, std::string Motivo) {
	WriteVar(GetLogFileName("BanDetail"), BannedName, "BannedBy",
			UserList[UserIndex].Name);
	WriteVar(GetLogFileName("BanDetail"), BannedName, "Reason", Motivo);

	LogGenteBanned(BannedName);
}

void LogCentinela(std::string texto) {
	std::ofstream f;
	f.open(GetLogFileName("centinela"), std::ios::app | std::ios::ate);
	f << vb6::Now() << " " << texto << std::endl;
	f.close();
}
