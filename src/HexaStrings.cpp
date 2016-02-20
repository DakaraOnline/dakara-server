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

#include "HexaStrings.h"

/* 'Modulo realizado por Gonzalo Larralde(CDT) <gonzalolarralde@yahoo.com.ar> */
/* 'Para la conversion a caracteres de cadenas MD5 y de */
/* 'semi encriptación de cadenas por ascii table offset */

std::string hexMd52Asc(std::string MD5) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int i;
	std::string L;

	if (vb6::Len(MD5) & 0x1) {
		MD5 = "0" + MD5;
	}

	for (i = (1); i <= (int)(vb6::Len(MD5) / 2); i++) {
		L = vb6::Mid(MD5, (2 * i) - 1, 2);
		retval = retval + vb6::Chr(hexHex2Dec(L));
	}
	return retval;
}

int hexHex2Dec(std::string hex) {
	return std::stoul("0x" + hex, nullptr, 16);
}

std::string txtOffset(std::string Text, int off) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int i;
	std::string L;

	for (i = (1); i <= (int)(vb6::Len(Text)); i++) {
		L = vb6::Mid(Text, i, 1);
		retval = retval + vb6::Chr((vb6::Asc(L) + off) & 0xFF);
	}
	return retval;
}
