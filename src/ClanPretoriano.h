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


#if 0

#ifndef CLSCLANPRETORIANO_H
#define CLSCLANPRETORIANO_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

class clsClanPretoriano {

/* '#################### */
/* ' Pretorians Map Vars (Only used for the default map) */
private: struct WorldPos LeftSpawnPos;
private: struct WorldPos RightSpawnPos;

/* '#################### */
/* 'Actions and spells */

/* ' King */
 private:

 private:

/* ' Healer */
 private:

 private:

/* ' SpellCaster */
 private:

 private:

/* ' Thief */
 private:

 private:

/* ' Indicates wether the clan is active or not */
private: bool ClanActive;

/* ' Max distance for the thief to steal */

/* ' Countdown to break the SpellCaster's wand */
private: int WandBreakCounter;
/* ' Number from wich starts countdown */
/* ' Min HP needed for SpellCaster to start countdown */

/* ' Time in which the king hasn't done anything */
private: int KingIdleTime;
/* ' Time needed for respawning an ally (Aprox 5 min) */

/* ' Max distance to follow a user, or separate from team */
/* ' Number of total clan members */

/* ' Indicates clan map and king position */
private: struct WorldPos CenterPos;
/* ' Indicates if the clan is spawned after being defeated */
private: bool RespawnClan;
/* ' The number of clan members still alive */
private: int ClanMembersAlive;

 private:
 struct tPretorianData {
 int NpcIndex;
 ePretorianAI NPCAI;
};

/* ' Indice del clan pretoriano */
private: int ClanIndex;

/* ' Contiene los index de los miembros del clan. */
private: std::vector<struct tPretorianData> Pretorianos;

 public:
 bool SpawnClan(int mapa, int X, int Y, int PretoClanIndex, bool Respawning = false);
 
 private:
 bool IsValidSpawnArea();
 
 private:
 void InitializePretoriansVars();
 
 private:
 void SpawnPretorian(struct WorldPos & SpawnPos, int PretorianAI, int PretoIndex, bool IsKing = false);
 
 private:
 int RandomTallHead();
 
 private:
 int RandomShortHead();
 
 public:
 void PerformPretorianAI(int NpcIndex);
 
 private:
 int GetPretorianAI(int NpcIndex);
 
 public:
 void AI_King(int NpcIndex);
 
 private:
 int KingBestTarget(int NpcIndex, int & Accion);
 
 private:
 void KingPerformAction(int NpcIndex, int BestTarget, int Accion);
 
 private:
 void KingMeleeAttack(vb6::Variant NpcIndex);
 
 private:
 void KingReviveAlly(int NpcIndex);
 
 public:
 void AI_Healer(int NpcIndex);
 
 private:
 int HealerBestTarget(int NpcIndex, int & Accion);
 
 private:
 void HealerPerformAction(int NpcIndex, int BestTarget, int Accion, bool & CanMove);
 
 private:
 void HealerMove(int NpcIndex);
 
 public:
 void AI_SpellCaster(int NpcIndex);
 
 private:
 bool SpellCasterSacrifice(int NpcIndex);
 
 private:
 int SpellCasterBestTarget(int NpcIndex, int & Accion);
 
 private:
 void SpellCasterPerformAction(int NpcIndex, int BestTarget, int Accion);
 
 private:
 void SpellCasterMove(int NpcIndex, int BestTarget);
 
 private:
 void SpellCasterDestroyWand(int NpcIndex, int SpellIndex);
 
 private:
 void DealWandDamage(int NpcIndex, int SpellIndex);
 
 private:
 void DealWandDamageToPets(int NpcIndex, int UserIndex, int SpellIndex);
 
 public:
 void AI_SwordMaster(int NpcIndex);
 
 private:
 int SwordMasterBestTarget(int NpcIndex);
 
 private:
 void SwordMasterMove(int NpcIndex, int BestTarget);
 
 private:
 void SwordMasterAttack(int NpcIndex);
 
 public:
 void AI_Shooter(int NpcIndex);
 
 private:
 int ShooterBestTarget(int NpcIndex);
 
 private:
 void ShooterMove(int NpcIndex, int BestTarget);
 
 private:
 void AI_Thief(int NpcIndex);
 
 private:
 int ThiefBestTarget(int NpcIndex, int & Action);
 
 private:
 void ThiefPerfomAction(int NpcIndex, int BestTarget, int Action);
 
 private:
 bool SnatchItem(int NpcIndex, int TargetIndex, int Slot);
 
 private:
 bool ThiefStealITem(int NpcIndex, int TargetIndex, int Slot);
 
 private:
 void ThiefTurnInvisible(int NpcIndex, bool TurnVisible);
 
 private:
 bool TargetClose(struct WorldPos & Pos);
 
 private:
 int CheckNearUserPets(int NpcIndex, int UserIndex);
 
 private:
 bool EsClaseMagica(int UserIndex);
 
 private:
 void GreedyWalkTo(int NpcIndex, int TargetMap, int TargetX, int TargetY);
 
 private:
 void MoveFailed(int NpcIndex);
 
 private:
 void ReturnToCenter(int NpcIndex);
 
 private:
 bool FarFromTeam(vb6::Variant NpcIndex);
 
 private:
 bool UserReachable(int NpcIndex, int UserIndex);
 
 private:
 bool InVisionRange(int UserIndex, int X, int Y, bool ExtendedRange = false);
 
 private:
 bool InVisionRangeNpc(int NpcIndex, int X, int Y, bool ExtendedRange = false);
 
 private:
 bool UserAtacable(int UserIndex, bool CheckVisibility = true, bool AttackAdmin = true);
 
 private:
 int UserDistance(int UserIndex, int X, int Y);
 
 private:
 int NpcDistance(int NpcIndex, int X, int Y);
 
 public:
 void MuerePretoriano(int NpcIndex);
 
 private:
 int AllyParalyzed(int NpcIndex, bool ExtendedRange);
 
 private:
 int AllyInjured(int NpcIndex);
 
 private:
 int AllyPoisoned(int NpcIndex);
 
 private:
 int AllyDead();
 
 public:
 bool CanAtackMember(int NpcIndex);
 
 public:
 int ClanMap();

 public:
 bool Active();

 public:
 void DeleteClan();
 
};
#endif

#endif

