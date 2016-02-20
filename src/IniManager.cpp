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

#include "IniManager.h"

#include <fstream>
#include <boost/algorithm/string.hpp>

#ifndef _WIN32
#include <unistd.h>
#endif


void clsIniManager::Initialize(std::string FileName) {
	std::ifstream inf;

	inf.open(FileName);
	std::string line, section;

	if (!inf) {
		throw std::runtime_error("File does not exist: " + FileName);
	}

	// std::cerr << "Opening file " << FileName << std::endl;

	while (std::getline(inf, line)) {
		boost::algorithm::trim_right(line);
		if (line.size() < 1)
			continue;
        if (line[0] == '\'' || line[0] == '#')
            continue;
		if (line[0] == '[') {
			size_t pos = line.find(']');
			if (pos != std::string::npos) {
				section = line.substr(1, pos - 1);
				boost::to_upper(section);
			}
		} else {
			size_t eqpos = line.find('=');
			if (eqpos != std::string::npos) {
				std::string key = line.substr(0, eqpos);
				boost::to_upper(key);
				data_[section][key] = line.substr(eqpos + 1);
			}
		}
	}

	inf.close();
}

std::string clsIniManager::GetValue(std::string Main, std::string key) {
	boost::to_upper(Main);
	boost::to_upper(key);
	auto it1 = data_.find(Main);
	if (it1 != data_.end()) {
		auto it2 = it1->second.find(key);
		if (it2 != it1->second.end()) {
			return it2->second;
		} else {
			//std::cerr << "Unknown Main: " << Main << " Key: " << key << std::endl;
		}
	} else {
		//std::cerr << "Unknown Main: " << Main << std::endl;
	}
	return "";
}

void clsIniManager::ChangeValue(std::string Main, std::string key, std::string value) {
	boost::to_upper(Main);
	boost::to_upper(key);
	data_[Main][key] = value;
}

bool clsIniManager::KeyExists(std::string Name) {
	boost::to_upper(Name);
	auto it1 = data_.find(Name);
	if (it1 != data_.end()) {
		return true;
	}
	return false;
}

void clsIniManager::AddKey(std::string Main, std::string key, std::string value) {
	ChangeValue(Main, key, value);
}

void clsIniManager::DumpFile(std::string File, bool sync_fs) {
	//FIXME
	//throw std::runtime_error("DumpFile not implemented, file: " + File);
#if 0
	std::ofstream f;
	f.open(File, std::ios::out | std::ios::trunc);

	for (auto& a : data_) {
		f << "[" << a.first << "]" << std::endl;

		for (auto& b : a.second) {
			f << b.first << "=" << b.second << std::endl;
		}

		f << std::endl;
	}

	f.close();
#else
	FILE* fd = fopen(File.c_str(), "w");

	try {
		for (auto& a : data_) {
			fprintf(fd, "[%s]\n", a.first.c_str());

			for (auto& b : a.second) {
				fprintf(fd, "%s=%s\n", b.first.c_str(), b.second.c_str());
			}

			fprintf(fd, "\n");
		}
	} catch (...) {

	}

	if (fd) {
		if (sync_fs) {
#ifndef _WIN32
			int n = fileno(fd);
			fsync(n);
#endif
		}

		fclose(fd);
	}
#endif
}
