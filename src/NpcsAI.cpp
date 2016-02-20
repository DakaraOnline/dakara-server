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

#include "NpcsAI.h"

const int ELEMENTALFUEGO = 93;
const int ELEMENTALTIERRA = 94;
const int ELEMENTALAGUA = 92;

/* 'Damos a los NPCs el mismo rango de visiï¿½n que un PJ */
const int RANGO_VISION_X = 8;
const int RANGO_VISION_Y = 6;

void GuardiasAI(int NpcIndex, bool DelCaos) {
	/* '*************************************************** */
	/* 'Autor: Unknown (orginal version) */
	/* 'Last Modification: 12/01/2010 (ZaMa) */
	/* '14/09/2009: ZaMa - Now npcs don't atack protected users. */
	/* '12/01/2010: ZaMa - Los npcs no atacan druidas mimetizados con npcs */
	/* '*************************************************** */
	struct WorldPos nPos;
	int headingloop;
	int UI;
	bool UserProtected;

	for (headingloop = (eHeading_NORTH); headingloop <= (eHeading_WEST);
			headingloop++) {
		nPos = Npclist[NpcIndex].Pos;
		if (Npclist[NpcIndex].flags.Inmovilizado == 0
				|| headingloop == Npclist[NpcIndex].Char.heading) {
			HeadtoPos(static_cast<eHeading>(headingloop), nPos);
			if (InMapBounds(nPos.Map, nPos.X, nPos.Y)) {
				UI = MapData[nPos.Map][nPos.X][nPos.Y].UserIndex;
				if (UI > 0) {
					UserProtected = !IntervaloPermiteSerAtacado(UI)
							&& UserList[UI].flags.NoPuedeSerAtacado;
					UserProtected = UserProtected || UserList[UI].flags.Ignorado
							|| UserList[UI].flags.EnConsulta;

					if (UserList[UI].flags.Muerto == 0
							&& UserList[UI].flags.AdminPerseguible
							&& !UserProtected) {
						/* 'ï¿½ES CRIMINAL? */
						if (!DelCaos) {
							if (criminal(UI)) {
								if (NpcAtacaUser(NpcIndex, UI)) {
									ChangeNPCChar(NpcIndex,
											Npclist[NpcIndex].Char.body,
											Npclist[NpcIndex].Char.Head,
											static_cast<eHeading>(headingloop));
								}
								return;
							} else if (Npclist[NpcIndex].flags.AttackedBy
									== UserList[UI].Name
									&& !Npclist[NpcIndex].flags.Follow) {

								if (NpcAtacaUser(NpcIndex, UI)) {
									ChangeNPCChar(NpcIndex,
											Npclist[NpcIndex].Char.body,
											Npclist[NpcIndex].Char.Head,
											static_cast<eHeading>(headingloop));
								}
								return;
							}
						} else {
							if (!criminal(UI)) {
								if (NpcAtacaUser(NpcIndex, UI)) {
									ChangeNPCChar(NpcIndex,
											Npclist[NpcIndex].Char.body,
											Npclist[NpcIndex].Char.Head,
											static_cast<eHeading>(headingloop));
								}
								return;
							} else if (Npclist[NpcIndex].flags.AttackedBy
									== UserList[UI].Name
									&& !Npclist[NpcIndex].flags.Follow) {

								if (NpcAtacaUser(NpcIndex, UI)) {
									ChangeNPCChar(NpcIndex,
											Npclist[NpcIndex].Char.body,
											Npclist[NpcIndex].Char.Head,
											static_cast<eHeading>(headingloop));
								}
								return;
							}
						}
					}
				}
			}
			/* 'not inmovil */
		}
	}

	RestoreOldMovement(NpcIndex);
}

/* '' */
/* ' Handles the evil npcs' artificial intelligency. */
/* ' */
/* ' @param NpcIndex Specifies reference to the npc */
void HostilMalvadoAI(int NpcIndex) {
	/* '************************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modify Date: 12/01/2010 (ZaMa) */
	/* '28/04/2009: ZaMa - Now those NPCs who doble attack, have 50% of posibility of casting a spell on user. */
	/* '14/09/200*: ZaMa - Now npcs don't atack protected users. */
	/* '12/01/2010: ZaMa - Los npcs no atacan druidas mimetizados con npcs */
	/* '************************************************************** */
	struct WorldPos nPos;
	int headingloop;
	int UI;
	int NPCI;
	bool atacoPJ;
	bool UserProtected;

	atacoPJ = false;

	for (headingloop = (eHeading_NORTH); headingloop <= (eHeading_WEST);
			headingloop++) {
		nPos = Npclist[NpcIndex].Pos;
		if (Npclist[NpcIndex].flags.Inmovilizado == 0
				|| Npclist[NpcIndex].Char.heading == headingloop) {
			HeadtoPos(static_cast<eHeading>(headingloop), nPos);
			if (InMapBounds(nPos.Map, nPos.X, nPos.Y)) {
				UI = MapData[nPos.Map][nPos.X][nPos.Y].UserIndex;
				NPCI = MapData[nPos.Map][nPos.X][nPos.Y].NpcIndex;
				if (UI > 0 && !atacoPJ) {
					UserProtected = !IntervaloPermiteSerAtacado(UI)
							&& UserList[UI].flags.NoPuedeSerAtacado;
					UserProtected = UserProtected || UserList[UI].flags.Ignorado
							|| UserList[UI].flags.EnConsulta;

					if (UserList[UI].flags.Muerto == 0
							&& UserList[UI].flags.AdminPerseguible
							&& (!UserProtected)) {

						atacoPJ = true;
						if (Npclist[NpcIndex].Movement == TipoAI_NpcObjeto) {
							/* ' Los npc objeto no atacan siempre al mismo usuario */
							if (RandomNumber(1, 3) == 3) {
								atacoPJ = false;
							}
						}

						if (atacoPJ) {
							if (Npclist[NpcIndex].flags.LanzaSpells) {
								if (Npclist[NpcIndex].flags.AtacaDoble) {
									if ((RandomNumber(0, 1))) {
										if (NpcAtacaUser(NpcIndex, UI)) {
											ChangeNPCChar(NpcIndex,
													Npclist[NpcIndex].Char.body,
													Npclist[NpcIndex].Char.Head,
													static_cast<eHeading>(headingloop));
										}
										return;
									}
								}

								ChangeNPCChar(NpcIndex,
										Npclist[NpcIndex].Char.body,
										Npclist[NpcIndex].Char.Head,
										static_cast<eHeading>(headingloop));
								NpcLanzaUnSpell(NpcIndex, UI);
							}
						}
						if (NpcAtacaUser(NpcIndex, UI)) {
							ChangeNPCChar(NpcIndex, Npclist[NpcIndex].Char.body,
									Npclist[NpcIndex].Char.Head, static_cast<eHeading>(headingloop));
						}
						return;

					}
				} else if (NPCI > 0) {
					if (Npclist[NPCI].MaestroUser > 0
							&& Npclist[NPCI].flags.Paralizado == 0) {
						ChangeNPCChar(NpcIndex, Npclist[NpcIndex].Char.body,
								Npclist[NpcIndex].Char.Head, static_cast<eHeading>(headingloop));
						NpcAtacaNpc(NpcIndex, NPCI, false);
						return;
					}
				}
			}
			/* 'inmo */
		}
	}

	RestoreOldMovement(NpcIndex);
}

void HostilBuenoAI(int NpcIndex) {
	/* '*************************************************** */
	/* 'Autor: Unknown (orginal version) */
	/* 'Last Modification: 12/01/2010 (ZaMa) */
	/* '14/09/2009: ZaMa - Now npcs don't atack protected users. */
	/* '12/01/2010: ZaMa - Los npcs no atacan druidas mimetizados con npcs */
	/* '*************************************************** */
	struct WorldPos nPos;
	int headingloop;
	int UI;
	bool UserProtected;

	for (headingloop = (eHeading_NORTH); headingloop <= (eHeading_WEST);
			headingloop++) {
		nPos = Npclist[NpcIndex].Pos;
		if (Npclist[NpcIndex].flags.Inmovilizado == 0
				|| Npclist[NpcIndex].Char.heading == headingloop) {
			HeadtoPos(static_cast<eHeading>(headingloop), nPos);
			if (InMapBounds(nPos.Map, nPos.X, nPos.Y)) {
				UI = MapData[nPos.Map][nPos.X][nPos.Y].UserIndex;
				if (UI > 0) {
					if (UserList[UI].Name
							== Npclist[NpcIndex].flags.AttackedBy) {

						UserProtected = !IntervaloPermiteSerAtacado(UI)
								&& UserList[UI].flags.NoPuedeSerAtacado;
						UserProtected = UserProtected
								|| UserList[UI].flags.Ignorado
								|| UserList[UI].flags.EnConsulta;

						if (UserList[UI].flags.Muerto == 0
								&& UserList[UI].flags.AdminPerseguible
								&& !UserProtected) {
							if (Npclist[NpcIndex].flags.LanzaSpells > 0) {
								NpcLanzaUnSpell(NpcIndex, UI);
							}

							if (NpcAtacaUser(NpcIndex, UI)) {
								ChangeNPCChar(NpcIndex,
										Npclist[NpcIndex].Char.body,
										Npclist[NpcIndex].Char.Head,
										static_cast<eHeading>(headingloop));
							}
							return;
						}
					}
				}
			}
		}
	}

	RestoreOldMovement(NpcIndex);
}

void IrUsuarioCercano(int NpcIndex) {
	/* '*************************************************** */
	/* 'Autor: Unknown (orginal version) */
	/* 'Last Modification: 25/07/2010 (ZaMa) */
	/* '14/09/2009: ZaMa - Now npcs don't follow protected users. */
	/* '12/01/2010: ZaMa - Los npcs no atacan druidas mimetizados con npcs */
	/* '25/07/2010: ZaMa - Agrego una validacion temporal para evitar que los npcs ataquen a usuarios de mapas difernetes. */
	/* '*************************************************** */
	int tHeading;
	int UserIndex;
	int SignoNS;
	int SignoEO;
	int i;
	bool UserProtected;

	if (Npclist[NpcIndex].flags.Inmovilizado == 1) {
		switch (Npclist[NpcIndex].Char.heading) {
		case eHeading_NORTH:
			SignoNS = -1;
			SignoEO = 0;

			break;

		case eHeading_EAST:
			SignoNS = 0;
			SignoEO = 1;

			break;

		case eHeading_SOUTH:
			SignoNS = 1;
			SignoEO = 0;

			break;

		case eHeading_WEST:
			SignoEO = -1;
			SignoNS = 0;
			break;

		default:
			SignoEO = SignoNS = 0;
			break;
		}

		for (i = (1); i <= (ConnGroups[Npclist[NpcIndex].Pos.Map].CountEntrys);
				i++) {
			UserIndex = ConnGroups[Npclist[NpcIndex].Pos.Map].UserEntrys[i];

			/* 'Is it in it's range of vision?? */
			if (vb6::Abs(UserList[UserIndex].Pos.X - Npclist[NpcIndex].Pos.X)
					<= RANGO_VISION_X
					&& vb6::Sgn(UserList[UserIndex].Pos.X - Npclist[NpcIndex].Pos.X)
							== SignoEO) {
				if (vb6::Abs(
						UserList[UserIndex].Pos.Y - Npclist[NpcIndex].Pos.Y)
						<= RANGO_VISION_Y
						&& vb6::Sgn(UserList[UserIndex].Pos.Y
								- Npclist[NpcIndex].Pos.Y) == SignoNS) {

					UserProtected = !IntervaloPermiteSerAtacado(UserIndex)
							&& UserList[UserIndex].flags.NoPuedeSerAtacado;
					UserProtected = UserProtected
							|| UserList[UserIndex].flags.Ignorado
							|| UserList[UserIndex].flags.EnConsulta;

					if (UserList[UserIndex].flags.Muerto == 0) {
						if (!UserProtected) {
							if (Npclist[NpcIndex].flags.LanzaSpells != 0) {
								NpcLanzaUnSpell(NpcIndex, UserIndex);
							}
							return;
						}
					}

				}
			}
		}

		/* ' No esta inmobilizado */
	} else {

		/* ' Tiene prioridad de seguir al usuario al que le pertenece si esta en el rango de vision */
		int OwnerIndex;

		OwnerIndex = Npclist[NpcIndex].Owner;
		if (OwnerIndex > 0) {

			/* ' TODO: Es temporal hatsa reparar un bug que hace que ataquen a usuarios de otros mapas */
			if (UserList[OwnerIndex].Pos.Map == Npclist[NpcIndex].Pos.Map) {

				/* 'Is it in it's range of vision?? */
				if (vb6::Abs(
						UserList[OwnerIndex].Pos.X - Npclist[NpcIndex].Pos.X)
						<= RANGO_VISION_X) {
					if (vb6::Abs(
							UserList[OwnerIndex].Pos.Y
									- Npclist[NpcIndex].Pos.Y)
							<= RANGO_VISION_Y) {

						/* ' va hacia el si o esta invi ni oculto */
						if (UserList[OwnerIndex].flags.invisible == 0
								&& UserList[OwnerIndex].flags.Oculto == 0
								&& !UserList[OwnerIndex].flags.EnConsulta
								&& !UserList[OwnerIndex].flags.Ignorado) {
							if (Npclist[NpcIndex].flags.LanzaSpells != 0) {
								NpcLanzaUnSpell(NpcIndex, OwnerIndex);
							}

							tHeading = FindDirection(Npclist[NpcIndex].Pos,
									UserList[OwnerIndex].Pos);
							MoveNPCChar(NpcIndex, tHeading);
							return;
						}
					}
				}

				/* ' Esto significa que esta bugueado.. Lo logueo, y "reparo" el error a mano (Todo temporal) */
			} else {
				LogError(
						"El npc: " + Npclist[NpcIndex].Name + "(" + std::to_string(NpcIndex)
								+ "), intenta atacar a "
								+ UserList[OwnerIndex].Name + "(Index: "
								+ std::to_string(OwnerIndex) + ", Mapa: "
								+ std::to_string(UserList[OwnerIndex].Pos.Map)
								+ ") desde el mapa "
								+ std::to_string(Npclist[NpcIndex].Pos.Map));
				Npclist[NpcIndex].Owner = 0;
			}
		}

		/* ' No le pertenece a nadie o el dueno no esta en el rango de vision, sigue a cualquiera */
		for (i = (1); i <= (ConnGroups[Npclist[NpcIndex].Pos.Map].CountEntrys);
				i++) {
			UserIndex = ConnGroups[Npclist[NpcIndex].Pos.Map].UserEntrys[i];

			/* 'Is it in it's range of vision?? */
			if (vb6::Abs(UserList[UserIndex].Pos.X - Npclist[NpcIndex].Pos.X)
					<= RANGO_VISION_X) {
				if (vb6::Abs(
						UserList[UserIndex].Pos.Y - Npclist[NpcIndex].Pos.Y)
						<= RANGO_VISION_Y) {

					UserProtected = !IntervaloPermiteSerAtacado(UserIndex)
							&& UserList[UserIndex].flags.NoPuedeSerAtacado;
					UserProtected = UserProtected
							|| UserList[UserIndex].flags.Ignorado
							|| UserList[UserIndex].flags.EnConsulta;

					if (UserList[UserIndex].flags.Muerto == 0
							&& UserList[UserIndex].flags.invisible == 0
							&& UserList[UserIndex].flags.Oculto == 0
							&& UserList[UserIndex].flags.AdminPerseguible
							&& !UserProtected) {

						if (Npclist[NpcIndex].flags.LanzaSpells != 0) {
							NpcLanzaUnSpell(NpcIndex, UserIndex);
						}

						tHeading = FindDirection(Npclist[NpcIndex].Pos,
								UserList[UserIndex].Pos);
						MoveNPCChar(NpcIndex, tHeading);
						return;
					}

				}
			}
		}

		/* 'Si llega aca es que no habï¿½a ningï¿½n usuario cercano vivo. */
		/* 'A bailar. Pablo (ToxicWaste) */
		if (RandomNumber(0, 10) == 0) {
			MoveNPCChar(NpcIndex,
					vb6::CByte(RandomNumber(eHeading_NORTH, eHeading_WEST)));
		}

	}

	RestoreOldMovement(NpcIndex);
}

/* '' */
/* ' Makes a Pet / Summoned Npc to Follow an enemy */
/* ' */
/* ' @param NpcIndex Specifies reference to the npc */
void SeguirAgresor(int NpcIndex) {
	/* '************************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modify by: Marco Vanotti (MarKoxX) */
	/* 'Last Modify Date: 08/16/2008 */
	/* '08/16/2008: MarKoxX - Now pets that do melï¿½ attacks have to be near the enemy to attack. */
	/* '************************************************************** */
	int tHeading;
	int UI;

	int i;

	int SignoNS;
	int SignoEO;

	if (Npclist[NpcIndex].flags.Paralizado == 1
			|| Npclist[NpcIndex].flags.Inmovilizado == 1) {
		switch (Npclist[NpcIndex].Char.heading) {
		case eHeading_NORTH:
			SignoNS = -1;
			SignoEO = 0;

			break;

		case eHeading_EAST:
			SignoNS = 0;
			SignoEO = 1;

			break;

		case eHeading_SOUTH:
			SignoNS = 1;
			SignoEO = 0;

			break;

		case eHeading_WEST:
			SignoEO = -1;
			SignoNS = 0;
			break;

		default:
			SignoEO = SignoNS = 0;
			break;
		}

		for (i = (1); i <= (ConnGroups[Npclist[NpcIndex].Pos.Map].CountEntrys);
				i++) {
			UI = ConnGroups[Npclist[NpcIndex].Pos.Map].UserEntrys[i];

			/* 'Is it in it's range of vision?? */
			if (vb6::Abs(UserList[UI].Pos.X - Npclist[NpcIndex].Pos.X)
					<= RANGO_VISION_X
					&& vb6::Sgn(UserList[UI].Pos.X - Npclist[NpcIndex].Pos.X)
							== SignoEO) {
				if (vb6::Abs(UserList[UI].Pos.Y - Npclist[NpcIndex].Pos.Y)
						<= RANGO_VISION_Y
						&& vb6::Sgn(UserList[UI].Pos.Y - Npclist[NpcIndex].Pos.Y)
								== SignoNS) {

					if (UserList[UI].Name
							== Npclist[NpcIndex].flags.AttackedBy) {
						if (Npclist[NpcIndex].MaestroUser > 0) {
							if (!criminal(Npclist[NpcIndex].MaestroUser)
									&& !criminal(UI)
									&& (UserList[Npclist[NpcIndex].MaestroUser].flags.Seguro
											|| UserList[Npclist[NpcIndex].MaestroUser].Faccion.ArmadaReal
													== 1)) {
								WriteConsoleMsg(Npclist[NpcIndex].MaestroUser,
										"La mascota no atacará a ciudadanos si eres miembro del ejército real o tienes el seguro activado.",
										FontTypeNames_FONTTYPE_INFO);
								FlushBuffer(Npclist[NpcIndex].MaestroUser);
								Npclist[NpcIndex].flags.AttackedBy = "";
								return;
							}
						}

						if (UserList[UI].flags.Muerto == 0
								&& UserList[UI].flags.invisible == 0
								&& UserList[UI].flags.Oculto == 0) {
							if (Npclist[NpcIndex].flags.LanzaSpells > 0) {
								NpcLanzaUnSpell(NpcIndex, UI);
							} else {
								if (Distancia(UserList[UI].Pos,
										Npclist[NpcIndex].Pos) <= 1) {
									/* ' TODO : Set this a separate AI for Elementals and Druid's pets */
									if (Npclist[NpcIndex].Numero != 92) {
										NpcAtacaUser(NpcIndex, UI);
									}
								}
							}
							return;
						}
					}

				}
			}

		}
	} else {
		for (i = (1); i <= (ConnGroups[Npclist[NpcIndex].Pos.Map].CountEntrys);
				i++) {
			UI = ConnGroups[Npclist[NpcIndex].Pos.Map].UserEntrys[i];

			/* 'Is it in it's range of vision?? */
			if (vb6::Abs(UserList[UI].Pos.X - Npclist[NpcIndex].Pos.X)
					<= RANGO_VISION_X) {
				if (vb6::Abs(UserList[UI].Pos.Y - Npclist[NpcIndex].Pos.Y)
						<= RANGO_VISION_Y) {

					if (UserList[UI].Name
							== Npclist[NpcIndex].flags.AttackedBy) {
						if (Npclist[NpcIndex].MaestroUser > 0) {
							if (!criminal(Npclist[NpcIndex].MaestroUser)
									&& !criminal(UI)
									&& (UserList[Npclist[NpcIndex].MaestroUser].flags.Seguro
											|| UserList[Npclist[NpcIndex].MaestroUser].Faccion.ArmadaReal
													== 1)) {
								WriteConsoleMsg(Npclist[NpcIndex].MaestroUser,
										"La mascota no atacará a ciudadanos si eres miembro del ejército real o tienes el seguro activado.",
										FontTypeNames_FONTTYPE_INFO);
								FlushBuffer(Npclist[NpcIndex].MaestroUser);
								Npclist[NpcIndex].flags.AttackedBy = "";
								FollowAmo(NpcIndex);
								return;
							}
						}

						if (UserList[UI].flags.Muerto == 0
								&& UserList[UI].flags.invisible == 0
								&& UserList[UI].flags.Oculto == 0) {
							if (Npclist[NpcIndex].flags.LanzaSpells > 0) {
								NpcLanzaUnSpell(NpcIndex, UI);
							} else {
								if (Distancia(UserList[UI].Pos,
										Npclist[NpcIndex].Pos) <= 1) {
									/* ' TODO : Set this a separate AI for Elementals and Druid's pets */
									if (Npclist[NpcIndex].Numero != 92) {
										NpcAtacaUser(NpcIndex, UI);
									}
								}
							}

							tHeading = FindDirection(Npclist[NpcIndex].Pos,
									UserList[UI].Pos);
							MoveNPCChar(NpcIndex, tHeading);

							return;
						}
					}

				}
			}

		}
	}

	RestoreOldMovement(NpcIndex);
}

void RestoreOldMovement(int NpcIndex) {
	if (Npclist[NpcIndex].MaestroUser == 0) {
		Npclist[NpcIndex].Movement = Npclist[NpcIndex].flags.OldMovement;
		Npclist[NpcIndex].Hostile = Npclist[NpcIndex].flags.OldHostil;
		Npclist[NpcIndex].flags.AttackedBy = "";
	}
}

void PersigueCiudadano(int NpcIndex) {
	/* '*************************************************** */
	/* 'Autor: Unknown (orginal version) */
	/* 'Last Modification: 12/01/2010 (ZaMa) */
	/* '14/09/2009: ZaMa - Now npcs don't follow protected users. */
	/* '12/01/2010: ZaMa - Los npcs no atacan druidas mimetizados con npcs. */
	/* '*************************************************** */
	int UserIndex;
	int tHeading;
	int i;
	bool UserProtected;

	for (i = (1); i <= (ConnGroups[Npclist[NpcIndex].Pos.Map].CountEntrys);
			i++) {
		UserIndex = ConnGroups[Npclist[NpcIndex].Pos.Map].UserEntrys[i];

		/* 'Is it in it's range of vision?? */
		if (vb6::Abs(UserList[UserIndex].Pos.X - Npclist[NpcIndex].Pos.X)
				<= RANGO_VISION_X) {
			if (vb6::Abs(UserList[UserIndex].Pos.Y - Npclist[NpcIndex].Pos.Y)
					<= RANGO_VISION_Y) {

				if (!criminal(UserIndex)) {

					UserProtected = !IntervaloPermiteSerAtacado(UserIndex)
							&& UserList[UserIndex].flags.NoPuedeSerAtacado;
					UserProtected = UserProtected
							|| UserList[UserIndex].flags.Ignorado
							|| UserList[UserIndex].flags.EnConsulta;

					if (UserList[UserIndex].flags.Muerto == 0
							&& UserList[UserIndex].flags.invisible == 0
							&& UserList[UserIndex].flags.Oculto == 0
							&& UserList[UserIndex].flags.AdminPerseguible
							&& !UserProtected) {

						if (Npclist[NpcIndex].flags.LanzaSpells > 0) {
							NpcLanzaUnSpell(NpcIndex, UserIndex);
						}
						tHeading = FindDirection(Npclist[NpcIndex].Pos,
								UserList[UserIndex].Pos);
						MoveNPCChar(NpcIndex, tHeading);
						return;
					}
				}

			}
		}

	}

	RestoreOldMovement(NpcIndex);
}

void PersigueCriminal(int NpcIndex) {
	/* '*************************************************** */
	/* 'Autor: Unknown (orginal version) */
	/* 'Last Modification: 12/01/2010 (ZaMa) */
	/* '14/09/2009: ZaMa - Now npcs don't follow protected users. */
	/* '12/01/2010: ZaMa - Los npcs no atacan druidas mimetizados con npcs. */
	/* '*************************************************** */
	int UserIndex;
	int tHeading;
	int i;
	int SignoNS;
	int SignoEO;
	bool UserProtected;

	if (Npclist[NpcIndex].flags.Inmovilizado == 1) {
		switch (Npclist[NpcIndex].Char.heading) {
		case eHeading_NORTH:
			SignoNS = -1;
			SignoEO = 0;

			break;

		case eHeading_EAST:
			SignoNS = 0;
			SignoEO = 1;

			break;

		case eHeading_SOUTH:
			SignoNS = 1;
			SignoEO = 0;

			break;

		case eHeading_WEST:
			SignoEO = -1;
			SignoNS = 0;
			break;

		default:
			SignoEO = SignoNS = 0;
			break;
		}

		for (i = (1); i <= (ConnGroups[Npclist[NpcIndex].Pos.Map].CountEntrys);
				i++) {
			UserIndex = ConnGroups[Npclist[NpcIndex].Pos.Map].UserEntrys[i];

			/* 'Is it in it's range of vision?? */
			if (vb6::Abs(UserList[UserIndex].Pos.X - Npclist[NpcIndex].Pos.X)
					<= RANGO_VISION_X
					&& vb6::Sgn(UserList[UserIndex].Pos.X - Npclist[NpcIndex].Pos.X)
							== SignoEO) {
				if (vb6::Abs(
						UserList[UserIndex].Pos.Y - Npclist[NpcIndex].Pos.Y)
						<= RANGO_VISION_Y
						&& vb6::Sgn(UserList[UserIndex].Pos.Y
								- Npclist[NpcIndex].Pos.Y) == SignoNS) {

					if (criminal(UserIndex)) {

						UserProtected = !IntervaloPermiteSerAtacado(UserIndex)
								&& UserList[UserIndex].flags.NoPuedeSerAtacado;
						UserProtected = UserProtected
								|| UserList[UserIndex].flags.Ignorado
								|| UserList[UserIndex].flags.EnConsulta;

						if (UserList[UserIndex].flags.Muerto == 0
								&& UserList[UserIndex].flags.invisible == 0
								&& UserList[UserIndex].flags.Oculto == 0
								&& UserList[UserIndex].flags.AdminPerseguible
								&& !UserProtected) {

							if (Npclist[NpcIndex].flags.LanzaSpells > 0) {
								NpcLanzaUnSpell(NpcIndex, UserIndex);
							}
							return;
						}
					}

				}
			}
		}
	} else {
		for (i = (1); i <= (ConnGroups[Npclist[NpcIndex].Pos.Map].CountEntrys);
				i++) {
			UserIndex = ConnGroups[Npclist[NpcIndex].Pos.Map].UserEntrys[i];

			/* 'Is it in it's range of vision?? */
			if (vb6::Abs(UserList[UserIndex].Pos.X - Npclist[NpcIndex].Pos.X)
					<= RANGO_VISION_X) {
				if (vb6::Abs(
						UserList[UserIndex].Pos.Y - Npclist[NpcIndex].Pos.Y)
						<= RANGO_VISION_Y) {

					if (criminal(UserIndex)) {

						UserProtected = !IntervaloPermiteSerAtacado(UserIndex)
								&& UserList[UserIndex].flags.NoPuedeSerAtacado;
						UserProtected = UserProtected
								|| UserList[UserIndex].flags.Ignorado;

						if (UserList[UserIndex].flags.Muerto == 0
								&& UserList[UserIndex].flags.invisible == 0
								&& UserList[UserIndex].flags.Oculto == 0
								&& UserList[UserIndex].flags.AdminPerseguible
								&& !UserProtected) {
							if (Npclist[NpcIndex].flags.LanzaSpells > 0) {
								NpcLanzaUnSpell(NpcIndex, UserIndex);
							}
							if (Npclist[NpcIndex].flags.Inmovilizado == 1) {
								return;
							}
							tHeading = FindDirection(Npclist[NpcIndex].Pos,
									UserList[UserIndex].Pos);
							MoveNPCChar(NpcIndex, tHeading);
							return;
						}
					}

				}
			}

		}
	}

	RestoreOldMovement(NpcIndex);
}

void SeguirAmo(int NpcIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int tHeading;
	int UI;

	if (Npclist[NpcIndex].Target == 0 && Npclist[NpcIndex].TargetNPC == 0) {
		UI = Npclist[NpcIndex].MaestroUser;

		if (UI > 0) {
			/* 'Is it in it's range of vision?? */
			if (vb6::Abs(UserList[UI].Pos.X - Npclist[NpcIndex].Pos.X)
					<= RANGO_VISION_X) {
				if (vb6::Abs(UserList[UI].Pos.Y - Npclist[NpcIndex].Pos.Y)
						<= RANGO_VISION_Y) {
					if (UserList[UI].flags.Muerto == 0
							&& UserList[UI].flags.invisible == 0
							&& UserList[UI].flags.Oculto == 0
							&& Distancia(Npclist[NpcIndex].Pos,
									UserList[UI].Pos) > 3) {
						tHeading = FindDirection(Npclist[NpcIndex].Pos,
								UserList[UI].Pos);
						MoveNPCChar(NpcIndex, tHeading);
						return;
					}
				}
			}
		}
	}

	RestoreOldMovement(NpcIndex);
}

void AiNpcAtacaNpc(int NpcIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int tHeading;
	int X;
	int Y;
	int NI;
	bool bNoEsta = false;

	int SignoNS;
	int SignoEO;

	if (Npclist[NpcIndex].flags.Inmovilizado == 1) {
		switch (Npclist[NpcIndex].Char.heading) {
		case eHeading_NORTH:
			SignoNS = -1;
			SignoEO = 0;

			break;

		case eHeading_EAST:
			SignoNS = 0;
			SignoEO = 1;

			break;

		case eHeading_SOUTH:
			SignoNS = 1;
			SignoEO = 0;

			break;

		case eHeading_WEST:
			SignoEO = -1;
			SignoNS = 0;
			break;

		default:
			SignoEO = SignoNS = 0;
			break;
		}

		for (Y = (Npclist[NpcIndex].Pos.Y);
				((vb6::IIf(SignoNS == 0, 1, SignoNS)) > 0) ?
						(Y
								<= (Npclist[NpcIndex].Pos.Y
										+ SignoNS * RANGO_VISION_Y)) :
						(Y
								>= (Npclist[NpcIndex].Pos.Y
										+ SignoNS * RANGO_VISION_Y));
				Y = Y + (vb6::IIf(SignoNS == 0, 1, SignoNS))) {
			for (X = (Npclist[NpcIndex].Pos.X);
					((vb6::IIf(SignoEO == 0, 1, SignoEO)) > 0) ?
							(X
									<= (Npclist[NpcIndex].Pos.X
											+ SignoEO * RANGO_VISION_X)) :
							(X
									>= (Npclist[NpcIndex].Pos.X
											+ SignoEO * RANGO_VISION_X));
					X = X + (vb6::IIf(SignoEO == 0, 1, SignoEO))) {
				if (X >= MinXBorder && X <= MaxXBorder && Y >= MinYBorder
						&& Y <= MaxYBorder) {
					NI = MapData[Npclist[NpcIndex].Pos.Map][X][Y].NpcIndex;
					if (NI > 0) {
						if (Npclist[NpcIndex].TargetNPC == NI) {
							bNoEsta = true;
							if (Npclist[NpcIndex].Numero == ELEMENTALFUEGO) {
								NpcLanzaUnSpellSobreNpc(NpcIndex, NI);
								if (Npclist[NI].NPCtype == eNPCType_DRAGON) {
									Npclist[NI].CanAttack = 1;
									NpcLanzaUnSpellSobreNpc(NI, NpcIndex);
								}
							} else {
								/* 'aca verificamosss la distancia de ataque */
								if (Distancia(Npclist[NpcIndex].Pos,
										Npclist[NI].Pos) <= 1) {
									NpcAtacaNpc(NpcIndex, NI);
								}
							}
							return;
						}
					}
				}
			}
		}
	} else {
		for (Y = (Npclist[NpcIndex].Pos.Y - RANGO_VISION_Y);
				Y <= (Npclist[NpcIndex].Pos.Y + RANGO_VISION_Y); Y++) {
			for (X = (Npclist[NpcIndex].Pos.X - RANGO_VISION_Y);
					X <= (Npclist[NpcIndex].Pos.X + RANGO_VISION_Y); X++) {
				if (X >= MinXBorder && X <= MaxXBorder && Y >= MinYBorder
						&& Y <= MaxYBorder) {
					NI = MapData[Npclist[NpcIndex].Pos.Map][X][Y].NpcIndex;
					if (NI > 0) {
						if (Npclist[NpcIndex].TargetNPC == NI) {
							bNoEsta = true;
							if (Npclist[NpcIndex].Numero == ELEMENTALFUEGO) {
								NpcLanzaUnSpellSobreNpc(NpcIndex, NI);
								if (Npclist[NI].NPCtype == eNPCType_DRAGON) {
									Npclist[NI].CanAttack = 1;
									NpcLanzaUnSpellSobreNpc(NI, NpcIndex);
								}
							} else {
								/* 'aca verificamosss la distancia de ataque */
								if (Distancia(Npclist[NpcIndex].Pos,
										Npclist[NI].Pos) <= 1) {
									NpcAtacaNpc(NpcIndex, NI);
								}
							}
							if (Npclist[NpcIndex].flags.Inmovilizado == 1) {
								return;
							}
							if (Npclist[NpcIndex].TargetNPC == 0) {
								return;
							}
							tHeading =
									FindDirection(Npclist[NpcIndex].Pos,
											Npclist[MapData[Npclist[NpcIndex].Pos.Map][X][Y].NpcIndex].Pos);
							MoveNPCChar(NpcIndex, tHeading);
							return;
						}
					}
				}
			}
		}
	}

	if (!bNoEsta) {
		if (Npclist[NpcIndex].MaestroUser > 0) {
			FollowAmo(NpcIndex);
		} else {
			Npclist[NpcIndex].Movement = Npclist[NpcIndex].flags.OldMovement;
			Npclist[NpcIndex].Hostile = Npclist[NpcIndex].flags.OldHostil;
		}
	}
}

void AiNpcObjeto(int NpcIndex) {
	/* '*************************************************** */
	/* 'Autor: ZaMa */
	/* 'Last Modification: 14/09/2009 (ZaMa) */
	/* '14/09/2009: ZaMa - Now npcs don't follow protected users. */
	/* '*************************************************** */
	int UserIndex;
	int i;
	bool UserProtected;

	for (i = (1); i <= (ConnGroups[Npclist[NpcIndex].Pos.Map].CountEntrys);
			i++) {
		UserIndex = ConnGroups[Npclist[NpcIndex].Pos.Map].UserEntrys[i];

		/* 'Is it in it's range of vision?? */
		if (vb6::Abs(UserList[UserIndex].Pos.X - Npclist[NpcIndex].Pos.X)
				<= RANGO_VISION_X) {
			if (vb6::Abs(UserList[UserIndex].Pos.Y - Npclist[NpcIndex].Pos.Y)
					<= RANGO_VISION_Y) {

				UserProtected = !IntervaloPermiteSerAtacado(UserIndex)
						&& UserList[UserIndex].flags.NoPuedeSerAtacado;

				if (UserList[UserIndex].flags.Muerto == 0
						&& UserList[UserIndex].flags.invisible == 0
						&& UserList[UserIndex].flags.Oculto == 0
						&& UserList[UserIndex].flags.AdminPerseguible
						&& !UserProtected) {

					/* ' No quiero que ataque siempre al primero */
					if (RandomNumber(1, 3) < 3) {
						if (Npclist[NpcIndex].flags.LanzaSpells > 0) {
							NpcLanzaUnSpell(NpcIndex, UserIndex);
						}

						return;
					}
				}
			}
		}

	}

}

void NPCAI(int NpcIndex) {
	/* '************************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modify by: ZaMa */
	/* 'Last Modify Date: 15/11/2009 */
	/* '08/16/2008: MarKoxX - Now pets that do melï¿½ attacks have to be near the enemy to attack. */
	/* '15/11/2009: ZaMa - Implementacion de npc objetos ai. */
	/* '************************************************************** */

	/* '<<<<<<<<<<< Ataques >>>>>>>>>>>>>>>> */
	if (Npclist[NpcIndex].MaestroUser == 0) {
		/* 'Busca a alguien para atacar */
		/* 'ï¿½Es un guardia? */
		if (Npclist[NpcIndex].NPCtype == eNPCType_GuardiaReal) {
			GuardiasAI(NpcIndex, false);
		} else if (Npclist[NpcIndex].NPCtype == eNPCType_Guardiascaos) {
			GuardiasAI(NpcIndex, true);
		} else if (Npclist[NpcIndex].Hostile
				&& Npclist[NpcIndex].Stats.Alineacion != 0) {
			HostilMalvadoAI(NpcIndex);
		} else if (Npclist[NpcIndex].Hostile
				&& Npclist[NpcIndex].Stats.Alineacion == 0) {
			HostilBuenoAI(NpcIndex);
		}
	} else {
		/* 'Evitamos que ataque a su amo, a menos */
		/* 'que el amo lo ataque. */
		/* 'Call HostilBuenoAI(NpcIndex) */
	}

	/* '<<<<<<<<<<<Movimiento>>>>>>>>>>>>>>>> */
	switch (Npclist[NpcIndex].Movement) {
	case TipoAI_MueveAlAzar:
		if (Npclist[NpcIndex].flags.Inmovilizado == 1) {
			return;
		}
		if (Npclist[NpcIndex].NPCtype == eNPCType_GuardiaReal) {
			if (RandomNumber(1, 12) == 3) {
				MoveNPCChar(NpcIndex,
						vb6::CByte(
								RandomNumber(eHeading_NORTH, eHeading_WEST)));
			}

			PersigueCriminal(NpcIndex);

		} else if (Npclist[NpcIndex].NPCtype == eNPCType_Guardiascaos) {
			if (RandomNumber(1, 12) == 3) {
				MoveNPCChar(NpcIndex,
						vb6::CByte(
								RandomNumber(eHeading_NORTH, eHeading_WEST)));
			}

			PersigueCiudadano(NpcIndex);

		} else {
			if (RandomNumber(1, 12) == 3) {
				MoveNPCChar(NpcIndex,
						vb6::CByte(
								RandomNumber(eHeading_NORTH, eHeading_WEST)));
			}
		}

		/* 'Va hacia el usuario cercano */
		break;

	case TipoAI_NpcMaloAtacaUsersBuenos:
		IrUsuarioCercano(NpcIndex);

		/* 'Va hacia el usuario que lo ataco(FOLLOW) */
		break;

	case TipoAI_NPCDEFENSA:
		SeguirAgresor(NpcIndex);

		/* 'Persigue criminales */
		break;

	case TipoAI_GuardiasAtacanCriminales:
		PersigueCriminal(NpcIndex);

		break;

	case TipoAI_SigueAmo:
		if (Npclist[NpcIndex].flags.Inmovilizado == 1) {
			return;
		}
		SeguirAmo(NpcIndex);
		if (RandomNumber(1, 12) == 3) {
			MoveNPCChar(NpcIndex,
					vb6::CByte(RandomNumber(eHeading_NORTH, eHeading_WEST)));
		}

		break;

	case TipoAI_NpcAtacaNpc:
		AiNpcAtacaNpc(NpcIndex);

		break;

	case TipoAI_NpcObjeto:
		AiNpcObjeto(NpcIndex);

		break;

	case TipoAI_NpcPathfinding:
		if (Npclist[NpcIndex].flags.Inmovilizado == 1) {
			return;
		}
		if (ReCalculatePath(NpcIndex)) {
			PathFindingAI(NpcIndex);
			/* 'Existe el camino? */
			/* 'Si no existe nos movemos al azar */
			if (Npclist[NpcIndex].PFINFO.NoPath) {
				/* 'Move randomly */
				MoveNPCChar(NpcIndex,
						RandomNumber(eHeading_NORTH, eHeading_WEST));
			}
		} else {
			if (!PathEnd(NpcIndex)) {
				FollowPath(NpcIndex);
			} else {
				Npclist[NpcIndex].PFINFO.PathLenght = 0;
			}
		}
		break;

	default:
		break;
	}
	return;
}

bool UserNear(int NpcIndex) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* 'Returns True if there is an user adjacent to the npc position. */
	/* '*************************************************** */

	if (Npclist[NpcIndex].PFINFO.TargetUser < 1)
		return false;

	retval = !(vb6::CInt(Distance(Npclist[NpcIndex].Pos.X, Npclist[NpcIndex].Pos.Y,
			UserList[Npclist[NpcIndex].PFINFO.TargetUser].Pos.X,
			UserList[Npclist[NpcIndex].PFINFO.TargetUser].Pos.Y)) > 1);
	return retval;
}

bool ReCalculatePath(int NpcIndex) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* 'Returns true if we have to seek a new path */
	/* '*************************************************** */

	if (Npclist[NpcIndex].PFINFO.PathLenght == 0) {
		retval = true;
	} else if (UserNear(NpcIndex) && PathEnd(NpcIndex)) {
		retval = true;
	}
	return retval;
}

bool PathEnd(int NpcIndex) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Gulfas Morgolock */
	/* 'Last Modification: - */
	/* 'Returns if the npc has arrived to the end of its path */
	/* '*************************************************** */
	retval = Npclist[NpcIndex].PFINFO.CurPos
			== Npclist[NpcIndex].PFINFO.PathLenght;
	return retval;
}

bool FollowPath(int NpcIndex) {
	bool retval = true;
	/* '*************************************************** */
	/* 'Author: Gulfas Morgolock */
	/* 'Last Modification: - */
	/* 'Moves the npc. */
	/* '*************************************************** */
	struct WorldPos tmpPos;
	int tHeading;

	tmpPos.Map = Npclist[NpcIndex].Pos.Map;
	/* ' invertï¿½ las coordenadas */
	tmpPos.X = Npclist[NpcIndex].PFINFO.Path[Npclist[NpcIndex].PFINFO.CurPos].X;
	tmpPos.Y = Npclist[NpcIndex].PFINFO.Path[Npclist[NpcIndex].PFINFO.CurPos].Y;

	/* 'Debug.Print "(" & tmpPos.X & "," & tmpPos.Y & ")" */

	tHeading = FindDirection(Npclist[NpcIndex].Pos, tmpPos);

	MoveNPCChar(NpcIndex, tHeading);

	Npclist[NpcIndex].PFINFO.CurPos = Npclist[NpcIndex].PFINFO.CurPos + 1;
	return retval;
}

bool PathFindingAI(int NpcIndex) {
	bool retval = true;
	/* '*************************************************** */
	/* 'Author: Gulfas Morgolock */
	/* 'Last Modification: - */
	/* 'This function seeks the shortest path from the Npc */
	/* 'to the user's location. */
	/* '*************************************************** */
	int Y;
	int X;

	/* 'Makes a loop that looks at */
	for (Y = (Npclist[NpcIndex].Pos.Y - 10);
			Y <= (Npclist[NpcIndex].Pos.Y + 10); Y++) {
		/* '5 tiles in every direction */
		for (X = (Npclist[NpcIndex].Pos.X - 10);
				X <= (Npclist[NpcIndex].Pos.X + 10); X++) {

			/* 'Make sure tile is legal */
			if (X > MinXBorder && X < MaxXBorder && Y > MinYBorder
					&& Y < MaxYBorder) {

				/* 'look for a user */
				if (MapData[Npclist[NpcIndex].Pos.Map][X][Y].UserIndex > 0) {
					/* 'Move towards user */
					int tmpUserIndex;
					tmpUserIndex =
							MapData[Npclist[NpcIndex].Pos.Map][X][Y].UserIndex;
					if (UserList[tmpUserIndex].flags.Muerto == 0
							&& UserList[tmpUserIndex].flags.invisible == 0
							&& UserList[tmpUserIndex].flags.Oculto == 0
							&& UserList[tmpUserIndex].flags.AdminPerseguible) {

						Npclist[NpcIndex].PFINFO.Target.X =
								UserList[tmpUserIndex].Pos.X;
						Npclist[NpcIndex].PFINFO.Target.Y =
								UserList[tmpUserIndex].Pos.Y;

						Npclist[NpcIndex].PFINFO.TargetUser = tmpUserIndex;
						SeekPath(NpcIndex);
						return retval;
					}
				}
			}
		}
	}
	return retval;
}

void NpcLanzaUnSpell(int NpcIndex, int UserIndex) {
	/* '************************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modify by: - */
	/* 'Last Modify Date: - */
	/* '************************************************************** */
	if (UserList[UserIndex].flags.invisible == 1
			|| UserList[UserIndex].flags.Oculto == 1) {
		return;
	}

	int k;
	k = RandomNumber(1, Npclist[NpcIndex].flags.LanzaSpells);
	NpcLanzaSpellSobreUser(NpcIndex, UserIndex, Npclist[NpcIndex].Spells[k]);
}

void NpcLanzaUnSpellSobreNpc(int NpcIndex, int TargetNPC) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int k;
	k = RandomNumber(1, Npclist[NpcIndex].flags.LanzaSpells);
	NpcLanzaSpellSobreNpc(NpcIndex, TargetNPC, Npclist[NpcIndex].Spells[k]);
}
