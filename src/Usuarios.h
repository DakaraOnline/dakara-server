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

#ifndef USUARIOS_H
#define USUARIOS_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

void ActStats(int VictimIndex, int AttackerIndex);

void RevivirUsuario(int UserIndex);

void ToggleBoatBody(int UserIndex);

void ChangeUserChar(int UserIndex, int body, int Head, int heading, int Arma, int Escudo, int casco);

int GetWeaponAnim(int UserIndex, int ObjIndex);

void EnviarFama(int UserIndex);

void EraseUserChar(int UserIndex, bool IsAdminInvisible);

void RefreshCharStatus(int UserIndex);

int GetNickColor(int UserIndex);

bool MakeUserChar(bool toMap, int sndIndex, int UserIndex, int Map, int X, int Y, bool ButIndex = false);

/* '' */
/* ' Checks if the user gets the next level. */
/* ' */
/* ' @param UserIndex Specifies reference to user */

void CheckUserLevel(int UserIndex);

bool PuedeAtravesarAgua(int UserIndex);

void MoveUserChar(int UserIndex, eHeading nHeading);

eHeading InvertHeading(eHeading nHeading);

void ChangeUserInv(int UserIndex, int Slot, struct UserOBJ & Object);

int NextOpenCharIndex();

std::size_t NextOpenUser();

void SendUserStatsTxt(int sendIndex, int UserIndex);

/* # IF ConUpTime THEN */
/* # END IF */

void SendUserMiniStatsTxt(int sendIndex, int UserIndex);

void SendUserMiniStatsTxtFromChar(int sendIndex, std::string charName);

void SendUserInvTxt(int sendIndex, int UserIndex);

void SendUserInvTxtFromChar(int sendIndex, std::string charName);

void SendUserSkillsTxt(int sendIndex, int UserIndex);

bool EsMascotaCiudadano(int NpcIndex, int UserIndex);

void NPCAtacado(int NpcIndex, int UserIndex);

bool PuedeApunalar(int UserIndex);

bool PuedeAcuchillar(int UserIndex);

void SubirSkill(int UserIndex, int Skill, bool Acerto);

/* '' */
/* ' Muere un usuario */
/* ' */
/* ' @param UserIndex  Indice del usuario que muere */
/* ' */

void UserDie(int UserIndex);

void ContarMuerte(int Muerto, int Atacante);

void Tilelibre(struct WorldPos & Pos, struct WorldPos & nPos, struct Obj & Obj, bool PuedeAgua,
		bool PuedeTierra);

void WarpUserChar(int UserIndex, int Map, int X, int Y, bool FX, bool Teletransported = bool());

void WarpMascotas(int UserIndex);

void WarpMascota(int UserIndex, int PetIndex);

/* '' */
/* ' Se inicia la salida de un usuario. */
/* ' */
/* ' @param    UserIndex   El index del usuario que va a salir */

void CerrarUserIndexIniciar(int UserIndex);

/* '' */
/* ' Cancels the exit of a user. If it's disconnected it's reset. */
/* ' */
/* ' @param    UserIndex   The index of the user whose exit is being reset. */

void CancelExit(int UserIndex);

/* 'CambiarNick: Cambia el Nick de un slot. */
/* ' */
/* 'UserIndex: Quien ejecutó la orden */
/* 'UserIndexDestino: SLot del usuario destino, a quien cambiarle el nick */
/* 'NuevoNick: Nuevo nick de UserIndexDestino */
void CambiarNick(int UserIndex, int UserIndexDestino, std::string NuevoNick);

void SendUserStatsTxtOFF(int sendIndex, std::string Nombre);

/* # IF ConUpTime THEN */
/* # END IF */

void SendUserOROTxtFromChar(int sendIndex, std::string charName);

void VolverCriminal(int UserIndex);

void VolverCiudadano(int UserIndex);

/* '' */
/* 'Checks if a given body index is a boat or not. */
/* ' */
/* '@param body    The body index to bechecked. */
/* '@return    True if the body is a boat, false otherwise. */

bool BodyIsBoat(int body);

void SetInvisible(int UserIndex, int userCharIndex, bool invisible);

void SetConsulatMode(int UserIndex);

bool IsArena(int UserIndex);

void PerdioNpc(int UserIndex, bool CheckPets = true);

void ApropioNpc(int UserIndex, int NpcIndex);

std::string GetDireccion(int UserIndex, int OtherUserIndex);

bool SameFaccion(int UserIndex, int OtherUserIndex);

int FarthestPet(int UserIndex);

/* '' */
/* ' Set the EluSkill value at the skill. */
/* ' */
/* ' @param UserIndex  Specifies reference to user */
/* ' @param Skill      Number of the skill to check */
/* ' @param Allocation True If the motive of the modification is the allocation, False if the skill increase by training */

void CheckEluSkill(int UserIndex, int Skill, bool Allocation);

bool HasEnoughItems(int UserIndex, int ObjIndex, int Amount);

int TotalOfferItems(int ObjIndex, int UserIndex);

int getMaxInventorySlots(int UserIndex);

void goHome(int UserIndex);

bool ToogleToAtackable(int UserIndex, int OwnerIndex, bool StealingNpc = true);

void setHome(int UserIndex, eCiudad newHome, int NpcIndex);

int GetHomeArrivalTime(int UserIndex);

void HomeArrival(int UserIndex);

#endif
