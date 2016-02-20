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

#include "Npcs.h"

void QuitarMascota(int UserIndex, int NpcIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int i;

	for (i = (1); i <= (MAXMASCOTAS); i++) {
		if (UserList[UserIndex].MascotasIndex[i] == NpcIndex) {
			UserList[UserIndex].MascotasIndex[i] = 0;
			UserList[UserIndex].MascotasType[i] = 0;

			UserList[UserIndex].NroMascotas = UserList[UserIndex].NroMascotas - 1;
			break; /* FIXME: EXIT FOR */
		}
	}
}

void QuitarMascotaNpc(int Maestro) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	Npclist[Maestro].Mascotas = Npclist[Maestro].Mascotas - 1;
}

void MuereNpc(int NpcIndex, int UserIndex) {
	/* '******************************************************** */
	/* 'Author: Unknown */
	/* 'Llamado cuando la vida de un NPC llega a cero. */
	/* 'Last Modify Date: 13/07/2010 */
	/* '22/06/06: (Nacho) Chequeamos si es pretoriano */
	/* '24/01/2007: Pablo (ToxicWaste): Agrego para actualización de tag si cambia de status. */
	/* '22/05/2010: ZaMa - Los caos ya no suben nobleza ni plebe al atacar npcs. */
	/* '23/05/2010: ZaMa - El usuario pierde la pertenencia del npc. */
	/* '13/07/2010: ZaMa - Optimizaciones de logica en la seleccion de pretoriano, y el posible cambio de alencion del usuario. */
	/* '******************************************************** */

	struct npc MiNPC;
	MiNPC = Npclist[NpcIndex];
	bool EraCriminal;

	/* ' Es pretoriano? */
	if (MiNPC.NPCtype == eNPCType_Pretoriano) {
		// ClanPretoriano[MiNPC.ClanIndex].MuerePretoriano(NpcIndex);
	}

	/* 'Quitamos el npc */
	QuitarNPC(NpcIndex);

	/* ' Lo mato un usuario? */
	if (UserIndex > 0) {

		if (MiNPC.flags.Snd3 > 0) {
			SendData(SendTarget_ToPCArea, UserIndex,
					dakara::protocol::server::BuildPlayWave(MiNPC.flags.Snd3, MiNPC.Pos.X, MiNPC.Pos.Y));
		}
		UserList[UserIndex].flags.TargetNPC = 0;
		UserList[UserIndex].flags.TargetNpcTipo = eNPCType_Comun;

		/* 'El user que lo mato tiene mascotas? */
		if (UserList[UserIndex].NroMascotas > 0) {
			int T;
			for (T = (1); T <= (MAXMASCOTAS); T++) {
				if (UserList[UserIndex].MascotasIndex[T] > 0) {
					if (Npclist[UserList[UserIndex].MascotasIndex[T]].TargetNPC == NpcIndex) {
						FollowAmo(UserList[UserIndex].MascotasIndex[T]);
					}
				}
			}
		}

		/* '[KEVIN] */
		if (MiNPC.flags.ExpCount > 0) {
			if (UserList[UserIndex].PartyIndex > 0) {
				ObtenerExito(UserIndex, MiNPC.flags.ExpCount, MiNPC.Pos.Map, MiNPC.Pos.X, MiNPC.Pos.Y);
			} else {
				UserList[UserIndex].Stats.Exp = UserList[UserIndex].Stats.Exp + MiNPC.flags.ExpCount;
				if (UserList[UserIndex].Stats.Exp > MAXEXP) {
					UserList[UserIndex].Stats.Exp = MAXEXP;
				}
				WriteConsoleMsg(UserIndex, "Has ganado " + vb6::CStr(MiNPC.flags.ExpCount) + " puntos de experiencia.",
						FontTypeNames_FONTTYPE_FIGHT);
			}
			MiNPC.flags.ExpCount = 0;
		}

		/* '[/KEVIN] */
		WriteConsoleMsg(UserIndex, "¡Has matado a la criatura!", FontTypeNames_FONTTYPE_FIGHT);
		if (UserList[UserIndex].Stats.NPCsMuertos < 32000) {
			UserList[UserIndex].Stats.NPCsMuertos = UserList[UserIndex].Stats.NPCsMuertos + 1;
		}

		EraCriminal = criminal(UserIndex);

		if (MiNPC.Stats.Alineacion == 0) {

			if (MiNPC.Numero == Guardias) {
				UserList[UserIndex].Reputacion.NobleRep = 0;
				UserList[UserIndex].Reputacion.PlebeRep = 0;
				UserList[UserIndex].Reputacion.AsesinoRep = UserList[UserIndex].Reputacion.AsesinoRep + 500;
				if (UserList[UserIndex].Reputacion.AsesinoRep > MAXREP) {
					UserList[UserIndex].Reputacion.AsesinoRep = MAXREP;
				}
			}

			if (MiNPC.MaestroUser == 0) {
				UserList[UserIndex].Reputacion.AsesinoRep = UserList[UserIndex].Reputacion.AsesinoRep
						+ vlASESINO;
				if (UserList[UserIndex].Reputacion.AsesinoRep > MAXREP) {
					UserList[UserIndex].Reputacion.AsesinoRep = MAXREP;
				}
			}

		} else if (!esCaos(UserIndex)) {
			if (MiNPC.Stats.Alineacion == 1) {
				UserList[UserIndex].Reputacion.PlebeRep = UserList[UserIndex].Reputacion.PlebeRep + vlCAZADOR;
				if (UserList[UserIndex].Reputacion.PlebeRep > MAXREP) {
					UserList[UserIndex].Reputacion.PlebeRep = MAXREP;
				}

			} else if (MiNPC.Stats.Alineacion == 2) {
				UserList[UserIndex].Reputacion.NobleRep = UserList[UserIndex].Reputacion.NobleRep
						+ vlASESINO / 2;
				if (UserList[UserIndex].Reputacion.NobleRep > MAXREP) {
					UserList[UserIndex].Reputacion.NobleRep = MAXREP;
				}

			} else if (MiNPC.Stats.Alineacion == 4) {
				UserList[UserIndex].Reputacion.PlebeRep = UserList[UserIndex].Reputacion.PlebeRep + vlCAZADOR;
				if (UserList[UserIndex].Reputacion.PlebeRep > MAXREP) {
					UserList[UserIndex].Reputacion.PlebeRep = MAXREP;
				}

			}
		}

		bool EsCriminal;
		EsCriminal = criminal(UserIndex);

		/* ' Cambio de alienacion? */
		if (EraCriminal != EsCriminal) {

			/* ' Se volvio pk? */
			if (EsCriminal) {
				if (esArmada(UserIndex)) {
					ExpulsarFaccionReal(UserIndex);
				}

				/* ' Se volvio ciuda */
			} else {
				if (esCaos(UserIndex)) {
					ExpulsarFaccionCaos(UserIndex);
				}
			}

			RefreshCharStatus(UserIndex);
		}

		CheckUserLevel(UserIndex);

		if (NpcIndex == UserList[UserIndex].flags.ParalizedByNpcIndex) {
			RemoveParalisis(UserIndex);
		}

		/* ' Userindex > 0 */
	}

	if (MiNPC.MaestroUser == 0) {
		/* 'Tiramos el inventario */
		NPC_TIRAR_ITEMS(MiNPC, MiNPC.NPCtype == eNPCType_Pretoriano);
		/* 'ReSpawn o no */
		ReSpawnNpc(MiNPC);
	}
}

void ResetNpcFlags(int NpcIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	/* 'Clear the npc's flags */

	Npclist[NpcIndex].flags.AfectaParalisis = 0;
	Npclist[NpcIndex].flags.AguaValida = 0;
	Npclist[NpcIndex].flags.AttackedBy = "";
	Npclist[NpcIndex].flags.AttackedFirstBy = "";
	Npclist[NpcIndex].flags.BackUp = 0;
	Npclist[NpcIndex].flags.Bendicion = 0;
	Npclist[NpcIndex].flags.Domable = 0;
	Npclist[NpcIndex].flags.Envenenado = 0;
	Npclist[NpcIndex].flags.Faccion = 0;
	Npclist[NpcIndex].flags.Follow = false;
	Npclist[NpcIndex].flags.AtacaDoble = 0;
	Npclist[NpcIndex].flags.LanzaSpells = 0;
	Npclist[NpcIndex].flags.invisible = 0;
	Npclist[NpcIndex].flags.Maldicion = 0;
	Npclist[NpcIndex].flags.OldHostil = 0;
	Npclist[NpcIndex].flags.OldMovement = TipoAI_None;
	Npclist[NpcIndex].flags.Paralizado = 0;
	Npclist[NpcIndex].flags.Inmovilizado = 0;
	Npclist[NpcIndex].flags.Respawn = 0;
	Npclist[NpcIndex].flags.RespawnOrigPos = 0;
	Npclist[NpcIndex].flags.Snd1 = 0;
	Npclist[NpcIndex].flags.Snd2 = 0;
	Npclist[NpcIndex].flags.Snd3 = 0;
	Npclist[NpcIndex].flags.TierraInvalida = 0;
}

void ResetNpcCounters(int NpcIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	Npclist[NpcIndex].Contadores.Paralisis = 0;
	Npclist[NpcIndex].Contadores.TiempoExistencia = 0;
}

void ResetNpcCharInfo(int NpcIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	Npclist[NpcIndex].Char.body = 0;
	Npclist[NpcIndex].Char.CascoAnim = 0;
	Npclist[NpcIndex].Char.CharIndex = 0;
	Npclist[NpcIndex].Char.FX = 0;
	Npclist[NpcIndex].Char.Head = 0;
	Npclist[NpcIndex].Char.heading = eHeading_None;
	Npclist[NpcIndex].Char.loops = 0;
	Npclist[NpcIndex].Char.ShieldAnim = 0;
	Npclist[NpcIndex].Char.WeaponAnim = 0;
}

void ResetNpcCriatures(int NpcIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int j;

	for (j = (1); j <= (Npclist[NpcIndex].NroCriaturas); j++) {
		Npclist[NpcIndex].Criaturas[j].NpcIndex = 0;
		Npclist[NpcIndex].Criaturas[j].NpcName = "";
	}

	Npclist[NpcIndex].NroCriaturas = 0;
}

void ResetExpresiones(int NpcIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int j;

	for (j = (1); j <= (Npclist[NpcIndex].NroExpresiones); j++) {
		Npclist[NpcIndex].Expresiones[j] = "";
	}

	Npclist[NpcIndex].NroExpresiones = 0;
}

void ResetNpcMainInfo(int NpcIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* '22/05/2010: ZaMa - Ahora se resetea el dueno del npc también. */
	/* '*************************************************** */

	Npclist[NpcIndex].Attackable = 0;
	Npclist[NpcIndex].CanAttack = 0;
	Npclist[NpcIndex].Comercia = 0;
	Npclist[NpcIndex].GiveEXP = 0;
	Npclist[NpcIndex].GiveGLD = 0;
	Npclist[NpcIndex].Hostile = 0;
	Npclist[NpcIndex].InvReSpawn = 0;

	if (Npclist[NpcIndex].MaestroUser > 0) {
		QuitarMascota(Npclist[NpcIndex].MaestroUser, NpcIndex);
	}
	if (Npclist[NpcIndex].MaestroNpc > 0) {
		QuitarMascotaNpc(Npclist[NpcIndex].MaestroNpc);
	}
	if (Npclist[NpcIndex].Owner > 0) {
		PerdioNpc(Npclist[NpcIndex].Owner);
	}

	Npclist[NpcIndex].MaestroUser = 0;
	Npclist[NpcIndex].MaestroNpc = 0;
	Npclist[NpcIndex].Owner = 0;

	Npclist[NpcIndex].Mascotas = 0;
	Npclist[NpcIndex].Movement = TipoAI_None;
	Npclist[NpcIndex].Name = "";
	Npclist[NpcIndex].NPCtype = eNPCType_Comun;
	Npclist[NpcIndex].Numero = 0;
	Npclist[NpcIndex].Orig.Map = 0;
	Npclist[NpcIndex].Orig.X = 0;
	Npclist[NpcIndex].Orig.Y = 0;
	Npclist[NpcIndex].PoderAtaque = 0;
	Npclist[NpcIndex].PoderEvasion = 0;
	Npclist[NpcIndex].Pos.Map = 0;
	Npclist[NpcIndex].Pos.X = 0;
	Npclist[NpcIndex].Pos.Y = 0;
	Npclist[NpcIndex].SkillDomar = 0;
	Npclist[NpcIndex].Target = 0;
	Npclist[NpcIndex].TargetNPC = 0;
	Npclist[NpcIndex].TipoItems = 0;
	Npclist[NpcIndex].Veneno = 0;
	Npclist[NpcIndex].desc = "";

	Npclist[NpcIndex].ClanIndex = 0;

	int j;
	for (j = (1); j <= (Npclist[NpcIndex].NroSpells); j++) {
		Npclist[NpcIndex].Spells[j] = 0;
	}

	ResetNpcCharInfo(NpcIndex);
	ResetNpcCriatures(NpcIndex);
	ResetExpresiones(NpcIndex);
}

void QuitarNPC(int NpcIndex) {
	/* '*************************************************** */
	/* 'Autor: Unknown (orginal version) */
	/* 'Last Modification: 16/11/2009 */
	/* '16/11/2009: ZaMa - Now npcs lose their owner */
	/* '*************************************************** */

	Npclist[NpcIndex].flags.NPCActive = false;

	if (InMapBounds(Npclist[NpcIndex].Pos.Map, Npclist[NpcIndex].Pos.X, Npclist[NpcIndex].Pos.Y)) {
		EraseNPCChar(NpcIndex);
	}

	/* 'Nos aseguramos de que el inventario sea removido... */
	/* 'asi los lobos no volveran a tirar armaduras ;)) */
	ResetNpcInv(NpcIndex);
	ResetNpcFlags(NpcIndex);
	ResetNpcCounters(NpcIndex);

	ResetNpcMainInfo(NpcIndex);

	if (NpcIndex == LastNPC) {
		while (!(Npclist[LastNPC].flags.NPCActive)) {
			LastNPC = LastNPC - 1;
			if (LastNPC < 1) {
				break;
			}
		}
	}

	if (NumNPCs != 0) {
		NumNPCs = NumNPCs - 1;
	}
}

void QuitarPet(int UserIndex, int NpcIndex) {
	/* '*************************************************** */
	/* 'Autor: ZaMa */
	/* 'Last Modification: 18/11/2009 */
	/* 'Kills a pet */
	/* '*************************************************** */

	int i;
	int PetIndex = 0;

	/* ' Busco el indice de la mascota */
	for (i = (1); i <= (MAXMASCOTAS); i++) {
		if (UserList[UserIndex].MascotasIndex[i] == NpcIndex) {
			PetIndex = i;
		}
	}

	/* ' Poco probable que pase, pero por las dudas.. */
	if (PetIndex == 0) {
		return;
	}

	/* ' Limpio el slot de la mascota */
	UserList[UserIndex].NroMascotas = UserList[UserIndex].NroMascotas - 1;
	UserList[UserIndex].MascotasIndex[PetIndex] = 0;
	UserList[UserIndex].MascotasType[PetIndex] = 0;

	/* ' Elimino la mascota */
	QuitarNPC(NpcIndex);
}

bool TestSpawnTrigger(struct WorldPos Pos, bool PuedeAgua) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (LegalPos(Pos.Map, Pos.X, Pos.Y, PuedeAgua)) {
		retval = MapData[Pos.Map][Pos.X][Pos.Y].trigger != 3 && MapData[Pos.Map][Pos.X][Pos.Y].trigger != 2
				&& MapData[Pos.Map][Pos.X][Pos.Y].trigger != 1;
	}

	return retval;
}

int CrearNPC(int NroNPC, int mapa, struct WorldPos OrigPos, int CustomHead) {
	int retval = 0;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	/* 'Crea un NPC del tipo NRONPC */

	struct WorldPos Pos;
	struct WorldPos newpos;
	struct WorldPos altpos;
	int nIndex;
	bool PosicionValida = false;
	int Iteraciones = 0;
	bool PuedeAgua;
	bool PuedeTierra;

	int Map;
	int X;
	int Y;

	/* 'Conseguimos un indice */
	nIndex = OpenNPC(NroNPC);

	if (nIndex > MAXNPCS) {
		return retval;
	}

	/* ' Cabeza customizada */
	if (CustomHead != 0) {
		Npclist[nIndex].Char.Head = CustomHead;
	}

	PuedeAgua = Npclist[nIndex].flags.AguaValida;
	PuedeTierra = vb6::IIf(Npclist[nIndex].flags.TierraInvalida == 1, false, true);

	/* 'Necesita ser respawned en un lugar especifico */
	if (InMapBounds(OrigPos.Map, OrigPos.X, OrigPos.Y)) {

		Map = OrigPos.Map;
		X = OrigPos.X;
		Y = OrigPos.Y;
		Npclist[nIndex].Orig = OrigPos;
		Npclist[nIndex].Pos = OrigPos;

	} else {

		/* 'mapa */
		Pos.Map = mapa;
		altpos.Map = mapa;

		while (!PosicionValida) {
			/* 'Obtenemos posicion al azar en x */
			Pos.X = RandomNumber(MinXBorder, MaxXBorder);
			/* 'Obtenemos posicion al azar en y */
			Pos.Y = RandomNumber(MinYBorder, MaxYBorder);

			/* 'Nos devuelve la posicion valida mas cercana */
			ClosestLegalPos(Pos, newpos, PuedeAgua, PuedeTierra);
			if (newpos.X != 0 && newpos.Y != 0) {
				altpos.X = newpos.X;
				/* 'posicion alternativa (para evitar el anti respawn, pero intentando qeu si tenía que ser en el agua, sea en el agua.) */
				altpos.Y = newpos.Y;
			} else {
				ClosestLegalPos(Pos, newpos, PuedeAgua);
				if (newpos.X != 0 && newpos.Y != 0) {
					altpos.X = newpos.X;
					/* 'posicion alternativa (para evitar el anti respawn) */
					altpos.Y = newpos.Y;
				}
			}
			/* 'Si X e Y son iguales a 0 significa que no se encontro posicion valida */
			if (LegalPosNPC(newpos.Map, newpos.X, newpos.Y, PuedeAgua) && !HayPCarea(newpos)
					&& TestSpawnTrigger(newpos, PuedeAgua)) {
				/* 'Asignamos las nuevas coordenas solo si son validas */
				Npclist[nIndex].Pos.Map = newpos.Map;
				Npclist[nIndex].Pos.X = newpos.X;
				Npclist[nIndex].Pos.Y = newpos.Y;
				PosicionValida = true;
			} else {
				newpos.X = 0;
				newpos.Y = 0;

			}

			/* 'for debug */
			Iteraciones = Iteraciones + 1;
			if (Iteraciones > MAXSPAWNATTEMPS) {
				if (altpos.X != 0 && altpos.Y != 0) {
					Map = altpos.Map;
					X = altpos.X;
					Y = altpos.Y;
					Npclist[nIndex].Pos.Map = Map;
					Npclist[nIndex].Pos.X = X;
					Npclist[nIndex].Pos.Y = Y;
					MakeNPCChar(true, Map, nIndex, Map, X, Y);
					return retval;
				} else {
					altpos.X = 50;
					altpos.Y = 50;
					ClosestLegalPos(altpos, newpos);
					if (newpos.X != 0 && newpos.Y != 0) {
						Npclist[nIndex].Pos.Map = newpos.Map;
						Npclist[nIndex].Pos.X = newpos.X;
						Npclist[nIndex].Pos.Y = newpos.Y;
						MakeNPCChar(true, newpos.Map, nIndex, newpos.Map, newpos.X, newpos.Y);
						return retval;
					} else {
						QuitarNPC(nIndex);
						LogError(
								vb6::CStr(MAXSPAWNATTEMPS) + " iteraciones en CrearNpc Mapa:" + vb6::CStr(mapa) + " NroNpc:"
										+ vb6::CStr(NroNPC));
						return retval;
					}
				}
			}
		}

		/* 'asignamos las nuevas coordenas */
		Map = newpos.Map;
		X = Npclist[nIndex].Pos.X;
		Y = Npclist[nIndex].Pos.Y;
	}

	/* 'Crea el NPC */
	MakeNPCChar(true, Map, nIndex, Map, X, Y);

	retval = nIndex;

	return retval;
}

void MakeNPCChar(bool toMap, int sndIndex, int NpcIndex, int Map, int X, int Y) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int CharIndex;

	if (Npclist[NpcIndex].Char.CharIndex == 0) {
		CharIndex = NextOpenCharIndex();
		Npclist[NpcIndex].Char.CharIndex = CharIndex;
		CharList[CharIndex] = NpcIndex;
	}

	MapData[Map][X][Y].NpcIndex = NpcIndex;

	if (!toMap) {
		WriteCharacterCreate(sndIndex, Npclist[NpcIndex].Char.body, Npclist[NpcIndex].Char.Head,
				Npclist[NpcIndex].Char.heading, Npclist[NpcIndex].Char.CharIndex, X, Y, 0, 0, 0, 0, 0, "", 0,
				0);
		FlushBuffer(sndIndex);
	} else {
		AgregarNpc(NpcIndex);
	}
}

void ChangeNPCChar(int NpcIndex, int body, int Head, eHeading heading) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (NpcIndex > 0) {
		Npclist[NpcIndex].Char.body = body;
		Npclist[NpcIndex].Char.Head = Head;
		Npclist[NpcIndex].Char.heading = heading;

		SendData(SendTarget_ToNPCArea, NpcIndex,
				dakara::protocol::server::BuildCharacterChange(Npclist[NpcIndex].Char.CharIndex, body, Head, heading, 0, 0, 0,
						0, 0));
	}
}

void EraseNPCChar(int NpcIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (Npclist[NpcIndex].Char.CharIndex != 0) {
		CharList[Npclist[NpcIndex].Char.CharIndex] = 0;
	}

	if (Npclist[NpcIndex].Char.CharIndex == LastChar) {
		while (!(CharList[LastChar] > 0)) {
			LastChar = LastChar - 1;
			if (LastChar <= 1) {
				break;
			}
		}
	}

	/* 'Quitamos del mapa */
	MapData[Npclist[NpcIndex].Pos.Map][Npclist[NpcIndex].Pos.X][Npclist[NpcIndex].Pos.Y].NpcIndex = 0;

	/* 'Actualizamos los clientes */
	SendData(SendTarget_ToNPCArea, NpcIndex,
			dakara::protocol::server::BuildCharacterRemove(Npclist[NpcIndex].Char.CharIndex));

	/* 'Update la lista npc */
	Npclist[NpcIndex].Char.CharIndex = 0;

	/* 'update NumChars */
	NumChars = NumChars - 1;

}

bool MoveNPCChar(int NpcIndex, int nHeading) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Autor: Unknown (orginal version) */
	/* 'Last Modification: 06/04/2009 */
	/* '06/04/2009: ZaMa - Now npcs can force to change position with dead character */
	/* '01/08/2009: ZaMa - Now npcs can't force to chance position with a dead character if that means to change the terrain the character is in */
	/* '26/09/2010: ZaMa - Turn sub into function to know if npc has moved or not. */
	/* '*************************************************** */

	/* FIXME: ON ERROR GOTO errh */

	struct WorldPos nPos;
	int UserIndex;

	nPos = Npclist[NpcIndex].Pos;
	HeadtoPos(static_cast<eHeading>(nHeading), nPos);

	/* ' es una posicion legal */
	if (LegalPosNPC(nPos.Map, nPos.X, nPos.Y, Npclist[NpcIndex].flags.AguaValida == 1,
			Npclist[NpcIndex].MaestroUser != 0)) {

		if (Npclist[NpcIndex].flags.AguaValida == 0 && HayAgua(Npclist[NpcIndex].Pos.Map, nPos.X, nPos.Y)) {
			return retval;
		}
		if (Npclist[NpcIndex].flags.TierraInvalida == 1
				&& !HayAgua(Npclist[NpcIndex].Pos.Map, nPos.X, nPos.Y)) {
			return retval;
		}

		UserIndex = MapData[Npclist[NpcIndex].Pos.Map][nPos.X][nPos.Y].UserIndex;
		/* ' Si hay un usuario a donde se mueve el npc, entonces esta muerto */
		if (UserIndex > 0) {

			/* ' No se traslada caspers de agua a tierra */
			if (HayAgua(Npclist[NpcIndex].Pos.Map, nPos.X, nPos.Y)
					&& !HayAgua(Npclist[NpcIndex].Pos.Map, Npclist[NpcIndex].Pos.X,
							Npclist[NpcIndex].Pos.Y)) {
				return retval;
			}
			/* ' No se traslada caspers de tierra a agua */
			if (!HayAgua(Npclist[NpcIndex].Pos.Map, nPos.X, nPos.Y)
					&& HayAgua(Npclist[NpcIndex].Pos.Map, Npclist[NpcIndex].Pos.X, Npclist[NpcIndex].Pos.Y)) {
				return retval;
			}

			/* ' Actualizamos posicion y mapa */
			MapData[UserList[UserIndex].Pos.Map][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].UserIndex =
					0;
			UserList[UserIndex].Pos.X = Npclist[NpcIndex].Pos.X;
			UserList[UserIndex].Pos.Y = Npclist[NpcIndex].Pos.Y;
			MapData[UserList[UserIndex].Pos.Map][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].UserIndex =
					UserIndex;

			/* ' Avisamos a los usuarios del area, y al propio usuario lo forzamos a moverse */
			SendData(SendTarget_ToPCAreaButIndex, UserIndex,
					dakara::protocol::server::BuildCharacterMove(UserList[UserIndex].Char.CharIndex, UserList[UserIndex].Pos.X,
							UserList[UserIndex].Pos.Y));
			WriteForceCharMove(UserIndex, InvertHeading(static_cast<eHeading>(nHeading)));
		}

		SendData(SendTarget_ToNPCArea, NpcIndex,
				dakara::protocol::server::BuildCharacterMove(Npclist[NpcIndex].Char.CharIndex, nPos.X, nPos.Y));

		/* 'Update map and user pos */
		MapData[Npclist[NpcIndex].Pos.Map][Npclist[NpcIndex].Pos.X][Npclist[NpcIndex].Pos.Y].NpcIndex = 0;
		Npclist[NpcIndex].Pos = nPos;
		Npclist[NpcIndex].Char.heading = static_cast<eHeading>(nHeading);
		MapData[Npclist[NpcIndex].Pos.Map][nPos.X][nPos.Y].NpcIndex = NpcIndex;
		CheckUpdateNeededNpc(NpcIndex, nHeading);

		/* ' Npc has moved */
		retval = true;

	} else if (Npclist[NpcIndex].MaestroUser == 0) {
		if (Npclist[NpcIndex].Movement == TipoAI_NpcPathfinding) {
			/* 'Someone has blocked the npc's way, we must to seek a new path! */
			if (nHeading != eHeading_None) {
				Npclist[NpcIndex].PFINFO.PathLenght = 0;
			}
		}
	}

	return retval;
}

int NextOpenNPC() {
	int retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int LoopC;

	// FIXME: Busqueda lineal!!

	for (LoopC = (1); LoopC <= (MAXNPCS + 1); LoopC++) {
		if (LoopC > MAXNPCS) {
			break;
		}
		if (!Npclist[LoopC].flags.NPCActive) {
			break;
		}
	}

	retval = LoopC;
	return retval;
}

void NpcEnvenenarUser(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 10/07/2010 */
	/* '10/07/2010: ZaMa - Now npcs can't poison dead users. */
	/* '*************************************************** */

	int N;

	if (UserList[UserIndex].flags.Muerto == 1) {
		return;
	}

	N = RandomNumber(1, 100);
	if (N < 30) {
		UserList[UserIndex].flags.Envenenado = 1;
		WriteConsoleMsg(UserIndex, "¡¡La criatura te ha envenenado!!", FontTypeNames_FONTTYPE_FIGHT);
	}

}

int SpawnNpc(int NpcIndex, struct WorldPos Pos, bool FX, bool Respawn) {
	int retval;
	/* '*************************************************** */
	/* 'Autor: Unknown (orginal version) */
	/* 'Last Modification: 06/15/2008 */
	/* '23/01/2007 -> Pablo (ToxicWaste): Creates an NPC of the type Npcindex */
	/* '06/15/2008 -> Optimizé el codigo. (NicoNZ) */
	/* '*************************************************** */
	struct WorldPos newpos;
	struct WorldPos altpos;
	int nIndex;
	bool PosicionValida;
	bool PuedeAgua;
	bool PuedeTierra;

	int Map;
	int X;
	int Y;

	/* 'Conseguimos un indice */
	nIndex = OpenNPC(NpcIndex, Respawn);

	if (nIndex > MAXNPCS) {
		retval = 0;
		return retval;
	}

	PuedeAgua = Npclist[nIndex].flags.AguaValida;
	PuedeTierra = Npclist[nIndex].flags.TierraInvalida != 1;

	/* 'Nos devuelve la posicion valida mas cercana */
	ClosestLegalPos(Pos, newpos, PuedeAgua, PuedeTierra);
	ClosestLegalPos(Pos, altpos, PuedeAgua);
	/* 'Si X e Y son iguales a 0 significa que no se encontro posicion valida */

	if (newpos.X != 0 && newpos.Y != 0) {
		/* 'Asignamos las nuevas coordenas solo si son validas */
		Npclist[nIndex].Pos.Map = newpos.Map;
		Npclist[nIndex].Pos.X = newpos.X;
		Npclist[nIndex].Pos.Y = newpos.Y;
		PosicionValida = true;
	} else {
		if (altpos.X != 0 && altpos.Y != 0) {
			Npclist[nIndex].Pos.Map = altpos.Map;
			Npclist[nIndex].Pos.X = altpos.X;
			Npclist[nIndex].Pos.Y = altpos.Y;
			PosicionValida = true;
		} else {
			PosicionValida = false;
		}
	}

	if (!PosicionValida) {
		QuitarNPC(nIndex);
		retval = 0;
		return retval;
	}

	/* 'asignamos las nuevas coordenas */
	Map = newpos.Map;
	X = Npclist[nIndex].Pos.X;
	Y = Npclist[nIndex].Pos.Y;

	/* 'Crea el NPC */
	MakeNPCChar(true, Map, nIndex, Map, X, Y);

	if (FX) {
		SendData(SendTarget_ToNPCArea, nIndex,
				dakara::protocol::server::BuildPlayWave(SND_WARP, X, Y));
		SendData(SendTarget_ToNPCArea, nIndex,
				dakara::protocol::server::BuildCreateFX(Npclist[nIndex].Char.CharIndex, FXIDs_FXWARP, 0));
	}

	retval = nIndex;

	return retval;
}

void ReSpawnNpc(const struct npc &MiNPC) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (MiNPC.flags.Respawn == 0) {
		CrearNPC(MiNPC.Numero, MiNPC.Pos.Map, MiNPC.Orig);
	}

}

void NPCTirarOro(struct npc & MiNPC) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	/* 'SI EL NPC TIENE ORO LO TIRAMOS */
	if (MiNPC.GiveGLD > 0) {
		struct Obj MiObj;
		int MiAux;
		MiAux = MiNPC.GiveGLD;
		while (MiAux > MAX_INVENTORY_OBJS) {
			MiObj.Amount = MAX_INVENTORY_OBJS;
			MiObj.ObjIndex = iORO;
			TirarItemAlPiso(MiNPC.Pos, MiObj);
			MiAux = MiAux - MAX_INVENTORY_OBJS;
		}
		if (MiAux > 0) {
			MiObj.Amount = MiAux;
			MiObj.ObjIndex = iORO;
			TirarItemAlPiso(MiNPC.Pos, MiObj);
		}
	}
}

int OpenNPC(int NpcNumber, bool Respawn) {
	int retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int NpcIndex;
	std::shared_ptr<clsIniManager> Leer;
	int LoopC;
	std::string ln;

	Leer = (LeerNPCs);

	std::string npcSect = "NPC" + vb6::CStr(NpcNumber);

	/* 'If requested index is invalid, abort */
	if (!Leer->KeyExists(npcSect)) {
		retval = MAXNPCS + 1;
		return retval;
	}

	NpcIndex = NextOpenNPC();

	/* 'Limite de npcs */
	if (NpcIndex > MAXNPCS) {
		retval = NpcIndex;
		return retval;
	}

	Npclist[NpcIndex].Numero = NpcNumber;
	Npclist[NpcIndex].Name = Leer->GetValue(npcSect, "Name");
	Npclist[NpcIndex].desc = Leer->GetValue(npcSect, "Desc");

	Npclist[NpcIndex].Movement = static_cast<TipoAI>(vb6::CInt(Leer->GetValue(npcSect, "Movement")));
	Npclist[NpcIndex].flags.OldMovement = Npclist[NpcIndex].Movement;

	Npclist[NpcIndex].flags.AguaValida = vb6::val(Leer->GetValue(npcSect, "AguaValida"));
	Npclist[NpcIndex].flags.TierraInvalida = vb6::val(Leer->GetValue(npcSect, "TierraInValida"));
	Npclist[NpcIndex].flags.Faccion = vb6::val(Leer->GetValue(npcSect, "Faccion"));
	Npclist[NpcIndex].flags.AtacaDoble = vb6::val(Leer->GetValue(npcSect, "AtacaDoble"));

	Npclist[NpcIndex].NPCtype = static_cast<eNPCType>(vb6::CInt(Leer->GetValue(npcSect, "NpcType")));

	Npclist[NpcIndex].Char.body = vb6::val(Leer->GetValue(npcSect, "Body"));
	Npclist[NpcIndex].Char.Head = vb6::val(Leer->GetValue(npcSect, "Head"));
	Npclist[NpcIndex].Char.heading = static_cast<eHeading>(vb6::CInt(Leer->GetValue(npcSect, "Heading")));

	Npclist[NpcIndex].Attackable = vb6::val(Leer->GetValue(npcSect, "Attackable"));
	Npclist[NpcIndex].Comercia = vb6::val(Leer->GetValue(npcSect, "Comercia"));
	Npclist[NpcIndex].Hostile = vb6::val(Leer->GetValue(npcSect, "Hostile"));
	Npclist[NpcIndex].flags.OldHostil = Npclist[NpcIndex].Hostile;

	Npclist[NpcIndex].GiveEXP = vb6::val(Leer->GetValue(npcSect, "GiveEXP"));
	if (HappyHourActivated && (HappyHour != 0)) {
		Npclist[NpcIndex].GiveEXP = Npclist[NpcIndex].GiveEXP * HappyHour;
	}

	Npclist[NpcIndex].flags.ExpCount = Npclist[NpcIndex].GiveEXP;

	Npclist[NpcIndex].Veneno = vb6::val(Leer->GetValue(npcSect, "Veneno"));

	Npclist[NpcIndex].flags.Domable = vb6::val(Leer->GetValue(npcSect, "Domable"));

	Npclist[NpcIndex].GiveGLD = vb6::val(Leer->GetValue(npcSect, "GiveGLD"));

	Npclist[NpcIndex].PoderAtaque = vb6::val(Leer->GetValue(npcSect, "PoderAtaque"));
	Npclist[NpcIndex].PoderEvasion = vb6::val(Leer->GetValue(npcSect, "PoderEvasion"));

	Npclist[NpcIndex].InvReSpawn = vb6::val(Leer->GetValue(npcSect, "InvReSpawn"));

	Npclist[NpcIndex].Stats.MaxHp = vb6::val(Leer->GetValue(npcSect, "MaxHP"));
	Npclist[NpcIndex].Stats.MinHp = vb6::val(Leer->GetValue(npcSect, "MinHP"));
	Npclist[NpcIndex].Stats.MaxHIT = vb6::val(Leer->GetValue(npcSect, "MaxHIT"));
	Npclist[NpcIndex].Stats.MinHIT = vb6::val(Leer->GetValue(npcSect, "MinHIT"));
	Npclist[NpcIndex].Stats.def = vb6::val(Leer->GetValue(npcSect, "DEF"));
	Npclist[NpcIndex].Stats.defM = vb6::val(Leer->GetValue(npcSect, "DEFm"));
	Npclist[NpcIndex].Stats.Alineacion = vb6::val(Leer->GetValue(npcSect, "Alineacion"));

	Npclist[NpcIndex].Invent.NroItems = vb6::Constrain(vb6::CInt(Leer->GetValue(npcSect, "NROITEMS")), 0, MAX_DAT_ITEMS);
	for (LoopC = (1); LoopC <= (Npclist[NpcIndex].Invent.NroItems); LoopC++) {
		ln = Leer->GetValue(npcSect, "Obj" + vb6::CStr(LoopC));
		Npclist[NpcIndex].Invent.Object[LoopC].ObjIndex = vb6::val(ReadField(1, ln, 45));
		Npclist[NpcIndex].Invent.Object[LoopC].Amount = vb6::val(ReadField(2, ln, 45));
	}

	for (LoopC = (1); LoopC <= (MAX_NPC_DROPS); LoopC++) {
		ln = Leer->GetValue(npcSect, "Drop" + vb6::CStr(LoopC));
		Npclist[NpcIndex].Drop[LoopC].ObjIndex = vb6::val(ReadField(1, ln, 45));
		Npclist[NpcIndex].Drop[LoopC].Amount = vb6::val(ReadField(2, ln, 45));
	}

	Npclist[NpcIndex].flags.LanzaSpells = vb6::Constrain(vb6::CInt(Leer->GetValue(npcSect, "LanzaSpells")), 0, MAXUSERHECHIZOS);
	if (Npclist[NpcIndex].flags.LanzaSpells > 0) {
		Npclist[NpcIndex].Spells.redim(0);
		Npclist[NpcIndex].Spells.redim(1, Npclist[NpcIndex].flags.LanzaSpells);
	}
	for (LoopC = (1); LoopC <= (Npclist[NpcIndex].flags.LanzaSpells); LoopC++) {
		Npclist[NpcIndex].Spells[LoopC] = vb6::val(Leer->GetValue(npcSect, "Sp" + vb6::CStr(LoopC)));
	}

	if (Npclist[NpcIndex].NPCtype == eNPCType_Entrenador) {
		Npclist[NpcIndex].NroCriaturas = vb6::Constrain(vb6::CInt(Leer->GetValue(npcSect, "NroCriaturas")), 0, MAX_CRIATURAS_ENTRENADOR);
		Npclist[NpcIndex].Criaturas.redim(0);
		Npclist[NpcIndex].Criaturas.redim(1, Npclist[NpcIndex].NroCriaturas);
		for (LoopC = (1); LoopC <= (Npclist[NpcIndex].NroCriaturas); LoopC++) {
			Npclist[NpcIndex].Criaturas[LoopC].NpcIndex = vb6::CInt(Leer->GetValue(npcSect, "CI" + vb6::CStr(LoopC)));
			Npclist[NpcIndex].Criaturas[LoopC].NpcName = Leer->GetValue(npcSect, "CN" + vb6::CStr(LoopC));
		}
	}

	Npclist[NpcIndex].flags.NPCActive = true;

	if (Respawn) {
		Npclist[NpcIndex].flags.Respawn = vb6::val(Leer->GetValue(npcSect, "ReSpawn"));
	} else {
		Npclist[NpcIndex].flags.Respawn = 1;
	}

	Npclist[NpcIndex].flags.BackUp = vb6::val(Leer->GetValue(npcSect, "BackUp"));
	Npclist[NpcIndex].flags.RespawnOrigPos = vb6::val(Leer->GetValue(npcSect, "OrigPos"));
	Npclist[NpcIndex].flags.AfectaParalisis = vb6::val(Leer->GetValue(npcSect, "AfectaParalisis"));

	Npclist[NpcIndex].flags.Snd1 = vb6::val(Leer->GetValue(npcSect, "Snd1"));
	Npclist[NpcIndex].flags.Snd2 = vb6::val(Leer->GetValue(npcSect, "Snd2"));
	Npclist[NpcIndex].flags.Snd3 = vb6::val(Leer->GetValue(npcSect, "Snd3"));

	/* '<<<<<<<<<<<<<< Expresiones >>>>>>>>>>>>>>>> */
	Npclist[NpcIndex].NroExpresiones = vb6::val(Leer->GetValue(npcSect, "NROEXP"));
	Npclist[NpcIndex].NroExpresiones = vb6::Constrain(Npclist[NpcIndex].NroExpresiones, 0, MAX_EXPRESIONES);
	
	if (Npclist[NpcIndex].NroExpresiones > 0) {
		Npclist[NpcIndex].Expresiones.redim(0);
		Npclist[NpcIndex].Expresiones.redim(1, Npclist[NpcIndex].NroExpresiones);
	}
	for (LoopC = (1); LoopC <= (Npclist[NpcIndex].NroExpresiones); LoopC++) {
		Npclist[NpcIndex].Expresiones[LoopC] = Leer->GetValue(npcSect, "Exp" + vb6::CStr(LoopC));
	}
	/* '<<<<<<<<<<<<<< Expresiones >>>>>>>>>>>>>>>> */

	/* 'Tipo de items con los que comercia */
	Npclist[NpcIndex].TipoItems = vb6::val(Leer->GetValue(npcSect, "TipoItems"));

	Npclist[NpcIndex].Ciudad = vb6::val(Leer->GetValue(npcSect, "Ciudad"));

	/* 'Update contadores de NPCs */
	if (NpcIndex > LastNPC) {
		LastNPC = NpcIndex;
	}
	NumNPCs = NumNPCs + 1;

	/* 'Devuelve el nuevo Indice */
	retval = NpcIndex;
	return retval;
}

void DoFollow(int NpcIndex, std::string UserName) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (Npclist[NpcIndex].flags.Follow) {
		Npclist[NpcIndex].flags.AttackedBy = "";
		Npclist[NpcIndex].flags.Follow = false;
		Npclist[NpcIndex].Movement = Npclist[NpcIndex].flags.OldMovement;
		Npclist[NpcIndex].Hostile = Npclist[NpcIndex].flags.OldHostil;
	} else {
		Npclist[NpcIndex].flags.AttackedBy = UserName;
		Npclist[NpcIndex].flags.Follow = true;
		Npclist[NpcIndex].Movement = TipoAI_NPCDEFENSA;
		Npclist[NpcIndex].Hostile = 0;
	}
}

void FollowAmo(int NpcIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	Npclist[NpcIndex].flags.Follow = true;
	Npclist[NpcIndex].Movement = TipoAI_SigueAmo;
	Npclist[NpcIndex].Hostile = 0;
	Npclist[NpcIndex].Target = 0;
	Npclist[NpcIndex].TargetNPC = 0;
}

void ValidarPermanenciaNpc(int NpcIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* 'Chequea si el npc continua perteneciendo a algún usuario */
	/* '*************************************************** */

	if (IntervaloPerdioNpc(Npclist[NpcIndex].Owner)) {
		PerdioNpc(Npclist[NpcIndex].Owner);
	}
}
