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

#ifndef ADMIN_H
#define ADMIN_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

struct tMotd {
	std::string texto;
	std::string Formato;
};

extern vb6::array<struct tMotd> MOTD;
extern bool EnviarPopupOfTheDay;
extern std::string PopupOfTheDayMessage;

struct tAPuestas {
	int Ganancias;
	int Perdidas;
	int Jugadas;
};
extern struct tAPuestas Apuestas;

extern int tInicioServer;

/* 'INTERVALOS */
extern int SanaIntervaloSinDescansar;
extern int StaminaIntervaloSinDescansar;
extern int SanaIntervaloDescansar;
extern int StaminaIntervaloDescansar;
extern int IntervaloSed;
extern int IntervaloHambre;
extern int IntervaloVeneno;
extern int IntervaloParalizado;
extern const int IntervaloParalizadoReducido;
extern int IntervaloInvisible;
extern int IntervaloFrio;
extern int IntervaloWavFx;
extern int IntervaloLanzaHechizo;
extern int IntervaloNPCPuedeAtacar;
extern int IntervaloNPCAI;
extern int IntervaloInvocacion;
/* '[Nacho] */
extern int IntervaloOculto;
extern int IntervaloUserPuedeAtacar;
extern int IntervaloGolpeUsar;
extern int IntervaloMagiaGolpe;
extern int IntervaloGolpeMagia;
extern int IntervaloUserPuedeCastear;
extern int IntervaloUserPuedeTrabajar;
extern int IntervaloParaConexion;
/* '[Gonzalo] */
extern int IntervaloCerrarConexion;
extern int IntervaloUserPuedeUsar;
extern int IntervaloFlechasCazadores;
extern int IntervaloPuedeSerAtacado;
extern int IntervaloAtacable;
extern int IntervaloOwnedNpc;
extern int IntervaloImprimirEnConsola;

/* 'BALANCE */

extern int PorcentajeRecuperoMana;

extern int MinutosWs;
extern int MinutosGuardarUsuarios;
extern int MinutosMotd;
extern int Puerto;
extern int MAX_PACKETS_PER_ITER;

extern int BootDelBackUp;
extern bool Lloviendo;
extern bool DeNoche;

bool VersionOK(std::string Ver);

void ReSpawnOrigPosNpcs();

void WorldSave();

/* # IF SeguridadAlkon THEN */
/* # END IF */

void ServerShutdown();

void PurgarPenas();

void Encarcelar(int UserIndex, int Minutos, std::string GmName = "");

void BorrarUsuario(std::string UserName);

bool BANCheck(std::string Name);

bool PersonajeExiste(std::string Name);

bool UnBan(std::string Name);

bool MD5ok(std::string md5formateado);

void MD5sCarga(clsIniManager& leerSini);

void BanIpAgrega(std::string ip);

bool BanIpBuscar(std::string ip);

bool BanIpQuita(std::string ip);

void BanIpGuardar();

void BanIpCargar();

void ActualizaEstadisticasWeb();

PlayerType UserDarPrivilegioLevel(std::string Name);

bool UserTieneMasPrivilegiosQue(int UserIndexIzquierdo, int UserIndexDerecho);

bool UserTieneMasPrivilegiosQue(std::string UserNameIzquierdo, int UserIndexDerecho);

bool UserTieneIgualPrivilegiosQue(int UserIndexIzquierdo, int UserIndexDerecho);

inline bool UserTienePrivilegio(int UserIndex, PlayerType p) {
	return UserList[UserIndex].flags.Privilegios2 & p;
}

inline bool UserTieneAlgunPrivilegios(int UserIndex, PlayerType p1) {
	return UserTienePrivilegio(UserIndex, p1);
}

inline bool UserTieneAlgunPrivilegios(int UserIndex, PlayerType p1, PlayerType p2) {
	return UserTienePrivilegio(UserIndex, p1) || UserTienePrivilegio(UserIndex, p2);
}

inline bool UserTieneAlgunPrivilegios(int UserIndex, PlayerType p1, PlayerType p2, PlayerType p3) {
	return UserTienePrivilegio(UserIndex, p1) || UserTienePrivilegio(UserIndex, p2) || UserTienePrivilegio(UserIndex, p3);
}

inline bool UserTieneAlgunPrivilegios(int UserIndex, PlayerType p1, PlayerType p2, PlayerType p3, PlayerType p4) {
	return UserTienePrivilegio(UserIndex, p1) || UserTienePrivilegio(UserIndex, p2) || UserTienePrivilegio(UserIndex, p3) || UserTienePrivilegio(UserIndex, p4);
}

inline bool UserTieneAlgunPrivilegios(int UserIndex, PlayerType p1, PlayerType p2, PlayerType p3, PlayerType p4, PlayerType p5) {
	return UserTienePrivilegio(UserIndex, p1) || UserTienePrivilegio(UserIndex, p2) || UserTienePrivilegio(UserIndex, p3) || UserTienePrivilegio(UserIndex, p4) || UserTienePrivilegio(UserIndex, p5);
}

/** Suma el privilegio a los ya existentes.
 *
 */
void UserAsignarPrivilegios(int UserIndex, PlayerType p);

void UserQuitarPrivilegios(int UserIndex, PlayerType p);

void UserResetPrivilegios(int UserIndex);

void BanCharacter(int bannerUserIndex, std::string UserName, std::string Reason);

#endif
