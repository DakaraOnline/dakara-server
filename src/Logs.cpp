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

#include <fstream>

#include "Logs.h"
#include "Declares.h"
#include "FileIO.h"
#include "vb6compat.h"


void Logger::log(const std::string& file, const std::string& msg){

	auto it = logStreams.find(file);

	if ( it == logStreams.end() ){
		std::shared_ptr< std::ofstream > f(new std::ofstream);
		auto res = logStreams.insert(std::make_pair(file, f));
		it = res.first;
		(*f).open(file, std::ios::app | std::ios::ate);
		if ((*f).fail())
			throw std::runtime_error("Archivo " + file + " No se puede abrir");
	}

	std::shared_ptr< std::ofstream > & fileStream = it->second;
	(*fileStream) << msg;
}

void Logger::flush(const std::string& file){
	if ( logStreams.find( file ) == logStreams.end() )
		throw std::runtime_error("Se trato de flushear " + file + " que no fue abierto");
	(*logStreams[file]).flush();
}

void Logger::reset(const std::string& file) {
	auto it = logStreams.find(file);
	if (it != logStreams.end()) {
		auto f = it->second;
		f->close();
		f->open(file, std::ios::out | std::ios::trunc);
	}
}

// Funcion llamada en el worldsave (tambien se flushean automaticamente por ofstream si alcanza un determinado tamaño,
// podria modificarlo para ser flusheados luego de alcanzar menos tamaño si es que consume mucha memoria)
void Logger::flushAll(){
	for (std::map<std::string, std::shared_ptr< std::ofstream > >::iterator it = logStreams.begin(); it != logStreams.end(); ++it)
	  (*(it->second)).flush();
}

void Logger::closeAll(){
	for (std::map<std::string, std::shared_ptr< std::ofstream > >::iterator it = logStreams.begin(); it != logStreams.end(); ++it)
	  (*(it->second)).close();
}

void LogApiSock(std::string str) {
	std::stringstream f;
	f << vb6::Now() << " " << str << std::endl;
	Logger::getInstance().log(GetLogFileName("sockets"),f.str());
}

void LogBugReport(int UserIndex, const std::string& s) {
	std::stringstream f;
	f << "[" << vb6::Now() << "] Ususario: " << UserList[UserIndex].Name << std::endl;
	f << s << std::endl;
	f << std::endl;

	Logger::getInstance().log(GetLogFileName("bugs"),f.str());

	// errores se flushean inmediatamente
	Logger::getInstance().flush(GetLogFileName("bugs"));
}

void LogMain(const std::string& s) {
	std::stringstream f;
	f << vb6::Now() << s << std::endl;
	Logger::getInstance().log(GetLogFileName("main"),f.str());

}

void LogConnect(int UserIndex, bool Join) {
	std::stringstream f;
	f << vb6::Now() << " " << UserList[UserIndex].Name << " ha " << (Join ? "entrado al" : "salido del") << " juego. NumUsers:" << NumUsers << " UserIndex:" << UserIndex << std::endl;
	auto &L = Logger::getInstance();
	auto logFile = GetLogFileName("connect");
	L.log(logFile, f.str());
	L.flush(logFile);
}

void LogBackUp() {
	std::stringstream f;
	f << vb6::Now() << std::endl;
	Logger::getInstance().log(GetLogFileName("BackUps"),f.str());
}

void LogNumUsers() {
	std::stringstream f;
	auto &L = Logger::getInstance();
	auto logFile = GetLogFileName("numusers");
	f << vb6::Now() << " " << NumUsers << std::endl;
	L.reset(logFile);
	L.log(logFile, f.str());
	L.flush(logFile);
}

void LogCriticEvent(std::string desc) {
	std::stringstream f;
	f << vb6::Now() << " " << desc << std::endl;
	Logger::getInstance().log(GetLogFileName("eventos"),f.str());
}

void LogEjercitoReal(std::string desc) {
	std::stringstream f;
	f << vb6::Now() << " " << desc << std::endl;
	Logger::getInstance().log(GetLogFileName("ejercito_real"),f.str());
}

void LogEjercitoCaos(std::string desc) {
	std::stringstream f;
	f << vb6::Now() << " " << desc << std::endl;
	Logger::getInstance().log(GetLogFileName("ejercuto_caos"),f.str());

}

void LogIndex(int index, std::string desc) {
	std::stringstream f;
	f << vb6::Now() << " " << desc << std::endl;
	Logger::getInstance().log(GetLogFileName("index_" + vb6::CStr(index)),f.str());
}

void LogError(std::string desc) {
	std::stringstream f;
	f << vb6::Now() << " " << desc << std::endl;
	std::cerr << f.str() << std::endl;
	Logger::getInstance().log(GetLogFileName("errores"),f.str());

	// errores se flushean inmediatamente
	Logger::getInstance().flush(GetLogFileName("errores"));
}

void LogStatic(std::string desc) {
	std::stringstream f;
	f << vb6::Now() << " " << desc << std::endl;
	Logger::getInstance().log(GetLogFileName("stats"),f.str());
}

void LogTarea(std::string desc) {
	std::stringstream f;
	f << vb6::Now() << " " << desc << std::endl;
	Logger::getInstance().log(GetLogFileName("haciendo"),f.str());
}

void LogClanes(std::string desc) {
	std::stringstream f;
	f << vb6::Now() << " " << desc << std::endl;
	Logger::getInstance().log(GetLogFileName("clanes"),f.str());
}

void LogIP(std::string str) {
	std::stringstream f;
	f << vb6::Now() << " " << str << std::endl;
	Logger::getInstance().log(GetLogFileName("ip"),f.str());
}

void LogDesarrollo(std::string str) {
	std::stringstream f;
	f << vb6::Now() << " " << str << std::endl;
	Logger::getInstance().log(GetLogFileName("desarollo"),f.str());
}

void LogGM(std::string Nombre, std::string texto) {
	std::stringstream f;
	f << vb6::Now() << " " << texto << std::endl;
	Logger::getInstance().log(GetLogFileName("gm_" + vb6::UCase(Nombre)),f.str());
}

void LogAsesinato(std::string texto) {
	std::stringstream f;
	f << vb6::Now() << " " << texto << std::endl;
	Logger::getInstance().log(GetLogFileName("asesinatos"),f.str());
}

void logVentaCasa(std::string texto) {
	std::stringstream f;
	f << vb6::Now() << " " << texto << std::endl;
	Logger::getInstance().log(GetLogFileName("propiedades"),f.str());
}

void LogHackAttemp(std::string texto) {
	std::stringstream f;
	f << vb6::Now() << " " << texto << std::endl;
	Logger::getInstance().log(GetLogFileName("hackattempt"),f.str());

	// cheats se flushean inmediatamente
	Logger::getInstance().flush(GetLogFileName("hackattempt"));
}

void LogCheating(std::string texto) {
	std::stringstream f;
	f << vb6::Now() << " " << texto << std::endl;
	Logger::getInstance().log(GetLogFileName("cheat"),f.str());
	// cheats se flushean inmediatamente
	Logger::getInstance().flush(GetLogFileName("cheat"));
}

void LogCriticalHackAttemp(std::string texto) {
	std::stringstream f;
	f << vb6::Now() << " " << texto << std::endl;
	Logger::getInstance().log(GetLogFileName("criticalhack"),f.str());
	// cheats se flushean inmediatamente
	Logger::getInstance().flush(GetLogFileName("criticalhack"));
}

void LogAntiCheat(std::string texto) {
	std::stringstream f;
	f << vb6::Now() << " " << texto << std::endl;
	Logger::getInstance().log(GetLogFileName("anticheat"),f.str());
}

void LogGenteBanned(std::string Nombre) {
	std::stringstream f;
	f << Nombre << std::endl;
	Logger::getInstance().log(GetLogFileName("GenteBanned"),f.str());
	// bans se flushean inmediatamente
	Logger::getInstance().flush(GetLogFileName("GenteBanned"));
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
	std::stringstream f;
	f << vb6::Now() << " " << texto << std::endl;
	Logger::getInstance().log(GetLogFileName("centinela"),f.str());
}
