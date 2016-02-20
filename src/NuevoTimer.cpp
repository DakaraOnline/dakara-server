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

#include "NuevoTimer.h"


/* ' */
/* ' Las siguientes funciones devuelven TRUE o FALSE si el intervalo */
/* ' permite hacerlo. Si devuelve TRUE, setean automaticamente el */
/* ' timer para que no se pueda hacer la accion hasta el nuevo ciclo. */
/* ' */

/* ' CASTING DE HECHIZOS */
bool IntervaloPermiteLanzarSpell(int UserIndex, bool Actualizar) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int TActual;

	TActual = vb6::GetTickCount();

	if (getInterval(TActual, UserList[UserIndex].Counters.TimerLanzarSpell) >= IntervaloUserPuedeCastear) {
		if (Actualizar) {
			UserList[UserIndex].Counters.TimerLanzarSpell = TActual;
		}
		retval = true;
	} else {
		retval = false;
	}

	return retval;
}

bool IntervaloPermiteAtacar(int UserIndex, bool Actualizar) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int TActual;

	TActual = vb6::GetTickCount();

	if (getInterval(TActual, UserList[UserIndex].Counters.TimerPuedeAtacar) >= IntervaloUserPuedeAtacar) {
		if (Actualizar) {
			UserList[UserIndex].Counters.TimerPuedeAtacar = TActual;
			UserList[UserIndex].Counters.TimerGolpeUsar = TActual;
		}
		retval = true;
	} else {
		retval = false;
	}
	return retval;
}

bool IntervaloPermiteGolpeUsar(int UserIndex, bool Actualizar) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Checks if the time that passed from the last hit is enough for the user to use a potion. */
	/* 'Last Modification: 06/04/2009 */
	/* '*************************************************** */

	int TActual;

	TActual = vb6::GetTickCount();

	if (getInterval(TActual, UserList[UserIndex].Counters.TimerGolpeUsar) >= IntervaloGolpeUsar) {
		if (Actualizar) {
			UserList[UserIndex].Counters.TimerGolpeUsar = TActual;
		}
		retval = true;
	} else {
		retval = false;
	}
	return retval;
}

bool IntervaloPermiteMagiaGolpe(int UserIndex, bool Actualizar) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */
	int TActual;

	if (UserList[UserIndex].Counters.TimerMagiaGolpe > UserList[UserIndex].Counters.TimerLanzarSpell) {
		return retval;
	}

	TActual = vb6::GetTickCount();

	if (getInterval(TActual, UserList[UserIndex].Counters.TimerLanzarSpell) >= IntervaloMagiaGolpe) {
		if (Actualizar) {
			UserList[UserIndex].Counters.TimerMagiaGolpe = TActual;
			UserList[UserIndex].Counters.TimerPuedeAtacar = TActual;
			UserList[UserIndex].Counters.TimerGolpeUsar = TActual;
		}
		retval = true;
	} else {
		retval = false;
	}
	return retval;
}

bool IntervaloPermiteGolpeMagia(int UserIndex, bool Actualizar) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int TActual;

	if (UserList[UserIndex].Counters.TimerGolpeMagia > UserList[UserIndex].Counters.TimerPuedeAtacar) {
		return retval;
	}

	TActual = vb6::GetTickCount();

	if (getInterval(TActual, UserList[UserIndex].Counters.TimerPuedeAtacar) >= IntervaloGolpeMagia) {
		if (Actualizar) {
			UserList[UserIndex].Counters.TimerGolpeMagia = TActual;
			UserList[UserIndex].Counters.TimerLanzarSpell = TActual;
		}
		retval = true;
	} else {
		retval = false;
	}
	return retval;
}

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
bool IntervaloPermiteTrabajar(int UserIndex, bool Actualizar) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int TActual;

	TActual = vb6::GetTickCount();

	if (getInterval(TActual, UserList[UserIndex].Counters.TimerPuedeTrabajar) >= IntervaloUserPuedeTrabajar) {
		if (Actualizar) {
			UserList[UserIndex].Counters.TimerPuedeTrabajar = TActual;
		}
		retval = true;
	} else {
		retval = false;
	}
	return retval;
}

/* ' USAR OBJETOS */
bool IntervaloPermiteUsar(int UserIndex, bool Actualizar) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 25/01/2010 (ZaMa) */
	/* '25/01/2010: ZaMa - General adjustments. */
	/* '*************************************************** */

	int TActual;

	TActual = vb6::GetTickCount();

	if (getInterval(TActual, UserList[UserIndex].Counters.TimerUsar) >= IntervaloUserPuedeUsar) {
		if (Actualizar) {
			UserList[UserIndex].Counters.TimerUsar = TActual;
			/* 'UserList(UserIndex).Counters.failedUsageAttempts = 0 */
		}
		retval = true;
	} else {
		retval = false;

		/* 'UserList(UserIndex).Counters.failedUsageAttempts = UserList(UserIndex).Counters.failedUsageAttempts + 1 */

		/* 'Tolerancia arbitraria - 20 es MUY alta, la está chiteando zarpado */
		/* 'If UserList(UserIndex).Counters.failedUsageAttempts = 20 Then */
		/* 'Call SendData(SendTarget.ToAdmins, 0, PrepareMessageConsoleMsg(UserList(UserIndex).name & " kicked by the server por posible modificación de intervalos.", FontTypeNames.FONTTYPE_FIGHT)) */
		/* 'Call CloseSocket(UserIndex) */
		/* 'End If */
	}

	return retval;
}

bool IntervaloPermiteUsarArcos(int UserIndex, bool Actualizar) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int TActual;

	TActual = vb6::GetTickCount();

	if (getInterval(TActual, UserList[UserIndex].Counters.TimerPuedeUsarArco) >= IntervaloFlechasCazadores) {
		if (Actualizar) {
			UserList[UserIndex].Counters.TimerPuedeUsarArco = TActual;
		}
		retval = true;
	} else {
		retval = false;
	}

	return retval;
}

bool IntervaloPermiteSerAtacado(int UserIndex, bool Actualizar) {
	bool retval;
	/* '************************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modify by: ZaMa */
	/* 'Last Modify Date: 13/11/2009 */
	/* '13/11/2009: ZaMa - Add the Timer which determines wether the user can be atacked by a NPc or not */
	/* '************************************************************** */
	int TActual;

	TActual = vb6::GetTickCount();

	/* ' Inicializa el timer */
	if (Actualizar) {
		UserList[UserIndex].Counters.TimerPuedeSerAtacado = TActual;
		UserList[UserIndex].flags.NoPuedeSerAtacado = true;
		retval = false;
	} else {
		if (getInterval(TActual, UserList[UserIndex].Counters.TimerPuedeSerAtacado)
				>= IntervaloPuedeSerAtacado) {
			UserList[UserIndex].flags.NoPuedeSerAtacado = false;
			retval = true;
		} else {
			retval = false;
		}
	}

	return retval;
}

bool IntervaloPerdioNpc(int UserIndex, bool Actualizar) {
	bool retval;
	/* '************************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modify by: ZaMa */
	/* 'Last Modify Date: 13/11/2009 */
	/* '13/11/2009: ZaMa - Add the Timer which determines wether the user still owns a Npc or not */
	/* '************************************************************** */
	int TActual;

	TActual = vb6::GetTickCount();

	/* ' Inicializa el timer */
	if (Actualizar) {
		UserList[UserIndex].Counters.TimerPerteneceNpc = TActual;
		retval = false;
	} else {
		if (getInterval(TActual, UserList[UserIndex].Counters.TimerPerteneceNpc) >= IntervaloOwnedNpc) {
			retval = true;
		} else {
			retval = false;
		}
	}

	return retval;
}

bool IntervaloEstadoAtacable(int UserIndex, bool Actualizar) {
	bool retval;
	/* '************************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modify by: ZaMa */
	/* 'Last Modify Date: 13/01/2010 */
	/* '13/01/2010: ZaMa - Add the Timer which determines wether the user can be atacked by an user or not */
	/* '************************************************************** */
	int TActual;

	TActual = vb6::GetTickCount();

	/* ' Inicializa el timer */
	if (Actualizar) {
		UserList[UserIndex].Counters.TimerEstadoAtacable = TActual;
		retval = true;
	} else {
		if (getInterval(TActual, UserList[UserIndex].Counters.TimerEstadoAtacable) >= IntervaloAtacable) {
			retval = false;
		} else {
			retval = true;
		}
	}

	return retval;
}

bool IntervaloGoHome(int UserIndex, int TimeInterval, bool Actualizar) {
	bool retval = false;
	/* '************************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modify by: ZaMa */
	/* 'Last Modify Date: 01/06/2010 */
	/* '01/06/2010: ZaMa - Add the Timer which determines wether the user can be teleported to its home or not */
	/* '************************************************************** */
	int TActual;

	TActual = vb6::GetTickCount();

	/* ' Inicializa el timer */
	if (Actualizar) {
		UserList[UserIndex].flags.Traveling = 1;
		UserList[UserIndex].Counters.goHome = TActual + TimeInterval;
	} else {
		if (TActual >= UserList[UserIndex].Counters.goHome) {
			retval = true;
		}
	}

	return retval;
}

bool checkInterval(int & startTime, int timeNow, int interval) {
	bool retval;
	int lInterval;

	if (timeNow < startTime) {
		lInterval = 0x7FFFFFFF - startTime + timeNow + 1;
	} else {
		lInterval = timeNow - startTime;
	}

	if (lInterval >= interval) {
		startTime = timeNow;
		retval = true;
	} else {
		retval = false;
	}
	return retval;
}

int getInterval(int timeNow, int startTime) {
	int retval;
	if (timeNow < startTime) {
		retval = 0x7FFFFFFF - startTime + timeNow + 1;
	} else {
		retval = timeNow - startTime;
	}
	return retval;
}
