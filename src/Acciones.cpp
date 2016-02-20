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

#include "Acciones.h"

/* '' */
/* ' Modulo para manejar las acciones (doble click) de los carteles, foro, puerta, ramitas */
/* ' */

/* '' */
/* ' Ejecuta la accion del doble click */
/* ' */
/* ' @param UserIndex UserIndex */
/* ' @param Map Numero de mapa */
/* ' @param X X */
/* ' @param Y Y */

void Accion(int UserIndex, int Map, int X, int Y) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int tempIndex;

	/* FIXME: ON ERROR RESUME NEXT */
	/* '¿Rango Visión? (ToxicWaste) */
	if ((vb6::Abs(UserList[UserIndex].Pos.Y - Y) > RANGO_VISION_Y)
			|| (vb6::Abs(UserList[UserIndex].Pos.X - X) > RANGO_VISION_X)) {
		return;
	}

	/* '¿Posicion valida? */
	if (InMapBounds(Map, X, Y)) {
		/* 'Acciones NPCs */
		if (MapData[Map][X][Y].NpcIndex > 0) {
			tempIndex = MapData[Map][X][Y].NpcIndex;

			/* 'Set the target NPC */
			UserList[UserIndex].flags.TargetNPC = tempIndex;

			if (Npclist[tempIndex].Comercia == 1) {
				/* '¿Esta el user muerto? Si es asi no puede comerciar */
				if (UserList[UserIndex].flags.Muerto == 1) {
					WriteConsoleMsg(UserIndex, "¡¡Estás muerto!!",
							FontTypeNames_FONTTYPE_INFO);
					return;
				}

				/* 'Is it already in commerce mode?? */
				if (UserList[UserIndex].flags.Comerciando) {
					return;
				}

				if (Distancia(Npclist[tempIndex].Pos, UserList[UserIndex].Pos)
						> 3) {
					WriteConsoleMsg(UserIndex,
							"Estás demasiado lejos del vendedor.",
							FontTypeNames_FONTTYPE_INFO);
					return;
				}

				/* 'Iniciamos la rutina pa' comerciar. */
				IniciarComercioNPC(UserIndex);

			} else if (Npclist[tempIndex].NPCtype == eNPCType_Banquero) {
				/* '¿Esta el user muerto? Si es asi no puede comerciar */
				if (UserList[UserIndex].flags.Muerto == 1) {
					WriteConsoleMsg(UserIndex, "¡¡Estás muerto!!",
							FontTypeNames_FONTTYPE_INFO);
					return;
				}

				/* 'Is it already in commerce mode?? */
				if (UserList[UserIndex].flags.Comerciando) {
					return;
				}

				if (Distancia(Npclist[tempIndex].Pos, UserList[UserIndex].Pos)
						> 3) {
					WriteConsoleMsg(UserIndex,
							"Estás demasiado lejos del vendedor.",
							FontTypeNames_FONTTYPE_INFO);
					return;
				}

				/* 'A depositar de una */
				IniciarDeposito(UserIndex);

			} else if (Npclist[tempIndex].NPCtype == eNPCType_Revividor
					|| Npclist[tempIndex].NPCtype
							== eNPCType_ResucitadorNewbie) {
				if (Distancia(UserList[UserIndex].Pos, Npclist[tempIndex].Pos)
						> 10) {
					WriteConsoleMsg(UserIndex,
							"El sacerdote no puede curarte debido a que estás demasiado lejos.",
							FontTypeNames_FONTTYPE_INFO);
					return;
				}

				/* 'Revivimos si es necesario */
				if (UserList[UserIndex].flags.Muerto == 1
						&& (Npclist[tempIndex].NPCtype == eNPCType_Revividor
								|| EsNewbie(UserIndex))) {
					RevivirUsuario(UserIndex);
				}

				if (Npclist[tempIndex].NPCtype == eNPCType_Revividor
						|| EsNewbie(UserIndex)) {
					/* 'curamos totalmente */
					UserList[UserIndex].Stats.MinHp =
							UserList[UserIndex].Stats.MaxHp;
					WriteUpdateUserStats(UserIndex);
				}
			}

			/* '¿Es un obj? */
		} else if (MapData[Map][X][Y].ObjInfo.ObjIndex > 0) {
			tempIndex = MapData[Map][X][Y].ObjInfo.ObjIndex;

			UserList[UserIndex].flags.TargetObj = tempIndex;

			switch (ObjData[tempIndex].OBJType) {
			/* 'Es una puerta */
			case eOBJType_otPuertas:
				AccionParaPuerta(Map, X, Y, UserIndex);
				/* 'Es un cartel */
				break;

			case eOBJType_otCarteles:
				AccionParaCartel(Map, X, Y, UserIndex);
				/* 'Foro */
				break;

			case eOBJType_otForos:
				AccionParaForo(Map, X, Y, UserIndex);
				/* 'Lena */
				break;

			case eOBJType_otLena:
				if (tempIndex == FOGATA_APAG
						&& UserList[UserIndex].flags.Muerto == 0) {
					AccionParaRamita(Map, X, Y, UserIndex);
				}
				break;

			default:
				break;
			}
			/* '>>>>>>>>>>>OBJETOS QUE OCUPAM MAS DE UN TILE<<<<<<<<<<<<< */
		} else if (MapData[Map][X + 1][Y].ObjInfo.ObjIndex > 0) {
			tempIndex = MapData[Map][X + 1][Y].ObjInfo.ObjIndex;
			UserList[UserIndex].flags.TargetObj = tempIndex;

			switch (ObjData[tempIndex].OBJType) {

			/* 'Es una puerta */
			case eOBJType_otPuertas:
				AccionParaPuerta(Map, X + 1, Y, UserIndex);

				break;

			default:
				break;
			}

		} else if (MapData[Map][X + 1][Y + 1].ObjInfo.ObjIndex > 0) {
			tempIndex = MapData[Map][X + 1][Y + 1].ObjInfo.ObjIndex;
			UserList[UserIndex].flags.TargetObj = tempIndex;

			switch (ObjData[tempIndex].OBJType) {
			/* 'Es una puerta */
			case eOBJType_otPuertas:
				AccionParaPuerta(Map, X + 1, Y + 1, UserIndex);
				break;
			default:
				break;
			}

		} else if (MapData[Map][X][Y + 1].ObjInfo.ObjIndex > 0) {
			tempIndex = MapData[Map][X][Y + 1].ObjInfo.ObjIndex;
			UserList[UserIndex].flags.TargetObj = tempIndex;

			switch (ObjData[tempIndex].OBJType) {
			/* 'Es una puerta */
			case eOBJType_otPuertas:
				AccionParaPuerta(Map, X, Y + 1, UserIndex);
				break;
			default:
				break;
			}
		}
	}
}

void AccionParaForo(int Map, int X, int Y, int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 02/01/2010 */
	/* '02/01/2010: ZaMa - Agrego foros faccionarios */
	/* '*************************************************** */

	/* FIXME: ON ERROR RESUME NEXT */

	struct WorldPos Pos;

	Pos.Map = Map;
	Pos.X = X;
	Pos.Y = Y;

	if (Distancia(Pos, UserList[UserIndex].Pos) > 2) {
		WriteConsoleMsg(UserIndex, "Estas demasiado lejos.",
				FontTypeNames_FONTTYPE_INFO);
		return;
	}

	if (SendPosts(UserIndex,
			ObjData[MapData[Map][X][Y].ObjInfo.ObjIndex].ForoID)) {
		WriteShowForumForm(UserIndex);
	}

}

void AccionParaPuerta(int Map, int X, int Y, int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	/* FIXME: ON ERROR RESUME NEXT */

	if (!(Distance(UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y, X, Y)
			> 2)) {
		if (ObjData[MapData[Map][X][Y].ObjInfo.ObjIndex].Llave == 0) {
			if (ObjData[MapData[Map][X][Y].ObjInfo.ObjIndex].Cerrada == 1) {
				/* 'Abre la puerta */
				if (ObjData[MapData[Map][X][Y].ObjInfo.ObjIndex].Llave == 0) {

					MapData[Map][X][Y].ObjInfo.ObjIndex =
							ObjData[MapData[Map][X][Y].ObjInfo.ObjIndex].IndexAbierta;

					SendToAreaByPos(Map, X, Y,
							PacketToString(
									dakara::protocol::server::BuildObjectCreate(
											X, Y,
											ObjData[MapData[Map][X][Y].ObjInfo.ObjIndex].GrhIndex)));
					/* 'Desbloquea */
					MapData[Map][X][Y].Blocked = 0;
					MapData[Map][X - 1][Y].Blocked = 0;

					/* 'Bloquea todos los mapas */
					Bloquear(true, Map, X, Y, 0);
					Bloquear(true, Map, X - 1, Y, 0);

					/* 'Sonido */
					auto msg = dakara::protocol::server::BuildPlayWave(SND_PUERTA, X, Y);
					SendData(SendTarget_ToPCArea, UserIndex, msg);

				} else {
					WriteConsoleMsg(UserIndex,
							"La puerta esta cerrada con llave.",
							FontTypeNames_FONTTYPE_INFO);
				}
			} else {
				/* 'Cierra puerta */
				MapData[Map][X][Y].ObjInfo.ObjIndex =
						ObjData[MapData[Map][X][Y].ObjInfo.ObjIndex].IndexCerrada;

				SendToAreaByPos(Map, X, Y,
						PacketToString(
								dakara::protocol::server::BuildObjectCreate(X,
										Y,
										ObjData[MapData[Map][X][Y].ObjInfo.ObjIndex].GrhIndex)));
				MapData[Map][X][Y].Blocked = 1;
				MapData[Map][X - 1][Y].Blocked = 1;

				Bloquear(true, Map, X - 1, Y, 1);
				Bloquear(true, Map, X, Y, 1);

				auto msg = dakara::protocol::server::BuildPlayWave(SND_PUERTA, X, Y);
				SendData(SendTarget_ToPCArea, UserIndex, msg);
			}

			UserList[UserIndex].flags.TargetObj =
					MapData[Map][X][Y].ObjInfo.ObjIndex;
		} else {
			WriteConsoleMsg(UserIndex, "La puerta está cerrada con llave.",
					FontTypeNames_FONTTYPE_INFO);
		}
	} else {
		WriteConsoleMsg(UserIndex, "Estás demasiado lejos.",
				FontTypeNames_FONTTYPE_INFO);
	}

}

void AccionParaCartel(int Map, int X, int Y, int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	/* FIXME: ON ERROR RESUME NEXT */

	if (ObjData[MapData[Map][X][Y].ObjInfo.ObjIndex].OBJType == 8) {

		if (vb6::Len(ObjData[MapData[Map][X][Y].ObjInfo.ObjIndex].texto) > 0) {
			WriteShowSignal(UserIndex, MapData[Map][X][Y].ObjInfo.ObjIndex);
		}

	}

}

void AccionParaRamita(int Map, int X, int Y, int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	/* FIXME: ON ERROR RESUME NEXT */

	int Suerte;
	int exito;
	struct Obj Obj;

	int SkillSupervivencia;

	struct WorldPos Pos;
	Pos.Map = Map;
	Pos.X = X;
	Pos.Y = Y;

	if (Distancia(Pos, UserList[UserIndex].Pos) > 2) {
		WriteConsoleMsg(UserIndex, "Estás demasiado lejos.",
				FontTypeNames_FONTTYPE_INFO);
		return;
	}

	if (MapData[Map][X][Y].trigger == eTrigger_ZONASEGURA
			|| MapInfo[Map].Pk == false) {
		WriteConsoleMsg(UserIndex, "No puedes hacer fogatas en zona segura.",
				FontTypeNames_FONTTYPE_INFO);
		return;
	}

	SkillSupervivencia =
			UserList[UserIndex].Stats.UserSkills[eSkill_Supervivencia];

	if (SkillSupervivencia < 6) {
		Suerte = 3;

	} else if (SkillSupervivencia <= 10) {
		Suerte = 2;

	} else {
		Suerte = 1;
	}

	exito = RandomNumber(1, Suerte);

	if (exito == 1) {
		if (MapInfo[UserList[UserIndex].Pos.Map].Zona != Ciudad) {
			Obj.ObjIndex = FOGATA;
			Obj.Amount = 1;

			WriteConsoleMsg(UserIndex, "Has prendido la fogata.",
					FontTypeNames_FONTTYPE_INFO);

			MakeObj(Obj, Map, X, Y);

			/* 'Las fogatas prendidas se deben eliminar */
			WorldPos Fogatita;
			Fogatita.Map = Map;
			Fogatita.X = X;
			Fogatita.Y = Y;
			TrashCollector.insert(Fogatita);

			SubirSkill(UserIndex, eSkill_Supervivencia, true);
		} else {
			WriteConsoleMsg(UserIndex,
					"La ley impide realizar fogatas en las ciudades.",
					FontTypeNames_FONTTYPE_INFO);
			return;
		}
	} else {
		WriteConsoleMsg(UserIndex, "No has podido hacer fuego.",
				FontTypeNames_FONTTYPE_INFO);
		SubirSkill(UserIndex, eSkill_Supervivencia, false);
	}

}
