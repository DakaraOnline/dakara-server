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

#include <sstream>

#include "Hechizos.h"


const int HELEMENTAL_FUEGO = 26;
const int HELEMENTAL_TIERRA = 28;

void NpcLanzaSpellSobreUser(int NpcIndex, int UserIndex, int Spell, bool DecirPalabras,
		bool IgnoreVisibilityCheck) {
	/* '*************************************************** */
	/* 'Autor: Unknown (orginal version) */
	/* 'Last Modification: 11/11/2010 */
	/* '13/02/2009: ZaMa - Los npcs que tiren magias, no podran hacerlo en mapas donde no se permita usarla. */
	/* '13/07/2010: ZaMa - Ahora no se contabiliza la muerte de un atacable. */
	/* '21/09/2010: ZaMa - Amplio los tipos de hechizos que pueden lanzar los npcs. */
	/* '21/09/2010: ZaMa - Permito que se ignore el chequeo de visibilidad (pueden atacar a invis u ocultos). */
	/* '11/11/2010: ZaMa - No se envian los efectos del hechizo si no lo castea. */
	/* '*************************************************** */

	if (Npclist[NpcIndex].CanAttack == 0) {
		return;
	}

	/* ' Doesn't consider if the user is hidden/invisible or not. */
	if (!IgnoreVisibilityCheck) {
		if (UserList[UserIndex].flags.invisible == 1 || UserList[UserIndex].flags.Oculto == 1) {
			return;
		}
	}

	/* ' Si no se peude usar magia en el mapa, no le deja hacerlo. */
	if (MapInfo[UserList[UserIndex].Pos.Map].MagiaSinEfecto > 0) {
		return;
	}

	Npclist[NpcIndex].CanAttack = 0;

	int dano;
	int AnilloObjIndex;
	AnilloObjIndex = UserList[UserIndex].Invent.AnilloEqpObjIndex;

	/* ' Heal HP */
	if (Hechizos[Spell].SubeHP == 1) {

		SendSpellEffects(UserIndex, NpcIndex, Spell, DecirPalabras);

		dano = RandomNumber(Hechizos[Spell].MinHp, Hechizos[Spell].MaxHp);

		UserList[UserIndex].Stats.MinHp = UserList[UserIndex].Stats.MinHp + dano;
		if (UserList[UserIndex].Stats.MinHp > UserList[UserIndex].Stats.MaxHp) {
			UserList[UserIndex].Stats.MinHp = UserList[UserIndex].Stats.MaxHp;
		}

		WriteConsoleMsg(UserIndex, Npclist[NpcIndex].Name + " te ha quitado " + vb6::CStr(dano) + " puntos de vida.",
				FontTypeNames_FONTTYPE_FIGHT);
		WriteUpdateUserStats(UserIndex);

		/* ' Damage */
	} else if (Hechizos[Spell].SubeHP == 2) {

		if (UserTienePrivilegio(UserIndex, PlayerType_User)) {

			SendSpellEffects(UserIndex, NpcIndex, Spell, DecirPalabras);

			dano = RandomNumber(Hechizos[Spell].MinHp, Hechizos[Spell].MaxHp);

			if (UserList[UserIndex].Invent.CascoEqpObjIndex > 0) {
				dano = dano
						- RandomNumber(ObjData[UserList[UserIndex].Invent.CascoEqpObjIndex].DefensaMagicaMin,
								ObjData[UserList[UserIndex].Invent.CascoEqpObjIndex].DefensaMagicaMax);
			}

			if (UserList[UserIndex].Invent.AnilloEqpObjIndex > 0) {
				dano = dano
						- RandomNumber(ObjData[UserList[UserIndex].Invent.AnilloEqpObjIndex].DefensaMagicaMin,
								ObjData[UserList[UserIndex].Invent.AnilloEqpObjIndex].DefensaMagicaMax);
			}

			if (dano < 0) {
				dano = 0;
			}

			UserList[UserIndex].Stats.MinHp = UserList[UserIndex].Stats.MinHp - dano;

			WriteConsoleMsg(UserIndex, Npclist[NpcIndex].Name + " te ha quitado " + vb6::CStr(dano) + " puntos de vida.",
					FontTypeNames_FONTTYPE_FIGHT);
			WriteUpdateUserStats(UserIndex);

			/* 'Muere */
			if (UserList[UserIndex].Stats.MinHp < 1) {
				UserList[UserIndex].Stats.MinHp = 0;
				if (Npclist[NpcIndex].NPCtype == eNPCType_GuardiaReal) {
					RestarCriminalidad(UserIndex);
				}

				int MasterIndex;
				MasterIndex = Npclist[NpcIndex].MaestroUser;

				/* '[Barrin 1-12-03] */
				if (MasterIndex > 0) {

					/* ' No son frags los muertos atacables */
					if (UserList[UserIndex].flags.AtacablePor != MasterIndex) {
						/* 'Store it! */
						StoreFrag(MasterIndex, UserIndex);

						ContarMuerte(UserIndex, MasterIndex);
					}

					ActStats(UserIndex, MasterIndex);
				}
				/* '[/Barrin] */

				UserDie(UserIndex);

			}

		}

	}

	/* ' Paralisis/Inmobilize */
	if (Hechizos[Spell].Paraliza == 1 || Hechizos[Spell].Inmoviliza == 1) {

		if (UserList[UserIndex].flags.Paralizado == 0) {

			SendSpellEffects(UserIndex, NpcIndex, Spell, DecirPalabras);

			if (AnilloObjIndex > 0) {
				if (ObjData[AnilloObjIndex].ImpideParalizar != 0) {
					WriteConsoleMsg(UserIndex, "Tu anillo rechaza los efectos de la paralisis.",
							FontTypeNames_FONTTYPE_FIGHT);
					return;
				}
			}

			if (Hechizos[Spell].Inmoviliza == 1) {

				UserList[UserIndex].flags.Inmovilizado = 1;

				if (AnilloObjIndex > 0) {
					if (ObjData[AnilloObjIndex].ImpideInmobilizar != 0) {
						UserList[UserIndex].flags.Inmovilizado = 0;
						WriteConsoleMsg(UserIndex, "Tu anillo rechaza los efectos del hechizo inmobilizar.",
								FontTypeNames_FONTTYPE_FIGHT);
					}
				}
			}

			UserList[UserIndex].flags.Paralizado = 1;
			UserList[UserIndex].Counters.Paralisis = IntervaloParalizado;

			WriteParalizeOK(UserIndex);

		}

	}

	/* ' Stupidity */
	if (Hechizos[Spell].Estupidez == 1) {

		if (UserList[UserIndex].flags.Estupidez == 0) {

			SendSpellEffects(UserIndex, NpcIndex, Spell, DecirPalabras);

			if (AnilloObjIndex > 0) {
				if (ObjData[AnilloObjIndex].ImpideAturdir != 0) {
					WriteConsoleMsg(UserIndex, "Tu anillo rechaza los efectos de la turbación.",
							FontTypeNames_FONTTYPE_FIGHT);
					return;
				}
			}

			UserList[UserIndex].flags.Estupidez = 1;
			UserList[UserIndex].Counters.Ceguera = IntervaloInvisible;

			WriteDumb(UserIndex);

		}
	}

	/* ' Blind */
	if (Hechizos[Spell].Ceguera == 1) {

		if (UserList[UserIndex].flags.Ceguera == 0) {

			SendSpellEffects(UserIndex, NpcIndex, Spell, DecirPalabras);

			if (AnilloObjIndex > 0) {
				if (ObjData[AnilloObjIndex].ImpideCegar != 0) {
					WriteConsoleMsg(UserIndex, "Tu anillo rechaza los efectos de la ceguera.",
							FontTypeNames_FONTTYPE_FIGHT);
					return;
				}
			}

			UserList[UserIndex].flags.Ceguera = 1;
			UserList[UserIndex].Counters.Ceguera = IntervaloInvisible;

			WriteBlind(UserIndex);

		}
	}

	/* ' Remove Invisibility/Hidden */
	if (Hechizos[Spell].RemueveInvisibilidadParcial == 1) {

		SendSpellEffects(UserIndex, NpcIndex, Spell, DecirPalabras);

		/* 'Sacamos el efecto de ocultarse */
		if (UserList[UserIndex].flags.Oculto == 1) {
			UserList[UserIndex].Counters.TiempoOculto = 0;
			UserList[UserIndex].flags.Oculto = 0;
			SetInvisible(UserIndex, UserList[UserIndex].Char.CharIndex, false);
			WriteConsoleMsg(UserIndex, "¡Has sido detectado!", FontTypeNames_FONTTYPE_VENENO);
		} else {
			/* 'sino, solo lo "iniciamos" en la sacada de invisibilidad. */
			WriteConsoleMsg(UserIndex, "Comienzas a hacerte visible.", FontTypeNames_FONTTYPE_VENENO);
			UserList[UserIndex].Counters.Invisibilidad = IntervaloInvisible - 1;
		}

	}

}

void SendSpellEffects(int UserIndex, int NpcIndex, int Spell, bool DecirPalabras) {
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 11/11/2010 */
	/* 'Sends spell's wav, fx and mgic words to users. */
	/* '*************************************************** */
	/* ' Spell Wav */
	SendData(SendTarget_ToPCArea, UserIndex,
			dakara::protocol::server::BuildPlayWave(Hechizos[Spell].WAV, UserList[UserIndex].Pos.X,
					UserList[UserIndex].Pos.Y));

	/* ' Spell FX */
	SendData(SendTarget_ToPCArea, UserIndex,
			dakara::protocol::server::BuildCreateFX(UserList[UserIndex].Char.CharIndex, Hechizos[Spell].FXgrh,
					Hechizos[Spell].loops));

	/* ' Spell Words */
	if (DecirPalabras) {
		SendData(SendTarget_ToNPCArea, NpcIndex,
				BuildChatOverHead(Hechizos[Spell].PalabrasMagicas, Npclist[NpcIndex].Char.CharIndex,
						vbCyan));
	}
}

void NpcLanzaSpellSobreNpc(int NpcIndex, int TargetNPC, int SpellIndex, bool DecirPalabras) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 21/09/2010 */
	/* '21/09/2010: ZaMa - Now npcs can cast a wider range of spells. */
	/* '*************************************************** */

	if (Npclist[NpcIndex].CanAttack == 0) {
		return;
	}
	Npclist[NpcIndex].CanAttack = 0;

	int Danio;

	/* ' Spell sound and FX */
	SendData(SendTarget_ToNPCArea, TargetNPC,
			dakara::protocol::server::BuildPlayWave(Hechizos[SpellIndex].WAV, Npclist[TargetNPC].Pos.X,
					Npclist[TargetNPC].Pos.Y));

	SendData(SendTarget_ToNPCArea, TargetNPC,
			dakara::protocol::server::BuildCreateFX(Npclist[TargetNPC].Char.CharIndex, Hechizos[SpellIndex].FXgrh,
					Hechizos[SpellIndex].loops));

	/* ' Decir las palabras magicas? */
	if (DecirPalabras) {
		SendData(SendTarget_ToNPCArea, NpcIndex,
				BuildChatOverHead(Hechizos[SpellIndex].PalabrasMagicas,
						Npclist[NpcIndex].Char.CharIndex, vbCyan));
	}

	/* ' Spell deals damage?? */
	if (Hechizos[SpellIndex].SubeHP == 2) {

		Danio = RandomNumber(Hechizos[SpellIndex].MinHp, Hechizos[SpellIndex].MaxHp);

		/* ' Deal damage */
		Npclist[TargetNPC].Stats.MinHp = Npclist[TargetNPC].Stats.MinHp - Danio;

		/* 'Muere? */
		if (Npclist[TargetNPC].Stats.MinHp < 1) {
			Npclist[TargetNPC].Stats.MinHp = 0;
			if (Npclist[NpcIndex].MaestroUser > 0) {
				MuereNpc(TargetNPC, Npclist[NpcIndex].MaestroUser);
			} else {
				MuereNpc(TargetNPC, 0);
			}
		}

		/* ' Spell recovers health?? */
	} else if (Hechizos[SpellIndex].SubeHP == 1) {

		Danio = RandomNumber(Hechizos[SpellIndex].MinHp, Hechizos[SpellIndex].MaxHp);

		/* ' Recovers health */
		Npclist[TargetNPC].Stats.MinHp = Npclist[TargetNPC].Stats.MinHp + Danio;

		if (Npclist[TargetNPC].Stats.MinHp > Npclist[TargetNPC].Stats.MaxHp) {
			Npclist[TargetNPC].Stats.MinHp = Npclist[TargetNPC].Stats.MaxHp;
		}

	}

	/* ' Spell Adds/Removes poison? */
	if (Hechizos[SpellIndex].Envenena == 1) {
		Npclist[TargetNPC].flags.Envenenado = 1;
	} else if (Hechizos[SpellIndex].CuraVeneno == 1) {
		Npclist[TargetNPC].flags.Envenenado = 0;
	}

	/* ' Spells Adds/Removes Paralisis/Inmobility? */
	if (Hechizos[SpellIndex].Paraliza == 1) {
		Npclist[TargetNPC].flags.Paralizado = 1;
		Npclist[TargetNPC].flags.Inmovilizado = 0;
		Npclist[TargetNPC].Contadores.Paralisis = IntervaloParalizado;

	} else if (Hechizos[SpellIndex].Inmoviliza == 1) {
		Npclist[TargetNPC].flags.Inmovilizado = 1;
		Npclist[TargetNPC].flags.Paralizado = 0;
		Npclist[TargetNPC].Contadores.Paralisis = IntervaloParalizado;

	} else if (Hechizos[SpellIndex].RemoverParalisis == 1) {
		if (Npclist[TargetNPC].flags.Paralizado == 1 || Npclist[TargetNPC].flags.Inmovilizado == 1) {
			Npclist[TargetNPC].flags.Paralizado = 0;
			Npclist[TargetNPC].flags.Inmovilizado = 0;
			Npclist[TargetNPC].Contadores.Paralisis = 0;
		}
	}

}

bool TieneHechizo(int i, int UserIndex) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int j;
	for (j = (1); j <= (MAXUSERHECHIZOS); j++) {
		if (UserList[UserIndex].Stats.UserHechizos[j] == i) {
			retval = true;
			return retval;
		}
	}

	return retval;
}

void AgregarHechizo(int UserIndex, int Slot) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int hIndex;
	int j;

	hIndex = ObjData[UserList[UserIndex].Invent.Object[Slot].ObjIndex].HechizoIndex;

	if (!TieneHechizo(hIndex, UserIndex)) {
		/* 'Buscamos un slot vacio */
		for (j = (1); j <= (MAXUSERHECHIZOS); j++) {
			if (UserList[UserIndex].Stats.UserHechizos[j] == 0) {
				break;
			}
		}

		if (j > MAXUSERHECHIZOS || UserList[UserIndex].Stats.UserHechizos[j] != 0) {
			WriteConsoleMsg(UserIndex, "No tienes espacio para más hechizos.", FontTypeNames_FONTTYPE_INFO);
		} else {
			UserList[UserIndex].Stats.UserHechizos[j] = hIndex;
			UpdateUserHechizos(false, UserIndex, vb6::CByte(j));
			/* 'Quitamos del inv el item */
			QuitarUserInvItem(UserIndex, vb6::CByte(Slot), 1);
		}
	} else {
		WriteConsoleMsg(UserIndex, "Ya tienes ese hechizo.", FontTypeNames_FONTTYPE_INFO);
	}

}

void DecirPalabrasMagicas(std::string SpellWords, int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 17/11/2009 */
	/* '25/07/2009: ZaMa - Invisible admins don't say any word when casting a spell */
	/* '17/11/2009: ZaMa - Now the user become visible when casting a spell, if it is hidden */
	/* '*************************************************** */

	if (UserList[UserIndex].flags.AdminInvisible != 1) {
		SendData(SendTarget_ToPCArea, UserIndex,
				BuildChatOverHead(SpellWords, UserList[UserIndex].Char.CharIndex, vbCyan));

		/* ' Si estaba oculto, se vuelve visible */
		if (UserList[UserIndex].flags.Oculto == 1) {
			UserList[UserIndex].flags.Oculto = 0;
			UserList[UserIndex].Counters.TiempoOculto = 0;

			if (UserList[UserIndex].flags.invisible == 0) {
				WriteConsoleMsg(UserIndex, "Has vuelto a ser visible.", FontTypeNames_FONTTYPE_INFO);
				SetInvisible(UserIndex, UserList[UserIndex].Char.CharIndex, false);
			}
		}
	}

	return;
}

/* '' */
/* ' Check if an user can cast a certain spell */
/* ' */
/* ' @param UserIndex Specifies reference to user */
/* ' @param HechizoIndex Specifies reference to spell */
/* ' @return   True if the user can cast the spell, otherwise returns false */
bool PuedeLanzar(int UserIndex, int HechizoIndex) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 12/01/2010 */
	/* 'Last Modification By: ZaMa */
	/* '06/11/09 - Corregida la bonificación de maná del mimetismo en el druida con flauta mágica equipada. */
	/* '19/11/2009: ZaMa - Validacion de mana para el Invocar Mascotas */
	/* '12/01/2010: ZaMa - Validacion de mana para hechizos lanzados por druida. */
	/* '*************************************************** */
	float DruidManaBonus;

	if (UserList[UserIndex].flags.Muerto) {
		WriteConsoleMsg(UserIndex, "No puedes lanzar hechizos estando muerto.", FontTypeNames_FONTTYPE_INFO);
		return retval;
	}

	if (Hechizos[HechizoIndex].NeedStaff > 0) {
		if (UserList[UserIndex].clase == eClass_Mage) {
			if (UserList[UserIndex].Invent.WeaponEqpObjIndex > 0) {
				if (ObjData[UserList[UserIndex].Invent.WeaponEqpObjIndex].StaffPower
						< Hechizos[HechizoIndex].NeedStaff) {
					WriteConsoleMsg(UserIndex,
							"No posees un báculo lo suficientemente poderoso para poder lanzar el conjuro.",
							FontTypeNames_FONTTYPE_INFO);
					return retval;
				}
			} else {
				WriteConsoleMsg(UserIndex, "No puedes lanzar este conjuro sin la ayuda de un báculo.",
						FontTypeNames_FONTTYPE_INFO);
				return retval;
			}
		}
	}

	if (UserList[UserIndex].Stats.UserSkills[eSkill_Magia] < Hechizos[HechizoIndex].MinSkill) {
		WriteConsoleMsg(UserIndex, "No tienes suficientes puntos de magia para lanzar este hechizo.",
				FontTypeNames_FONTTYPE_INFO);
		return retval;
	}

	if (UserList[UserIndex].Stats.MinSta < Hechizos[HechizoIndex].StaRequerido) {
		if (UserList[UserIndex].Genero == eGenero_Hombre) {
			WriteConsoleMsg(UserIndex, "Estás muy cansado para lanzar este hechizo.",
					FontTypeNames_FONTTYPE_INFO);
		} else {
			WriteConsoleMsg(UserIndex, "Estás muy cansada para lanzar este hechizo.",
					FontTypeNames_FONTTYPE_INFO);
		}
		return retval;
	}

	DruidManaBonus = 1;
	if (UserList[UserIndex].clase == eClass_Druid) {
		if (UserList[UserIndex].Invent.AnilloEqpObjIndex == FLAUTAELFICA) {
			/* ' 50% menos de mana requerido para mimetismo */
			if (Hechizos[HechizoIndex].Mimetiza == 1) {
				DruidManaBonus = 0.5;

				/* ' 30% menos de mana requerido para invocaciones */
			} else if (Hechizos[HechizoIndex].Tipo == TipoHechizo_uInvocacion) {
				DruidManaBonus = 0.7;

				/* ' 10% menos de mana requerido para las demas magias, excepto apoca */
			} else if (HechizoIndex != APOCALIPSIS_SPELL_INDEX) {
				DruidManaBonus = 0.9;
			}
		}

		/* ' Necesita tener la barra de mana completa para invocar una mascota */
		if (Hechizos[HechizoIndex].Warp == 1) {
			if (UserList[UserIndex].Stats.MinMAN != UserList[UserIndex].Stats.MaxMAN) {
				WriteConsoleMsg(UserIndex, "Debes poseer toda tu maná para poder lanzar este hechizo.",
						FontTypeNames_FONTTYPE_INFO);
				return retval;
				/* ' Si no tiene mascotas, no tiene sentido que lo use */
			} else if (UserList[UserIndex].NroMascotas == 0) {
				WriteConsoleMsg(UserIndex, "Debes poseer alguna mascota para poder lanzar este hechizo.",
						FontTypeNames_FONTTYPE_INFO);
				return retval;
			}
		}
	}

	if (UserList[UserIndex].Stats.MinMAN < Hechizos[HechizoIndex].ManaRequerido * DruidManaBonus) {
		WriteConsoleMsg(UserIndex, "No tienes suficiente maná.", FontTypeNames_FONTTYPE_INFO);
		return retval;
	}

	retval = true;
	return retval;
}

void HechizoTerrenoEstado(int UserIndex, bool & b) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int PosCasteadaX;
	int PosCasteadaY;
	int PosCasteadaM;
	int H;
	int TempX;
	int TempY;

	PosCasteadaX = UserList[UserIndex].flags.TargetX;
	PosCasteadaY = UserList[UserIndex].flags.TargetY;
	PosCasteadaM = UserList[UserIndex].flags.TargetMap;

	H = UserList[UserIndex].flags.Hechizo;

	if (Hechizos[H].RemueveInvisibilidadParcial == 1) {
		b = true;
		for (TempX = (PosCasteadaX - 8); TempX <= (PosCasteadaX + 8); TempX++) {
			for (TempY = (PosCasteadaY - 8); TempY <= (PosCasteadaY + 8); TempY++) {
				if (InMapBounds(PosCasteadaM, TempX, TempY)) {
					if (MapData[PosCasteadaM][TempX][TempY].UserIndex > 0) {
						/* 'hay un user */
						if (UserList[MapData[PosCasteadaM][TempX][TempY].UserIndex].flags.invisible == 1
								&& UserList[MapData[PosCasteadaM][TempX][TempY].UserIndex].flags.AdminInvisible
										== 0) {
							SendData(SendTarget_ToPCArea, UserIndex,
									dakara::protocol::server::BuildCreateFX(
											UserList[MapData[PosCasteadaM][TempX][TempY].UserIndex].Char.CharIndex,
											Hechizos[H].FXgrh, Hechizos[H].loops));
						}
					}
				}
			}
		}

		InfoHechizo(UserIndex);
	}
}

/* '' */
/* ' Le da propiedades al nuevo npc */
/* ' */
/* ' @param UserIndex  Indice del usuario que invoca. */
/* ' @param b  Indica si se termino la operación. */

void HechizoInvocacion(int UserIndex, bool & HechizoCasteado) {
	/* '*************************************************** */
	/* 'Author: Uknown */
	/* 'Last modification: 18/09/2010 */
	/* 'Sale del sub si no hay una posición valida. */
	/* '18/11/2009: Optimizacion de codigo. */
	/* '18/09/2010: ZaMa - No se permite invocar en mapas con InvocarSinEfecto. */
	/* '*************************************************** */

	int mapa;
	mapa = UserList[UserIndex].Pos.Map;

	/* 'No permitimos se invoquen criaturas en zonas seguras */
	if (MapInfo[mapa].Pk == false
			|| MapData[mapa][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].trigger
					== eTrigger_ZONASEGURA) {
		WriteConsoleMsg(UserIndex, "No puedes invocar criaturas en zona segura.",
				FontTypeNames_FONTTYPE_INFO);
		return;
	}

	/* 'No permitimos se invoquen criaturas en mapas donde esta prohibido hacerlo */
	if (MapInfo[mapa].InvocarSinEfecto == 1) {
		WriteConsoleMsg(UserIndex,
				"Invocar no está permitido aquí! Retirate de la Zona si deseas utilizar el Hechizo.",
				FontTypeNames_FONTTYPE_INFO);
		return;
	}

	int SpellIndex;
	int NroNpcs;
	int NpcIndex;
	int PetIndex;
	struct WorldPos TargetPos;

	TargetPos.Map = UserList[UserIndex].flags.TargetMap;
	TargetPos.X = UserList[UserIndex].flags.TargetX;
	TargetPos.Y = UserList[UserIndex].flags.TargetY;

	SpellIndex = UserList[UserIndex].flags.Hechizo;

	/* ' Warp de mascotas */
	if (Hechizos[SpellIndex].Warp == 1) {
		PetIndex = FarthestPet(UserIndex);

		/* ' La invoco cerca mio */
		if (PetIndex > 0) {
			WarpMascota(UserIndex, PetIndex);
		}

		/* ' Invocacion normal */
	} else {
		if (UserList[UserIndex].NroMascotas >= MAXMASCOTAS) {
			return;
		}

		for (NroNpcs = (1); NroNpcs <= (Hechizos[SpellIndex].cant); NroNpcs++) {

			if (UserList[UserIndex].NroMascotas < MAXMASCOTAS) {
				NpcIndex = SpawnNpc(Hechizos[SpellIndex].NumNpc, TargetPos, true, false);
				if (NpcIndex > 0) {
					UserList[UserIndex].NroMascotas = UserList[UserIndex].NroMascotas + 1;

					PetIndex = FreeMascotaIndex(UserIndex);

					UserList[UserIndex].MascotasIndex[PetIndex] = NpcIndex;
					UserList[UserIndex].MascotasType[PetIndex] = Npclist[NpcIndex].Numero;

					Npclist[NpcIndex].MaestroUser = UserIndex;
					Npclist[NpcIndex].Contadores.TiempoExistencia = IntervaloInvocacion;
					Npclist[NpcIndex].GiveGLD = 0;

					FollowAmo(NpcIndex);
				} else {
					return;
				}
			} else {
				break;
			}

		}
	}

	InfoHechizo(UserIndex);
	HechizoCasteado = true;
}

void HandleHechizoTerreno(int UserIndex, int SpellIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 18/11/2009 */
	/* '18/11/2009: ZaMa - Optimizacion de codigo. */
	/* '*************************************************** */

	bool HechizoCasteado = false;
	int ManaRequerida = 0;

	switch (Hechizos[SpellIndex].Tipo) {
	case TipoHechizo_uInvocacion:
		HechizoInvocacion(UserIndex, HechizoCasteado);
		break;

	case TipoHechizo_uEstado:
		HechizoTerrenoEstado(UserIndex, HechizoCasteado);
		break;

	default:
		break;
	}

	if (HechizoCasteado) {
		SubirSkill(UserIndex, eSkill_Magia, true);

		ManaRequerida = Hechizos[SpellIndex].ManaRequerido;

		/* ' Invocó una mascota */
		if (Hechizos[SpellIndex].Warp == 1) {
			/* ' Consume toda la mana */
			ManaRequerida = UserList[UserIndex].Stats.MinMAN;
		} else {
			/* ' Bonificaciones en hechizos */
			if (UserList[UserIndex].clase == eClass_Druid) {
				/* ' Solo con flauta equipada */
				if (UserList[UserIndex].Invent.AnilloEqpObjIndex == FLAUTAELFICA) {
					/* ' 30% menos de mana para invocaciones */
					ManaRequerida = ManaRequerida * 0.7;
				}
			}
		}

		/* ' Quito la mana requerida */
		UserList[UserIndex].Stats.MinMAN = UserList[UserIndex].Stats.MinMAN - ManaRequerida;
		if (UserList[UserIndex].Stats.MinMAN < 0) {
			UserList[UserIndex].Stats.MinMAN = 0;
		}

		/* ' Quito la estamina requerida */
		UserList[UserIndex].Stats.MinSta = UserList[UserIndex].Stats.MinSta
				- Hechizos[SpellIndex].StaRequerido;
		if (UserList[UserIndex].Stats.MinSta < 0) {
			UserList[UserIndex].Stats.MinSta = 0;
		}

		/* ' Update user stats */
		WriteUpdateUserStats(UserIndex);
	}

}

void HandleHechizoUsuario(int UserIndex, int SpellIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 12/01/2010 */
	/* '18/11/2009: ZaMa - Optimizacion de codigo. */
	/* '12/01/2010: ZaMa - Optimizacion y agrego bonificaciones al druida. */
	/* '*************************************************** */

	bool HechizoCasteado = false;
	int ManaRequerida = 0;

	switch (Hechizos[SpellIndex].Tipo) {
	case TipoHechizo_uEstado:
		/* ' Afectan estados (por ejem : Envenenamiento) */
		HechizoEstadoUsuario(UserIndex, HechizoCasteado);
		break;

	case TipoHechizo_uPropiedades:
		/* ' Afectan HP,MANA,STAMINA,ETC */
		HechizoCasteado = HechizoPropUsuario(UserIndex);
		break;

	default:
		break;
	}

	if (HechizoCasteado) {
		SubirSkill(UserIndex, eSkill_Magia, true);

		ManaRequerida = Hechizos[SpellIndex].ManaRequerido;

		/* ' Bonificaciones para druida */
		if (UserList[UserIndex].clase == eClass_Druid) {
			/* ' Solo con flauta magica */
			if (UserList[UserIndex].Invent.AnilloEqpObjIndex == FLAUTAELFICA) {
				if (Hechizos[SpellIndex].Mimetiza == 1) {
					/* ' 50% menos de mana para mimetismo */
					ManaRequerida = ManaRequerida * 0.5;

				} else if (SpellIndex != APOCALIPSIS_SPELL_INDEX) {
					/* ' 10% menos de mana para todo menos apoca y descarga */
					ManaRequerida = ManaRequerida * 0.9;
				}
			}
		}

		/* ' Quito la mana requerida */
		UserList[UserIndex].Stats.MinMAN = UserList[UserIndex].Stats.MinMAN - ManaRequerida;
		if (UserList[UserIndex].Stats.MinMAN < 0) {
			UserList[UserIndex].Stats.MinMAN = 0;
		}

		/* ' Quito la estamina requerida */
		UserList[UserIndex].Stats.MinSta = UserList[UserIndex].Stats.MinSta
				- Hechizos[SpellIndex].StaRequerido;
		if (UserList[UserIndex].Stats.MinSta < 0) {
			UserList[UserIndex].Stats.MinSta = 0;
		}

		/* ' Update user stats */
		WriteUpdateUserStats(UserIndex);
		WriteUpdateUserStats(UserList[UserIndex].flags.TargetUser);
		UserList[UserIndex].flags.TargetUser = 0;
	}

}

void HandleHechizoNPC(int UserIndex, int HechizoIndex) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 12/01/2010 */
	/* '13/02/2009: ZaMa - Agregada 50% bonificacion en coste de mana a mimetismo para druidas */
	/* '17/11/2009: ZaMa - Optimizacion de codigo. */
	/* '12/01/2010: ZaMa - Bonificacion para druidas de 10% para todos hechizos excepto apoca y descarga. */
	/* '12/01/2010: ZaMa - Los druidas mimetizados con npcs ahora son ignorados. */
	/* '*************************************************** */
	bool HechizoCasteado = false;
	int ManaRequerida = 0;

	switch (Hechizos[HechizoIndex].Tipo) {
	case TipoHechizo_uEstado:
		/* ' Afectan estados (por ejem : Envenenamiento) */
		HechizoEstadoNPC(UserList[UserIndex].flags.TargetNPC, HechizoIndex, HechizoCasteado, UserIndex);
		break;

	case TipoHechizo_uPropiedades:
		/* ' Afectan HP,MANA,STAMINA,ETC */
		HechizoPropNPC(HechizoIndex, UserList[UserIndex].flags.TargetNPC, UserIndex, HechizoCasteado);
		break;

	default:
		break;
	}

	if (HechizoCasteado) {
		SubirSkill(UserIndex, eSkill_Magia, true);

		ManaRequerida = Hechizos[HechizoIndex].ManaRequerido;

		/* ' Bonificación para druidas. */
		if (UserList[UserIndex].clase == eClass_Druid) {
			/* ' Se mostró como usuario, puede ser atacado por npcs */
			UserList[UserIndex].flags.Ignorado = false;

			/* ' Solo con flauta equipada */
			if (UserList[UserIndex].Invent.AnilloEqpObjIndex == FLAUTAELFICA) {
				if (Hechizos[HechizoIndex].Mimetiza == 1) {
					/* ' 50% menos de mana para mimetismo */
					ManaRequerida = ManaRequerida * 0.5;
					/* ' Será ignorado hasta que pierda el efecto del mimetismo o ataque un npc */
					UserList[UserIndex].flags.Ignorado = true;
				} else {
					/* ' 10% menos de mana para hechizos */
					if (HechizoIndex != APOCALIPSIS_SPELL_INDEX) {
						ManaRequerida = ManaRequerida * 0.9;
					}
				}
			}
		}

		/* ' Quito la mana requerida */
		UserList[UserIndex].Stats.MinMAN = UserList[UserIndex].Stats.MinMAN - ManaRequerida;
		if (UserList[UserIndex].Stats.MinMAN < 0) {
			UserList[UserIndex].Stats.MinMAN = 0;
		}

		/* ' Quito la estamina requerida */
		UserList[UserIndex].Stats.MinSta = UserList[UserIndex].Stats.MinSta
				- Hechizos[HechizoIndex].StaRequerido;
		if (UserList[UserIndex].Stats.MinSta < 0) {
			UserList[UserIndex].Stats.MinSta = 0;
		}

		/* ' Update user stats */
		WriteUpdateUserStats(UserIndex);
		UserList[UserIndex].flags.TargetNPC = 0;
	}
}

void LanzarHechizo(int SpellIndex, int UserIndex) {
	/* '*************************************************** */
	/* 'Autor: Unknown (orginal version) */
	/* 'Last Modification: 02/16/2010 */
	/* '24/01/2007 ZaMa - Optimizacion de codigo. */
	/* '02/16/2010: Marco - Now .flags.hechizo makes reference to global spell index instead of user's spell index */
	/* '*************************************************** */

	if (UserList[UserIndex].flags.EnConsulta) {
		WriteConsoleMsg(UserIndex, "No puedes lanzar hechizos si estás en consulta.",
				FontTypeNames_FONTTYPE_INFO);
		return;
	}

	if (PuedeLanzar(UserIndex, SpellIndex)) {
		switch (Hechizos[SpellIndex].Target) {
		case TargetType_uUsuarios:
			if (UserList[UserIndex].flags.TargetUser > 0) {
				if (vb6::Abs(UserList[UserList[UserIndex].flags.TargetUser].Pos.Y - UserList[UserIndex].Pos.Y)
						<= RANGO_VISION_Y) {
					HandleHechizoUsuario(UserIndex, SpellIndex);
				} else {
					WriteConsoleMsg(UserIndex, "Estás demasiado lejos para lanzar este hechizo.",
							FontTypeNames_FONTTYPE_WARNING);
				}
			} else {
				WriteConsoleMsg(UserIndex, "Este hechizo actúa sólo sobre usuarios.",
						FontTypeNames_FONTTYPE_INFO);
			}

			break;

		case TargetType_uNPC:
			if (UserList[UserIndex].flags.TargetNPC > 0) {
				if (vb6::Abs(Npclist[UserList[UserIndex].flags.TargetNPC].Pos.Y - UserList[UserIndex].Pos.Y)
						<= RANGO_VISION_Y) {
					HandleHechizoNPC(UserIndex, SpellIndex);
				} else {
					WriteConsoleMsg(UserIndex, "Estás demasiado lejos para lanzar este hechizo.",
							FontTypeNames_FONTTYPE_WARNING);
				}
			} else {
				WriteConsoleMsg(UserIndex, "Este hechizo sólo afecta a los npcs.",
						FontTypeNames_FONTTYPE_INFO);
			}

			break;

		case TargetType_uUsuariosYnpc:
			if (UserList[UserIndex].flags.TargetUser > 0) {
				if (vb6::Abs(UserList[UserList[UserIndex].flags.TargetUser].Pos.Y - UserList[UserIndex].Pos.Y)
						<= RANGO_VISION_Y) {
					HandleHechizoUsuario(UserIndex, SpellIndex);
				} else {
					WriteConsoleMsg(UserIndex, "Estás demasiado lejos para lanzar este hechizo.",
							FontTypeNames_FONTTYPE_WARNING);
				}
			} else if (UserList[UserIndex].flags.TargetNPC > 0) {
				if (vb6::Abs(Npclist[UserList[UserIndex].flags.TargetNPC].Pos.Y - UserList[UserIndex].Pos.Y)
						<= RANGO_VISION_Y) {
					HandleHechizoNPC(UserIndex, SpellIndex);
				} else {
					WriteConsoleMsg(UserIndex, "Estás demasiado lejos para lanzar este hechizo.",
							FontTypeNames_FONTTYPE_WARNING);
				}
			} else {
				WriteConsoleMsg(UserIndex, "Target inválido.", FontTypeNames_FONTTYPE_INFO);
			}

			break;

		case TargetType_uTerreno:
			HandleHechizoTerreno(UserIndex, SpellIndex);
			break;
		}

	}

	if (UserList[UserIndex].Counters.Trabajando) {
		UserList[UserIndex].Counters.Trabajando = UserList[UserIndex].Counters.Trabajando - 1;
	}

	if (UserList[UserIndex].Counters.Ocultando) {
		UserList[UserIndex].Counters.Ocultando = UserList[UserIndex].Counters.Ocultando - 1;
	}
}

void HechizoEstadoUsuario(int UserIndex, bool & HechizoCasteado) {
	/* '*************************************************** */
	/* 'Autor: Unknown (orginal version) */
	/* 'Last Modification: 28/04/2010 */
	/* 'Handles the Spells that afect the Stats of an User */
	/* '24/01/2007 Pablo (ToxicWaste) - Invisibilidad no permitida en Mapas con InviSinEfecto */
	/* '26/01/2007 Pablo (ToxicWaste) - Cambios que permiten mejor manejo de ataques en los rings. */
	/* '26/01/2007 Pablo (ToxicWaste) - Revivir no permitido en Mapas con ResuSinEfecto */
	/* '02/01/2008 Marcos (ByVal) - Curar Veneno no permitido en usuarios muertos. */
	/* '06/28/2008 NicoNZ - Agregué que se le de valor al flag Inmovilizado. */
	/* '17/11/2008: NicoNZ - Agregado para quitar la penalización de vida en el ring y cambio de ecuacion. */
	/* '13/02/2009: ZaMa - Arreglada ecuacion para quitar vida tras resucitar en rings. */
	/* '23/11/2009: ZaMa - Optimizacion de codigo. */
	/* '28/04/2010: ZaMa - Agrego Restricciones para ciudas respecto al estado atacable. */
	/* '16/09/2010: ZaMa - Solo se hace invi para los clientes si no esta navegando. */
	/* '*************************************************** */

	int HechizoIndex;
	int TargetIndex;

	HechizoIndex = UserList[UserIndex].flags.Hechizo;
	TargetIndex = UserList[UserIndex].flags.TargetUser;

	int AnilloObjIndex;
	AnilloObjIndex = UserList[TargetIndex].Invent.AnilloEqpObjIndex;

	/* ' <-------- Agrega Invisibilidad ----------> */
	if (Hechizos[HechizoIndex].Invisibilidad == 1) {
		if (UserList[TargetIndex].flags.Muerto == 1) {
			WriteConsoleMsg(UserIndex, "¡El usuario está muerto!", FontTypeNames_FONTTYPE_INFO);
			HechizoCasteado = false;
			return;
		}

		if (UserList[TargetIndex].Counters.Saliendo) {
			if (UserIndex != TargetIndex) {
				WriteConsoleMsg(UserIndex, "¡El hechizo no tiene efecto!", FontTypeNames_FONTTYPE_INFO);
				HechizoCasteado = false;
				return;
			} else {
				WriteConsoleMsg(UserIndex, "¡No puedes hacerte invisible mientras te encuentras saliendo!",
						FontTypeNames_FONTTYPE_WARNING);
				HechizoCasteado = false;
				return;
			}
		}

		/* 'No usar invi mapas InviSinEfecto */
		if (MapInfo[UserList[TargetIndex].Pos.Map].InviSinEfecto > 0) {
			WriteConsoleMsg(UserIndex, "¡La invisibilidad no funciona aquí!", FontTypeNames_FONTTYPE_INFO);
			HechizoCasteado = false;
			return;
		}

		/* ' Chequea si el status permite ayudar al otro usuario */
		HechizoCasteado = CanSupportUser(UserIndex, TargetIndex, true);
		if (!HechizoCasteado) {
			return;
		}

		/* 'Si sos user, no uses este hechizo con GMS. */
		if (UserTienePrivilegio(UserIndex, PlayerType_User)) {
			if (!UserTienePrivilegio(TargetIndex, PlayerType_User)) {
				HechizoCasteado = false;
				return;
			}
		}

		UserList[TargetIndex].flags.invisible = 1;

		/* ' Solo se hace invi para los clientes si no esta navegando */
		if (UserList[TargetIndex].flags.Navegando == 0) {
			SetInvisible(TargetIndex, UserList[TargetIndex].Char.CharIndex, true);
		}

		InfoHechizo(UserIndex);
		HechizoCasteado = true;
	}

	/* ' <-------- Agrega Mimetismo ----------> */
	if (Hechizos[HechizoIndex].Mimetiza == 1) {
		if (UserList[TargetIndex].flags.Muerto == 1) {
			return;
		}

		if (UserList[TargetIndex].flags.Navegando == 1) {
			return;
		}
		if (UserList[UserIndex].flags.Navegando == 1) {
			return;
		}

		/* 'Si sos user, no uses este hechizo con GMS. */
		if (UserTienePrivilegio(UserIndex, PlayerType_User)) {
			if (!UserTienePrivilegio(TargetIndex, PlayerType_User)) {
				HechizoCasteado = false;
				return;
			}
		}

		if (UserList[UserIndex].flags.Mimetizado == 1) {
			WriteConsoleMsg(UserIndex, "Ya te encuentras mimetizado. El hechizo no ha tenido efecto.",
					FontTypeNames_FONTTYPE_INFO);
			return;
		}

		if (UserList[UserIndex].flags.AdminInvisible == 1) {
			return;
		}

		/* 'copio el char original al mimetizado */

		UserList[UserIndex].CharMimetizado.body = UserList[UserIndex].Char.body;
		UserList[UserIndex].CharMimetizado.Head = UserList[UserIndex].Char.Head;
		UserList[UserIndex].CharMimetizado.CascoAnim = UserList[UserIndex].Char.CascoAnim;
		UserList[UserIndex].CharMimetizado.ShieldAnim = UserList[UserIndex].Char.ShieldAnim;
		UserList[UserIndex].CharMimetizado.WeaponAnim = UserList[UserIndex].Char.WeaponAnim;

		UserList[UserIndex].flags.Mimetizado = 1;

		/* 'ahora pongo local el del enemigo */
		UserList[UserIndex].Char.body = UserList[TargetIndex].Char.body;
		UserList[UserIndex].Char.Head = UserList[TargetIndex].Char.Head;
		UserList[UserIndex].Char.CascoAnim = UserList[TargetIndex].Char.CascoAnim;
		UserList[UserIndex].Char.ShieldAnim = UserList[TargetIndex].Char.ShieldAnim;
		UserList[UserIndex].Char.WeaponAnim = UserList[TargetIndex].Char.WeaponAnim;

		ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
				UserList[UserIndex].Char.heading, UserList[UserIndex].Char.WeaponAnim,
				UserList[UserIndex].Char.ShieldAnim, UserList[UserIndex].Char.CascoAnim);

		InfoHechizo(UserIndex);
		HechizoCasteado = true;
	}

	/* ' <-------- Agrega Envenenamiento ----------> */
	if (Hechizos[HechizoIndex].Envenena == 1) {
		if (UserIndex == TargetIndex) {
			WriteConsoleMsg(UserIndex, "No puedes atacarte a vos mismo.", FontTypeNames_FONTTYPE_FIGHT);
			return;
		}

		if (!PuedeAtacar(UserIndex, TargetIndex)) {
			return;
		}
		if (UserIndex != TargetIndex) {
			UsuarioAtacadoPorUsuario(UserIndex, TargetIndex);
		}
		UserList[TargetIndex].flags.Envenenado = 1;
		InfoHechizo(UserIndex);
		HechizoCasteado = true;
	}

	/* ' <-------- Cura Envenenamiento ----------> */
	if (Hechizos[HechizoIndex].CuraVeneno == 1) {

		/* 'Verificamos que el usuario no este muerto */
		if (UserList[TargetIndex].flags.Muerto == 1) {
			WriteConsoleMsg(UserIndex, "¡El usuario está muerto!", FontTypeNames_FONTTYPE_INFO);
			HechizoCasteado = false;
			return;
		}

		/* ' Chequea si el status permite ayudar al otro usuario */
		HechizoCasteado = CanSupportUser(UserIndex, TargetIndex);
		if (!HechizoCasteado) {
			return;
		}

		/* 'Si sos user, no uses este hechizo con GMS. */
		if (UserTienePrivilegio(UserIndex, PlayerType_User)) {
			if (!UserTienePrivilegio(TargetIndex, PlayerType_User)) {
				HechizoCasteado = false;
				return;
			}
		}

		UserList[TargetIndex].flags.Envenenado = 0;
		InfoHechizo(UserIndex);
		HechizoCasteado = true;
	}

	/* ' <-------- Agrega Maldicion ----------> */
	if (Hechizos[HechizoIndex].Maldicion == 1) {
		if (UserIndex == TargetIndex) {
			WriteConsoleMsg(UserIndex, "No puedes atacarte a vos mismo.", FontTypeNames_FONTTYPE_FIGHT);
			return;
		}

		if (!PuedeAtacar(UserIndex, TargetIndex)) {
			return;
		}
		if (UserIndex != TargetIndex) {
			UsuarioAtacadoPorUsuario(UserIndex, TargetIndex);
		}
		UserList[TargetIndex].flags.Maldicion = 1;
		InfoHechizo(UserIndex);
		HechizoCasteado = true;
	}

	/* ' <-------- Remueve Maldicion ----------> */
	if (Hechizos[HechizoIndex].RemoverMaldicion == 1) {
		UserList[TargetIndex].flags.Maldicion = 0;
		InfoHechizo(UserIndex);
		HechizoCasteado = true;
	}

	/* ' <-------- Agrega Bendicion ----------> */
	if (Hechizos[HechizoIndex].Bendicion == 1) {
		UserList[TargetIndex].flags.Bendicion = 1;
		InfoHechizo(UserIndex);
		HechizoCasteado = true;
	}

	/* ' <-------- Agrega Paralisis/Inmobilidad ----------> */
	if (Hechizos[HechizoIndex].Paraliza == 1 || Hechizos[HechizoIndex].Inmoviliza == 1) {
		if (UserIndex == TargetIndex) {
			WriteConsoleMsg(UserIndex, "No puedes atacarte a vos mismo.", FontTypeNames_FONTTYPE_FIGHT);
			return;
		}

		if (UserList[TargetIndex].flags.Paralizado == 0) {
			if (!PuedeAtacar(UserIndex, TargetIndex)) {
				return;
			}

			if (UserIndex != TargetIndex) {
				UsuarioAtacadoPorUsuario(UserIndex, TargetIndex);
			}

			InfoHechizo(UserIndex);
			HechizoCasteado = true;

			if (AnilloObjIndex > 0) {
				if (ObjData[AnilloObjIndex].ImpideParalizar != 0) {
					WriteConsoleMsg(UserIndex, "Tu anillo rechaza los efectos de la paralisis.",
							FontTypeNames_FONTTYPE_FIGHT);
					WriteConsoleMsg(UserIndex, " ¡El hechizo no tiene efecto!", FontTypeNames_FONTTYPE_FIGHT);
					FlushBuffer(TargetIndex);
					return;
				}
			}

			if (Hechizos[HechizoIndex].Inmoviliza == 1) {
				UserList[TargetIndex].flags.Inmovilizado = 1;

				if (AnilloObjIndex > 0) {
					if (ObjData[AnilloObjIndex].ImpideInmobilizar != 0) {
						UserList[TargetIndex].flags.Inmovilizado = 0;
						WriteConsoleMsg(UserIndex, "Tu anillo rechaza los efectos del hechizo inmobilizar.",
								FontTypeNames_FONTTYPE_FIGHT);
						WriteConsoleMsg(UserIndex, " ¡El hechizo no tiene efecto!",
								FontTypeNames_FONTTYPE_FIGHT);
					}
				}
			}

			UserList[TargetIndex].flags.Paralizado = 1;
			UserList[TargetIndex].Counters.Paralisis = IntervaloParalizado;

			UserList[TargetIndex].flags.ParalizedByIndex = UserIndex;
			UserList[TargetIndex].flags.ParalizedBy = UserList[UserIndex].Name;

			WriteParalizeOK(TargetIndex);
			FlushBuffer(TargetIndex);
		}
	}

	/* ' <-------- Remueve Paralisis/Inmobilidad ----------> */
	if (Hechizos[HechizoIndex].RemoverParalisis == 1) {

		/* ' Remueve si esta en ese estado */
		if (UserList[TargetIndex].flags.Paralizado == 1) {

			/* ' Chequea si el status permite ayudar al otro usuario */
			HechizoCasteado = CanSupportUser(UserIndex, TargetIndex, true);
			if (!HechizoCasteado) {
				return;
			}

			RemoveParalisis(TargetIndex);
			InfoHechizo(UserIndex);

		}
	}

	/* ' <-------- Remueve Estupidez (Aturdimiento) ----------> */
	if (Hechizos[HechizoIndex].RemoverEstupidez == 1) {

		/* ' Remueve si esta en ese estado */
		if (UserList[TargetIndex].flags.Estupidez == 1) {

			/* ' Chequea si el status permite ayudar al otro usuario */
			HechizoCasteado = CanSupportUser(UserIndex, TargetIndex);
			if (!HechizoCasteado) {
				return;
			}

			UserList[TargetIndex].flags.Estupidez = 0;

			/* 'no need to crypt this */
			WriteDumbNoMore(TargetIndex);
			FlushBuffer(TargetIndex);
			InfoHechizo(UserIndex);

		}
	}

	/* ' <-------- Revive ----------> */
	if (Hechizos[HechizoIndex].Revivir == 1) {
		if (UserList[TargetIndex].flags.Muerto == 1) {

			/* 'Seguro de resurreccion (solo afecta a los hechizos, no al sacerdote ni al comando de GM) */
			if (UserList[TargetIndex].flags.SeguroResu) {
				WriteConsoleMsg(UserIndex,
						"¡El espíritu no tiene intenciones de regresar al mundo de los vivos!",
						FontTypeNames_FONTTYPE_INFO);
				HechizoCasteado = false;
				return;
			}

			/* 'No usar resu en mapas con ResuSinEfecto */
			if (MapInfo[UserList[TargetIndex].Pos.Map].ResuSinEfecto > 0) {
				WriteConsoleMsg(UserIndex,
						"¡Revivir no está permitido aquí! Retirate de la Zona si deseas utilizar el Hechizo.",
						FontTypeNames_FONTTYPE_INFO);
				HechizoCasteado = false;
				return;
			}

			/* 'No podemos resucitar si nuestra barra de energía no está llena. (GD: 29/04/07) */
			if (UserList[UserIndex].Stats.MaxSta != UserList[UserIndex].Stats.MinSta) {
				WriteConsoleMsg(UserIndex, "No puedes resucitar si no tienes tu barra de energía llena.",
						FontTypeNames_FONTTYPE_INFO);
				HechizoCasteado = false;
				return;
			}

			/* 'revisamos si necesita vara */
			if (UserList[UserIndex].clase == eClass_Mage) {
				if (UserList[UserIndex].Invent.WeaponEqpObjIndex > 0) {
					if (ObjData[UserList[UserIndex].Invent.WeaponEqpObjIndex].StaffPower
							< Hechizos[HechizoIndex].NeedStaff) {
						WriteConsoleMsg(UserIndex, "Necesitas un báculo mejor para lanzar este hechizo.",
								FontTypeNames_FONTTYPE_INFO);
						HechizoCasteado = false;
						return;
					}
				}
			} else if (UserList[UserIndex].clase == eClass_Bard) {
				if (UserList[UserIndex].Invent.AnilloEqpObjIndex != LAUDELFICO
						&& UserList[UserIndex].Invent.AnilloEqpObjIndex != LAUDMAGICO) {
					WriteConsoleMsg(UserIndex, "Necesitas un instrumento mágico para devolver la vida.",
							FontTypeNames_FONTTYPE_INFO);
					HechizoCasteado = false;
					return;
				}
			} else if (UserList[UserIndex].clase == eClass_Druid) {
				if (UserList[UserIndex].Invent.AnilloEqpObjIndex != FLAUTAELFICA
						&& UserList[UserIndex].Invent.AnilloEqpObjIndex != FLAUTAMAGICA) {
					WriteConsoleMsg(UserIndex, "Necesitas un instrumento mágico para devolver la vida.",
							FontTypeNames_FONTTYPE_INFO);
					HechizoCasteado = false;
					return;
				}
			}

			/* ' Chequea si el status permite ayudar al otro usuario */
			HechizoCasteado = CanSupportUser(UserIndex, TargetIndex, true);
			if (!HechizoCasteado) {
				return;
			}

			bool EraCriminal;
			EraCriminal = criminal(UserIndex);

			if (!criminal(TargetIndex)) {
				if (TargetIndex != UserIndex) {
					UserList[UserIndex].Reputacion.NobleRep = UserList[UserIndex].Reputacion.NobleRep + 500;
					if (UserList[UserIndex].Reputacion.NobleRep > MAXREP) {
						UserList[UserIndex].Reputacion.NobleRep = MAXREP;
					}
					WriteConsoleMsg(UserIndex, "¡Los Dioses te sonríen, has ganado 500 puntos de nobleza!",
							FontTypeNames_FONTTYPE_INFO);
				}
			}

			if (EraCriminal && !criminal(UserIndex)) {
				RefreshCharStatus(UserIndex);
			}

			/* 'Pablo Toxic Waste (GD: 29/04/07) */
			UserList[TargetIndex].Stats.MinAGU = 0;
			UserList[TargetIndex].flags.Sed = 1;
			UserList[TargetIndex].Stats.MinHam = 0;
			UserList[TargetIndex].flags.Hambre = 1;
			WriteUpdateHungerAndThirst(TargetIndex);
			InfoHechizo(UserIndex);
			UserList[TargetIndex].Stats.MinMAN = 0;
			UserList[TargetIndex].Stats.MinSta = 0;

			/* 'Agregado para quitar la penalización de vida en el ring y cambio de ecuacion. (NicoNZ) */
			if ((TriggerZonaPelea(UserIndex, TargetIndex) != eTrigger6_TRIGGER6_PERMITE)) {
				/* 'Solo saco vida si es User. no quiero que exploten GMs por ahi. */
				if (UserTienePrivilegio(UserIndex, PlayerType_User)) {
					UserList[UserIndex].Stats.MinHp = UserList[UserIndex].Stats.MinHp
							* (1 - UserList[TargetIndex].Stats.ELV * 0.015);
				}
			}

			if ((UserList[UserIndex].Stats.MinHp <= 0)) {
				UserDie(UserIndex);
				WriteConsoleMsg(UserIndex, "El esfuerzo de resucitar fue demasiado grande.",
						FontTypeNames_FONTTYPE_INFO);
				HechizoCasteado = false;
			} else {
				WriteConsoleMsg(UserIndex, "El esfuerzo de resucitar te ha debilitado.",
						FontTypeNames_FONTTYPE_INFO);
				HechizoCasteado = true;
			}

			if (UserList[TargetIndex].flags.Traveling == 1) {
				UserList[TargetIndex].Counters.goHome = 0;
				UserList[TargetIndex].flags.Traveling = 0;
				/* 'Call WriteConsoleMsg(TargetIndex, "Tu viaje ha sido cancelado.", FontTypeNames.FONTTYPE_FIGHT) */
				WriteMultiMessage(TargetIndex, eMessages_CancelHome);
			}

			RevivirUsuario(TargetIndex);
		} else {
			HechizoCasteado = false;
		}

	}

	/* ' <-------- Agrega Ceguera ----------> */
	if (Hechizos[HechizoIndex].Ceguera == 1) {
		if (UserIndex == TargetIndex) {
			WriteConsoleMsg(UserIndex, "No puedes atacarte a vos mismo.", FontTypeNames_FONTTYPE_FIGHT);
			return;
		}

		if (!PuedeAtacar(UserIndex, TargetIndex)) {
			return;
		}
		if (UserIndex != TargetIndex) {
			UsuarioAtacadoPorUsuario(UserIndex, TargetIndex);
		}

		InfoHechizo(UserIndex);
		HechizoCasteado = true;

		if (AnilloObjIndex > 0) {
			if (ObjData[AnilloObjIndex].ImpideCegar != 0) {
				WriteConsoleMsg(UserIndex, "Tu anillo rechaza los efectos de la ceguera.",
						FontTypeNames_FONTTYPE_FIGHT);
				WriteConsoleMsg(UserIndex, " ¡El hechizo no tiene efecto!", FontTypeNames_FONTTYPE_FIGHT);
				FlushBuffer(TargetIndex);
				return;
			}
		}

		UserList[TargetIndex].flags.Ceguera = 1;
		UserList[TargetIndex].Counters.Ceguera = IntervaloParalizado / 3;

		WriteBlind(TargetIndex);
		FlushBuffer(TargetIndex);

	}

	/* ' <-------- Agrega Estupidez (Aturdimiento) ----------> */
	if (Hechizos[HechizoIndex].Estupidez == 1) {
		if (UserIndex == TargetIndex) {
			WriteConsoleMsg(UserIndex, "No puedes atacarte a vos mismo.", FontTypeNames_FONTTYPE_FIGHT);
			return;
		}

		if (!PuedeAtacar(UserIndex, TargetIndex)) {
			return;
		}

		if (UserIndex != TargetIndex) {
			UsuarioAtacadoPorUsuario(UserIndex, TargetIndex);
		}

		InfoHechizo(UserIndex);
		HechizoCasteado = true;

		if (AnilloObjIndex > 0) {
			if (ObjData[AnilloObjIndex].ImpideAturdir != 0) {
				WriteConsoleMsg(UserIndex, "Tu anillo rechaza los efectos de la turbación.",
						FontTypeNames_FONTTYPE_FIGHT);
				WriteConsoleMsg(UserIndex, " ¡El hechizo no tiene efecto!", FontTypeNames_FONTTYPE_FIGHT);
				FlushBuffer(TargetIndex);
				return;
			}
		}

		if (UserList[TargetIndex].flags.Estupidez == 0) {
			UserList[TargetIndex].flags.Estupidez = 1;
			UserList[TargetIndex].Counters.Ceguera = IntervaloParalizado;
		}

		WriteDumb(TargetIndex);
		FlushBuffer(TargetIndex);

	}

}

void HechizoEstadoNPC(int NpcIndex, int SpellIndex, bool & HechizoCasteado, int UserIndex) {
	/* '*************************************************** */
	/* 'Autor: Unknown (orginal version) */
	/* 'Last Modification: 07/07/2008 */
	/* 'Handles the Spells that afect the Stats of an NPC */
	/* '04/13/2008 NicoNZ - Guardias Faccionarios pueden ser */
	/* 'removidos por users de su misma faccion. */
	/* '07/07/2008: NicoNZ - Solo se puede mimetizar con npcs si es druida */
	/* '*************************************************** */

	if (Hechizos[SpellIndex].Invisibilidad == 1) {
		InfoHechizo(UserIndex);
		Npclist[NpcIndex].flags.invisible = 1;
		HechizoCasteado = true;
	}

	if (Hechizos[SpellIndex].Envenena == 1) {
		if (!PuedeAtacarNPC(UserIndex, NpcIndex)) {
			HechizoCasteado = false;
			return;
		}
		NPCAtacado(NpcIndex, UserIndex);
		InfoHechizo(UserIndex);
		Npclist[NpcIndex].flags.Envenenado = 1;
		HechizoCasteado = true;
	}

	if (Hechizos[SpellIndex].CuraVeneno == 1) {
		InfoHechizo(UserIndex);
		Npclist[NpcIndex].flags.Envenenado = 0;
		HechizoCasteado = true;
	}

	if (Hechizos[SpellIndex].Maldicion == 1) {
		if (!PuedeAtacarNPC(UserIndex, NpcIndex)) {
			HechizoCasteado = false;
			return;
		}
		NPCAtacado(NpcIndex, UserIndex);
		InfoHechizo(UserIndex);
		Npclist[NpcIndex].flags.Maldicion = 1;
		HechizoCasteado = true;
	}

	if (Hechizos[SpellIndex].RemoverMaldicion == 1) {
		InfoHechizo(UserIndex);
		Npclist[NpcIndex].flags.Maldicion = 0;
		HechizoCasteado = true;
	}

	if (Hechizos[SpellIndex].Bendicion == 1) {
		InfoHechizo(UserIndex);
		Npclist[NpcIndex].flags.Bendicion = 1;
		HechizoCasteado = true;
	}

	if (Hechizos[SpellIndex].Paraliza == 1) {
		if (Npclist[NpcIndex].flags.AfectaParalisis == 0) {
			if (!PuedeAtacarNPC(UserIndex, NpcIndex, true)) {
				HechizoCasteado = false;
				return;
			}
			NPCAtacado(NpcIndex, UserIndex);
			InfoHechizo(UserIndex);
			Npclist[NpcIndex].flags.Paralizado = 1;
			Npclist[NpcIndex].flags.Inmovilizado = 0;
			Npclist[NpcIndex].Contadores.Paralisis = IntervaloParalizado;
			HechizoCasteado = true;
		} else {
			WriteConsoleMsg(UserIndex, "El NPC es inmune a este hechizo.", FontTypeNames_FONTTYPE_INFO);
			HechizoCasteado = false;
			return;
		}
	}

	if (Hechizos[SpellIndex].RemoverParalisis == 1) {
		if (Npclist[NpcIndex].flags.Paralizado == 1 || Npclist[NpcIndex].flags.Inmovilizado == 1) {
			if (Npclist[NpcIndex].MaestroUser == UserIndex) {
				InfoHechizo(UserIndex);
				Npclist[NpcIndex].flags.Paralizado = 0;
				Npclist[NpcIndex].Contadores.Paralisis = 0;
				HechizoCasteado = true;
			} else {
				if (Npclist[NpcIndex].NPCtype == eNPCType_GuardiaReal) {
					if (esArmada(UserIndex)) {
						InfoHechizo(UserIndex);
						Npclist[NpcIndex].flags.Paralizado = 0;
						Npclist[NpcIndex].Contadores.Paralisis = 0;
						HechizoCasteado = true;
						return;
					} else {
						WriteConsoleMsg(UserIndex,
								"Sólo puedes remover la parálisis de los Guardias si perteneces a su facción.",
								FontTypeNames_FONTTYPE_INFO);
						HechizoCasteado = false;
						return;
					}
				} else {
					if (Npclist[NpcIndex].NPCtype == eNPCType_Guardiascaos) {
						if (esCaos(UserIndex)) {
							InfoHechizo(UserIndex);
							Npclist[NpcIndex].flags.Paralizado = 0;
							Npclist[NpcIndex].Contadores.Paralisis = 0;
							HechizoCasteado = true;
							return;
						} else {
							WriteConsoleMsg(UserIndex,
									"Solo puedes remover la parálisis de los Guardias si perteneces a su facción.",
									FontTypeNames_FONTTYPE_INFO);
							HechizoCasteado = false;
							return;
						}
					}
				}
			}
		} else {
			WriteConsoleMsg(UserIndex, "Este NPC no está paralizado", FontTypeNames_FONTTYPE_INFO);
			HechizoCasteado = false;
			return;
		}
	}

	if (Hechizos[SpellIndex].Inmoviliza == 1) {
		if (Npclist[NpcIndex].flags.AfectaParalisis == 0) {
			if (!PuedeAtacarNPC(UserIndex, NpcIndex, true)) {
				HechizoCasteado = false;
				return;
			}
			NPCAtacado(NpcIndex, UserIndex);
			Npclist[NpcIndex].flags.Inmovilizado = 1;
			Npclist[NpcIndex].flags.Paralizado = 0;
			Npclist[NpcIndex].Contadores.Paralisis = IntervaloParalizado;
			InfoHechizo(UserIndex);
			HechizoCasteado = true;
		} else {
			WriteConsoleMsg(UserIndex, "El NPC es inmune al hechizo.", FontTypeNames_FONTTYPE_INFO);
		}
	}

	if (Hechizos[SpellIndex].Mimetiza == 1) {
		if (UserList[UserIndex].flags.Mimetizado == 1) {
			WriteConsoleMsg(UserIndex, "Ya te encuentras mimetizado. El hechizo no ha tenido efecto.",
					FontTypeNames_FONTTYPE_INFO);
			return;
		}

		if (UserList[UserIndex].flags.AdminInvisible == 1) {
			return;
		}

		if (UserList[UserIndex].clase == eClass_Druid) {
			/* 'copio el char original al mimetizado */

			UserList[UserIndex].CharMimetizado.body = UserList[UserIndex].Char.body;
			UserList[UserIndex].CharMimetizado.Head = UserList[UserIndex].Char.Head;
			UserList[UserIndex].CharMimetizado.CascoAnim = UserList[UserIndex].Char.CascoAnim;
			UserList[UserIndex].CharMimetizado.ShieldAnim = UserList[UserIndex].Char.ShieldAnim;
			UserList[UserIndex].CharMimetizado.WeaponAnim = UserList[UserIndex].Char.WeaponAnim;

			UserList[UserIndex].flags.Mimetizado = 1;

			/* 'ahora pongo lo del NPC. */
			UserList[UserIndex].Char.body = Npclist[NpcIndex].Char.body;
			UserList[UserIndex].Char.Head = Npclist[NpcIndex].Char.Head;
			UserList[UserIndex].Char.CascoAnim = NingunCasco;
			UserList[UserIndex].Char.ShieldAnim = NingunEscudo;
			UserList[UserIndex].Char.WeaponAnim = NingunArma;

			ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
					UserList[UserIndex].Char.heading, UserList[UserIndex].Char.WeaponAnim,
					UserList[UserIndex].Char.ShieldAnim, UserList[UserIndex].Char.CascoAnim);

		} else {
			WriteConsoleMsg(UserIndex, "Sólo los druidas pueden mimetizarse con criaturas.",
					FontTypeNames_FONTTYPE_INFO);
			return;
		}

		InfoHechizo(UserIndex);
		HechizoCasteado = true;
	}

}

void HechizoPropNPC(int SpellIndex, int NpcIndex, int UserIndex, bool & HechizoCasteado) {
	/* '*************************************************** */
	/* 'Autor: Unknown (orginal version) */
	/* 'Last Modification: 18/09/2010 */
	/* 'Handles the Spells that afect the Life NPC */
	/* '14/08/2007 Pablo (ToxicWaste) - Orden general. */
	/* '18/09/2010: ZaMa - Ahora valida si podes ayudar a un npc. */
	/* '*************************************************** */

	int dano;

	/* 'Salud */
	if (Hechizos[SpellIndex].SubeHP == 1) {

		HechizoCasteado = CanSupportNpc(UserIndex, NpcIndex);

		if (HechizoCasteado) {
			dano = RandomNumber(Hechizos[SpellIndex].MinHp, Hechizos[SpellIndex].MaxHp);
			dano = dano + Porcentaje(dano, 3 * UserList[UserIndex].Stats.ELV);

			InfoHechizo(UserIndex);
			Npclist[NpcIndex].Stats.MinHp = Npclist[NpcIndex].Stats.MinHp + dano;
			if (Npclist[NpcIndex].Stats.MinHp > Npclist[NpcIndex].Stats.MaxHp) {
				Npclist[NpcIndex].Stats.MinHp = Npclist[NpcIndex].Stats.MaxHp;
			}
			WriteConsoleMsg(UserIndex, "Has curado " + vb6::CStr(dano) + " puntos de vida a la criatura.",
					FontTypeNames_FONTTYPE_FIGHT);
		}

	} else if (Hechizos[SpellIndex].SubeHP == 2) {
		if (!PuedeAtacarNPC(UserIndex, NpcIndex)) {
			HechizoCasteado = false;
			return;
		}
		NPCAtacado(NpcIndex, UserIndex);
		dano = RandomNumber(Hechizos[SpellIndex].MinHp, Hechizos[SpellIndex].MaxHp);
		dano = dano + Porcentaje(dano, 3 * UserList[UserIndex].Stats.ELV);

		if (Hechizos[SpellIndex].StaffAffected) {
			if (UserList[UserIndex].clase == eClass_Mage) {
				if (UserList[UserIndex].Invent.WeaponEqpObjIndex > 0) {
					dano = (dano
							* (ObjData[UserList[UserIndex].Invent.WeaponEqpObjIndex].StaffDamageBonus + 70))
							/ 100;
					/* 'Aumenta dano segun el staff- */
					/* 'Dano = (Dano* (70 + BonifBáculo)) / 100 */
				} else {
					/* 'Baja dano a 70% del original */
					dano = dano * 0.7;
				}
			}
		}
		if (UserList[UserIndex].Invent.AnilloEqpObjIndex == LAUDELFICO
				|| UserList[UserIndex].Invent.AnilloEqpObjIndex == FLAUTAELFICA) {
			/* 'laud magico de los bardos */
			dano = dano * 1.04;
		}

		InfoHechizo(UserIndex);
		HechizoCasteado = true;

		if (Npclist[NpcIndex].flags.Snd2 > 0) {
			SendData(SendTarget_ToNPCArea, NpcIndex,
					dakara::protocol::server::BuildPlayWave(Npclist[NpcIndex].flags.Snd2, Npclist[NpcIndex].Pos.X,
							Npclist[NpcIndex].Pos.Y));
		}

		/* 'Quizas tenga defenza magica el NPC. Pablo (ToxicWaste) */
		dano = dano - Npclist[NpcIndex].Stats.defM;
		if (dano < 0) {
			dano = 0;
		}

		Npclist[NpcIndex].Stats.MinHp = Npclist[NpcIndex].Stats.MinHp - dano;
		WriteConsoleMsg(UserIndex, "¡Le has quitado " + vb6::CStr(dano) + " puntos de vida a la criatura!",
				FontTypeNames_FONTTYPE_FIGHT);
		CalcularDarExp(UserIndex, NpcIndex, dano);

		if (Npclist[NpcIndex].Stats.MinHp < 1) {
			Npclist[NpcIndex].Stats.MinHp = 0;
			MuereNpc(NpcIndex, UserIndex);
		}
	}

}

void InfoHechizo(int UserIndex) {
	/* '*************************************************** */
	/* 'Autor: Unknown (orginal version) */
	/* 'Last Modification: 25/07/2009 */
	/* '25/07/2009: ZaMa - Code improvements. */
	/* '25/07/2009: ZaMa - Now invisible admins magic sounds are not sent to anyone but themselves */
	/* '*************************************************** */
	int SpellIndex;
	int tUser;
	int tNPC;

	SpellIndex = UserList[UserIndex].flags.Hechizo;
	tUser = UserList[UserIndex].flags.TargetUser;
	tNPC = UserList[UserIndex].flags.TargetNPC;

	DecirPalabrasMagicas(Hechizos[SpellIndex].PalabrasMagicas, UserIndex);

	if (tUser > 0) {
		/* ' Los admins invisibles no producen sonidos ni fx's */
		if (UserList[UserIndex].flags.AdminInvisible == 1 && UserIndex == tUser) {
			EnviarDatosASlot(UserIndex,
					PacketToString(dakara::protocol::server::BuildCreateFX(UserList[tUser].Char.CharIndex, Hechizos[SpellIndex].FXgrh,
							Hechizos[SpellIndex].loops)));
			EnviarDatosASlot(UserIndex,
					PacketToString(dakara::protocol::server::BuildPlayWave(Hechizos[SpellIndex].WAV, UserList[tUser].Pos.X,
							UserList[tUser].Pos.Y)));
		} else {
			SendData(SendTarget_ToPCArea, tUser,
					dakara::protocol::server::BuildCreateFX(UserList[tUser].Char.CharIndex, Hechizos[SpellIndex].FXgrh,
							Hechizos[SpellIndex].loops));
			/* 'Esta linea faltaba. Pablo (ToxicWaste) */
			SendData(SendTarget_ToPCArea, tUser,
					dakara::protocol::server::BuildPlayWave(Hechizos[SpellIndex].WAV, UserList[tUser].Pos.X,
							UserList[tUser].Pos.Y));
		}
	} else if (tNPC > 0) {
		SendData(SendTarget_ToNPCArea, tNPC,
				dakara::protocol::server::BuildCreateFX(Npclist[tNPC].Char.CharIndex, Hechizos[SpellIndex].FXgrh,
						Hechizos[SpellIndex].loops));
		SendData(SendTarget_ToNPCArea, tNPC,
				dakara::protocol::server::BuildPlayWave(Hechizos[SpellIndex].WAV, Npclist[tNPC].Pos.X, Npclist[tNPC].Pos.Y));
	}

	if (tUser > 0) {
		if (UserIndex != tUser) {
			if (UserList[UserIndex].showName) {
				WriteConsoleMsg(UserIndex, Hechizos[SpellIndex].HechizeroMsg + " " + UserList[tUser].Name,
						FontTypeNames_FONTTYPE_FIGHT);
			} else {
				WriteConsoleMsg(UserIndex, Hechizos[SpellIndex].HechizeroMsg + " alguien.",
						FontTypeNames_FONTTYPE_FIGHT);
			}
			WriteConsoleMsg(tUser, UserList[UserIndex].Name + " " + Hechizos[SpellIndex].TargetMsg,
					FontTypeNames_FONTTYPE_FIGHT);
		} else {
			WriteConsoleMsg(UserIndex, Hechizos[SpellIndex].PropioMsg, FontTypeNames_FONTTYPE_FIGHT);
		}
	} else if (tNPC > 0) {
		WriteConsoleMsg(UserIndex, Hechizos[SpellIndex].HechizeroMsg + " " + "la criatura.",
				FontTypeNames_FONTTYPE_FIGHT);
	}

}

bool HechizoPropUsuario(int UserIndex) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Autor: Unknown (orginal version) */
	/* 'Last Modification: 28/04/2010 */
	/* '02/01/2008 Marcos (ByVal) - No permite tirar curar heridas a usuarios muertos. */
	/* '28/04/2010: ZaMa - Agrego Restricciones para ciudas respecto al estado atacable. */
	/* '*************************************************** */

	int SpellIndex;
	int dano = 0;
	int TargetIndex;

	SpellIndex = UserList[UserIndex].flags.Hechizo;
	TargetIndex = UserList[UserIndex].flags.TargetUser;

	if (UserList[TargetIndex].flags.Muerto) {
		WriteConsoleMsg(UserIndex, "No puedes lanzar este hechizo a un muerto.", FontTypeNames_FONTTYPE_INFO);
		return retval;
	}

	/* ' <-------- Aumenta Hambre ----------> */
	if (Hechizos[SpellIndex].SubeHam == 1) {

		InfoHechizo(UserIndex);

		dano = RandomNumber(Hechizos[SpellIndex].MinHam, Hechizos[SpellIndex].MaxHam);

		UserList[TargetIndex].Stats.MinHam = UserList[TargetIndex].Stats.MinHam + dano;
		if (UserList[TargetIndex].Stats.MinHam > UserList[TargetIndex].Stats.MaxHam) {
			UserList[TargetIndex].Stats.MinHam = UserList[TargetIndex].Stats.MaxHam;
		}

		if (UserIndex != TargetIndex) {
			WriteConsoleMsg(UserIndex,
					"Le has restaurado " + vb6::CStr(dano) + " puntos de hambre a " + UserList[TargetIndex].Name + ".",
					FontTypeNames_FONTTYPE_FIGHT);
			WriteConsoleMsg(TargetIndex,
					UserList[UserIndex].Name + " te ha restaurado " + vb6::CStr(dano) + " puntos de hambre.",
					FontTypeNames_FONTTYPE_FIGHT);
		} else {
			WriteConsoleMsg(UserIndex, "Te has restaurado " + vb6::CStr(dano) + " puntos de hambre.",
					FontTypeNames_FONTTYPE_FIGHT);
		}

		WriteUpdateHungerAndThirst(TargetIndex);

		/* ' <-------- Quita Hambre ----------> */
	} else if (Hechizos[SpellIndex].SubeHam == 2) {
		if (!PuedeAtacar(UserIndex, TargetIndex)) {
			return retval;
		}

		if (UserIndex != TargetIndex) {
			UsuarioAtacadoPorUsuario(UserIndex, TargetIndex);
		} else {
			return retval;
		}

		InfoHechizo(UserIndex);

		dano = RandomNumber(Hechizos[SpellIndex].MinHam, Hechizos[SpellIndex].MaxHam);

		UserList[TargetIndex].Stats.MinHam = UserList[TargetIndex].Stats.MinHam - dano;

		if (UserIndex != TargetIndex) {
			WriteConsoleMsg(UserIndex,
					"Le has quitado " + vb6::CStr(dano) + " puntos de hambre a " + UserList[TargetIndex].Name + ".",
					FontTypeNames_FONTTYPE_FIGHT);
			WriteConsoleMsg(TargetIndex,
					UserList[UserIndex].Name + " te ha quitado " + vb6::CStr(dano) + " puntos de hambre.",
					FontTypeNames_FONTTYPE_FIGHT);
		} else {
			WriteConsoleMsg(UserIndex, "Te has quitado " + vb6::CStr(dano) + " puntos de hambre.",
					FontTypeNames_FONTTYPE_FIGHT);
		}

		if (UserList[TargetIndex].Stats.MinHam < 1) {
			UserList[TargetIndex].Stats.MinHam = 0;
			UserList[TargetIndex].flags.Hambre = 1;
		}

		WriteUpdateHungerAndThirst(TargetIndex);
	}

	/* ' <-------- Aumenta Sed ----------> */
	if (Hechizos[SpellIndex].SubeSed == 1) {

		InfoHechizo(UserIndex);

		dano = RandomNumber(Hechizos[SpellIndex].MinSed, Hechizos[SpellIndex].MaxSed);

		UserList[TargetIndex].Stats.MinAGU = UserList[TargetIndex].Stats.MinAGU + dano;
		if (UserList[TargetIndex].Stats.MinAGU > UserList[TargetIndex].Stats.MaxAGU) {
			UserList[TargetIndex].Stats.MinAGU = UserList[TargetIndex].Stats.MaxAGU;
		}

		WriteUpdateHungerAndThirst(TargetIndex);

		if (UserIndex != TargetIndex) {
			WriteConsoleMsg(UserIndex,
					"Le has restaurado " + vb6::CStr(dano) + " puntos de sed a " + UserList[TargetIndex].Name + ".",
					FontTypeNames_FONTTYPE_FIGHT);
			WriteConsoleMsg(TargetIndex,
					UserList[UserIndex].Name + " te ha restaurado " + vb6::CStr(dano) + " puntos de sed.",
					FontTypeNames_FONTTYPE_FIGHT);
		} else {
			WriteConsoleMsg(UserIndex, "Te has restaurado " + vb6::CStr(dano) + " puntos de sed.",
					FontTypeNames_FONTTYPE_FIGHT);
		}

		/* ' <-------- Quita Sed ----------> */
	} else if (Hechizos[SpellIndex].SubeSed == 2) {

		if (!PuedeAtacar(UserIndex, TargetIndex)) {
			return retval;
		}

		if (UserIndex != TargetIndex) {
			UsuarioAtacadoPorUsuario(UserIndex, TargetIndex);
		}

		InfoHechizo(UserIndex);

		dano = RandomNumber(Hechizos[SpellIndex].MinSed, Hechizos[SpellIndex].MaxSed);

		UserList[TargetIndex].Stats.MinAGU = UserList[TargetIndex].Stats.MinAGU - dano;

		if (UserIndex != TargetIndex) {
			WriteConsoleMsg(UserIndex,
					"Le has quitado " + vb6::CStr(dano) + " puntos de sed a " + UserList[TargetIndex].Name + ".",
					FontTypeNames_FONTTYPE_FIGHT);
			WriteConsoleMsg(TargetIndex,
					UserList[UserIndex].Name + " te ha quitado " + vb6::CStr(dano) + " puntos de sed.",
					FontTypeNames_FONTTYPE_FIGHT);
		} else {
			WriteConsoleMsg(UserIndex, "Te has quitado " + vb6::CStr(dano) + " puntos de sed.",
					FontTypeNames_FONTTYPE_FIGHT);
		}

		if (UserList[TargetIndex].Stats.MinAGU < 1) {
			UserList[TargetIndex].Stats.MinAGU = 0;
			UserList[TargetIndex].flags.Sed = 1;
		}

		WriteUpdateHungerAndThirst(TargetIndex);

	}

	/* ' <-------- Aumenta Agilidad ----------> */
	if (Hechizos[SpellIndex].SubeAgilidad == 1) {

		/* ' Chequea si el status permite ayudar al otro usuario */
		if (!CanSupportUser(UserIndex, TargetIndex)) {
			return retval;
		}

		InfoHechizo(UserIndex);
		dano = RandomNumber(Hechizos[SpellIndex].MinAgilidad, Hechizos[SpellIndex].MaxAgilidad);

		UserList[TargetIndex].flags.DuracionEfecto = 1200;
		UserList[TargetIndex].Stats.UserAtributos[eAtributos_Agilidad] =
				UserList[TargetIndex].Stats.UserAtributos[eAtributos_Agilidad] + dano;
		if (UserList[TargetIndex].Stats.UserAtributos[eAtributos_Agilidad]
				> MinimoInt(MAXATRIBUTOS,
						UserList[TargetIndex].Stats.UserAtributosBackUP[eAtributos_Agilidad] * 2)) {
			UserList[TargetIndex].Stats.UserAtributos[eAtributos_Agilidad] = MinimoInt(MAXATRIBUTOS,
					UserList[TargetIndex].Stats.UserAtributosBackUP[eAtributos_Agilidad] * 2);
		}

		UserList[TargetIndex].flags.TomoPocion = true;
		WriteUpdateDexterity(TargetIndex);

		/* ' <-------- Quita Agilidad ----------> */
	} else if (Hechizos[SpellIndex].SubeAgilidad == 2) {

		if (!PuedeAtacar(UserIndex, TargetIndex)) {
			return retval;
		}

		if (UserIndex != TargetIndex) {
			UsuarioAtacadoPorUsuario(UserIndex, TargetIndex);
		}

		InfoHechizo(UserIndex);

		UserList[TargetIndex].flags.TomoPocion = true;
		dano = RandomNumber(Hechizos[SpellIndex].MinAgilidad, Hechizos[SpellIndex].MaxAgilidad);
		UserList[TargetIndex].flags.DuracionEfecto = 700;
		UserList[TargetIndex].Stats.UserAtributos[eAtributos_Agilidad] =
				UserList[TargetIndex].Stats.UserAtributos[eAtributos_Agilidad] - dano;
		if (UserList[TargetIndex].Stats.UserAtributos[eAtributos_Agilidad] < MINATRIBUTOS) {
			UserList[TargetIndex].Stats.UserAtributos[eAtributos_Agilidad] = MINATRIBUTOS;
		}

		WriteUpdateDexterity(TargetIndex);
	}

	/* ' <-------- Aumenta Fuerza ----------> */
	if (Hechizos[SpellIndex].SubeFuerza == 1) {

		/* ' Chequea si el status permite ayudar al otro usuario */
		if (!CanSupportUser(UserIndex, TargetIndex)) {
			return retval;
		}

		InfoHechizo(UserIndex);
		dano = RandomNumber(Hechizos[SpellIndex].MinFuerza, Hechizos[SpellIndex].MaxFuerza);

		UserList[TargetIndex].flags.DuracionEfecto = 1200;

		UserList[TargetIndex].Stats.UserAtributos[eAtributos_Fuerza] =
				UserList[TargetIndex].Stats.UserAtributos[eAtributos_Fuerza] + dano;
		if (UserList[TargetIndex].Stats.UserAtributos[eAtributos_Fuerza]
				> MinimoInt(MAXATRIBUTOS,
						UserList[TargetIndex].Stats.UserAtributosBackUP[eAtributos_Fuerza] * 2)) {
			UserList[TargetIndex].Stats.UserAtributos[eAtributos_Fuerza] = MinimoInt(MAXATRIBUTOS,
					UserList[TargetIndex].Stats.UserAtributosBackUP[eAtributos_Fuerza] * 2);
		}

		UserList[TargetIndex].flags.TomoPocion = true;
		WriteUpdateStrenght(TargetIndex);

		/* ' <-------- Quita Fuerza ----------> */
	} else if (Hechizos[SpellIndex].SubeFuerza == 2) {

		if (!PuedeAtacar(UserIndex, TargetIndex)) {
			return retval;
		}

		if (UserIndex != TargetIndex) {
			UsuarioAtacadoPorUsuario(UserIndex, TargetIndex);
		}

		InfoHechizo(UserIndex);

		UserList[TargetIndex].flags.TomoPocion = true;

		dano = RandomNumber(Hechizos[SpellIndex].MinFuerza, Hechizos[SpellIndex].MaxFuerza);
		UserList[TargetIndex].flags.DuracionEfecto = 700;
		UserList[TargetIndex].Stats.UserAtributos[eAtributos_Fuerza] =
				UserList[TargetIndex].Stats.UserAtributos[eAtributos_Fuerza] - dano;
		if (UserList[TargetIndex].Stats.UserAtributos[eAtributos_Fuerza] < MINATRIBUTOS) {
			UserList[TargetIndex].Stats.UserAtributos[eAtributos_Fuerza] = MINATRIBUTOS;
		}

		WriteUpdateStrenght(TargetIndex);
	}

	/* ' <-------- Cura salud ----------> */
	if (Hechizos[SpellIndex].SubeHP == 1) {

		/* 'Verifica que el usuario no este muerto */
		if (UserList[TargetIndex].flags.Muerto == 1) {
			WriteConsoleMsg(UserIndex, "¡El usuario está muerto!", FontTypeNames_FONTTYPE_INFO);
			return retval;
		}

		/* ' Chequea si el status permite ayudar al otro usuario */
		if (!CanSupportUser(UserIndex, TargetIndex)) {
			return retval;
		}

		dano = RandomNumber(Hechizos[SpellIndex].MinHp, Hechizos[SpellIndex].MaxHp);
		dano = dano + Porcentaje(dano, 3 * UserList[UserIndex].Stats.ELV);

		InfoHechizo(UserIndex);

		UserList[TargetIndex].Stats.MinHp = UserList[TargetIndex].Stats.MinHp + dano;
		if (UserList[TargetIndex].Stats.MinHp > UserList[TargetIndex].Stats.MaxHp) {
			UserList[TargetIndex].Stats.MinHp = UserList[TargetIndex].Stats.MaxHp;
		}

		WriteUpdateHP(TargetIndex);

		if (UserIndex != TargetIndex) {
			WriteConsoleMsg(UserIndex,
					"Le has restaurado " + vb6::CStr(dano) + " puntos de vida a " + UserList[TargetIndex].Name + ".",
					FontTypeNames_FONTTYPE_FIGHT);
			WriteConsoleMsg(TargetIndex,
					UserList[UserIndex].Name + " te ha restaurado " + vb6::CStr(dano) + " puntos de vida.",
					FontTypeNames_FONTTYPE_FIGHT);
		} else {
			WriteConsoleMsg(UserIndex, "Te has restaurado " + vb6::CStr(dano) + " puntos de vida.",
					FontTypeNames_FONTTYPE_FIGHT);
		}

		/* ' <-------- Quita salud (Dana) ----------> */
	} else if (Hechizos[SpellIndex].SubeHP == 2) {

		if (UserIndex == TargetIndex) {
			WriteConsoleMsg(UserIndex, "No puedes atacarte a vos mismo.", FontTypeNames_FONTTYPE_FIGHT);
			return retval;
		}

		dano = RandomNumber(Hechizos[SpellIndex].MinHp, Hechizos[SpellIndex].MaxHp);

		dano = dano + Porcentaje(dano, 3 * UserList[UserIndex].Stats.ELV);

		if (Hechizos[SpellIndex].StaffAffected) {
			if (UserList[UserIndex].clase == eClass_Mage) {
				if (UserList[UserIndex].Invent.WeaponEqpObjIndex > 0) {
					dano = (dano
							* (ObjData[UserList[UserIndex].Invent.WeaponEqpObjIndex].StaffDamageBonus + 70))
							/ 100;
				} else {
					/* 'Baja dano a 70% del original */
					dano = dano * 0.7;
				}
			}
		}

		if (UserList[UserIndex].Invent.AnilloEqpObjIndex == LAUDELFICO
				|| UserList[UserIndex].Invent.AnilloEqpObjIndex == FLAUTAELFICA) {
			/* 'laud magico de los bardos */
			dano = dano * 1.04;
		}

		/* 'cascos antimagia */
		if ((UserList[TargetIndex].Invent.CascoEqpObjIndex > 0)) {
			dano = dano
					- RandomNumber(ObjData[UserList[TargetIndex].Invent.CascoEqpObjIndex].DefensaMagicaMin,
							ObjData[UserList[TargetIndex].Invent.CascoEqpObjIndex].DefensaMagicaMax);
		}

		/* 'anillos */
		if ((UserList[TargetIndex].Invent.AnilloEqpObjIndex > 0)) {
			dano = dano
					- RandomNumber(ObjData[UserList[TargetIndex].Invent.AnilloEqpObjIndex].DefensaMagicaMin,
							ObjData[UserList[TargetIndex].Invent.AnilloEqpObjIndex].DefensaMagicaMax);
		}

		if (dano < 0) {
			dano = 0;
		}

		if (!PuedeAtacar(UserIndex, TargetIndex)) {
			return retval;
		}

		if (UserIndex != TargetIndex) {
			UsuarioAtacadoPorUsuario(UserIndex, TargetIndex);
		}

		InfoHechizo(UserIndex);

		UserList[TargetIndex].Stats.MinHp = UserList[TargetIndex].Stats.MinHp - dano;

		WriteUpdateHP(TargetIndex);

		WriteConsoleMsg(UserIndex,
				"Le has quitado " + vb6::CStr(dano) + " puntos de vida a " + UserList[TargetIndex].Name + ".",
				FontTypeNames_FONTTYPE_FIGHT);
		WriteConsoleMsg(TargetIndex, UserList[UserIndex].Name + " te ha quitado " + vb6::CStr(dano) + " puntos de vida.",
				FontTypeNames_FONTTYPE_FIGHT);

		/* 'Muere */
		if (UserList[TargetIndex].Stats.MinHp < 1) {

			if (UserList[TargetIndex].flags.AtacablePor != UserIndex) {
				/* 'Store it! */
				StoreFrag(UserIndex, TargetIndex);
				ContarMuerte(TargetIndex, UserIndex);
			}

			UserList[TargetIndex].Stats.MinHp = 0;
			ActStats(TargetIndex, UserIndex);
			UserDie(TargetIndex);
		}

	}

	/* ' <-------- Aumenta Mana ----------> */
	if (Hechizos[SpellIndex].SubeMana == 1) {

		InfoHechizo(UserIndex);
		UserList[TargetIndex].Stats.MinMAN = UserList[TargetIndex].Stats.MinMAN + dano;
		if (UserList[TargetIndex].Stats.MinMAN > UserList[TargetIndex].Stats.MaxMAN) {
			UserList[TargetIndex].Stats.MinMAN = UserList[TargetIndex].Stats.MaxMAN;
		}

		WriteUpdateMana(TargetIndex);

		if (UserIndex != TargetIndex) {
			WriteConsoleMsg(UserIndex,
					"Le has restaurado " + vb6::CStr(dano) + " puntos de maná a " + UserList[TargetIndex].Name + ".",
					FontTypeNames_FONTTYPE_FIGHT);
			WriteConsoleMsg(TargetIndex,
					UserList[UserIndex].Name + " te ha restaurado " + vb6::CStr(dano) + " puntos de maná.",
					FontTypeNames_FONTTYPE_FIGHT);
		} else {
			WriteConsoleMsg(UserIndex, "Te has restaurado " + vb6::CStr(dano) + " puntos de maná.",
					FontTypeNames_FONTTYPE_FIGHT);
		}

		/* ' <-------- Quita Mana ----------> */
	} else if (Hechizos[SpellIndex].SubeMana == 2) {
		if (!PuedeAtacar(UserIndex, TargetIndex)) {
			return retval;
		}

		if (UserIndex != TargetIndex) {
			UsuarioAtacadoPorUsuario(UserIndex, TargetIndex);
		}

		InfoHechizo(UserIndex);

		if (UserIndex != TargetIndex) {
			WriteConsoleMsg(UserIndex,
					"Le has quitado " + vb6::CStr(dano) + " puntos de maná a " + UserList[TargetIndex].Name + ".",
					FontTypeNames_FONTTYPE_FIGHT);
			WriteConsoleMsg(TargetIndex,
					UserList[UserIndex].Name + " te ha quitado " + vb6::CStr(dano) + " puntos de maná.",
					FontTypeNames_FONTTYPE_FIGHT);
		} else {
			WriteConsoleMsg(UserIndex, "Te has quitado " + vb6::CStr(dano) + " puntos de maná.",
					FontTypeNames_FONTTYPE_FIGHT);
		}

		UserList[TargetIndex].Stats.MinMAN = UserList[TargetIndex].Stats.MinMAN - dano;
		if (UserList[TargetIndex].Stats.MinMAN < 1) {
			UserList[TargetIndex].Stats.MinMAN = 0;
		}

		WriteUpdateMana(TargetIndex);

	}

	/* ' <-------- Aumenta Stamina ----------> */
	if (Hechizos[SpellIndex].SubeSta == 1) {
		InfoHechizo(UserIndex);
		UserList[TargetIndex].Stats.MinSta = UserList[TargetIndex].Stats.MinSta + dano;
		if (UserList[TargetIndex].Stats.MinSta > UserList[TargetIndex].Stats.MaxSta) {
			UserList[TargetIndex].Stats.MinSta = UserList[TargetIndex].Stats.MaxSta;
		}

		WriteUpdateSta(TargetIndex);

		if (UserIndex != TargetIndex) {
			WriteConsoleMsg(UserIndex,
					"Le has restaurado " + vb6::CStr(dano) + " puntos de energía a " + UserList[TargetIndex].Name + ".",
					FontTypeNames_FONTTYPE_FIGHT);
			WriteConsoleMsg(TargetIndex,
					UserList[UserIndex].Name + " te ha restaurado " + vb6::CStr(dano) + " puntos de energía.",
					FontTypeNames_FONTTYPE_FIGHT);
		} else {
			WriteConsoleMsg(UserIndex, "Te has restaurado " + vb6::CStr(dano) + " puntos de energía.",
					FontTypeNames_FONTTYPE_FIGHT);
		}

		/* ' <-------- Quita Stamina ----------> */
	} else if (Hechizos[SpellIndex].SubeSta == 2) {
		if (!PuedeAtacar(UserIndex, TargetIndex)) {
			return retval;
		}

		if (UserIndex != TargetIndex) {
			UsuarioAtacadoPorUsuario(UserIndex, TargetIndex);
		}

		InfoHechizo(UserIndex);

		if (UserIndex != TargetIndex) {
			WriteConsoleMsg(UserIndex,
					"Le has quitado " + vb6::CStr(dano) + " puntos de energía a " + UserList[TargetIndex].Name + ".",
					FontTypeNames_FONTTYPE_FIGHT);
			WriteConsoleMsg(TargetIndex,
					UserList[UserIndex].Name + " te ha quitado " + vb6::CStr(dano) + " puntos de energía.",
					FontTypeNames_FONTTYPE_FIGHT);
		} else {
			WriteConsoleMsg(UserIndex, "Te has quitado " + vb6::CStr(dano) + " puntos de energía.",
					FontTypeNames_FONTTYPE_FIGHT);
		}

		UserList[TargetIndex].Stats.MinSta = UserList[TargetIndex].Stats.MinSta - dano;

		if (UserList[TargetIndex].Stats.MinSta < 1) {
			UserList[TargetIndex].Stats.MinSta = 0;
		}

		WriteUpdateSta(TargetIndex);

	}

	retval = true;

	FlushBuffer(TargetIndex);

	return retval;
}

bool CanSupportUser(int CasterIndex, int TargetIndex, bool DoCriminal) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 28/04/2010 */
	/* 'Checks if caster can cast support magic on target user. */
	/* '*************************************************** */

	/* ' Te podes curar a vos mismo */
	if (CasterIndex == TargetIndex) {
		retval = true;
		return retval;
	}

	/* ' No podes ayudar si estas en consulta */
	if (UserList[CasterIndex].flags.EnConsulta) {
		WriteConsoleMsg(CasterIndex, "No puedes ayudar usuarios mientras estas en consulta.",
				FontTypeNames_FONTTYPE_INFO);
		return retval;
	}

	/* ' Si estas en la arena, esta todo permitido */
	if (TriggerZonaPelea(CasterIndex, TargetIndex) == eTrigger6_TRIGGER6_PERMITE) {
		retval = true;
		return retval;
	}

	/* ' Victima criminal? */
	if (criminal(TargetIndex)) {

		/* ' Casteador Ciuda? */
		if (!criminal(CasterIndex)) {

			/* ' Armadas no pueden ayudar */
			if (esArmada(CasterIndex)) {
				WriteConsoleMsg(CasterIndex,
						"Los miembros del ejército real no pueden ayudar a los criminales.",
						FontTypeNames_FONTTYPE_INFO);
				return retval;
			}

			/* ' Si el ciuda tiene el seguro puesto no puede ayudar */
			if (UserList[CasterIndex].flags.Seguro) {
				WriteConsoleMsg(CasterIndex,
						"Para ayudar criminales debes sacarte el seguro ya que te volverás criminal como ellos.",
						FontTypeNames_FONTTYPE_INFO);
				return retval;
			} else {
				/* ' Penalizacion */
				if (DoCriminal) {
					VolverCriminal(CasterIndex);
				} else {
					DisNobAuBan(CasterIndex, UserList[CasterIndex].Reputacion.NobleRep * 0.5, 10000);
				}
			}
		}

		/* ' Victima ciuda o army */
	} else {
		/* ' Casteador es caos? => No Pueden ayudar ciudas */
		if (esCaos(CasterIndex)) {
			WriteConsoleMsg(CasterIndex,
					"Los miembros de la legión oscura no pueden ayudar a los ciudadanos.",
					FontTypeNames_FONTTYPE_INFO);
			return retval;

			/* ' Casteador ciuda/army? */
		} else if (!criminal(CasterIndex)) {

			/* ' Esta en estado atacable? */
			if (UserList[TargetIndex].flags.AtacablePor > 0) {

				/* ' No esta atacable por el casteador? */
				if (UserList[TargetIndex].flags.AtacablePor != CasterIndex) {

					/* ' Si es armada no puede ayudar */
					if (esArmada(CasterIndex)) {
						WriteConsoleMsg(CasterIndex,
								"Los miembros del ejército real no pueden ayudar a ciudadanos en estado atacable.",
								FontTypeNames_FONTTYPE_INFO);
						return retval;
					}

					/* ' Seguro puesto? */
					if (UserList[CasterIndex].flags.Seguro) {
						WriteConsoleMsg(CasterIndex,
								"Para ayudar ciudadanos en estado atacable debes sacarte el seguro, pero te puedes volver criminal.",
								FontTypeNames_FONTTYPE_INFO);
						return retval;
					} else {
						DisNobAuBan(CasterIndex, UserList[CasterIndex].Reputacion.NobleRep * 0.5, 10000);
					}
				}
			}

		}
	}

	retval = true;

	return retval;
}

void UpdateUserHechizos(bool UpdateAll, int UserIndex, int Slot) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	int LoopC;

	/* 'Actualiza un solo slot */
	if (!UpdateAll) {
		/* 'Actualiza el inventario */
		if (UserList[UserIndex].Stats.UserHechizos[Slot] > 0) {
			ChangeUserHechizo(UserIndex, Slot, UserList[UserIndex].Stats.UserHechizos[Slot]);
		} else {
			ChangeUserHechizo(UserIndex, Slot, 0);
		}
	} else {
		/* 'Actualiza todos los slots */
		for (LoopC = (1); LoopC <= (MAXUSERHECHIZOS); LoopC++) {
			/* 'Actualiza el inventario */
			if (UserList[UserIndex].Stats.UserHechizos[LoopC] > 0) {
				ChangeUserHechizo(UserIndex, LoopC, UserList[UserIndex].Stats.UserHechizos[LoopC]);
			} else {
				ChangeUserHechizo(UserIndex, LoopC, 0);
			}
		}
	}

}

bool CanSupportNpc(int CasterIndex, int TargetIndex) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 18/09/2010 */
	/* 'Checks if caster can cast support magic on target Npc. */
	/* '*************************************************** */

	int OwnerIndex;

	OwnerIndex = Npclist[TargetIndex].Owner;

	/* ' Si no tiene dueno puede */
	if (OwnerIndex == 0) {
		retval = true;
		return retval;
	}

	/* ' Puede hacerlo si es su propio npc */
	if (CasterIndex == OwnerIndex) {
		retval = true;
		return retval;
	}

	/* ' No podes ayudar si estas en consulta */
	if (UserList[CasterIndex].flags.EnConsulta) {
		WriteConsoleMsg(CasterIndex, "No puedes ayudar npcs mientras estas en consulta.",
				FontTypeNames_FONTTYPE_INFO);
		return retval;
	}

	/* ' Si estas en la arena, esta todo permitido */
	if (TriggerZonaPelea(CasterIndex, OwnerIndex) == eTrigger6_TRIGGER6_PERMITE) {
		retval = true;
		return retval;
	}

	/* ' Victima criminal? */
	if (criminal(OwnerIndex)) {
		/* ' Victima caos? */
		if (esCaos(OwnerIndex)) {
			/* ' Atacante caos? */
			if (esCaos(CasterIndex)) {
				/* ' No podes ayudar a un npc de un caos si sos caos */
				WriteConsoleMsg(CasterIndex,
						"No puedes ayudar npcs que están luchando contra un miembro de tu facción.",
						FontTypeNames_FONTTYPE_INFO);
				return retval;
			}
		}

		/* ' Uno es caos y el otro no, o la victima es pk, entonces puede ayudar al npc */
		retval = true;
		return retval;

		/* ' Victima ciuda */
	} else {
		/* ' Atacante ciuda? */
		if (!criminal(CasterIndex)) {
			/* ' Atacante armada? */
			if (esArmada(CasterIndex)) {
				/* ' Victima armada? */
				if (esArmada(OwnerIndex)) {
					/* ' No podes ayudar a un npc de un armada si sos armada */
					WriteConsoleMsg(CasterIndex,
							"No puedes ayudar npcs que están luchando contra un miembro de tu facción.",
							FontTypeNames_FONTTYPE_INFO);
					return retval;
				}
			}

			/* ' Uno es armada y el otro ciuda, o los dos ciudas, puede atacar si no tiene seguro */
			if (UserList[CasterIndex].flags.Seguro) {
				WriteConsoleMsg(CasterIndex,
						"Para ayudar a criaturas que luchan contra ciudadanos debes sacarte el seguro.",
						FontTypeNames_FONTTYPE_INFO);
				return retval;

				/* ' ayudo al npc sin seguro, se convierte en atacable */
			} else {
				ToogleToAtackable(CasterIndex, OwnerIndex, true);
				retval = true;
				return retval;
			}

		}

		/* ' Atacante criminal y victima ciuda, entonces puede ayudar al npc */
		retval = true;
		return retval;

	}
}

void ChangeUserHechizo(int UserIndex, int Slot, int Hechizo) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	UserList[UserIndex].Stats.UserHechizos[Slot] = Hechizo;
	WriteChangeSpellSlot(UserIndex, Slot);
}

void DesplazarHechizo(int UserIndex, int Dire, int HechizoDesplazado) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	if ((Dire != 1 && Dire != -1)) {
		return;
	}
	if (!(HechizoDesplazado >= 1 && HechizoDesplazado <= MAXUSERHECHIZOS)) {
		return;
	}

	int TempHechizo;

	/* 'Mover arriba */
	if (Dire == 1) {
		if (HechizoDesplazado == 1) {
			WriteConsoleMsg(UserIndex, "No puedes mover el hechizo en esa dirección.",
					FontTypeNames_FONTTYPE_INFO);
			return;
		} else {
			TempHechizo = UserList[UserIndex].Stats.UserHechizos[HechizoDesplazado];
			UserList[UserIndex].Stats.UserHechizos[HechizoDesplazado] =
					UserList[UserIndex].Stats.UserHechizos[HechizoDesplazado - 1];
			UserList[UserIndex].Stats.UserHechizos[HechizoDesplazado - 1] = TempHechizo;
		}
		/* 'mover abajo */
	} else {
		if (HechizoDesplazado == MAXUSERHECHIZOS) {
			WriteConsoleMsg(UserIndex, "No puedes mover el hechizo en esa dirección.",
					FontTypeNames_FONTTYPE_INFO);
			return;
		} else {
			TempHechizo = UserList[UserIndex].Stats.UserHechizos[HechizoDesplazado];
			UserList[UserIndex].Stats.UserHechizos[HechizoDesplazado] =
					UserList[UserIndex].Stats.UserHechizos[HechizoDesplazado + 1];
			UserList[UserIndex].Stats.UserHechizos[HechizoDesplazado + 1] = TempHechizo;
		}
	}

}

void DisNobAuBan(int UserIndex, int NoblePts, int BandidoPts) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	/* 'disminuye la nobleza NoblePts puntos y aumenta el bandido BandidoPts puntos */
	bool EraCriminal;
	EraCriminal = criminal(UserIndex);

	/* 'Si estamos en la arena no hacemos nada */
	if (MapData[UserList[UserIndex].Pos.Map][UserList[UserIndex].Pos.X][UserList[UserIndex].Pos.Y].trigger
			== 6) {
		return;
	}

	if (UserTieneAlgunPrivilegios(UserIndex, PlayerType_User, PlayerType_Consejero)) {
		/* 'pierdo nobleza... */
		UserList[UserIndex].Reputacion.NobleRep = UserList[UserIndex].Reputacion.NobleRep - NoblePts;
		if (UserList[UserIndex].Reputacion.NobleRep < 0) {
			UserList[UserIndex].Reputacion.NobleRep = 0;
		}

		/* 'gano bandido... */
		UserList[UserIndex].Reputacion.BandidoRep = UserList[UserIndex].Reputacion.BandidoRep + BandidoPts;
		if (UserList[UserIndex].Reputacion.BandidoRep > MAXREP) {
			UserList[UserIndex].Reputacion.BandidoRep = MAXREP;
		}
		/* 'Call WriteNobilityLost(UserIndex) */
		WriteMultiMessage(UserIndex, eMessages_NobilityLost);
		if (criminal(UserIndex)) {
			if (UserList[UserIndex].Faccion.ArmadaReal == 1) {
				ExpulsarFaccionReal(UserIndex);
			}
		}
	}

	if (!EraCriminal && criminal(UserIndex)) {
		RefreshCharStatus(UserIndex);
	}
}
