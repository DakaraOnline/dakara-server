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

#ifndef MODNUEVOTIMER_H
#define MODNUEVOTIMER_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

/* ' */
/* ' Las siguientes funciones devuelven TRUE o FALSE si el intervalo */
/* ' permite hacerlo. Si devuelve TRUE, setean automaticamente el */
/* ' timer para que no se pueda hacer la accion hasta el nuevo ciclo. */
/* ' */

/* ' CASTING DE HECHIZOS */
bool IntervaloPermiteLanzarSpell(int UserIndex, bool Actualizar = true);

bool IntervaloPermiteAtacar(int UserIndex, bool Actualizar = true);

bool IntervaloPermiteGolpeUsar(int UserIndex, bool Actualizar = true);

bool IntervaloPermiteMagiaGolpe(int UserIndex, bool Actualizar = true);

bool IntervaloPermiteGolpeMagia(int UserIndex, bool Actualizar = true);

/* ' ATAQUE CUERPO A CUERPO */
/* 'Public Function IntervaloPermiteAtacar(ByVal UserIndex As Integer, Optional ByVal Actualizar As Boolean = True) As Boolean */
/* 'Dim TActual As Long */
/* ' */
/* 'TActual = GetTickCount() And &H7FFFFFFF'' */
/* ' */
/* 'If TActual - UserList(UserIndex).Counters.TimerPuedeAtacar >= IntervaloUserPuedeAtacar Then */
/* '    If Actualizar Then UserList(UserIndex).Counters.TimerPuedeAtacar = TActual */
/* '    IntervaloPermiteAtacar = True */
/* 'Else */
/* '    IntervaloPermiteAtacar = False */
/* 'End If */
/* 'End Function */

/* ' TRABAJO */
bool IntervaloPermiteTrabajar(int UserIndex, bool Actualizar = true);

/* ' USAR OBJETOS */
bool IntervaloPermiteUsar(int UserIndex, bool Actualizar = true);

bool IntervaloPermiteUsarArcos(int UserIndex, bool Actualizar = true);

bool IntervaloPermiteSerAtacado(int UserIndex, bool Actualizar = false);

bool IntervaloPerdioNpc(int UserIndex, bool Actualizar = false);

bool IntervaloEstadoAtacable(int UserIndex, bool Actualizar = false);

bool IntervaloGoHome(int UserIndex, int TimeInterval = int(), bool Actualizar = false);

bool checkInterval(int & startTime, int timeNow, int interval);

int getInterval(int timeNow, int startTime);

#endif
