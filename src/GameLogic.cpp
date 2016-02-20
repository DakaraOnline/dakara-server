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

#include "GameLogic.h"

bool EsNewbie(int UserIndex) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	retval = UserList[UserIndex].Stats.ELV <= LimiteNewbie;
	return retval;
}

bool esArmada(int UserIndex) {
	bool retval;
	/* '*************************************************** */
	/* 'Autor: Pablo (ToxicWaste) */
	/* 'Last Modification: 23/01/2007 */
	/* '*************************************************** */

	retval = (UserList[UserIndex].Faccion.ArmadaReal == 1);
	return retval;
}

bool esCaos(int UserIndex) {
	bool retval;
	/* '*************************************************** */
	/* 'Autor: Pablo (ToxicWaste) */
	/* 'Last Modification: 23/01/2007 */
	/* '*************************************************** */

	retval = (UserList[UserIndex].Faccion.FuerzasCaos == 1);
	return retval;
}

bool EsGm(int UserIndex) {
	return UserTienePrivilegio(UserIndex, PlayerType_Admin) ||
			 UserTienePrivilegio(UserIndex, PlayerType_Dios) ||
			 UserTienePrivilegio(UserIndex, PlayerType_SemiDios) ||
			 UserTienePrivilegio(UserIndex, PlayerType_Consejero);
}

void DoTileEvents(int UserIndex, int Map, int X, int Y) {
	/* '*************************************************** */
	/* 'Autor: Pablo (ToxicWaste) & Unknown (orginal version) */
	/* 'Last Modification: 06/03/2010 */
	/* 'Handles the Map passage of Users. Allows the existance */
	/* 'of exclusive maps for Newbies, Royal Army and Caos Legion members */
	/* 'and enables GMs to enter every map without restriction. */
	/* 'Uses: Mapinfo(map).Restringir = "NEWBIE" (newbies), "ARMADA", "CAOS", "FACCION" or "NO". */
	/* ' 06/03/2010 : Now we have 5 attemps to not fall into a map change or another teleport while going into a teleport. (Marco) */
	/* '*************************************************** */

	struct WorldPos nPos;
	bool FxFlag = false;
	int TelepRadio = 0;
	struct WorldPos DestPos;

	/* 'Controla las salidas */
	if (InMapBounds(Map, X, Y)) {
		if (MapData[Map][X][Y].ObjInfo.ObjIndex > 0) {
			FxFlag = ObjData[MapData[Map][X][Y].ObjInfo.ObjIndex].OBJType == eOBJType_otTeleport;
			TelepRadio = ObjData[MapData[Map][X][Y].ObjInfo.ObjIndex].Radio;
		}

		if (MapData[Map][X][Y].TileExit.Map > 0 && MapData[Map][X][Y].TileExit.Map <= NumMaps) {

			/* ' Es un teleport, entra en una posicion random, acorde al radio (si es 0, es pos fija) */
			/* ' We have 5 attempts to not falling into another teleport or a map exit.. If we get to the fifth attemp, */
			/* ' the teleport will act as if its radius = 0. */
			if (FxFlag && TelepRadio > 0) {
				int attemps = 0;
				bool exitMap;
				do {
					DestPos.X = MapData[Map][X][Y].TileExit.X + RandomNumber(TelepRadio * (-1), TelepRadio);
					DestPos.Y = MapData[Map][X][Y].TileExit.Y + RandomNumber(TelepRadio * (-1), TelepRadio);

					attemps = attemps + 1;

					exitMap = MapData[MapData[Map][X][Y].TileExit.Map][DestPos.X][DestPos.Y].TileExit.Map > 0
							&& MapData[MapData[Map][X][Y].TileExit.Map][DestPos.X][DestPos.Y].TileExit.Map
									<= NumMaps;
				} while (!((attemps >= 5 || exitMap == false)));

				if (attemps >= 5) {
					DestPos.X = MapData[Map][X][Y].TileExit.X;
					DestPos.Y = MapData[Map][X][Y].TileExit.Y;
				}
				/* ' Posicion fija */
			} else {
				DestPos.X = MapData[Map][X][Y].TileExit.X;
				DestPos.Y = MapData[Map][X][Y].TileExit.Y;
			}

			DestPos.Map = MapData[Map][X][Y].TileExit.Map;

			if (EsGm(UserIndex)) {
				LogGM(UserList[UserIndex].Name,
						"Utilizó un teleport hacia el mapa " + vb6::CStr(DestPos.Map) + " ("
								+ vb6::CStr(DestPos.X) + "," + vb6::CStr(DestPos.Y) + ")");
			}

			/* ' Si es un mapa que no admite muertos */
			if (MapInfo[DestPos.Map].OnDeathGoTo.Map != 0) {
				/* ' Si esta muerto no puede entrar */
				if (UserList[UserIndex].flags.Muerto == 1) {
					WriteConsoleMsg(UserIndex, "Sólo se permite entrar al mapa a los personajes vivos.",
							FontTypeNames_FONTTYPE_INFO);
					ClosestStablePos(UserList[UserIndex].Pos, nPos);

					if (nPos.X != 0 && nPos.Y != 0) {
						WarpUserChar(UserIndex, nPos.Map, nPos.X, nPos.Y, FxFlag);
					}

					return;
				}
			}

			/* '¿Es mapa de newbies? */
			if (MapInfo[DestPos.Map].Restringir == eRestrict_restrict_newbie) {
				/* '¿El usuario es un newbie? */
				if (EsNewbie(UserIndex) || EsGm(UserIndex)) {
					if (LegalPos(DestPos.Map, DestPos.X, DestPos.Y, PuedeAtravesarAgua(UserIndex))) {
						WarpUserChar(UserIndex, DestPos.Map, DestPos.X, DestPos.Y, FxFlag);
					} else {
						ClosestLegalPos(DestPos, nPos);
						if (nPos.X != 0 && nPos.Y != 0) {
							WarpUserChar(UserIndex, nPos.Map, nPos.X, nPos.Y, FxFlag);
						}
					}
					/* 'No es newbie */
				} else {
					WriteConsoleMsg(UserIndex, "Mapa exclusivo para newbies.", FontTypeNames_FONTTYPE_INFO);
					ClosestStablePos(UserList[UserIndex].Pos, nPos);

					if (nPos.X != 0 && nPos.Y != 0) {
						WarpUserChar(UserIndex, nPos.Map, nPos.X, nPos.Y, false);
					}
				}
				/* '¿Es mapa de Armadas? */
			} else if (MapInfo[DestPos.Map].Restringir == eRestrict_restrict_armada) {
				/* '¿El usuario es Armada? */
				if (esArmada(UserIndex) || EsGm(UserIndex)) {
					if (LegalPos(DestPos.Map, DestPos.X, DestPos.Y, PuedeAtravesarAgua(UserIndex))) {
						WarpUserChar(UserIndex, DestPos.Map, DestPos.X, DestPos.Y, FxFlag);
					} else {
						ClosestLegalPos(DestPos, nPos);
						if (nPos.X != 0 && nPos.Y != 0) {
							WarpUserChar(UserIndex, nPos.Map, nPos.X, nPos.Y, FxFlag);
						}
					}
					/* 'No es armada */
				} else {
					WriteConsoleMsg(UserIndex, "Mapa exclusivo para miembros del ejército real.",
							FontTypeNames_FONTTYPE_INFO);
					ClosestStablePos(UserList[UserIndex].Pos, nPos);

					if (nPos.X != 0 && nPos.Y != 0) {
						WarpUserChar(UserIndex, nPos.Map, nPos.X, nPos.Y, FxFlag);
					}
				}
				/* '¿Es mapa de Caos? */
			} else if (MapInfo[DestPos.Map].Restringir == eRestrict_restrict_caos) {
				/* '¿El usuario es Caos? */
				if (esCaos(UserIndex) || EsGm(UserIndex)) {
					if (LegalPos(DestPos.Map, DestPos.X, DestPos.Y, PuedeAtravesarAgua(UserIndex))) {
						WarpUserChar(UserIndex, DestPos.Map, DestPos.X, DestPos.Y, FxFlag);
					} else {
						ClosestLegalPos(DestPos, nPos);
						if (nPos.X != 0 && nPos.Y != 0) {
							WarpUserChar(UserIndex, nPos.Map, nPos.X, nPos.Y, FxFlag);
						}
					}
					/* 'No es caos */
				} else {
					WriteConsoleMsg(UserIndex, "Mapa exclusivo para miembros de la legión oscura.",
							FontTypeNames_FONTTYPE_INFO);
					ClosestStablePos(UserList[UserIndex].Pos, nPos);

					if (nPos.X != 0 && nPos.Y != 0) {
						WarpUserChar(UserIndex, nPos.Map, nPos.X, nPos.Y, FxFlag);
					}
				}
				/* '¿Es mapa de faccionarios? */
			} else if (MapInfo[DestPos.Map].Restringir == eRestrict_restrict_faccion) {
				/* '¿El usuario es Armada o Caos? */
				if (esArmada(UserIndex) || esCaos(UserIndex) || EsGm(UserIndex)) {
					if (LegalPos(DestPos.Map, DestPos.X, DestPos.Y, PuedeAtravesarAgua(UserIndex))) {
						WarpUserChar(UserIndex, DestPos.Map, DestPos.X, DestPos.Y, FxFlag);
					} else {
						ClosestLegalPos(DestPos, nPos);
						if (nPos.X != 0 && nPos.Y != 0) {
							WarpUserChar(UserIndex, nPos.Map, nPos.X, nPos.Y, FxFlag);
						}
					}
					/* 'No es Faccionario */
				} else {
					WriteConsoleMsg(UserIndex,
							"Solo se permite entrar al mapa si eres miembro de alguna facción.",
							FontTypeNames_FONTTYPE_INFO);
					ClosestStablePos(UserList[UserIndex].Pos, nPos);

					if (nPos.X != 0 && nPos.Y != 0) {
						WarpUserChar(UserIndex, nPos.Map, nPos.X, nPos.Y, FxFlag);
					}
				}
				/* 'No es un mapa de newbies, ni Armadas, ni Caos, ni faccionario. */
			} else {
				if (LegalPos(DestPos.Map, DestPos.X, DestPos.Y, PuedeAtravesarAgua(UserIndex))) {
					WarpUserChar(UserIndex, DestPos.Map, DestPos.X, DestPos.Y, FxFlag);
				} else {
					ClosestLegalPos(DestPos, nPos);
					if (nPos.X != 0 && nPos.Y != 0) {
						WarpUserChar(UserIndex, nPos.Map, nPos.X, nPos.Y, FxFlag);
					}
				}
			}

			/* 'Te fusite del mapa. La criatura ya no es más tuya ni te reconoce como que vos la atacaste. */
			int aN;

			aN = UserList[UserIndex].flags.AtacadoPorNpc;
			if (aN > 0) {
				Npclist[aN].Movement = Npclist[aN].flags.OldMovement;
				Npclist[aN].Hostile = Npclist[aN].flags.OldHostil;
				Npclist[aN].flags.AttackedBy = "";
			}

			aN = UserList[UserIndex].flags.NPCAtacado;
			if (aN > 0) {
				if (Npclist[aN].flags.AttackedFirstBy == UserList[UserIndex].Name) {
					Npclist[aN].flags.AttackedFirstBy = "";
				}
			}
			UserList[UserIndex].flags.AtacadoPorNpc = 0;
			UserList[UserIndex].flags.NPCAtacado = 0;
		}
	}
	return;
}

bool InRangoVision(int UserIndex, int X, int Y) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (X > UserList[UserIndex].Pos.X - MinXBorder && X < UserList[UserIndex].Pos.X + MinXBorder) {
		if (Y > UserList[UserIndex].Pos.Y - MinYBorder && Y < UserList[UserIndex].Pos.Y + MinYBorder) {
			retval = true;
			return retval;
		}
	}
	retval = false;

	return retval;
}

bool InVisionRangeAndMap(int UserIndex, struct WorldPos & OtherUserPos) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 20/11/2010 */
	/* ' */
	/* '*************************************************** */

	/* ' Same map? */
	if (UserList[UserIndex].Pos.Map != OtherUserPos.Map) {
		return retval;
	}

	/* ' In x range? */
	if (OtherUserPos.X < UserList[UserIndex].Pos.X - MinXBorder
			|| OtherUserPos.X > UserList[UserIndex].Pos.X + MinXBorder) {
		return retval;
	}

	/* ' In y range? */
	if (OtherUserPos.Y < UserList[UserIndex].Pos.Y - MinYBorder
			&& OtherUserPos.Y > UserList[UserIndex].Pos.Y + MinYBorder) {
		return retval;
	}

	retval = true;

	return retval;
}

bool InRangoVisionNPC(int NpcIndex, int X, int Y) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (X > Npclist[NpcIndex].Pos.X - MinXBorder && X < Npclist[NpcIndex].Pos.X + MinXBorder) {
		if (Y > Npclist[NpcIndex].Pos.Y - MinYBorder && Y < Npclist[NpcIndex].Pos.Y + MinYBorder) {
			retval = true;
			return retval;
		}
	}
	retval = false;

	return retval;
}

bool InMapBounds(int Map, int X, int Y) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if ((Map <= 0 || Map > NumMaps) || X < MinXBorder || X > MaxXBorder || Y < MinYBorder || Y > MaxYBorder) {
		retval = false;
	} else {
		retval = true;
	}

	return retval;
}

bool RhombLegalPos(struct WorldPos & Pos, int & vX, int & vY, int Distance, bool PuedeAgua, bool PuedeTierra,
		bool CheckExitTile) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Marco Vanotti (Marco) */
	/* 'Last Modification: - */
	/* ' walks all the perimeter of a rhomb of side  "distance + 1", */
	/* ' which starts at Pos.x - Distance and Pos.y */
	/* '*************************************************** */

	int i;

	vX = Pos.X - Distance;
	vY = Pos.Y;

	for (i = (0); i <= (Distance - 1); i++) {
		if ((LegalPos(Pos.Map, vX + i, vY - i, PuedeAgua, PuedeTierra, CheckExitTile))) {
			vX = vX + i;
			vY = vY - i;
			retval = true;
			return retval;
		}
	}

	vX = Pos.X;
	vY = Pos.Y - Distance;

	for (i = (0); i <= (Distance - 1); i++) {
		if ((LegalPos(Pos.Map, vX + i, vY + i, PuedeAgua, PuedeTierra, CheckExitTile))) {
			vX = vX + i;
			vY = vY + i;
			retval = true;
			return retval;
		}
	}

	vX = Pos.X + Distance;
	vY = Pos.Y;

	for (i = (0); i <= (Distance - 1); i++) {
		if ((LegalPos(Pos.Map, vX - i, vY + i, PuedeAgua, PuedeTierra, CheckExitTile))) {
			vX = vX - i;
			vY = vY + i;
			retval = true;
			return retval;
		}
	}

	vX = Pos.X;
	vY = Pos.Y + Distance;

	for (i = (0); i <= (Distance - 1); i++) {
		if ((LegalPos(Pos.Map, vX - i, vY - i, PuedeAgua, PuedeTierra, CheckExitTile))) {
			vX = vX - i;
			vY = vY - i;
			retval = true;
			return retval;
		}
	}

	retval = false;

	return retval;
}

bool RhombLegalTilePos(struct WorldPos & Pos, int & vX, int & vY, int Distance, int ObjIndex, int ObjAmount,
		bool PuedeAgua, bool PuedeTierra) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: - */
	/* ' walks all the perimeter of a rhomb of side  "distance + 1", */
	/* ' which starts at Pos.x - Distance and Pos.y */
	/* ' and searchs for a valid position to drop items */
	/* '*************************************************** */

	int i;
	int X;
	int Y;

	vX = Pos.X - Distance;
	vY = Pos.Y;

	for (i = (0); i <= (Distance - 1); i++) {

		X = vX + i;
		Y = vY - i;

		if ((LegalPos(Pos.Map, X, Y, PuedeAgua, PuedeTierra, true))) {

			/* ' No hay obj tirado o la suma de lo que hay + lo nuevo <= 10k */
			if (!HayObjeto(Pos.Map, X, Y, ObjIndex, ObjAmount)) {
				vX = X;
				vY = Y;

				retval = true;
				return retval;
			}

		}
	}

	vX = Pos.X;
	vY = Pos.Y - Distance;

	for (i = (0); i <= (Distance - 1); i++) {

		X = vX + i;
		Y = vY + i;

		if ((LegalPos(Pos.Map, X, Y, PuedeAgua, PuedeTierra, true))) {

			/* ' No hay obj tirado o la suma de lo que hay + lo nuevo <= 10k */
			if (!HayObjeto(Pos.Map, X, Y, ObjIndex, ObjAmount)) {
				vX = X;
				vY = Y;

				retval = true;
				return retval;
			}
		}
	}

	vX = Pos.X + Distance;
	vY = Pos.Y;

	for (i = (0); i <= (Distance - 1); i++) {

		X = vX - i;
		Y = vY + i;

		if ((LegalPos(Pos.Map, X, Y, PuedeAgua, PuedeTierra, true))) {

			/* ' No hay obj tirado o la suma de lo que hay + lo nuevo <= 10k */
			if (!HayObjeto(Pos.Map, X, Y, ObjIndex, ObjAmount)) {
				vX = X;
				vY = Y;

				retval = true;
				return retval;
			}
		}
	}

	vX = Pos.X;
	vY = Pos.Y + Distance;

	for (i = (0); i <= (Distance - 1); i++) {

		X = vX - i;
		Y = vY - i;

		if ((LegalPos(Pos.Map, X, Y, PuedeAgua, PuedeTierra, true))) {
			/* ' No hay obj tirado o la suma de lo que hay + lo nuevo <= 10k */
			if (!HayObjeto(Pos.Map, X, Y, ObjIndex, ObjAmount)) {
				vX = X;
				vY = Y;

				retval = true;
				return retval;
			}
		}
	}

	retval = false;

	return retval;
}

bool HayObjeto(int mapa, int X, int Y, int ObjIndex, int ObjAmount) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: - */
	/* 'Checks if there's space in a tile to add an itemAmount */
	/* '*************************************************** */
	int MapObjIndex;
	MapObjIndex = MapData[mapa][X][Y].ObjInfo.ObjIndex;

	/* ' Hay un objeto tirado? */
	if (MapObjIndex != 0) {
		/* ' Es el mismo objeto? */
		if (MapObjIndex == ObjIndex) {
			/* ' La suma es menor a 10k? */
			retval = (MapData[mapa][X][Y].ObjInfo.Amount + ObjAmount > MAX_INVENTORY_OBJS);
		} else {
			retval = true;
		}
	} else {
		retval = false;
	}

	return retval;
}

void ClosestLegalPos(struct WorldPos Pos, struct WorldPos & nPos, bool PuedeAgua, bool PuedeTierra,
		bool CheckExitTile) {
	/* '***************************************************************** */
	/* 'Author: Unknown (original version) */
	/* 'Last Modification: 09/14/2010 (Marco) */
	/* 'History: */
	/* ' - 01/24/2007 (ToxicWaste) */
	/* 'Encuentra la posicion legal mas cercana y la guarda en nPos */
	/* '***************************************************************** */

	bool Found = false;
	int LoopC;
	int tX;
	int tY;

	nPos = Pos;
	tX = Pos.X;
	tY = Pos.Y;

	LoopC = 1;

	/* ' La primera posicion es valida? */
	if (LegalPos(Pos.Map, nPos.X, nPos.Y, PuedeAgua, PuedeTierra, CheckExitTile)) {
		Found = true;

		/* ' Busca en las demas posiciones, en forma de "rombo" */
	} else {
		while ((!Found) && LoopC <= 12) {
			if (RhombLegalPos(Pos, tX, tY, LoopC, PuedeAgua, PuedeTierra, CheckExitTile)) {
				nPos.X = tX;
				nPos.Y = tY;
				Found = true;
			}

			LoopC = LoopC + 1;
		}

	}

	if (!Found) {
		nPos.X = 0;
		nPos.Y = 0;
	}

}

void ClosestStablePos(struct WorldPos Pos, struct WorldPos & nPos) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 09/14/2010 */
	/* 'Encuentra la posicion legal mas cercana que no sea un portal y la guarda en nPos */
	/* '***************************************************************** */

	ClosestLegalPos(Pos, nPos, false, true, true);

}

int NameIndex(std::string Name) {
	int retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int UserIndex;

	/* '¿Nombre valido? */
	if (vb6::LenB(Name) == 0) {
		retval = 0;
		return retval;
	}

	if (vb6::InStrB(Name, "+") != 0) {
		Name = vb6::UCase(vb6::Replace(Name, "+", " "));
	}

	// FIXME: Busqueda lineal!
	// FIXME: Busqueda lineal!

	UserIndex = 1;
	while (!(vb6::UCase(UserList[UserIndex].Name) == vb6::UCase(Name))) {

		UserIndex = UserIndex + 1;

		if (UserIndex > MaxUsers) {
			retval = 0;
			return retval;
		}
	}

	retval = UserIndex;
	return retval;
}

bool CheckForSameIP(int UserIndex, std::string UserIP) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int LoopC;

	for (LoopC = (1); LoopC <= (MaxUsers); LoopC++) {
		if (UserList[LoopC].flags.UserLogged == true) {
			if (UserList[LoopC].ip == UserIP && UserIndex != LoopC) {
				retval = true;
				return retval;
			}
		}
	}

	retval = false;
	return retval;
}

bool CheckForSameName(std::string Name, int& OtherUserIndex) {
	/* 'Controlo que no existan usuarios con el mismo nombre */
	int LoopC;
	OtherUserIndex = -1;

	for (LoopC = (1); LoopC <= (LastUser); LoopC++) {
		if (UserList[LoopC].flags.UserLogged) {

			/* 'If UCase$(UserList(LoopC).Name) = UCase$(Name) And UserList(LoopC).ConnID <> -1 Then */
			/* 'OJO PREGUNTAR POR EL CONNID <> -1 PRODUCE QUE UN PJ EN DETERMINADO */
			/* 'MOMENTO PUEDA ESTAR LOGUEADO 2 VECES (IE: CIERRA EL SOCKET DESDE ALLA) */
			/* 'ESE EVENTO NO DISPARA UN SAVE USER, LO QUE PUEDE SER UTILIZADO PARA DUPLICAR ITEMS */
			/* 'ESTE BUG EN ALKON PRODUJO QUE EL SERVIDOR ESTE CAIDO DURANTE 3 DIAS. ATENTOS. */

			if (vb6::UCase(UserList[LoopC].Name) == vb6::UCase(Name)) {
				OtherUserIndex = LoopC;
				return true;
			}
		}
	}

	return false;
}

void HeadtoPos(eHeading Head, struct WorldPos & Pos) {
	switch (Head) {
	case eHeading_NORTH:
		Pos.Y = Pos.Y - 1;
		break;

	case eHeading_SOUTH:
		Pos.Y = Pos.Y + 1;
		break;

	case eHeading_EAST:
		Pos.X = Pos.X + 1;
		break;

	case eHeading_WEST:
		Pos.X = Pos.X - 1;
		break;

	case eHeading_None:
		break;
	}
}

void HeadtoPos(eHeading Head, struct Position & Pos) {
	switch (Head) {
	case eHeading_NORTH:
		Pos.Y = Pos.Y - 1;
		break;

	case eHeading_SOUTH:
		Pos.Y = Pos.Y + 1;
		break;

	case eHeading_EAST:
		Pos.X = Pos.X + 1;
		break;

	case eHeading_WEST:
		Pos.X = Pos.X - 1;
		break;

	case eHeading_None:
		break;
	}
}

bool LegalPos(int Map, int X, int Y, bool PuedeAgua, bool PuedeTierra, bool CheckExitTile) {
	bool retval;
	/* '*************************************************** */
	/* 'Autor: Pablo (ToxicWaste) & Unknown (orginal version) */
	/* 'Last Modification: 23/01/2007 */
	/* 'Checks if the position is Legal. */
	/* '*************************************************** */

	/* '¿Es un mapa valido? */
	if ((Map <= 0 || Map > NumMaps)
			|| (X < MinXBorder || X > MaxXBorder || Y < MinYBorder || Y > MaxYBorder)) {
		retval = false;
	} else {
		if (PuedeAgua && PuedeTierra) {
			retval = (MapData[Map][X][Y].Blocked != 1) && (MapData[Map][X][Y].UserIndex == 0)
					&& (MapData[Map][X][Y].NpcIndex == 0);
		} else if (PuedeTierra && !PuedeAgua) {
			retval = (MapData[Map][X][Y].Blocked != 1) && (MapData[Map][X][Y].UserIndex == 0)
					&& (MapData[Map][X][Y].NpcIndex == 0) && (!HayAgua(Map, X, Y));
		} else if (PuedeAgua && !PuedeTierra) {
			retval = (MapData[Map][X][Y].Blocked != 1) && (MapData[Map][X][Y].UserIndex == 0)
					&& (MapData[Map][X][Y].NpcIndex == 0) && (HayAgua(Map, X, Y));
		} else {
			retval = false;
		}

		if (CheckExitTile) {
			retval = retval && (MapData[Map][X][Y].TileExit.Map == 0);
		}

	}

	return retval;
}

bool MoveToLegalPos(int Map, int X, int Y, bool PuedeAgua, bool PuedeTierra) {
	bool retval;
	/* '*************************************************** */
	/* 'Autor: ZaMa */
	/* 'Last Modification: 13/07/2009 */
	/* 'Checks if the position is Legal, but considers that if there's a casper, it's a legal movement. */
	/* '13/07/2009: ZaMa - Now it's also legal move where an invisible admin is. */
	/* '*************************************************** */

	int UserIndex;
	bool IsDeadChar;
	bool IsAdminInvisible;

	/* '¿Es un mapa valido? */
	if ((Map <= 0 || Map > NumMaps)
			|| (X < MinXBorder || X > MaxXBorder || Y < MinYBorder || Y > MaxYBorder)) {
		retval = false;
	} else {
		UserIndex = MapData[Map][X][Y].UserIndex;

		if (UserIndex > 0) {
			IsDeadChar = (UserList[UserIndex].flags.Muerto == 1);
			IsAdminInvisible = (UserList[UserIndex].flags.AdminInvisible == 1);
		} else {
			IsDeadChar = false;
			IsAdminInvisible = false;
		}

		if (PuedeAgua && PuedeTierra) {
			retval = (MapData[Map][X][Y].Blocked != 1) && (UserIndex == 0 || IsDeadChar || IsAdminInvisible)
					&& (MapData[Map][X][Y].NpcIndex == 0);
		} else if (PuedeTierra && !PuedeAgua) {
			retval = (MapData[Map][X][Y].Blocked != 1) && (UserIndex == 0 || IsDeadChar || IsAdminInvisible)
					&& (MapData[Map][X][Y].NpcIndex == 0) && (!HayAgua(Map, X, Y));
		} else if (PuedeAgua && !PuedeTierra) {
			retval = (MapData[Map][X][Y].Blocked != 1) && (UserIndex == 0 || IsDeadChar || IsAdminInvisible)
					&& (MapData[Map][X][Y].NpcIndex == 0) && (HayAgua(Map, X, Y));
		} else {
			retval = false;
		}
	}

	return retval;
}

void FindLegalPos(int UserIndex, int Map, int & X, int & Y) {
	/* '*************************************************** */
	/* 'Autor: ZaMa */
	/* 'Last Modification: 26/03/2009 */
	/* 'Search for a Legal pos for the user who is being teleported. */
	/* '*************************************************** */

	if (MapData[Map][X][Y].UserIndex != 0 || MapData[Map][X][Y].NpcIndex != 0) {

		/* ' Se teletransporta a la misma pos a la que estaba */
		if (MapData[Map][X][Y].UserIndex == UserIndex) {
			return;
		}

		bool FoundPlace = false;
		int tX = 0;
		int tY = 0;
		int Rango = 0;
		int OtherUserIndex;

		for (Rango = (1); Rango <= (5); Rango++) {
			for (tY = (Y - Rango); tY <= (Y + Rango); tY++) {
				for (tX = (X - Rango); tX <= (X + Rango); tX++) {
					/* 'Reviso que no haya User ni NPC */
					if (MapData[Map][tX][tY].UserIndex == 0 && MapData[Map][tX][tY].NpcIndex == 0) {

						if (InMapBounds(Map, tX, tY)) {
							FoundPlace = true;
						}

						break;
					}

				}

				if (FoundPlace) {
					break;
				}
			}

			if (FoundPlace) {
				break;
			}
		}

		/* 'Si encontramos un lugar, listo, nos quedamos ahi */
		if (FoundPlace) {
			X = tX;
			Y = tY;
		} else {
			/* 'Muy poco probable, pero.. */
			/* 'Si no encontramos un lugar, sacamos al usuario que tenemos abajo, y si es un NPC, lo pisamos. */
			OtherUserIndex = MapData[Map][X][Y].UserIndex;
			if (OtherUserIndex != 0) {
				/* 'Si no encontramos lugar, y abajo teniamos a un usuario, lo pisamos y cerramos su comercio seguro */
				if (UserList[OtherUserIndex].ComUsu.DestUsu > 0) {
					/* 'Le avisamos al que estaba comerciando que se tuvo que ir. */
					if (UserList[UserList[OtherUserIndex].ComUsu.DestUsu].flags.UserLogged) {
						FinComerciarUsu(UserList[OtherUserIndex].ComUsu.DestUsu);
						WriteConsoleMsg(UserList[OtherUserIndex].ComUsu.DestUsu,
								"Comercio cancelado. El otro usuario se ha desconectado.",
								FontTypeNames_FONTTYPE_TALK);
						FlushBuffer(UserList[OtherUserIndex].ComUsu.DestUsu);
					}
					/* 'Lo sacamos. */
					if (UserList[OtherUserIndex].flags.UserLogged) {
						FinComerciarUsu(OtherUserIndex);
						WriteErrorMsg(OtherUserIndex,
								"Alguien se ha conectado donde te encontrabas, por favor reconéctate...");
						FlushBuffer(OtherUserIndex);
					}
				}

				CloseSocket(OtherUserIndex);
			}
		}
	}

}

bool LegalPosNPC(int Map, int X, int Y, int AguaValida, bool IsPet) {
	bool retval;
	/* '*************************************************** */
	/* 'Autor: Unkwnown */
	/* 'Last Modification: 09/23/2009 */
	/* 'Checks if it's a Legal pos for the npc to move to. */
	/* '09/23/2009: Pato - If UserIndex is a AdminInvisible, then is a legal pos. */
	/* '*************************************************** */
	bool IsDeadChar;
	int UserIndex;
	bool IsAdminInvisible;

	if ((Map <= 0 || Map > NumMaps)
			|| (X < MinXBorder || X > MaxXBorder || Y < MinYBorder || Y > MaxYBorder)) {
		retval = false;
		return retval;
	}

	UserIndex = MapData[Map][X][Y].UserIndex;
	if (UserIndex > 0) {
		IsDeadChar = UserList[UserIndex].flags.Muerto == 1;
		IsAdminInvisible = (UserList[UserIndex].flags.AdminInvisible == 1);
	} else {
		IsDeadChar = false;
		IsAdminInvisible = false;
	}

	if (AguaValida == 0) {
		retval = (MapData[Map][X][Y].Blocked != 1)
				&& (MapData[Map][X][Y].UserIndex == 0 || IsDeadChar || IsAdminInvisible)
				&& (MapData[Map][X][Y].NpcIndex == 0)
				&& (MapData[Map][X][Y].trigger != eTrigger_POSINVALIDA || IsPet) && !HayAgua(Map, X, Y);
	} else {
		retval = (MapData[Map][X][Y].Blocked != 1)
				&& (MapData[Map][X][Y].UserIndex == 0 || IsDeadChar || IsAdminInvisible)
				&& (MapData[Map][X][Y].NpcIndex == 0)
				&& (MapData[Map][X][Y].trigger != eTrigger_POSINVALIDA || IsPet);
	}
	return retval;
}

void SendHelp(int index) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int NumHelpLines;
	int LoopC;

	NumHelpLines = vb6::Constrain(vb6::CInt(GetVar(GetDatPath(DATPATH::Help), "INIT", "NumLines")), 0, MAX_HELP_LINES);

	for (LoopC = (1); LoopC <= (NumHelpLines); LoopC++) {
		WriteConsoleMsg(index, GetVar(GetDatPath(DATPATH::Help), "Help", "Line" + vb6::CStr(LoopC)),
				FontTypeNames_FONTTYPE_INFO);
	}

}

void Expresar(int NpcIndex, int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (Npclist[NpcIndex].NroExpresiones > 0) {
		int randomi;
		randomi = RandomNumber(1, Npclist[NpcIndex].NroExpresiones);
		SendData(SendTarget_ToPCArea, UserIndex,
				BuildChatOverHead(Npclist[NpcIndex].Expresiones[randomi],
						Npclist[NpcIndex].Char.CharIndex, 0x00ffffff));
	}
}

void LookatTile(int UserIndex, int Map, int X, int Y) {
	/* '*************************************************** */
	/* 'Autor: Unknown (orginal version) */
	/* 'Last Modification: 26/03/2009 */
	/* '13/02/2009: ZaMa - El nombre del gm que aparece por consola al clickearlo, tiene el color correspondiente a su rango */
	/* '07/10/2010: ZaMa - Adaptado para que funcione mas de un centinela en paralelo. */
	/* '*************************************************** */

	/* 'Responde al click del usuario sobre el mapa */
	int FoundChar = 0;
	int FoundSomething = 0;
	int TempCharIndex = 0;
	std::string Stat;
	FontTypeNames ft = FontTypeNames_FONTTYPE_INFO;

	/* '¿Rango Visión? (ToxicWaste) */
	if ((vb6::Abs(UserList[UserIndex].Pos.Y - Y) > RANGO_VISION_Y)
			|| (vb6::Abs(UserList[UserIndex].Pos.X - X) > RANGO_VISION_X)) {
		return;
	}

	/* '¿Posicion valida? */
	if (InMapBounds(Map, X, Y)) {
		UserList[UserIndex].flags.TargetMap = Map;
		UserList[UserIndex].flags.TargetX = X;
		UserList[UserIndex].flags.TargetY = Y;
		/* '¿Es un obj? */
		if (MapData[Map][X][Y].ObjInfo.ObjIndex > 0) {
			/* 'Informa el nombre */
			UserList[UserIndex].flags.TargetObjMap = Map;
			UserList[UserIndex].flags.TargetObjX = X;
			UserList[UserIndex].flags.TargetObjY = Y;
			FoundSomething = 1;
		} else if (MapData[Map][X + 1][Y].ObjInfo.ObjIndex > 0) {
			/* 'Informa el nombre */
			if (ObjData[MapData[Map][X + 1][Y].ObjInfo.ObjIndex].OBJType == eOBJType_otPuertas) {
				UserList[UserIndex].flags.TargetObjMap = Map;
				UserList[UserIndex].flags.TargetObjX = X + 1;
				UserList[UserIndex].flags.TargetObjY = Y;
				FoundSomething = 1;
			}
		} else if (MapData[Map][X + 1][Y + 1].ObjInfo.ObjIndex > 0) {
			if (ObjData[MapData[Map][X + 1][Y + 1].ObjInfo.ObjIndex].OBJType == eOBJType_otPuertas) {
				/* 'Informa el nombre */
				UserList[UserIndex].flags.TargetObjMap = Map;
				UserList[UserIndex].flags.TargetObjX = X + 1;
				UserList[UserIndex].flags.TargetObjY = Y + 1;
				FoundSomething = 1;
			}
		} else if (MapData[Map][X][Y + 1].ObjInfo.ObjIndex > 0) {
			if (ObjData[MapData[Map][X][Y + 1].ObjInfo.ObjIndex].OBJType == eOBJType_otPuertas) {
				/* 'Informa el nombre */
				UserList[UserIndex].flags.TargetObjMap = Map;
				UserList[UserIndex].flags.TargetObjX = X;
				UserList[UserIndex].flags.TargetObjY = Y + 1;
				FoundSomething = 1;
			}
		}

		if (FoundSomething == 1) {
			UserList[UserIndex].flags.TargetObj =
					MapData[Map][UserList[UserIndex].flags.TargetObjX][UserList[UserIndex].flags.TargetObjY].ObjInfo.ObjIndex;
			if (MostrarCantidad(UserList[UserIndex].flags.TargetObj)) {
				WriteConsoleMsg(UserIndex,
						ObjData[UserList[UserIndex].flags.TargetObj].Name + " - "
								+ vb6::CStr(MapData[UserList[UserIndex].flags.TargetObjMap][UserList[UserIndex].flags.TargetObjX][UserList[UserIndex].flags.TargetObjY].ObjInfo.Amount)
								+ "", FontTypeNames_FONTTYPE_INFO);
			} else {
				WriteConsoleMsg(UserIndex, ObjData[UserList[UserIndex].flags.TargetObj].Name,
						FontTypeNames_FONTTYPE_INFO);
			}

		}
		/* '¿Es un personaje? */
		if (Y + 1 <= YMaxMapSize) {
			if (MapData[Map][X][Y + 1].UserIndex > 0) {
				TempCharIndex = MapData[Map][X][Y + 1].UserIndex;
				FoundChar = 1;
			}
			if (MapData[Map][X][Y + 1].NpcIndex > 0) {
				TempCharIndex = MapData[Map][X][Y + 1].NpcIndex;
				FoundChar = 2;
			}
		}
		/* '¿Es un personaje? */
		if (FoundChar == 0) {
			if (MapData[Map][X][Y].UserIndex > 0) {
				TempCharIndex = MapData[Map][X][Y].UserIndex;
				FoundChar = 1;
			}
			if (MapData[Map][X][Y].NpcIndex > 0) {
				TempCharIndex = MapData[Map][X][Y].NpcIndex;
				FoundChar = 2;
			}
		}

		/* 'Reaccion al personaje */
		/* '  ¿Encontro un Usuario? */
		if (FoundChar == 1) {
			if (UserList[TempCharIndex].flags.AdminInvisible == 0
					|| UserTienePrivilegio(UserIndex, PlayerType_Dios)) {
				/* 'No tiene descRM y quiere que se vea su nombre. */
				if (vb6::LenB(UserList[TempCharIndex].DescRM) == 0 && UserList[TempCharIndex].showName) {
					if (EsNewbie(TempCharIndex)) {
						Stat = " <NEWBIE>";
					}

					if (UserList[TempCharIndex].Faccion.ArmadaReal == 1) {
						Stat = Stat + " <Ejército Real> " + "<" + TituloReal(TempCharIndex) + ">";
					} else if (UserList[TempCharIndex].Faccion.FuerzasCaos == 1) {
						Stat = Stat + " <Legión Oscura> " + "<" + TituloCaos(TempCharIndex) + ">";
					}

					if (UserList[TempCharIndex].GuildIndex > 0) {
						Stat = Stat + " <" + GuildName(UserList[TempCharIndex].GuildIndex) + ">";
					}

					if (vb6::Len(UserList[TempCharIndex].desc) > 0) {
						Stat = "Ves a " + UserList[TempCharIndex].Name + Stat + " - "
								+ UserList[TempCharIndex].desc;
					} else {
						Stat = "Ves a " + UserList[TempCharIndex].Name + Stat;
					}

					if (UserTienePrivilegio(TempCharIndex, PlayerType_RoyalCouncil)) {
						Stat = Stat + " [CONSEJO DE BANDERBILL]";
						ft = FontTypeNames_FONTTYPE_CONSEJOVesA;
					} else if (UserTienePrivilegio(TempCharIndex, PlayerType_ChaosCouncil)) {
						Stat = Stat + " [CONCILIO DE LAS SOMBRAS]";
						ft = FontTypeNames_FONTTYPE_CONSEJOCAOSVesA;
					} else {
						if (!UserTienePrivilegio(TempCharIndex, PlayerType_User)) {
							Stat = Stat + " <GAME MASTER>";

							/* ' Elijo el color segun el rango del GM: */
							/* ' Dios */
							if (UserTienePrivilegio(TempCharIndex, PlayerType_Dios)) {
								ft = FontTypeNames_FONTTYPE_DIOS;
								/* ' Gm */
							} else if (UserTienePrivilegio(TempCharIndex, PlayerType_SemiDios)) {
								ft = FontTypeNames_FONTTYPE_GM;
								/* ' Conse */
							} else if (UserTienePrivilegio(TempCharIndex, PlayerType_Consejero)) {
								ft = FontTypeNames_FONTTYPE_CONSE;
								/* ' Rm o Dsrm */
							} else if (UserTienePrivilegio(TempCharIndex, PlayerType_RoleMaster)) {
								ft = FontTypeNames_FONTTYPE_EJECUCION;
							}

						} else if (criminal(TempCharIndex)) {
							Stat = Stat + " <CRIMINAL>";
							ft = FontTypeNames_FONTTYPE_FIGHT;
						} else {
							Stat = Stat + " <CIUDADANO>";
							ft = FontTypeNames_FONTTYPE_CITIZEN;
						}
					}
					/* 'Si tiene descRM la muestro siempre. */
				} else {
					Stat = UserList[TempCharIndex].DescRM;
					ft = FontTypeNames_FONTTYPE_INFOBOLD;
				}

				if (vb6::LenB(Stat) > 0) {
					WriteConsoleMsg(UserIndex, Stat, ft);
				}

				FoundSomething = 1;
				UserList[UserIndex].flags.TargetUser = TempCharIndex;
				UserList[UserIndex].flags.TargetNPC = 0;
				UserList[UserIndex].flags.TargetNpcTipo = eNPCType_Comun;
			}
		}

		/* '¿Encontro un NPC? */
		if (FoundChar == 2) {
			std::string estatus;
			int MinHp;
			int MaxHp;
			int SupervivenciaSkill;
			std::string sDesc;

			MinHp = Npclist[TempCharIndex].Stats.MinHp;
			MaxHp = Npclist[TempCharIndex].Stats.MaxHp;
			SupervivenciaSkill = UserList[UserIndex].Stats.UserSkills[eSkill_Supervivencia];

			if (UserTienePrivilegio(UserIndex, PlayerType_SemiDios) ||
				UserTienePrivilegio(UserIndex, PlayerType_Dios) ||
				UserTienePrivilegio(UserIndex, PlayerType_Admin)) {
				estatus = "(" + vb6::CStr(MinHp) + "/" + vb6::CStr(MaxHp) + ") ";
			} else {
				if (UserList[UserIndex].flags.Muerto == 0) {

					if (SupervivenciaSkill <= 10) {
						estatus = "(Dudoso) ";

					} else if (SupervivenciaSkill <= 20) {
						if (MinHp < (MaxHp / 2)) {
							estatus = "(Herido) ";
						} else {
							estatus = "(Sano) ";
						}

					} else if (SupervivenciaSkill <= 30) {
						if (MinHp < (MaxHp * 0.5)) {
							estatus = "(Malherido) ";
						} else if (MinHp < (MaxHp * 0.75)) {
							estatus = "(Herido) ";
						} else {
							estatus = "(Sano) ";
						}

					} else if (SupervivenciaSkill <= 40) {
						if (MinHp < (MaxHp * 0.25)) {
							estatus = "(Muy malherido) ";
						} else if (MinHp < (MaxHp * 0.5)) {
							estatus = "(Herido) ";
						} else if (MinHp < (MaxHp * 0.75)) {
							estatus = "(Levemente herido) ";
						} else {
							estatus = "(Sano) ";
						}

					} else if (SupervivenciaSkill < 60) {
						if (MinHp < (MaxHp * 0.05)) {
							estatus = "(Agonizando) ";
						} else if (MinHp < (MaxHp * 0.1)) {
							estatus = "(Casi muerto) ";
						} else if (MinHp < (MaxHp * 0.25)) {
							estatus = "(Muy Malherido) ";
						} else if (MinHp < (MaxHp * 0.5)) {
							estatus = "(Herido) ";
						} else if (MinHp < (MaxHp * 0.75)) {
							estatus = "(Levemente herido) ";
						} else if (MinHp < (MaxHp)) {
							estatus = "(Sano) ";
						} else {
							estatus = "(Intacto) ";
						}
					} else {
						estatus = "(" + vb6::CStr(MinHp) + "/" + vb6::CStr(MaxHp) + ") ";
					}
				}
			}

			if (vb6::Len(Npclist[TempCharIndex].desc) > 1) {
				Stat = Npclist[TempCharIndex].desc;

				/* '¿Es el rey o el demonio? */
				if (Npclist[TempCharIndex].NPCtype == eNPCType_Noble) {
					/* 'Es el Rey. */
					if (Npclist[TempCharIndex].flags.Faccion == 0) {
						/* 'Si es de la Legión Oscura y usuario común mostramos el mensaje correspondiente y lo ejecutamos: */
						if (UserList[UserIndex].Faccion.FuerzasCaos == 1) {
							Stat = MENSAJE_REY_CAOS;
							if (UserTienePrivilegio(UserIndex, PlayerType_User)) {
								if (UserList[UserIndex].flags.Muerto == 0) {
									UserDie(UserIndex);
								}
							}
						} else if (criminal(UserIndex)) {
							/* 'Nos fijamos si es criminal enlistable o no enlistable: */
							/* 'Es criminal no enlistable. */
							if (UserList[UserIndex].Faccion.CiudadanosMatados > 0
									|| UserList[UserIndex].Faccion.Reenlistadas > 4) {
								Stat = MENSAJE_REY_CRIMINAL_NOENLISTABLE;
								/* 'Es criminal enlistable. */
							} else {
								Stat = MENSAJE_REY_CRIMINAL_ENLISTABLE;
							}
						}
						/* 'Es el demonio */
					} else {
						/* 'Si es de la Armada Real y usuario común mostramos el mensaje correspondiente y lo ejecutamos: */
						if (UserList[UserIndex].Faccion.ArmadaReal == 1) {
							Stat = MENSAJE_DEMONIO_REAL;
							/* ' */
							if (UserTienePrivilegio(UserIndex, PlayerType_User)) {
								if (UserList[UserIndex].flags.Muerto == 0) {
									UserDie(UserIndex);
								}
							}
						} else if (!criminal(UserIndex)) {
							/* 'Nos fijamos si es ciudadano enlistable o no enlistable: */
							/* 'Es ciudadano no enlistable. */
							if (UserList[UserIndex].Faccion.RecibioExpInicialReal == 1
									|| UserList[UserIndex].Faccion.Reenlistadas > 4) {
								Stat = MENSAJE_DEMONIO_CIUDADANO_NOENLISTABLE;
								/* 'Es ciudadano enlistable. */
							} else {
								Stat = MENSAJE_DEMONIO_CIUDADANO_ENLISTABLE;
							}
						}
					}
				}

				/* 'Enviamos el mensaje propiamente dicho: */
				WriteChatOverHead(UserIndex, Stat, Npclist[TempCharIndex].Char.CharIndex, 0x00ffffff);
			} else {

				int CentinelaIndex;
				CentinelaIndex = EsCentinela(TempCharIndex);

				if (CentinelaIndex != 0) {
					/* 'Enviamos nuevamente el texto del centinela según quien pregunta */
					CentinelaSendClave(UserIndex, CentinelaIndex);
				} else {
					if (Npclist[TempCharIndex].MaestroUser > 0) {
						WriteConsoleMsg(UserIndex,
								estatus + Npclist[TempCharIndex].Name + " es mascota de "
										+ UserList[Npclist[TempCharIndex].MaestroUser].Name + ".",
								FontTypeNames_FONTTYPE_INFO);
					} else {
						sDesc = estatus + Npclist[TempCharIndex].Name;
						if (Npclist[TempCharIndex].Owner > 0) {
							sDesc = sDesc + " le pertenece a " + UserList[Npclist[TempCharIndex].Owner].Name;
						}
						sDesc = sDesc + ".";

						WriteConsoleMsg(UserIndex, sDesc, FontTypeNames_FONTTYPE_INFO);

						if (UserTienePrivilegio(UserIndex, PlayerType_Dios) || UserTienePrivilegio(UserIndex, PlayerType_Admin)) {
							WriteConsoleMsg(UserIndex,
									"Le pegó primero: " + Npclist[TempCharIndex].flags.AttackedFirstBy + ".",
									FontTypeNames_FONTTYPE_INFO);
						}
					}
				}
			}

			FoundSomething = 1;
			UserList[UserIndex].flags.TargetNpcTipo = Npclist[TempCharIndex].NPCtype;
			UserList[UserIndex].flags.TargetNPC = TempCharIndex;
			UserList[UserIndex].flags.TargetUser = 0;
			UserList[UserIndex].flags.TargetObj = 0;
		}

		if (FoundChar == 0) {
			UserList[UserIndex].flags.TargetNPC = 0;
			UserList[UserIndex].flags.TargetNpcTipo = eNPCType_Comun;
			UserList[UserIndex].flags.TargetUser = 0;
		}

		/* '*** NO ENCOTRO NADA *** */
		if (FoundSomething == 0) {
			UserList[UserIndex].flags.TargetNPC = 0;
			UserList[UserIndex].flags.TargetNpcTipo = eNPCType_Comun;
			UserList[UserIndex].flags.TargetUser = 0;
			UserList[UserIndex].flags.TargetObj = 0;
			UserList[UserIndex].flags.TargetObjMap = 0;
			UserList[UserIndex].flags.TargetObjX = 0;
			UserList[UserIndex].flags.TargetObjY = 0;
			WriteMultiMessage(UserIndex, eMessages_DontSeeAnything);
		}
	} else {
		if (FoundSomething == 0) {
			UserList[UserIndex].flags.TargetNPC = 0;
			UserList[UserIndex].flags.TargetNpcTipo = eNPCType_Comun;
			UserList[UserIndex].flags.TargetUser = 0;
			UserList[UserIndex].flags.TargetObj = 0;
			UserList[UserIndex].flags.TargetObjMap = 0;
			UserList[UserIndex].flags.TargetObjX = 0;
			UserList[UserIndex].flags.TargetObjY = 0;

			WriteMultiMessage(UserIndex, eMessages_DontSeeAnything);
		}
	}

	return;
}

eHeading FindDirection(struct WorldPos Pos, struct WorldPos Target) {
	eHeading retval = eHeading_None;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* 'Devuelve la direccion en la cual el target se encuentra */
	/* 'desde pos, 0 si la direc es igual */
	/* '***************************************************************** */

	int X;
	int Y;

	X = Pos.X - Target.X;
	Y = Pos.Y - Target.Y;

	/* 'NE */
	if (vb6::Sgn(X) == -1 && vb6::Sgn(Y) == 1) {
		retval = vb6::IIf(RandomNumber(0, 1), eHeading_NORTH, eHeading_EAST);
		return retval;
	}

	/* 'NW */
	if (vb6::Sgn(X) == 1 && vb6::Sgn(Y) == 1) {
		retval = vb6::IIf(RandomNumber(0, 1), eHeading_WEST, eHeading_NORTH);
		return retval;
	}

	/* 'SW */
	if (vb6::Sgn(X) == 1 && vb6::Sgn(Y) == -1) {
		retval = vb6::IIf(RandomNumber(0, 1), eHeading_WEST, eHeading_SOUTH);
		return retval;
	}

	/* 'SE */
	if (vb6::Sgn(X) == -1 && vb6::Sgn(Y) == -1) {
		retval = vb6::IIf(RandomNumber(0, 1), eHeading_SOUTH, eHeading_EAST);
		return retval;
	}

	/* 'Sur */
	if (vb6::Sgn(X) == 0 && vb6::Sgn(Y) == -1) {
		retval = eHeading_SOUTH;
		return retval;
	}

	/* 'norte */
	if (vb6::Sgn(X) == 0 && vb6::Sgn(Y) == 1) {
		retval = eHeading_NORTH;
		return retval;
	}

	/* 'oeste */
	if (vb6::Sgn(X) == 1 && vb6::Sgn(Y) == 0) {
		retval = eHeading_WEST;
		return retval;
	}

	/* 'este */
	if (vb6::Sgn(X) == -1 && vb6::Sgn(Y) == 0) {
		retval = eHeading_EAST;
		return retval;
	}

	/* 'misma */
	if (vb6::Sgn(X) == 0 && vb6::Sgn(Y) == 0) {
		retval = eHeading_None;
		return retval;
	}

	return retval;
}

bool ItemNoEsDeMapa(int index, bool bIsExit) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	retval = ObjData[index].OBJType != eOBJType_otPuertas && ObjData[index].OBJType != eOBJType_otForos
			&& ObjData[index].OBJType != eOBJType_otCarteles && ObjData[index].OBJType != eOBJType_otArboles
			&& ObjData[index].OBJType != eOBJType_otYacimiento
			&& !(ObjData[index].OBJType == eOBJType_otTeleport && bIsExit);

	return retval;
}

bool MostrarCantidad(int index) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	retval = ObjData[index].OBJType != eOBJType_otPuertas && ObjData[index].OBJType != eOBJType_otForos
			&& ObjData[index].OBJType != eOBJType_otCarteles && ObjData[index].OBJType != eOBJType_otArboles
			&& ObjData[index].OBJType != eOBJType_otYacimiento
			&& ObjData[index].OBJType != eOBJType_otTeleport;

	return retval;
}

bool EsObjetoFijo(eOBJType OBJType) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	retval = OBJType == eOBJType_otForos || OBJType == eOBJType_otCarteles || OBJType == eOBJType_otArboles
			|| OBJType == eOBJType_otYacimiento;
	return retval;
}

int RestrictStringToByte(std::string x) {
	int retval = 0;
	/* '*************************************************** */
	/* 'Author: Torres Patricio (Pato) */
	/* 'Last Modification: 04/18/2011 */
	/* ' */
	/* '*************************************************** */
	x = vb6::UCase(x);

	if (x == "NEWBIE") {
		retval = 1;
	} else if (x == "ARMADA") {
		retval = 2;
	} else if (x == "CAOS") {
		retval = 3;
	} else if (x == "FACCION") {
		retval = 4;
	}

	return retval;
}

std::string RestrictByteToString(int x) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Torres Patricio (Pato) */
	/* 'Last Modification: 04/18/2011 */
	/* ' */
	/* '*************************************************** */
	switch (x) {
	case 1:
		retval = "NEWBIE";
		break;

	case 2:
		retval = "ARMADA";
		break;

	case 3:
		retval = "CAOS";
		break;

	case 4:
		retval = "FACCION";
		break;

	case 0:
		retval = "NO";
		break;
	}
	return retval;
}

int TerrainStringToByte(std::string x) {
	int retval;
	/* '*************************************************** */
	/* 'Author: Torres Patricio (Pato) */
	/* 'Last Modification: 04/18/2011 */
	/* ' */
	/* '*************************************************** */
	x = vb6::UCase(x);

	if (x == "BOSQUE") {
		retval = 0;
	} else if (x == "NIEVE") {
		retval = 1;
	} else if (x == "DESIERTO") {
		retval = 2;
	} else if (x == "CIUDAD") {
		retval = 3;
	} else if (x == "CAMPO") {
		retval = 4;
	} else if (x == "DUNGEON") {
		retval = 5;
	} else {
		throw std::runtime_error("unknown terrain: " + x);
	}
	return retval;
}

std::string TerrainByteToString(int x) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Torres Patricio (Pato) */
	/* 'Last Modification: 04/18/2011 */
	/* ' */
	/* '*************************************************** */
	switch (x) {
	case 1:
		retval = "NIEVE";
		break;

	case 2:
		retval = "DESIERTO";
		break;

	case 3:
		retval = "CIUDAD";
		break;

	case 4:
		retval = "CAMPO";
		break;

	case 5:
		retval = "DUNGEON";
		break;

	case 0:
		retval = "BOSQUE";
		break;

	default:
		throw std::runtime_error("unknown terrain: " + vb6::CStr(x));
	}
	return retval;
}
