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

#ifndef CLSINIMANAGER_H
#define CLSINIMANAGER_H
#include <vector>
#include <memory>
#include <string>
#include <map>

#include <boost/noncopyable.hpp>

#include "vb6compat.h"

class clsIniManager : private boost::noncopyable {
public:
	void Initialize(std::string FileName);

	std::string GetValue(std::string Main, std::string key);

	std::string GetValue(std::string Main, std::string key, std::string default_val) {
		std::string res = GetValue(Main, key);
		return (res.length() == 0) ? default_val : res;
	}

	void ChangeValue(std::string Main, std::string key, std::string value);

	bool KeyExists(std::string Name);

	void AddKey(std::string Main, std::string key, std::string value);

	void DumpFile(std::string File, bool sync_fs = false);

private:
	std::map<std::string, std::map<std::string, std::string> > data_;
};

#endif
