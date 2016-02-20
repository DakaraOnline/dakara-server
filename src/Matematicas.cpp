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

#include "Matematicas.h"

int Porcentaje(int Total, int Porc) {
	int retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	retval = (Total * Porc) / 100;
	return retval;
}

int Distancia(struct WorldPos & wp1, struct WorldPos & wp2) {
	int retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	/* 'Encuentra la distancia entre dos WorldPos */
	retval = vb6::Abs(wp1.X - wp2.X) + vb6::Abs(wp1.Y - wp2.Y) + (vb6::Abs(wp1.Map - wp2.Map) * 100);
	return retval;
}

double Distance(int X1, int Y1, int X2, int Y2) {
	double retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	/* 'Encuentra la distancia entre dos puntos */

	retval = vb6::Sqr(((Y1 - Y2) * (Y1 - Y2) + (X1 - X2) * (X1 - X2)));

	return retval;
}

int RandomNumber(int LowerBound, int UpperBound) {
	int retval;
	/* '************************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero */
	/* 'Last Modify Date: 3/06/2006 */
	/* 'Generates a random number in the range given - recoded to use longs and work properly with ranges */
	/* '************************************************************** */
	retval = vb6::Fix(vb6::Rnd() * (UpperBound - LowerBound + 1)) + LowerBound;
	return retval;
}
