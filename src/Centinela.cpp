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

#include "Centinela.h"

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
static const int NPC_CENTINELA = 16;

/* 'Tiempo inicial en minutos. No reducir sin antes revisar el timer que maneja estos datos. */
static const int TIEMPO_INICIAL = 2;
/* 'Tiempo minimo fijo para volver a pasar */
static const int TIEMPO_PASAR_BASE = 20;
/* 'Tiempo máximo para el random para que el centinela vuelva a pasar */
static const int TIEMPO_PASAR_RANDOM = 10;

bool centinelaActivado;

/* 'Guardo cuando voy a resetear a la lista de usuarios del centinela */
static int centinelaStartTime;
static int centinelaInterval;

static bool DetenerAsignacion;

const int NRO_CENTINELA = 5;
vb6::array<struct tCentinela> Centinela;

void CallUserAttention() {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 03/10/2010 */
	/* 'Makes noise and FX to call the user's attention. */
	/* '03/10/2010: ZaMa - Adaptado para que funcione mas de un centinela en paralelo. */
	/* '************************************************* */

	/* 'Esta el sistema habilitado? */
	if (!centinelaActivado) {
		return;
	}

	int index;
	int UserIndex;

	int TActual;
	TActual = (vb6::GetTickCount());

	/* ' Chequea todos los centinelas */
	for (index = (1); index <= (NRO_CENTINELA); index++) {

		/* ' Centinela activo? */
		if (Centinela[index].Activo) {

			UserIndex = Centinela[index].RevisandoUserIndex;

			/* ' Esta revisando un usuario? */
			if (UserIndex != 0) {

				if (getInterval(TActual, Centinela[index].SpawnTime) >= 5000) {

					if (!UserList[UserIndex].flags.CentinelaOK) {
						WritePlayWave(UserIndex, SND_WARP, Npclist[Centinela[index].NpcIndex].Pos.X,
								Npclist[Centinela[index].NpcIndex].Pos.Y);
						WriteCreateFX(UserIndex, Npclist[Centinela[index].NpcIndex].Char.CharIndex,
								FXIDs_FXWARP, 0);

						/* 'Resend the key */
						CentinelaSendClave(UserIndex, index);

						FlushBuffer(UserIndex);
					}
				}
			}
		}

	}
}

void GoToNextWorkingChar() {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 03/10/2010 */
	/* 'Va al siguiente usuario que se encuentre trabajando */
	/* '09/27/2010: C4b3z0n - Ahora una vez que termina la lista de usuarios, si se cumplio el tiempo de reset, resetea la info y asigna un nuevo tiempo. */
	/* '03/10/2010: ZaMa - Adaptado para que funcione mas de un centinela en paralelo. */
	/* '************************************************* */

	int LoopC;
	int CentinelaIndex;

	CentinelaIndex = GetIdleCentinela(1);

	for (LoopC = (1); LoopC <= (LastUser); LoopC++) {

		/* ' Usuario trabajando y no revisado? */
		if (UserList[LoopC].flags.UserLogged && UserList[LoopC].Counters.Trabajando > 0
				&& UserTienePrivilegio(LoopC, PlayerType_User)) {
			if (!UserList[LoopC].flags.CentinelaOK && UserList[LoopC].flags.CentinelaIndex == 0) {
				/* 'Inicializamos */
				Centinela[CentinelaIndex].RevisandoUserIndex = LoopC;
				Centinela[CentinelaIndex].TiempoRestante = TIEMPO_INICIAL;
				Centinela[CentinelaIndex].clave = RandomNumber(1, 32000);
				Centinela[CentinelaIndex].SpawnTime = vb6::GetTickCount();
				Centinela[CentinelaIndex].Activo = true;

				/* 'Ponemos al centinela en posición */
				WarpCentinela(LoopC, CentinelaIndex);

				/* ' Spawneo? */
				if (Centinela[CentinelaIndex].NpcIndex != 0) {
					/* 'Mandamos el mensaje (el centinela habla y aparece en consola para que no haya dudas) */
					WriteChatOverHead(LoopC,
							"Saludos " + UserList[LoopC].Name
									+ ", soy el Centinela de estas tierras. Me gustaría que escribas /CENTINELA "
									+ vb6::CStr(Centinela[CentinelaIndex].clave)
									+ " en no más de dos minutos.",
							(Npclist[Centinela[CentinelaIndex].NpcIndex].Char.CharIndex), vbGreen);
					WriteConsoleMsg(LoopC, "El centinela intenta llamar tu atención. ¡Respóndele rápido!",
							FontTypeNames_FONTTYPE_CENTINELA);
					FlushBuffer(LoopC);

					/* ' Guardo el indice del centinela */
					UserList[LoopC].flags.CentinelaIndex = CentinelaIndex;
				}

				/* ' Si ya se asigno un usuario a cada centinela, me voy */
				CentinelaIndex = CentinelaIndex + 1;
				if (CentinelaIndex > NRO_CENTINELA) {
					return;
				}

				/* ' Si no queda nadie inactivo, me voy */
				CentinelaIndex = GetIdleCentinela(CentinelaIndex);
				if (CentinelaIndex == 0) {
					return;
				}

			}
		}

	}

}

int GetIdleCentinela(int StartCheckIndex) {
	int retval = 0;
	/* '************************************************* */
	/* 'Author: ZaMa */
	/* 'Last modified: 07/10/2010 */
	/* 'Returns the index of the first idle centinela found, starting from a given index. */
	/* '************************************************* */
	int index;

	for (index = (StartCheckIndex); index <= (NRO_CENTINELA); index++) {

		if (!Centinela[index].Activo) {
			retval = index;
			return retval;
		}

	}

	return retval;
}

void CentinelaFinalCheck(int CentiIndex) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 02/10/2010 */
	/* 'Al finalizar el tiempo, se retira y realiza la acción pertinente dependiendo del caso */
	/* '03/10/2010: ZaMa - Adaptado para que funcione mas de un centinela en paralelo. */
	/* '************************************************* */

	int UserIndex;
	std::string UserName;

	UserIndex = Centinela[CentiIndex].RevisandoUserIndex;

	if (!UserList[UserIndex].flags.CentinelaOK) {

		UserName = UserList[UserIndex].Name;

		/* 'Logueamos el evento */
		LogCentinela("Centinela ejecuto y echó a " + UserName + " por uso de macro inasistido.");

		/* 'Avisamos a los admins */
		SendData(SendTarget_ToAdmins, 0,
				dakara::protocol::server::BuildConsoleMsg(
						"Servidor> El centinela ha ejecutado a " + UserName + " y lo echó del juego.",
						FontTypeNames_FONTTYPE_SERVER));

		/* ' Evitamos loguear el logout */
		Centinela[CentiIndex].RevisandoUserIndex = 0;

		WriteShowMessageBox(UserIndex, "Has sido ejecutado por macro inasistido y echado del juego.");
		UserDie(UserIndex);
		FlushBuffer(UserIndex);
		CloseSocket(UserIndex);
	}

	Centinela[CentiIndex].clave = 0;
	Centinela[CentiIndex].TiempoRestante = 0;
	Centinela[CentiIndex].RevisandoUserIndex = 0;
	Centinela[CentiIndex].Activo = false;

	if (Centinela[CentiIndex].NpcIndex != 0) {
		QuitarNPC(Centinela[CentiIndex].NpcIndex);
		Centinela[CentiIndex].NpcIndex = 0;
	}
}

void CentinelaCheckClave(int UserIndex, int clave) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 02/10/2010 */
	/* 'Corrobora la clave que le envia el usuario */
	/* '02/10/2010: ZaMa - Adaptado para que funcione mas de un centinela en paralelo. */
	/* '08/10/2010: ZaMa - Agrego algunos logueos mas coherentes. */
	/* '************************************************* */

	int CentinelaIndex;

	CentinelaIndex = UserList[UserIndex].flags.CentinelaIndex;

	/* ' No esta siendo revisado por ningun centinela? Clickeo a alguno? */
	if (CentinelaIndex == 0) {

		/* ' Si no clickeo a ninguno, simplemente logueo el evento (Sino hago hablar al centi) */
		CentinelaIndex = EsCentinela(UserList[UserIndex].flags.TargetNPC);
		if (CentinelaIndex == 0) {
			LogCentinela(
					"El usuario " + UserList[UserIndex].Name + " respondió aunque no se le hablaba a él..");
			return;
		}

	}

	if (clave == Centinela[CentinelaIndex].clave
			&& UserIndex == Centinela[CentinelaIndex].RevisandoUserIndex) {

		if (!UserList[UserIndex].flags.CentinelaOK) {

			UserList[UserIndex].flags.CentinelaOK = true;
			WriteChatOverHead(UserIndex,
					"¡Muchas gracias " + UserList[UserIndex].Name + "! Espero no haber sido una molestia.",
					Npclist[Centinela[CentinelaIndex].NpcIndex].Char.CharIndex, 0x00ffffff);

			Centinela[CentinelaIndex].Activo = false;
			FlushBuffer(UserIndex);

		} else {
			/* 'Logueamos el evento */
			LogCentinela(
					"El usuario " + UserList[UserIndex].Name
							+ " respondió más de una vez la contrasena correcta.");
		}

	} else {

		/* 'Logueamos el evento */
		if (UserIndex != Centinela[CentinelaIndex].RevisandoUserIndex) {
			WriteChatOverHead(UserIndex, "No es a ti a quien estoy hablando, ¿No ves?",
					Npclist[Centinela[CentinelaIndex].NpcIndex].Char.CharIndex, 0x00ffffff);
			LogCentinela(
					"El usuario " + UserList[UserIndex].Name + " respondió aunque no se le hablaba a él.");
		} else {

			if (!UserList[UserIndex].flags.CentinelaOK) {
				/* ' Clave incorrecta, la reenvio */
				CentinelaSendClave(UserIndex, CentinelaIndex);
				LogCentinela(
						"El usuario " + UserList[UserIndex].Name + " respondió una clave incorrecta: "
								+ vb6::CStr(clave) + " - Se esperaba : "
								+ vb6::CStr(Centinela[CentinelaIndex].clave));
			} else {
				LogCentinela(
						"El usuario " + UserList[UserIndex].Name
								+ " respondió una clave incorrecta después de haber respondido una clave correcta.");
			}
		}
	}

}

void ResetCentinelaInfo() {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 02/10/2010 */
	/* 'Cada determinada cantidad de tiempo, volvemos a revisar */
	/* '07/10/2010: ZaMa - Adaptado para que funcione mas de un centinela en paralelo. */
	/* '************************************************* */
	int LoopC;

	for (LoopC = (1); LoopC <= (LastUser); LoopC++) {

		UserList[LoopC].flags.CentinelaOK = false;
		UserList[LoopC].flags.CentinelaIndex = 0;

	}

}

void CentinelaSendClave(int UserIndex, int CentinelaIndex) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 02/10/2010 */
	/* 'Enviamos al usuario la clave vía el personaje centinela */
	/* '02/10/2010: ZaMa - Adaptado para que funcione mas de un centinela en paralelo. */
	/* '************************************************* */

	if (Centinela[CentinelaIndex].NpcIndex == 0) {
		return;
	}

	if (Centinela[CentinelaIndex].RevisandoUserIndex == UserIndex) {

		if (!UserList[UserIndex].flags.CentinelaOK) {
			WriteChatOverHead(UserIndex,
					"¡La clave que te he dicho es /CENTINELA " + vb6::CStr(Centinela[CentinelaIndex].clave)
							+ ", escríbelo rápido!",
					Npclist[Centinela[CentinelaIndex].NpcIndex].Char.CharIndex, vbGreen);
			WriteConsoleMsg(UserIndex, "El centinela intenta llamar tu atención. ¡Respondele rápido!",
					FontTypeNames_FONTTYPE_CENTINELA);
		} else {
			WriteChatOverHead(UserIndex, "Te agradezco, pero ya me has respondido. Me retiraré pronto.",
					(Npclist[Centinela[CentinelaIndex].NpcIndex].Char.CharIndex), vbGreen);
		}

	} else {
		WriteChatOverHead(UserIndex, "No es a ti a quien estoy hablando, ¿No ves?",
				Npclist[Centinela[CentinelaIndex].NpcIndex].Char.CharIndex, vbWhite);
	}

}

void PasarMinutoCentinela() {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 02/10/2010 */
	/* 'Control del timer. Llamado cada un minuto. */
	/* '03/10/2010: ZaMa - Adaptado para que funcione mas de un centinela en paralelo. */
	/* '************************************************* */

	int index;
	int UserIndex;
	int IdleCount = 0;

	if (!centinelaActivado) {
		return;
	}

	/* ' Primero reviso los que estan chequeando usuarios */
	for (index = (1); index <= (NRO_CENTINELA); index++) {

		/* ' Esta activo? */
		if (Centinela[index].Activo) {
			Centinela[index].TiempoRestante = Centinela[index].TiempoRestante - 1;

			/* ' Temrino el tiempo de chequeo? */
			if (Centinela[index].TiempoRestante == 0) {
				CentinelaFinalCheck(index);
			} else {

				UserIndex = Centinela[index].RevisandoUserIndex;

				/* 'RECORDamos al user que debe escribir */
				if (Distancia(Npclist[Centinela[index].NpcIndex].Pos, UserList[UserIndex].Pos) > 5) {
					WarpCentinela(UserIndex, index);
				}

				/* 'El centinela habla y se manda a consola para que no quepan dudas */
				WriteChatOverHead(UserIndex,
						"¡" + UserList[UserIndex].Name
								+ ", tienes un minuto más para responder! Debes escribir /CENTINELA "
								+ vb6::CStr(Centinela[index].clave) + ".",
						(Npclist[Centinela[index].NpcIndex].Char.CharIndex), vbRed);
				WriteConsoleMsg(UserIndex,
						"¡" + UserList[UserIndex].Name + ", tienes un minuto más para responder!",
						FontTypeNames_FONTTYPE_CENTINELA);
				FlushBuffer(UserIndex);
			}
		} else {

			/* ' Lo reseteo aca, para que pueda hablarle al usuario chequeado aunque haya respondido bien. */
			if (Centinela[index].NpcIndex != 0) {
				if (Centinela[index].RevisandoUserIndex != 0) {
					UserList[Centinela[index].RevisandoUserIndex].flags.CentinelaIndex = 0;
					Centinela[index].RevisandoUserIndex = 0;
				}
				QuitarNPC(Centinela[index].NpcIndex);
				Centinela[index].NpcIndex = 0;
			}

			IdleCount = IdleCount + 1;
		}

	}

	/* 'Verificamos si ya debemos resetear la lista */
	int TActual;
	TActual = vb6::GetTickCount();

	if (checkInterval(centinelaStartTime, TActual, centinelaInterval)) {
		/* ' Espero a que terminen de controlar todos los centinelas */
		DetenerAsignacion = true;
	}

	/* ' Si hay algun centinela libre, se fija si no hay trabajadores disponibles para chequear */
	if (IdleCount != 0) {

		/* ' Si es tiempo de resetear flags, chequeo que no quede nadie activo */
		if (DetenerAsignacion) {

			/* ' No se completaron los ultimos chequeos */
			if (IdleCount < NRO_CENTINELA) {
				return;
			}

			/* ' Resetea todos los flags */
			ResetCentinelaInfo();
			DetenerAsignacion = false;

			/* ' Renuevo el contador de reseteo */
			RenovarResetTimer();

		}

		GoToNextWorkingChar();

	}
}

void WarpCentinela(int UserIndex, int CentinelaIndex) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 02/10/2010 */
	/* 'Inciamos la revisión del usuario UserIndex */
	/* '02/10/2010: ZaMa - Adaptado para que funcione mas de un centinela en paralelo. */
	/* '************************************************* */

	/* 'Evitamos conflictos de índices */
	if (Centinela[CentinelaIndex].NpcIndex != 0) {
		QuitarNPC(Centinela[CentinelaIndex].NpcIndex);
		Centinela[CentinelaIndex].NpcIndex = 0;
	}

	/* ' Spawn it */
	Centinela[CentinelaIndex].NpcIndex = SpawnNpc(NPC_CENTINELA, UserList[UserIndex].Pos, true, false);

	/* 'Si no pudimos crear el NPC, seguimos esperando a poder hacerlo */
	if (Centinela[CentinelaIndex].NpcIndex == 0) {
		Centinela[CentinelaIndex].RevisandoUserIndex = 0;
		Centinela[CentinelaIndex].Activo = false;
	}

}

void CentinelaUserLogout(int CentinelaIndex) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 02/11/2010 */
	/* 'El usuario al que revisabamos se desconectó */
	/* '02/10/2010: ZaMa - Adaptado para que funcione mas de un centinela en paralelo. */
	/* '02/11/2010: ZaMa - Ahora no loguea que el usuario cerro si puso bien la clave. */
	/* '************************************************* */

	if (Centinela[CentinelaIndex].RevisandoUserIndex != 0) {

		/* 'Logueamos el evento */
		if (!UserList[Centinela[CentinelaIndex].RevisandoUserIndex].flags.CentinelaOK) {
			LogCentinela(
					"El usuario " + UserList[Centinela[CentinelaIndex].RevisandoUserIndex].Name
							+ " se desolgueó al pedirsele la contrasena.");
		}

		/* 'Reseteamos y esperamos a otro PasarMinuto para ir al siguiente user */
		Centinela[CentinelaIndex].clave = 0;
		Centinela[CentinelaIndex].TiempoRestante = 0;
		Centinela[CentinelaIndex].RevisandoUserIndex = 0;
		Centinela[CentinelaIndex].Activo = false;

		if (Centinela[CentinelaIndex].NpcIndex != 0) {
			QuitarNPC(Centinela[CentinelaIndex].NpcIndex);
			Centinela[CentinelaIndex].NpcIndex = 0;
		}

	}

}

void ResetCentinelas() {
	/* '************************************************* */
	/* 'Author: ZaMa */
	/* 'Last modified: 02/10/2010 */
	/* 'Resetea todos los centinelas */
	/* '************************************************* */
	int index;
	int UserIndex;

	for (index = (vb6::LBound(Centinela)); index <= (vb6::UBound(Centinela)); index++) {

		/* ' Si esta activo, reseteo toda la info y quito el npc */
		if (Centinela[index].Activo) {

			Centinela[index].Activo = false;

			UserIndex = Centinela[index].RevisandoUserIndex;
			if (UserIndex != 0) {
				UserList[UserIndex].flags.CentinelaIndex = 0;
				UserList[UserIndex].flags.CentinelaOK = false;
				Centinela[index].RevisandoUserIndex = 0;
			}

			Centinela[index].clave = 0;
			Centinela[index].TiempoRestante = 0;

			if (Centinela[index].NpcIndex != 0) {
				QuitarNPC(Centinela[index].NpcIndex);
				Centinela[index].NpcIndex = 0;
			}

		}

	}

	DetenerAsignacion = false;
	RenovarResetTimer();

}

int EsCentinela(int NpcIndex) {
	int retval = 0;
	/* '************************************************* */
	/* 'Author: ZaMa */
	/* 'Last modified: 07/10/2010 */
	/* 'Devuelve True si el indice pertenece a un centinela. */
	/* '************************************************* */

	int index;

	if (NpcIndex == 0) {
		return retval;
	}

	for (index = (1); index <= (NRO_CENTINELA); index++) {

		if (Centinela[index].NpcIndex == NpcIndex) {
			retval = index;
			return retval;
		}

	}

	return retval;
}

void RenovarResetTimer() {
	/* '************************************************* */
	/* 'Author: ZaMa */
	/* 'Last modified: 07/10/2010 */
	/* 'Renueva el timer que resetea el flag "CentinelaOk" de todos los usuarios. */
	/* '************************************************* */
	centinelaInterval = (RandomNumber(0, TIEMPO_PASAR_RANDOM) + TIEMPO_PASAR_BASE) * 60 * 1000;
}
