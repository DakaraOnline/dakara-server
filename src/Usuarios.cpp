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

#include "Usuarios.h"
#include "boost/date_time/posix_time/posix_time.hpp"

void ActStats(int VictimIndex, int AttackerIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 11/03/2010 */
	/* '11/03/2010: ZaMa - Ahora no te vuelve cirminal por matar un atacable */
	/* '*************************************************** */

	int DaExp;
	bool EraCriminal;

	DaExp = vb6::CInt(UserList[VictimIndex].Stats.ELV) * 2;

	UserList[AttackerIndex].Stats.Exp = UserList[AttackerIndex].Stats.Exp + DaExp;
	if (UserList[AttackerIndex].Stats.Exp > MAXEXP) {
		UserList[AttackerIndex].Stats.Exp = MAXEXP;
	}

	if (TriggerZonaPelea(VictimIndex, AttackerIndex) != eTrigger6_TRIGGER6_PERMITE) {

		/* ' Es legal matarlo si estaba en atacable */
		if (UserList[VictimIndex].flags.AtacablePor != AttackerIndex) {
			EraCriminal = criminal(AttackerIndex);

			if (!criminal(VictimIndex)) {
				UserList[AttackerIndex].Reputacion.AsesinoRep = UserList[AttackerIndex].Reputacion.AsesinoRep
						+ vlASESINO * 2;
				if (UserList[AttackerIndex].Reputacion.AsesinoRep > MAXREP) {
					UserList[AttackerIndex].Reputacion.AsesinoRep = MAXREP;
				}
				UserList[AttackerIndex].Reputacion.BurguesRep = 0;
				UserList[AttackerIndex].Reputacion.NobleRep = 0;
				UserList[AttackerIndex].Reputacion.PlebeRep = 0;
			} else {
				UserList[AttackerIndex].Reputacion.NobleRep = UserList[AttackerIndex].Reputacion.NobleRep
						+ vlNoble;
				if (UserList[AttackerIndex].Reputacion.NobleRep > MAXREP) {
					UserList[AttackerIndex].Reputacion.NobleRep = MAXREP;
				}
			}

			bool EsCriminal;
			EsCriminal = criminal(AttackerIndex);

			if (EraCriminal != EsCriminal) {
				RefreshCharStatus(AttackerIndex);
			}

		}
	}

	/* 'Lo mata */
	WriteMultiMessage(AttackerIndex, eMessages_HaveKilledUser, VictimIndex, DaExp);
	WriteMultiMessage(VictimIndex, eMessages_UserKill, AttackerIndex);

	FlushBuffer(VictimIndex);

	/* 'Log */
	LogAsesinato(UserList[AttackerIndex].Name + " asesino a " + UserList[VictimIndex].Name);
}

void RevivirUsuario(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	UserList[UserIndex].flags.Muerto = 0;
	UserList[UserIndex].Stats.MinHp = UserList[UserIndex].Stats.UserAtributos[eAtributos_Constitucion];

	if (UserList[UserIndex].Stats.MinHp > UserList[UserIndex].Stats.MaxHp) {
		UserList[UserIndex].Stats.MinHp = UserList[UserIndex].Stats.MaxHp;
	}

	if (UserList[UserIndex].flags.Navegando == 1) {
		ToggleBoatBody(UserIndex);
	} else {
		DarCuerpoDesnudo(UserIndex);

		UserList[UserIndex].Char.Head = UserList[UserIndex].OrigChar.Head;
	}

	if (UserList[UserIndex].flags.Traveling) {
		UserList[UserIndex].flags.Traveling = 0;
		UserList[UserIndex].Counters.goHome = 0;
		WriteMultiMessage(UserIndex, eMessages_CancelHome);
	}

	ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
			UserList[UserIndex].Char.heading, UserList[UserIndex].Char.WeaponAnim,
			UserList[UserIndex].Char.ShieldAnim, UserList[UserIndex].Char.CascoAnim);
	WriteUpdateUserStats(UserIndex);
}

void ToggleBoatBody(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 25/07/2010 */
	/* 'Gives boat body depending on user alignment. */
	/* '25/07/2010: ZaMa - Now makes difference depending on faccion and atacable status. */
	/* '*************************************************** */

	int Ropaje;
	bool EsFaccionario = false;
	int NewBody = 0;

	UserList[UserIndex].Char.Head = 0;
	if (UserList[UserIndex].Invent.BarcoObjIndex == 0) {
		return;
	}

	Ropaje = ObjData[UserList[UserIndex].Invent.BarcoObjIndex].Ropaje;

	/* ' Criminales y caos */
	if (criminal(UserIndex)) {

		EsFaccionario = esCaos(UserIndex);

		if (Ropaje == iBarca) {
			if (EsFaccionario) {
				NewBody = iBarcaCaos;
			} else {
				NewBody = iBarcaPk;
			}
		} else if (Ropaje == iGalera) {
			if (EsFaccionario) {
				NewBody = iGaleraCaos;
			} else {
				NewBody = iGaleraPk;
			}
		} else if (Ropaje == iGaleon) {
			if (EsFaccionario) {
				NewBody = iGaleonCaos;
			} else {
				NewBody = iGaleonPk;
			}
		}

		/* ' Ciudas y Armadas */
	} else {

		EsFaccionario = esArmada(UserIndex);

		/* ' Atacable */
		if (UserList[UserIndex].flags.AtacablePor != 0) {

			if (Ropaje == iBarca) {
				if (EsFaccionario) {
					NewBody = iBarcaRealAtacable;
				} else {
					NewBody = iBarcaCiudaAtacable;
				}
			} else if (Ropaje == iGalera) {
				if (EsFaccionario) {
					NewBody = iGaleraRealAtacable;
				} else {
					NewBody = iGaleraCiudaAtacable;
				}
			} else if (Ropaje == iGaleon) {
				if (EsFaccionario) {
					NewBody = iGaleonRealAtacable;
				} else {
					NewBody = iGaleonCiudaAtacable;
				}
			}

			/* ' Normal */
		} else {

            if (Ropaje == iBarca) {
				if (EsFaccionario) {
					NewBody = iBarcaReal;
				} else {
					NewBody = iBarcaCiuda;
				}
			} else if (Ropaje == iGalera) {
				if (EsFaccionario) {
					NewBody = iGaleraReal;
				} else {
					NewBody = iGaleraCiuda;
				}
			} else if (Ropaje == iGaleon) {
				if (EsFaccionario) {
					NewBody = iGaleonReal;
				} else {
					NewBody = iGaleonCiuda;
				}
			}
		}
	}

	UserList[UserIndex].Char.body = NewBody;
	UserList[UserIndex].Char.ShieldAnim = NingunEscudo;
	UserList[UserIndex].Char.WeaponAnim = NingunArma;
	UserList[UserIndex].Char.CascoAnim = NingunCasco;

}

void ChangeUserChar(int UserIndex, int body, int Head, int heading, int Arma, int Escudo, int casco) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */
	UserList[UserIndex].Char.body = body;
	UserList[UserIndex].Char.Head = Head;
	UserList[UserIndex].Char.heading = static_cast<eHeading>(heading);
	UserList[UserIndex].Char.WeaponAnim = Arma;
	UserList[UserIndex].Char.ShieldAnim = Escudo;
	UserList[UserIndex].Char.CascoAnim = casco;

	SendData(SendTarget_ToPCArea, UserIndex,
			dakara::protocol::server::BuildCharacterChange(UserList[UserIndex].Char.CharIndex,body, Head, static_cast<eHeading>(heading),Arma,
					Escudo, casco, UserList[UserIndex].Char.FX, UserList[UserIndex].Char.loops));
}

int GetWeaponAnim(int UserIndex, int ObjIndex) {
	int retval;
	/* '*************************************************** */
	/* 'Author: Torres Patricio (Pato) */
	/* 'Last Modification: 03/29/10 */
	/* ' */
	/* '*************************************************** */
	int Tmp;

	Tmp = ObjData[ObjIndex].WeaponRazaEnanaAnim;

	if (Tmp > 0) {
		if (UserList[UserIndex].raza == eRaza_Enano || UserList[UserIndex].raza == eRaza_Gnomo) {
			retval = Tmp;
			return retval;
		}
	}

	retval = ObjData[ObjIndex].WeaponAnim;
	return retval;
}

void EnviarFama(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int L;

	L = (-UserList[UserIndex].Reputacion.AsesinoRep) + (-UserList[UserIndex].Reputacion.BandidoRep)
			+ UserList[UserIndex].Reputacion.BurguesRep + (-UserList[UserIndex].Reputacion.LadronesRep)
			+ UserList[UserIndex].Reputacion.NobleRep + UserList[UserIndex].Reputacion.PlebeRep;
	L = vb6::Round(L / 6);

	UserList[UserIndex].Reputacion.Promedio = L;

	WriteFame(UserIndex);
}

void EraseUserChar(int UserIndex, bool IsAdminInvisible) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 08/01/2009 */
	/* '08/01/2009: ZaMa - No se borra el char de un admin invisible en todos los clientes excepto en su mismo cliente. */
	/* '************************************************* */

	if (UserList[UserIndex].Char.CharIndex > 0 && UserList[UserIndex].Char.CharIndex <= LastChar) {

		CharList[UserList[UserIndex].Char.CharIndex] = 0;

		if (UserList[UserIndex].Char.CharIndex == LastChar) {
			while (!(CharList[LastChar] > 0)) {
				LastChar = LastChar - 1;
				if (LastChar <= 1) {
					break;
				}
			}
		}

		/* ' Si esta invisible, solo el sabe de su propia existencia, es innecesario borrarlo en los demas clientes */
		if (IsAdminInvisible) {
			SendData(SendTarget_ToUserIndex, UserIndex,
					dakara::protocol::server::BuildCharacterRemove(UserList[UserIndex].Char.CharIndex));
		} else {
			/* 'Le mandamos el mensaje para que borre el personaje a los clientes que estén cerca */
			SendData(SendTarget_ToPCArea, UserIndex,
					dakara::protocol::server::BuildCharacterRemove(UserList[UserIndex].Char.CharIndex));
		}
	}

	if (MapaValido(UserList[UserIndex].Pos.Map)) {
		QuitarUser(UserIndex, UserList[UserIndex].Pos.Map);

		MapData[UserList[UserIndex].Pos.Map][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].UserIndex =
				0;
	}

	UserList[UserIndex].Char.CharIndex = 0;

	NumChars = NumChars - 1;
	return;
}

void RefreshCharStatus(int UserIndex) {
	/* '************************************************* */
	/* 'Author: Tararira */
	/* 'Last modified: 04/07/2009 */
	/* 'Refreshes the status and tag of UserIndex. */
	/* '04/07/2009: ZaMa - Ahora mantenes la fragata fantasmal si estas muerto. */
	/* '************************************************* */
	std::string ClanTag;
	int NickColor;

	if (UserList[UserIndex].GuildIndex > 0) {
		ClanTag = GuildName(UserList[UserIndex].GuildIndex);
		ClanTag = " <" + ClanTag + ">";
	}

	NickColor = GetNickColor(UserIndex);

	if (UserList[UserIndex].showName) {
		SendData(SendTarget_ToPCArea, UserIndex,
				dakara::protocol::server::BuildUpdateTagAndStatus(UserIndex, NickColor, UserList[UserIndex].Name + ClanTag));
	} else {
		SendData(SendTarget_ToPCArea, UserIndex,
				dakara::protocol::server::BuildUpdateTagAndStatus(UserIndex, NickColor, ""));
	}

	/* 'Si esta navengando, se cambia la barca. */
	if (UserList[UserIndex].flags.Navegando) {
		if (UserList[UserIndex].flags.Muerto == 1) {
			UserList[UserIndex].Char.body = iFragataFantasmal;
		} else {
			ToggleBoatBody(UserIndex);
		}

		ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
				UserList[UserIndex].Char.heading, UserList[UserIndex].Char.WeaponAnim,
				UserList[UserIndex].Char.ShieldAnim, UserList[UserIndex].Char.CascoAnim);
	}
}

int GetNickColor(int UserIndex) {
	int retval;
	/* '************************************************* */
	/* 'Author: ZaMa */
	/* 'Last modified: 15/01/2010 */
	/* ' */
	/* '************************************************* */

	if (criminal(UserIndex)) {
		retval = eNickColor_ieCriminal;
	} else {
		retval = eNickColor_ieCiudadano;
	}

	if (UserList[UserIndex].flags.AtacablePor > 0) {
		retval = retval | eNickColor_ieAtacable;
	}

	return retval;
}

bool MakeUserChar(bool toMap, int sndIndex, int UserIndex, int Map, int X, int Y, bool ButIndex) {
	bool retval;
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 15/01/2010 */
	/* '23/07/2009: Budi - Ahora se envía el nick */
	/* '15/01/2010: ZaMa - Ahora se envia el color del nick. */
	/* '************************************************* */

	int CharIndex;
	std::string ClanTag;
	int NickColor;
	std::string UserName;
	int Privileges;

	if (InMapBounds(Map, X, Y)) {
		/* 'If needed make a new character in list */
		if (UserList[UserIndex].Char.CharIndex == 0) {
			CharIndex = NextOpenCharIndex();
			UserList[UserIndex].Char.CharIndex = CharIndex;
			CharList[CharIndex] = UserIndex;
		}

		/* 'Place character on map if needed */
		if (toMap) {
			MapData[Map][X][Y].UserIndex = UserIndex;
		}

		/* 'Send make character command to clients */
		if (!toMap) {
			if (UserList[UserIndex].GuildIndex > 0) {
				ClanTag = GuildName(UserList[UserIndex].GuildIndex);
			}

			NickColor = GetNickColor(UserIndex);

			/* FIXME: WTF es esto, le mandamos al cliente los privilegios? */
			// Privileges = UserList[UserIndex].flags.Privilegios;
			Privileges = 0;

			/* 'Preparo el nick */
			if (UserList[UserIndex].showName) {
				UserName = UserList[UserIndex].Name;

				if (UserList[UserIndex].flags.EnConsulta) {
					UserName = UserName + " " + TAG_CONSULT_MODE;
				} else {
					if (UserTieneAlgunPrivilegios(sndIndex, PlayerType_User, PlayerType_Consejero, PlayerType_RoleMaster)) {
						if (vb6::LenB(ClanTag) != 0) {
							UserName = UserName + " <" + ClanTag + ">";
						}
					} else {
						if ((UserList[UserIndex].flags.invisible || UserList[UserIndex].flags.Oculto)
								&& (UserList[UserIndex].flags.AdminInvisible != 1)) {
							UserName = UserName + " " + TAG_USER_INVISIBLE;
						} else {
							if (vb6::LenB(ClanTag) != 0) {
								UserName = UserName + " <" + ClanTag + ">";
							}
						}
					}
				}
			}

			WriteCharacterCreate(sndIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
					UserList[UserIndex].Char.heading, UserList[UserIndex].Char.CharIndex, X, Y,
					UserList[UserIndex].Char.WeaponAnim, UserList[UserIndex].Char.ShieldAnim,
					UserList[UserIndex].Char.FX, 999, UserList[UserIndex].Char.CascoAnim, UserName, NickColor,
					Privileges);
		} else {
			/* 'Hide the name and clan - set privs as normal user */
			AgregarUser(UserIndex, UserList[UserIndex].Pos.Map, ButIndex);
		}
	}

	retval = true;

	return retval;
}

/* '' */
/* ' Checks if the user gets the next level. */
/* ' */
/* ' @param UserIndex Specifies reference to user */

void CheckUserLevel(int UserIndex) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 08/04/2011 */
	/* 'Chequea que el usuario no halla alcanzado el siguiente nivel, */
	/* 'de lo contrario le da la vida, mana, etc, correspodiente. */
	/* '07/08/2006 Integer - Modificacion de los valores */
	/* '01/10/2007 Tavo - Corregido el BUG de STAT_MAXELV */
	/* '24/01/2007 Pablo (ToxicWaste) - Agrego modificaciones en ELU al subir de nivel. */
	/* '24/01/2007 Pablo (ToxicWaste) - Agrego modificaciones de la subida de mana de los magos por lvl. */
	/* '13/03/2007 Pablo (ToxicWaste) - Agrego diferencias entre el 18 y el 19 en Constitución. */
	/* '09/01/2008 Pablo (ToxicWaste) - Ahora el incremento de vida por Consitución se controla desde Balance.dat */
	/* '12/09/2008 Marco Vanotti (Marco) - Ahora si se llega a nivel 25 y está en un clan, se lo expulsa para no sumar antifacción */
	/* '02/03/2009 ZaMa - Arreglada la validacion de expulsion para miembros de clanes faccionarios que llegan a 25. */
	/* '11/19/2009 Pato - Modifico la nueva fórmula de maná ganada para el bandido y se la limito a 499 */
	/* '02/04/2010: ZaMa - Modifico la ganancia de hit por nivel del ladron. */
	/* '08/04/2011: Amraphen - Arreglada la distribución de probabilidades para la vida en el caso de promedio entero. */
	/* '************************************************* */
	int Pts = 0;
	int AumentoHIT = 0;
	int AumentoMANA = 0;
	int AumentoSTA = 0;
	int AumentoHP = 0;
	bool WasNewbie = false;
	double Promedio = 0;
	int aux = 0;
	vb6::array<int> DistVida;
	/* 'Guild Index */
	int GI = 0;

	DistVida.redim(1, 5);

	WasNewbie = EsNewbie(UserIndex);

	while (UserList[UserIndex].Stats.Exp >= UserList[UserIndex].Stats.ELU) {

		/* 'Checkea si alcanzó el máximo nivel */
		if (UserList[UserIndex].Stats.ELV >= STAT_MAXELV) {
			UserList[UserIndex].Stats.Exp = 0;
			UserList[UserIndex].Stats.ELU = 0;
			return;
		}

		/* 'Store it! */
		UserLevelUp(UserIndex);

		SendData(SendTarget_ToPCArea, UserIndex,
				dakara::protocol::server::BuildPlayWave(SND_NIVEL, UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y));
		WriteConsoleMsg(UserIndex, "¡Has subido de nivel!", FontTypeNames_FONTTYPE_INFO);

		if (UserList[UserIndex].Stats.ELV == 1) {
			Pts = 10;
		} else {
			/* 'For multiple levels being rised at once */
			Pts = Pts + 5;
		}

		UserList[UserIndex].Stats.ELV = UserList[UserIndex].Stats.ELV + 1;

		UserList[UserIndex].Stats.Exp = UserList[UserIndex].Stats.Exp - UserList[UserIndex].Stats.ELU;

		/* 'Nueva subida de exp x lvl. Pablo (ToxicWaste) */
		if (UserList[UserIndex].Stats.ELV < 15) {
			UserList[UserIndex].Stats.ELU = UserList[UserIndex].Stats.ELU * 1.4;
		} else if (UserList[UserIndex].Stats.ELV < 21) {
			UserList[UserIndex].Stats.ELU = UserList[UserIndex].Stats.ELU * 1.35;
		} else if (UserList[UserIndex].Stats.ELV < 26) {
			UserList[UserIndex].Stats.ELU = UserList[UserIndex].Stats.ELU * 1.3;
		} else if (UserList[UserIndex].Stats.ELV < 35) {
			UserList[UserIndex].Stats.ELU = UserList[UserIndex].Stats.ELU * 1.2;
		} else if (UserList[UserIndex].Stats.ELV < 40) {
			UserList[UserIndex].Stats.ELU = UserList[UserIndex].Stats.ELU * 1.3;
		} else {
			UserList[UserIndex].Stats.ELU = UserList[UserIndex].Stats.ELU * 1.375;
		}

		/* 'Calculo subida de vida */
		Promedio = ModVida[UserList[UserIndex].clase]
				- (21 - UserList[UserIndex].Stats.UserAtributos[eAtributos_Constitucion]) * 0.5;
		aux = RandomNumber(0, 100);

		if (Promedio - vb6::Int(Promedio) == 0.5) {
			/* 'Es promedio semientero */
			DistVida[1] = DistribucionSemienteraVida[1];
			DistVida[2] = DistVida[1] + DistribucionSemienteraVida[2];
			DistVida[3] = DistVida[2] + DistribucionSemienteraVida[3];
			DistVida[4] = DistVida[3] + DistribucionSemienteraVida[4];

			if (aux <= DistVida[1]) {
				AumentoHP = Promedio + 1.5;
			} else if (aux <= DistVida[2]) {
				AumentoHP = Promedio + 0.5;
			} else if (aux <= DistVida[3]) {
				AumentoHP = Promedio - 0.5;
			} else {
				AumentoHP = Promedio - 1.5;
			}
		} else {
			/* 'Es promedio entero */
			DistVida[1] = DistribucionEnteraVida[1];
			DistVida[2] = DistVida[1] + DistribucionEnteraVida[2];
			DistVida[3] = DistVida[2] + DistribucionEnteraVida[3];
			DistVida[4] = DistVida[3] + DistribucionEnteraVida[4];
			DistVida[5] = DistVida[4] + DistribucionEnteraVida[5];

			if (aux <= DistVida[1]) {
				AumentoHP = Promedio + 2;
			} else if (aux <= DistVida[2]) {
				AumentoHP = Promedio + 1;
			} else if (aux <= DistVida[3]) {
				AumentoHP = Promedio;
			} else if (aux <= DistVida[4]) {
				AumentoHP = Promedio - 1;
			} else {
				AumentoHP = Promedio - 2;
			}

		}

		switch (UserList[UserIndex].clase) {
		case eClass_Warrior:
			AumentoHIT = vb6::IIf(UserList[UserIndex].Stats.ELV > 35, 2, 3);
			AumentoSTA = AumentoSTDef;

			break;

		case eClass_Hunter:
			AumentoHIT = vb6::IIf(UserList[UserIndex].Stats.ELV > 35, 2, 3);
			AumentoSTA = AumentoSTDef;

			break;

		case eClass_Pirat:
			AumentoHIT = 3;
			AumentoSTA = AumentoSTDef;

			break;

		case eClass_Paladin:
			AumentoHIT = vb6::IIf(UserList[UserIndex].Stats.ELV > 35, 1, 3);
			AumentoMANA = UserList[UserIndex].Stats.UserAtributos[eAtributos_Inteligencia];
			AumentoSTA = AumentoSTDef;

			break;

		case eClass_Thief:
			AumentoHIT = 2;
			AumentoSTA = AumentoSTLadron;

			break;

		case eClass_Mage:
			AumentoHIT = 1;
			AumentoMANA = 2.8 * UserList[UserIndex].Stats.UserAtributos[eAtributos_Inteligencia];
			AumentoSTA = AumentoSTMago;

			break;

		case eClass_Worker:
			AumentoHIT = 2;
			AumentoSTA = AumentoSTTrabajador;

			break;

		case eClass_Cleric:
			AumentoHIT = 2;
			AumentoMANA = 2 * UserList[UserIndex].Stats.UserAtributos[eAtributos_Inteligencia];
			AumentoSTA = AumentoSTDef;

			break;

		case eClass_Druid:
			AumentoHIT = 2;
			AumentoMANA = 2 * UserList[UserIndex].Stats.UserAtributos[eAtributos_Inteligencia];
			AumentoSTA = AumentoSTDef;

			break;

		case eClass_Assasin:
			AumentoHIT = vb6::IIf(UserList[UserIndex].Stats.ELV > 35, 1, 3);
			AumentoMANA = UserList[UserIndex].Stats.UserAtributos[eAtributos_Inteligencia];
			AumentoSTA = AumentoSTDef;

			break;

		case eClass_Bard:
			AumentoHIT = 2;
			AumentoMANA = 2 * UserList[UserIndex].Stats.UserAtributos[eAtributos_Inteligencia];
			AumentoSTA = AumentoSTDef;

			break;

		case eClass_Bandit:
			AumentoHIT = vb6::IIf(UserList[UserIndex].Stats.ELV > 35, 1, 3);
			AumentoMANA = UserList[UserIndex].Stats.UserAtributos[eAtributos_Inteligencia] / 3 * 2;
			AumentoSTA = AumentoStBandido;

			break;

		default:
			AumentoHIT = 2;
			AumentoSTA = AumentoSTDef;
			break;
		}

		/* 'Actualizamos HitPoints */
		UserList[UserIndex].Stats.MaxHp = UserList[UserIndex].Stats.MaxHp + AumentoHP;
		if (UserList[UserIndex].Stats.MaxHp > STAT_MAXHP) {
			UserList[UserIndex].Stats.MaxHp = STAT_MAXHP;
		}

		/* 'Actualizamos Stamina */
		UserList[UserIndex].Stats.MaxSta = UserList[UserIndex].Stats.MaxSta + AumentoSTA;
		if (UserList[UserIndex].Stats.MaxSta > STAT_MAXSTA) {
			UserList[UserIndex].Stats.MaxSta = STAT_MAXSTA;
		}

		/* 'Actualizamos Mana */
		UserList[UserIndex].Stats.MaxMAN = UserList[UserIndex].Stats.MaxMAN + AumentoMANA;
		if (UserList[UserIndex].Stats.MaxMAN > STAT_MAXMAN) {
			UserList[UserIndex].Stats.MaxMAN = STAT_MAXMAN;
		}

		/* 'Actualizamos Golpe Máximo */
		UserList[UserIndex].Stats.MaxHIT = UserList[UserIndex].Stats.MaxHIT + AumentoHIT;
		if (UserList[UserIndex].Stats.ELV < 36) {
			if (UserList[UserIndex].Stats.MaxHIT > STAT_MAXHIT_UNDER36) {
				UserList[UserIndex].Stats.MaxHIT = STAT_MAXHIT_UNDER36;
			}
		} else {
			if (UserList[UserIndex].Stats.MaxHIT > STAT_MAXHIT_OVER36) {
				UserList[UserIndex].Stats.MaxHIT = STAT_MAXHIT_OVER36;
			}
		}

		/* 'Actualizamos Golpe Mínimo */
		UserList[UserIndex].Stats.MinHIT = UserList[UserIndex].Stats.MinHIT + AumentoHIT;
		if (UserList[UserIndex].Stats.ELV < 36) {
			if (UserList[UserIndex].Stats.MinHIT > STAT_MAXHIT_UNDER36) {
				UserList[UserIndex].Stats.MinHIT = STAT_MAXHIT_UNDER36;
			}
		} else {
			if (UserList[UserIndex].Stats.MinHIT > STAT_MAXHIT_OVER36) {
				UserList[UserIndex].Stats.MinHIT = STAT_MAXHIT_OVER36;
			}
		}

		/* 'Notificamos al user */
		if (AumentoHP > 0) {
			WriteConsoleMsg(UserIndex, "Has ganado " + vb6::CStr(AumentoHP) + " puntos de vida.",
					FontTypeNames_FONTTYPE_INFO);
		}
		if (AumentoSTA > 0) {
			WriteConsoleMsg(UserIndex, "Has ganado " + vb6::CStr(AumentoSTA) + " puntos de energía.",
					FontTypeNames_FONTTYPE_INFO);
		}
		if (AumentoMANA > 0) {
			WriteConsoleMsg(UserIndex, "Has ganado " + vb6::CStr(AumentoMANA) + " puntos de maná.",
					FontTypeNames_FONTTYPE_INFO);
		}
		if (AumentoHIT > 0) {
			WriteConsoleMsg(UserIndex, "Tu golpe máximo aumentó en " + vb6::CStr(AumentoHIT) + " puntos.",
					FontTypeNames_FONTTYPE_INFO);
			WriteConsoleMsg(UserIndex, "Tu golpe mínimo aumentó en " + vb6::CStr(AumentoHIT) + " puntos.",
					FontTypeNames_FONTTYPE_INFO);
		}

		LogDesarrollo(
				UserList[UserIndex].Name + " paso a nivel " + vb6::CStr(UserList[UserIndex].Stats.ELV) + " gano HP: "
						+ vb6::CStr(AumentoHP));

		UserList[UserIndex].Stats.MinHp = UserList[UserIndex].Stats.MaxHp;

		/* 'If user is in a party, we modify the variable p_sumaniveleselevados */
		ActualizarSumaNivelesElevados(UserIndex);
		/* 'If user reaches lvl 25 and he is in a guild, we check the guild's alignment and expulses the user if guild has factionary alignment */

		if (UserList[UserIndex].Stats.ELV == 25) {
			GI = UserList[UserIndex].GuildIndex;
			if (GI > 0) {
				if (GuildAlignment(GI) == "Del Mal" || GuildAlignment(GI) == "Real") {
					/* 'We get here, so guild has factionary alignment, we have to expulse the user */
					m_EcharMiembroDeClan(-1, UserList[UserIndex].Name);
					SendData(SendTarget_ToGuildMembers, GI,
							dakara::protocol::server::BuildConsoleMsg(UserList[UserIndex].Name + " deja el clan.",
									FontTypeNames_FONTTYPE_GUILD));
					WriteConsoleMsg(UserIndex,
							"¡Ya tienes la madurez suficiente como para decidir bajo que estandarte pelearás! Por esta razón, hasta tanto no te enlistes en la facción bajo la cual tu clan está alineado, estarás excluído del mismo.",
							FontTypeNames_FONTTYPE_GUILD);
				}
			}
		}

	}

	/* 'If it ceased to be a newbie, remove newbie items and get char away from newbie dungeon */
	if (!EsNewbie(UserIndex) && WasNewbie) {
		QuitarNewbieObj(UserIndex);
		if (MapInfo[UserList[UserIndex].Pos.Map].Restringir == eRestrict_restrict_newbie) {
			WarpUserChar(UserIndex, 1, 50, 50, true);
			WriteConsoleMsg(UserIndex, "Debes abandonar el Dungeon Newbie.", FontTypeNames_FONTTYPE_INFO);
		}
	}

	/* 'Send all gained skill points at once (if any) */
	if (Pts > 0) {
		WriteLevelUp(UserIndex, Pts);

		UserList[UserIndex].Stats.SkillPts = UserList[UserIndex].Stats.SkillPts + Pts;

		WriteConsoleMsg(UserIndex, "Has ganado un total de " + vb6::CStr(Pts) + " skillpoints.",
				FontTypeNames_FONTTYPE_INFO);
	}

	WriteUpdateUserStats(UserIndex);
	return;
}

bool PuedeAtravesarAgua(int UserIndex) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	retval = UserList[UserIndex].flags.Navegando == 1 || UserList[UserIndex].flags.Vuela == 1;
	return retval;
}

void MoveUserChar(int UserIndex, eHeading nHeading) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 13/07/2009 */
	/* 'Moves the char, sending the message to everyone in range. */
	/* '30/03/2009: ZaMa - Now it's legal to move where a casper is, changing its pos to where the moving char was. */
	/* '28/05/2009: ZaMa - When you are moved out of an Arena, the resurrection safe is activated. */
	/* '13/07/2009: ZaMa - Now all the clients don't know when an invisible admin moves, they force the admin to move. */
	/* '13/07/2009: ZaMa - Invisible admins aren't allowed to force dead characater to move */
	/* '************************************************* */
	struct WorldPos nPos;
	bool sailing;
	int CasperIndex = 0;
	eHeading CasperHeading;
	bool isAdminInvi;

	sailing = PuedeAtravesarAgua(UserIndex);
	nPos = UserList[UserIndex].Pos;
	HeadtoPos(nHeading, nPos);

	isAdminInvi = (UserList[UserIndex].flags.AdminInvisible == 1);

	if (MoveToLegalPos(UserList[UserIndex].Pos.Map, nPos.X, nPos.Y, sailing, !sailing)) {
		/* 'si no estoy solo en el mapa... */
		if (MapInfo[UserList[UserIndex].Pos.Map].NumUsers > 1) {

			CasperIndex = MapData[UserList[UserIndex].Pos.Map][nPos.X][nPos.Y].UserIndex;
			/* 'Si hay un usuario, y paso la validacion, entonces es un casper */
			if (CasperIndex > 0) {
				/* ' Los admins invisibles no pueden patear caspers */
				if (!isAdminInvi) {

					if (TriggerZonaPelea(UserIndex, CasperIndex) == eTrigger6_TRIGGER6_PROHIBE) {
						if (UserList[CasperIndex].flags.SeguroResu == false) {
							UserList[CasperIndex].flags.SeguroResu = true;
							WriteMultiMessage(CasperIndex, eMessages_ResuscitationSafeOn);
						}
					}

					CasperHeading = InvertHeading(nHeading);
					HeadtoPos(CasperHeading, UserList[CasperIndex].Pos);

					/* ' Si es un admin invisible, no se avisa a los demas clientes */
					if (UserList[CasperIndex].flags.AdminInvisible != 1) {
						SendData(SendTarget_ToPCAreaButIndex, CasperIndex,
								dakara::protocol::server::BuildCharacterMove(UserList[CasperIndex].Char.CharIndex,
										UserList[CasperIndex].Pos.X, UserList[CasperIndex].Pos.Y));
					}

					WriteForceCharMove(CasperIndex, CasperHeading);

					/* 'Update map and char */
					UserList[CasperIndex].Char.heading = CasperHeading;
					MapData[UserList[CasperIndex].Pos.Map][UserList[CasperIndex].Pos.X][UserList[CasperIndex].Pos.Y].UserIndex =
							CasperIndex;

					/* 'Actualizamos las áreas de ser necesario */
					CheckUpdateNeededUser(CasperIndex, CasperHeading);
				}
			}

			/* ' Si es un admin invisible, no se avisa a los demas clientes */
			if (!isAdminInvi) {
				SendData(SendTarget_ToPCAreaButIndex, UserIndex,
						dakara::protocol::server::BuildCharacterMove(UserList[UserIndex].Char.CharIndex, nPos.X, nPos.Y));
			}

		}

		/* ' Los admins invisibles no pueden patear caspers */
		if (!(isAdminInvi && (CasperIndex != 0))) {
			int oldUserIndex;

			oldUserIndex =
					MapData[UserList[UserIndex].Pos.Map][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].UserIndex;

			/* ' Si no hay intercambio de pos con nadie */
			if (oldUserIndex == UserIndex) {
				MapData[UserList[UserIndex].Pos.Map][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].UserIndex =
						0;
			}

			UserList[UserIndex].Pos = nPos;
			UserList[UserIndex].Char.heading = nHeading;
			MapData[UserList[UserIndex].Pos.Map][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].UserIndex =
					UserIndex;

			DoTileEvents(UserIndex, UserList[UserIndex].Pos.Map, UserList[UserIndex].Pos.X,
					UserList[UserIndex].Pos.Y);

			/* 'Actualizamos las áreas de ser necesario */
			CheckUpdateNeededUser(UserIndex, nHeading);
		} else {
			WritePosUpdate(UserIndex);
		}
	} else {
		WritePosUpdate(UserIndex);
	}

	if (UserList[UserIndex].Counters.Trabajando) {
		UserList[UserIndex].Counters.Trabajando = UserList[UserIndex].Counters.Trabajando - 1;
	}

	if (UserList[UserIndex].Counters.Ocultando) {
		UserList[UserIndex].Counters.Ocultando = UserList[UserIndex].Counters.Ocultando - 1;
	}
}

eHeading InvertHeading(eHeading nHeading) {
	eHeading retval = eHeading_None;
	/* '************************************************* */
	/* 'Author: ZaMa */
	/* 'Last modified: 30/03/2009 */
	/* 'Returns the heading opposite to the one passed by val. */
	/* '************************************************* */
	switch (nHeading) {
	case eHeading_EAST:
		retval = eHeading_WEST;
		break;

	case eHeading_WEST:
		retval = eHeading_EAST;
		break;

	case eHeading_SOUTH:
		retval = eHeading_NORTH;
		break;

	case eHeading_NORTH:
		retval = eHeading_SOUTH;
		break;

    case eHeading_None:
        throw std::runtime_error("eHeading_None");
	}
	return retval;
}

void ChangeUserInv(int UserIndex, int Slot, struct UserOBJ & Object) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	UserList[UserIndex].Invent.Object[Slot] = Object;
	WriteChangeInventorySlot(UserIndex, Slot);
}

int NextOpenCharIndex() {
	int retval = 0;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int LoopC;

	for (LoopC = (1); LoopC <= (MAXCHARS); LoopC++) {
		if (CharList[LoopC] == 0) {
			retval = LoopC;
			NumChars = NumChars + 1;

			if (LoopC > LastChar) {
				LastChar = LoopC;
			}

			return retval;
		}
	}
	return retval;
}

std::size_t NextOpenUser() {
	int retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int LoopC;

	// FIXME: BUSQUEDA LINEAL

	for (LoopC = (1); LoopC <= (MaxUsers + 1); LoopC++) {
		if (LoopC > MaxUsers) {
			break;
		}
		if ((UserList[LoopC].sockctx == nullptr && UserList[LoopC].flags.UserLogged == false)) {
			break;
		}
	}

	retval = LoopC;
	return retval;
}

void SendUserStatsTxt(int sendIndex, int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int GuildI;

	WriteConsoleMsg(sendIndex, "Estadísticas de: " + UserList[UserIndex].Name, FontTypeNames_FONTTYPE_INFO);
	WriteConsoleMsg(sendIndex,
			"Nivel: " + vb6::CStr(UserList[UserIndex].Stats.ELV) + "  EXP: " + vb6::CStr(UserList[UserIndex].Stats.Exp) + "/"
					+ vb6::CStr(UserList[UserIndex].Stats.ELU), FontTypeNames_FONTTYPE_INFO);
	WriteConsoleMsg(sendIndex,
			"Salud: " + vb6::CStr(UserList[UserIndex].Stats.MinHp) + "/" + vb6::CStr(UserList[UserIndex].Stats.MaxHp) + "  Maná: "
					+ vb6::CStr(UserList[UserIndex].Stats.MinMAN) + "/" + vb6::CStr(UserList[UserIndex].Stats.MaxMAN)
					+ "  Energía: " + vb6::CStr(UserList[UserIndex].Stats.MinSta) + "/"
					+ vb6::CStr(UserList[UserIndex].Stats.MaxSta), FontTypeNames_FONTTYPE_INFO);

	if (UserList[UserIndex].Invent.WeaponEqpObjIndex > 0) {
		WriteConsoleMsg(sendIndex,
				"Menor Golpe/Mayor Golpe: " + vb6::CStr(UserList[UserIndex].Stats.MinHIT) + "/"
						+ vb6::CStr(UserList[UserIndex].Stats.MaxHIT) + " ("
						+ vb6::CStr(ObjData[UserList[UserIndex].Invent.WeaponEqpObjIndex].MinHIT) + "/"
						+ vb6::CStr(ObjData[UserList[UserIndex].Invent.WeaponEqpObjIndex].MaxHIT) + ")",
				FontTypeNames_FONTTYPE_INFO);
	} else {
		WriteConsoleMsg(sendIndex,
				"Menor Golpe/Mayor Golpe: " + vb6::CStr(UserList[UserIndex].Stats.MinHIT) + "/"
						+ vb6::CStr(UserList[UserIndex].Stats.MaxHIT), FontTypeNames_FONTTYPE_INFO);
	}

	if (UserList[UserIndex].Invent.ArmourEqpObjIndex > 0) {
		if (UserList[UserIndex].Invent.EscudoEqpObjIndex > 0) {
			WriteConsoleMsg(sendIndex,
					"(CUERPO) Mín Def/Máx Def: "
							+ vb6::CStr(ObjData[UserList[UserIndex].Invent.ArmourEqpObjIndex].MinDef)
							+ vb6::CStr(ObjData[UserList[UserIndex].Invent.EscudoEqpObjIndex].MinDef) + "/"
							+ vb6::CStr(ObjData[UserList[UserIndex].Invent.ArmourEqpObjIndex].MaxDef)
							+ vb6::CStr(ObjData[UserList[UserIndex].Invent.EscudoEqpObjIndex].MaxDef),
					FontTypeNames_FONTTYPE_INFO);
		} else {
			WriteConsoleMsg(sendIndex,
					"(CUERPO) Mín Def/Máx Def: "
							+ vb6::CStr(ObjData[UserList[UserIndex].Invent.ArmourEqpObjIndex].MinDef) + "/"
							+ vb6::CStr(ObjData[UserList[UserIndex].Invent.ArmourEqpObjIndex].MaxDef),
					FontTypeNames_FONTTYPE_INFO);
		}
	} else {
		WriteConsoleMsg(sendIndex, "(CUERPO) Mín Def/Máx Def: 0", FontTypeNames_FONTTYPE_INFO);
	}

	if (UserList[UserIndex].Invent.CascoEqpObjIndex > 0) {
		WriteConsoleMsg(sendIndex,
				"(CABEZA) Mín Def/Máx Def: " + vb6::CStr(ObjData[UserList[UserIndex].Invent.CascoEqpObjIndex].MinDef)
						+ "/" + vb6::CStr(ObjData[UserList[UserIndex].Invent.CascoEqpObjIndex].MaxDef),
				FontTypeNames_FONTTYPE_INFO);
	} else {
		WriteConsoleMsg(sendIndex, "(CABEZA) Mín Def/Máx Def: 0", FontTypeNames_FONTTYPE_INFO);
	}

	GuildI = UserList[UserIndex].GuildIndex;
	if (GuildI > 0) {
		WriteConsoleMsg(sendIndex, "Clan: " + GuildName(GuildI), FontTypeNames_FONTTYPE_INFO);
		if (vb6::UCase(GuildLeader(GuildI)) == vb6::UCase(UserList[UserIndex].Name)) {
			WriteConsoleMsg(sendIndex, "Status: Líder", FontTypeNames_FONTTYPE_INFO);
		}
		/* 'guildpts no tienen objeto */
	}

	/* # IF ConUpTime THEN */
	boost::posix_time::time_duration TempDate;
	// std::string TempStr;
	TempDate = vb6::Now() - UserList[UserIndex].LogOnTime;
	int minutosTotales = UserList[UserIndex].UpTime;
	WriteConsoleMsg(sendIndex, "Logeado hace: " + boost::posix_time::to_simple_string(TempDate), FontTypeNames_FONTTYPE_INFO);
	std::stringstream s;
	s << "Total: " << ((minutosTotales/24)/60) <<" Dias, " << ((minutosTotales/60)%24) <<" Horas, "<< (minutosTotales%60) << " minutos";
	WriteConsoleMsg(sendIndex, s.str() , FontTypeNames_FONTTYPE_INFO);

	/* # END IF */
	if (UserList[UserIndex].flags.Traveling == 1) {
		WriteConsoleMsg(sendIndex,
				"Tiempo restante para llegar a tu hogar: " + vb6::CStr(GetHomeArrivalTime(UserIndex)) + " segundos.",
				FontTypeNames_FONTTYPE_INFO);
	}

	WriteConsoleMsg(sendIndex,
			"Oro: " + vb6::CStr(UserList[UserIndex].Stats.GLD) + "  Posición: " + vb6::CStr(UserList[UserIndex].Pos.X) + ","
					+ vb6::CStr(UserList[UserIndex].Pos.Y) + " en mapa " + vb6::CStr(UserList[UserIndex].Pos.Map),
			FontTypeNames_FONTTYPE_INFO);
	WriteConsoleMsg(sendIndex,
			"Dados: " + vb6::CStr(UserList[UserIndex].Stats.UserAtributos[eAtributos_Fuerza]) + ", "
					+ vb6::CStr(UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad]) + ", "
					+ vb6::CStr(UserList[UserIndex].Stats.UserAtributos[eAtributos_Inteligencia]) + ", "
					+ vb6::CStr(UserList[UserIndex].Stats.UserAtributos[eAtributos_Carisma]) + ", "
					+ vb6::CStr(UserList[UserIndex].Stats.UserAtributos[eAtributos_Constitucion]),
			FontTypeNames_FONTTYPE_INFO);
}

void SendUserMiniStatsTxt(int sendIndex, int UserIndex) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 23/01/2007 */
	/* 'Shows the users Stats when the user is online. */
	/* '23/01/2007 Pablo (ToxicWaste) - Agrego de funciones y mejora de distribución de parámetros. */
	/* '************************************************* */
	WriteConsoleMsg(sendIndex, "Pj: " + UserList[UserIndex].Name, FontTypeNames_FONTTYPE_INFO);
	WriteConsoleMsg(sendIndex,
			"Ciudadanos matados: " + vb6::CStr(UserList[UserIndex].Faccion.CiudadanosMatados) + " Criminales matados: "
					+ vb6::CStr(UserList[UserIndex].Faccion.CriminalesMatados) + " usuarios matados: "
					+ vb6::CStr(UserList[UserIndex].Stats.UsuariosMatados), FontTypeNames_FONTTYPE_INFO);
	WriteConsoleMsg(sendIndex, "NPCs muertos: " + vb6::CStr(UserList[UserIndex].Stats.NPCsMuertos),
			FontTypeNames_FONTTYPE_INFO);
	WriteConsoleMsg(sendIndex, "Clase: " + vb6::CStr(ListaClases[UserList[UserIndex].clase]),
			FontTypeNames_FONTTYPE_INFO);
	WriteConsoleMsg(sendIndex, "Pena: " + vb6::CStr(UserList[UserIndex].Counters.Pena), FontTypeNames_FONTTYPE_INFO);

	if (UserList[UserIndex].Faccion.ArmadaReal == 1) {
		WriteConsoleMsg(sendIndex, "Ejército real desde: " + UserList[UserIndex].Faccion.FechaIngreso,
				FontTypeNames_FONTTYPE_INFO);
		WriteConsoleMsg(sendIndex,
				"Ingresó en nivel: " + vb6::CStr(UserList[UserIndex].Faccion.NivelIngreso) + " con "
						+ vb6::CStr(UserList[UserIndex].Faccion.MatadosIngreso) + " ciudadanos matados.",
				FontTypeNames_FONTTYPE_INFO);
		WriteConsoleMsg(sendIndex, "Veces que ingresó: " + vb6::CStr(UserList[UserIndex].Faccion.Reenlistadas),
				FontTypeNames_FONTTYPE_INFO);

	} else if (UserList[UserIndex].Faccion.FuerzasCaos == 1) {
		WriteConsoleMsg(sendIndex, "Legión oscura desde: " + vb6::CStr(UserList[UserIndex].Faccion.FechaIngreso),
				FontTypeNames_FONTTYPE_INFO);
		WriteConsoleMsg(sendIndex, "Ingresó en nivel: " + vb6::CStr(UserList[UserIndex].Faccion.NivelIngreso),
				FontTypeNames_FONTTYPE_INFO);
		WriteConsoleMsg(sendIndex, "Veces que ingresó: " + vb6::CStr(UserList[UserIndex].Faccion.Reenlistadas),
				FontTypeNames_FONTTYPE_INFO);

	} else if (UserList[UserIndex].Faccion.RecibioExpInicialReal == 1) {
		WriteConsoleMsg(sendIndex, "Fue ejército real", FontTypeNames_FONTTYPE_INFO);
		WriteConsoleMsg(sendIndex, "Veces que ingresó: " + vb6::CStr(UserList[UserIndex].Faccion.Reenlistadas),
				FontTypeNames_FONTTYPE_INFO);

	} else if (UserList[UserIndex].Faccion.RecibioExpInicialCaos == 1) {
		WriteConsoleMsg(sendIndex, "Fue legión oscura", FontTypeNames_FONTTYPE_INFO);
		WriteConsoleMsg(sendIndex, "Veces que ingresó: " + vb6::CStr(UserList[UserIndex].Faccion.Reenlistadas),
				FontTypeNames_FONTTYPE_INFO);
	}

	WriteConsoleMsg(sendIndex, "Asesino: " + vb6::CStr(UserList[UserIndex].Reputacion.AsesinoRep),
			FontTypeNames_FONTTYPE_INFO);
	WriteConsoleMsg(sendIndex, "Noble: " + vb6::CStr(UserList[UserIndex].Reputacion.NobleRep),
			FontTypeNames_FONTTYPE_INFO);
	WriteConsoleMsg(sendIndex, "Bandido: " + vb6::CStr(UserList[UserIndex].Reputacion.BandidoRep),
			FontTypeNames_FONTTYPE_INFO);

	if (UserList[UserIndex].GuildIndex > 0) {
		WriteConsoleMsg(sendIndex, "Clan: " + GuildName(UserList[UserIndex].GuildIndex),
				FontTypeNames_FONTTYPE_INFO);
	}
}

void SendUserMiniStatsTxtFromChar(int sendIndex, std::string charName) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 23/01/2007 */
	/* 'Shows the users Stats when the user is offline. */
	/* '23/01/2007 Pablo (ToxicWaste) - Agrego de funciones y mejora de distribución de parámetros. */
	/* '************************************************* */
	std::string CharFile;
	std::string Ban;
	std::string BanDetailPath;

	BanDetailPath = GetLogFileName("BanDetail");
	CharFile = GetCharPath(charName);

	if (FileExist(CharFile)) {
		WriteConsoleMsg(sendIndex, "Pj: " + charName, FontTypeNames_FONTTYPE_INFO);
		WriteConsoleMsg(sendIndex,
				"Ciudadanos matados: " + GetVar(CharFile, "FACCIONES", "CiudMatados") + " CriminalesMatados: "
						+ GetVar(CharFile, "FACCIONES", "CrimMatados") + " usuarios matados: "
						+ GetVar(CharFile, "MUERTES", "UserMuertes"), FontTypeNames_FONTTYPE_INFO);
		WriteConsoleMsg(sendIndex, "NPCs muertos: " + GetVar(CharFile, "MUERTES", "NpcsMuertes"),
				FontTypeNames_FONTTYPE_INFO);
		WriteConsoleMsg(sendIndex, "Clase: " + ListaClases[vb6::CInt(GetVar(CharFile, "INIT", "Clase"))],
				FontTypeNames_FONTTYPE_INFO);
		WriteConsoleMsg(sendIndex, "Pena: " + GetVar(CharFile, "COUNTERS", "PENA"),
				FontTypeNames_FONTTYPE_INFO);

		if (vb6::CByte(GetVar(CharFile, "FACCIONES", "EjercitoReal")) == 1) {
			WriteConsoleMsg(sendIndex,
					"Ejército real desde: " + GetVar(CharFile, "FACCIONES", "FechaIngreso"),
					FontTypeNames_FONTTYPE_INFO);
			WriteConsoleMsg(sendIndex,
					"Ingresó en nivel: " + (GetVar(CharFile, "FACCIONES", "NivelIngreso")) + " con "
							+ (GetVar(CharFile, "FACCIONES", "MatadosIngreso"))
							+ " ciudadanos matados.", FontTypeNames_FONTTYPE_INFO);
			WriteConsoleMsg(sendIndex,
					"Veces que ingresó: " + vb6::CStr(vb6::CByte(GetVar(CharFile, "FACCIONES", "Reenlistadas"))),
					FontTypeNames_FONTTYPE_INFO);

		} else if (vb6::CByte(GetVar(CharFile, "FACCIONES", "EjercitoCaos")) == 1) {
			WriteConsoleMsg(sendIndex,
					"Legión oscura desde: " + GetVar(CharFile, "FACCIONES", "FechaIngreso"),
					FontTypeNames_FONTTYPE_INFO);
			WriteConsoleMsg(sendIndex,
					"Ingresó en nivel: " + vb6::CStr(vb6::CInt(GetVar(CharFile, "FACCIONES", "NivelIngreso"))),
					FontTypeNames_FONTTYPE_INFO);
			WriteConsoleMsg(sendIndex,
					"Veces que ingresó: " + vb6::CStr(vb6::CByte(GetVar(CharFile, "FACCIONES", "Reenlistadas"))),
					FontTypeNames_FONTTYPE_INFO);

		} else if (vb6::CByte(GetVar(CharFile, "FACCIONES", "rExReal")) == 1) {
			WriteConsoleMsg(sendIndex, "Fue ejército real", FontTypeNames_FONTTYPE_INFO);
			WriteConsoleMsg(sendIndex,
					"Veces que ingresó: " + vb6::CStr(vb6::CByte(GetVar(CharFile, "FACCIONES", "Reenlistadas"))),
					FontTypeNames_FONTTYPE_INFO);

		} else if (vb6::CByte(GetVar(CharFile, "FACCIONES", "rExCaos")) == 1) {
			WriteConsoleMsg(sendIndex, "Fue legión oscura", FontTypeNames_FONTTYPE_INFO);
			WriteConsoleMsg(sendIndex,
					"Veces que ingresó: " + vb6::CStr(vb6::CByte(GetVar(CharFile, "FACCIONES", "Reenlistadas"))),
					FontTypeNames_FONTTYPE_INFO);
		}

		WriteConsoleMsg(sendIndex, "Asesino: " + vb6::CStr(vb6::CLng(GetVar(CharFile, "REP", "Asesino"))),
				FontTypeNames_FONTTYPE_INFO);
		WriteConsoleMsg(sendIndex, "Noble: " + vb6::CStr(vb6::CLng(GetVar(CharFile, "REP", "Nobles"))),
				FontTypeNames_FONTTYPE_INFO);
		WriteConsoleMsg(sendIndex, "Bandido: " + vb6::CStr(vb6::CLng(GetVar(CharFile, "REP", "BANDIDO"))),
				FontTypeNames_FONTTYPE_INFO);

		if (vb6::IsNumeric(GetVar(CharFile, "Guild", "GUILDINDEX"))) {
			WriteConsoleMsg(sendIndex,
					"Clan: " + GuildName(vb6::CInt(GetVar(CharFile, "Guild", "GUILDINDEX"))),
					FontTypeNames_FONTTYPE_INFO);
		}

		Ban = GetVar(CharFile, "FLAGS", "Ban");
		WriteConsoleMsg(sendIndex, "Ban: " + Ban, FontTypeNames_FONTTYPE_INFO);

		if (Ban == "1") {
			WriteConsoleMsg(sendIndex,
					"Ban por: " + GetVar(CharFile, charName, "BannedBy") + " Motivo: "
							+ GetVar(BanDetailPath, charName, "Reason"), FontTypeNames_FONTTYPE_INFO);
		}
	} else {
		WriteConsoleMsg(sendIndex, "El pj no existe: " + charName, FontTypeNames_FONTTYPE_INFO);
	}
}

void SendUserInvTxt(int sendIndex, int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int j;

	WriteConsoleMsg(sendIndex, UserList[UserIndex].Name, FontTypeNames_FONTTYPE_INFO);
	WriteConsoleMsg(sendIndex, "Tiene " + vb6::CStr(UserList[UserIndex].Invent.NroItems) + " objetos.",
			FontTypeNames_FONTTYPE_INFO);

	for (j = (1); j <= (UserList[UserIndex].CurrentInventorySlots); j++) {
		if (UserList[UserIndex].Invent.Object[j].ObjIndex > 0) {
			WriteConsoleMsg(sendIndex,
					"Objeto " + vb6::CStr(j) + " " + ObjData[UserList[UserIndex].Invent.Object[j].ObjIndex].Name
							+ " Cantidad:" + vb6::CStr(UserList[UserIndex].Invent.Object[j].Amount),
					FontTypeNames_FONTTYPE_INFO);
		}
	}
}

void SendUserInvTxtFromChar(int sendIndex, std::string charName) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int j;
	std::string CharFile;
	std::string Tmp;
	int ObjInd;
	int ObjCant;

	CharFile = GetCharPath(charName);

	if (FileExist(CharFile, 0)) {
		WriteConsoleMsg(sendIndex, charName, FontTypeNames_FONTTYPE_INFO);
		WriteConsoleMsg(sendIndex, "Tiene " + GetVar(CharFile, "Inventory", "CantidadItems") + " objetos.",
				FontTypeNames_FONTTYPE_INFO);

		for (j = (1); j <= (MAX_INVENTORY_SLOTS); j++) {
			Tmp = GetVar(CharFile, "Inventory", "Obj" + vb6::CStr(j));
			ObjInd = vb6::CInt(ReadField(1, Tmp, vb6::Asc("-")));
			ObjCant = vb6::CInt(ReadField(2, Tmp, vb6::Asc("-")));
			if (ObjInd > 0) {
				WriteConsoleMsg(sendIndex,
						"Objeto " + vb6::CStr(j) + " " + ObjData[ObjInd].Name + " Cantidad:" + vb6::CStr(ObjCant),
						FontTypeNames_FONTTYPE_INFO);
			}
		}
	} else {
		WriteConsoleMsg(sendIndex, "Usuario inexistente: " + charName, FontTypeNames_FONTTYPE_INFO);
	}
}

void SendUserSkillsTxt(int sendIndex, int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */
	int j;

	WriteConsoleMsg(sendIndex, UserList[UserIndex].Name, FontTypeNames_FONTTYPE_INFO);

	for (j = (1); j <= (NUMSKILLS); j++) {
		WriteConsoleMsg(sendIndex, SkillsNames[j] + " = " + vb6::CStr(UserList[UserIndex].Stats.UserSkills[j]),
				FontTypeNames_FONTTYPE_INFO);
	}

	WriteConsoleMsg(sendIndex, "SkillLibres:" + vb6::CStr(UserList[UserIndex].Stats.SkillPts),
			FontTypeNames_FONTTYPE_INFO);
}

bool EsMascotaCiudadano(int NpcIndex, int UserIndex) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (Npclist[NpcIndex].MaestroUser > 0) {
		retval = !criminal(Npclist[NpcIndex].MaestroUser);
		if (retval) {
			WriteConsoleMsg(Npclist[NpcIndex].MaestroUser,
					"¡¡" + UserList[UserIndex].Name + " esta atacando tu mascota!!",
					FontTypeNames_FONTTYPE_INFO);
		}
	}
	return retval;
}

void NPCAtacado(int NpcIndex, int UserIndex) {
	/* '********************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 02/04/2010 */
	/* '24/01/2007 -> Pablo (ToxicWaste): Agrego para que se actualize el tag si corresponde. */
	/* '24/07/2007 -> Pablo (ToxicWaste): Guardar primero que ataca NPC y el que atacas ahora. */
	/* '06/28/2008 -> NicoNZ: Los elementales al atacarlos por su amo no se paran más al lado de él sin hacer nada. */
	/* '02/04/2010: ZaMa: Un ciuda no se vuelve mas criminal al atacar un npc no hostil. */
	/* '********************************************** */
	bool EraCriminal;

	/* 'Guardamos el usuario que ataco el npc. */
	Npclist[NpcIndex].flags.AttackedBy = UserList[UserIndex].Name;

	/* 'Npc que estabas atacando. */
	int LastNpcHit;
	LastNpcHit = UserList[UserIndex].flags.NPCAtacado;
	/* 'Guarda el NPC que estas atacando ahora. */
	UserList[UserIndex].flags.NPCAtacado = NpcIndex;

	/* 'Revisamos robo de npc. */
	/* 'Guarda el primer nick que lo ataca. */
	if (Npclist[NpcIndex].flags.AttackedFirstBy == "") {
		/* 'El que le pegabas antes ya no es tuyo */
		if (LastNpcHit != 0) {
			if (Npclist[LastNpcHit].flags.AttackedFirstBy == UserList[UserIndex].Name) {
				Npclist[LastNpcHit].flags.AttackedFirstBy = "";
			}
		}
		Npclist[NpcIndex].flags.AttackedFirstBy = UserList[UserIndex].Name;
	} else if (Npclist[NpcIndex].flags.AttackedFirstBy != UserList[UserIndex].Name) {
		/* 'Estas robando NPC */
		/* 'El que le pegabas antes ya no es tuyo */
		if (LastNpcHit != 0) {
			if (Npclist[LastNpcHit].flags.AttackedFirstBy == UserList[UserIndex].Name) {
				Npclist[LastNpcHit].flags.AttackedFirstBy = "";
			}
		}
	}

	if (Npclist[NpcIndex].MaestroUser > 0) {
		if (Npclist[NpcIndex].MaestroUser != UserIndex) {
			AllMascotasAtacanUser(UserIndex, Npclist[NpcIndex].MaestroUser);
		}
	}

	if (EsMascotaCiudadano(NpcIndex, UserIndex)) {
		VolverCriminal(UserIndex);
		Npclist[NpcIndex].Movement = TipoAI_NPCDEFENSA;
		Npclist[NpcIndex].Hostile = 1;
	} else {
		EraCriminal = criminal(UserIndex);

		/* 'Reputacion */
		if (Npclist[NpcIndex].Stats.Alineacion == 0) {
			if (Npclist[NpcIndex].NPCtype == eNPCType_GuardiaReal) {
				VolverCriminal(UserIndex);
			}

		} else if (Npclist[NpcIndex].Stats.Alineacion == 1) {
			UserList[UserIndex].Reputacion.PlebeRep = UserList[UserIndex].Reputacion.PlebeRep + vlCAZADOR / 2;
			if (UserList[UserIndex].Reputacion.PlebeRep > MAXREP) {
				UserList[UserIndex].Reputacion.PlebeRep = MAXREP;
			}
		}

		if (Npclist[NpcIndex].MaestroUser != UserIndex) {
			/* 'hacemos que el npc se defienda */
			Npclist[NpcIndex].Movement = TipoAI_NPCDEFENSA;
			Npclist[NpcIndex].Hostile = 1;
		}

		if (EraCriminal && !criminal(UserIndex)) {
			VolverCiudadano(UserIndex);
		}
	}
}
bool PuedeApunalar(int UserIndex) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int WeaponIndex;

	WeaponIndex = UserList[UserIndex].Invent.WeaponEqpObjIndex;

	if (WeaponIndex > 0) {
		if (ObjData[WeaponIndex].Apunala == 1) {
			retval = UserList[UserIndex].Stats.UserSkills[eSkill_Apunalar] >= MIN_APUNALAR
					|| UserList[UserIndex].clase == eClass_Assasin;
		}
	}

	return retval;
}

bool PuedeAcuchillar(int UserIndex) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 25/01/2010 (ZaMa) */
	/* ' */
	/* '*************************************************** */

	int WeaponIndex;

	if (UserList[UserIndex].clase == eClass_Pirat) {

		WeaponIndex = UserList[UserIndex].Invent.WeaponEqpObjIndex;
		if (WeaponIndex > 0) {
			retval = (ObjData[WeaponIndex].Acuchilla == 1);
		}
	}

	return retval;
}

void SubirSkill(int UserIndex, int Skill, bool Acerto) {
	/* '************************************************* */
	/* 'Author: Unknown */
	/* 'Last modified: 11/19/2009 */
	/* '11/19/2009 Pato - Implement the new system to train the skills. */
	/* '************************************************* */
	if (UserList[UserIndex].flags.Hambre == 0 && UserList[UserIndex].flags.Sed == 0) {
		if (UserList[UserIndex].Counters.AsignedSkills < 10) {
			if (UserList[UserIndex].flags.UltimoMensaje != 7) {
				WriteConsoleMsg(UserIndex,
						"Para poder entrenar un skill debes asignar los 10 skills iniciales.",
						FontTypeNames_FONTTYPE_INFO);
				UserList[UserIndex].flags.UltimoMensaje = 7;
			}

			return;
		}

		if (UserList[UserIndex].Stats.UserSkills[Skill] == MAXSKILLPOINTS) {
			return;
		}

		int Lvl;
		Lvl = UserList[UserIndex].Stats.ELV;

		if (Lvl > vb6::UBound(LevelSkill)) {
			Lvl = vb6::UBound(LevelSkill);
		}

		if (UserList[UserIndex].Stats.UserSkills[Skill] >= LevelSkill[Lvl].LevelValue) {
			return;
		}

		if (Acerto) {
			UserList[UserIndex].Stats.ExpSkills[Skill] = UserList[UserIndex].Stats.ExpSkills[Skill]
					+ EXP_ACIERTO_SKILL;
		} else {
			UserList[UserIndex].Stats.ExpSkills[Skill] = UserList[UserIndex].Stats.ExpSkills[Skill]
					+ EXP_FALLO_SKILL;
		}

		if (UserList[UserIndex].Stats.ExpSkills[Skill] >= UserList[UserIndex].Stats.EluSkills[Skill]) {
			UserList[UserIndex].Stats.UserSkills[Skill] = UserList[UserIndex].Stats.UserSkills[Skill] + 1;
			WriteConsoleMsg(UserIndex,
					"¡Has mejorado tu skill " + SkillsNames[Skill] + " en un punto! Ahora tienes "
							+ vb6::CStr(UserList[UserIndex].Stats.UserSkills[Skill]) + " pts.",
					FontTypeNames_FONTTYPE_INFO);

			UserList[UserIndex].Stats.Exp = UserList[UserIndex].Stats.Exp + 50;
			if (UserList[UserIndex].Stats.Exp > MAXEXP) {
				UserList[UserIndex].Stats.Exp = MAXEXP;
			}

			WriteConsoleMsg(UserIndex, "¡Has ganado 50 puntos de experiencia!", FontTypeNames_FONTTYPE_FIGHT);

			WriteUpdateExp(UserIndex);
			CheckUserLevel(UserIndex);
			CheckEluSkill(UserIndex, Skill, false);
		}
	}
}

/* '' */
/* ' Muere un usuario */
/* ' */
/* ' @param UserIndex  Indice del usuario que muere */
/* ' */

void UserDie(int UserIndex) {
	/* '************************************************ */
	/* 'Author: Uknown */
	/* 'Last Modified: 12/01/2010 (ZaMa) */
	/* '04/15/2008: NicoNZ - Ahora se resetea el counter del invi */
	/* '13/02/2009: ZaMa - Ahora se borran las mascotas cuando moris en agua. */
	/* '27/05/2009: ZaMa - El seguro de resu no se activa si estas en una arena. */
	/* '21/07/2009: Marco - Al morir se desactiva el comercio seguro. */
	/* '16/11/2009: ZaMa - Al morir perdes la criatura que te pertenecia. */
	/* '27/11/2009: Budi - Al morir envia los atributos originales. */
	/* '12/01/2010: ZaMa - Los druidas pierden la inmunidad de ser atacados cuando mueren. */
	/* '************************************************ */

	int i;
	int aN;

	int iSoundDeath;

	/* 'Sonido */
	if (UserList[UserIndex].Genero == eGenero_Mujer) {
		if (HayAgua(UserList[UserIndex].Pos.Map, UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y)) {
			iSoundDeath = e_SoundIndex_MUERTE_MUJER_AGUA;
		} else {
			iSoundDeath = e_SoundIndex_MUERTE_MUJER;
		}
	} else {
		if (HayAgua(UserList[UserIndex].Pos.Map, UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y)) {
			iSoundDeath = e_SoundIndex_MUERTE_HOMBRE_AGUA;
		} else {
			iSoundDeath = e_SoundIndex_MUERTE_HOMBRE;
		}
	}

	SonidosMapas->ReproducirSonido(SendTarget_ToPCArea, UserIndex, iSoundDeath);

	/* 'Quitar el dialogo del user muerto */
	SendData(SendTarget_ToPCArea, UserIndex,
			dakara::protocol::server::BuildRemoveCharDialog(UserList[UserIndex].Char.CharIndex));

	UserList[UserIndex].Stats.MinHp = 0;
	UserList[UserIndex].Stats.MinSta = 0;
	UserList[UserIndex].flags.AtacadoPorUser = 0;
	UserList[UserIndex].flags.Envenenado = 0;
	UserList[UserIndex].flags.Muerto = 1;

	UserList[UserIndex].Counters.Trabajando = 0;

	/* ' No se activa en arenas */
	if (TriggerZonaPelea(UserIndex, UserIndex) != eTrigger6_TRIGGER6_PERMITE) {
		UserList[UserIndex].flags.SeguroResu = true;
		/* 'Call WriteResuscitationSafeOn(UserIndex) */
		WriteMultiMessage(UserIndex, eMessages_ResuscitationSafeOn);
	} else {
		UserList[UserIndex].flags.SeguroResu = false;
		/* 'Call WriteResuscitationSafeOff(UserIndex) */
		WriteMultiMessage(UserIndex, eMessages_ResuscitationSafeOff);
	}

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

	PerdioNpc(UserIndex, false);

	/* '<<<< Atacable >>>> */
	if (UserList[UserIndex].flags.AtacablePor > 0) {
		UserList[UserIndex].flags.AtacablePor = 0;
		RefreshCharStatus(UserIndex);
	}

	/* '<<<< Paralisis >>>> */
	if (UserList[UserIndex].flags.Paralizado == 1) {
		UserList[UserIndex].flags.Paralizado = 0;
		WriteParalizeOK(UserIndex);
	}

	/* '<<< Estupidez >>> */
	if (UserList[UserIndex].flags.Estupidez == 1) {
		UserList[UserIndex].flags.Estupidez = 0;
		WriteDumbNoMore(UserIndex);
	}

	/* '<<<< Descansando >>>> */
	if (UserList[UserIndex].flags.Descansar) {
		UserList[UserIndex].flags.Descansar = false;
		WriteRestOK(UserIndex);
	}

	/* '<<<< Meditando >>>> */
	if (UserList[UserIndex].flags.Meditando) {
		UserList[UserIndex].flags.Meditando = false;
		WriteMeditateToggle(UserIndex);
	}

	/* '<<<< Invisible >>>> */
	if (UserList[UserIndex].flags.invisible == 1 || UserList[UserIndex].flags.Oculto == 1) {
		UserList[UserIndex].flags.Oculto = 0;
		UserList[UserIndex].flags.invisible = 0;
		UserList[UserIndex].Counters.TiempoOculto = 0;
		UserList[UserIndex].Counters.Invisibilidad = 0;

		/* 'Call SendData(SendTarget.ToPCArea, UserIndex, PrepareMessageSetInvisible(.Char.CharIndex, False)) */
		SetInvisible(UserIndex, UserList[UserIndex].Char.CharIndex, false);
	}

	if (TriggerZonaPelea(UserIndex, UserIndex) != eTrigger6_TRIGGER6_PERMITE) {
		/* ' << Si es newbie no pierde el inventario >> */
		if (!EsNewbie(UserIndex)) {
			TirarTodo(UserIndex);
		} else {
			TirarTodosLosItemsNoNewbies(UserIndex);
		}
	}

	/* ' DESEQUIPA TODOS LOS OBJETOS */
	/* 'desequipar armadura */
	if (UserList[UserIndex].Invent.ArmourEqpObjIndex > 0) {
		Desequipar(UserIndex, UserList[UserIndex].Invent.ArmourEqpSlot, false);
	}

	/* 'desequipar arma */
	if (UserList[UserIndex].Invent.WeaponEqpObjIndex > 0) {
		Desequipar(UserIndex, UserList[UserIndex].Invent.WeaponEqpSlot, false);
	}

	/* 'desequipar casco */
	if (UserList[UserIndex].Invent.CascoEqpObjIndex > 0) {
		Desequipar(UserIndex, UserList[UserIndex].Invent.CascoEqpSlot, false);
	}

	/* 'desequipar herramienta */
	if (UserList[UserIndex].Invent.AnilloEqpSlot > 0) {
		Desequipar(UserIndex, UserList[UserIndex].Invent.AnilloEqpSlot, false);
	}

	/* 'desequipar municiones */
	if (UserList[UserIndex].Invent.MunicionEqpObjIndex > 0) {
		Desequipar(UserIndex, UserList[UserIndex].Invent.MunicionEqpSlot, false);
	}

	/* 'desequipar escudo */
	if (UserList[UserIndex].Invent.EscudoEqpObjIndex > 0) {
		Desequipar(UserIndex, UserList[UserIndex].Invent.EscudoEqpSlot, false);
	}

	/* ' << Reseteamos los posibles FX sobre el personaje >> */
	if (UserList[UserIndex].Char.loops == INFINITE_LOOPS) {
		UserList[UserIndex].Char.FX = 0;
		UserList[UserIndex].Char.loops = 0;
	}

	/* ' << Restauramos el mimetismo */
	if (UserList[UserIndex].flags.Mimetizado == 1) {
		UserList[UserIndex].Char.body = UserList[UserIndex].CharMimetizado.body;
		UserList[UserIndex].Char.Head = UserList[UserIndex].CharMimetizado.Head;
		UserList[UserIndex].Char.CascoAnim = UserList[UserIndex].CharMimetizado.CascoAnim;
		UserList[UserIndex].Char.ShieldAnim = UserList[UserIndex].CharMimetizado.ShieldAnim;
		UserList[UserIndex].Char.WeaponAnim = UserList[UserIndex].CharMimetizado.WeaponAnim;
		UserList[UserIndex].Counters.Mimetismo = 0;
		UserList[UserIndex].flags.Mimetizado = 0;
		/* ' Puede ser atacado por npcs (cuando resucite) */
		UserList[UserIndex].flags.Ignorado = false;
	}

	/* ' << Restauramos los atributos >> */
	if (UserList[UserIndex].flags.TomoPocion == true) {
		for (i = (1); i <= (5); i++) {
			UserList[UserIndex].Stats.UserAtributos[i] = UserList[UserIndex].Stats.UserAtributosBackUP[i];
		}
	}

	/* '<< Cambiamos la apariencia del char >> */
	if (UserList[UserIndex].flags.Navegando == 0) {
		UserList[UserIndex].Char.body = iCuerpoMuerto;
		UserList[UserIndex].Char.Head = iCabezaMuerto;
		UserList[UserIndex].Char.ShieldAnim = NingunEscudo;
		UserList[UserIndex].Char.WeaponAnim = NingunArma;
		UserList[UserIndex].Char.CascoAnim = NingunCasco;
	} else {
		UserList[UserIndex].Char.body = iFragataFantasmal;
	}

	for (i = (1); i <= (MAXMASCOTAS); i++) {
		if (UserList[UserIndex].MascotasIndex[i] > 0) {
			MuereNpc(UserList[UserIndex].MascotasIndex[i], 0);
			/* ' Si estan en agua o zona segura */
		} else {
			UserList[UserIndex].MascotasType[i] = 0;
		}
	}

	UserList[UserIndex].NroMascotas = 0;

	/* '<< Actualizamos clientes >> */
	ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
			UserList[UserIndex].Char.heading, NingunArma, NingunEscudo, NingunCasco);
	WriteUpdateUserStats(UserIndex);
	WriteUpdateStrenghtAndDexterity(UserIndex);
	/* '<<Castigos por party>> */
	if (UserList[UserIndex].PartyIndex > 0) {
		ObtenerExito(UserIndex, UserList[UserIndex].Stats.ELV * -10 * CantMiembros(UserIndex),
				UserList[UserIndex].Pos.Map, UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y);
	}

	/* '<<Cerramos comercio seguro>> */
	LimpiarComercioSeguro(UserIndex);

	/* ' Hay que teletransportar? */
	int mapa;
	mapa = UserList[UserIndex].Pos.Map;
	int MapaTelep;
	MapaTelep = MapInfo[mapa].OnDeathGoTo.Map;

	if (MapaTelep != 0) {
		WriteConsoleMsg(UserIndex, "¡¡¡Tu estado no te permite permanecer en el mapa!!!",
				FontTypeNames_FONTTYPE_INFOBOLD);
		WarpUserChar(UserIndex, MapaTelep, MapInfo[mapa].OnDeathGoTo.X, MapInfo[mapa].OnDeathGoTo.Y, true,
				true);
	}
}

void ContarMuerte(int Muerto, int Atacante) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 13/07/2010 */
	/* '13/07/2010: ZaMa - Los matados en estado atacable ya no suman frag. */
	/* '*************************************************** */

	if (EsNewbie(Muerto)) {
		return;
	}

	if (TriggerZonaPelea(Muerto, Atacante) == eTrigger6_TRIGGER6_PERMITE) {
		return;
	}

	if (criminal(Muerto)) {
		if (UserList[Atacante].flags.LastCrimMatado != UserList[Muerto].Name) {
			UserList[Atacante].flags.LastCrimMatado = UserList[Muerto].Name;
			if (UserList[Atacante].Faccion.CriminalesMatados < MAXUSERMATADOS) {
				UserList[Atacante].Faccion.CriminalesMatados = UserList[Atacante].Faccion.CriminalesMatados
						+ 1;
			}
		}

		if (UserList[Atacante].Faccion.RecibioExpInicialCaos == 1
				&& UserList[Muerto].Faccion.FuerzasCaos == 1) {
			/* 'jaja que trucho */
			UserList[Atacante].Faccion.Reenlistadas = 200;

			/* 'con esto evitamos que se vuelva a reenlistar */
		}
	} else {
		if (UserList[Atacante].flags.LastCiudMatado != UserList[Muerto].Name) {
			UserList[Atacante].flags.LastCiudMatado = UserList[Muerto].Name;
			if (UserList[Atacante].Faccion.CiudadanosMatados < MAXUSERMATADOS) {
				UserList[Atacante].Faccion.CiudadanosMatados = UserList[Atacante].Faccion.CiudadanosMatados
						+ 1;
			}
		}
	}

	if (UserList[Atacante].Stats.UsuariosMatados < MAXUSERMATADOS) {
		UserList[Atacante].Stats.UsuariosMatados = UserList[Atacante].Stats.UsuariosMatados + 1;
	}
}

void Tilelibre(struct WorldPos & Pos, struct WorldPos & nPos, struct Obj & Obj, bool PuedeAgua,
		bool PuedeTierra) {
	/* '************************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modify Date: 18/09/2010 */
	/* '23/01/2007 -> Pablo (ToxicWaste): El agua es ahora un TileLibre agregando las condiciones necesarias. */
	/* '18/09/2010: ZaMa - Aplico optimizacion de busqueda de tile libre en forma de rombo. */
	/* '************************************************************** */

	bool Found = false;
	int LoopC;
	int tX;
	int tY;

	nPos = Pos;
	tX = Pos.X;
	tY = Pos.Y;

	LoopC = 1;

	/* ' La primera posicion es valida? */
	if (LegalPos(Pos.Map, nPos.X, nPos.Y, PuedeAgua, PuedeTierra, true)) {

		if (!HayObjeto(Pos.Map, nPos.X, nPos.Y, Obj.ObjIndex, Obj.Amount)) {
			Found = true;
		}

	}

	/* ' Busca en las demas posiciones, en forma de "rombo" */
	if (!Found) {
		while ((!Found) && LoopC <= 16) {
			if (RhombLegalTilePos(Pos, tX, tY, LoopC, Obj.ObjIndex, Obj.Amount, PuedeAgua, PuedeTierra)) {
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

void WarpUserChar(int UserIndex, int Map, int X, int Y, bool FX, bool Teletransported) {
	/* '************************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modify Date: 11/23/2010 */
	/* '15/07/2009 - ZaMa: Automatic toogle navigate after warping to water. */
	/* '13/11/2009 - ZaMa: Now it's activated the timer which determines if the npc can atacak the user. */
	/* '16/09/2010 - ZaMa: No se pierde la visibilidad al cambiar de mapa al estar navegando invisible. */
	/* '11/23/2010 - C4b3z0n: Ahora si no se permite Invi o Ocultar en el mapa al que cambias, te lo saca */
	/* '************************************************************** */
	int OldMap;

	/* 'Quitar el dialogo */
	SendData(SendTarget_ToPCArea, UserIndex,
			dakara::protocol::server::BuildRemoveCharDialog(UserList[UserIndex].Char.CharIndex));

	OldMap = UserList[UserIndex].Pos.Map;

	EraseUserChar(UserIndex, UserList[UserIndex].flags.AdminInvisible == 1);

	if (OldMap != Map) {
		WriteChangeMap(UserIndex, Map, MapInfo[UserList[UserIndex].Pos.Map].MapVersion);

		/* 'El chequeo de invi/ocultar solo afecta a Usuarios (C4b3z0n) */
		if (UserTienePrivilegio(UserIndex, PlayerType_User)) {
			/* 'Para enviar el mensaje de invi y hacer visible (C4b3z0n) */
			bool AhoraVisible = false;
			bool WasInvi = false;
			/* 'Chequeo de flags de mapa por invisibilidad (C4b3z0n) */
			if (MapInfo[Map].InviSinEfecto > 0 && UserList[UserIndex].flags.invisible == 1) {
				UserList[UserIndex].flags.invisible = 0;
				UserList[UserIndex].Counters.Invisibilidad = 0;
				AhoraVisible = true;
				/* 'si era invi, para el string */
				WasInvi = true;
			}
			/* 'Chequeo de flags de mapa por ocultar (C4b3z0n) */
			if (MapInfo[Map].OcultarSinEfecto > 0 && UserList[UserIndex].flags.Oculto == 1) {
				AhoraVisible = true;
				UserList[UserIndex].flags.Oculto = 0;
				UserList[UserIndex].Counters.TiempoOculto = 0;
			}

			/* 'Si no era visible y ahora es, le avisa. (C4b3z0n) */
			if (AhoraVisible) {
				SetInvisible(UserIndex, UserList[UserIndex].Char.CharIndex, false);
				/* 'era invi */
				if (WasInvi) {
					WriteConsoleMsg(UserIndex,
							"Has vuelto a ser visible ya que no esta permitida la invisibilidad en este mapa.",
							FontTypeNames_FONTTYPE_INFO);
					/* 'estaba oculto */
				} else {
					WriteConsoleMsg(UserIndex,
							"Has vuelto a ser visible ya que no esta permitido ocultarse en este mapa.",
							FontTypeNames_FONTTYPE_INFO);
				}
			}
		}

		WritePlayMidi(UserIndex, MapInfo[Map].Music);

		/* 'Update new Map Users */
		MapInfo[Map].NumUsers = MapInfo[Map].NumUsers + 1;

		/* 'Update old Map Users */
		MapInfo[OldMap].NumUsers = MapInfo[OldMap].NumUsers - 1;
		if (MapInfo[OldMap].NumUsers < 0) {
			MapInfo[OldMap].NumUsers = 0;
		}

		/* 'Si el mapa al que entro NO ES superficial AND en el que estaba TAMPOCO ES superficial, ENTONCES */
		bool nextMap;
		bool previousMap;

		nextMap = vb6::IIf(distanceToCities[Map].distanceToCity[UserList[UserIndex].Hogar] >= 0, true, false);
		previousMap = vb6::IIf(
				distanceToCities[UserList[UserIndex].Pos.Map].distanceToCity[UserList[UserIndex].Hogar] >= 0,
				true, false);

		/* '138 => 139 (Ambos superficiales, no tiene que pasar nada) */
		if (previousMap && nextMap) {
			/* 'NO PASA NADA PORQUE NO ENTRO A UN DUNGEON. */
			/* '139 => 140 (139 es superficial, 140 no. Por lo tanto 139 es el ultimo mapa superficial) */
		} else if (previousMap && !nextMap) {
			UserList[UserIndex].flags.lastMap = UserList[UserIndex].Pos.Map;
			/* '140 => 139 (140 es no es superficial, 139 si. Por lo tanto, el último mapa es 0 ya que no esta en un dungeon) */
		} else if (!previousMap && nextMap) {
			UserList[UserIndex].flags.lastMap = 0;
			/* '140 => 141 (Ninguno es superficial, el ultimo mapa es el mismo de antes) */
		} else if (!previousMap && !nextMap) {
			// FIXME
			// UserList[UserIndex].flags.lastMap = UserList[UserIndex].flags.lastMap;
		}

		WriteRemoveAllDialogs(UserIndex);
	}

	UserList[UserIndex].Pos.X = X;
	UserList[UserIndex].Pos.Y = Y;
	UserList[UserIndex].Pos.Map = Map;

	if (!MakeUserChar(true, Map, UserIndex, Map, X, Y)) {
		return;
	}

	WriteUserCharIndexInServer(UserIndex);

	DoTileEvents(UserIndex, Map, X, Y);

	/* 'Force a flush, so user index is in there before it's destroyed for teleporting */
	FlushBuffer(UserIndex);

	/* 'Seguis invisible al pasar de mapa */
	if ((UserList[UserIndex].flags.invisible == 1 || UserList[UserIndex].flags.Oculto == 1)
			&& (UserList[UserIndex].flags.AdminInvisible != 1)) {

		/* ' No si estas navegando */
		if (UserList[UserIndex].flags.Navegando == 0) {
			SetInvisible(UserIndex, UserList[UserIndex].Char.CharIndex, true);
		}
	}

	if (Teletransported) {
		if (UserList[UserIndex].flags.Traveling == 1) {
			UserList[UserIndex].flags.Traveling = 0;
			UserList[UserIndex].Counters.goHome = 0;
			WriteMultiMessage(UserIndex, eMessages_CancelHome);
		}
	}

	/* 'FX */
	if (FX && UserList[UserIndex].flags.AdminInvisible == 0) {
		SendData(SendTarget_ToPCArea, UserIndex, dakara::protocol::server::BuildPlayWave(SND_WARP, X, Y));
		SendData(SendTarget_ToPCArea, UserIndex,
				dakara::protocol::server::BuildCreateFX(UserList[UserIndex].Char.CharIndex, FXIDs_FXWARP, 0));
	}

	if (UserList[UserIndex].NroMascotas) {
		WarpMascotas(UserIndex);
	}

	/* ' No puede ser atacado cuando cambia de mapa, por cierto tiempo */
	IntervaloPermiteSerAtacado(UserIndex, true);

	/* ' Perdes el npc al cambiar de mapa */
	PerdioNpc(UserIndex, false);

	/* ' Automatic toogle navigate */
	if (!UserTienePrivilegio(UserIndex, PlayerType_User)) {
		if (HayAgua(UserList[UserIndex].Pos.Map, UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y)) {
			if (UserList[UserIndex].flags.Navegando == 0) {
				UserList[UserIndex].flags.Navegando = 1;

				/* 'Tell the client that we are navigating. */
				WriteNavigateToggle(UserIndex);
			}
		} else {
			if (UserList[UserIndex].flags.Navegando == 1) {
				UserList[UserIndex].flags.Navegando = 0;

				/* 'Tell the client that we are navigating. */
				WriteNavigateToggle(UserIndex);
			}
		}
	}

}

void WarpMascotas(int UserIndex) {
	/* '************************************************ */
	/* 'Author: Uknown */
	/* 'Last Modified: 26/10/2010 */
	/* '13/02/2009: ZaMa - Arreglado respawn de mascotas al cambiar de mapa. */
	/* '13/02/2009: ZaMa - Las mascotas no regeneran su vida al cambiar de mapa (Solo entre mapas inseguros). */
	/* '11/05/2009: ZaMa - Chequeo si la mascota pueden spwnear para asiganrle los stats. */
	/* '26/10/2010: ZaMa - Ahora las mascotas rapswnean de forma aleatoria. */
	/* '************************************************ */
	int i;
	int petType;
	bool PetRespawn = false;
	int PetTiempoDeVida;
	int NroPets;
	int InvocadosMatados = 0;
	bool canWarp;
	int index;
	int iMinHP = 0;

	NroPets = UserList[UserIndex].NroMascotas;
	canWarp = (MapInfo[UserList[UserIndex].Pos.Map].Pk == true);

	for (i = (1); i <= (MAXMASCOTAS); i++) {
		index = UserList[UserIndex].MascotasIndex[i];

		if (index > 0) {
			/* ' si la mascota tiene tiempo de vida > 0 significa q fue invocada => we kill it */
			if (Npclist[index].Contadores.TiempoExistencia > 0) {
				QuitarNPC(index);
				UserList[UserIndex].MascotasIndex[i] = 0;
				InvocadosMatados = InvocadosMatados + 1;
				NroPets = NroPets - 1;

				petType = 0;
			} else {
				/* 'Store data and remove NPC to recreate it after warp */
				/* 'PetRespawn = Npclist(index).flags.Respawn = 0 */
				petType = UserList[UserIndex].MascotasType[i];
				/* 'PetTiempoDeVida = Npclist(index).Contadores.TiempoExistencia */

				/* ' Guardamos el hp, para restaurarlo uando se cree el npc */
				iMinHP = Npclist[index].Stats.MinHp;

				QuitarNPC(index);

				/* ' Restauramos el valor de la variable */
				UserList[UserIndex].MascotasType[i] = petType;

			}
		} else if (UserList[UserIndex].MascotasType[i] > 0) {
			/* 'Store data and remove NPC to recreate it after warp */
			PetRespawn = true;
			petType = UserList[UserIndex].MascotasType[i];
			PetTiempoDeVida = 0;
		} else {
			petType = 0;
		}

		if (petType > 0 && canWarp) {

			struct WorldPos SpawnPos;

			SpawnPos.Map = UserList[UserIndex].Pos.Map;
			SpawnPos.X = UserList[UserIndex].Pos.X + RandomNumber(-3, 3);
			SpawnPos.Y = UserList[UserIndex].Pos.Y + RandomNumber(-3, 3);

			index = SpawnNpc(petType, SpawnPos, false, PetRespawn);

			/* 'Controlamos que se sumoneo OK - should never happen. Continue to allow removal of other pets if not alone */
			/* ' Exception: Pets don't spawn in water if they can't swim */
			if (index == 0) {
				WriteConsoleMsg(UserIndex, "Tus mascotas no pueden transitar este mapa.",
						FontTypeNames_FONTTYPE_INFO);
			} else {
				UserList[UserIndex].MascotasIndex[i] = index;

				/* ' Nos aseguramos de que conserve el hp, si estaba danado */
				Npclist[index].Stats.MinHp = vb6::IIf(iMinHP == 0, Npclist[index].Stats.MinHp, iMinHP);

				Npclist[index].MaestroUser = UserIndex;
				Npclist[index].Contadores.TiempoExistencia = PetTiempoDeVida;
				FollowAmo(index);
			}
		}
	}

	if (InvocadosMatados > 0) {
		WriteConsoleMsg(UserIndex, "Pierdes el control de tus mascotas invocadas.",
				FontTypeNames_FONTTYPE_INFO);
	}

	if (!canWarp) {
		WriteConsoleMsg(UserIndex, "No se permiten mascotas en zona segura. Éstas te esperarán afuera.",
				FontTypeNames_FONTTYPE_INFO);
	}

	UserList[UserIndex].NroMascotas = NroPets;
}

void WarpMascota(int UserIndex, int PetIndex) {
	/* '************************************************ */
	/* 'Author: ZaMa */
	/* 'Last Modified: 18/11/2009 */
	/* 'Warps a pet without changing its stats */
	/* '************************************************ */
	int petType;
	int NpcIndex;
	int iMinHP;
	struct WorldPos TargetPos;

	TargetPos.Map = UserList[UserIndex].flags.TargetMap;
	TargetPos.X = UserList[UserIndex].flags.TargetX;
	TargetPos.Y = UserList[UserIndex].flags.TargetY;

	NpcIndex = UserList[UserIndex].MascotasIndex[PetIndex];

	/* 'Store data and remove NPC to recreate it after warp */
	petType = UserList[UserIndex].MascotasType[PetIndex];

	/* ' Guardamos el hp, para restaurarlo cuando se cree el npc */
	iMinHP = Npclist[NpcIndex].Stats.MinHp;

	QuitarNPC(NpcIndex);

	/* ' Restauramos el valor de la variable */
	UserList[UserIndex].MascotasType[PetIndex] = petType;
	UserList[UserIndex].NroMascotas = UserList[UserIndex].NroMascotas + 1;
	NpcIndex = SpawnNpc(petType, TargetPos, false, false);

	/* 'Controlamos que se sumoneo OK - should never happen. Continue to allow removal of other pets if not alone */
	/* ' Exception: Pets don't spawn in water if they can't swim */
	if (NpcIndex == 0) {
		WriteConsoleMsg(UserIndex,
				"Tu mascota no pueden transitar este sector del mapa, intenta invocarla en otra parte.",
				FontTypeNames_FONTTYPE_INFO);
	} else {
		UserList[UserIndex].MascotasIndex[PetIndex] = NpcIndex;

		/* ' Nos aseguramos de que conserve el hp, si estaba danado */
		Npclist[NpcIndex].Stats.MinHp = vb6::IIf(iMinHP == 0, Npclist[NpcIndex].Stats.MinHp, iMinHP);

		Npclist[NpcIndex].MaestroUser = UserIndex;
		Npclist[NpcIndex].Movement = TipoAI_SigueAmo;
		Npclist[NpcIndex].Target = 0;
		Npclist[NpcIndex].TargetNPC = 0;

		FollowAmo(NpcIndex);
	}
}

/* '' */
/* ' Se inicia la salida de un usuario. */
/* ' */
/* ' @param    UserIndex   El index del usuario que va a salir */

void CerrarUserIndexIniciar(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 16/09/2010 */
	/* '16/09/2010 - ZaMa: Cuando se va el invi estando navegando, no se saca el invi (ya esta visible). */
	/* '*************************************************** */
	bool isNotVisible = false;
	bool HiddenPirat = false;

	if (UserList[UserIndex].flags.UserLogged) {
		if (UserList[UserIndex].flags.CentinelaIndex != 0) {
			CentinelaUserLogout(UserList[UserIndex].flags.CentinelaIndex);
		}

		/* 'exit secure commerce */
		int tUser = UserList[UserIndex].ComUsu.DestUsu;
		if (tUser > 0) {
			if (UserList[tUser].flags.UserLogged) {
				if (UserList[tUser].ComUsu.DestUsu == UserIndex) {
					if (UserIndexSocketValido(tUser)) {
						WriteConsoleMsg(tUser, "Comercio cancelado por el otro usuario.",
								FontTypeNames_FONTTYPE_TALK);
					}
					FinComerciarUsu(tUser);
				}
			}

			if (UserIndexSocketValido(UserIndex)) {
				WriteConsoleMsg(UserIndex, "Comercio cancelado.", FontTypeNames_FONTTYPE_TALK);
			}
			FinComerciarUsu(UserIndex);
		}

		if (!UserList[UserIndex].Counters.Saliendo) {
			UserList[UserIndex].Counters.Saliendo = true;
			UserList[UserIndex].Counters.Salir = vb6::IIf(
					UserTienePrivilegio(UserIndex, PlayerType_User)
							&& MapInfo[UserList[UserIndex].Pos.Map].Pk, IntervaloCerrarConexion, 0);

			isNotVisible = (UserList[UserIndex].flags.Oculto || UserList[UserIndex].flags.invisible);
			if (isNotVisible) {
				UserList[UserIndex].flags.invisible = 0;

				if (UserList[UserIndex].flags.Oculto) {
					if (UserList[UserIndex].flags.Navegando == 1) {
						if (UserList[UserIndex].clase == eClass_Pirat) {
							/* ' Pierde la apariencia de fragata fantasmal */
							ToggleBoatBody(UserIndex);
							if (UserIndexSocketValido(UserIndex)) {
								WriteConsoleMsg(UserIndex, "¡Has recuperado tu apariencia normal!",
										FontTypeNames_FONTTYPE_INFO);
							}
							ChangeUserChar(UserIndex, UserList[UserIndex].Char.body,
									UserList[UserIndex].Char.Head, UserList[UserIndex].Char.heading,
									NingunArma, NingunEscudo, NingunCasco);
							HiddenPirat = true;
						}
					}
				}

				UserList[UserIndex].flags.Oculto = 0;

				/* ' Para no repetir mensajes */
				if (!HiddenPirat) {
					if (UserIndexSocketValido(UserIndex)) {
						WriteConsoleMsg(UserIndex, "Has vuelto a ser visible.", FontTypeNames_FONTTYPE_INFO);
					}
				}

				/* ' Si esta navegando ya esta visible */
				if (UserList[UserIndex].flags.Navegando == 0) {
					SetInvisible(UserIndex, UserList[UserIndex].Char.CharIndex, false);
				}
			}

			if (UserList[UserIndex].flags.Traveling == 1) {
				if (UserIndexSocketValido(UserIndex)) {
					WriteMultiMessage(UserIndex, eMessages_CancelHome);
				}
				UserList[UserIndex].flags.Traveling = 0;
				UserList[UserIndex].Counters.goHome = 0;
			}

			WriteConsoleMsg(UserIndex,
					"Cerrando...Se cerrará el juego en " + vb6::CStr(UserList[UserIndex].Counters.Salir)
							+ " segundos...", FontTypeNames_FONTTYPE_INFO);
		}
	}
}

/* '' */
/* ' Cancels the exit of a user. If it's disconnected it's reset. */
/* ' */
/* ' @param    UserIndex   The index of the user whose exit is being reset. */

void CancelExit(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 04/02/08 */
	/* ' */
	/* '*************************************************** */
	if (UserList[UserIndex].Counters.Saliendo) {
		/* ' Is the user still connected? */
		if (UserIndexSocketValido(UserIndex)) {
			UserList[UserIndex].Counters.Saliendo = false;
			UserList[UserIndex].Counters.Salir = 0;
			WriteConsoleMsg(UserIndex, "/salir cancelado.", FontTypeNames_FONTTYPE_WARNING);
		} else {
			/* 'Simply reset */
			UserList[UserIndex].Counters.Salir = vb6::IIf(
					UserTienePrivilegio(UserIndex, PlayerType_User)
							&& MapInfo[UserList[UserIndex].Pos.Map].Pk, IntervaloCerrarConexion, 0);
		}
	}
}

/* 'CambiarNick: Cambia el Nick de un slot. */
/* ' */
/* 'UserIndex: Quien ejecutó la orden */
/* 'UserIndexDestino: SLot del usuario destino, a quien cambiarle el nick */
/* 'NuevoNick: Nuevo nick de UserIndexDestino */
void CambiarNick(int UserIndex, int UserIndexDestino, std::string NuevoNick) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */
	(void)UserIndex;

	std::string ViejoNick;
	std::string ViejoCharBackup;

	if (UserList[UserIndexDestino].flags.UserLogged == false) {
		return;
	}

	ViejoNick = UserList[UserIndexDestino].Name;

	if (FileExist(GetCharPath(ViejoNick), 0)) {
		/* 'hace un backup del char */
		ViejoCharBackup = GetCharPath(ViejoNick) + ".old-" + vb6::dateToString(vb6::Now());
		vb6::Name(GetCharPath(ViejoNick), ViejoCharBackup);
	}

	UserList[UserIndexDestino].Name = NuevoNick;
	SaveUser(UserIndexDestino, GetCharPath(NuevoNick));
}

void SendUserStatsTxtOFF(int sendIndex, std::string Nombre) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (FileExist(GetCharPath(Nombre), 0) == false) {
		WriteConsoleMsg(sendIndex, "Pj Inexistente", FontTypeNames_FONTTYPE_INFO);
	} else {
		WriteConsoleMsg(sendIndex, "Estadísticas de: " + Nombre, FontTypeNames_FONTTYPE_INFO);
		WriteConsoleMsg(sendIndex,
				"Nivel: " + GetVar(GetCharPath(Nombre), "stats", "elv") + "  EXP: "
						+ GetVar(GetCharPath(Nombre), "stats", "Exp") + "/"
						+ GetVar(GetCharPath(Nombre), "stats", "elu"), FontTypeNames_FONTTYPE_INFO);
		WriteConsoleMsg(sendIndex,
				"Energía: " + GetVar(GetCharPath(Nombre), "stats", "minsta") + "/"
						+ GetVar(GetCharPath(Nombre), "stats", "maxSta"), FontTypeNames_FONTTYPE_INFO);
		WriteConsoleMsg(sendIndex,
				"Salud: " + GetVar(GetCharPath(Nombre), "stats", "MinHP") + "/"
						+ GetVar(GetCharPath(Nombre), "Stats", "MaxHP") + "  Maná: "
						+ GetVar(GetCharPath(Nombre), "Stats", "MinMAN") + "/"
						+ GetVar(GetCharPath(Nombre), "Stats", "MaxMAN"), FontTypeNames_FONTTYPE_INFO);

		WriteConsoleMsg(sendIndex,
				"Menor Golpe/Mayor Golpe: " + GetVar(GetCharPath(Nombre), "stats", "MaxHIT"),
				FontTypeNames_FONTTYPE_INFO);

		WriteConsoleMsg(sendIndex, "Oro: " + GetVar(GetCharPath(Nombre), "stats", "GLD"),
				FontTypeNames_FONTTYPE_INFO);

		/* # IF ConUpTime THEN */
		int TempSecs;
		// std::string TempStr;
		TempSecs = vb6::CInt(GetVar(GetCharPath(Nombre), "INIT", "UpTime"));
		// TempStr = (TempSecs/86400) + " Días, " + ((TempSecsMod86400)/3600) + " Horas, " + ((TempSecsMod86400)Mod3600)/60 + " Minutos, " + (((TempSecsMod86400)Mod3600)Mod60) + " Segundos.";
		WriteConsoleMsg(sendIndex, "Tiempo Logeado: " + vb6::CStr(TempSecs), FontTypeNames_FONTTYPE_INFO);
		/* # END IF */

		WriteConsoleMsg(sendIndex,
				"Dados: " + GetVar(GetCharPath(Nombre), "ATRIBUTOS", "AT1") + ", "
						+ GetVar(GetCharPath(Nombre), "ATRIBUTOS", "AT2") + ", "
						+ GetVar(GetCharPath(Nombre), "ATRIBUTOS", "AT3") + ", "
						+ GetVar(GetCharPath(Nombre), "ATRIBUTOS", "AT4") + ", "
						+ GetVar(GetCharPath(Nombre), "ATRIBUTOS", "AT5"),
				FontTypeNames_FONTTYPE_INFO);
	}
}

void SendUserOROTxtFromChar(int sendIndex, std::string charName) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	std::string CharFile;

	CharFile = GetCharPath(charName);

	if (FileExist(CharFile, 0)) {
		WriteConsoleMsg(sendIndex, charName, FontTypeNames_FONTTYPE_INFO);
		WriteConsoleMsg(sendIndex, "Tiene " + GetVar(CharFile, "STATS", "BANCO") + " en el banco.",
				FontTypeNames_FONTTYPE_INFO);
	} else {
		WriteConsoleMsg(sendIndex, "Usuario inexistente: " + charName, FontTypeNames_FONTTYPE_INFO);
	}
}

void VolverCriminal(int UserIndex) {
	/* '************************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modify Date: 21/02/2010 */
	/* 'Nacho: Actualiza el tag al cliente */
	/* '21/02/2010: ZaMa - Ahora deja de ser atacable si se hace criminal. */
	/* '************************************************************** */
	if (MapData[UserList[UserIndex].Pos.Map][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].trigger
			== eTrigger_ZONAPELEA) {
		return;
	}

	if (UserTieneAlgunPrivilegios (UserIndex, PlayerType_User, PlayerType_Consejero)) {
		UserList[UserIndex].Reputacion.BurguesRep = 0;
		UserList[UserIndex].Reputacion.NobleRep = 0;
		UserList[UserIndex].Reputacion.PlebeRep = 0;
		UserList[UserIndex].Reputacion.BandidoRep = UserList[UserIndex].Reputacion.BandidoRep + vlASALTO;
		if (UserList[UserIndex].Reputacion.BandidoRep > MAXREP) {
			UserList[UserIndex].Reputacion.BandidoRep = MAXREP;
		}
		if (UserList[UserIndex].Faccion.ArmadaReal == 1) {
			ExpulsarFaccionReal(UserIndex);
		}

		if (UserList[UserIndex].flags.AtacablePor > 0) {
			UserList[UserIndex].flags.AtacablePor = 0;
		}

	}

	RefreshCharStatus(UserIndex);
}

void VolverCiudadano(int UserIndex) {
	/* '************************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modify Date: 21/06/2006 */
	/* 'Nacho: Actualiza el tag al cliente. */
	/* '************************************************************** */
	if (MapData[UserList[UserIndex].Pos.Map][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].trigger
			== 6) {
		return;
	}

	UserList[UserIndex].Reputacion.LadronesRep = 0;
	UserList[UserIndex].Reputacion.BandidoRep = 0;
	UserList[UserIndex].Reputacion.AsesinoRep = 0;
	UserList[UserIndex].Reputacion.PlebeRep = UserList[UserIndex].Reputacion.PlebeRep + vlASALTO;
	if (UserList[UserIndex].Reputacion.PlebeRep > MAXREP) {
		UserList[UserIndex].Reputacion.PlebeRep = MAXREP;
	}

	RefreshCharStatus(UserIndex);
}

/* '' */
/* 'Checks if a given body index is a boat or not. */
/* ' */
/* '@param body    The body index to bechecked. */
/* '@return    True if the body is a boat, false otherwise. */

bool BodyIsBoat(int body) {
	bool retval = false;
	/* '************************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modify Date: 10/07/2008 */
	/* 'Checks if a given body index is a boat */
	/* '************************************************************** */
	/* 'TODO : This should be checked somehow else. This is nasty.... */
	if (body == iFragataReal || body == iFragataCaos || body == iBarcaPk || body == iGaleraPk
			|| body == iGaleonPk || body == iBarcaCiuda || body == iGaleraCiuda || body == iGaleonCiuda
			|| body == iFragataFantasmal) {
		retval = true;
	}
	return retval;
}

void SetInvisible(int UserIndex, int userCharIndex, bool invisible) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	std::string sndNick;

	SendData(SendTarget_ToUsersAndRmsAndCounselorsAreaButGMs, UserIndex,
			dakara::protocol::server::BuildSetInvisible(userCharIndex, invisible));

	sndNick = UserList[UserIndex].Name;

	if (invisible) {
		sndNick = sndNick + " " + TAG_USER_INVISIBLE;
	} else {
		if (UserList[UserIndex].GuildIndex > 0) {
			sndNick = sndNick + " <" + GuildName(UserList[UserIndex].GuildIndex) + ">";
		}
	}

	SendData(SendTarget_ToGMsAreaButRmsOrCounselors, UserIndex,
			dakara::protocol::server::BuildCharacterChangeNick(userCharIndex, sndNick));
}

void SetConsulatMode(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Torres Patricio (Pato) */
	/* 'Last Modification: 05/06/10 */
	/* ' */
	/* '*************************************************** */

	std::string sndNick;

	sndNick = UserList[UserIndex].Name;

	if (UserList[UserIndex].flags.EnConsulta) {
		sndNick = sndNick + " " + TAG_CONSULT_MODE;
	} else {
		if (UserList[UserIndex].GuildIndex > 0) {
			sndNick = sndNick + " <" + GuildName(UserList[UserIndex].GuildIndex) + ">";
		}
	}

	SendData(SendTarget_ToPCArea, UserIndex,
			dakara::protocol::server::BuildCharacterChangeNick(UserList[UserIndex].Char.CharIndex, sndNick));
}

bool IsArena(int UserIndex) {
	bool retval;
	/* '************************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modify Date: 10/11/2009 */
	/* 'Returns true if the user is in an Arena */
	/* '************************************************************** */
	retval = (TriggerZonaPelea(UserIndex, UserIndex) == eTrigger6_TRIGGER6_PERMITE);
	return retval;
}

void PerdioNpc(int UserIndex, bool CheckPets) {
	/* '************************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modify Date: 11/07/2010 (ZaMa) */
	/* 'The user loses his owned npc */
	/* '18/01/2010: ZaMa - Las mascotas dejan de atacar al npc que se perdió. */
	/* '11/07/2010: ZaMa - Coloco el indice correcto de las mascotas y ahora siguen al amo si existen. */
	/* '13/07/2010: ZaMa - Ahora solo dejan de atacar las mascotas si estan atacando al npc que pierde su amo. */
	/* '************************************************************** */

	int PetCounter;
	int PetIndex;
	int NpcIndex;

	NpcIndex = UserList[UserIndex].flags.OwnedNpc;
	if (NpcIndex > 0) {

		if (CheckPets) {
			/* ' Dejan de atacar las mascotas */
			if (UserList[UserIndex].NroMascotas > 0) {
				for (PetCounter = (1); PetCounter <= (MAXMASCOTAS); PetCounter++) {

					PetIndex = UserList[UserIndex].MascotasIndex[PetCounter];

					if (PetIndex > 0) {
						/* ' Si esta atacando al npc deja de hacerlo */
						if (Npclist[PetIndex].TargetNPC == NpcIndex) {
							FollowAmo(PetIndex);
						}
					}

				}
			}
		}

		/* ' Reset flags */
		Npclist[NpcIndex].Owner = 0;
		UserList[UserIndex].flags.OwnedNpc = 0;

	}
}

void ApropioNpc(int UserIndex, int NpcIndex) {
	/* '************************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modify Date: 27/07/2010 (zaMa) */
	/* 'The user owns a new npc */
	/* '18/01/2010: ZaMa - El sistema no aplica a zonas seguras. */
	/* '19/04/2010: ZaMa - Ahora los admins no se pueden apropiar de npcs. */
	/* '27/07/2010: ZaMa - El sistema no aplica a mapas seguros. */
	/* '************************************************************** */

	/* ' Los admins no se pueden apropiar de npcs */
	if (EsGm(UserIndex)) {
		return;
	}

	int mapa;
	mapa = UserList[UserIndex].Pos.Map;

	/* ' No aplica a triggers seguras */
	if (MapData[mapa][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].trigger == eTrigger_ZONASEGURA) {
		return;
	}

	/* ' No se aplica a mapas seguros */
	if (MapInfo[mapa].Pk == false) {
		return;
	}

	/* ' No aplica a algunos mapas que permiten el robo de npcs */
	if (MapInfo[mapa].RoboNpcsPermitido == 1) {
		return;
	}

	/* ' Pierde el npc anterior */
	if (UserList[UserIndex].flags.OwnedNpc > 0) {
		Npclist[UserList[UserIndex].flags.OwnedNpc].Owner = 0;
	}

	/* ' Si tenia otro dueno, lo perdio aca */
	Npclist[NpcIndex].Owner = UserIndex;
	UserList[UserIndex].flags.OwnedNpc = NpcIndex;

	/* ' Inicializo o actualizo el timer de pertenencia */
	IntervaloPerdioNpc(UserIndex, true);
}

std::string GetDireccion(int UserIndex, int OtherUserIndex) {
	std::string retval;
	/* '************************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modify Date: 17/11/2009 */
	/* 'Devuelve la direccion hacia donde esta el usuario */
	/* '************************************************************** */
	int X;
	int Y;

	X = UserList[UserIndex].Pos.X - UserList[OtherUserIndex].Pos.X;
	Y = UserList[UserIndex].Pos.Y - UserList[OtherUserIndex].Pos.Y;

	if (X == 0 && Y > 0) {
		retval = "Sur";
	} else if (X == 0 && Y < 0) {
		retval = "Norte";
	} else if (X > 0 && Y == 0) {
		retval = "Este";
	} else if (X < 0 && Y == 0) {
		retval = "Oeste";
	} else if (X > 0 && Y < 0) {
		retval = "NorEste";
	} else if (X < 0 && Y < 0) {
		retval = "NorOeste";
	} else if (X > 0 && Y > 0) {
		retval = "SurEste";
	} else if (X < 0 && Y > 0) {
		retval = "SurOeste";
	}

	return retval;
}

bool SameFaccion(int UserIndex, int OtherUserIndex) {
	bool retval;
	/* '************************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modify Date: 17/11/2009 */
	/* 'Devuelve True si son de la misma faccion */
	/* '************************************************************** */
	retval = (esCaos(UserIndex) && esCaos(OtherUserIndex))
			|| (esArmada(UserIndex) && esArmada(OtherUserIndex));
	return retval;
}

int FarthestPet(int UserIndex) {
	int retval = 0;
	/* '************************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modify Date: 18/11/2009 */
	/* 'Devuelve el indice de la mascota mas lejana. */
	/* '************************************************************** */

	int PetIndex;
	int Distancia = 0;
	int OtraDistancia;

	if (UserList[UserIndex].NroMascotas == 0) {
		return retval;
	}

	for (PetIndex = (1); PetIndex <= (MAXMASCOTAS); PetIndex++) {
		/* ' Solo pos invocar criaturas que exitan! */
		if (UserList[UserIndex].MascotasIndex[PetIndex] > 0) {
			/* ' Solo aplica a mascota, nada de elementales.. */
			if (Npclist[UserList[UserIndex].MascotasIndex[PetIndex]].Contadores.TiempoExistencia == 0) {
				if (retval == 0) {
					/* ' Por si tiene 1 sola mascota */
					retval = PetIndex;
					Distancia = vb6::Abs(
							UserList[UserIndex].Pos.X
									- Npclist[UserList[UserIndex].MascotasIndex[PetIndex]].Pos.X)
							+ vb6::Abs(
									UserList[UserIndex].Pos.Y
											- Npclist[UserList[UserIndex].MascotasIndex[PetIndex]].Pos.Y);
				} else {
					/* ' La distancia de la proxima mascota */
					OtraDistancia = vb6::Abs(
							UserList[UserIndex].Pos.X
									- Npclist[UserList[UserIndex].MascotasIndex[PetIndex]].Pos.X)
							+ vb6::Abs(
									UserList[UserIndex].Pos.Y
											- Npclist[UserList[UserIndex].MascotasIndex[PetIndex]].Pos.Y);
					/* ' Esta mas lejos? */
					if (OtraDistancia > Distancia) {
						Distancia = OtraDistancia;
						retval = PetIndex;
					}
				}
			}
		}
	}

	return retval;
}

/* '' */
/* ' Set the EluSkill value at the skill. */
/* ' */
/* ' @param UserIndex  Specifies reference to user */
/* ' @param Skill      Number of the skill to check */
/* ' @param Allocation True If the motive of the modification is the allocation, False if the skill increase by training */

void CheckEluSkill(int UserIndex, int Skill, bool Allocation) {
	/* '************************************************* */
	/* 'Author: Torres Patricio (Pato) */
	/* 'Last modified: 11/20/2009 */
	/* ' */
	/* '************************************************* */

	if (UserList[UserIndex].Stats.UserSkills[Skill] < MAXSKILLPOINTS) {
		if (Allocation) {
			UserList[UserIndex].Stats.ExpSkills[Skill] = 0;
		} else {
			UserList[UserIndex].Stats.ExpSkills[Skill] = UserList[UserIndex].Stats.ExpSkills[Skill]
					- UserList[UserIndex].Stats.EluSkills[Skill];
		}

		UserList[UserIndex].Stats.EluSkills[Skill] = ELU_SKILL_INICIAL
				* std::pow(1.05, UserList[UserIndex].Stats.UserSkills[Skill]);
	} else {
		UserList[UserIndex].Stats.ExpSkills[Skill] = 0;
		UserList[UserIndex].Stats.EluSkills[Skill] = 0;
	}

}

bool HasEnoughItems(int UserIndex, int ObjIndex, int Amount) {
	bool retval;
	/* '************************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modify Date: 25/11/2009 */
	/* 'Cheks Wether the user has the required amount of items in the inventory or not */
	/* '************************************************************** */

	int Slot;
	int ItemInvAmount = 0;

	for (Slot = (1); Slot <= (UserList[UserIndex].CurrentInventorySlots); Slot++) {
		/* ' Si es el item que busco */
		if (UserList[UserIndex].Invent.Object[Slot].ObjIndex == ObjIndex) {
			/* ' Lo sumo a la cantidad total */
			ItemInvAmount = ItemInvAmount + UserList[UserIndex].Invent.Object[Slot].Amount;
		}
	}

	retval = Amount <= ItemInvAmount;
	return retval;
}

int TotalOfferItems(int ObjIndex, int UserIndex) {
	int retval = 0;
	/* '************************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modify Date: 25/11/2009 */
	/* 'Cheks the amount of items the user has in offerSlots. */
	/* '************************************************************** */
	int Slot;

	for (Slot = (1); Slot <= (MAX_OFFER_SLOTS); Slot++) {
		/* ' Si es el item que busco */
		if (UserList[UserIndex].ComUsu.Objeto[Slot] == ObjIndex) {
			/* ' Lo sumo a la cantidad total */
			retval = retval + UserList[UserIndex].ComUsu.cant[Slot];
		}
	}

	return retval;
}

int getMaxInventorySlots(int UserIndex) {
	int retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if (UserList[UserIndex].Invent.MochilaEqpObjIndex > 0) {
		/* '5=slots por fila, hacer constante */
		retval = MAX_NORMAL_INVENTORY_SLOTS
				+ ObjData[UserList[UserIndex].Invent.MochilaEqpObjIndex].MochilaType * 5;
	} else {
		retval = MAX_NORMAL_INVENTORY_SLOTS;
	}
	return retval;
}

void goHome(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Budi */
	/* 'Last Modification: 01/06/2010 */
	/* '01/06/2010: ZaMa - Ahora usa otro tipo de intervalo (lo saque de tPiquetec) */
	/* '*************************************************** */

	int Distance;
	int Tiempo;

	if (UserList[UserIndex].flags.Muerto == 1) {
		if (UserList[UserIndex].flags.lastMap == 0) {
			Distance =
					distanceToCities[UserList[UserIndex].Pos.Map].distanceToCity[UserList[UserIndex].Hogar];
		} else {
			Distance =
					distanceToCities[UserList[UserIndex].flags.lastMap].distanceToCity[UserList[UserIndex].Hogar]
							+ GOHOME_PENALTY;
		}

		/* ' [TEMPORAL]  30 'seg */
		Tiempo = (Distance + 1) * MaximoInt((UserList[UserIndex].Stats.ELV - 25), 0) * 1.5;

		IntervaloGoHome(UserIndex, Tiempo * 1000, true);

		WriteMultiMessage(UserIndex, eMessages_Home, Distance, Tiempo, 0,
				MapInfo[Ciudades[UserList[UserIndex].Hogar].Map].Name);
	} else {
		WriteConsoleMsg(UserIndex, "Debes estar muerto para poder utilizar este comando.",
				FontTypeNames_FONTTYPE_FIGHT);
	}

}

bool ToogleToAtackable(int UserIndex, int OwnerIndex, bool StealingNpc) {
	bool retval = false;
 	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 15/01/2010 */
	/* 'Change to Atackable mode. */
	/* '*************************************************** */

	int AtacablePor;

	if (MapInfo[UserList[UserIndex].Pos.Map].Pk == false) {
		WriteConsoleMsg(UserIndex, "No puedes robar npcs en zonas seguras.", FontTypeNames_FONTTYPE_INFO);
		return retval;
	}

	AtacablePor = UserList[UserIndex].flags.AtacablePor;

	if (AtacablePor > 0) {
		/* ' Intenta robar un npc */
		if (StealingNpc) {
			/* ' Puede atacar el mismo npc que ya estaba robando, pero no una nuevo. */
			if (AtacablePor != OwnerIndex) {
				WriteConsoleMsg(UserIndex,
						"No puedes atacar otra criatura con dueno hasta que haya terminado tu castigo.",
						FontTypeNames_FONTTYPE_INFO);
				return retval;
			}
			/* ' Esta atacando a alguien en estado atacable => Se renueva el timer de atacable */
		} else {
			/* ' Renovar el timer */
			IntervaloEstadoAtacable(UserIndex, true);
			retval = true;
			return retval;
		}
	}

	UserList[UserIndex].flags.AtacablePor = OwnerIndex;

	/* ' Actualizar clientes */
	RefreshCharStatus(UserIndex);

	/* ' Inicializar el timer */
	IntervaloEstadoAtacable(UserIndex, true);

	retval = true;

	return retval;
}

void setHome(int UserIndex, eCiudad newHome, int NpcIndex) {
	/* '*************************************************** */
	/* 'Author: Budi */
	/* 'Last Modification: 01/06/2010 */
	/* '30/04/2010: ZaMa - Ahora el npc avisa que se cambio de hogar. */
	/* '01/06/2010: ZaMa - Ahora te avisa si ya tenes ese hogar. */
	/* '*************************************************** */
	if (newHome < eCiudad_cUllathorpe || newHome > eCiudad_cLastCity - 1) {
		return;
	}

	if (UserList[UserIndex].Hogar != newHome) {
		UserList[UserIndex].Hogar = newHome;

		WriteChatOverHead(UserIndex,
				"¡¡¡Bienvenido a nuestra humilde comunidad, este es ahora tu nuevo hogar!!!",
				Npclist[NpcIndex].Char.CharIndex, 0x00ffffff);
	} else {
		WriteChatOverHead(UserIndex, "¡¡¡Ya eres miembro de nuestra humilde comunidad!!!",
				Npclist[NpcIndex].Char.CharIndex, 0x00ffffff);
	}

}

int GetHomeArrivalTime(int UserIndex) {
	int retval;
	/* '************************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modify by: ZaMa */
	/* 'Last Modify Date: 01/06/2010 */
	/* 'Calculates the time left to arrive home. */
	/* '************************************************************** */
	int TActual;

	TActual = vb6::GetTickCount();

	retval = getInterval(UserList[UserIndex].Counters.goHome, TActual) * 0.001;

	return retval;
}

void HomeArrival(int UserIndex) {
	/* '************************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modify by: ZaMa */
	/* 'Last Modify Date: 01/06/2010 */
	/* 'Teleports user to its home. */
	/* '************************************************************** */

	int tX;
	int tY;
	int tMap;

	/* 'Antes de que el pj llegue a la ciudad, lo hacemos dejar de navegar para que no se buguee. */
	if (UserList[UserIndex].flags.Navegando == 1) {
		UserList[UserIndex].Char.body = iCuerpoMuerto;
		UserList[UserIndex].Char.Head = iCabezaMuerto;
		UserList[UserIndex].Char.ShieldAnim = NingunEscudo;
		UserList[UserIndex].Char.WeaponAnim = NingunArma;
		UserList[UserIndex].Char.CascoAnim = NingunCasco;

		UserList[UserIndex].flags.Navegando = 0;

		WriteNavigateToggle(UserIndex);
		/* 'Le sacamos el navegando, pero no le mostramos a los demás porque va a ser sumoneado hasta ulla. */
	}

	tX = Ciudades[UserList[UserIndex].Hogar].X;
	tY = Ciudades[UserList[UserIndex].Hogar].Y;
	tMap = Ciudades[UserList[UserIndex].Hogar].Map;

	FindLegalPos(UserIndex, tMap, tX, tY);
	WarpUserChar(UserIndex, tMap, tX, tY, true);

	WriteMultiMessage(UserIndex, eMessages_FinishHome);

	UserList[UserIndex].flags.Traveling = 0;
	UserList[UserIndex].Counters.goHome = 0;

}
