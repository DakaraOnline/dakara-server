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

/*
 * Crypto.cpp
 *
 *  Created on: 28/9/2014
 *      Author: ale
 */

#include "stdafx.h"

#include "Crypto.h"

#include <random>
#include <algorithm>


namespace {

std::random_device rd;
std::mt19937 gen(rd());

}

std::string CryptoMakeRandomString(size_t len) {
	// 62 chars
	static const char* CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	std::string ret(len, ' ');
	std::uniform_int_distribution<> dis(0, 62 - 1);

	for (size_t i = 0; i < len; ++i) {
		ret[i] = CHARS[dis(gen)];
	}

	return ret;
}

std::vector<uint8_t> CryptoMakeRandomVector(size_t len) {
	std::vector<uint8_t> res;
	std::uniform_int_distribution<> dis(0, 255);

	res.resize(len, 0);

	for (size_t i = 0; i < len; ++i) {
		res[i] = dis(gen);
	}

	return res;
}


