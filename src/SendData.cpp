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

#include "SendData.h"
#include "ProtocolNew.h"


std::string PacketToString(const dakara::protocol::Packet& p) {
	clsByteQueue q;
	p.serialize(&q);
	return q.PeekBinaryFixed(q.length());
}

void SendData(SendTarget sndRoute, int sndIndex, const dakara::protocol::Packet& p, bool IsDenounce) {
	clsByteQueue q;

	p.serialize(&q);

	SendData(sndRoute, sndIndex, q.PeekBinaryFixed(q.length()), IsDenounce);
}

/* '' */
/* ' Contains all methods to send data to different user groups. */
/* ' Makes use of the modAreas module. */
/* ' */
/* ' @author Juan Martín Sotuyo Dodero (Maraxus) juansotuyo@gmail.com */
/* ' @version 1.0.0 */
/* ' @date 20070107 */

void SendData(SendTarget sndRoute, int sndIndex, std::string sndData, bool IsDenounce) {
	/* '************************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) - Rewrite of original */
	/* 'Last Modify Date: 14/11/2010 */
	/* 'Last modified by: ZaMa */
	/* '14/11/2010: ZaMa - Now denounces can be desactivated. */
	/* '************************************************************** */

	if (sndData.empty())
		return;
	int LoopC;

	switch (sndRoute) {
	case SendTarget_ToPCArea:
		SendToUserArea(sndIndex, sndData);
		return;

		break;

	case SendTarget_ToAdmins:
		for (LoopC = (1); LoopC <= (LastUser); LoopC++) {
			if (UserIndexSocketValido(LoopC)) {
				if (UserTieneAlgunPrivilegios(LoopC, PlayerType_Admin, PlayerType_Dios, PlayerType_SemiDios, PlayerType_Consejero)) {
					/* ' Denounces can be desactivated */
					if (IsDenounce) {
						if (UserList[LoopC].flags.SendDenounces) {
							EnviarDatosASlot(LoopC, sndData);
						}
					} else {
						EnviarDatosASlot(LoopC, sndData);
					}
				}
			}
		}
		return;

		break;

	case SendTarget_ToAll:
		for (LoopC = (1); LoopC <= (LastUser); LoopC++) {
			if (UserIndexSocketValido(LoopC)) {
				/* 'Esta logeado como usuario? */
				if (UserList[LoopC].flags.UserLogged) {
					EnviarDatosASlot(LoopC, sndData);
				}
			}
		}
		return;

		break;

	case SendTarget_ToAllButIndex:
		for (LoopC = (1); LoopC <= (LastUser); LoopC++) {
			if (UserIndexSocketValido(LoopC) && (LoopC != sndIndex)) {
				/* 'Esta logeado como usuario? */
				if (UserList[LoopC].flags.UserLogged) {
					EnviarDatosASlot(LoopC, sndData);
				}
			}
		}
		return;

		break;

	case SendTarget_toMap:
		SendToMap(sndIndex, sndData);
		return;

		break;

	case SendTarget_ToMapButIndex:
		SendToMapButIndex(sndIndex, sndData);
		return;

		break;

	case SendTarget_ToGuildMembers:
//  LoopC = m_Iterador_ProximoUserIndex(sndIndex);
//   while (LoopC>0) {
//    if ((UserIndexSocketValido(LoopC))) {
//    EnviarDatosASlot(LoopC, sndData);
//   }
//   LoopC = m_Iterador_ProximoUserIndex(sndIndex);
		for (auto LoopC : guild_Iterador_ProximoUserIndex(sndIndex)) {
			if ((UserIndexSocketValido(LoopC))) {
				EnviarDatosASlot(LoopC, sndData);
			}
		}
		break;
		return;

		break;

	case SendTarget_ToDeadArea:
		SendToDeadUserArea(sndIndex, sndData);
		return;

		break;

	case SendTarget_ToPCAreaButIndex:
		SendToUserAreaButindex(sndIndex, sndData);
		return;

		break;

	case SendTarget_ToClanArea:
		SendToUserGuildArea(sndIndex, sndData);
		return;

		break;

	case SendTarget_ToPartyArea:
		SendToUserPartyArea(sndIndex, sndData);
		return;

		break;

	case SendTarget_ToAdminsAreaButConsejeros:
		SendToAdminsButConsejerosArea(sndIndex, sndData);
		return;

		break;

	case SendTarget_ToNPCArea:
		SendToNpcArea(sndIndex, sndData);
		return;

		break;

	case SendTarget_ToDiosesYclan:
		//	LoopC = m_Iterador_ProximoUserIndex(sndIndex);
		//	while (LoopC > 0) {
		//		if ((UserIndexSocketValido(LoopC))) {
		//			EnviarDatosASlot(LoopC, sndData);
		//		}
		//		LoopC = m_Iterador_ProximoUserIndex(sndIndex);
		//	}
		for (auto LoopC : guild_Iterador_ProximoUserIndex(sndIndex)) {
			if ((UserIndexSocketValido(LoopC))) {
				EnviarDatosASlot(LoopC, sndData);
			}
		}

//		LoopC = Iterador_ProximoGM(sndIndex);
//		while (LoopC > 0) {
//			if ((UserIndexSocketValido(LoopC))) {
//				EnviarDatosASlot(LoopC, sndData);
//			}
//			LoopC = Iterador_ProximoGM(sndIndex);
//		}

		for (auto LoopC : guild_Iterador_ProximoGM(sndIndex)) {
			if ((UserIndexSocketValido(LoopC))) {
				EnviarDatosASlot(LoopC, sndData);
			}
		}

		return;

		break;

	case SendTarget_ToConsejo:
		for (LoopC = (1); LoopC <= (LastUser); LoopC++) {
			if ((UserIndexSocketValido(LoopC))) {
				if (UserTienePrivilegio(LoopC, PlayerType_RoyalCouncil)) {
					EnviarDatosASlot(LoopC, sndData);
				}
			}
		}
		return;

		break;

	case SendTarget_ToConsejoCaos:
		for (LoopC = (1); LoopC <= (LastUser); LoopC++) {
			if ((UserIndexSocketValido(LoopC))) {
				if (UserTienePrivilegio(LoopC, PlayerType_ChaosCouncil)) {
					EnviarDatosASlot(LoopC, sndData);
				}
			}
		}
		return;

		break;

	case SendTarget_ToRolesMasters:
		for (LoopC = (1); LoopC <= (LastUser); LoopC++) {
			if ((UserIndexSocketValido(LoopC))) {
				if (UserTienePrivilegio(LoopC, PlayerType_RoleMaster)) {
					EnviarDatosASlot(LoopC, sndData);
				}
			}
		}
		return;

		break;

	case SendTarget_ToCiudadanos:
		for (LoopC = (1); LoopC <= (LastUser); LoopC++) {
			if ((UserIndexSocketValido(LoopC))) {
				if (!criminal(LoopC)) {
					EnviarDatosASlot(LoopC, sndData);
				}
			}
		}
		return;

		break;

	case SendTarget_ToCriminales:
		for (LoopC = (1); LoopC <= (LastUser); LoopC++) {
			if ((UserIndexSocketValido(LoopC))) {
				if (criminal(LoopC)) {
					EnviarDatosASlot(LoopC, sndData);
				}
			}
		}
		return;

		break;

	case SendTarget_ToReal:
		for (LoopC = (1); LoopC <= (LastUser); LoopC++) {
			if ((UserIndexSocketValido(LoopC))) {
				if (UserList[LoopC].Faccion.ArmadaReal == 1) {
					EnviarDatosASlot(LoopC, sndData);
				}
			}
		}
		return;

		break;

	case SendTarget_ToCaos:
		for (LoopC = (1); LoopC <= (LastUser); LoopC++) {
			if ((UserIndexSocketValido(LoopC))) {
				if (UserList[LoopC].Faccion.FuerzasCaos == 1) {
					EnviarDatosASlot(LoopC, sndData);
				}
			}
		}
		return;

		break;

	case SendTarget_ToCiudadanosYRMs:
		for (LoopC = (1); LoopC <= (LastUser); LoopC++) {
			if ((UserIndexSocketValido(LoopC))) {
				if (!criminal(LoopC) || UserTienePrivilegio(LoopC, PlayerType_RoleMaster)) {
					EnviarDatosASlot(LoopC, sndData);
				}
			}
		}
		return;

		break;

	case SendTarget_ToCriminalesYRMs:
		for (LoopC = (1); LoopC <= (LastUser); LoopC++) {
			if ((UserIndexSocketValido(LoopC))) {
				if (criminal(LoopC) || UserTienePrivilegio(LoopC, PlayerType_RoleMaster)) {
					EnviarDatosASlot(LoopC, sndData);
				}
			}
		}
		return;

		break;

	case SendTarget_ToRealYRMs:
		for (LoopC = (1); LoopC <= (LastUser); LoopC++) {
			if ((UserIndexSocketValido(LoopC))) {
				if (UserList[LoopC].Faccion.ArmadaReal == 1
						|| UserTienePrivilegio(LoopC, PlayerType_RoleMaster)) {
					EnviarDatosASlot(LoopC, sndData);
				}
			}
		}
		return;

		break;

	case SendTarget_ToCaosYRMs:
		for (LoopC = (1); LoopC <= (LastUser); LoopC++) {
			if ((UserIndexSocketValido(LoopC))) {
				if (UserList[LoopC].Faccion.FuerzasCaos == 1
						|| UserTienePrivilegio(LoopC, PlayerType_RoleMaster)) {
					EnviarDatosASlot(LoopC, sndData);
				}
			}
		}
		return;

		break;

	case SendTarget_ToHigherAdmins:
		for (LoopC = (1); LoopC <= (LastUser); LoopC++) {
			if (UserIndexSocketValido(LoopC)) {
				if (UserTieneAlgunPrivilegios(LoopC, PlayerType_Admin, PlayerType_Dios)) {
					EnviarDatosASlot(LoopC, sndData);
				}
			}
		}
		return;

		break;

	case SendTarget_ToGMsAreaButRmsOrCounselors:
		SendToGMsAreaButRmsOrCounselors(sndIndex, sndData);
		return;

		break;

	case SendTarget_ToUsersAreaButGMs:
		SendToUsersAreaButGMs(sndIndex, sndData);
		return;

		break;

	case SendTarget_ToUsersAndRmsAndCounselorsAreaButGMs:
		SendToUsersAndRmsAndCounselorsAreaButGMs(sndIndex, sndData);
		return;

		break;

	case SendTarget_ToAdminsButCounselors:
		for (LoopC = (1); LoopC <= (LastUser); LoopC++) {
			if (UserIndexSocketValido(LoopC)) {
				if (UserTieneAlgunPrivilegios(LoopC, PlayerType_Admin, PlayerType_Dios, PlayerType_SemiDios, PlayerType_RoleMaster)
						&& !UserTieneAlgunPrivilegios(LoopC, PlayerType_Consejero)) {
					EnviarDatosASlot(LoopC, sndData);
				}
			}
		}
		return;

		break;

	case SendTarget_ToAdminsButCounselorsAndRms:
		for (LoopC = (1); LoopC <= (LastUser); LoopC++) {
			if (UserIndexSocketValido(LoopC)) {
				if (UserTieneAlgunPrivilegios(LoopC, PlayerType_Admin, PlayerType_Dios, PlayerType_SemiDios)
						&& !UserTieneAlgunPrivilegios(LoopC, PlayerType_Consejero, PlayerType_RoleMaster)) {
						EnviarDatosASlot(LoopC, sndData);
				}
			}
		}
		return;

		break;

	case SendTarget_ToHigherAdminsButRMs:
		for (LoopC = (1); LoopC <= (LastUser); LoopC++) {
			if (UserIndexSocketValido(LoopC)) {
				if (UserTieneAlgunPrivilegios(LoopC, PlayerType_Admin, PlayerType_Dios)
						&& !UserTieneAlgunPrivilegios(LoopC, PlayerType_RoleMaster)) {
						EnviarDatosASlot(LoopC, sndData);
				}
			}
		}
		return;

		break;

	case SendTarget_ToRMsAndHigherAdmins:
		for (LoopC = (1); LoopC <= (LastUser); LoopC++) {
			if ((UserIndexSocketValido(LoopC))) {
				if (UserTieneAlgunPrivilegios(LoopC, PlayerType_RoleMaster, PlayerType_Admin, PlayerType_Dios)) {
					EnviarDatosASlot(LoopC, sndData);
				}
			}
		}
		return;
		break;

	case SendTarget_ToGM:
		throw std::runtime_error("SendData unhandled target: SendTarget_ToGM");
		break;

	case SendTarget_ToUserIndex:
		EnviarDatosASlot(sndIndex, sndData);
		break;
	}
}

void SendToUserArea(int UserIndex, std::string sdData) {
	/* '************************************************************** */
	/* 'Author: Lucio N. Tourrilhes (DuNga) */
	/* 'Last Modify Date: Unknow */
	/* ' */
	/* '************************************************************** */
	int LoopC;
	int tempIndex;

	int Map;
	int AreaX;
	int AreaY;

	Map = UserList[UserIndex].Pos.Map;
	AreaX = UserList[UserIndex].AreasInfo.AreaPerteneceX;
	AreaY = UserList[UserIndex].AreasInfo.AreaPerteneceY;

	if (!MapaValido(Map)) {
		return;
	}

	for (LoopC = (1); LoopC <= (ConnGroups[Map].CountEntrys); LoopC++) {
		tempIndex = ConnGroups[Map].UserEntrys[LoopC];

		/* 'Esta en el area? */
		if (UserList[tempIndex].AreasInfo.AreaReciveX && AreaX) {
			if (UserList[tempIndex].AreasInfo.AreaReciveY && AreaY) {
				if (UserIndexSocketValido(tempIndex)) {
					EnviarDatosASlot(tempIndex, sdData);
				}
			}
		}
	}
}

void SendToUserAreaButindex(int UserIndex, std::string sdData) {
	/* '************************************************************** */
	/* 'Author: Lucio N. Tourrilhes (DuNga) */
	/* 'Last Modify Date: Unknow */
	/* ' */
	/* '************************************************************** */
	int LoopC;
	int TempInt;
	int tempIndex;

	int Map;
	int AreaX;
	int AreaY;

	Map = UserList[UserIndex].Pos.Map;
	AreaX = UserList[UserIndex].AreasInfo.AreaPerteneceX;
	AreaY = UserList[UserIndex].AreasInfo.AreaPerteneceY;

	if (!MapaValido(Map)) {
		return;
	}

	for (LoopC = (1); LoopC <= (ConnGroups[Map].CountEntrys); LoopC++) {
		tempIndex = ConnGroups[Map].UserEntrys[LoopC];

		TempInt = UserList[tempIndex].AreasInfo.AreaReciveX && AreaX;
		/* 'Esta en el area? */
		if (TempInt) {
			TempInt = UserList[tempIndex].AreasInfo.AreaReciveY && AreaY;
			if (TempInt) {
				if (tempIndex != UserIndex) {
					if (UserIndexSocketValido(tempIndex)) {
						EnviarDatosASlot(tempIndex, sdData);
					}
				}
			}
		}
	}
}

void SendToDeadUserArea(int UserIndex, std::string sdData) {
	/* '************************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modify Date: Unknow */
	/* ' */
	/* '************************************************************** */
	int LoopC;
	int tempIndex;

	int Map;
	int AreaX;
	int AreaY;

	Map = UserList[UserIndex].Pos.Map;
	AreaX = UserList[UserIndex].AreasInfo.AreaPerteneceX;
	AreaY = UserList[UserIndex].AreasInfo.AreaPerteneceY;

	if (!MapaValido(Map)) {
		return;
	}

	for (LoopC = (1); LoopC <= (ConnGroups[Map].CountEntrys); LoopC++) {
		tempIndex = ConnGroups[Map].UserEntrys[LoopC];

		/* 'Esta en el area? */
		if (UserList[tempIndex].AreasInfo.AreaReciveX && AreaX) {
			if (UserList[tempIndex].AreasInfo.AreaReciveY && AreaY) {
				/* 'Dead and admins read */
				if (UserIndexSocketValido(tempIndex) == true
						&& (UserList[tempIndex].flags.Muerto == 1
								|| UserTieneAlgunPrivilegios(tempIndex, PlayerType_Admin, PlayerType_Dios, PlayerType_SemiDios, PlayerType_Consejero))) {
					EnviarDatosASlot(tempIndex, sdData);
				}
			}
		}
	}
}

void SendToUserGuildArea(int UserIndex, std::string sdData) {
	/* '************************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modify Date: Unknow */
	/* ' */
	/* '************************************************************** */
	int LoopC;
	int tempIndex;

	int Map;
	int AreaX;
	int AreaY;

	Map = UserList[UserIndex].Pos.Map;
	AreaX = UserList[UserIndex].AreasInfo.AreaPerteneceX;
	AreaY = UserList[UserIndex].AreasInfo.AreaPerteneceY;

	if (!MapaValido(Map)) {
		return;
	}

	if (UserList[UserIndex].GuildIndex == 0) {
		return;
	}

	for (LoopC = (1); LoopC <= (ConnGroups[Map].CountEntrys); LoopC++) {
		tempIndex = ConnGroups[Map].UserEntrys[LoopC];

		/* 'Esta en el area? */
		if (UserList[tempIndex].AreasInfo.AreaReciveX && AreaX) {
			if (UserList[tempIndex].AreasInfo.AreaReciveY && AreaY) {
				if (UserIndexSocketValido(tempIndex)
						&& (UserList[tempIndex].GuildIndex == UserList[UserIndex].GuildIndex
								|| (UserTienePrivilegio(tempIndex, PlayerType_Dios) && !UserTienePrivilegio(tempIndex, PlayerType_RoleMaster)))) {
					EnviarDatosASlot(tempIndex, sdData);
				}
			}
		}
	}
}

void SendToUserPartyArea(int UserIndex, std::string sdData) {
	/* '************************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modify Date: Unknow */
	/* ' */
	/* '************************************************************** */
	int LoopC;
	int tempIndex;

	int Map;
	int AreaX;
	int AreaY;

	Map = UserList[UserIndex].Pos.Map;
	AreaX = UserList[UserIndex].AreasInfo.AreaPerteneceX;
	AreaY = UserList[UserIndex].AreasInfo.AreaPerteneceY;

	if (!MapaValido(Map)) {
		return;
	}

	if (UserList[UserIndex].PartyIndex == 0) {
		return;
	}

	for (LoopC = (1); LoopC <= (ConnGroups[Map].CountEntrys); LoopC++) {
		tempIndex = ConnGroups[Map].UserEntrys[LoopC];

		/* 'Esta en el area? */
		if (UserList[tempIndex].AreasInfo.AreaReciveX && AreaX) {
			if (UserList[tempIndex].AreasInfo.AreaReciveY && AreaY) {
				if (UserIndexSocketValido(tempIndex)
						&& UserList[tempIndex].PartyIndex == UserList[UserIndex].PartyIndex) {
					EnviarDatosASlot(tempIndex, sdData);
				}
			}
		}
	}
}

void SendToAdminsButConsejerosArea(int UserIndex, std::string sdData) {
	/* '************************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modify Date: Unknow */
	/* ' */
	/* '************************************************************** */
	int LoopC;
	int tempIndex;

	int Map;
	int AreaX;
	int AreaY;

	Map = UserList[UserIndex].Pos.Map;
	AreaX = UserList[UserIndex].AreasInfo.AreaPerteneceX;
	AreaY = UserList[UserIndex].AreasInfo.AreaPerteneceY;

	if (!MapaValido(Map)) {
		return;
	}

	for (LoopC = (1); LoopC <= (ConnGroups[Map].CountEntrys); LoopC++) {
		tempIndex = ConnGroups[Map].UserEntrys[LoopC];

		/* 'Esta en el area? */
		if (UserList[tempIndex].AreasInfo.AreaReciveX && AreaX) {
			if (UserList[tempIndex].AreasInfo.AreaReciveY && AreaY) {
				if (UserIndexSocketValido(tempIndex)) {
					if (UserTieneAlgunPrivilegios(tempIndex, PlayerType_SemiDios, PlayerType_Dios, PlayerType_Admin)) {
						EnviarDatosASlot(tempIndex, sdData);
					}
				}
			}
		}
	}
}

void SendToNpcArea(int NpcIndex, std::string sdData) {
	/* '************************************************************** */
	/* 'Author: Lucio N. Tourrilhes (DuNga) */
	/* 'Last Modify Date: Unknow */
	/* ' */
	/* '************************************************************** */
	int LoopC;
	int TempInt;
	int tempIndex;

	int Map;
	int AreaX;
	int AreaY;

	Map = Npclist[NpcIndex].Pos.Map;
	AreaX = Npclist[NpcIndex].AreasInfo.AreaPerteneceX;
	AreaY = Npclist[NpcIndex].AreasInfo.AreaPerteneceY;

	if (!MapaValido(Map)) {
		return;
	}

	for (LoopC = (1); LoopC <= (ConnGroups[Map].CountEntrys); LoopC++) {
		tempIndex = ConnGroups[Map].UserEntrys[LoopC];

		TempInt = UserList[tempIndex].AreasInfo.AreaReciveX && AreaX;
		/* 'Esta en el area? */
		if (TempInt) {
			TempInt = UserList[tempIndex].AreasInfo.AreaReciveY && AreaY;
			if (TempInt) {
				if (UserIndexSocketValido(tempIndex)) {
					EnviarDatosASlot(tempIndex, sdData);
				}
			}
		}
	}
}

void SendToAreaByPos(int Map, int AreaX, int AreaY, std::string sdData) {
	/* '************************************************************** */
	/* 'Author: Lucio N. Tourrilhes (DuNga) */
	/* 'Last Modify Date: Unknow */
	/* ' */
	/* '************************************************************** */
	int LoopC;
	int TempInt;
	int tempIndex;

	AreaX = std::pow(2,	(AreaX / 9));
	AreaY = std::pow(2, (AreaY / 9));

	if (!MapaValido(Map)) {
		return;
	}

	for (LoopC = (1); LoopC <= (ConnGroups[Map].CountEntrys); LoopC++) {
		tempIndex = ConnGroups[Map].UserEntrys[LoopC];

		TempInt = UserList[tempIndex].AreasInfo.AreaReciveX && AreaX;
		/* 'Esta en el area? */
		if (TempInt) {
			TempInt = UserList[tempIndex].AreasInfo.AreaReciveY && AreaY;
			if (TempInt) {
				if (UserIndexSocketValido(tempIndex)) {
					EnviarDatosASlot(tempIndex, sdData);
				}
			}
		}
	}
}

void SendToMap(int Map, std::string sdData) {
	/* '************************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modify Date: 5/24/2007 */
	/* ' */
	/* '************************************************************** */
	int LoopC;
	int tempIndex;

	if (!MapaValido(Map)) {
		return;
	}

	for (LoopC = (1); LoopC <= (ConnGroups[Map].CountEntrys); LoopC++) {
		tempIndex = ConnGroups[Map].UserEntrys[LoopC];

		if (UserIndexSocketValido(tempIndex)) {
			EnviarDatosASlot(tempIndex, sdData);
		}
	}
}

void SendToMapButIndex(int UserIndex, std::string sdData) {
	/* '************************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modify Date: 5/24/2007 */
	/* ' */
	/* '************************************************************** */
	int LoopC;
	int Map;
	int tempIndex;

	Map = UserList[UserIndex].Pos.Map;

	if (!MapaValido(Map)) {
		return;
	}

	for (LoopC = (1); LoopC <= (ConnGroups[Map].CountEntrys); LoopC++) {
		tempIndex = ConnGroups[Map].UserEntrys[LoopC];

		if (tempIndex != UserIndex && UserIndexSocketValido(tempIndex)) {
			EnviarDatosASlot(tempIndex, sdData);
		}
	}
}

void SendToGMsAreaButRmsOrCounselors(int UserIndex, std::string sdData) {
	/* '************************************************************** */
	/* 'Author: Torres Patricio(Pato) */
	/* 'Last Modify Date: 12/02/2010 */
	/* '12/02/2010: ZaMa - Restrinjo solo a dioses, admins y gms. */
	/* '15/02/2010: ZaMa - Cambio el nombre de la funcion (viejo: ToGmsArea, nuevo: ToGmsAreaButRMsOrCounselors) */
	/* '************************************************************** */
	int LoopC;
	int tempIndex;

	int Map;
	int AreaX;
	int AreaY;

	Map = UserList[UserIndex].Pos.Map;
	AreaX = UserList[UserIndex].AreasInfo.AreaPerteneceX;
	AreaY = UserList[UserIndex].AreasInfo.AreaPerteneceY;

	if (!MapaValido(Map)) {
		return;
	}

	for (LoopC = (1); LoopC <= (ConnGroups[Map].CountEntrys); LoopC++) {
		tempIndex = ConnGroups[Map].UserEntrys[LoopC];

		/* 'Esta en el area? */
		if (UserList[tempIndex].AreasInfo.AreaReciveX && AreaX) {
			if (UserList[tempIndex].AreasInfo.AreaReciveY && AreaY) {
				if (UserIndexSocketValido(tempIndex)) {
					/* ' Exclusivo para dioses, admins y gms */
					if (EsGm(tempIndex)) {
						EnviarDatosASlot(tempIndex, sdData);
					}
				}
			}
		}
	}
}

void SendToUsersAreaButGMs(int UserIndex, std::string sdData) {
	/* '************************************************************** */
	/* 'Author: Torres Patricio(Pato) */
	/* 'Last Modify Date: 10/17/2009 */
	/* ' */
	/* '************************************************************** */
	int LoopC;
	int tempIndex;

	int Map;
	int AreaX;
	int AreaY;

	Map = UserList[UserIndex].Pos.Map;
	AreaX = UserList[UserIndex].AreasInfo.AreaPerteneceX;
	AreaY = UserList[UserIndex].AreasInfo.AreaPerteneceY;

	if (!MapaValido(Map)) {
		return;
	}

	for (LoopC = (1); LoopC <= (ConnGroups[Map].CountEntrys); LoopC++) {
		tempIndex = ConnGroups[Map].UserEntrys[LoopC];

		/* 'Esta en el area? */
		if (UserList[tempIndex].AreasInfo.AreaReciveX && AreaX) {
			if (UserList[tempIndex].AreasInfo.AreaReciveY && AreaY) {
				if (UserIndexSocketValido(tempIndex)) {
					if (UserTienePrivilegio(tempIndex, PlayerType_User)) {
						EnviarDatosASlot(tempIndex, sdData);
					}
				}
			}
		}
	}
}

void SendToUsersAndRmsAndCounselorsAreaButGMs(int UserIndex, std::string sdData) {
	/* '************************************************************** */
	/* 'Author: Torres Patricio(Pato) */
	/* 'Last Modify Date: 10/17/2009 */
	/* ' */
	/* '************************************************************** */
	int LoopC;
	int tempIndex;

	int Map;
	int AreaX;
	int AreaY;

	Map = UserList[UserIndex].Pos.Map;
	AreaX = UserList[UserIndex].AreasInfo.AreaPerteneceX;
	AreaY = UserList[UserIndex].AreasInfo.AreaPerteneceY;

	if (!MapaValido(Map)) {
		return;
	}

	for (LoopC = (1); LoopC <= (ConnGroups[Map].CountEntrys); LoopC++) {
		tempIndex = ConnGroups[Map].UserEntrys[LoopC];

		/* 'Esta en el area? */
		if (UserList[tempIndex].AreasInfo.AreaReciveX && AreaX) {
			if (UserList[tempIndex].AreasInfo.AreaReciveY && AreaY) {
				if (UserIndexSocketValido(tempIndex)) {
					if (UserTieneAlgunPrivilegios (tempIndex, PlayerType_User, PlayerType_Consejero, PlayerType_RoleMaster)) {
						EnviarDatosASlot(tempIndex, sdData);
					}
				}
			}
		}
	}
}

void AlertarFaccionarios(int UserIndex) {
	/* '************************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modify Date: 17/11/2009 */
	/* 'Alerta a los faccionarios, dandoles una orientacion */
	/* '************************************************************** */
	int LoopC;
	int tempIndex;
	int Map;
	FontTypeNames Font;

	if (esCaos(UserIndex)) {
		Font = FontTypeNames_FONTTYPE_CONSEJOCAOS;
	} else {
		Font = FontTypeNames_FONTTYPE_CONSEJO;
	}

	Map = UserList[UserIndex].Pos.Map;

	if (!MapaValido(Map)) {
		return;
	}

	for (LoopC = (1); LoopC <= (ConnGroups[Map].CountEntrys); LoopC++) {
		tempIndex = ConnGroups[Map].UserEntrys[LoopC];

		if (UserIndexSocketValido(tempIndex)) {
			if (tempIndex != UserIndex) {
				/* ' Solo se envia a los de la misma faccion */
				if (SameFaccion(UserIndex, tempIndex)) {
					WriteConsoleMsg(tempIndex,
							"Escuchas el llamado de un companero que proviene del "
									+ GetDireccion(UserIndex, tempIndex), Font);
				}
			}
		}
	}
}
