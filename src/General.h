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

#ifndef GENERAL_H
#define GENERAL_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

extern std::shared_ptr<clsIniManager> LeerNPCs;

void dakara_print_backtrace();

void DarCuerpoDesnudo(int UserIndex, bool Mimetizado = false);

void Bloquear(bool toMap, int sndIndex, int X, int Y, bool b);

bool HayAgua(int Map, int X, int Y);

bool HayLava(int Map, int X, int Y);

void LimpiarMundo();

void EnviarSpawnList(int UserIndex);

void Main();

void LoadConstants();

/* # IF SeguridadAlkon THEN */
/* # END IF */

void LoadArrays();

void ResetUsersConnections();

void InitMainTimers();

/* # IF SeguridadAlkon THEN */
/* # END IF */

void SocketConfig();

/* # IF UsarQueSocket = 1 THEN */

/* # ELSEIF UsarQueSocket = 0 THEN */

/* # ELSEIF UsarQueSocket = 2 THEN */

/* # ELSEIF UsarQueSocket = 3 THEN */

/* # END IF */

void LogServerStartTime();

bool FileExist(std::string File, int FileType = 0);

std::string ReadField(int Pos, std::string Text, int SepASCII);

bool MapaValido(int Map);

void MostrarNumUsers();

bool ValidInputNP(std::string cad);

void Restart();

/* # IF UsarQueSocket = 0 THEN */

/* # ELSEIF UsarQueSocket = 1 THEN */

/* # ELSEIF UsarQueSocket = 2 THEN */

/* # END IF */

/* # IF UsarQueSocket = 0 THEN */

/* # ELSEIF UsarQueSocket = 1 THEN */

/* # ELSEIF UsarQueSocket = 2 THEN */

/* # END IF */

bool Intemperie(int UserIndex);

void EfectoLluvia(int UserIndex);

void TiempoInvocacion(int UserIndex);

void EfectoFrio(int UserIndex);

void EfectoLava(int UserIndex);

/* '' */
/* ' Maneja  el efecto del estado atacable */
/* ' */
/* ' @param UserIndex  El index del usuario a ser afectado por el estado atacable */
/* ' */

void EfectoEstadoAtacable(int UserIndex);

/* '' */
/* ' Maneja el tiempo de arrivo al hogar */
/* ' */
/* ' @param UserIndex  El index del usuario a ser afectado por el /hogar */
/* ' */

void TravelingEffect(int UserIndex);

/* '' */
/* ' Maneja el tiempo y el efecto del mimetismo */
/* ' */
/* ' @param UserIndex  El index del usuario a ser afectado por el mimetismo */
/* ' */

void EfectoMimetismo(int UserIndex);

void EfectoInvisibilidad(int UserIndex);

void EfectoParalisisNpc(int NpcIndex);

void EfectoCegueEstu(int UserIndex);

void EfectoParalisisUser(int UserIndex);

void RemoveParalisis(int UserIndex);

void RecStamina(int UserIndex, bool & EnviarStats, int Intervalo);

void EfectoVeneno(int UserIndex);

void DuracionPociones(int UserIndex);

void HambreYSed(int UserIndex, bool & fenviarAyS);

void Sanar(int UserIndex, bool & EnviarStats, int Intervalo);

void CargaNpcsDat();

void PasarSegundo();

#if 0
double ReiniciarAutoUpdate();

void ReiniciarServidor(bool EjecutarLauncher = true);
#endif

void GuardarUsuarios();

void InicializaEstadisticas();

void FreeNPCs();

void FreeCharIndexes();

#endif
