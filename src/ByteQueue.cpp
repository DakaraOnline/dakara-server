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

#include "ByteQueue.h"

#define BOOST_NO_CXX11_SCOPED_ENUMS
#define BOOST_NO_SCOPED_ENUMS

#include <boost/locale.hpp>

clsByteQueue::clsByteQueue() : readPos(0) {

}

void clsByteQueue::commitRead(int pos) {
	data.erase(data.begin(), data.begin() + pos);
	readPos -= pos;
}

void clsByteQueue::revertRead(int oldPos) {
	readPos = oldPos;
}

//void clsByteQueue::CopyBuffer(std::shared_ptr<clsByteQueue> & source) {
//	throw std::runtime_error("not implemented: CopyBuffer");
//}
//
//void clsByteQueue::WriteData(std::vector<int> & buf, int dataLength) {
//	throw std::runtime_error("not implemented: WriteData");
//}
//
//void clsByteQueue::ReadData(std::vector<int> & buf, int dataLength) {
//
//}
//
//void clsByteQueue::RemoveData(int dataLength) {
//
//}

void clsByteQueue::WriteByte(std::uint8_t value) {
	data.push_back(static_cast<std::uint8_t>(0xff & value));
}

void clsByteQueue::WriteInteger(std::int16_t value) {
	union {
		std::int16_t a;
		std::int8_t b[8];
	} w;
	w.a = value;
	data.insert(data.end(), w.b, w.b + sizeof(w.a));
}

void clsByteQueue::WriteLong(std::int32_t value) {
	union {
		std::int32_t a;
		std::int8_t b[8];
	} w;
	w.a = value;
	data.insert(data.end(), w.b, w.b + sizeof(w.a));
}

void clsByteQueue::WriteSingle(float value) {
	union {
		float a;
		std::int8_t b[8];
	} w;
	w.a = value;
	data.insert(data.end(), w.b, w.b + sizeof(w.a));
}

void clsByteQueue::WriteDouble(double value) {
	union {
		double a;
		std::int8_t b[8];
	} w;
	w.a = value;
	data.insert(data.end(), w.b, w.b + sizeof(w.a));
}

void clsByteQueue::WriteBoolean(bool value) {
	data.push_back(value ? 1 : 0);
}

void clsByteQueue::WriteUnicodeStringFixed(const std::string& value) {
	WriteBinaryFixed(boost::locale::conv::from_utf<char>(value, CLSBYTEQUEUE_CLIENT_ENCODING));
}

void clsByteQueue::WriteUnicodeString(const std::string& value) {
	WriteBinary(boost::locale::conv::from_utf<char>(value, CLSBYTEQUEUE_CLIENT_ENCODING));
}

void clsByteQueue::WriteBinary(const std::string& value) {
	WriteInteger(value.size());
	WriteBinaryFixed(value);
}

void clsByteQueue::WriteBlock(const char* buf, int n) {
	data.insert(data.end(), buf, buf + n);
}

std::string clsByteQueue::ReadBinaryFixed(int length) {
	std::string tmp = PeekBinaryFixed(length);
	readPos += tmp.size();
	return tmp;
}

std::string clsByteQueue::ReadUnicodeStringFixed(int length) {
	return boost::locale::conv::to_utf<char>(ReadBinaryFixed(length), CLSBYTEQUEUE_CLIENT_ENCODING);
}

std::string clsByteQueue::ReadBinary() {
	std::string tmp = PeekBinary();
	readPos += tmp.size() + 2;
	return tmp;
}

std::string clsByteQueue::ReadUnicodeString() {
	return boost::locale::conv::to_utf<char>(ReadBinary(), CLSBYTEQUEUE_CLIENT_ENCODING);
}

//void clsByteQueue::ReadBlock(std::vector<int> & block, int dataLength) {
//
//}

std::string clsByteQueue::PeekBinaryFixed(std::size_t length) {
	if (length > BQ_MAX_STRING_SIZE)
		throw bytequeue_data_error("length > BQ_MAX_STRING_SIZE");
	if (readPos + length > data.size())
		throw insufficient_data_error();
	const char* p = reinterpret_cast<const char*>(data.data() + readPos);
	return std::string(p, p + length);
}

std::string clsByteQueue::PeekUnicodeStringFixed(int length) {
	return boost::locale::conv::to_utf<char>(PeekBinaryFixed(length), CLSBYTEQUEUE_CLIENT_ENCODING);
}

std::string clsByteQueue::PeekBinary() {
	std::size_t length = PeekInteger();
	if (length > BQ_MAX_STRING_SIZE)
		throw bytequeue_data_error("length > BQ_MAX_STRING_SIZE");
	if (readPos + length + 2 > data.size())
		throw insufficient_data_error();
	const char* p = reinterpret_cast<const char*>(data.data() + readPos);
	return std::string(p + 2, p + 2 + length);
}

std::string clsByteQueue::PeekUnicodeString() {
	return boost::locale::conv::to_utf<char>(PeekBinary(), CLSBYTEQUEUE_CLIENT_ENCODING);
}

//int clsByteQueue::PeekBlock(std::vector<int> & block, int dataLength) {
//
//}
//
//int clsByteQueue::Capacity() {
//
//}
//
//void clsByteQueue::Capacity(int value) {
//
//}

int clsByteQueue::length() {
	return data.size() - readPos;
}

