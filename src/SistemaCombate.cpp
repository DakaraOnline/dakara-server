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

#include "SistemaCombate.h"

const int MAXDISTANCIAARCO = 18;
const int MAXDISTANCIAMAGIA = 18;

int MinimoInt(int a, int b) {
	int retval;
	if (a > b) {
		retval = b;
	} else {
		retval = a;
	}
	return retval;
}

int MaximoInt(int a, int b) {
	int retval;
	if (a > b) {
		retval = a;
	} else {
		retval = b;
	}
	return retval;
}

int PoderEvasionEscudo(int UserIndex) {
	int retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	retval = (UserList[UserIndex].Stats.UserSkills[eSkill_Defensa]
			* ModClase[UserList[UserIndex].clase].Escudo) / 2;
	return retval;
}

int PoderEvasion(int UserIndex) {
	int retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */
	int lTemp;
	lTemp = (UserList[UserIndex].Stats.UserSkills[eSkill_Tacticas]
			+ UserList[UserIndex].Stats.UserSkills[eSkill_Tacticas] / 33
					* UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad])
			* ModClase[UserList[UserIndex].clase].Evasion;

	retval = (lTemp + (2.5 * MaximoInt(UserList[UserIndex].Stats.ELV - 12, 0)));
	return retval;
}

int PoderAtaqueArma(int UserIndex) {
	int retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int PoderAtaqueTemp;

	if (UserList[UserIndex].Stats.UserSkills[eSkill_Armas] < 31) {
		PoderAtaqueTemp = UserList[UserIndex].Stats.UserSkills[eSkill_Armas]
				* ModClase[UserList[UserIndex].clase].AtaqueArmas;
	} else if (UserList[UserIndex].Stats.UserSkills[eSkill_Armas] < 61) {
		PoderAtaqueTemp = (UserList[UserIndex].Stats.UserSkills[eSkill_Armas]
				+ UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad])
				* ModClase[UserList[UserIndex].clase].AtaqueArmas;
	} else if (UserList[UserIndex].Stats.UserSkills[eSkill_Armas] < 91) {
		PoderAtaqueTemp = (UserList[UserIndex].Stats.UserSkills[eSkill_Armas]
				+ 2 * UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad])
				* ModClase[UserList[UserIndex].clase].AtaqueArmas;
	} else {
		PoderAtaqueTemp = (UserList[UserIndex].Stats.UserSkills[eSkill_Armas]
				+ 3 * UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad])
				* ModClase[UserList[UserIndex].clase].AtaqueArmas;
	}

	retval = (PoderAtaqueTemp + (2.5 * MaximoInt(UserList[UserIndex].Stats.ELV - 12, 0)));
	return retval;
}

int PoderAtaqueProyectil(int UserIndex) {
	int retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int PoderAtaqueTemp;
	int SkillProyectiles;

	SkillProyectiles = UserList[UserIndex].Stats.UserSkills[eSkill_Proyectiles];

	if (SkillProyectiles < 31) {
		PoderAtaqueTemp = SkillProyectiles * ModClase[UserList[UserIndex].clase].AtaqueProyectiles;
	} else if (SkillProyectiles < 61) {
		PoderAtaqueTemp = (SkillProyectiles + UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad])
				* ModClase[UserList[UserIndex].clase].AtaqueProyectiles;
	} else if (SkillProyectiles < 91) {
		PoderAtaqueTemp =
				(SkillProyectiles + 2 * UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad])
						* ModClase[UserList[UserIndex].clase].AtaqueProyectiles;
	} else {
		PoderAtaqueTemp =
				(SkillProyectiles + 3 * UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad])
						* ModClase[UserList[UserIndex].clase].AtaqueProyectiles;
	}

	retval = (PoderAtaqueTemp + (2.5 * MaximoInt(UserList[UserIndex].Stats.ELV - 12, 0)));
	return retval;
}

int PoderAtaqueWrestling(int UserIndex) {
	int retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int PoderAtaqueTemp;
	int WrestlingSkill;

	WrestlingSkill = UserList[UserIndex].Stats.UserSkills[eSkill_Wrestling];

	if (WrestlingSkill < 31) {
		PoderAtaqueTemp = WrestlingSkill * ModClase[UserList[UserIndex].clase].AtaqueWrestling;
	} else if (WrestlingSkill < 61) {
		PoderAtaqueTemp = (WrestlingSkill + UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad])
				* ModClase[UserList[UserIndex].clase].AtaqueWrestling;
	} else if (WrestlingSkill < 91) {
		PoderAtaqueTemp = (WrestlingSkill + 2 * UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad])
				* ModClase[UserList[UserIndex].clase].AtaqueWrestling;
	} else {
		PoderAtaqueTemp = (WrestlingSkill + 3 * UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad])
				* ModClase[UserList[UserIndex].clase].AtaqueWrestling;
	}

	retval = (PoderAtaqueTemp + (2.5 * MaximoInt(UserList[UserIndex].Stats.ELV - 12, 0)));
	return retval;
}

bool UserImpactoNpc(int UserIndex, int NpcIndex) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int PoderAtaque;
	int Arma;
	eSkill Skill;
	int ProbExito;

	Arma = UserList[UserIndex].Invent.WeaponEqpObjIndex;

	/* 'Usando un arma */
	if (Arma > 0) {
		if (ObjData[Arma].proyectil == 1) {
			PoderAtaque = PoderAtaqueProyectil(UserIndex);
			Skill = eSkill_Proyectiles;
		} else {
			PoderAtaque = PoderAtaqueArma(UserIndex);
			Skill = eSkill_Armas;
		}
		/* 'Peleando con punos */
	} else {
		PoderAtaque = PoderAtaqueWrestling(UserIndex);
		Skill = eSkill_Wrestling;
	}

	/* ' Chances are rounded */
	ProbExito = MaximoInt(10, MinimoInt(90, 50 + ((PoderAtaque - Npclist[NpcIndex].PoderEvasion) * 0.4)));

	retval = (RandomNumber(1, 100) <= ProbExito);

	if (retval) {
		SubirSkill(UserIndex, Skill, true);
	} else {
		SubirSkill(UserIndex, Skill, false);
	}
	return retval;
}

bool NpcImpacto(int NpcIndex, int UserIndex) {
	bool retval;
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 03/15/2006 */
	/* 'Revisa si un NPC logra impactar a un user o no */
	/* '03/15/2006 Maraxus - Evité una división por cero que eliminaba NPCs */
	/* '************************************************* */
	bool Rechazo;
	int ProbRechazo;
	int ProbExito;
	int UserEvasion;
	int NpcPoderAtaque;
	int PoderEvasioEscudo;
	int SkillTacticas;
	int SkillDefensa;

	UserEvasion = PoderEvasion(UserIndex);
	NpcPoderAtaque = Npclist[NpcIndex].PoderAtaque;
	PoderEvasioEscudo = PoderEvasionEscudo(UserIndex);

	SkillTacticas = UserList[UserIndex].Stats.UserSkills[eSkill_Tacticas];
	SkillDefensa = UserList[UserIndex].Stats.UserSkills[eSkill_Defensa];

	/* 'Esta usando un escudo ??? */
	if (UserList[UserIndex].Invent.EscudoEqpObjIndex > 0) {
		UserEvasion = UserEvasion + PoderEvasioEscudo;
	}

	/* ' Chances are rounded */
	ProbExito = MaximoInt(10, MinimoInt(90, 50 + ((NpcPoderAtaque - UserEvasion) * 0.4)));

	retval = (RandomNumber(1, 100) <= ProbExito);

	/* ' el usuario esta usando un escudo ??? */
	if (UserList[UserIndex].Invent.EscudoEqpObjIndex > 0) {
		if (!retval) {
			/* 'Evitamos división por cero */
			if (SkillDefensa + SkillTacticas > 0) {
				/* ' Chances are rounded */
				ProbRechazo = MaximoInt(10,
						MinimoInt(90, 100 * SkillDefensa / (SkillDefensa + SkillTacticas)));
			} else {
				/* 'Si no tiene skills le dejamos el 10% mínimo */
				ProbRechazo = 10;
			}

			Rechazo = (RandomNumber(1, 100) <= ProbRechazo);

			if (Rechazo) {
				/* 'Se rechazo el ataque con el escudo */
				SendData(SendTarget_ToPCArea, UserIndex,
						dakara::protocol::server::BuildPlayWave(SND_ESCUDO, UserList[UserIndex].Pos.X,
								UserList[UserIndex].Pos.Y));
				/* 'Call WriteBlockedWithShieldUser(UserIndex) */
				WriteMultiMessage(UserIndex, eMessages_BlockedWithShieldUser);
				SubirSkill(UserIndex, eSkill_Defensa, true);
			} else {
				SubirSkill(UserIndex, eSkill_Defensa, false);
			}
		}
	}
	return retval;
}

int CalcularDano(int UserIndex, int NpcIndex) {
	int retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 01/04/2010 (ZaMa) */
	/* '01/04/2010: ZaMa - Modifico el dano de wrestling. */
	/* '01/04/2010: ZaMa - Agrego bonificadores de wrestling para los guantes. */
	/* '*************************************************** */
	int DanoArma;
	int DanoUsuario;
	struct ObjData Arma;
	float ModifClase;
	struct ObjData proyectil;
	int DanoMaxArma;
	int DanoMinArma;
	int ObjIndex;

	/* ''sacar esto si no queremos q la matadracos mate el Dragon si o si */
	bool matoDragon;
	matoDragon = false;

	if (UserList[UserIndex].Invent.WeaponEqpObjIndex > 0) {
		Arma = ObjData[UserList[UserIndex].Invent.WeaponEqpObjIndex];

		/* ' Ataca a un npc? */
		if (NpcIndex > 0) {
			if (Arma.proyectil == 1) {
				ModifClase = ModClase[UserList[UserIndex].clase].DanoProyectiles;
				DanoArma = RandomNumber(Arma.MinHIT, Arma.MaxHIT);
				DanoMaxArma = Arma.MaxHIT;

				if (Arma.Municion == 1) {
					proyectil = ObjData[UserList[UserIndex].Invent.MunicionEqpObjIndex];
					DanoArma = DanoArma + RandomNumber(proyectil.MinHIT, proyectil.MaxHIT);
					/* ' For some reason this isn't done... */
					/* 'DanoMaxArma = DanoMaxArma + proyectil.MaxHIT */
				}
			} else {
				ModifClase = ModClase[UserList[UserIndex].clase].DanoArmas;

				/* ' Usa la mata Dragones? */
				if (UserList[UserIndex].Invent.WeaponEqpObjIndex == EspadaMataDragonesIndex) {
					/* 'Ataca Dragon? */
					if (Npclist[NpcIndex].NPCtype == eNPCType_DRAGON) {
						DanoArma = RandomNumber(Arma.MinHIT, Arma.MaxHIT);
						DanoMaxArma = Arma.MaxHIT;
						/* ''sacar esto si no queremos q la matadracos mate el Dragon si o si */
						matoDragon = true;
						/* ' Sino es Dragon dano es 1 */
					} else {
						DanoArma = 1;
						DanoMaxArma = 1;
					}
				} else {
					DanoArma = RandomNumber(Arma.MinHIT, Arma.MaxHIT);
					DanoMaxArma = Arma.MaxHIT;
				}
			}
			/* ' Ataca usuario */
		} else {
			if (Arma.proyectil == 1) {
				ModifClase = ModClase[UserList[UserIndex].clase].DanoProyectiles;
				DanoArma = RandomNumber(Arma.MinHIT, Arma.MaxHIT);
				DanoMaxArma = Arma.MaxHIT;

				if (Arma.Municion == 1) {
					proyectil = ObjData[UserList[UserIndex].Invent.MunicionEqpObjIndex];
					DanoArma = DanoArma + RandomNumber(proyectil.MinHIT, proyectil.MaxHIT);
					/* ' For some reason this isn't done... */
					/* 'DanoMaxArma = DanoMaxArma + proyectil.MaxHIT */
				}
			} else {
				ModifClase = ModClase[UserList[UserIndex].clase].DanoArmas;

				if (UserList[UserIndex].Invent.WeaponEqpObjIndex == EspadaMataDragonesIndex) {
					ModifClase = ModClase[UserList[UserIndex].clase].DanoArmas;
					/* ' Si usa la espada mataDragones dano es 1 */
					DanoArma = 1;
					DanoMaxArma = 1;
				} else {
					DanoArma = RandomNumber(Arma.MinHIT, Arma.MaxHIT);
					DanoMaxArma = Arma.MaxHIT;
				}
			}
		}
	} else {
		ModifClase = ModClase[UserList[UserIndex].clase].DanoWrestling;

		/* ' Dano sin guantes */
		DanoMinArma = 4;
		DanoMaxArma = 9;

		/* ' Plus de guantes (en slot de anillo) */
		ObjIndex = UserList[UserIndex].Invent.AnilloEqpObjIndex;
		if (ObjIndex > 0) {
			if (ObjData[ObjIndex].Guante == 1) {
				DanoMinArma = DanoMinArma + ObjData[ObjIndex].MinHIT;
				DanoMaxArma = DanoMaxArma + ObjData[ObjIndex].MaxHIT;
			}
		}

		DanoArma = RandomNumber(DanoMinArma, DanoMaxArma);

	}

	DanoUsuario = RandomNumber(UserList[UserIndex].Stats.MinHIT, UserList[UserIndex].Stats.MaxHIT);

	/* ''sacar esto si no queremos q la matadracos mate el Dragon si o si */
	if (matoDragon) {
		retval = Npclist[NpcIndex].Stats.MinHp + Npclist[NpcIndex].Stats.def;
	} else {
		retval = (3.0 * DanoArma
				+ ((DanoMaxArma / 5.0)
						* MaximoInt(0, UserList[UserIndex].Stats.UserAtributos[eAtributos_Fuerza] - 15))
				+ DanoUsuario) * ModifClase;
	}
	return retval;
}

void UserDanoNpc(int UserIndex, int NpcIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 07/04/2010 (Pato) */
	/* '25/01/2010: ZaMa - Agrego poder acuchillar npcs. */
	/* '07/04/2010: ZaMa - Los asesinos apunalan acorde al dano base sin descontar la defensa del npc. */
	/* '07/04/2010: Pato - Si se mata al dragón en party se loguean los miembros de la misma. */
	/* '11/07/2010: ZaMa - Ahora la defensa es solo ignorada para asesinos. */
	/* '*************************************************** */

	int dano;
	int DanoBase;
	int PI;
	std::string Text;
	int i;

	int BoatIndex;

	DanoBase = CalcularDano(UserIndex, NpcIndex);

	/* 'esta navegando? si es asi le sumamos el dano del barco */
	if (UserList[UserIndex].flags.Navegando == 1) {

		BoatIndex = UserList[UserIndex].Invent.BarcoObjIndex;
		if (BoatIndex > 0) {
			DanoBase = DanoBase + RandomNumber(ObjData[BoatIndex].MinHIT, ObjData[BoatIndex].MaxHIT);
		}
	}

	dano = DanoBase - Npclist[NpcIndex].Stats.def;

	if (dano < 0) {
		dano = 0;
	}

	WriteMultiMessage(UserIndex, eMessages_UserHitNPC, dano);
	CalcularDarExp(UserIndex, NpcIndex, dano);
	Npclist[NpcIndex].Stats.MinHp = Npclist[NpcIndex].Stats.MinHp - dano;

	if (Npclist[NpcIndex].Stats.MinHp > 0) {
		/* 'Trata de apunalar por la espalda al enemigo */
		if (PuedeApunalar(UserIndex)) {

			/* ' La defensa se ignora solo en asesinos */
			if (UserList[UserIndex].clase != eClass_Assasin) {
				DanoBase = dano;
			}

			DoApunalar(UserIndex, NpcIndex, 0, DanoBase);

		}

		/* 'trata de dar golpe crítico */
		DoGolpeCritico(UserIndex, NpcIndex, 0, dano);

		if (PuedeAcuchillar(UserIndex)) {
			DoAcuchillar(UserIndex, NpcIndex, 0, dano);
		}
	}

	if (Npclist[NpcIndex].Stats.MinHp <= 0) {
		/* ' Si era un Dragon perdemos la espada mataDragones */
		if (Npclist[NpcIndex].NPCtype == eNPCType_DRAGON) {
			/* 'Si tiene equipada la matadracos se la sacamos */
			if (UserList[UserIndex].Invent.WeaponEqpObjIndex == EspadaMataDragonesIndex) {
				QuitarObjetos(EspadaMataDragonesIndex, 1, UserIndex);
			}
			if (Npclist[NpcIndex].Stats.MaxHp > 100000) {
				Text = UserList[UserIndex].Name + " mató un dragón";
				PI = UserList[UserIndex].PartyIndex;

				if (PI > 0) {
					std::vector<int> MembersOnline;
					Parties[PI]->ObtenerMiembrosOnline(MembersOnline);
					Text = Text + " estando en party ";

					for (int m : MembersOnline) {
						if (m > 0) {
							Text = Text + UserList[m].Name + ", ";
						}
					}

					Text = vb6::Left(Text, vb6::Len(Text) - 2) + ")";
				}

				LogDesarrollo(Text + ".");
			}
		}

		/* ' Para que las mascotas no sigan intentando luchar y */
		/* ' comiencen a seguir al amo */
		for (i = (1); i <= (MAXMASCOTAS); i++) {
			if (UserList[UserIndex].MascotasIndex[i] > 0) {
				if (Npclist[UserList[UserIndex].MascotasIndex[i]].TargetNPC == NpcIndex) {
					Npclist[UserList[UserIndex].MascotasIndex[i]].TargetNPC = 0;
					Npclist[UserList[UserIndex].MascotasIndex[i]].Movement = TipoAI_SigueAmo;
				}
			}
		}

		MuereNpc(NpcIndex, UserIndex);
	}
}

void NpcDano(int NpcIndex, int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 18/09/2010 (ZaMa) */
	/* '18/09/2010: ZaMa - Ahora se considera siempre la defensa del barco y el escudo. */
	/* '*************************************************** */

	int dano;
	int Lugar;
	struct ObjData Obj;

	int BoatDefense = 0;
	int HeadDefense = 0;
	int BodyDefense = 0;

	int BoatIndex;
	int HelmetIndex ;
	int ArmourIndex;
	int ShieldIndex;

	dano = RandomNumber(Npclist[NpcIndex].Stats.MinHIT, Npclist[NpcIndex].Stats.MaxHIT);

	/* ' Navega? */
	if (UserList[UserIndex].flags.Navegando == 1) {
		/* ' En barca suma defensa */
		BoatIndex = UserList[UserIndex].Invent.BarcoObjIndex;
		if (BoatIndex > 0) {
			Obj = ObjData[BoatIndex];
			BoatDefense = RandomNumber(Obj.MinDef, Obj.MaxDef);
		}
	}

	Lugar = RandomNumber(PartesCuerpo_bCabeza, PartesCuerpo_bTorso);

	switch (Lugar) {

	case PartesCuerpo_bCabeza:

		/* 'Si tiene casco absorbe el golpe */
		HelmetIndex = UserList[UserIndex].Invent.CascoEqpObjIndex;
		if (HelmetIndex > 0) {
			Obj = ObjData[HelmetIndex];
			HeadDefense = RandomNumber(Obj.MinDef, Obj.MaxDef);
		}

		break;

	default:

		int MinDef = 0;
		int MaxDef = 0;

		/* 'Si tiene armadura absorbe el golpe */
		ArmourIndex = UserList[UserIndex].Invent.ArmourEqpObjIndex;
		if (ArmourIndex > 0) {
			Obj = ObjData[ArmourIndex];
			MinDef = Obj.MinDef;
			MaxDef = Obj.MaxDef;
		}

		/* ' Si tiene casco absorbe el golpe */
		ShieldIndex = UserList[UserIndex].Invent.EscudoEqpObjIndex;
		if (ShieldIndex > 0) {
			Obj = ObjData[ShieldIndex];
			MinDef = MinDef + Obj.MinDef;
			MaxDef = MaxDef + Obj.MaxDef;
		}

		BodyDefense = RandomNumber(MinDef, MaxDef);

		break;
	}

	/* ' Dano final */
	dano = dano - HeadDefense - BodyDefense - BoatDefense;
	if (dano < 1) {
		dano = 1;
	}

	WriteMultiMessage(UserIndex, eMessages_NPCHitUser, Lugar, dano);

	if (UserTienePrivilegio(UserIndex, PlayerType_User)) {
		UserList[UserIndex].Stats.MinHp = UserList[UserIndex].Stats.MinHp - dano;
	}

	if (UserList[UserIndex].flags.Meditando) {
		if (dano
				> vb6::Fix(
						UserList[UserIndex].Stats.MinHp / 100
								* UserList[UserIndex].Stats.UserAtributos[eAtributos_Inteligencia]
								* UserList[UserIndex].Stats.UserSkills[eSkill_Meditar] / 100 * 12
								/ (RandomNumber(0, 5) + 7))) {
			UserList[UserIndex].flags.Meditando = false;
			WriteMeditateToggle(UserIndex);
			WriteConsoleMsg(UserIndex, "Dejas de meditar.", FontTypeNames_FONTTYPE_INFO);
			UserList[UserIndex].Char.FX = 0;
			UserList[UserIndex].Char.loops = 0;
			SendData(SendTarget_ToPCArea, UserIndex,
					dakara::protocol::server::BuildCreateFX(UserList[UserIndex].Char.CharIndex, 0, 0));
		}
	}

	/* 'Muere el usuario */
	if (UserList[UserIndex].Stats.MinHp <= 0) {
		/* 'Le informamos que ha muerto ;) */
		WriteMultiMessage(UserIndex, eMessages_NPCKillUser);

		/* 'Si lo mato un guardia */
		if (criminal(UserIndex)) {
			if (Npclist[NpcIndex].NPCtype == eNPCType_GuardiaReal) {
				RestarCriminalidad(UserIndex);
			}
		}

		if (Npclist[NpcIndex].MaestroUser > 0) {
			AllFollowAmo(Npclist[NpcIndex].MaestroUser);
		} else {
			/* 'Al matarlo no lo sigue mas */
			if (Npclist[NpcIndex].Stats.Alineacion == 0) {
				Npclist[NpcIndex].Movement = Npclist[NpcIndex].flags.OldMovement;
				Npclist[NpcIndex].Hostile = Npclist[NpcIndex].flags.OldHostil;
				Npclist[NpcIndex].flags.AttackedBy = "";
			}

		}

		UserDie(UserIndex);
	}
}

void RestarCriminalidad(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	bool EraCriminal;
	EraCriminal = criminal(UserIndex);

	if (UserList[UserIndex].Reputacion.BandidoRep > 0) {
		UserList[UserIndex].Reputacion.BandidoRep = UserList[UserIndex].Reputacion.BandidoRep - vlASALTO;
		if (UserList[UserIndex].Reputacion.BandidoRep < 0) {
			UserList[UserIndex].Reputacion.BandidoRep = 0;
		}
	} else if (UserList[UserIndex].Reputacion.LadronesRep > 0) {
		UserList[UserIndex].Reputacion.LadronesRep = UserList[UserIndex].Reputacion.LadronesRep
				- (vlCAZADOR * 10);
		if (UserList[UserIndex].Reputacion.LadronesRep < 0) {
			UserList[UserIndex].Reputacion.LadronesRep = 0;
		}
	}

	if (EraCriminal && !criminal(UserIndex)) {

		if (esCaos(UserIndex)) {
			ExpulsarFaccionCaos(UserIndex);
		}

		RefreshCharStatus(UserIndex);
	}

}

void CheckPets(int NpcIndex, int UserIndex, bool CheckElementales) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 15/04/2010 */
	/* '15/04/2010: ZaMa - Las mascotas no se apropian de npcs. */
	/* '*************************************************** */

	int j;

	/* ' Si no tengo mascotas, para que cheaquear lo demas? */
	if (UserList[UserIndex].NroMascotas == 0) {
		return;
	}

	if (!PuedeAtacarNPC(UserIndex, NpcIndex, false, true)) {
		return;
	}

	for (j = (1); j <= (MAXMASCOTAS); j++) {
		if (UserList[UserIndex].MascotasIndex[j] > 0) {
			if (UserList[UserIndex].MascotasIndex[j] != NpcIndex) {
				if (CheckElementales
						|| (Npclist[UserList[UserIndex].MascotasIndex[j]].Numero != ELEMENTALFUEGO
								&& Npclist[UserList[UserIndex].MascotasIndex[j]].Numero != ELEMENTALTIERRA)) {

					if (Npclist[UserList[UserIndex].MascotasIndex[j]].TargetNPC == 0) {
						Npclist[UserList[UserIndex].MascotasIndex[j]].TargetNPC = NpcIndex;
					}
					Npclist[UserList[UserIndex].MascotasIndex[j]].Movement = TipoAI_NpcAtacaNpc;
				}
			}
		}
	}
}

void AllFollowAmo(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int j;

	for (j = (1); j <= (MAXMASCOTAS); j++) {
		if (UserList[UserIndex].MascotasIndex[j] > 0) {
			FollowAmo(UserList[UserIndex].MascotasIndex[j]);
		}
	}
}

bool NpcAtacaUser(int NpcIndex, int UserIndex) {
	bool retval = false;
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: - */
	/* ' */
	/* '************************************************* */

	if (UserList[UserIndex].flags.AdminInvisible == 1) {
		return retval;
	}

	if (!UserTienePrivilegio(UserIndex, PlayerType_User) && !UserList[UserIndex].flags.AdminPerseguible) {
		return retval;
	}

	/* ' El npc puede atacar ??? */
	if (Npclist[NpcIndex].CanAttack == 1) {
		retval = true;
		CheckPets(NpcIndex, UserIndex, false);

		if (Npclist[NpcIndex].Target == 0) {
			Npclist[NpcIndex].Target = UserIndex;
		}

		if (UserList[UserIndex].flags.AtacadoPorNpc == 0 && UserList[UserIndex].flags.AtacadoPorUser == 0) {
			UserList[UserIndex].flags.AtacadoPorNpc = NpcIndex;
		}
	} else {
		retval = false;
		return retval;
	}

	Npclist[NpcIndex].CanAttack = 0;

	if (Npclist[NpcIndex].flags.Snd1 > 0) {
		SendData(SendTarget_ToNPCArea, NpcIndex,
				dakara::protocol::server::BuildPlayWave(Npclist[NpcIndex].flags.Snd1, Npclist[NpcIndex].Pos.X,
						Npclist[NpcIndex].Pos.Y));
	}

	if (NpcImpacto(NpcIndex, UserIndex)) {
		SendData(SendTarget_ToPCArea, UserIndex,
				dakara::protocol::server::BuildPlayWave(SND_IMPACTO, UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y));

		if (UserList[UserIndex].flags.Meditando == false) {
			if (UserList[UserIndex].flags.Navegando == 0) {
				SendData(SendTarget_ToPCArea, UserIndex,
						dakara::protocol::server::BuildCreateFX(UserList[UserIndex].Char.CharIndex, FXSANGRE, 0));
			}
		}

		NpcDano(NpcIndex, UserIndex);
		WriteUpdateHP(UserIndex);

		/* '¿Puede envenenar? */
		if (Npclist[NpcIndex].Veneno == 1) {
			NpcEnvenenarUser(UserIndex);
		}

		SubirSkill(UserIndex, eSkill_Tacticas, false);
	} else {
		WriteMultiMessage(UserIndex, eMessages_NPCSwing);
		SubirSkill(UserIndex, eSkill_Tacticas, true);
	}

	/* 'Controla el nivel del usuario */
	CheckUserLevel(UserIndex);
	return retval;
}

bool NpcImpactoNpc(int Atacante, int Victima) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int PoderAtt;
	int PoderEva;
	int ProbExito;

	PoderAtt = Npclist[Atacante].PoderAtaque;
	PoderEva = Npclist[Victima].PoderEvasion;

	/* ' Chances are rounded */
	ProbExito = MaximoInt(10, MinimoInt(90, 50 + (PoderAtt - PoderEva) * 0.4));
	retval = (RandomNumber(1, 100) <= ProbExito);
	return retval;
}

void NpcDanoNpc(int Atacante, int Victima) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int dano;
	int MasterIndex;

	dano = RandomNumber(Npclist[Atacante].Stats.MinHIT, Npclist[Atacante].Stats.MaxHIT);
	Npclist[Victima].Stats.MinHp = Npclist[Victima].Stats.MinHp - dano;

	if (Npclist[Victima].Stats.MinHp < 1) {
		Npclist[Atacante].Movement = Npclist[Atacante].flags.OldMovement;

		if (vb6::LenB(Npclist[Atacante].flags.AttackedBy) != 0) {
			Npclist[Atacante].Hostile = Npclist[Atacante].flags.OldHostil;
		}

		MasterIndex = Npclist[Atacante].MaestroUser;
		if (MasterIndex > 0) {
			FollowAmo(Atacante);
		}

		MuereNpc(Victima, MasterIndex);
	}
}

void NpcAtacaNpc(int Atacante, int Victima, bool cambiarMOvimiento) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 01/03/2009 */
	/* '01/03/2009: ZaMa - Las mascotas no pueden atacar al rey si quedan pretorianos vivos. */
	/* '23/05/2010: ZaMa - Ahora los elementales renuevan el tiempo de pertencia del npc que atacan si pertenece a su amo. */
	/* '************************************************* */

	int MasterIndex;

	/* 'Es el Rey Preatoriano? */
	if (Npclist[Victima].NPCtype == eNPCType_Pretoriano) {
		/* FIXME: PRETORIANOS */
#if 0
		if (!ClanPretoriano[Npclist[Victima].ClanIndex]->CanAtackMember(Victima)) {
			WriteConsoleMsg(Npclist[Atacante].MaestroUser,
					"Debes matar al resto del ejército antes de atacar al rey!",
					FontTypeNames_FONTTYPE_FIGHT);
			Npclist[Atacante].TargetNPC = 0;
			return;
		}
#endif
	}

	/* ' El npc puede atacar ??? */
	if (Npclist[Atacante].CanAttack == 1) {
		Npclist[Atacante].CanAttack = 0;
		if (cambiarMOvimiento) {
			Npclist[Victima].TargetNPC = Atacante;
			Npclist[Victima].Movement = TipoAI_NpcAtacaNpc;
		}
	} else {
		return;
	}

	if (Npclist[Atacante].flags.Snd1 > 0) {
		SendData(SendTarget_ToNPCArea, Atacante,
				dakara::protocol::server::BuildPlayWave(Npclist[Atacante].flags.Snd1, Npclist[Atacante].Pos.X,
						Npclist[Atacante].Pos.Y));
	}

	MasterIndex = Npclist[Atacante].MaestroUser;

	/* ' Tiene maestro? */
	if (MasterIndex > 0) {
		/* ' Su maestro es dueno del npc al que ataca? */
		if (Npclist[Victima].Owner == MasterIndex) {
			/* ' Renuevo el timer de pertenencia */
			IntervaloPerdioNpc(MasterIndex, true);
		}
	}

	if (NpcImpactoNpc(Atacante, Victima)) {
		if (Npclist[Victima].flags.Snd2 > 0) {
			SendData(SendTarget_ToNPCArea, Victima,
					dakara::protocol::server::BuildPlayWave(Npclist[Victima].flags.Snd2, Npclist[Victima].Pos.X,
							Npclist[Victima].Pos.Y));
		} else {
			SendData(SendTarget_ToNPCArea, Victima,
					dakara::protocol::server::BuildPlayWave(SND_IMPACTO2, Npclist[Victima].Pos.X, Npclist[Victima].Pos.Y));
		}

		if (MasterIndex > 0) {
			SendData(SendTarget_ToNPCArea, Atacante,
					dakara::protocol::server::BuildPlayWave(SND_IMPACTO, Npclist[Atacante].Pos.X, Npclist[Atacante].Pos.Y));
		} else {
			SendData(SendTarget_ToNPCArea, Victima,
					dakara::protocol::server::BuildPlayWave(SND_IMPACTO, Npclist[Victima].Pos.X, Npclist[Victima].Pos.Y));
		}

		NpcDanoNpc(Atacante, Victima);
	} else {
		if (MasterIndex > 0) {
			SendData(SendTarget_ToNPCArea, Atacante,
					dakara::protocol::server::BuildPlayWave(SND_SWING, Npclist[Atacante].Pos.X, Npclist[Atacante].Pos.Y));
		} else {
			SendData(SendTarget_ToNPCArea, Victima,
					dakara::protocol::server::BuildPlayWave(SND_SWING, Npclist[Victima].Pos.X, Npclist[Victima].Pos.Y));
		}
	}
}

bool UsuarioAtacaNpc(int UserIndex, int NpcIndex) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 13/02/2011 (Amraphen) */
	/* '12/01/2010: ZaMa - Los druidas pierden la inmunidad de ser atacados por npcs cuando los atacan. */
	/* '14/01/2010: ZaMa - Lo transformo en función, para que no se pierdan municiones al atacar targets inválidos. */
	/* '13/02/2011: Amraphen - Ahora la stamina es quitada cuando efectivamente se ataca al NPC. */
	/* '*************************************************** */

	if (!PuedeAtacarNPC(UserIndex, NpcIndex)) {
		return retval;
	}

	NPCAtacado(NpcIndex, UserIndex);

	if (UserImpactoNpc(UserIndex, NpcIndex)) {
		if (Npclist[NpcIndex].flags.Snd2 > 0) {
			SendData(SendTarget_ToNPCArea, NpcIndex,
					dakara::protocol::server::BuildPlayWave(Npclist[NpcIndex].flags.Snd2, Npclist[NpcIndex].Pos.X,
							Npclist[NpcIndex].Pos.Y));
		} else {
			SendData(SendTarget_ToPCArea, UserIndex,
					dakara::protocol::server::BuildPlayWave(SND_IMPACTO2, Npclist[NpcIndex].Pos.X, Npclist[NpcIndex].Pos.Y));
		}

		UserDanoNpc(UserIndex, NpcIndex);
	} else {
		SendData(SendTarget_ToPCArea, UserIndex,
				dakara::protocol::server::BuildPlayWave(SND_SWING, UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y));
		WriteMultiMessage(UserIndex, eMessages_UserSwing);
	}

	/* 'Quitamos stamina */
	QuitarSta(UserIndex, RandomNumber(1, 10));

	/* ' Reveló su condición de usuario al atacar, los npcs lo van a atacar */
	UserList[UserIndex].flags.Ignorado = false;

	retval = true;

	return retval;
}

void UsuarioAtaca(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 13/02/2011 (Amraphen) */
	/* '13/02/2011: Amraphen - Ahora se quita la stamina en el sub UsuarioAtacaNPC. */
	/* '*************************************************** */

	int index;
	struct WorldPos AttackPos;

	/* 'Check bow's interval */
	if (!IntervaloPermiteUsarArcos(UserIndex, false)) {
		return;
	}

	/* 'Check Spell-Magic interval */
	if (!IntervaloPermiteMagiaGolpe(UserIndex)) {
		/* 'Check Attack interval */
		if (!IntervaloPermiteAtacar(UserIndex)) {
			return;
		}
	}

	/* 'Chequeamos que tenga por lo menos 10 de stamina. */
	if (UserList[UserIndex].Stats.MinSta < 10) {
		if (UserList[UserIndex].Genero == eGenero_Hombre) {
			WriteConsoleMsg(UserIndex, "Estás muy cansado para luchar.", FontTypeNames_FONTTYPE_INFO);
		} else {
			WriteConsoleMsg(UserIndex, "Estás muy cansada para luchar.", FontTypeNames_FONTTYPE_INFO);
		}
		return;
	}

	AttackPos = UserList[UserIndex].Pos;
	HeadtoPos(UserList[UserIndex].Char.heading, AttackPos);

	/* 'Exit if not legal */
	if (AttackPos.X < XMinMapSize || AttackPos.X > XMaxMapSize || AttackPos.Y <= YMinMapSize
			|| AttackPos.Y > YMaxMapSize) {
		SendData(SendTarget_ToPCArea, UserIndex,
				dakara::protocol::server::BuildPlayWave(SND_SWING, UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y));
		return;
	}

	index = MapData[AttackPos.Map][AttackPos.X][AttackPos.Y].UserIndex;

	/* 'Look for user */
	if (index > 0) {
		UsuarioAtacaUsuario(UserIndex, index);
		WriteUpdateUserStats(UserIndex);
		WriteUpdateUserStats(index);
		return;
	}

	index = MapData[AttackPos.Map][AttackPos.X][AttackPos.Y].NpcIndex;

	/* 'Look for NPC */
	if (index > 0) {
		if (Npclist[index].Attackable) {
			if (Npclist[index].MaestroUser > 0 && MapInfo[Npclist[index].Pos.Map].Pk == false) {
				WriteConsoleMsg(UserIndex, "No puedes atacar mascotas en zona segura.",
						FontTypeNames_FONTTYPE_FIGHT);
				return;
			}

			UsuarioAtacaNpc(UserIndex, index);
		} else {
			WriteConsoleMsg(UserIndex, "No puedes atacar a este NPC.", FontTypeNames_FONTTYPE_FIGHT);
		}

		WriteUpdateUserStats(UserIndex);

		return;
	}

	SendData(SendTarget_ToPCArea, UserIndex,
			dakara::protocol::server::BuildPlayWave(SND_SWING, UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y));
	WriteUpdateUserStats(UserIndex);

	if (UserList[UserIndex].Counters.Trabajando) {
		UserList[UserIndex].Counters.Trabajando = UserList[UserIndex].Counters.Trabajando - 1;
	}

	if (UserList[UserIndex].Counters.Ocultando) {
		UserList[UserIndex].Counters.Ocultando = UserList[UserIndex].Counters.Ocultando - 1;
	}
}

bool UsuarioImpacto(int AtacanteIndex, int VictimaIndex) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 21/05/2010 */
	/* '21/05/2010: ZaMa - Evito division por cero. */
	/* '*************************************************** */

	int ProbRechazo;
	bool Rechazo;
	int ProbExito;
	int PoderAtaque;
	int UserPoderEvasion;
	int UserPoderEvasionEscudo;
	int Arma;
	int SkillTacticas;
	int SkillDefensa;
	int ProbEvadir;
	eSkill Skill;

	SkillTacticas = UserList[VictimaIndex].Stats.UserSkills[eSkill_Tacticas];
	SkillDefensa = UserList[VictimaIndex].Stats.UserSkills[eSkill_Defensa];

	Arma = UserList[AtacanteIndex].Invent.WeaponEqpObjIndex;

	/* 'Calculamos el poder de evasion... */
	UserPoderEvasion = PoderEvasion(VictimaIndex);

	if (UserList[VictimaIndex].Invent.EscudoEqpObjIndex > 0) {
		UserPoderEvasionEscudo = PoderEvasionEscudo(VictimaIndex);
		UserPoderEvasion = UserPoderEvasion + UserPoderEvasionEscudo;
	} else {
		UserPoderEvasionEscudo = 0;
	}

	/* 'Esta usando un arma ??? */
	if (UserList[AtacanteIndex].Invent.WeaponEqpObjIndex > 0) {
		if (ObjData[Arma].proyectil == 1) {
			PoderAtaque = PoderAtaqueProyectil(AtacanteIndex);
			Skill = eSkill_Proyectiles;
		} else {
			PoderAtaque = PoderAtaqueArma(AtacanteIndex);
			Skill = eSkill_Armas;
		}
	} else {
		PoderAtaque = PoderAtaqueWrestling(AtacanteIndex);
		Skill = eSkill_Wrestling;
	}

	/* ' Chances are rounded */
	ProbExito = MaximoInt(10, MinimoInt(90, 50 + (PoderAtaque - UserPoderEvasion) * 0.4));

	/* ' Se reduce la evasion un 25% */
	if (UserList[VictimaIndex].flags.Meditando) {
		ProbEvadir = (100 - ProbExito) * 0.75;
		ProbExito = MinimoInt(90, 100 - ProbEvadir);
	}

	retval = (RandomNumber(1, 100) <= ProbExito);

	/* ' el usuario esta usando un escudo ??? */
	if (UserList[VictimaIndex].Invent.EscudoEqpObjIndex > 0) {
		/* 'Fallo ??? */
		if (!retval) {

			int SumaSkills;

			/* ' Para evitar division por 0 */
			SumaSkills = MaximoInt(1, SkillDefensa + SkillTacticas);

			/* ' Chances are rounded */
			ProbRechazo = MaximoInt(10, MinimoInt(90, 100 * SkillDefensa / SumaSkills));
			Rechazo = (RandomNumber(1, 100) <= ProbRechazo);
			if (Rechazo) {
				/* 'Se rechazo el ataque con el escudo */
				SendData(SendTarget_ToPCArea, VictimaIndex,
						dakara::protocol::server::BuildPlayWave(SND_ESCUDO, UserList[VictimaIndex].Pos.X,
								UserList[VictimaIndex].Pos.Y));

				WriteMultiMessage(AtacanteIndex, eMessages_BlockedWithShieldother);
				WriteMultiMessage(VictimaIndex, eMessages_BlockedWithShieldUser);

				SubirSkill(VictimaIndex, eSkill_Defensa, true);
			} else {
				SubirSkill(VictimaIndex, eSkill_Defensa, false);
			}
		}
	}

	if (!retval) {
		SubirSkill(AtacanteIndex, Skill, false);
	}

	FlushBuffer(VictimaIndex);

	return retval;
}

bool UsuarioAtacaUsuario(int AtacanteIndex, int VictimaIndex) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 14/01/2010 (ZaMa) */
	/* '14/01/2010: ZaMa - Lo transformo en función, para que no se pierdan municiones al atacar targets */
	/* '                    inválidos, y evitar un doble chequeo innecesario */
	/* '*************************************************** */

	if (!PuedeAtacar(AtacanteIndex, VictimaIndex)) {
		return retval;
	}

	if (Distancia(UserList[AtacanteIndex].Pos, UserList[VictimaIndex].Pos) > MAXDISTANCIAARCO) {
		WriteConsoleMsg(AtacanteIndex, "Estás muy lejos para disparar.", FontTypeNames_FONTTYPE_FIGHT);
		return retval;
	}

	UsuarioAtacadoPorUsuario(AtacanteIndex, VictimaIndex);

	if (UsuarioImpacto(AtacanteIndex, VictimaIndex)) {
		SendData(SendTarget_ToPCArea, AtacanteIndex,
				dakara::protocol::server::BuildPlayWave(SND_IMPACTO, UserList[AtacanteIndex].Pos.X,
						UserList[AtacanteIndex].Pos.Y));

		if (UserList[VictimaIndex].flags.Navegando == 0) {
			SendData(SendTarget_ToPCArea, VictimaIndex,
					dakara::protocol::server::BuildCreateFX(UserList[VictimaIndex].Char.CharIndex, FXSANGRE, 0));
		}

		/* 'Pablo (ToxicWaste): Guantes de Hurto del Bandido en acción */
		if (UserList[AtacanteIndex].clase == eClass_Bandit) {
			DoDesequipar(AtacanteIndex, VictimaIndex);

			/* 'y ahora, el ladrón puede llegar a paralizar con el golpe. */
		} else if (UserList[AtacanteIndex].clase == eClass_Thief) {
			DoHandInmo(AtacanteIndex, VictimaIndex);
		}

		SubirSkill(VictimaIndex, eSkill_Tacticas, false);
		UserDanoUser(AtacanteIndex, VictimaIndex);
	} else {
		/* ' Invisible admins doesn't make sound to other clients except itself */
		if (UserList[AtacanteIndex].flags.AdminInvisible == 1) {
			EnviarDatosASlot(AtacanteIndex,
					PacketToString(dakara::protocol::server::BuildPlayWave(SND_SWING, UserList[AtacanteIndex].Pos.X,
							UserList[AtacanteIndex].Pos.Y)));
		} else {
			SendData(SendTarget_ToPCArea, AtacanteIndex,
					dakara::protocol::server::BuildPlayWave(SND_SWING, UserList[AtacanteIndex].Pos.X,
							UserList[AtacanteIndex].Pos.Y));
		}

		WriteMultiMessage(AtacanteIndex, eMessages_UserSwing);
		WriteMultiMessage(VictimaIndex, eMessages_UserAttackedSwing, AtacanteIndex);
		SubirSkill(VictimaIndex, eSkill_Tacticas, true);
	}

	if (UserList[AtacanteIndex].clase == eClass_Thief) {
		Desarmar(AtacanteIndex, VictimaIndex);
	}

	retval = true;

	return retval;
}

void UserDanoUser(int AtacanteIndex, int VictimaIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 12/01/2010 (ZaMa) */
	/* '12/01/2010: ZaMa - Implemento armas arrojadizas y probabilidad de acuchillar. */
	/* '11/03/2010: ZaMa - Ahora no cuenta la muerte si estaba en estado atacable, y no se vuelve criminal. */
	/* '18/09/2010: ZaMa - Ahora se cosidera la defensa de los barcos siempre. */
	/* '*************************************************** */

	int dano;
	int Lugar;
	struct ObjData Obj;

	int BoatDefense = 0;
	int BodyDefense = 0;
	int HeadDefense = 0;
	int WeaponBoost = 0;

	int BoatIndex;
	int WeaponIndex;
	int HelmetIndex;
	int ArmourIndex;
	int ShieldIndex;

//	int BarcaIndex;
//	int ArmaIndex;
//	int CascoIndex;
//	int ArmaduraIndex;

	dano = CalcularDano(AtacanteIndex);

	UserEnvenena(AtacanteIndex, VictimaIndex);

	/* ' Aumento de dano por barca (atacante) */
	if (UserList[AtacanteIndex].flags.Navegando == 1) {

		BoatIndex = UserList[AtacanteIndex].Invent.BarcoObjIndex;

		if (BoatIndex > 0) {
			Obj = ObjData[BoatIndex];
			dano = dano + RandomNumber(Obj.MinHIT, Obj.MaxHIT);
		}

	}

	/* ' Aumento de defensa por barca (victima) */
	if (UserList[VictimaIndex].flags.Navegando == 1) {

		BoatIndex = UserList[VictimaIndex].Invent.BarcoObjIndex;

		if (BoatIndex > 0) {
			Obj = ObjData[BoatIndex];
			BoatDefense = RandomNumber(Obj.MinDef, Obj.MaxDef);
		}

	}

	/* ' Refuerzo arma (atacante) */
	WeaponIndex = UserList[AtacanteIndex].Invent.WeaponEqpObjIndex;
	if (WeaponIndex > 0) {
		WeaponBoost = ObjData[WeaponIndex].Refuerzo;
	}

	Lugar = RandomNumber(PartesCuerpo_bCabeza, PartesCuerpo_bTorso);

	switch (Lugar) {

	case PartesCuerpo_bCabeza:

		/* 'Si tiene casco absorbe el golpe */
		HelmetIndex = UserList[VictimaIndex].Invent.CascoEqpObjIndex;
		if (HelmetIndex > 0) {
			Obj = ObjData[HelmetIndex];
			HeadDefense = RandomNumber(Obj.MinDef, Obj.MaxDef);
		}

		break;

	default:

		int MinDef = 0;
		int MaxDef = 0;

		/* 'Si tiene armadura absorbe el golpe */
		ArmourIndex = UserList[VictimaIndex].Invent.ArmourEqpObjIndex;
		if (ArmourIndex > 0) {
			Obj = ObjData[ArmourIndex];
			MinDef = Obj.MinDef;
			MaxDef = Obj.MaxDef;
		}

		/* ' Si tiene escudo, tambien absorbe el golpe */
		ShieldIndex = UserList[VictimaIndex].Invent.EscudoEqpObjIndex;
		if (ShieldIndex > 0) {
			Obj = ObjData[ShieldIndex];
			MinDef = MinDef + Obj.MinDef;
			MaxDef = MaxDef + Obj.MaxDef;
		}

		BodyDefense = RandomNumber(MinDef, MaxDef);

		break;
	}

	dano = dano + WeaponBoost - HeadDefense - BodyDefense - BoatDefense;
	if (dano < 0) {
		dano = 1;
	}

	WriteMultiMessage(AtacanteIndex, eMessages_UserHittedUser, UserList[VictimaIndex].Char.CharIndex, Lugar,
			dano);
	WriteMultiMessage(VictimaIndex, eMessages_UserHittedByUser, UserList[AtacanteIndex].Char.CharIndex, Lugar,
			dano);

	UserList[VictimaIndex].Stats.MinHp = UserList[VictimaIndex].Stats.MinHp - dano;

	if (UserList[AtacanteIndex].flags.Hambre == 0 && UserList[AtacanteIndex].flags.Sed == 0) {
		/* 'Si usa un arma quizas suba "Combate con armas" */
		if (WeaponIndex > 0) {
			if (ObjData[WeaponIndex].proyectil) {
				/* 'es un Arco. Sube Armas a Distancia */
				SubirSkill(AtacanteIndex, eSkill_Proyectiles, true);

				/* ' Si acuchilla */
				if (PuedeAcuchillar(AtacanteIndex)) {
					DoAcuchillar(AtacanteIndex, 0, VictimaIndex, dano);
				}
			} else {
				/* 'Sube combate con armas. */
				SubirSkill(AtacanteIndex, eSkill_Armas, true);
			}
		} else {
			/* 'sino tal vez lucha libre */
			SubirSkill(AtacanteIndex, eSkill_Wrestling, true);
		}

		/* 'Trata de apunalar por la espalda al enemigo */
		if (PuedeApunalar(AtacanteIndex)) {
			DoApunalar(AtacanteIndex, 0, VictimaIndex, dano);
		}
		/* 'e intenta dar un golpe crítico [Pablo (ToxicWaste)] */
		DoGolpeCritico(AtacanteIndex, 0, VictimaIndex, dano);
	}

	if (UserList[VictimaIndex].Stats.MinHp <= 0) {

		/* ' No cuenta la muerte si estaba en estado atacable */
		if (UserList[VictimaIndex].flags.AtacablePor != AtacanteIndex) {
			/* 'Store it! */
			StoreFrag(AtacanteIndex, VictimaIndex);

			ContarMuerte(VictimaIndex, AtacanteIndex);
		}

		/* ' Para que las mascotas no sigan intentando luchar y */
		/* ' comiencen a seguir al amo */
		int j;
		for (j = (1); j <= (MAXMASCOTAS); j++) {
			if (UserList[AtacanteIndex].MascotasIndex[j] > 0) {
				if (Npclist[UserList[AtacanteIndex].MascotasIndex[j]].Target == VictimaIndex) {
					Npclist[UserList[AtacanteIndex].MascotasIndex[j]].Target = 0;
					FollowAmo(UserList[AtacanteIndex].MascotasIndex[j]);
				}
			}
		}

		ActStats(VictimaIndex, AtacanteIndex);
		UserDie(VictimaIndex);
	} else {
		/* 'Está vivo - Actualizamos el HP */
		WriteUpdateHP(VictimaIndex);
	}

	/* 'Controla el nivel del usuario */
	CheckUserLevel(AtacanteIndex);

	FlushBuffer(VictimaIndex);
}

void UsuarioAtacadoPorUsuario(int AttackerIndex, int VictimIndex) {
	/* '*************************************************** */
	/* 'Autor: Unknown */
	/* 'Last Modification: 05/05/2010 */
	/* 'Last Modified By: Lucas Tavolaro Ortiz (Tavo) */
	/* '10/01/2008: Tavo - Se cancela la salida del juego si el user esta saliendo */
	/* '05/05/2010: ZaMa - Ahora no suma puntos de bandido al atacar a alguien en estado atacable. */
	/* '*************************************************** */

	if (TriggerZonaPelea(AttackerIndex, VictimIndex) == eTrigger6_TRIGGER6_PERMITE) {
		return;
	}

	bool EraCriminal = false;
	bool VictimaEsAtacable = false;

	if (!criminal(AttackerIndex)) {
		if (!criminal(VictimIndex)) {
			/* ' Si la victima no es atacable por el agresor, entonces se hace pk */
			VictimaEsAtacable = UserList[VictimIndex].flags.AtacablePor == AttackerIndex;
			if (!VictimaEsAtacable) {
				VolverCriminal(AttackerIndex);
			}
		}
	}

	if (UserList[VictimIndex].flags.Meditando) {
		UserList[VictimIndex].flags.Meditando = false;
		WriteMeditateToggle(VictimIndex);
		WriteConsoleMsg(VictimIndex, "Dejas de meditar.", FontTypeNames_FONTTYPE_INFO);
		UserList[VictimIndex].Char.FX = 0;
		UserList[VictimIndex].Char.loops = 0;
		SendData(SendTarget_ToPCArea, VictimIndex,
				dakara::protocol::server::BuildCreateFX(UserList[VictimIndex].Char.CharIndex, 0, 0));
	}

	EraCriminal = criminal(AttackerIndex);

	/* ' Si ataco a un atacable, no suma puntos de bandido */
	if (!VictimaEsAtacable) {
		if (!criminal(VictimIndex)) {
			UserList[AttackerIndex].Reputacion.BandidoRep = UserList[AttackerIndex].Reputacion.BandidoRep
					+ vlASALTO;
			if (UserList[AttackerIndex].Reputacion.BandidoRep > MAXREP) {
				UserList[AttackerIndex].Reputacion.BandidoRep = MAXREP;
			}

			UserList[AttackerIndex].Reputacion.NobleRep = UserList[AttackerIndex].Reputacion.NobleRep * 0.5;
			if (UserList[AttackerIndex].Reputacion.NobleRep < 0) {
				UserList[AttackerIndex].Reputacion.NobleRep = 0;
			}
		} else {
			UserList[AttackerIndex].Reputacion.NobleRep = UserList[AttackerIndex].Reputacion.NobleRep
					+ vlNoble;
			if (UserList[AttackerIndex].Reputacion.NobleRep > MAXREP) {
				UserList[AttackerIndex].Reputacion.NobleRep = MAXREP;
			}
		}
	}

	if (criminal(AttackerIndex)) {
		if (UserList[AttackerIndex].Faccion.ArmadaReal == 1) {
			ExpulsarFaccionReal(AttackerIndex);
		}

		if (!EraCriminal) {
			RefreshCharStatus(AttackerIndex);
		}
	} else if (EraCriminal) {
		RefreshCharStatus(AttackerIndex);
	}

	AllMascotasAtacanUser(AttackerIndex, VictimIndex);
	AllMascotasAtacanUser(VictimIndex, AttackerIndex);

	/* 'Si la victima esta saliendo se cancela la salida */
	CancelExit(VictimIndex);
	FlushBuffer(VictimIndex);
}

void AllMascotasAtacanUser(int victim, int Maestro) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */
	/* 'Reaccion de las mascotas */
	int iCount;

	for (iCount = (1); iCount <= (MAXMASCOTAS); iCount++) {
		if (UserList[Maestro].MascotasIndex[iCount] > 0) {
			Npclist[UserList[Maestro].MascotasIndex[iCount]].flags.AttackedBy = UserList[victim].Name;
			Npclist[UserList[Maestro].MascotasIndex[iCount]].Movement = TipoAI_NPCDEFENSA;
			Npclist[UserList[Maestro].MascotasIndex[iCount]].Hostile = 1;
		}
	}
}

bool PuedeAtacar(int AttackerIndex, int VictimIndex) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Autor: Unknown */
	/* 'Last Modification: 02/04/2010 */
	/* 'Returns true if the AttackerIndex is allowed to attack the VictimIndex. */
	/* '24/01/2007 Pablo (ToxicWaste) - Ordeno todo y agrego situacion de Defensa en ciudad Armada y Caos. */
	/* '24/02/2009: ZaMa - Los usuarios pueden atacarse entre si. */
	/* '02/04/2010: ZaMa - Los armadas no pueden atacar nunca a los ciudas, salvo que esten atacables. */
	/* '*************************************************** */

	/* 'MUY importante el orden de estos "IF"... */

	/* 'Estas muerto no podes atacar */
	if (UserList[AttackerIndex].flags.Muerto == 1) {
		WriteConsoleMsg(AttackerIndex, "¡¡Estás muerto!!", FontTypeNames_FONTTYPE_INFO);
		retval = false;
		return retval;
	}

	/* 'No podes atacar a alguien muerto */
	if (UserList[VictimIndex].flags.Muerto == 1) {
		WriteConsoleMsg(AttackerIndex, "No puedes atacar a un espíritu.", FontTypeNames_FONTTYPE_INFO);
		retval = false;
		return retval;
	}

	/* ' No podes atacar si estas en consulta */
	if (UserList[AttackerIndex].flags.EnConsulta) {
		WriteConsoleMsg(AttackerIndex, "No puedes atacar usuarios mientras estas en consulta.",
				FontTypeNames_FONTTYPE_INFO);
		return retval;
	}

	/* ' No podes atacar si esta en consulta */
	if (UserList[VictimIndex].flags.EnConsulta) {
		WriteConsoleMsg(AttackerIndex, "No puedes atacar usuarios mientras estan en consulta.",
				FontTypeNames_FONTTYPE_INFO);
		return retval;
	}

	/* 'Estamos en una Arena? o un trigger zona segura? */
	switch (TriggerZonaPelea(AttackerIndex, VictimIndex)) {
	case eTrigger6_TRIGGER6_PERMITE:
		retval = (UserList[VictimIndex].flags.AdminInvisible == 0);
		return retval;

		break;

	case eTrigger6_TRIGGER6_PROHIBE:
		retval = false;
		return retval;

		break;

	case eTrigger6_TRIGGER6_AUSENTE:
		/* 'Si no estamos en el Trigger 6 entonces es imposible atacar un gm */
		if (!UserTienePrivilegio(VictimIndex, PlayerType_User)) {
			if (UserList[VictimIndex].flags.AdminInvisible == 0) {
				WriteConsoleMsg(AttackerIndex, "El ser es demasiado poderoso.",
						FontTypeNames_FONTTYPE_WARNING);
			}
			retval = false;
			return retval;
		}
		break;
	}

	/* 'Ataca un ciudadano? */
	if (!criminal(VictimIndex)) {
		/* ' El atacante es ciuda? */
		if (!criminal(AttackerIndex)) {
			/* ' El atacante es armada? */
			if (esArmada(AttackerIndex)) {
				/* ' La victima es armada? */
				if (esArmada(VictimIndex)) {
					/* ' No puede */
					WriteConsoleMsg(AttackerIndex,
							"Los soldados del ejército real tienen prohibido atacar ciudadanos.",
							FontTypeNames_FONTTYPE_WARNING);
					return retval;
				}
			}

			/* ' Ciuda (o army) atacando a otro ciuda (o army) */
			if (UserList[VictimIndex].flags.AtacablePor == AttackerIndex) {
				/* ' Se vuelve atacable. */
				if (ToogleToAtackable(AttackerIndex, VictimIndex, false)) {
					retval = true;
					return retval;
				}
			}
		}
		/* ' Ataca a un criminal */
	} else {
		/* 'Sos un Caos atacando otro caos? */
		if (esCaos(VictimIndex)) {
			if (esCaos(AttackerIndex)) {
				WriteConsoleMsg(AttackerIndex,
						"Los miembros de la legión oscura tienen prohibido atacarse entre sí.",
						FontTypeNames_FONTTYPE_WARNING);
				return retval;
			}
		}
	}

	/* 'Tenes puesto el seguro? */
	if (UserList[AttackerIndex].flags.Seguro) {
		if (!criminal(VictimIndex)) {
			WriteConsoleMsg(AttackerIndex,
					"No puedes atacar ciudadanos, para hacerlo debes desactivar el seguro.",
					FontTypeNames_FONTTYPE_WARNING);
			retval = false;
			return retval;
		}
	} else {
		/* ' Un ciuda es atacado */
		if (!criminal(VictimIndex)) {
			/* ' Por un armada sin seguro */
			if (esArmada(AttackerIndex)) {
				/* ' No puede */
				WriteConsoleMsg(AttackerIndex,
						"Los soldados del ejército real tienen prohibido atacar ciudadanos.",
						FontTypeNames_FONTTYPE_WARNING);
				retval = false;
				return retval;
			}
		}
	}

	/* 'Estas en un Mapa Seguro? */
	if (MapInfo[UserList[VictimIndex].Pos.Map].Pk == false) {
		if (esArmada(AttackerIndex)) {
			if (UserList[AttackerIndex].Faccion.RecompensasReal > 11) {
				if (UserList[VictimIndex].Pos.Map == 58 || UserList[VictimIndex].Pos.Map == 59
						|| UserList[VictimIndex].Pos.Map == 60) {
					WriteConsoleMsg(VictimIndex,
							"¡Huye de la ciudad! Estás siendo atacado y no podrás defenderte.",
							FontTypeNames_FONTTYPE_WARNING);
					/* 'Beneficio de Armadas que atacan en su ciudad. */
					retval = true;
					return retval;
				}
			}
		}
		if (esCaos(AttackerIndex)) {
			if (UserList[AttackerIndex].Faccion.RecompensasCaos > 11) {
				if (UserList[VictimIndex].Pos.Map == 151 || UserList[VictimIndex].Pos.Map == 156) {
					WriteConsoleMsg(VictimIndex,
							"¡Huye de la ciudad! Estás siendo atacado y no podrás defenderte.",
							FontTypeNames_FONTTYPE_WARNING);
					/* 'Beneficio de Caos que atacan en su ciudad. */
					retval = true;
					return retval;
				}
			}
		}
		WriteConsoleMsg(AttackerIndex, "Esta es una zona segura, aquí no puedes atacar a otros usuarios.",
				FontTypeNames_FONTTYPE_WARNING);
		retval = false;
		return retval;
	}

	/* 'Estas atacando desde un trigger seguro? o tu victima esta en uno asi? */
	if (MapData[UserList[VictimIndex].Pos.Map][UserList[VictimIndex].Pos.X][UserList[VictimIndex].Pos.Y].trigger
			== eTrigger_ZONASEGURA
			|| MapData[UserList[AttackerIndex].Pos.Map][UserList[AttackerIndex].Pos.X][UserList[AttackerIndex].Pos.Y].trigger
					== eTrigger_ZONASEGURA) {
		WriteConsoleMsg(AttackerIndex, "No puedes pelear aquí.", FontTypeNames_FONTTYPE_WARNING);
		retval = false;
		return retval;
	}

	retval = true;
	return retval;
}

bool PuedeAtacarNPC(int AttackerIndex, int NpcIndex, bool Paraliza, bool IsPet) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Autor: Unknown Author (Original version) */
	/* 'Returns True if AttackerIndex can attack the NpcIndex */
	/* 'Last Modification: 04/07/2010 */
	/* '24/01/2007 Pablo (ToxicWaste) - Orden y corrección de ataque sobre una mascota y guardias */
	/* '14/08/2007 Pablo (ToxicWaste) - Reescribo y agrego TODOS los casos posibles cosa de usar */
	/* 'esta función para todo lo referente a ataque a un NPC. Ya sea Magia, Físico o a Distancia. */
	/* '16/11/2009: ZaMa - Agrego validacion de pertenencia de npc. */
	/* '02/04/2010: ZaMa - Los armadas ya no peuden atacar npcs no hotiles. */
	/* '23/05/2010: ZaMa - El inmo/para renuevan el timer de pertenencia si el ataque fue a un npc propio. */
	/* '04/07/2010: ZaMa - Ahora no se puede apropiar del dragon de dd. */
	/* '*************************************************** */

	/* 'Estas muerto? */
	if (UserList[AttackerIndex].flags.Muerto == 1) {
		WriteConsoleMsg(AttackerIndex, "¡¡Estás muerto!!", FontTypeNames_FONTTYPE_INFO);
		return retval;
	}

	/* 'Sos consejero? */
	if (UserTienePrivilegio(AttackerIndex, PlayerType_Consejero)) {
		/* 'No pueden atacar NPC los Consejeros. */
		return retval;
	}

	/* ' No podes atacar si estas en consulta */
	if (UserList[AttackerIndex].flags.EnConsulta) {
		WriteConsoleMsg(AttackerIndex, "No puedes atacar npcs mientras estas en consulta.",
				FontTypeNames_FONTTYPE_INFO);
		return retval;
	}

	/* 'Es una criatura atacable? */
	if (Npclist[NpcIndex].Attackable == 0) {
		WriteConsoleMsg(AttackerIndex, "No puedes atacar esta criatura.", FontTypeNames_FONTTYPE_INFO);
		return retval;
	}

	/* 'Es valida la distancia a la cual estamos atacando? */
	if (Distancia(UserList[AttackerIndex].Pos, Npclist[NpcIndex].Pos) >= MAXDISTANCIAARCO) {
		WriteConsoleMsg(AttackerIndex, "Estás muy lejos para disparar.", FontTypeNames_FONTTYPE_FIGHT);
		return retval;
	}

	/* 'Es una criatura No-Hostil? */
	if (Npclist[NpcIndex].Hostile == 0) {
		/* 'Es Guardia del Caos? */
		if (Npclist[NpcIndex].NPCtype == eNPCType_Guardiascaos) {
			/* 'Lo quiere atacar un caos? */
			if (esCaos(AttackerIndex)) {
				WriteConsoleMsg(AttackerIndex,
						"No puedes atacar Guardias del Caos siendo de la legión oscura.",
						FontTypeNames_FONTTYPE_INFO);
				return retval;
			}
			/* 'Es guardia Real? */
		} else if (Npclist[NpcIndex].NPCtype == eNPCType_GuardiaReal) {
			/* 'Lo quiere atacar un Armada? */
			if (esArmada(AttackerIndex)) {
				WriteConsoleMsg(AttackerIndex, "No puedes atacar Guardias Reales siendo del ejército real.",
						FontTypeNames_FONTTYPE_INFO);
				return retval;
			}
			/* 'Tienes el seguro puesto? */
			if (UserList[AttackerIndex].flags.Seguro) {
				WriteConsoleMsg(AttackerIndex, "Para poder atacar Guardias Reales debes quitarte el seguro.",
						FontTypeNames_FONTTYPE_INFO);
				return retval;
			} else {
				WriteConsoleMsg(AttackerIndex, "¡Atacaste un Guardia Real! Eres un criminal.",
						FontTypeNames_FONTTYPE_INFO);
				VolverCriminal(AttackerIndex);
				retval = true;
				return retval;
			}

			/* 'No era un Guardia, asi que es una criatura No-Hostil común. */
			/* 'Para asegurarnos que no sea una Mascota: */
		} else if (Npclist[NpcIndex].MaestroUser == 0) {
			/* 'Si sos ciudadano tenes que quitar el seguro para atacarla. */
			if (!criminal(AttackerIndex)) {

				/* ' Si sos armada no podes atacarlo directamente */
				if (esArmada(AttackerIndex)) {
					WriteConsoleMsg(AttackerIndex,
							"Los miembros del ejército real no pueden atacar npcs no hostiles.",
							FontTypeNames_FONTTYPE_INFO);
					return retval;
				}

				/* 'Sos ciudadano, tenes el seguro puesto? */
				if (UserList[AttackerIndex].flags.Seguro) {
					WriteConsoleMsg(AttackerIndex, "Para atacar a este NPC debes quitarte el seguro.",
							FontTypeNames_FONTTYPE_INFO);
					return retval;
				} else {
					/* 'No tiene seguro puesto. Puede atacar pero es penalizado. */
					WriteConsoleMsg(AttackerIndex,
							"Atacaste un NPC no-hostil. Continúa haciéndolo y te podrás convertir en criminal.",
							FontTypeNames_FONTTYPE_INFO);
					/* 'NicoNZ: Cambio para que al atacar npcs no hostiles no bajen puntos de nobleza */
					DisNobAuBan(AttackerIndex, 0, 1000);
					retval = true;
					return retval;
				}
			}
		}
	}

	int MasterIndex;
	MasterIndex = Npclist[NpcIndex].MaestroUser;

	/* 'Es el NPC mascota de alguien? */
	if (MasterIndex > 0) {

		/* ' Dueno de la mascota ciuda? */
		if (!criminal(MasterIndex)) {

			/* ' Atacante ciuda? */
			if (!criminal(AttackerIndex)) {

				/* ' Si esta en estado atacable puede atacar su mascota sin problemas */
				if (UserList[MasterIndex].flags.AtacablePor == AttackerIndex) {
					/* ' Toogle to atacable and restart the timer */
					ToogleToAtackable(AttackerIndex, MasterIndex);
					retval = true;
					return retval;
				}

				/* 'Atacante armada? */
				if (esArmada(AttackerIndex)) {
					/* 'El atacante es Armada y esta intentando atacar mascota de un Ciudadano */
					WriteConsoleMsg(AttackerIndex,
							"Los miembros del ejército real no pueden atacar mascotas de ciudadanos.",
							FontTypeNames_FONTTYPE_INFO);
					return retval;
				}

				/* 'El atacante es Ciudadano y esta intentando atacar mascota de un Ciudadano. */
				if (UserList[AttackerIndex].flags.Seguro) {
					/* 'El atacante tiene el seguro puesto. No puede atacar. */
					WriteConsoleMsg(AttackerIndex,
							"Para atacar mascotas de ciudadanos debes quitarte el seguro.",
							FontTypeNames_FONTTYPE_INFO);
					return retval;
				} else {
					/* 'El atacante no tiene el seguro puesto. Recibe penalización. */
					WriteConsoleMsg(AttackerIndex,
							"Has atacado la Mascota de un ciudadano. Eres un criminal.",
							FontTypeNames_FONTTYPE_INFO);
					VolverCriminal(AttackerIndex);
					retval = true;
					return retval;
				}
			} else {
				/* 'El atacante es criminal y quiere atacar un elemental ciuda, pero tiene el seguro puesto (NicoNZ) */
				if (UserList[AttackerIndex].flags.Seguro) {
					WriteConsoleMsg(AttackerIndex,
							"Para atacar mascotas de ciudadanos debes quitarte el seguro.",
							FontTypeNames_FONTTYPE_INFO);
					return retval;
				}
			}

			/* 'Es mascota de un caos? */
		} else if (esCaos(MasterIndex)) {
			/* 'Es Caos el Dueno. */
			if (esCaos(AttackerIndex)) {
				/* 'Un Caos intenta atacar una criatura de un Caos. No puede atacar. */
				WriteConsoleMsg(AttackerIndex,
						"Los miembros de la legión oscura no pueden atacar mascotas de otros legionarios. ",
						FontTypeNames_FONTTYPE_INFO);
				return retval;
			}
		}

		/* ' No es mascota de nadie, le pertenece a alguien? */
	} else if (Npclist[NpcIndex].Owner > 0) {

		int OwnerUserIndex;
		OwnerUserIndex = Npclist[NpcIndex].Owner;

		/* ' Puede atacar a su propia criatura! */
		if (OwnerUserIndex == AttackerIndex) {
			retval = true;
			/* ' Renuevo el timer */
			IntervaloPerdioNpc(OwnerUserIndex, true);
			return retval;
		}

		/* ' Esta compartiendo el npc con el atacante? => Puede atacar! */
		if (UserList[OwnerUserIndex].flags.ShareNpcWith == AttackerIndex) {
			retval = true;
			return retval;
		}

		/* ' Si son del mismo clan o party, pueden atacar (No renueva el timer) */
		if (!SameClan(OwnerUserIndex, AttackerIndex) && !SameParty(OwnerUserIndex, AttackerIndex)) {

			/* ' Si se le agoto el tiempo */
			/* ' Se lo roba :P */
			if (IntervaloPerdioNpc(OwnerUserIndex)) {
				PerdioNpc(OwnerUserIndex);
				ApropioNpc(AttackerIndex, NpcIndex);
				retval = true;
				return retval;

				/* ' Si lanzo un hechizo de para o inmo */
			} else if (Paraliza) {

				/* ' Si ya esta paralizado o inmobilizado, no puedo inmobilizarlo de nuevo */
				if (Npclist[NpcIndex].flags.Inmovilizado == 1 || Npclist[NpcIndex].flags.Paralizado == 1) {

					/* 'TODO_ZAMA: Si dejo esto asi, los pks con seguro peusto van a poder inmobilizar criaturas con dueno */
					/* ' Si es pk neutral, puede hacer lo que quiera :P. */
					if (!criminal(AttackerIndex) && !criminal(OwnerUserIndex)) {

						/* 'El atacante es Armada */
						if (esArmada(AttackerIndex)) {

							/* 'Intententa paralizar un npc de un armada? */
							if (esArmada(OwnerUserIndex)) {
								/* 'El atacante es Armada y esta intentando paralizar un npc de un armada: No puede */
								WriteConsoleMsg(AttackerIndex,
										"Los miembros del Ejército Real no pueden paralizar criaturas ya paralizadas pertenecientes a otros miembros del Ejército Real",
										FontTypeNames_FONTTYPE_INFO);
								return retval;

								/* 'El atacante es Armada y esta intentando paralizar un npc de un ciuda */
							} else {
								/* ' Si tiene seguro no puede */
								if (UserList[AttackerIndex].flags.Seguro) {
									WriteConsoleMsg(AttackerIndex,
											"Para paralizar criaturas ya paralizadas pertenecientes a ciudadanos debes quitarte el seguro.",
											FontTypeNames_FONTTYPE_INFO);
									return retval;
								} else {
									/* ' Si ya estaba atacable, no podrá atacar a un npc perteneciente a otro ciuda */
									if (ToogleToAtackable(AttackerIndex, OwnerUserIndex)) {
										WriteConsoleMsg(AttackerIndex,
												"Has paralizado la criatura de un ciudadano, ahora eres atacable por él.",
												FontTypeNames_FONTTYPE_INFO);
										retval = true;
									}

									return retval;

								}
							}

							/* ' El atacante es ciuda */
						} else {
							/* 'El atacante tiene el seguro puesto, no puede paralizar */
							if (UserList[AttackerIndex].flags.Seguro) {
								WriteConsoleMsg(AttackerIndex,
										"Para paralizar criaturas ya paralizadas pertenecientes a ciudadanos debes quitarte el seguro.",
										FontTypeNames_FONTTYPE_INFO);
								return retval;

								/* 'El atacante no tiene el seguro puesto, ataca. */
							} else {
								/* ' Si ya estaba atacable, no podrá atacar a un npc perteneciente a otro ciuda */
								if (ToogleToAtackable(AttackerIndex, OwnerUserIndex)) {
									WriteConsoleMsg(AttackerIndex,
											"Has paralizado la criatura de un ciudadano, ahora eres atacable por él.",
											FontTypeNames_FONTTYPE_INFO);
									retval = true;
								}

								return retval;
							}
						}

						/* ' Al menos uno de los dos es criminal */
					} else {
						/* ' Si ambos son caos */
						if (esCaos(AttackerIndex) && esCaos(OwnerUserIndex)) {
							/* 'El atacante es Caos y esta intentando paralizar un npc de un Caos */
							WriteConsoleMsg(AttackerIndex,
									"Los miembros de la legión oscura no pueden paralizar criaturas ya paralizadas por otros legionarios.",
									FontTypeNames_FONTTYPE_INFO);
							return retval;
						}
					}

					/* ' El npc no esta inmobilizado ni paralizado */
				} else {
					/* ' Si no tiene dueno, puede apropiarselo */
					if (OwnerUserIndex == 0) {

						/* ' Siempre que no posea uno ya (el inmo/para no cambia pertenencia de npcs). */
						if (UserList[AttackerIndex].flags.OwnedNpc == 0) {
							ApropioNpc(AttackerIndex, NpcIndex);
						}

						/* ' Si inmobiliza a su propio npc, renueva el timer */
					} else if (OwnerUserIndex == AttackerIndex) {
						/* ' Renuevo el timer */
						IntervaloPerdioNpc(OwnerUserIndex, true);
					}

					/* ' Siempre se pueden paralizar/inmobilizar npcs con o sin dueno */
					/* ' que no tengan ese estado */
					retval = true;
					return retval;

				}

				/* ' No lanzó hechizos inmobilizantes */
			} else {

				/* ' El npc le pertenece a un ciudadano */
				if (!criminal(OwnerUserIndex)) {

					/* 'El atacante es Armada y esta intentando atacar un npc de un Ciudadano */
					if (esArmada(AttackerIndex)) {

						/* 'Intententa atacar un npc de un armada? */
						if (esArmada(OwnerUserIndex)) {
							/* 'El atacante es Armada y esta intentando atacar el npc de un armada: No puede */
							WriteConsoleMsg(AttackerIndex,
									"Los miembros del Ejército Real no pueden atacar criaturas pertenecientes a otros miembros del Ejército Real",
									FontTypeNames_FONTTYPE_INFO);
							return retval;

							/* 'El atacante es Armada y esta intentando atacar un npc de un ciuda */
						} else {

							/* ' Si tiene seguro no puede */
							if (UserList[AttackerIndex].flags.Seguro) {
								WriteConsoleMsg(AttackerIndex,
										"Para atacar criaturas ya pertenecientes a ciudadanos debes quitarte el seguro.",
										FontTypeNames_FONTTYPE_INFO);
								return retval;
							} else {
								/* ' Si ya estaba atacable, no podrá atacar a un npc perteneciente a otro ciuda */
								if (ToogleToAtackable(AttackerIndex, OwnerUserIndex)) {
									WriteConsoleMsg(AttackerIndex,
											"Has atacado a la criatura de un ciudadano, ahora eres atacable por él.",
											FontTypeNames_FONTTYPE_INFO);
									retval = true;
								}

								return retval;
							}
						}

						/* ' No es aramda, puede ser criminal o ciuda */
					} else {

						/* 'El atacante es Ciudadano y esta intentando atacar un npc de un Ciudadano. */
						if (!criminal(AttackerIndex)) {

							if (UserList[AttackerIndex].flags.Seguro) {
								/* 'El atacante tiene el seguro puesto. No puede atacar. */
								WriteConsoleMsg(AttackerIndex,
										"Para atacar criaturas pertenecientes a ciudadanos debes quitarte el seguro.",
										FontTypeNames_FONTTYPE_INFO);
								return retval;

								/* 'El atacante no tiene el seguro puesto, ataca. */
							} else {
								if (ToogleToAtackable(AttackerIndex, OwnerUserIndex)) {
									WriteConsoleMsg(AttackerIndex,
											"Has atacado a la criatura de un ciudadano, ahora eres atacable por él.",
											FontTypeNames_FONTTYPE_INFO);
									retval = true;
								}

								return retval;
							}

							/* 'El atacante es criminal y esta intentando atacar un npc de un Ciudadano. */
						} else {
							/* ' Es criminal atacando un npc de un ciuda, con seguro puesto. */
							if (UserList[AttackerIndex].flags.Seguro) {
								WriteConsoleMsg(AttackerIndex,
										"Para atacar criaturas pertenecientes a ciudadanos debes quitarte el seguro.",
										FontTypeNames_FONTTYPE_INFO);
								return retval;
							}

							retval = true;
						}
					}

					/* ' Es npc de un criminal */
				} else {
					if (esCaos(OwnerUserIndex)) {
						/* 'Es Caos el Dueno. */
						if (esCaos(AttackerIndex)) {
							/* 'Un Caos intenta atacar una npc de un Caos. No puede atacar. */
							WriteConsoleMsg(AttackerIndex,
									"Los miembros de la Legión Oscura no pueden atacar criaturas de otros legionarios. ",
									FontTypeNames_FONTTYPE_INFO);
							return retval;
						}
					}
				}
			}
		}

		/* ' Si no tiene dueno el npc, se lo apropia */
	} else {
		/* ' Solo pueden apropiarse de npcs los caos, armadas o ciudas. */
		if (!criminal(AttackerIndex) || esCaos(AttackerIndex)) {
			/* ' No puede apropiarse de los pretos! */
			if (Npclist[NpcIndex].NPCtype != eNPCType_Pretoriano) {
				/* ' No puede apropiarse del dragon de dd! */
				if (Npclist[NpcIndex].NPCtype != eNPCType_DRAGON) {
					/* ' Si es una mascota atacando, no se apropia del npc */
					if (!IsPet) {
						/* ' No es dueno de ningun npc => Se lo apropia. */
						if (UserList[AttackerIndex].flags.OwnedNpc == 0) {
							ApropioNpc(AttackerIndex, NpcIndex);
							/* ' Es dueno de un npc, pero no puede ser de este porque no tiene propietario. */
						} else {
							/* ' Se va a aduenar del npc (y perder el otro) solo si no inmobiliza/paraliza */
							if (!Paraliza) {
								ApropioNpc(AttackerIndex, NpcIndex);
							}
						}
					}
				}
			}
		}
	}

	/* 'Es el Rey Preatoriano? */
	if (Npclist[NpcIndex].NPCtype == eNPCType_Pretoriano) {
/* FIXME: PRETORIANOS */
#if 0
		if (!ClanPretoriano[Npclist[NpcIndex].ClanIndex]->CanAtackMember(NpcIndex)) {
			WriteConsoleMsg(AttackerIndex, "Debes matar al resto del ejército antes de atacar al rey.",
					FontTypeNames_FONTTYPE_FIGHT);
			return retval;
		}
#endif
	}

	retval = true;

	return retval;
}

bool SameClan(int UserIndex, int OtherUserIndex) {
	bool retval;
	/* '*************************************************** */
	/* 'Autor: ZaMa */
	/* 'Returns True if both players belong to the same clan. */
	/* 'Last Modification: 16/11/2009 */
	/* '*************************************************** */
	retval = (UserList[UserIndex].GuildIndex == UserList[OtherUserIndex].GuildIndex)
			&& UserList[UserIndex].GuildIndex != 0;
	return retval;
}

bool SameParty(int UserIndex, int OtherUserIndex) {
	bool retval;
	/* '*************************************************** */
	/* 'Autor: ZaMa */
	/* 'Returns True if both players belong to the same party. */
	/* 'Last Modification: 16/11/2009 */
	/* '*************************************************** */
	retval = UserList[UserIndex].PartyIndex == UserList[OtherUserIndex].PartyIndex
			&& UserList[UserIndex].PartyIndex != 0;
	return retval;
}

void CalcularDarExp(int UserIndex, int NpcIndex, int ElDano) {
	/* '*************************************************** */
	/* 'Autor: Nacho (Integer) */
	/* 'Last Modification: 03/09/06 Nacho */
	/* 'Reescribi gran parte del Sub */
	/* 'Ahora, da toda la experiencia del npc mientras este vivo. */
	/* '*************************************************** */
	int ExpaDar;

	/* '[Nacho] Chekeamos que las variables sean validas para las operaciones */
	if (ElDano <= 0) {
		ElDano = 0;
	}
	if (Npclist[NpcIndex].Stats.MaxHp <= 0) {
		return;
	}
	if (ElDano > Npclist[NpcIndex].Stats.MinHp) {
		ElDano = Npclist[NpcIndex].Stats.MinHp;
	}

	/* '[Nacho] La experiencia a dar es la porcion de vida quitada * toda la experiencia */
	ExpaDar = vb6::CLng(ElDano * (Npclist[NpcIndex].GiveEXP / Npclist[NpcIndex].Stats.MaxHp));
	if (ExpaDar <= 0) {
		return;
	}

	/* '[Nacho] Vamos contando cuanta experiencia sacamos, porque se da toda la que no se dio al user que mata al NPC */
	/* 'Esto es porque cuando un elemental ataca, no se da exp, y tambien porque la cuenta que hicimos antes */
	/* 'Podria dar un numero fraccionario, esas fracciones se acumulan hasta formar enteros ;P */
	if (ExpaDar > Npclist[NpcIndex].flags.ExpCount) {
		ExpaDar = Npclist[NpcIndex].flags.ExpCount;
		Npclist[NpcIndex].flags.ExpCount = 0;
	} else {
		Npclist[NpcIndex].flags.ExpCount = Npclist[NpcIndex].flags.ExpCount - ExpaDar;
	}

	/* '[Nacho] Le damos la exp al user */
	if (ExpaDar > 0) {
		if (UserList[UserIndex].PartyIndex > 0) {
			ObtenerExito(UserIndex, ExpaDar, Npclist[NpcIndex].Pos.Map, Npclist[NpcIndex].Pos.X,
					Npclist[NpcIndex].Pos.Y);
		} else {
			UserList[UserIndex].Stats.Exp = UserList[UserIndex].Stats.Exp + ExpaDar;
			if (UserList[UserIndex].Stats.Exp > MAXEXP) {
				UserList[UserIndex].Stats.Exp = MAXEXP;
			}
			WriteConsoleMsg(UserIndex, "Has ganado " + vb6::CStr(ExpaDar) + " puntos de experiencia.",
					FontTypeNames_FONTTYPE_FIGHT);
		}

		CheckUserLevel(UserIndex);
	}
}

eTrigger6 TriggerZonaPelea(int Origen, int Destino) {
	eTrigger6 retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	/* 'TODO: Pero que rebuscado!! */
	/* 'Nigo:  Te lo redisene, pero no te borro el TODO para que lo revises. */

	eTrigger tOrg;
	eTrigger tDst;

	tOrg = MapData[UserList[Origen].Pos.Map][UserList[Origen].Pos.X][UserList[Origen].Pos.Y].trigger;
	tDst = MapData[UserList[Destino].Pos.Map][UserList[Destino].Pos.X][UserList[Destino].Pos.Y].trigger;

	if (tOrg == eTrigger_ZONAPELEA || tDst == eTrigger_ZONAPELEA) {
		if (tOrg == tDst) {
			retval = eTrigger6_TRIGGER6_PERMITE;
		} else {
			retval = eTrigger6_TRIGGER6_PROHIBE;
		}
	} else {
		retval = eTrigger6_TRIGGER6_AUSENTE;
	}

	return retval;
}

void UserEnvenena(int AtacanteIndex, int VictimaIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int ObjInd;

	ObjInd = UserList[AtacanteIndex].Invent.WeaponEqpObjIndex;

	if (ObjInd > 0) {
		if (ObjData[ObjInd].proyectil == 1) {
			ObjInd = UserList[AtacanteIndex].Invent.MunicionEqpObjIndex;
		}

		if (ObjInd > 0) {
			if (ObjData[ObjInd].Envenena == 1) {

				if (RandomNumber(1, 100) < 60) {
					UserList[VictimaIndex].flags.Envenenado = 1;
					WriteConsoleMsg(VictimaIndex, "¡¡" + UserList[AtacanteIndex].Name + " te ha envenenado!!",
							FontTypeNames_FONTTYPE_FIGHT);
					WriteConsoleMsg(AtacanteIndex, "¡¡Has envenenado a " + UserList[VictimaIndex].Name + "!!",
							FontTypeNames_FONTTYPE_FIGHT);
				}
			}
		}
	}

	FlushBuffer(VictimaIndex);
}

void LanzarProyectil(int UserIndex, int X, int Y) {
	/* '*************************************************** */
	/* 'Autor: ZaMa */
	/* 'Last Modification: 10/07/2010 */
	/* 'Throws an arrow or knive to target user/npc. */
	/* '*************************************************** */

	int MunicionSlot;
	int MunicionIndex;
	int WeaponSlot;
	int WeaponIndex;

	int TargetUserIndex;
	int TargetNpcIndex;

	int DummyInt = 0;

	bool Threw;
	Threw = true;

	/* 'Make sure the item is valid and there is ammo equipped. */

	MunicionSlot = UserList[UserIndex].Invent.MunicionEqpSlot;
	MunicionIndex = UserList[UserIndex].Invent.MunicionEqpObjIndex;
	WeaponSlot = UserList[UserIndex].Invent.WeaponEqpSlot;
	WeaponIndex = UserList[UserIndex].Invent.WeaponEqpObjIndex;

	/* ' Tiene arma equipada? */
	if (WeaponIndex == 0) {
		DummyInt = 1;
		WriteConsoleMsg(UserIndex, "No tienes un arco o cuchilla equipada.", FontTypeNames_FONTTYPE_INFO);

		/* ' En un slot válido? */
	} else if (WeaponSlot < 1 || WeaponSlot > UserList[UserIndex].CurrentInventorySlots) {
		DummyInt = 1;
		WriteConsoleMsg(UserIndex, "No tienes un arco o cuchilla equipada.", FontTypeNames_FONTTYPE_INFO);

		/* ' Usa munición? (Si no la usa, puede ser un arma arrojadiza) */
	} else if (ObjData[WeaponIndex].Municion == 1) {

		/* ' La municion esta equipada en un slot valido? */
		if (MunicionSlot < 1 || MunicionSlot > UserList[UserIndex].CurrentInventorySlots) {
			DummyInt = 1;
			WriteConsoleMsg(UserIndex, "No tienes municiones equipadas.", FontTypeNames_FONTTYPE_INFO);

			/* ' Tiene munición? */
		} else if (MunicionIndex == 0) {
			DummyInt = 1;
			WriteConsoleMsg(UserIndex, "No tienes municiones equipadas.", FontTypeNames_FONTTYPE_INFO);

			/* ' Son flechas? */
		} else if (ObjData[MunicionIndex].OBJType != eOBJType_otFlechas) {
			DummyInt = 1;
			WriteConsoleMsg(UserIndex, "No tienes municiones.", FontTypeNames_FONTTYPE_INFO);

			/* ' Tiene suficientes? */
		} else if (UserList[UserIndex].Invent.Object[MunicionSlot].Amount < 1) {
			DummyInt = 1;
			WriteConsoleMsg(UserIndex, "No tienes municiones.", FontTypeNames_FONTTYPE_INFO);
		}

		/* ' Es un arma de proyectiles? */
	} else if (ObjData[WeaponIndex].proyectil != 1) {
		DummyInt = 2;
	}

	if (DummyInt != 0) {
		if (DummyInt == 1) {
			Desequipar(UserIndex, WeaponSlot, false);
		}

		Desequipar(UserIndex, MunicionSlot, true);
		return;
	}

	/* 'Quitamos stamina */
	if (UserList[UserIndex].Stats.MinSta >= 10) {
		QuitarSta(UserIndex, RandomNumber(1, 10));
	} else {
		if (UserList[UserIndex].Genero == eGenero_Hombre) {
			WriteConsoleMsg(UserIndex, "Estás muy cansado para luchar.", FontTypeNames_FONTTYPE_INFO);
		} else {
			WriteConsoleMsg(UserIndex, "Estás muy cansada para luchar.", FontTypeNames_FONTTYPE_INFO);
		}
		return;
	}

	LookatTile(UserIndex, UserList[UserIndex].Pos.Map, X, Y);

	TargetUserIndex = UserList[UserIndex].flags.TargetUser;
	TargetNpcIndex = UserList[UserIndex].flags.TargetNPC;

	/* 'Validate target */
	if (TargetUserIndex > 0) {
		/* 'Only allow to atack if the other one can retaliate (can see us) */
		if (vb6::Abs(UserList[TargetUserIndex].Pos.Y - UserList[UserIndex].Pos.Y) > RANGO_VISION_Y) {
			WriteConsoleMsg(UserIndex, "Estás demasiado lejos para atacar.", FontTypeNames_FONTTYPE_WARNING);
			return;
		}

		/* 'Prevent from hitting self */
		if (TargetUserIndex == UserIndex) {
			WriteConsoleMsg(UserIndex, "¡No puedes atacarte a vos mismo!", FontTypeNames_FONTTYPE_INFO);
			return;
		}

		/* 'Attack! */
		Threw = UsuarioAtacaUsuario(UserIndex, TargetUserIndex);

	} else if (TargetNpcIndex > 0) {
		/* 'Only allow to atack if the other one can retaliate (can see us) */
		if (vb6::Abs(Npclist[TargetNpcIndex].Pos.Y - UserList[UserIndex].Pos.Y) > RANGO_VISION_Y
				&& vb6::Abs(Npclist[TargetNpcIndex].Pos.X - UserList[UserIndex].Pos.X) > RANGO_VISION_X) {
			WriteConsoleMsg(UserIndex, "Estás demasiado lejos para atacar.", FontTypeNames_FONTTYPE_WARNING);
			return;
		}

		/* 'Is it attackable??? */
		if (Npclist[TargetNpcIndex].Attackable != 0) {
			/* 'Attack! */
			Threw = UsuarioAtacaNpc(UserIndex, TargetNpcIndex);
		}
	}

	/* ' Solo pierde la munición si pudo atacar al target, o tiro al aire */
	if (Threw) {

		int Slot;

		/* ' Tiene equipado arco y flecha? */
		if (ObjData[WeaponIndex].Municion == 1) {
			Slot = MunicionSlot;
			/* ' Tiene equipado un arma arrojadiza */
		} else {
			Slot = WeaponSlot;
		}

		/* 'Take 1 knife/arrow away */
		QuitarUserInvItem(UserIndex, Slot, 1);
		UpdateUserInv(false, UserIndex, Slot);

	}
}
