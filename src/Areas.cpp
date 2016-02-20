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

#include "Areas.h"

/* ' Modulo de envio por areas compatible con la versión 9.10.x ... By DuNga */

/* '>>>>>>AREAS>>>>>AREAS>>>>>>>>AREAS>>>>>>>AREAS>>>>>>>>>> */

const int USER_NUEVO = 255;

/* 'Cuidado: */
/* ' ¡¡¡LAS AREAS ESTÁN HARDCODEADAS!!! */
static int CurDay;
static int CurHour;

static vb6::array<vb6::array<int> > AreasInfo;
static vb6::array<int> PosToArea;
static vb6::array<int> AreasRecive;
vb6::array<struct ConnGroup> ConnGroups;

void InitAreas() {
	/* '************************************************************** */
	/* 'Author: Lucio N. Tourrilhes (DuNga) */
	/* 'Last Modify Date: Unknow */
	/* ' */
	/* '************************************************************** */
	int LoopC;
	int loopX;

	AreasInfo.redim(1, 100); /* XXX MULTIDIMENSIONAL [('1', '100'), ('1', '100')] */
	for (auto& v : AreasInfo) {
		v.redim(1, 100);
	}
	PosToArea.redim(1, 100); /* XXX */
	AreasRecive.redim(0, 12); /* XXX */

	/* ' Setup areas... */
	for (LoopC = (0); LoopC <= (11); LoopC++) {
		AreasRecive[LoopC] = (1 << LoopC) || vb6::IIf(LoopC != 0, 1 << (LoopC - 1), 0)
				|| vb6::IIf(LoopC != 11, 1 << (LoopC + 1), 0);
	}

	for (LoopC = (1); LoopC <= (100); LoopC++) {
		PosToArea[LoopC] = LoopC / 9;
	}

	for (LoopC = (1); LoopC <= (100); LoopC++) {
		for (loopX = (1); loopX <= (100); loopX++) {
			/* 'Usamos 121 IDs de area para saber si pasasamos de area "más rápido" */
			AreasInfo[LoopC][loopX] = (LoopC / 9 + 1) * (loopX / 9 + 1);
		}
	}

	/* 'Setup AutoOptimizacion de areas */
	/* 'A ke tipo de dia pertenece? */
	CurDay = vb6::IIf(vb6::Weekday(vb6::Now()) > 6, 1, 2);
	/* 'A ke parte de la hora pertenece */
	CurHour = vb6::Fix(vb6::Hour(vb6::Now()) / 3);

	ConnGroups.redim(0);
	ConnGroups.redim(1, NumMaps);

	clsIniManager leerAreas;
	leerAreas.Initialize(GetDatPath(DATPATH::AreasStats));

	for (LoopC = (1); LoopC <= (NumMaps); LoopC++) {
		ConnGroups[LoopC].OptValue = vb6::val(
				leerAreas.GetValue("Mapa" + vb6::CStr(LoopC), vb6::CStr(CurDay) + "-" + vb6::CStr(CurHour)));

		if (ConnGroups[LoopC].OptValue == 0) {
			ConnGroups[LoopC].OptValue = 1;
		}
		ConnGroups[LoopC].UserEntrys.redim(0);
		ConnGroups[LoopC].UserEntrys.redim(1, ConnGroups[LoopC].OptValue);
	}
}

void AreasOptimizacion() {
	/* '************************************************************** */
	/* 'Author: Lucio N. Tourrilhes (DuNga) */
	/* 'Last Modify Date: Unknow */
	/* 'Es la función de autooptimizacion.... la idea es no mandar redimensionando arrays grandes todo el tiempo */
	/* '************************************************************** */
	int LoopC;
	int tCurDay;
	int tCurHour;
	int EntryValue;

	clsIniManager leerAreas;
	leerAreas.Initialize(GetDatPath(DATPATH::AreasStats));

	if ((CurDay != vb6::IIf(vb6::Weekday(vb6::Now()) > 6, 1, 2))
			|| (CurHour != vb6::Fix(vb6::Hour(vb6::Now()) / 3))) {

		/* 'A ke tipo de dia pertenece? */
		tCurDay = vb6::IIf(vb6::Weekday(vb6::Now()) > 6, 1, 2);
		/* 'A ke parte de la hora pertenece */
		tCurHour = vb6::Fix(vb6::Hour(vb6::Now()) / 3);

		for (LoopC = (1); LoopC <= (NumMaps); LoopC++) {
			EntryValue = vb6::val(leerAreas.GetValue("Mapa" + vb6::CStr(LoopC), vb6::CStr(CurDay) + "-" + vb6::CStr(CurHour)));
			leerAreas.ChangeValue("Mapa" + vb6::CStr(LoopC), vb6::CStr(CurDay) + "-" + vb6::CStr(CurHour),
					vb6::CStr(vb6::CInt((EntryValue + ConnGroups[LoopC].OptValue) / 2)));

			ConnGroups[LoopC].OptValue = vb6::val(
					leerAreas.GetValue("Mapa" + vb6::CStr(LoopC), vb6::CStr(tCurDay) + "-" + vb6::CStr(tCurHour)));
			if (ConnGroups[LoopC].OptValue == 0) {
				ConnGroups[LoopC].OptValue = 1;
			}
			if (ConnGroups[LoopC].OptValue >= MapInfo[LoopC].NumUsers) {
				ConnGroups[LoopC].UserEntrys.redim(1, ConnGroups[LoopC].OptValue);
			}
		}

		CurDay = tCurDay;
		CurHour = tCurHour;
	}

	leerAreas.DumpFile(GetDatPath(DATPATH::AreasStats));
}

void CheckUpdateNeededUser(int UserIndex, int Head, bool ButIndex) {
	/* '************************************************************** */
	/* 'Author: Lucio N. Tourrilhes (DuNga) */
	/* 'Last Modify Date: 28/10/2010 */
	/* 'Es la función clave del sistema de areas... Es llamada al mover un user */
	/* '15/07/2009: ZaMa - Now it doesn't send an invisible admin char info */
	/* '28/10/2010: ZaMa - Now it doesn't send a saling char invisible message. */
	/* '************************************************************** */
	if (UserList[UserIndex].AreasInfo.AreaID
			== AreasInfo[UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y]) {
		return;
	}

	int MinX = 0;
	int MaxX = 0;
	int MinY = 0;
	int MaxY = 0;
	int X;
	int Y;
	int TempInt;
	int Map;

	MinX = UserList[UserIndex].AreasInfo.MinX;
	MinY = UserList[UserIndex].AreasInfo.MinY;

	if (Head == eHeading_NORTH) {
		MaxY = MinY - 1;
		MinY = MinY - 9;
		MaxX = MinX + 26;
		UserList[UserIndex].AreasInfo.MinX = vb6::CInt(MinX);
		UserList[UserIndex].AreasInfo.MinY = vb6::CInt(MinY);

	} else if (Head == eHeading_SOUTH) {
		MaxY = MinY + 35;
		MinY = MinY + 27;
		MaxX = MinX + 26;
		UserList[UserIndex].AreasInfo.MinX = vb6::CInt(MinX);
		UserList[UserIndex].AreasInfo.MinY = vb6::CInt(MinY - 18);

	} else if (Head == eHeading_WEST) {
		MaxX = MinX - 1;
		MinX = MinX - 9;
		MaxY = MinY + 26;
		UserList[UserIndex].AreasInfo.MinX = vb6::CInt(MinX);
		UserList[UserIndex].AreasInfo.MinY = vb6::CInt(MinY);

	} else if (Head == eHeading_EAST) {
		MaxX = MinX + 35;
		MinX = MinX + 27;
		MaxY = MinY + 26;
		UserList[UserIndex].AreasInfo.MinX = vb6::CInt(MinX - 18);
		UserList[UserIndex].AreasInfo.MinY = vb6::CInt(MinY);

	} else if (Head == USER_NUEVO) {
		/* 'Esto pasa por cuando cambiamos de mapa o logeamos... */
		MinY = ((UserList[UserIndex].Pos.Y / 9) - 1) * 9;
		MaxY = MinY + 26;

		MinX = ((UserList[UserIndex].Pos.X / 9) - 1) * 9;
		MaxX = MinX + 26;

		UserList[UserIndex].AreasInfo.MinX = vb6::CInt(MinX);
		UserList[UserIndex].AreasInfo.MinY = vb6::CInt(MinY);
	}

	if (MinY < 1) {
		MinY = 1;
	}
	if (MinX < 1) {
		MinX = 1;
	}
	if (MaxY > 100) {
		MaxY = 100;
	}
	if (MaxX > 100) {
		MaxX = 100;
	}

	Map = UserList[UserIndex].Pos.Map;

	/* 'Esto es para ke el cliente elimine lo "fuera de area..." */
	WriteAreaChanged(UserIndex);

	/* 'Actualizamos!!! */
	for (X = (MinX); X <= (MaxX); X++) {
		for (Y = (MinY); Y <= (MaxY); Y++) {

			/* '<<< User >>> */
			if (MapData[Map][X][Y].UserIndex) {

				TempInt = MapData[Map][X][Y].UserIndex;

				if (UserIndex != TempInt) {

					/* ' Solo avisa al otro cliente si no es un admin invisible */
					if (!(UserList[TempInt].flags.AdminInvisible == 1)) {
						if (MakeUserChar(false, UserIndex, TempInt, Map, X, Y)) {
							/* ' Si esta navegando, siempre esta visible */
							if (UserList[TempInt].flags.Navegando == 0) {
								/* 'Si el user estaba invisible le avisamos al nuevo cliente de eso */
								if (UserList[TempInt].flags.invisible || UserList[TempInt].flags.Oculto) {
									if (UserTieneAlgunPrivilegios(UserIndex, PlayerType_User, PlayerType_Consejero, PlayerType_RoleMaster)) {
										WriteSetInvisible(UserIndex, UserList[TempInt].Char.CharIndex, true);
									}
								}
							}
						}
					}

					/* ' Solo avisa al otro cliente si no es un admin invisible */
					if (!(UserList[UserIndex].flags.AdminInvisible == 1)) {
						if (MakeUserChar(false, TempInt, UserIndex, UserList[UserIndex].Pos.Map,
								UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y)) {

							/* ' Si esta navegando, siempre esta visible */
							if (UserList[UserIndex].flags.Navegando == 0) {
								if (UserList[UserIndex].flags.invisible || UserList[UserIndex].flags.Oculto) {
									if (UserTienePrivilegio(TempInt, PlayerType_User)) {
										WriteSetInvisible(TempInt, UserList[UserIndex].Char.CharIndex, true);
									}
								}
							}
						}
					}

					FlushBuffer(TempInt);

				} else if (Head == USER_NUEVO) {
					if (!ButIndex) {
						MakeUserChar(false, UserIndex, UserIndex, Map, X, Y);
					}
				}
			}

			/* '<<< Npc >>> */
			if (MapData[Map][X][Y].NpcIndex) {
				MakeNPCChar(false, UserIndex, MapData[Map][X][Y].NpcIndex, Map, X, Y);
			}

			/* '<<< Item >>> */
			if (MapData[Map][X][Y].ObjInfo.ObjIndex) {
				TempInt = MapData[Map][X][Y].ObjInfo.ObjIndex;
				if (!EsObjetoFijo(ObjData[TempInt].OBJType)) {
					WriteObjectCreate(UserIndex, ObjData[TempInt].GrhIndex, X, Y);

					if (ObjData[TempInt].OBJType == eOBJType_otPuertas) {
						Bloquear(false, UserIndex, X, Y, MapData[Map][X][Y].Blocked);
						Bloquear(false, UserIndex, X - 1, Y, MapData[Map][X - 1][Y].Blocked);
					}
				}
			}

		}
	}

	/* 'Precalculados :P */
	TempInt = UserList[UserIndex].Pos.X / 9;
	UserList[UserIndex].AreasInfo.AreaReciveX = AreasRecive[TempInt];
	UserList[UserIndex].AreasInfo.AreaPerteneceX = 1 << TempInt;

	TempInt = UserList[UserIndex].Pos.Y / 9;
	UserList[UserIndex].AreasInfo.AreaReciveY = AreasRecive[TempInt];
	UserList[UserIndex].AreasInfo.AreaPerteneceY = 1 << TempInt;

	UserList[UserIndex].AreasInfo.AreaID = AreasInfo[UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y];
}

void CheckUpdateNeededNpc(int NpcIndex, int Head) {
	/* '************************************************************** */
	/* 'Author: Lucio N. Tourrilhes (DuNga) */
	/* 'Last Modify Date: Unknow */
	/* ' Se llama cuando se mueve un Npc */
	/* '************************************************************** */
	if (Npclist[NpcIndex].AreasInfo.AreaID == AreasInfo[Npclist[NpcIndex].Pos.X][Npclist[NpcIndex].Pos.Y]) {
		return;
	}

	int MinX = 0;
	int MaxX = 0;
	int MinY = 0;
	int MaxY = 0;
	int X;
	int Y;
	int TempInt;

	MinX = Npclist[NpcIndex].AreasInfo.MinX;
	MinY = Npclist[NpcIndex].AreasInfo.MinY;

	if (Head == eHeading_NORTH) {
		MaxY = MinY - 1;
		MinY = MinY - 9;
		MaxX = MinX + 26;
		Npclist[NpcIndex].AreasInfo.MinX = vb6::CInt(MinX);
		Npclist[NpcIndex].AreasInfo.MinY = vb6::CInt(MinY);

	} else if (Head == eHeading_SOUTH) {
		MaxY = MinY + 35;
		MinY = MinY + 27;
		MaxX = MinX + 26;
		Npclist[NpcIndex].AreasInfo.MinX = vb6::CInt(MinX);
		Npclist[NpcIndex].AreasInfo.MinY = vb6::CInt(MinY - 18);

	} else if (Head == eHeading_WEST) {
		MaxX = MinX - 1;
		MinX = MinX - 9;
		MaxY = MinY + 26;
		Npclist[NpcIndex].AreasInfo.MinX = vb6::CInt(MinX);
		Npclist[NpcIndex].AreasInfo.MinY = vb6::CInt(MinY);

	} else if (Head == eHeading_EAST) {
		MaxX = MinX + 35;
		MinX = MinX + 27;
		MaxY = MinY + 26;
		Npclist[NpcIndex].AreasInfo.MinX = vb6::CInt(MinX - 18);
		Npclist[NpcIndex].AreasInfo.MinY = vb6::CInt(MinY);

	} else if (Head == USER_NUEVO) {
		/* 'Esto pasa por cuando cambiamos de mapa o logeamos... */
		MinY = ((Npclist[NpcIndex].Pos.Y / 9) - 1) * 9;
		MaxY = MinY + 26;

		MinX = ((Npclist[NpcIndex].Pos.X / 9) - 1) * 9;
		MaxX = MinX + 26;

		Npclist[NpcIndex].AreasInfo.MinX = vb6::CInt(MinX);
		Npclist[NpcIndex].AreasInfo.MinY = vb6::CInt(MinY);
	}

	if (MinY < 1) {
		MinY = 1;
	}
	if (MinX < 1) {
		MinX = 1;
	}
	if (MaxY > 100) {
		MaxY = 100;
	}
	if (MaxX > 100) {
		MaxX = 100;
	}

	/* 'Actualizamos!!! */
	if (MapInfo[Npclist[NpcIndex].Pos.Map].NumUsers != 0) {
		for (X = (MinX); X <= (MaxX); X++) {
			for (Y = (MinY); Y <= (MaxY); Y++) {
				if (MapData[Npclist[NpcIndex].Pos.Map][X][Y].UserIndex) {
					MakeNPCChar(false, MapData[Npclist[NpcIndex].Pos.Map][X][Y].UserIndex, NpcIndex,
							Npclist[NpcIndex].Pos.Map, Npclist[NpcIndex].Pos.X, Npclist[NpcIndex].Pos.Y);
				}
			}
		}
	}

	/* 'Precalculados :P */
	TempInt = Npclist[NpcIndex].Pos.X / 9;
	Npclist[NpcIndex].AreasInfo.AreaReciveX = AreasRecive[TempInt];
	Npclist[NpcIndex].AreasInfo.AreaPerteneceX = 1 << TempInt;

	TempInt = Npclist[NpcIndex].Pos.Y / 9;
	Npclist[NpcIndex].AreasInfo.AreaReciveY = AreasRecive[TempInt];
	Npclist[NpcIndex].AreasInfo.AreaPerteneceY = 1 << TempInt;

	Npclist[NpcIndex].AreasInfo.AreaID = AreasInfo[Npclist[NpcIndex].Pos.X][Npclist[NpcIndex].Pos.Y];
}

void QuitarUser(int UserIndex, int Map) {
	/* '************************************************************** */
	/* 'Author: Lucio N. Tourrilhes (DuNga) */
	/* 'Last Modify Date: Unknow */
	/* ' */
	/* '************************************************************** */

	int TempVal;
	int LoopC;

	/* 'Search for the user */
	for (LoopC = (1); LoopC <= (ConnGroups[Map].CountEntrys); LoopC++) {
		if (ConnGroups[Map].UserEntrys[LoopC] == UserIndex) {
			break;
		}
	}

	/* 'Char not found */
	if (LoopC > ConnGroups[Map].CountEntrys) {
		return;
	}

	/* 'Remove from old map */
	ConnGroups[Map].CountEntrys = ConnGroups[Map].CountEntrys - 1;
	TempVal = ConnGroups[Map].CountEntrys;

	/* 'Move list back */
	for (; LoopC <= (TempVal); LoopC++) {
		ConnGroups[Map].UserEntrys[LoopC] = ConnGroups[Map].UserEntrys[LoopC + 1];
	}

	/* 'Nescesito Redim? */
	if (TempVal > ConnGroups[Map].OptValue) {
		ConnGroups[Map].UserEntrys.redim(1, TempVal);
	}
}

void AgregarUser(int UserIndex, int Map, bool ButIndex) {
	/* '************************************************************** */
	/* 'Author: Lucio N. Tourrilhes (DuNga) */
	/* 'Last Modify Date: 04/01/2007 */
	/* 'Modified by Juan Martín Sotuyo Dodero (Maraxus) */
	/* '   - Now the method checks for repetead users instead of trusting parameters. */
	/* '   - If the character is new to the map, update it */
	/* '************************************************************** */

	int TempVal;
	bool EsNuevo;
	int i;

	if (!MapaValido(Map)) {
		return;
	}

	EsNuevo = true;

	/* 'Prevent adding repeated users */
	for (i = (1); i <= (ConnGroups[Map].CountEntrys); i++) {
		if (ConnGroups[Map].UserEntrys[i] == UserIndex) {
			EsNuevo = false;
			break;
		}
	}

	if (EsNuevo) {
		/* 'Update map and connection groups data */
		ConnGroups[Map].CountEntrys = ConnGroups[Map].CountEntrys + 1;
		TempVal = ConnGroups[Map].CountEntrys;

		/* 'Nescesito Redim */
		if (TempVal > ConnGroups[Map].OptValue) {
			ConnGroups[Map].UserEntrys.redim(1, TempVal);
		}

		ConnGroups[Map].UserEntrys[TempVal] = UserIndex;
	}

	/* 'Update user */
	UserList[UserIndex].AreasInfo.AreaID = 0;

	UserList[UserIndex].AreasInfo.AreaPerteneceX = 0;
	UserList[UserIndex].AreasInfo.AreaPerteneceY = 0;
	UserList[UserIndex].AreasInfo.AreaReciveX = 0;
	UserList[UserIndex].AreasInfo.AreaReciveY = 0;

	CheckUpdateNeededUser(UserIndex, USER_NUEVO, ButIndex);
}

void AgregarNpc(int NpcIndex) {
	/* '************************************************************** */
	/* 'Author: Lucio N. Tourrilhes (DuNga) */
	/* 'Last Modify Date: Unknow */
	/* ' */
	/* '************************************************************** */
	Npclist[NpcIndex].AreasInfo.AreaID = 0;

	Npclist[NpcIndex].AreasInfo.AreaPerteneceX = 0;
	Npclist[NpcIndex].AreasInfo.AreaPerteneceY = 0;
	Npclist[NpcIndex].AreasInfo.AreaReciveX = 0;
	Npclist[NpcIndex].AreasInfo.AreaReciveY = 0;

	CheckUpdateNeededNpc(NpcIndex, USER_NUEVO);
}
