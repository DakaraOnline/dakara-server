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

#include "ByteBuffer.h"
#include "allheaders.h"

#include <cstring>
#include <memory>

#define BYTE_SIZE  1
/* #define BOOL_SIZE  2 */ /* FIXME: WTF 2 bytes for Bool? */
#define INTEGER_SIZE  2
#define LONG_SIZE  4
#define SINGLE_SIZE  4
#define DOUBLE_SIZE  8
#define STRING_LENGTH_SIZE  2

void clsByteBuffer::initializeReader(std::vector<std::int8_t>& v) {
	data.resize(0);
	data.swap(v);
	position = 0;
}

void clsByteBuffer::initializeWriter() {
	data.resize(0);
	data.reserve(10240);
	position = 0;
}

//void clsByteBuffer::getBytes(int & destination, int length) {
//}

int clsByteBuffer::getByte() {
	int r = *static_cast<std::int8_t*>(data.data() + position);
	position += BYTE_SIZE;
	return r;
}

//bool clsByteBuffer::getBoolean() {
//
//}

int clsByteBuffer::getInteger() {
	int r = *reinterpret_cast<std::int16_t*>(data.data() + position);
	position += INTEGER_SIZE;
	return r;
}

int clsByteBuffer::getLong() {
	int r = *reinterpret_cast<std::int32_t*>(data.data() + position);
	position += LONG_SIZE;
	return r;
}

float clsByteBuffer::getSingle() {
	float r = *reinterpret_cast<float*>(data.data() + position);
	position += SINGLE_SIZE;
	return r;
}

double clsByteBuffer::getDouble() {
	double r = *reinterpret_cast<double*>(data.data() + position);
	position += DOUBLE_SIZE;
	return r;
}

std::string clsByteBuffer::getString(int length) {
	if (length < 0) {
		length = getInteger();
		return getString(length);
	} else {
		if (length > 0) {
			std::string retval{data.data(), data.data() + length};
			position += length;
			return retval;
		}
	}

	return "";
}

void clsByteBuffer::putByte(int value) {
	data.push_back(static_cast<std::int8_t>(value & 0xff));
}

//void clsByteBuffer::putBoolean(bool value) {
//	CopyMemory(data[lastPos + 1], value, BOOL_SIZE);
//	lastPos = lastPos + BOOL_SIZE;
//}

void clsByteBuffer::putInteger(int value) {
	data.resize(data.size() + INTEGER_SIZE);
	std::uint16_t* p = reinterpret_cast<std::uint16_t*>(data.data() + data.size() - INTEGER_SIZE);
	*p = value & 0xffff;
}

void clsByteBuffer::putLong(int value) {
	data.resize(data.size() + LONG_SIZE);
	std::uint32_t* p = reinterpret_cast<std::uint32_t*>(data.data() + data.size() - LONG_SIZE);
	*p = value;
}

void clsByteBuffer::putSingle(float value) {
	data.resize(data.size() + SINGLE_SIZE);
	float* p = reinterpret_cast<float*>(data.data() + data.size() - SINGLE_SIZE);
	*p = value;
}

void clsByteBuffer::putDouble(double value) {
	data.resize(data.size() + DOUBLE_SIZE);
	double* p = reinterpret_cast<double*>(data.data() + data.size() - DOUBLE_SIZE);
	*p = value;
}

void clsByteBuffer::putString(const std::string & str, bool withLength) {
	int length;

	length = str.size();

	if (withLength) {
		putInteger(length);
		putString(str, false);
	} else {
		if (length > 0) {
			data.resize(data.size() + length);
			std::uint8_t*p = reinterpret_cast<std::uint8_t*>(data.data());
			std::memcpy(p, str.c_str(), length);
		}
	}
}

//void clsByteBuffer::getVoid(int length) {
//	CurrentPos = CurrentPos + length;
//}

//void clsByteBuffer::putVoid(int length) {
//	data.resize(data.size() + length);
//}
//
//void clsByteBuffer::clearData() {
//	data.resize(0);
//	position = 0;
//}
//
//int clsByteBuffer::getLastPos() {
//}
//
//int clsByteBuffer::getCurrentPos() {
//	int retval;
//	retval = CurrentPos;
//	return retval;
//}
//
//bool clsByteBuffer::Eof() {
//	bool retval;
//	retval = (CurrentPos > vb6::UBound(data));
//	return retval;
//}
//

std::vector<std::int8_t>& clsByteBuffer::getBuffer() {
	return data;
}

