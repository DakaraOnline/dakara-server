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

#ifndef CLSBYTEBUFFER_H
#define CLSBYTEBUFFER_H
#include <vector>
#include <memory>
#include <string>
#include <cstdint>
#include "vb6compat.h"
#include "enums.h"

class clsByteBuffer {

private:
	std::vector<std::int8_t> data;
	std::size_t position{};

public:
	void initializeReader(std::vector<std::int8_t>& v);

public:
	void initializeWriter();

//public:
//	void getBytes(int & destination, int length = -1);

public:
	int getByte();

//public:
//	bool getBoolean();

public:
	int getInteger();

public:
	int getLong();

public:
	float getSingle();

public:
	double getDouble();

public:
	std::string getString(int length = -1);

public:
	void putByte(int value);

//public:
//	void putBoolean(bool value);

public:
	void putInteger(int value);

public:
	void putLong(int value);

public:
	void putSingle(float value);

public:
	void putDouble(double value);

public:
	void putString(const std::string & str, bool withLength = true);

//public:
//	void getVoid(int length);
//
//public:
//	void putVoid(int length);

//public:
//	void clearData();
//
//public:
//	int getLastPos();
//
//public:
//	int getCurrentPos();
//
//public:
//	bool Eof();

public:
	std::vector<std::int8_t>& getBuffer();

};
#endif
