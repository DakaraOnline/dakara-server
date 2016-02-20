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

#include "Timers.h"
#include "SocketsLib.h"

#include <iostream>

int ESCUCHADAS;

static int iDay;

const int NIM_ADD = 0;
const int NIM_DELETE = 2;
const int NIF_MESSAGE = 1;
const int NIF_ICON = 2;
const int NIF_TIP = 4;

namespace {

std::unique_ptr<dakara::Timer> timerAuditoria;
std::unique_ptr<dakara::Timer> timerPiquete;
std::unique_ptr<dakara::Timer> timerFX;
std::unique_ptr<dakara::Timer> timerGameTimer;
std::unique_ptr<dakara::Timer> timerLluviaEvent;
std::unique_ptr<dakara::Timer> timerLluvia;
std::unique_ptr<dakara::Timer> timerAutoSave;
std::unique_ptr<dakara::Timer> timerNpcAtaca;
std::unique_ptr<dakara::Timer> timerAI;
std::unique_ptr<dakara::Timer> timerKillLog;
std::unique_ptr<dakara::Timer> timerHandleData;

void TimerHandleData_Timer() {
	int UserIndex;
	for (UserIndex = (1); UserIndex <= (LastUser); UserIndex++) {
		if (UserIndexSocketValido(UserIndex) && UserList[UserIndex].incomingData->length()) {
			if (UserList[UserIndex].ConnIgnoreIncomingData && UserList[UserIndex].IncomingDataAvailable) {
				try {
					HandleIncomingData(UserIndex);
				} catch (std::exception& ex) {
					std::cerr << "Unhandled error on TimerHandleData::callback: " << ex.what() << std::endl;
					LogApiSock("Unhandled error on TimerHandleData::callback, " + std::string(ex.what()));
					CloseSocket(UserIndex);
				} catch (...) {
					std::cerr << "UNKNOWN error on TimerHandleData::callback!" << std::endl;
					LogApiSock("UNKNOWN error on TimerHandleData::callback!");
					CloseSocket(UserIndex);
				}
			}
		}
	}
	// Allow the timer to drift in time.
	timerHandleData->registerTimer(50);
}

}

void TimersRegisterAll() {
	dakara::SocketServer& ss = (*DakaraSocketServer.get());

	timerAuditoria = ss.addTimer(1000, Auditoria_Timer, true);
	timerPiquete = ss.addTimer(6000, tPiqueteC_Timer, true);
	timerFX = ss.addTimer(4000, FX_Timer, true);
	timerGameTimer = ss.addTimer(40, GameTimer_Timer, true);
	timerLluviaEvent = ss.addTimer(6000, tLluviaEvent_Timer, true);
	timerLluvia = ss.addTimer(500, tLluvia_Timer, true);
	timerAutoSave = ss.addTimer(60000, AutoSave_Timer, true);
	timerNpcAtaca = ss.addTimer(IntervaloNPCPuedeAtacar, npcataca_Timer, true);
	timerAI = ss.addTimer(IntervaloNPCAI, TIMER_AI_Timer, true);
	timerKillLog = ss.addTimer(60000, KillLog_Timer, true);
	timerHandleData = ss.addTimer(50, TimerHandleData_Timer, false);
}

void CheckIdleUser() {
	int iUserIndex;

	for (iUserIndex = (1); iUserIndex <= (MaxUsers); iUserIndex++) {
		/* 'Conexion activa? y es un usuario loggeado? */
		if (UserIndexSocketValido(iUserIndex) && UserList[iUserIndex].flags.UserLogged) {
			/* 'Actualiza el contador de inactividad */
			if (UserList[iUserIndex].flags.Traveling == 0) {
				UserList[iUserIndex].Counters.IdleCount = UserList[iUserIndex].Counters.IdleCount + 1;
			}

			if (UserList[iUserIndex].Counters.IdleCount >= IdleLimit) {
				WriteShowMessageBox(iUserIndex, "Demasiado tiempo inactivo. Has sido desconectado.");
				/* 'mato los comercios seguros */
				if (UserList[iUserIndex].ComUsu.DestUsu > 0) {
					if (UserList[UserList[iUserIndex].ComUsu.DestUsu].flags.UserLogged) {
						if (UserList[UserList[iUserIndex].ComUsu.DestUsu].ComUsu.DestUsu == iUserIndex) {
							WriteConsoleMsg(UserList[iUserIndex].ComUsu.DestUsu,
									"Comercio cancelado por el otro usuario.", FontTypeNames_FONTTYPE_TALK);
							FinComerciarUsu(UserList[iUserIndex].ComUsu.DestUsu);
							/* 'flush the buffer to send the message right away */
							FlushBuffer(UserList[iUserIndex].ComUsu.DestUsu);
						}
					}
					FinComerciarUsu(iUserIndex);
				}
				CerrarUserIndexIniciar(iUserIndex);
			}
		}
	}
}

void Auditoria_Timer() {
	static int centinelSecs = 0;
	static int socketsClean = 0;

	centinelSecs = centinelSecs + 1;

	if (centinelSecs == 5) {
		/* 'Every 5 seconds, we try to call the player's attention so it will report the code. */
		CallUserAttention();

		centinelSecs = 0;
	}

	/* Sockets */
	socketsClean++;
	if (socketsClean >= 10) {
		socketsClean = 0;
	}

	/* 'sistema de desconexion de 10 segs */
	PasarSegundo();
}

void UpdateNpcsExp(float Multiplicador) {

	int NpcIndex;
	for (NpcIndex = (1); NpcIndex <= (LastNPC); NpcIndex++) {
		Npclist[NpcIndex].GiveEXP = Npclist[NpcIndex].GiveEXP * Multiplicador;
		Npclist[NpcIndex].flags.ExpCount = Npclist[NpcIndex].flags.ExpCount * Multiplicador;
	}
}

void AutoSave_Timer() {

	/* 'fired every minute */
	static int Minutos = 0;
	static int MinutosLatsClean = 0;
	static int MinsPjesSave = 0;
	static int MinsSendMotd = 0;

	static int PrintConsole = 0;

	Minutos = Minutos + 1;
	MinsPjesSave = MinsPjesSave + 1;
	MinsSendMotd = MinsSendMotd + 1;

	double tmpHappyHour;

	/* Imprimir en la consola el numero de users */
	PrintConsole++;
	if (PrintConsole >= IntervaloImprimirEnConsola) {
		std::cerr << vb6::dateToString(vb6::Now()) << " Online: " << NumUsers << std::endl;
		PrintConsole = 0;
	}

	/* ' HappyHour */
	iDay = vb6::Weekday(vb6::Now());
	tmpHappyHour = HappyHourDays[iDay];

	if (tmpHappyHour != HappyHour) {

		if (HappyHourActivated) {
			/* ' Reestablece la exp de los npcs */
			if (HappyHour != 0) {
				UpdateNpcsExp(1 / HappyHour);
			}
		}

		/* ' Desactiva */
		if (tmpHappyHour == 1) {
			SendData(SendTarget_ToAll, 0,
					dakara::protocol::server::BuildConsoleMsg("¡Ha concluido la Happy Hour!", FontTypeNames_FONTTYPE_DIOS));

			HappyHourActivated = false;

			/* ' Activa */
		} else {
			UpdateNpcsExp(tmpHappyHour);

			if (HappyHour != 1) {
				SendData(SendTarget_ToAll, 0,
						dakara::protocol::server::BuildConsoleMsg(
								"Se ha modificado la Happy Hour, a partir de ahora las criaturas aumentan su experiencia en un "
										+ vb6::CStr(vb6::Round((tmpHappyHour - 1) * 100, 2)) + "%",
								FontTypeNames_FONTTYPE_DIOS));
			} else {
				SendData(SendTarget_ToAll, 0,
						dakara::protocol::server::BuildConsoleMsg(
								"¡Ha comenzado la Happy Hour! ¡Las criaturas aumentan su experiencia en un "
										+ vb6::CStr(vb6::Round((tmpHappyHour - 1) * 100, 2)) + "%!",
								FontTypeNames_FONTTYPE_DIOS));
			}

			HappyHourActivated = true;
		}

		HappyHour = tmpHappyHour;
	}

	AreasOptimizacion();

	/* 'Actualizamos el centinela */
	PasarMinutoCentinela();

	if (Minutos == MinutosWs - 1) {
		SendData(SendTarget_ToAll, 0,
				dakara::protocol::server::BuildConsoleMsg("Worldsave en 1 minuto ...", FontTypeNames_FONTTYPE_VENENO));
	}

	if (Minutos >= MinutosWs) {
		DoBackUp();
		aClon->VaciarColeccion();
		Minutos = 0;
	}

	if (MinsPjesSave == MinutosGuardarUsuarios - 1) {
		SendData(SendTarget_ToAll, 0,
				dakara::protocol::server::BuildConsoleMsg("CharSave en 1 minuto ...", FontTypeNames_FONTTYPE_VENENO));
	} else if (MinsPjesSave >= MinutosGuardarUsuarios) {
		ActualizaExperiencias();
		GuardarUsuarios();
		MinsPjesSave = 0;
	}

	if (MinutosLatsClean >= 15) {
		MinutosLatsClean = 0;
		/* 'respawn de los guardias en las pos originales */
		ReSpawnOrigPosNpcs();
		LimpiarMundo();
	} else {
		MinutosLatsClean = MinutosLatsClean + 1;
	}

	if (MinsSendMotd >= MinutosMotd) {
		int i;
		for (i = (1); i <= (LastUser); i++) {
			if (UserList[i].flags.UserLogged) {
				SendMOTD(i);
			}
		}
		MinsSendMotd = 0;
	}

	PurgarPenas();
	CheckIdleUser();

	LogNumUsers();
}

void FX_Timer() {
	SonidosMapas->ReproducirSonidosDeMapas();
}

void GameTimer_Timer() {
	int iUserIndex;
	bool bEnviarStats;
	bool bEnviarAyS;

	/* '<<<<<< Procesa eventos de los usuarios >>>>>> */
	/* 'LastUser */
	for (iUserIndex = (1); iUserIndex <= (MaxUsers); iUserIndex++) {
		/* 'Conexion activa? */
		if (UserIndexSocketValido(iUserIndex)) {
			/* '¿User valido? */

			if (UserList[iUserIndex].flags.UserLogged) {

				/* '[Alejo-18-5] */
				bEnviarStats = false;
				bEnviarAyS = false;

				if (UserList[iUserIndex].flags.Paralizado == 1) {
					EfectoParalisisUser(iUserIndex);
				}
				if (UserList[iUserIndex].flags.Ceguera == 1 || UserList[iUserIndex].flags.Estupidez) {
					EfectoCegueEstu(iUserIndex);
				}

				if (UserList[iUserIndex].flags.Muerto == 0) {

					/* '[Consejeros] */
					if (UserTieneAlgunPrivilegios(iUserIndex, PlayerType_User)) {
						EfectoLava(iUserIndex);
					}

					if (UserList[iUserIndex].flags.Desnudo != 0
							&& UserTieneAlgunPrivilegios(iUserIndex, PlayerType_User)) {
						EfectoFrio(iUserIndex);
					}

					if (UserList[iUserIndex].flags.Meditando) {
						DoMeditar(iUserIndex);
					}

					if (UserList[iUserIndex].flags.Envenenado != 0
							&& UserTieneAlgunPrivilegios(iUserIndex, PlayerType_User)) {
						EfectoVeneno(iUserIndex);
					}

					if (UserList[iUserIndex].flags.AdminInvisible != 1) {
						if (UserList[iUserIndex].flags.invisible == 1) {
							EfectoInvisibilidad(iUserIndex);
						}
						if (UserList[iUserIndex].flags.Oculto == 1) {
							DoPermanecerOculto(iUserIndex);
						}
					}

					if (UserList[iUserIndex].flags.Mimetizado == 1) {
						EfectoMimetismo(iUserIndex);
					}

					if (UserList[iUserIndex].flags.AtacablePor != 0) {
						EfectoEstadoAtacable(iUserIndex);
					}

					DuracionPociones(iUserIndex);

					HambreYSed(iUserIndex, bEnviarAyS);

					if (UserList[iUserIndex].flags.Hambre == 0 && UserList[iUserIndex].flags.Sed == 0) {
						if (Lloviendo) {
							if (!Intemperie(iUserIndex)) {
								if (!UserList[iUserIndex].flags.Descansar) {
									/* 'No esta descansando */
									Sanar(iUserIndex, bEnviarStats, SanaIntervaloSinDescansar);
									if (bEnviarStats) {
										WriteUpdateHP(iUserIndex);
										bEnviarStats = false;
									}
									RecStamina(iUserIndex, bEnviarStats, StaminaIntervaloSinDescansar);
									if (bEnviarStats) {
										WriteUpdateSta(iUserIndex);
										bEnviarStats = false;
									}
								} else {
									/* 'esta descansando */
									Sanar(iUserIndex, bEnviarStats, SanaIntervaloDescansar);
									if (bEnviarStats) {
										WriteUpdateHP(iUserIndex);
										bEnviarStats = false;
									}
									RecStamina(iUserIndex, bEnviarStats, StaminaIntervaloDescansar);
									if (bEnviarStats) {
										WriteUpdateSta(iUserIndex);
										bEnviarStats = false;
									}
									/* 'termina de descansar automaticamente */
									if (UserList[iUserIndex].Stats.MaxHp == UserList[iUserIndex].Stats.MinHp
											&& UserList[iUserIndex].Stats.MaxSta
													== UserList[iUserIndex].Stats.MinSta) {
										WriteRestOK(iUserIndex);
										WriteConsoleMsg(iUserIndex, "Has terminado de descansar.",
												FontTypeNames_FONTTYPE_INFO);
										UserList[iUserIndex].flags.Descansar = false;
									}

								}
							}
						} else {
							if (!UserList[iUserIndex].flags.Descansar) {
								/* 'No esta descansando */

								Sanar(iUserIndex, bEnviarStats, SanaIntervaloSinDescansar);
								if (bEnviarStats) {
									WriteUpdateHP(iUserIndex);
									bEnviarStats = false;
								}
								RecStamina(iUserIndex, bEnviarStats, StaminaIntervaloSinDescansar);
								if (bEnviarStats) {
									WriteUpdateSta(iUserIndex);
									bEnviarStats = false;
								}

							} else {
								/* 'esta descansando */

								Sanar(iUserIndex, bEnviarStats, SanaIntervaloDescansar);
								if (bEnviarStats) {
									WriteUpdateHP(iUserIndex);
									bEnviarStats = false;
								}
								RecStamina(iUserIndex, bEnviarStats, StaminaIntervaloDescansar);
								if (bEnviarStats) {
									WriteUpdateSta(iUserIndex);
									bEnviarStats = false;
								}
								/* 'termina de descansar automaticamente */
								if (UserList[iUserIndex].Stats.MaxHp == UserList[iUserIndex].Stats.MinHp
										&& UserList[iUserIndex].Stats.MaxSta
												== UserList[iUserIndex].Stats.MinSta) {
									WriteRestOK(iUserIndex);
									WriteConsoleMsg(iUserIndex, "Has terminado de descansar.",
											FontTypeNames_FONTTYPE_INFO);
									UserList[iUserIndex].flags.Descansar = false;
								}

							}
						}
					}

					if (bEnviarAyS) {
						WriteUpdateHungerAndThirst(iUserIndex);
					}

					if (UserList[iUserIndex].NroMascotas > 0) {
						TiempoInvocacion(iUserIndex);
					}
				} else {
					if (UserList[iUserIndex].flags.Traveling != 0) {
						TravelingEffect(iUserIndex);
					}
					/* 'Muerto */
				}
				/* 'no esta logeado? */
			} else {
				/* 'Inactive players will be removed! */
				UserList[iUserIndex].Counters.IdleCount = UserList[iUserIndex].Counters.IdleCount + 1;
				if (UserList[iUserIndex].Counters.IdleCount > IntervaloParaConexion) {
					UserList[iUserIndex].Counters.IdleCount = 0;
					CloseSocket(iUserIndex);
				}
				/* 'UserLogged */
			}

		}

		if (UserIndexSocketValido(iUserIndex)) {
			/* 'If there is anything to be sent, we send it */
			FlushBuffer(iUserIndex);
		}
	}
}

void KillLog_Timer() {
#if 0
	if (FileExist(vb6::App().Path + "/logs/connect.log", 0)) {
		/* FIXME: KILL App . Path & "/logs/connect.log" */
	}
	if (FileExist(vb6::App().Path + "/logs/haciendo.log", 0)) {
		/* FIXME: KILL App . Path & "/logs/haciendo.log" */
	}
	if (FileExist(vb6::App().Path + "/logs/stats.log", 0)) {
		/* FIXME: KILL App . Path & "/logs/stats.log" */
	}
	if (FileExist(vb6::App().Path + "/logs/Asesinatos.log", 0)) {
		/* FIXME: KILL App . Path & "/logs/Asesinatos.log" */
	}
	if (FileExist(vb6::App().Path + "/logs/HackAttemps.log", 0)) {
		/* FIXME: KILL App . Path & "/logs/HackAttemps.log" */
	}
	if (!FileExist(vb6::App().Path + "/logs/nokillwsapi.txt")) {
		if (FileExist(vb6::App().Path + "/logs/wsapi.log", 0)) {
			/* FIXME: KILL App . Path & "/logs/wsapi.log" */
		}
	}
#endif
}

void npcataca_Timer() {

	/* FIXME: ON ERROR RESUME NEXT */
	int npc;

	for (npc = (1); npc <= (LastNPC); npc++) {
		Npclist[npc].CanAttack = 1;
	}

}

void securityTimer_Timer() {

	/* # IF SeguridadAlkon THEN */
	/* # END IF */

}

void TIMER_AI_Timer() {

	/* FIXME: ON ERROR GOTO ErrorHandler */
	int NpcIndex;
	int mapa;

	/* 'Barrin 29/9/03 */
	if (!haciendoBK && !EnPausa) {
		/* 'Update NPCs */
		for (NpcIndex = (1); NpcIndex <= (LastNPC); NpcIndex++) {

			/* 'Nos aseguramos que sea INTELIGENTE! */
			if (Npclist[NpcIndex].flags.NPCActive) {

				/* ' Chequea si contiua teniendo dueño */
				if (Npclist[NpcIndex].Owner > 0) {
					ValidarPermanenciaNpc(NpcIndex);
				}

				if (Npclist[NpcIndex].flags.Paralizado == 1) {
					EfectoParalisisNpc(NpcIndex);
				} else {
					/* ' Preto? Tienen ai especial */
					if (Npclist[NpcIndex].NPCtype == eNPCType_Pretoriano) {
#if 0
						ClanPretoriano[Npclist[NpcIndex].ClanIndex].PerformPretorianAI(NpcIndex);
#endif
					} else {
						/* 'Usamos AI si hay algun user en el mapa */
						if (Npclist[NpcIndex].flags.Inmovilizado == 1) {
							EfectoParalisisNpc(NpcIndex);
						}

						mapa = Npclist[NpcIndex].Pos.Map;

						if (mapa > 0) {
							if (MapInfo[mapa].NumUsers > 0) {
								if (Npclist[NpcIndex].Movement != TipoAI_ESTATICO) {
									NPCAI(NpcIndex);
								}
							}
						}
					}
				}
			}
		}
	}
}

void tLluvia_Timer() {
	/* ' [TEMPORAL] */

#if 0
	int iCount;
	if (Lloviendo) {
		for (iCount = (1); iCount <= (LastUser); iCount++) {
			EfectoLluvia(iCount);
		}
	}
#endif
}

void tLluviaEvent_Timer() {
	static int MinutosLloviendo = 0;
	static int MinutosSinLluvia = 0;

	if (!Lloviendo) {
		MinutosSinLluvia = MinutosSinLluvia + 1;
		if (MinutosSinLluvia >= 15 && MinutosSinLluvia < 1440) {
			if (RandomNumber(1, 100) <= 2) {
				Lloviendo = true;
				MinutosSinLluvia = 0;
				SendData(SendTarget_ToAll, 0, dakara::protocol::server::BuildRainToggle());
			}
		} else if (MinutosSinLluvia >= 1440) {
			Lloviendo = true;
			MinutosSinLluvia = 0;
			SendData(SendTarget_ToAll, 0, dakara::protocol::server::BuildRainToggle());
		}
	} else {
		MinutosLloviendo = MinutosLloviendo + 1;
		if (MinutosLloviendo >= 5) {
			Lloviendo = false;
			SendData(SendTarget_ToAll, 0, dakara::protocol::server::BuildRainToggle());
			MinutosLloviendo = 0;
		} else {
			if (RandomNumber(1, 100) <= 2) {
				Lloviendo = false;
				MinutosLloviendo = 0;
				SendData(SendTarget_ToAll, 0, dakara::protocol::server::BuildRainToggle());
			}
		}
	}
}

void tPiqueteC_Timer() {
	bool NuevaA;
	/* ' Dim NuevoL As Boolean */
	int GI;
	int i;

	for (i = (1); i <= (LastUser); i++) {
		if (UserList[i].flags.UserLogged) {
			if (MapData[UserList[i].Pos.Map][UserList[i].Pos.X][UserList[i].Pos.Y].trigger
					== eTrigger_ANTIPIQUETE) {
				if (UserList[i].flags.Muerto == 0) {
					UserList[i].Counters.PiqueteC = UserList[i].Counters.PiqueteC + 1;
					WriteConsoleMsg(i, "¡¡¡Estás obstruyendo la vía pública, muévete o serás encarcelado!!!",
							FontTypeNames_FONTTYPE_INFO);

					if (UserList[i].Counters.PiqueteC > 23) {
						UserList[i].Counters.PiqueteC = 0;
						Encarcelar(i, TIEMPO_CARCEL_PIQUETE);
					}
				} else {
					UserList[i].Counters.PiqueteC = 0;
				}
			} else {
				UserList[i].Counters.PiqueteC = 0;
			}

			/* 'ustedes se preguntaran que hace esto aca? */
			/* 'bueno la respuesta es simple: el codigo de AO es una mierda y encontrar */
			/* 'todos los puntos en los cuales la alineacion puede cambiar es un dolor de */
			/* 'huevos, asi que lo controlo aca, cada 6 segundos, lo cual es razonable */

			GI = UserList[i].GuildIndex;
			if (GI > 0) {
				NuevaA = false;
				/* ' NuevoL = False */
				if (!m_ValidarPermanencia(i, true, NuevaA)) {
					WriteConsoleMsg(i,
							"Has sido expulsado del clan. ¡El clan ha sumado un punto de antifacción!",
							FontTypeNames_FONTTYPE_GUILD);
				}
				if (NuevaA) {
					SendData(SendTarget_ToGuildMembers, GI,
							dakara::protocol::server::BuildConsoleMsg(
									"¡El clan ha pasado a tener alineación " + GuildAlignment(GI) + "!",
									FontTypeNames_FONTTYPE_GUILD));
					LogClanes("¡El clan cambio de alineación!");
				}
				/* '                    If NuevoL Then */
				/* '                        Call SendData(SendTarget.ToGuildMembers, GI, PrepareMessageConsoleMsg("¡El clan tiene un nuevo líder!", FontTypeNames.FONTTYPE_GUILD)) */
				/* '                        Call LogClanes("¡El clan tiene nuevo lider!") */
				/* '                    End If */
			}

			FlushBuffer(i);
		}
	}
}

