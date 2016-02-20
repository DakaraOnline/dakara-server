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

#include <cmath>

#include "Party.h"

clsParty::clsParty() {
	p_expTotal = 0;
	p_Fundador = 0;
	p_CantMiembros = 0;
	p_SumaNivelesElevados = 0;
	p_members.redim(1, PARTY_MAXMEMBERS);
}

clsParty::~clsParty() {
}

/* '' */
/* ' Sets the new p_sumaniveleselevados to the party. */
/* ' */
/* ' @param lvl Specifies reference to user level */
/* ' @remarks When a user level up and he is in a party, we update p_sumaNivelesElavados so the formula still works. */
void clsParty::UpdateSumaNivelesElevados(int Lvl) {
	/* '************************************************* */
	/* 'Author: Marco Vanotti (MarKoxX) */
	/* 'Last modified: 11/24/09 */
	/* '11/24/09: Pato - Change the exponent to a variable with the exponent */
	/* '************************************************* */
	p_SumaNivelesElevados = p_SumaNivelesElevados - (std::pow((Lvl - 1), ExponenteNivelParty))
			+ std::pow(Lvl, ExponenteNivelParty);
}

int clsParty::MiExperiencia(int UserIndex) {
	int retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 11/27/09 */
	/* 'Last Modification By: Budi */
	/* ' - 09/29/07 Experience is round to the biggest number less than that number */
	/* ' - 09/29/07 Now experience is a real-number */
	/* ' - 11/27/09 Arreglé el Out of Range. */
	/* '*************************************************** */
	/* 'Me dice cuanta experiencia tengo colectada ya en la party */
	int i;
	i = 1;

	while (i <= PARTY_MAXMEMBERS && p_members[i].UserIndex != UserIndex) {
		i = i + 1;
	}

	if (i <= PARTY_MAXMEMBERS) {
		retval = vb6::Fix(p_members[i].Experiencia);
		/* 'esto no deberia pasar :p */
	} else {
		retval = -1;
	}

	return retval;
}

void clsParty::ObtenerExito(int ExpGanada, int mapa, int X, int Y) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 07/04/08 */
	/* 'Last Modification By: Marco Vanotti (MarKoxX) */
	/* ' - 09/29/07 New formula for calculating the experience point of each user */
	/* ' - 09/29/07 Experience is round to the biggest number less than that number */
	/* ' - 09/29/07 Now experience is a real-number */
	/* ' - 04/04/08 Ahora antes de calcular la experiencia a X usuario se fija si ese usuario existe (MarKoxX) */
	/* ' - 07/04/08 New formula to calculate Experience for each user. (MarKoxX) */
	/* '*************************************************** */
	/* 'Se produjo un evento que da experiencia en la wp referenciada */
	int i;
	int UI;
	double expThisUser;

	p_expTotal = p_expTotal + ExpGanada;

	for (i = (1); i <= (PARTY_MAXMEMBERS); i++) {
		UI = p_members[i].UserIndex;
		if (UI > 0) {
			/* ' Formula: Exp* (Nivel ^ ExponenteNivelParty) / sumadeNivelesElevados */
			expThisUser = vb6::CDbl(
					ExpGanada * (std::pow(UserList[p_members[i].UserIndex].Stats.ELV, ExponenteNivelParty))
							/ p_SumaNivelesElevados);

			if (mapa == UserList[UI].Pos.Map && UserList[UI].flags.Muerto == 0) {
				if (Distance(UserList[UI].Pos.X, UserList[UI].Pos.Y, X, Y) <= PARTY_MAXDISTANCIA) {
					p_members[i].Experiencia = p_members[i].Experiencia + expThisUser;
					if (p_members[i].Experiencia < 0) {
						p_members[i].Experiencia = 0;
					}
					if (PARTY_EXPERIENCIAPORGOLPE) {
						UserList[UI].Stats.Exp = UserList[UI].Stats.Exp + vb6::Fix(expThisUser);
						if (UserList[UI].Stats.Exp > MAXEXP) {
							UserList[UI].Stats.Exp = MAXEXP;
						}
						CheckUserLevel(UI);
						WriteUpdateUserStats(UI);
					}
				}
			}
		}
	}

}

void clsParty::MandarMensajeAConsola(std::string texto, std::string Sender) {
	/* 'feo feo, muy feo acceder a senddata desde aca, pero BUEEEEEEEEEEE... */
	int i;

	for (i = (1); i <= (PARTY_MAXMEMBERS); i++) {
		if (p_members[i].UserIndex > 0) {
			WriteConsoleMsg(p_members[i].UserIndex, " [" + Sender + "] " + texto,
					FontTypeNames_FONTTYPE_PARTY);
		}
	}

}

bool clsParty::EsPartyLeader(int UserIndex) {
	bool retval;
	retval = (UserIndex == p_Fundador);
	return retval;
}

bool clsParty::NuevoMiembro(int UserIndex) {
	bool retval = false;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 07/04/08 */
	/* 'Last Modification By: Marco Vanotti (MarKoxX) */
	/* ' - 09/29/07 There is no level prohibition (Tavo) */
	/* ' - 07/04/08 Added const ExponenteNivelParty. (MarKoxX) */
	/* '*************************************************** */

	int i;
	i = 1;
	while (i <= PARTY_MAXMEMBERS && p_members[i].UserIndex > 0) {
		i = i + 1;
	}

	if (i <= PARTY_MAXMEMBERS) {
		p_members[i].Experiencia = 0;
		p_members[i].UserIndex = UserIndex;
		retval = true;
		p_CantMiembros = p_CantMiembros + 1;
		p_SumaNivelesElevados = p_SumaNivelesElevados
				+ (std::pow(UserList[UserIndex].Stats.ELV, ExponenteNivelParty));
	} else {
		retval = false;
	}

	return retval;
}

bool clsParty::SaleMiembro(int UserIndex) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 07/04/08 */
	/* 'Last Modification By: Marco Vanotti (MarKoxX) */
	/* ' - 09/29/07 Experience is round to the biggest number less than that number */
	/* ' - 09/29/07 Now experience is a real-number (Tavo) */
	/* ' - 07/04/08 Added const ExponenteNivelParty. (MarKoxX) */
	/* '11/03/2010: ZaMa - Ahora no le dice al lider que salio de su propia party, y optimice con with. */
	/* '*************************************************** */
	/* 'el valor de retorno representa si se disuelve la party */
	int i;
	int j;
	int MemberIndex;

	i = 1;
	retval = false;
	while (i <= PARTY_MAXMEMBERS && p_members[i].UserIndex != UserIndex) {
		i = i + 1;
	}

	if (i == 1) {
		/* 'sale el founder, la party se disuelve */
		retval = true;
		MandarMensajeAConsola("El líder disuelve la party.", "Servidor");

		for (j = (PARTY_MAXMEMBERS); ((-1) > 0) ? (j <= (1)) : (j >= (1)); j = j + (-1)) {

			if (p_members[j].UserIndex > 0) {

				/* ' No envia el mensaje al lider */
				if (j != 1) {
					WriteConsoleMsg(p_members[j].UserIndex,
							"Abandonas la party liderada por " + UserList[p_members[1].UserIndex].Name + ".",
							FontTypeNames_FONTTYPE_PARTY);
				}

				WriteConsoleMsg(p_members[j].UserIndex,
						"Durante la misma has conseguido " + vb6::CStr(vb6::Fix(p_members[j].Experiencia))
								+ " puntos de experiencia.", FontTypeNames_FONTTYPE_PARTY);

				if (!PARTY_EXPERIENCIAPORGOLPE) {
					UserList[p_members[j].UserIndex].Stats.Exp = UserList[p_members[j].UserIndex].Stats.Exp
							+ vb6::Fix(p_members[j].Experiencia);
					if (UserList[p_members[j].UserIndex].Stats.Exp > MAXEXP) {
						UserList[p_members[j].UserIndex].Stats.Exp = MAXEXP;
					}
					CheckUserLevel(p_members[j].UserIndex);
					WriteUpdateUserStats(p_members[j].UserIndex);
				}

				MandarMensajeAConsola(UserList[p_members[j].UserIndex].Name + " abandona la party.",
						"Servidor");

				UserList[p_members[j].UserIndex].PartyIndex = 0;
				p_CantMiembros = p_CantMiembros - 1;
				p_SumaNivelesElevados = p_SumaNivelesElevados
						- std::pow(UserList[UserIndex].Stats.ELV, ExponenteNivelParty);
				p_members[j].UserIndex = 0;
				p_members[j].Experiencia = 0;

			}

		}
	} else {
		if (i <= PARTY_MAXMEMBERS) {

			MemberIndex = p_members[i].UserIndex;

			if (!PARTY_EXPERIENCIAPORGOLPE) {
				UserList[MemberIndex].Stats.Exp = UserList[MemberIndex].Stats.Exp
						+ vb6::Fix(p_members[i].Experiencia);
				if (UserList[MemberIndex].Stats.Exp > MAXEXP) {
					UserList[MemberIndex].Stats.Exp = MAXEXP;
				}

				CheckUserLevel(MemberIndex);
				WriteUpdateUserStats(MemberIndex);
			}

			MandarMensajeAConsola(UserList[MemberIndex].Name + " abandona la party.", "Servidor");
			/* 'TODO: Revisar que esto este bien, y no este faltando/sobrando un mensaje, ahora solo los estoy corrigiendo */
			WriteConsoleMsg(MemberIndex,
					"Durante la misma has conseguido " + vb6::CStr(vb6::Fix(p_members[i].Experiencia))
							+ " puntos de experiencia.", FontTypeNames_FONTTYPE_PARTY);

			p_CantMiembros = p_CantMiembros - 1;
			p_SumaNivelesElevados = p_SumaNivelesElevados
					- std::pow(UserList[UserIndex].Stats.ELV, ExponenteNivelParty);
			MemberIndex = 0;
			p_members[i].Experiencia = 0;
			p_members[i].UserIndex = 0;
			CompactMemberList();
		}
	}

	return retval;
}

bool clsParty::HacerLeader(int UserIndex) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 09/29/07 */
	/* 'Last Modification By: Lucas Tavolaro Ortiz (Tavo) */
	/* ' - 09/29/07 There is no level prohibition */
	/* '*************************************************** */
	int i;
	int OldLeader;
	double oldExp;
	int UserIndexIndex;

	UserIndexIndex = 0;
	retval = true;

	for (i = (1); i <= (PARTY_MAXMEMBERS); i++) {
		if (p_members[i].UserIndex > 0) {
			if (p_members[i].UserIndex == UserIndex) {
				UserIndexIndex = i;
			}
		}
	}

	if (UserIndexIndex == 0) {
		/* 'catastrofe! esto no deberia pasar nunca! pero como es AO.... :p */
		LogError("INCONSISTENCIA DE PARTIES");
		std::cerr << ("INCONSISTENCIA DE PARTIES en HacerLeader") << std::endl;
		SendData(SendTarget_ToAdmins, 0,
				dakara::protocol::server::BuildConsoleMsg(
						"¡¡¡Inconsistencia de parties en HACERLEADER (UII = 0), AVISE A UN PROGRAMADOR ESTO ES UNA CATASTROFE!!!!",
						FontTypeNames_FONTTYPE_GUILD));
		retval = false;
		return retval;
	}

	/* 'aca esta todo bien y doy vuelta las collections */
	OldLeader = p_members[1].UserIndex;
	oldExp = p_members[1].Experiencia;

	/* 'que en realdiad es el userindex, pero no quiero inconsistencias moviendo experiencias */
	p_members[1].UserIndex = p_members[UserIndexIndex].UserIndex;
	p_members[1].Experiencia = p_members[UserIndexIndex].Experiencia;

	p_members[UserIndexIndex].UserIndex = OldLeader;
	p_members[UserIndexIndex].Experiencia = oldExp;

	p_Fundador = p_members[1].UserIndex;

	/* 'no need to compact */
	return retval;
}

void clsParty::ObtenerMiembrosOnline(std::vector<int> & MemberList) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 09/29/07 */
	/* 'Last Modification By: Marco Vanotti (MarKoxX) */
	/* ' - 09/29/07 Experience is round to the biggest number less than that number */
	/* ' - 09/29/07 Now experience is a real-number (Tavo) */
	/* ' - 08/18/08 Now TotalExperience is fixed (MarKoxX) */
	/* ' - 11/27/09 Rehice la función, ahora devuelve el array con los UI online (Budi) */
	/* '*************************************************** */

	int i;

	for (i = (1); i <= (PARTY_MAXMEMBERS); i++) {
		if (p_members[i].UserIndex > 0) {
			MemberList.push_back(p_members[i].UserIndex);
		}
	}
}

int clsParty::ObtenerExperienciaTotal() {
	int retval;
	/* '*************************************************** */
	/* 'Author: Budi */
	/* 'Last Modification: 11/27/09 */
	/* 'Retrieves the total experience acumulated in the party */
	/* '*************************************************** */
	retval = p_expTotal;
	return retval;
}

bool clsParty::PuedeEntrar(int UserIndex, std::string razon) {
	bool retval;
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 09/29/07 */
	/* 'Last Modification By: Lucas Tavolaro Ortiz (Tavo) */
	/* ' - 09/29/07 There is no level prohibition */
	/* '*************************************************** */
	/* 'DEFINE LAS REGLAS DEL JUEGO PARA DEJAR ENTRAR A MIEMBROS */
	bool esArmada;
	bool esCaos;
//	int MyLevel;
	int i;
	bool rv;
	int UI;

	rv = true;
	esArmada = (UserList[UserIndex].Faccion.ArmadaReal == 1);
	esCaos = (UserList[UserIndex].Faccion.FuerzasCaos == 1);
//	MyLevel = UserList[UserIndex].Stats.ELV;

	rv = Distancia(UserList[p_members[1].UserIndex].Pos, UserList[UserIndex].Pos) <= MAXDISTANCIAINGRESOPARTY;
	if (rv) {
		rv = (p_members[PARTY_MAXMEMBERS].UserIndex == 0);
		if (rv) {
			for (i = (1); i <= (PARTY_MAXMEMBERS); i++) {
				UI = p_members[i].UserIndex;
				/* 'pongo los casos que evitarian que pueda entrar */
				/* 'aspirante armada en party crimi */
				if (UI > 0) {
					if (esArmada && criminal(UI)) {
						razon = "Los miembros del ejército real no entran a una party con criminales.";
						rv = false;
					}
					/* 'aspirante caos en party ciuda */
					if (esCaos && !criminal(UI)) {
						razon = "Los miembros de la legión oscura no entran a una party con ciudadanos.";
						rv = false;
					}
					/* 'aspirante crimi en party armada */
					if (UserList[UI].Faccion.ArmadaReal == 1 && criminal(UserIndex)) {
						razon = "Los criminales no entran a parties con miembros del ejército real.";
						rv = false;
					}
					/* 'aspirante ciuda en party caos */
					if (UserList[UI].Faccion.FuerzasCaos == 1 && !criminal(UserIndex)) {
						razon = "Los ciudadanos no entran a parties con miembros de la legión oscura.";
						rv = false;
					}

					/* 'violate una programacion estructurada */
					if (!rv) {
						break; /* FIXME: EXIT FOR */
					}
				}
			}
		} else {
			razon = "La mayor cantidad de miembros es " + vb6::CStr(PARTY_MAXMEMBERS);
		}
	} else {
		/* '¿Con o sin nombre? */
		razon = "El usuario " + UserList[UserIndex].Name + " se encuentra muy lejos.";
	}

	retval = rv;

	return retval;
}

void clsParty::FlushExperiencia() {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: 09/29/07 */
	/* 'Last Modification By: Lucas Tavolaro Ortiz (Tavo) */
	/* ' - 09/29/07 Experience is round to the biggest number less than that number */
	/* ' - 09/29/07 Now experience is a real-number */
	/* '*************************************************** */
	/* 'esta funcion se invoca frente a cerradas del servidor. Flushea la experiencia */
	/* 'acumulada a los usuarios. */

	int i;
	/* 'esto sirve SOLO cuando acumulamos la experiencia! */
	if (!PARTY_EXPERIENCIAPORGOLPE) {
		for (i = (1); i <= (PARTY_MAXMEMBERS); i++) {
			if (p_members[i].UserIndex > 0) {
				if (p_members[i].Experiencia > 0) {
					UserList[p_members[i].UserIndex].Stats.Exp = UserList[p_members[i].UserIndex].Stats.Exp
							+ vb6::Fix(p_members[i].Experiencia);
					if (UserList[p_members[i].UserIndex].Stats.Exp > MAXEXP) {
						UserList[p_members[i].UserIndex].Stats.Exp = MAXEXP;
					}
					CheckUserLevel(p_members[i].UserIndex);
				} else {
					if (vb6::Abs(UserList[p_members[i].UserIndex].Stats.Exp)
							> vb6::Abs(vb6::Fix(p_members[i].Experiencia))) {
						UserList[p_members[i].UserIndex].Stats.Exp =
								UserList[p_members[i].UserIndex].Stats.Exp
										+ vb6::Fix(p_members[i].Experiencia);
					} else {
						UserList[p_members[i].UserIndex].Stats.Exp = 0;
					}
				}
				p_members[i].Experiencia = 0;
				WriteUpdateUserStats(p_members[i].UserIndex);
			}
		}
	}

}

void clsParty::CompactMemberList() {
	int i;
	int freeIndex = 0;
	i = 1;
	while (i <= PARTY_MAXMEMBERS) {
		if (p_members[i].UserIndex == 0 && freeIndex == 0) {
			freeIndex = i;
		} else if (p_members[i].UserIndex > 0 && freeIndex > 0) {
			p_members[freeIndex].Experiencia = p_members[i].Experiencia;
			p_members[freeIndex].UserIndex = p_members[i].UserIndex;
			p_members[i].UserIndex = 0;
			p_members[i].Experiencia = 0;
			/* 'muevo el de la pos i a freeindex */
			i = freeIndex;
			freeIndex = 0;
		}
		i = i + 1;
	}

}

int clsParty::CantMiembros() {
	int retval;
	retval = p_CantMiembros;
	return retval;
}
