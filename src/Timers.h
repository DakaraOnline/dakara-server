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

#ifndef TIMERS_H_
#define TIMERS_H_

extern int ESCUCHADAS;

extern const int NIM_ADD;
extern const int NIM_DELETE;
extern const int NIF_MESSAGE;
extern const int NIF_ICON;
extern const int NIF_TIP;

void TimersRegisterAll();

void CheckIdleUser();

void Auditoria_Timer();

void UpdateNpcsExp(float Multiplicador);

void AutoSave_Timer();

void FX_Timer();

void GameTimer_Timer();

void KillLog_Timer();

void npcataca_Timer();

void packetResend_Timer();

void securityTimer_Timer();

void TIMER_AI_Timer();

void tLluvia_Timer();

void tLluviaEvent_Timer();

void tPiqueteC_Timer();

#endif /* TIMERS_H_ */
