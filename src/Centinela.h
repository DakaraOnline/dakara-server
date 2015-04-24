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

/*  AUTOMATICALLY CONVERTED FILE  */
#ifndef MODCENTINELA_H
#define MODCENTINELA_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"
/* [(0, 'ATTRIBUTE'), (1, 'VB_Name'), (5, '='), (4, '"modCentinela"')] */
/* '***************************************************************** */
/* 'modCentinela.bas - ImperiumAO - v1.2 */
/* ' */
/* 'Funciónes de control para usuarios que se encuentran trabajando */
/* ' */

/* '***************************************************************** */
/* 'Augusto Rando(barrin@imperiumao.com.ar) */
/* '   ImperiumAO 1.2 */
/* '   - First Relase */
/* ' */
/* 'Juan Martín Sotuyo Dodero (juansotuyo@gmail.com) */
/* '   Alkon AO 0.11.5 */
/* '   - Small improvements and added logs to detect possible cheaters */
/* ' */
/* 'Juan Martín Sotuyo Dodero (juansotuyo@gmail.com) */
/* '   Alkon AO 0.12.0 */
/* '   - Added several messages to spam users until they reply */
/* ' */
/* 'ZaMa */
/* '   Alkon AO 0.13.0 */
/* '   - Added several paralel checks */
/* '***************************************************************** */

/* 'Índice del NPC en el .dat */

/* 'Tiempo inicial en minutos. No reducir sin antes revisar el timer que maneja estos datos. */
/* 'Tiempo minimo fijo para volver a pasar */
/* 'Tiempo máximo para el random para que el centinela vuelva a pasar */

 struct tCentinela {
 /* ' Index of centinela en el servidor */
 int NpcIndex;
 /* '¿Qué índice revisamos? */
 int RevisandoUserIndex;
 /* '¿Cuántos minutos le quedan al usuario? */
 int TiempoRestante;
 /* 'Clave que debe escribir */
 int clave;
 int SpawnTime;
 bool Activo;
};

extern bool centinelaActivado;

/* 'Guardo cuando voy a resetear a la lista de usuarios del centinela */

extern const int NRO_CENTINELA;
extern vb6::array<struct tCentinela> Centinela;

 void CallUserAttention();
 
 void GoToNextWorkingChar();
 
 int GetIdleCentinela(int StartCheckIndex);
 
 void CentinelaFinalCheck(int CentiIndex);
 
 void CentinelaCheckClave(int UserIndex, int clave);
 
 void ResetCentinelaInfo();
 
 void CentinelaSendClave(int UserIndex, int CentinelaIndex);
 
 void PasarMinutoCentinela();
 
 void WarpCentinela(int UserIndex, int CentinelaIndex);
 
 void CentinelaUserLogout(int CentinelaIndex);
 
 void ResetCentinelas();
 
 int EsCentinela(int NpcIndex);
 
 void RenovarResetTimer();

#endif
