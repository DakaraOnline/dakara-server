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

/* public api for steve reid's public domain SHA-1 implementation */
/* this file is in the public domain */
/* edited for dakara-online by Alejandro Santos */

#ifndef __SHA1_H
#define __SHA1_H

#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>


typedef struct {
    uint32_t state[5];
    uint32_t count[2];
    uint8_t  buffer[64];
} SHA1_CTX;

#define SHA1_DIGEST_SIZE 20

void SHA1_Init(SHA1_CTX* context);
void SHA1_Update(SHA1_CTX* context, const uint8_t* data, const size_t len);
void SHA1_Final(SHA1_CTX* context, uint8_t digest[SHA1_DIGEST_SIZE]);

std::vector<uint8_t> SHA1_RawString(const std::string& str);
std::vector<uint8_t> SHA1_RawString(const char* data, size_t datalen);

std::string SHA1_HexString(const std::string& str);
std::string SHA1_HexString(const char* data, size_t datalen);

#endif /* __SHA1_H */
