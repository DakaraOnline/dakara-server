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

#if 0

#include "clsClanPretoriano.h"
#include "allheaders.h"

/* '#################### */
/* ' Pretorians Map Vars (Only used for the default map) */

/* '#################### */
/* 'Actions and spells */

/* ' King */

/* ' Healer */

/* ' SpellCaster */

/* ' Thief */

/* ' Indicates wether the clan is active or not */

/* ' Max distance for the thief to steal */
static const int THIEF_STEAL_DISTANCE = 2;

/* ' Countdown to break the SpellCaster's wand */
/* ' Number from wich starts countdown */
static const int MAX_WAND_BREAK_VALUE = 6;
/* ' Min HP needed for SpellCaster to start countdown */
static const int START_COUNTDOWN_MIN_HP = 750;

/* ' Time in which the king hasn't done anything */
/* ' Time needed for respawning an ally (Aprox 5 min) */
static const int ALLY_RESPAWN_TIME = 2000;

/* ' Max distance to follow a user, or separate from team */
static const int MAX_DISTANCE = 14;
/* ' Number of total clan members */
static const int NRO_PRETORIANOS = 9;

/* ' Indicates clan map and king position */
/* ' Indicates if the clan is spawned after being defeated */
/* ' The number of clan members still alive */

/* ' Indice del clan pretoriano */

/* ' Contiene los index de los miembros del clan. */

 bool clsClanPretoriano::SpawnClan(int mapa, int X, int Y, int PretoClanIndex, bool Respawning) {
 bool retval;
 /* '******************************************************** */
 /* 'Author: EL OSO */
 /* 'Inicializa el clan Pretoriano. */
 /* 'Last Modify Date: 21/09/2010 */
 /* '22/06/2006: (Nacho) - Seteamos cuantos NPCs creamos */
 /* '21/09/2010: ZaMa - Reescribi la funcion, ahora se le pasa las coordenadas de respawn */
 /* '******************************************************** */
 /* FIXME: ON ERROR GOTO ErrHandler */
 
 struct WorldPos nPos;
 int PretoIndex;
 
 /* ' Initial pos */
 CenterPos.Map = mapa;
 CenterPos.X = X;
 CenterPos.Y = Y;
 
 Pretorianos.resize(0);
 Pretorianos.resize(1 + NRO_PRETORIANOS);
 
 ClanIndex = PretoClanIndex;
 
 /* ' Check valid spawn place only if it's the first time */
  if (!Respawning) {
  /* ' The clan only respawns on pretorian map */
   if (mapa == MAPA_PRETORIANO) {
   RespawnClan = true;
   InitializePretoriansVars();
   
   /* ' Default coordinates, override admin choise */
   CenterPos = LeftSpawnPos;
   
   /* ' Check if it's a valid area to respawn */
   } else {
   if (!IsValidSpawnArea()) {
   return retval;
   }
  }
 }
 
 nPos = CenterPos;
 
 /* ' Spawn clan members */
 ClanMembersAlive = NRO_PRETORIANOS;
 
 /* ' Spawn King */
 PretoIndex = PretoIndex+1;
 SpawnPretorian(nPos, ePretorianAI_King, PretoIndex, true);
 
 /* ' Spawn 2 Healers */
 PretoIndex = PretoIndex+1;
 nPos.X = nPos.X+3;
 SpawnPretorian(nPos, ePretorianAI_Healer, PretoIndex);
 
 PretoIndex = PretoIndex+1;
 nPos.X = nPos.X-6;
 SpawnPretorian(nPos, ePretorianAI_Healer, PretoIndex);
 
 /* ' Spawn 3 Sword Masters */
 PretoIndex = PretoIndex+1;
 nPos.Y = nPos.Y+3;
 SpawnPretorian(nPos, ePretorianAI_SwordMaster, PretoIndex);
 
 PretoIndex = PretoIndex+1;
 nPos.X = nPos.X+3;
 SpawnPretorian(nPos, ePretorianAI_SwordMaster, PretoIndex);
 
 PretoIndex = PretoIndex+1;
 nPos.X = nPos.X+3;
 SpawnPretorian(nPos, ePretorianAI_SwordMaster, PretoIndex);
 
 /* ' Sapwn 1 Shooter */
 PretoIndex = PretoIndex+1;
 nPos.Y = nPos.Y-6;
 nPos.X = nPos.X-1;
 SpawnPretorian(nPos, ePretorianAI_Shooter, PretoIndex);
 
 /* ' Spawn 1 SpellCaster */
 PretoIndex = PretoIndex+1;
 nPos.X = nPos.X-4;
 SpawnPretorian(nPos, ePretorianAI_SpellCaster, PretoIndex);
 
 /* ' Spawn 1 Thief */
 PretoIndex = PretoIndex+1;
 SpawnPretorian(nPos, ePretorianAI_Thief, PretoIndex);
 
 /* ' Reset wand break counter */
 WandBreakCounter = MAX_WAND_BREAK_VALUE;
 
 /* ' Now is active */
 ClanActive = true;
 
 /* ' Clan creation success */
 retval = true;
 
 return retval;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en CrearClanPretoriano. Error: " + Err.Number + " - " + Err.description);
return retval;
}

 bool clsClanPretoriano::IsValidSpawnArea() {
 bool retval;
 /* '******************************************************** */
 /* 'Author: ZaMa */
 /* 'Checks if it's a clean area to respawn the clan. */
 /* 'Required conditions: */
 /* '-> A 12x12 square free of blocks and in map bounds. */
 /* '-> Must be a non-water terrain */
 /* 'Last Modify Date: 21/09/2010 */
 /* '******************************************************** */
 
 int loopX;
 int LoopY;
 
  for (loopX = (CenterPos.X-6); loopX <= (CenterPos.X+6); loopX++) {
   for (LoopY = (CenterPos.Y-6); LoopY <= (CenterPos.Y+6); LoopY++) {
   
   if (!InMapBounds(CenterPos.Map, loopX, LoopY)) {
   return retval;
   }
   
   if (HayAgua(CenterPos.Map, loopX, LoopY)) {
   return retval;
   }
   
  }
 }
 
 retval = true;
 
return retval;
}

 void clsClanPretoriano::InitializePretoriansVars() {
 /* '******************************************************** */
 /* 'Author: ZaMa */
 /* 'Initialize the variables/const used in pretorian map */
 /* 'Last Modify Date: 21/09/2010 */
 /* '******************************************************** */
 
 LeftSpawnPos.Map = MAPA_PRETORIANO;
 LeftSpawnPos.X = 35;
 LeftSpawnPos.Y = 25;
 
 RightSpawnPos.Map = MAPA_PRETORIANO;
 RightSpawnPos.X = 67;
 RightSpawnPos.Y = 25;
 
}

 void clsClanPretoriano::SpawnPretorian(struct WorldPos & SpawnPos, int PretorianAI, int PretoIndex, bool IsKing) {
 /* '******************************************************** */
 /* 'Author: ZaMa */
 /* 'Spawns the Pretorian in the given position. */
 /* 'Last Modify Date: 21/09/2010 */
 /* '******************************************************** */
 
 struct WorldPos FinalPos;
 int NpcIndex;
 int Head;
 
 int PretoDatNumber;
 PretoDatNumber = RandomNumber(PretorianAIOffset[PretorianAI], PretorianAIOffset[PretorianAI+1]-1);
 
 /* ' Odd numbers are tall races */
  if ((PretoDatNumber && 1) == 1) {
  Head = RandomTallHead();
  } else {
  Head = RandomShortHead();
 }
 
 /* ' The King has to spawn always in the given position */
  if (IsKing) {
  
  /* ' Check if there's any npc in the king's position */
  int OtherNpcIndex;
  OtherNpcIndex = MapData[SpawnPos.Map][SpawnPos.X][SpawnPos.Y].NpcIndex;
  
  /* ' Found one */
   if (OtherNpcIndex != 0) {
   /* ' Move it to the closest legal position */
   ClosestLegalPos(SpawnPos, FinalPos);
    if (FinalPos.X != 0 && FinalPos.Y != 0) {
    SendData(SendTarget_ToNPCArea, OtherNpcIndex, PrepareMessageCharacterMove(Npclist[OtherNpcIndex].Char.CharIndex, FinalPos.X, FinalPos.Y));
    /* ' Update map and npc pos */
    MapData[SpawnPos.Map][SpawnPos.X][SpawnPos.Y].NpcIndex = 0;
    Npclist[OtherNpcIndex].Pos = FinalPos;
    MapData[FinalPos.Map][FinalPos.X][FinalPos.Y].NpcIndex = OtherNpcIndex;
    
    /* ' King's position is now empty */
    FinalPos = SpawnPos;
    
    /* ' Couldn't find a legal pos => Remove it */
    } else {
    QuitarNPC(OtherNpcIndex);
   }
   } else {
   FinalPos = SpawnPos;
  }
  
  /* ' Other clan member doesn't have to spawn in the exact position */
  } else {
  ClosestLegalPos(SpawnPos, FinalPos, false, true);
 }
 
 /* ' Create and Spawn npc */
 NpcIndex = CrearNPC(PretorianDatNumbers[PretoDatNumber], FinalPos.Map, FinalPos, Head);
 
 /* ' Store Index */
 Pretorianos[PretoIndex].NpcIndex = NpcIndex;
 Pretorianos[PretoIndex].NPCAI = PretorianAI;
 
 /* ' Asign ClanIndex */
 Npclist[NpcIndex].ClanIndex = ClanIndex;
 
}

 int clsClanPretoriano::RandomTallHead() {
 int retval;
 /* '******************************************************** */
 /* 'Author: ZaMa */
 /* 'Gets a random tall race's Head. */
 /* 'Last Modify Date: 21/09/2010 */
 /* '******************************************************** */
 
 /* ' 3 tall races */
 int raza;
 raza = RandomNumber(1, 3);
 
 /* ' Male */
  if ((RandomNumber(0, 1) == 1)) {
  
  /* ' Human */
   if (raza == 1) {
   retval = RandomNumber(HUMANO_H_PRIMER_CABEZA, HUMANO_H_ULTIMA_CABEZA);
   /* ' Elf */
   } else if (raza == 2) {
   retval = RandomNumber(ELFO_H_PRIMER_CABEZA, ELFO_H_ULTIMA_CABEZA);
   /* ' Drow */
   } else {
   retval = RandomNumber(DROW_H_PRIMER_CABEZA, DROW_H_ULTIMA_CABEZA);
  }
  
  /* ' Female */
  } else {
  
  /* ' Human */
   if (raza == 1) {
   retval = RandomNumber(HUMANO_M_PRIMER_CABEZA, HUMANO_M_ULTIMA_CABEZA);
   /* ' Elf */
   } else if (raza == 2) {
   retval = RandomNumber(ELFO_M_PRIMER_CABEZA, ELFO_M_ULTIMA_CABEZA);
   /* ' Drow */
   } else {
   retval = RandomNumber(DROW_M_PRIMER_CABEZA, DROW_M_ULTIMA_CABEZA);
  }
  
 }
 
return retval;
}

 int clsClanPretoriano::RandomShortHead() {
 int retval;
 /* '******************************************************** */
 /* 'Author: ZaMa */
 /* 'Gets a random short race's Head. */
 /* 'Last Modify Date: 21/09/2010 */
 /* '******************************************************** */
 
 /* ' 2 short races */
 int raza;
 raza = RandomNumber(1, 2);
 
 /* ' Male */
  if ((RandomNumber(0, 1) == 1)) {
  
  /* ' Dwarf */
   if (raza == 1) {
   retval = RandomNumber(ENANO_H_PRIMER_CABEZA, ENANO_H_ULTIMA_CABEZA);
   /* ' Gnome */
   } else {
   retval = RandomNumber(GNOMO_H_PRIMER_CABEZA, GNOMO_H_ULTIMA_CABEZA);
  }
  
  /* ' Female */
  } else {
  
  /* ' Dwarf */
   if (raza == 1) {
   retval = RandomNumber(ENANO_M_PRIMER_CABEZA, ENANO_M_ULTIMA_CABEZA);
   /* ' Gnome */
   } else {
   retval = RandomNumber(GNOMO_M_PRIMER_CABEZA, GNOMO_M_ULTIMA_CABEZA);
  }
  
 }
 
return retval;
}

 void clsClanPretoriano::PerformPretorianAI(int NpcIndex) {
 /* '******************************************************** */
 /* 'Author: ZaMa */
 /* 'Performs Pretorian's AI. */
 /* 'Last Modify Date: 21/09/2010 */
 /* '******************************************************** */
 
 int PretorianAI;
 PretorianAI = GetPretorianAI(NpcIndex);
 
 switch (PretorianAI) {
  
  case ePretorianAI_King:
  AI_King(NpcIndex);
  
  break;
  
  case ePretorianAI_Healer:
  AI_Healer(NpcIndex);
  
  break;
  
  case ePretorianAI_SpellCaster:
  AI_SpellCaster(NpcIndex);
  
  break;
  
  case ePretorianAI_SwordMaster:
  AI_SwordMaster(NpcIndex);
  
  break;
  
  case ePretorianAI_Shooter:
  AI_Shooter(NpcIndex);
  
  break;
  
  case ePretorianAI_Thief:
  AI_Thief(NpcIndex);
  
 break;
 }
 
}

 int clsClanPretoriano::GetPretorianAI(int NpcIndex) {
 int retval;
 /* '******************************************************** */
 /* 'Author: ZaMa */
 /* 'Returns the Pretorian's AI for the given Npc. */
 /* 'Last Modify Date: 21/09/2010 */
 /* '******************************************************** */
 
 int Counter;
 
  for (Counter = (1); Counter <= (NRO_PRETORIANOS); Counter++) {
   if (Pretorianos[Counter].NpcIndex == NpcIndex) {
   retval = Pretorianos[Counter].NPCAI;
   return retval;
  }
 }
 
return retval;
}

 void clsClanPretoriano::AI_King(int NpcIndex) {
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 19/09/2010 */
 /* '*************************************************** */
 /* FIXME: ON ERROR GOTO ErrHandler */
 
 int BestTarget;
 int Action;
 
 BestTarget = KingBestTarget(NpcIndex, Action);
 
 KingPerformAction(NpcIndex, BestTarget, Action);
 
 return;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en AI_King. Error: " + Err.Number + " - " + Err.description);
}

 int clsClanPretoriano::KingBestTarget(int NpcIndex, int & Accion) {
 int retval;
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 05/07/2010 */
 /* 'Pick the best target according to the following criteria: */
 /* '1) First try to heal status effects on allies (paralisis, poison, damaged) if any is alive */
 /* '2) If no ally is alive, then start a melee atack to near users */
 /* '3) If a user tries to run, then blind and make him stupid */
 /* '4) if no one is near, then heal himself. */
 /* '*************************************************** */
 /* FIXME: ON ERROR GOTO ErrHandler */
 
 int BestTarget;
 
 /* ' There should be more than one in order to support */
  if (ClanMembersAlive != 1) {
  
  /* ' Chooses target only if can attack */
   if (Npclist[NpcIndex].CanAttack == 1) {
   /* ' First checks if any ally is paralized in order to remove its paralizis */
   BestTarget = AllyParalyzed(NpcIndex, false);
    if (BestTarget != 0) {
    /* ' 20% of probability of doing it */
     if (RandomNumber(1, 100)<21) {
     Accion = eKingAction_HealAllyParalisis;
    }
    } else {
    /* ' Now checks if any ally is poisoned in order to remove its poison */
    BestTarget = AllyPoisoned(NpcIndex);
     if (BestTarget != 0) {
     Accion = eKingAction_HealAllyPoison;
     } else {
     /* ' If no target found, then try to heal injured allies */
     BestTarget = AllyInjured(NpcIndex);
      if (BestTarget != 0) {
      Accion = eKingAction_HealAlly;
     }
    }
   }
  }
  
  /* ' King's alone */
  } else {
  
  int mapa;
  int NPCPosX;
  int NPCPosY;
  
  int UserIndex;
  int Counter;
  
  int BestTargetDistance;
  int Distance;
  
   mapa = Npclist[NpcIndex].Pos.Map;
   NPCPosX = Npclist[NpcIndex].Pos.X;
   NPCPosY = Npclist[NpcIndex].Pos.Y;
  
  int CounterStart;
  int CounterEnd;
  int CounterStep;
  
  /* ' To avoid that all attack the same target */
  CounterStep = RandomNumber(0, 1);
   if (CounterStep == 1) {
   CounterStart = 1;
   CounterEnd = ConnGroups[mapa].CountEntrys;
   } else {
   CounterStart = ConnGroups[mapa].CountEntrys;
   CounterEnd = 1;
   CounterStep = -1;
  }
  
  /* ' Search for the best user target */
   for (Counter = (CounterStart); ((CounterStep) > 0) ? (Counter <= (CounterEnd)) : (Counter >= (CounterEnd)); Counter = Counter + (CounterStep)) {
   
   UserIndex = ConnGroups[mapa].UserEntrys[Counter];
   
   /* 'Is it in it's range of vision?? */
    if (InVisionRange(UserIndex, NPCPosX, NPCPosY)) {
    /* ' Can be atacked? If it's blinded, doesn't count. */
     if (UserAtacable(UserIndex) && UserList[UserIndex].flags.Ceguera == 0) {
     /* ' if previous user choosen, select the better */
      if (BestTarget != 0) {
      /* ' Has priority to attack the nearest */
      Distance = UserDistance(UserIndex, NPCPosX, NPCPosY);
      
       if (Distance<BestTargetDistance) {
       BestTarget = UserIndex;
       BestTargetDistance = Distance;
      }
      } else {
      BestTarget = UserIndex;
      BestTargetDistance = UserDistance(UserIndex, NPCPosX, NPCPosY);
     }
    }
   }
   
  }
  
  /* ' Any target found? */
   if (BestTarget != 0) {
   /* ' Is reachable? */
    if (UserReachable(NpcIndex, BestTarget)) {
    /* ' Chase it */
    Accion = eKingAction_ChaseTarget;
    
    /* ' The target is trying to escape => Stop him with a massive status attack */
    } else {
    Accion = eKingAction_MassiveAttack;
   }
   
   /* ' No target found => Retreat and heal */
   } else {
   Accion = eKingAction_RetreatAndHeal;
  }
 }
 
 retval = BestTarget;
 
 return retval;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en KingBestTarget. Error: " + Err.Number + " - " + Err.description);
return retval;
}

 void clsClanPretoriano::KingPerformAction(int NpcIndex, int BestTarget, int Accion) {
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 05/07/2010 */
 /* 'Performs the required action. */
 /* '*************************************************** */
 /* FIXME: ON ERROR GOTO ErrHandler */
 
 int IdleTime;
 
  switch (Accion) {
   
   case eKingAction_HealAllyParalisis:
   NpcLanzaSpellSobreNpc(NpcIndex, BestTarget, Npclist[NpcIndex].Spells[eKingSpells_RemoveParalisis], true);
   
   break;
   
   case eKingAction_HealAllyPoison:
   NpcLanzaSpellSobreNpc(NpcIndex, BestTarget, Npclist[NpcIndex].Spells[eKingSpells_HealPoison], true);
   
   break;
   
   case eKingAction_HealAlly:
   NpcLanzaSpellSobreNpc(NpcIndex, BestTarget, Npclist[NpcIndex].Spells[eKingSpells_LittleHeal], true);
   
   /* ' If time for respawning an ally has passed, then try to do it */
   if (KingIdleTime>ALLY_RESPAWN_TIME) {
   KingReviveAlly(NpcIndex);
   }
   IdleTime = KingIdleTime+1;
   
   break;
   
   case eKingAction_ChaseTarget:
   case eKingAction_MassiveAttack:
   
    if (Accion == eKingAction_ChaseTarget) {
    GreedyWalkTo(NpcIndex, UserList[BestTarget].Pos.Map, UserList[BestTarget].Pos.X, UserList[BestTarget].Pos.Y);
    } else {
    NpcLanzaSpellSobreUser(NpcIndex, BestTarget, Npclist[NpcIndex].Spells[eKingSpells_StupidityAttack], true, true);
    /* ' So it can make double attack */
    Npclist[NpcIndex].CanAttack = 1;
    NpcLanzaSpellSobreUser(NpcIndex, BestTarget, Npclist[NpcIndex].Spells[eKingSpells_BlindAttack], true, true);
    
    /* ' King Message */
    WriteConsoleMsg(BestTarget, "El rey pretoriano te ha vuelto estúpido.", FontTypeNames_FONTTYPE_FIGHT);
    WriteConsoleMsg(BestTarget, "El rey pretoriano te ha vuelto ciego ", FontTypeNames_FONTTYPE_FIGHT);
    WriteConsoleMsg(BestTarget, "A la distancia escuchas las siguientes palabras: ¡Cobarde, no eres digno de luchar conmigo si escapas! ", FontTypeNames_FONTTYPE_VENENO);
   }
   
   KingMeleeAttack(NpcIndex);
   
   break;
   
   case eKingAction_RetreatAndHeal:
   ReturnToCenter(NpcIndex);
    if (Npclist[NpcIndex].Stats.MinHp != Npclist[NpcIndex].Stats.MaxHp) {
    NpcLanzaSpellSobreNpc(NpcIndex, NpcIndex, Npclist[NpcIndex].Spells[eKingSpells_LittleHeal], true);
   }
   
   /* ' If time for respawning an ally has passed, then try to do it */
   if (KingIdleTime>ALLY_RESPAWN_TIME) {
   KingReviveAlly(NpcIndex);
   }
   IdleTime = KingIdleTime+1;
   
  break;
  }
  
 /* ' Resets if anyone is around, else increases */
 KingIdleTime = IdleTime;
 Debug.PRINTKingIdleTime();
 return;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en KingPerformAction. Error: " + Err.Number + " - " + Err.description);
}

 void clsClanPretoriano::KingMeleeAttack(vb6::Variant NpcIndex) {
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 19/09/2010 */
 /* 'King performes a melee attack ignoring attack intervals */
 /* '*************************************************** */
 /* FIXME: ON ERROR GOTO ErrHandler */
 
 int headingloop;
 struct WorldPos nPos;
 
 int UserIndex;
 
  /* ' Check the four directions */
   for (headingloop = (eHeading_NORTH); headingloop <= (eHeading_WEST); headingloop++) {
   
   nPos = Npclist[NpcIndex].Pos;
   
   HeadtoPos(headingloop, nPos);
   
   /* ' In map Limits? */
    if (InMapBounds(nPos.Map, nPos.X, nPos.Y)) {
    
    UserIndex = MapData[nPos.Map][nPos.X][nPos.Y].UserIndex;
     if (UserIndex>0) {
      if (UserAtacable(UserIndex, false)) {
       if (NpcAtacaUser(NpcIndex, UserIndex)) {
       ChangeNPCChar(NpcIndex, Npclist[NpcIndex].Char.body, Npclist[NpcIndex].Char.Head, headingloop);
      }
      
      /* ''special speed ability for praetorian king (Ignores intervals) */
      Npclist[NpcIndex].CanAttack = 1;
     }
    }
   }
  }
  
 return;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en KingMeleeAttack. Error: " + Err.Number + " - " + Err.description);
}

 void clsClanPretoriano::KingReviveAlly(int NpcIndex) {
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 26/09/2010 */
 /* 'King tries to revive an ally. */
 /* '*************************************************** */
 
 int AllyIndex;
 struct WorldPos nPos;
 
  /* ' Has to be in the center to revive */
   if (Npclist[NpcIndex].Pos.X == CenterPos.X) {
    if (Npclist[NpcIndex].Pos.Y == CenterPos.Y) {
    
    /* ' Any ally dead? */
    AllyIndex = AllyDead();
     if (AllyIndex != 0) {
     nPos = CenterPos;
     nPos.X = nPos.X+1;
     SpawnPretorian(nPos, Pretorianos[AllyIndex].NPCAI, AllyIndex);
     ClanMembersAlive = ClanMembersAlive+1;
    }
    
    /* ' Reset iddle time */
    KingIdleTime = 0;
    
   }
  }
  
}

 void clsClanPretoriano::AI_Healer(int NpcIndex) {
 /* '*************************************************** */
 /* 'Author: Unkown */
 /* 'Last Modification: - */
 /* '*************************************************** */
 /* FIXME: ON ERROR GOTO ErrHandler */
 
 int BestTarget;
 int Accion;
 
 /* ' Chooses target only if can attack */
  if (Npclist[NpcIndex].CanAttack == 1) {
  /* ' First checks if any ally is paralized in order to remove its paralizis */
  BestTarget = AllyParalyzed(NpcIndex, false);
   if (BestTarget != 0) {
   Accion = eHealerAction_HealAllyParalisis;
   } else {
   /* ' Now picks the best target to attack, either user or pet */
   BestTarget = HealerBestTarget(NpcIndex, Accion);
   
   /* ' If no target found, then try to heal injured allies */
    if (BestTarget == 0) {
    BestTarget = AllyInjured(NpcIndex);
    
    /* ' Found an injured Ally */
     if (BestTarget != 0) {
     Accion = eHealerAction_HealAlly;
    }
    
   }
  }
 }
 
 /* ' Search for far paralized allies, if not better choise selected */
  if (BestTarget == 0) {
  
  /* 'if it's paralized, it has no sense doing it */
   if (Npclist[NpcIndex].flags.Paralizado == 0) {
   
   BestTarget = AllyParalyzed(NpcIndex, true);
    if (BestTarget != 0) {
    Accion = eHealerAction_RescueFarAlly;
   }
   
  }
  
 }
 
 bool CanMove;
 
 /* ' Performes the best action acording to the chosen target */
 HealerPerformAction(NpcIndex, BestTarget, Accion, CanMove);
 
 /* ' Moves only if in danger */
 if (CanMove) {
 HealerMove(NpcIndex);
 }
 
 return;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en AI_Healer. Error: " + Err.Number + " - " + Err.description);
}

 int clsClanPretoriano::HealerBestTarget(int NpcIndex, int & Accion) {
 int retval;
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 09/07/2010 */
 /* 'Pick the best target according to the following criteria: */
 /* '1) "hoaxed" friends MUST be released */
 /* '2) enemy shall be annihilated no matter what */
 /* '3) party healing if no threats */
 /* '*************************************************** */
 
 /* FIXME: ON ERROR GOTO ErrHandler */
 
 int UserIndex;
 int Counter;
 
 int PetIndex;
 
 int BestTarget;
 bool BestTargetInvisible;
 
 int NpcX;
 int NpcY;
 
 NpcX = Npclist[NpcIndex].Pos.X;
 NpcY = Npclist[NpcIndex].Pos.Y;
 
 int CounterStart;
 int CounterEnd;
 int CounterStep;
 
 /* ' To avoid that all attack the same target */
 CounterStep = RandomNumber(0, 1);
  if (CounterStep == 1) {
  CounterStart = 1;
  CounterEnd = ConnGroups[CenterPos.Map].CountEntrys;
  } else {
  CounterStart = ConnGroups[CenterPos.Map].CountEntrys;
  CounterEnd = 1;
  CounterStep = -1;
 }
 
  for (Counter = (CounterStart); ((CounterStep) > 0) ? (Counter <= (CounterEnd)) : (Counter >= (CounterEnd)); Counter = Counter + (CounterStep)) {
  
  UserIndex = ConnGroups[CenterPos.Map].UserEntrys[Counter];
  
  /* ' Can be atacked (doesn't matter if invisible or hidden)? */
   if (UserAtacable(UserIndex, false)) {
   
   /* ' Checks if ther's a non-paralized user pet in range. If so, then paralize it. */
   PetIndex = CheckNearUserPets(NpcIndex, UserIndex);
    if (PetIndex != 0) {
    BestTarget = PetIndex;
    Accion = eHealerAction_ParalizePet;
    break; /* FIXME: EXIT FOR */
   }
   
   /* 'Is it in it's range of vision?? */
    if (InVisionRange(UserIndex, NpcX, NpcY)) {
    
     /* ' It's Paralized? */
      if (UserList[UserIndex].flags.Paralizado == 0) {
      
      /* ' It's visible? */
       if ((UserList[UserIndex].flags.invisible == 0) && (UserList[UserIndex].flags.Oculto == 0)) {
       
       BestTarget = UserIndex;
       Accion = eHealerAction_ParalizeUser;
       
      }
      
      /* ' User Paralized, if not better target found then attack it */
      } else if (BestTarget == 0) {
      
      BestTarget = UserIndex;
      Accion = eHealerAction_AttackUser;
      
     }
     
   }
   
  }
  
 }
 
 retval = BestTarget;
 
 return retval;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en HealerBestTarget. Error: " + Err.Number + " - " + Err.description);
return retval;
}

 void clsClanPretoriano::HealerPerformAction(int NpcIndex, int BestTarget, int Accion, bool & CanMove) {
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 09/07/2010 */
 /* 'Performs the required action. Determines if the npc can move after perfoming the selected action. */
 /* '*************************************************** */
 
  switch (Accion) {
   
   case eHealerAction_HealAllyParalisis:
   NpcLanzaSpellSobreNpc(NpcIndex, BestTarget, Npclist[NpcIndex].Spells[eHealerSpells_RemoveParalisis], true);
   CanMove = false;
   
   break;
   
   case eHealerAction_ParalizePet:
   NpcLanzaSpellSobreNpc(NpcIndex, BestTarget, Npclist[NpcIndex].Spells[eHealerSpells_ParalizeNpc], true);
   CanMove = true;
   
   break;
   
   case eHealerAction_ParalizeUser:
   SendData(SendTarget_ToNPCArea, NpcIndex, PrepareMessageChatOverHead(Hechizos[Npclist[NpcIndex].Spells[eHealerSpells_ParalizeUser]].PalabrasMagicas, Npclist[NpcIndex].Char.CharIndex, vbCyan));
   NpcLanzaSpellSobreUser(NpcIndex, BestTarget, Npclist[NpcIndex].Spells[eHealerSpells_ParalizeUser], true);
   CanMove = false;
   
   break;
   
   case eHealerAction_AttackUser:
   NpcLanzaSpellSobreUser(NpcIndex, BestTarget, Npclist[NpcIndex].Spells[eHealerSpells_Tormenta], true, true);
   CanMove = false;
   
   break;
   
   case eHealerAction_HealAlly:
   NpcLanzaSpellSobreNpc(NpcIndex, BestTarget, Npclist[NpcIndex].Spells[eHealerSpells_Heal], true);
   CanMove = true;
   
   break;
   
   case eHealerAction_RescueFarAlly:
   GreedyWalkTo(NpcIndex, Npclist[NpcIndex].Pos.Map, Npclist[BestTarget].Pos.X, Npclist[BestTarget].Pos.Y);
   CanMove = false;
   
   break;
   
   default:
   CanMove = true;
   
  break;
  }
 
}

 void clsClanPretoriano::HealerMove(int NpcIndex) {
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 09/07/2010 */
 /* 'Doesn't move after casting some spells. Try to avoid swordmasters. */
 /* '*************************************************** */
 
  /* ' Can't move if paralized */
  if (Npclist[NpcIndex].flags.Paralizado == 1) {
  return;
  }
  
  /* ' Only applies to clan map */
  if (Npclist[NpcIndex].Pos.Map != CenterPos.Map) {
  return;
  }
  
  /* ' if nobody's near or it's idle then returns near the king */
  ReturnToCenter(NpcIndex);
  
  /* ' Runs away from close users */
   if (TargetClose(Npclist[NpcIndex].Pos)) {
   ReturnToCenter(NpcIndex);
  }
  
}

 void clsClanPretoriano::AI_SpellCaster(int NpcIndex) {
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: - */
 /* '*************************************************** */
 /* FIXME: ON ERROR GOTO ErrHandler */
 
 int BestTarget;
 int Accion;
 
 /* ' It sacrifices itself giving a fatal blow if close to death */
 if (SpellCasterSacrifice(NpcIndex)) {
 return;
 }
 
 /* ' If healthy then choose best target */
 BestTarget = SpellCasterBestTarget(NpcIndex, Accion);
 
 /* ' Performes the best action acoording to the chosen target */
  if (BestTarget != 0) {
  SpellCasterPerformAction(NpcIndex, BestTarget, Accion);
 }
 
 /* ' Moves only if in danger */
 SpellCasterMove(NpcIndex, BestTarget);
 
 return;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en AI_SpellCaster. Error: " + Err.Number + " - " + Err.description);
}

 bool clsClanPretoriano::SpellCasterSacrifice(int NpcIndex) {
 bool retval;
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 05/07/2010 */
 /* 'Checks if the required conditions to sacrify are fullfiled, if so then does it. */
 /* 'The wand break counter is stored in the boat slot, asuming it'd never be used for any other purpose. */
 /* '*************************************************** */
 
   if (Npclist[NpcIndex].Stats.MinHp<=START_COUNTDOWN_MIN_HP) {
   SendData(SendTarget_ToNPCArea, NpcIndex, PrepareMessageCreateFX(Npclist[NpcIndex].Char.CharIndex, FXIDs_FXMEDITARGRANDE, INFINITE_LOOPS));
   
    if (Npclist[NpcIndex].CanAttack == 1) {
    
    Npclist[NpcIndex].CanAttack = 0;
    
    WandBreakCounter = WandBreakCounter-1;
    SpellCasterDestroyWand(NpcIndex, eSpellCasterSpells_Apocalipsis);
    
    /* '  Wand broken => dies */
    if (WandBreakCounter == 0) {
    MuereNpc(NpcIndex, 0);
    }
    
   }
   
   retval = true;
   
   } else {
   /* 'Restore wand break counter */
    if (WandBreakCounter != MAX_WAND_BREAK_VALUE) {
    WandBreakCounter = MAX_WAND_BREAK_VALUE;
    SendData(SendTarget_ToNPCArea, NpcIndex, PrepareMessageCreateFX(Npclist[NpcIndex].Char.CharIndex, 0, 0));
   }
  }
 
return retval;
}

 int clsClanPretoriano::SpellCasterBestTarget(int NpcIndex, int & Accion) {
 int retval;
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 05/07/2010 */
 /* 'Pick the best target according to the following criteria: */
 /* '1) Invisible enemies can be detected sometimes */
 /* '2) A wizard's mission is background spellcasting attack */
 /* '*************************************************** */
 
 /* FIXME: ON ERROR GOTO ErrHandler */
 
 int UserIndex;
 int Counter;
 
 int BestTarget;
 int NpcX;
 int NpcY;
 bool BestTargetInvisible;
 
 NpcX = Npclist[NpcIndex].Pos.X;
 NpcY = Npclist[NpcIndex].Pos.Y;
 
 int CounterStart;
 int CounterEnd;
 int CounterStep;
 
 /* ' To avoid that all attack the same target */
 CounterStep = RandomNumber(0, 1);
  if (CounterStep == 1) {
  CounterStart = 1;
  CounterEnd = ConnGroups[CenterPos.Map].CountEntrys;
  } else {
  CounterStart = ConnGroups[CenterPos.Map].CountEntrys;
  CounterEnd = 1;
  CounterStep = -1;
 }
 
  for (Counter = (CounterStart); ((CounterStep) > 0) ? (Counter <= (CounterEnd)) : (Counter >= (CounterEnd)); Counter = Counter + (CounterStep)) {
  
  UserIndex = ConnGroups[CenterPos.Map].UserEntrys[Counter];
  
  /* 'Is it in it's range of vision?? */
   if (InVisionRange(UserIndex, NpcX, NpcY)) {
   
   /* ' Can be atacked? */
    if (UserAtacable(UserIndex, false)) {
    
     /* ' It's invisible? */
      if ((UserList[UserIndex].flags.invisible == 1) || (UserList[UserIndex].flags.Oculto == 1)) {
      
      /* ' Try to remove invisibility */
       if ((RandomNumber(1, 100)<=35)) {
       BestTarget = UserIndex;
       Accion = eSpellCasterAction_RemoveInvi;
       break; /* FIXME: EXIT FOR */
      }
      
      /* ' Paralized invisible users are good target! */
       if (UserList[UserIndex].flags.Paralizado == 1) {
       BestTarget = UserIndex;
       BestTargetInvisible = true;
       Accion = eSpellCasterAction_Attack;
      }
      
      /* ' Visible but paralized? */
      } else if ((UserList[UserIndex].flags.Paralizado == 1)) {
      
      /* ' If not found an invisible and paralized target, then it's a good one */
       if (!BestTargetInvisible || BestTarget == 0) {
       BestTarget = UserIndex;
       Accion = eSpellCasterAction_Attack;
      }
      
      /* ' Visible and can move, if not better found then choose it */
      } else if (BestTarget == 0) {
      
      BestTarget = UserIndex;
      Accion = eSpellCasterAction_Attack;
      
     }
     
   }
   
  }
  
 }
 
 retval = BestTarget;
 
 return retval;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en SpellCasterBestTarget. Error: " + Err.Number + " - " + Err.description);
return retval;
}

 void clsClanPretoriano::SpellCasterPerformAction(int NpcIndex, int BestTarget, int Accion) {
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 05/07/2010 */
 /* 'Performs the required action. */
 /* '*************************************************** */
 
  switch (Accion) {
   
   case eSpellCasterAction_Attack:
   NpcLanzaSpellSobreUser(NpcIndex, BestTarget, Npclist[NpcIndex].Spells[eSpellCasterSpells_Apocalipsis], true, true);
   
   break;
   
   case eSpellCasterAction_RemoveInvi:
   NpcLanzaSpellSobreUser(NpcIndex, BestTarget, Npclist[NpcIndex].Spells[eSpellCasterSpells_RemoInvi], true, true);
   
  break;
  }
 
}

 void clsClanPretoriano::SpellCasterMove(int NpcIndex, int BestTarget) {
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 05/07/2010 */
 /* 'Doesn't move unless nobody is near or there is no best target. */
 /* '*************************************************** */
 
  /* ' Can't move if paralized */
  if (Npclist[NpcIndex].flags.Paralizado == 1) {
  return;
  }
  
  /* ' Only applies to clan map */
  if (Npclist[NpcIndex].Pos.Map != CenterPos.Map) {
  return;
  }
  
  /* ' if nobody's near or it's idle then returns near the king */
  if ((BestTarget == 0) && (Npclist[NpcIndex].CanAttack == 1)) {
  ReturnToCenter(NpcIndex);
  }
  
  /* ' Runs away from close users */
   if (TargetClose(Npclist[NpcIndex].Pos)) {
   ReturnToCenter(NpcIndex);
  }
  
}

 void clsClanPretoriano::SpellCasterDestroyWand(int NpcIndex, int SpellIndex) {
 /* '*************************************************** */
 /* 'Author: Unkown */
 /* 'Last Modification: - */
 /* '*************************************************** */
 /* FIXME: ON ERROR GOTO ErrHandler */
 /* ''sonidos: 30 y 32, y no los cambien sino termina siendo muy chistoso... */
 /* ''Para el FX utiliza el del hechizos(SpellIndex) */
 
  switch (WandBreakCounter) {
   case 5:
   SendData(SendTarget_ToNPCArea, NpcIndex, PrepareMessageChatOverHead("Rahma", Npclist[NpcIndex].Char.CharIndex, vbGreen));
   SendData(SendTarget_ToNPCArea, NpcIndex, PrepareMessagePlayWave(SONIDO_DRAGON_VIVO, Npclist[NpcIndex].Pos.X, Npclist[NpcIndex].Pos.Y));
   break;
   
   case 4:
   SendData(SendTarget_ToNPCArea, NpcIndex, PrepareMessageChatOverHead("vôrtax", Npclist[NpcIndex].Char.CharIndex, vbGreen));
   SendData(SendTarget_ToNPCArea, NpcIndex, PrepareMessagePlayWave(SONIDO_DRAGON_VIVO, Npclist[NpcIndex].Pos.X, Npclist[NpcIndex].Pos.Y));
   break;
   
   case 3:
   SendData(SendTarget_ToNPCArea, NpcIndex, PrepareMessageChatOverHead("Zill", Npclist[NpcIndex].Char.CharIndex, vbGreen));
   SendData(SendTarget_ToNPCArea, NpcIndex, PrepareMessagePlayWave(SONIDO_DRAGON_VIVO, Npclist[NpcIndex].Pos.X, Npclist[NpcIndex].Pos.Y));
   break;
   
   case 2:
   SendData(SendTarget_ToNPCArea, NpcIndex, PrepareMessageChatOverHead("yäkà E'nta", Npclist[NpcIndex].Char.CharIndex, vbGreen));
   SendData(SendTarget_ToNPCArea, NpcIndex, PrepareMessagePlayWave(SONIDO_DRAGON_VIVO, Npclist[NpcIndex].Pos.X, Npclist[NpcIndex].Pos.Y));
   break;
   
   case 1:
   SendData(SendTarget_ToNPCArea, NpcIndex, PrepareMessageChatOverHead("¡¡Koràtá!!", Npclist[NpcIndex].Char.CharIndex, vbGreen));
   SendData(SendTarget_ToNPCArea, NpcIndex, PrepareMessagePlayWave(SONIDO_DRAGON_VIVO, Npclist[NpcIndex].Pos.X, Npclist[NpcIndex].Pos.Y));
   break;
   
   case 0:
   SendData(SendTarget_ToNPCArea, NpcIndex, PrepareMessageChatOverHead("", Npclist[NpcIndex].Char.CharIndex, vbGreen));
   SendData(SendTarget_ToNPCArea, NpcIndex, PrepareMessagePlayWave(SONIDO_DRAGON_VIVO, Npclist[NpcIndex].Pos.X, Npclist[NpcIndex].Pos.Y));
   
   DealWandDamage(NpcIndex, Npclist[NpcIndex].Spells[SpellIndex]);
  break;
  }
  
 return;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en SpellCasterDestroyWand. Error: " + Err.Number + " - " + Err.description);
}

 void clsClanPretoriano::DealWandDamage(int NpcIndex, int SpellIndex) {
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 17/06/2011 */
 /* 'Description: Deals massive wand damage. */
 /* '17/06/2011: Amraphen - User's hp is updated once he gets hit by wand damage. */
 /* '*************************************************** */
 /* FIXME: ON ERROR GOTO ErrHandler */
 
 int UserIndex;
 int Counter;
 
 int Distancia;
 int Danio;
 
 int X;
 int Y;
 
  X = Npclist[NpcIndex].Pos.X;
  Y = Npclist[NpcIndex].Pos.Y;
  
   for (Counter = (1); Counter <= (ConnGroups[CenterPos.Map].CountEntrys); Counter++) {
   
   UserIndex = ConnGroups[CenterPos.Map].UserEntrys[Counter];
   
    if (UserIndex != 0) {
    
      if (UserAtacable(UserIndex, false, false)) {
      
      Distancia = UserDistance(UserIndex, X, Y);
      Danio = vb6::Abs(vb6::Int(880/(Distancia $ (3/7))));
      
      UserList[UserIndex].Stats.MinHp = UserList[UserIndex].Stats.MinHp-Danio;
      
      WriteConsoleMsg(UserIndex, Npclist[NpcIndex].Name + " te ha quitado " + Danio + " puntos de vida al romper su vara.", FontTypeNames_FONTTYPE_FIGHT);
      SendData(SendTarget_ToPCArea, UserIndex, PrepareMessagePlayWave(Hechizos[SpellIndex].WAV, UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y));
      SendData(SendTarget_ToPCArea, UserIndex, PrepareMessageCreateFX(UserList[UserIndex].Char.CharIndex, Hechizos[SpellIndex].FXgrh, Hechizos[SpellIndex].loops));
      
       if (UserList[UserIndex].Stats.MinHp<1) {
       UserList[UserIndex].Stats.MinHp = 0;
       UserDie(UserIndex);
       } else {
       /* 'Updates user's hp: */
       WriteUpdateHP(UserIndex);
       /* ' Also hit pets */
       if (UserList[UserIndex].NroMascotas>0) {
       DealWandDamageToPets(NpcIndex, UserIndex, SpellIndex);
       }
       
      }
      
     }
     
   }
   
  }
  
 return;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en DealWandDamage. Error: " + Err.Number + " - " + Err.description);
}

 void clsClanPretoriano::DealWandDamageToPets(int NpcIndex, int UserIndex, int SpellIndex) {
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 26/09/2010 */
 /* 'Deals massive wand damage to user pets. */
 /* '*************************************************** */
 /* FIXME: ON ERROR GOTO ErrHandler */
 
 int PetIndex;
 int PetCounter;
 
 int Distancia;
 int Danio;
 
 int NpcX;
 int NpcY;
 
 NpcX = Npclist[NpcIndex].Pos.X;
 NpcY = Npclist[NpcIndex].Pos.Y;
 
  for (PetCounter = (1); PetCounter <= (MAXMASCOTAS); PetCounter++) {
  
  PetIndex = UserList[UserIndex].MascotasIndex[PetCounter];
   if (PetIndex>0) {
    
    Distancia = NpcDistance(PetIndex, NpcX, NpcY);
    Danio = vb6::Abs(vb6::Int(880/(Distancia $ (3/7))));
    
    Npclist[PetIndex].Stats.MinHp = Npclist[PetIndex].Stats.MinHp-Danio;
    
    SendData(SendTarget_ToNPCArea, PetIndex, PrepareMessagePlayWave(Hechizos[SpellIndex].WAV, Npclist[PetIndex].Pos.X, Npclist[PetIndex].Pos.Y));
    SendData(SendTarget_ToNPCArea, PetIndex, PrepareMessageCreateFX(Npclist[PetIndex].Char.CharIndex, Hechizos[SpellIndex].FXgrh, Hechizos[SpellIndex].loops));
    
     if (Npclist[PetIndex].Stats.MinHp<1) {
     Npclist[PetIndex].Stats.MinHp = 0;
     MuereNpc(PetIndex, 0);
    }
    
  }
  
 }
 
 return;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en DealWandDamageToPets. Error: " + Err.Number + " - " + Err.description);
}

 void clsClanPretoriano::AI_SwordMaster(int NpcIndex) {
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: - */
 /* '*************************************************** */
 /* FIXME: ON ERROR GOTO ErrHandler */
 
 int BestTarget;
 
 /* ' First choose best target */
 BestTarget = SwordMasterBestTarget(NpcIndex);
 
 /* ' Then moves, close to target user if in range */
 SwordMasterMove(NpcIndex, BestTarget);
 
 /* ' Finally, attacks sorrounding targets */
 SwordMasterAttack(NpcIndex);
 
 return;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en AI_SwordMaster. Error: " + Err.Number + " - " + Err.description);
}

 int clsClanPretoriano::SwordMasterBestTarget(int NpcIndex) {
 int retval;
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 26/06/2010 */
 /* 'Picks the best target according to the following criteria: */
 /* '1) The nearest enemy will be attacked. */
 /* '*************************************************** */
 
 /* FIXME: ON ERROR GOTO ErrHandler */
 
 int UserIndex;
 int Counter;
 
 int BestTarget;
 int BestTargetDistance;
 
 int NpcX;
 int NpcY;
 int Distance;
 
 NpcX = Npclist[NpcIndex].Pos.X;
 NpcY = Npclist[NpcIndex].Pos.Y;
 
 int CounterStart;
 int CounterEnd;
 int CounterStep;
 
 /* ' To avoid that all attack the same target */
 CounterStep = RandomNumber(0, 1);
  if (CounterStep == 1) {
  CounterStart = 1;
  CounterEnd = ConnGroups[CenterPos.Map].CountEntrys;
  } else {
  CounterStart = ConnGroups[CenterPos.Map].CountEntrys;
  CounterEnd = 1;
  CounterStep = -1;
 }
 
  for (Counter = (CounterStart); ((CounterStep) > 0) ? (Counter <= (CounterEnd)) : (Counter >= (CounterEnd)); Counter = Counter + (CounterStep)) {
  
  UserIndex = ConnGroups[CenterPos.Map].UserEntrys[Counter];
  
  /* 'Is it in it's range of vision?? */
   if (InVisionRange(UserIndex, NpcX, NpcY)) {
   
   /* ' Can be atacked? */
    if (UserAtacable(UserIndex)) {
    /* ' Checks limits in order to avoid to separate it from the rest of the clan */
     if (UserReachable(NpcIndex, UserIndex)) {
     
      if (BestTarget != 0) {
      
      /* ' Has priority to attack the nearest */
      Distance = UserDistance(UserIndex, NpcX, NpcY);
      
       if (Distance<BestTargetDistance) {
       BestTarget = UserIndex;
       BestTargetDistance = Distance;
      }
      
      } else {
      BestTarget = UserIndex;
      BestTargetDistance = UserDistance(UserIndex, NpcX, NpcY);
     }
     
    }
    
   }
   
  }
  
 }
 
 retval = BestTarget;
 
 return retval;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en SwordMasterBestTarget. Error: " + Err.Number + " - " + Err.description);
return retval;
}

 void clsClanPretoriano::SwordMasterMove(int NpcIndex, int BestTarget) {
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 24/06/2010 */
 /* 'La idea es que no lo "alejen" del rey y despues queden */
 /* 'lejos de la batalla cuando matan a un enemigo o este */
 /* 'sale del area de combate (tipica forma de separar un clan) */
 /* '*************************************************** */
 
 /* FIXME: ON ERROR GOTO ErrHandler */
 
  /* ' If paralized can't move */
  if (Npclist[NpcIndex].flags.Paralizado == 1) {
  return;
  }
  
  /* ' Only applies to clan map */
  if (Npclist[NpcIndex].Pos.Map != CenterPos.Map) {
  return;
  }
  
  /* ' If it's far from protection then returns to center */
   if (FarFromTeam(NpcIndex)) {
   ReturnToCenter(NpcIndex);
   return;
  }
  
  /* ' If someone's in range, then go close to him */
   if (BestTarget>0) {
   
    GreedyWalkTo(NpcIndex, CenterPos.Map, UserList[BestTarget].Pos.X, UserList[BestTarget].Pos.Y);
   
   /* 'Returns to center if no target found */
   } else {
   ReturnToCenter(NpcIndex);
  }
  
 return;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en SwordMasterMove. Error: " + Err.Number + " - " + Err.description);
}

 void clsClanPretoriano::SwordMasterAttack(int NpcIndex) {
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 26/06/2010 */
 /* 'Searchs and Attacks the sorrounding target */
 /* '*************************************************** */
 
 /* FIXME: ON ERROR GOTO ErrHandler */
 
 int headingloop;
 struct WorldPos NpcPos;
 int UserIndex;
 
  /* ' Check the four directions */
   for (headingloop = (eHeading_NORTH); headingloop <= (eHeading_WEST); headingloop++) {
   
   NpcPos = Npclist[NpcIndex].Pos;
   HeadtoPos(headingloop, NpcPos);
   
   UserIndex = MapData[NpcPos.Map][NpcPos.X][NpcPos.Y].UserIndex;
   
    if (UserIndex>0) {
     if (UserAtacable(UserIndex, false)) {
      if (NpcAtacaUser(NpcIndex, UserIndex)) {
      ChangeNPCChar(NpcIndex, Npclist[NpcIndex].Char.body, Npclist[NpcIndex].Char.Head, headingloop);
      break; /* FIXME: EXIT FOR */
     }
    }
   }
   
  }
  
 return;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en SwordMasterAttack. Error: " + Err.Number + " - " + Err.description);
}

 void clsClanPretoriano::AI_Shooter(int NpcIndex) {
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: - */
 /* '*************************************************** */
 int BestTarget;
 
 /* ' First choose best target */
 BestTarget = ShooterBestTarget(NpcIndex);
 
 /* ' Found a target => attack! */
  if (BestTarget>0) {
  /* ' Attack with arrow */
  NpcLanzaSpellSobreUser(NpcIndex, BestTarget, Npclist[NpcIndex].Spells[1]);
 }
 
 /* ' Then moves, close to target user if attacking one */
 ShooterMove(NpcIndex, BestTarget);
 
 return;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en AI_Shooter. Error: " + Err.Number + " - " + Err.description);
}

 int clsClanPretoriano::ShooterBestTarget(int NpcIndex) {
 int retval;
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 24/06/2010 */
 /* 'Picks the best target according to the following criteria: */
 /* '1) Magic clases ARE dangerous, but they are weak too, they're */
 /* '   our primary target */
 /* '2) in any other case, our nearest enemy will be attacked */
 /* '*************************************************** */
 
 /* FIXME: ON ERROR GOTO ErrHandler */
 
 int UserIndex;
 int Counter;
 
 int BestTarget;
 int BestTargetDistance;
 
 int NpcX;
 int NpcY;
 int Distance;
 
 NpcX = Npclist[NpcIndex].Pos.X;
 NpcY = Npclist[NpcIndex].Pos.Y;
 
 int CounterStart;
 int CounterEnd;
 int CounterStep;
 
 /* ' To avoid that all attack the same target */
 CounterStep = RandomNumber(0, 1);
  if (CounterStep == 1) {
  CounterStart = 1;
  CounterEnd = ConnGroups[CenterPos.Map].CountEntrys;
  } else {
  CounterStart = ConnGroups[CenterPos.Map].CountEntrys;
  CounterEnd = 1;
  CounterStep = -1;
 }
 
  for (Counter = (CounterStart); ((CounterStep) > 0) ? (Counter <= (CounterEnd)) : (Counter >= (CounterEnd)); Counter = Counter + (CounterStep)) {
  
  UserIndex = ConnGroups[CenterPos.Map].UserEntrys[Counter];
  
  /* 'Is it in it's range of vision?? */
   if (InVisionRange(UserIndex, NpcX, NpcY)) {
   
   /* ' Can be atacked? */
    if (UserAtacable(UserIndex)) {
    
    /* ' Has Priority to attack magic clases */
     if (EsClaseMagica(UserIndex)) {
     BestTarget = UserIndex;
     break; /* FIXME: EXIT FOR */
     } else {
      if (BestTarget != 0) {
      
      /* ' Has priority to attack the nearest */
      Distance = UserDistance(UserIndex, NpcX, NpcY);
      
       if (Distance<BestTargetDistance) {
       BestTarget = UserIndex;
       BestTargetDistance = Distance;
      }
      
      } else {
      BestTarget = UserIndex;
      BestTargetDistance = UserDistance(UserIndex, NpcX, NpcY);
     }
     
    }
    
   }
   
  }
  
 }
 
 retval = BestTarget;
 
 return retval;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en ShooterBestTarget. Error: " + Err.Number + " - " + Err.description);
return retval;
}

 void clsClanPretoriano::ShooterMove(int NpcIndex, int BestTarget) {
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 24/06/2010 */
 /* 'Vamos a setear el hold on del cazador en el medio entre el rey */
 /* 'y el atacante. De esta manera se lo podra atacar aun asi está lejos */
 /* 'pero sin alejarse del rango de los an hoax vorps de los */
 /* 'clerigos o rey. A menos q este paralizado, claro */
 /* '*************************************************** */
 
 /* FIXME: ON ERROR GOTO ErrHandler */
 
  /* ' If paralized can't move */
  if (Npclist[NpcIndex].flags.Paralizado == 1) {
  return;
  }
  
  /* ' Only applies to clan map */
  if (Npclist[NpcIndex].Pos.Map != CenterPos.Map) {
  return;
  }
  
  /* ' If it's far from protection then returns to center */
   if (FarFromTeam(NpcIndex)) {
   ReturnToCenter(NpcIndex);
   return;
  }
  
  /* ' Don't go too far from center */
   if (vb6::Abs(CenterPos.X-Npclist[NpcIndex].Pos.X)>4 || vb6::Abs(CenterPos.Y-Npclist[NpcIndex].Pos.Y)>4) {
   ReturnToCenter(NpcIndex);
   return;
  }
  
  /* ' If has attacked someone, then go close to him */
   if (BestTarget>0) {
   
   GreedyWalkTo(NpcIndex, CenterPos.Map, CenterPos.X+((UserList[BestTarget].Pos.X-CenterPos.X)/2), CenterPos.Y+((UserList[BestTarget].Pos.Y-CenterPos.Y)/2));
   return;
   } else {
   
   /* ' Search for aproaching enemies */
   int Counter;
   int UserIndex;
   
    for (Counter = (1); Counter <= (ConnGroups[CenterPos.Map].CountEntrys); Counter++) {
    
    UserIndex = ConnGroups[CenterPos.Map].UserEntrys[Counter];
    
    /* 'Is it in extended range of vision from center position?? */
     if (InVisionRange(UserIndex, CenterPos.X, CenterPos.Y, true)) {
     
     /* ' Can be atacked? */
      if (UserAtacable(UserIndex)) {
      
       GreedyWalkTo(NpcIndex, CenterPos.Map, UserList[UserIndex].Pos.X, UserList[UserIndex].Pos.Y);
      
      return;
     }
     
    }
   }
  }
  
  /* 'Returns to center if no target found */
  if (Npclist[NpcIndex].CanAttack == 1) {
  ReturnToCenter(NpcIndex);
  }
  
 return;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en ShooterMove. Error: " + Err.Number + " - " + Err.description);
}

 void clsClanPretoriano::AI_Thief(int NpcIndex) {
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: - */
 /* '*************************************************** */
 /* FIXME: ON ERROR GOTO ErrHandler */
 
 int BestTarget;
 int Action;
 
 /* ' First choose best target */
 BestTarget = ThiefBestTarget(NpcIndex, Action);
 
 /* ' Perform's thief action acording to its priorities */
 ThiefPerfomAction(NpcIndex, BestTarget, Action);
 
 return;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en AI_Thief. Error: " + Err.Number + " - " + Err.description);
}

 int clsClanPretoriano::ThiefBestTarget(int NpcIndex, int & Action) {
 int retval;
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 26/06/2010 */
 /* 'Picks the best target according to the following criteria: */
 /* '1) Has priority to attack hunters. */
 /* '2) Targets the nearer user. */
 /* '*************************************************** */
 
 /* FIXME: ON ERROR GOTO ErrHandler */
 
 int UserIndex;
 int Counter;
 
 int BestTarget;
 int BestTargetDistance;
 
 int NpcX;
 int NpcY;
 int Distance;
 
 NpcX = Npclist[NpcIndex].Pos.X;
 NpcY = Npclist[NpcIndex].Pos.Y;
 
 int CounterStart;
 int CounterEnd;
 int CounterStep;
 
 /* ' To avoid that all attack the same target */
 CounterStep = RandomNumber(0, 1);
  if (CounterStep == 1) {
  CounterStart = 1;
  CounterEnd = ConnGroups[CenterPos.Map].CountEntrys;
  } else {
  CounterStart = ConnGroups[CenterPos.Map].CountEntrys;
  CounterEnd = 1;
  CounterStep = -1;
 }
 
  for (Counter = (CounterStart); ((CounterStep) > 0) ? (Counter <= (CounterEnd)) : (Counter >= (CounterEnd)); Counter = Counter + (CounterStep)) {
  
  UserIndex = ConnGroups[CenterPos.Map].UserEntrys[Counter];
  
  /* 'Is it in it's range of vision?? */
   if (InVisionRange(UserIndex, NpcX, NpcY)) {
   
   /* ' Can be atacked? */
    if (UserAtacable(UserIndex, false)) {
    /* ' Checks limits in order to avoid to separate it from the rest of the clan */
     if (UserReachable(NpcIndex, UserIndex)) {
     
     /* ' Is it a hunter? => Has priority */
      if (UserList[UserIndex].clase == eClass_Hunter) {
      BestTarget = UserIndex;
      BestTargetDistance = UserDistance(UserIndex, NpcX, NpcY);
      break; /* FIXME: EXIT FOR */
     }
     
      if (BestTarget != 0) {
      
      /* ' Has priority to attack the nearest */
      Distance = UserDistance(UserIndex, NpcX, NpcY);
      
       if (Distance<BestTargetDistance) {
       BestTarget = UserIndex;
       BestTargetDistance = Distance;
      }
      
      } else {
      BestTarget = UserIndex;
      BestTargetDistance = UserDistance(UserIndex, NpcX, NpcY);
     }
     
    }
    
   }
   
  }
  
 }
 
 /* ' Couldn't find anyone */
  if (BestTarget == 0) {
  Action = eThiefAction_None;
  } else {
  /* ' if close to target => Snatch/Steal */
   if (BestTargetDistance<=THIEF_STEAL_DISTANCE) {
   Action = eThiefAction_Steal;
   
   /* ' Too far => Attack while aproaching */
   } else {
   Action = eThiefAction_Attack;
  }
 }
 
 retval = BestTarget;
 
 return retval;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en ThiefBestTarget. Error: " + Err.Number + " - " + Err.description);
return retval;
}

 void clsClanPretoriano::ThiefPerfomAction(int NpcIndex, int BestTarget, int Action) {
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 28/10/2010 */
 /* '28/10/2010: ZaMa - Now thief doesn't steal/snatch admins. */
 /* '*************************************************** */
 /* FIXME: ON ERROR GOTO ErrHandler */
 
 int WeaponEqpSlot;
 int MunicionEqpSlot;
 
  switch (Action) {
   
   case eThiefAction_Attack:
   case eThiefAction_Steal:
   
   /* ' Can't do anything */
    if (Npclist[NpcIndex].CanAttack == 1) {
    
    /* ' Attack with arrow */
     if (Action == eThiefAction_Attack) {
     NpcLanzaSpellSobreUser(NpcIndex, BestTarget, Npclist[NpcIndex].Spells[eThiefSpells_Arrow], false, true);
     
     /* ' Can paralize */
      if (RandomNumber(1, 100)<10) {
      NpcLanzaSpellSobreUser(NpcIndex, BestTarget, Npclist[NpcIndex].Spells[eThiefSpells_Paralisis], false, true);
      WriteConsoleMsg(BestTarget, "¡¡" + Npclist[NpcIndex].Name + " te ha paralizado con su golpe!!", FontTypeNames_FONTTYPE_VENENO);
      
      /* ' Can unequip weapon */
      } else if (RandomNumber(1, 100)<22) {
      
      WeaponEqpSlot = UserList[BestTarget].Invent.WeaponEqpSlot;
      if (WeaponEqpSlot != 0) {
      Desequipar(BestTarget, WeaponEqpSlot, true);
      }
      
     }
     
     /* ' Try to snatch/Steal (except for admins) */
     } else if (!EsGm(BestTarget)) {
     
     /* ' Can snatch weapon or arrows */
      if (RandomNumber(1, 100)<16) {
      
      WeaponEqpSlot = UserList[BestTarget].Invent.WeaponEqpSlot;
       if (WeaponEqpSlot != 0) {
       
        if (SnatchItem(NpcIndex, BestTarget, WeaponEqpSlot)) {
        WriteConsoleMsg(BestTarget, "¡¡" + Npclist[NpcIndex].Name + " te ha arrebatado tu arma!!", FontTypeNames_FONTTYPE_VENENO);
       }
       
       } else {
       MunicionEqpSlot = UserList[BestTarget].Invent.MunicionEqpSlot;
        if (MunicionEqpSlot != 0) {
        
         if (SnatchItem(NpcIndex, BestTarget, MunicionEqpSlot)) {
         WriteConsoleMsg(BestTarget, "¡¡" + Npclist[NpcIndex].Name + " te ha arrebatado tus municiones!!", FontTypeNames_FONTTYPE_VENENO);
        }
        
       }
      }
      
      /* ' Can steal the items of a slot */
      } else if (RandomNumber(1, 100)<16) {
      
      int Slot;
      Slot = RandomNumber(1, UserList[BestTarget].CurrentInventorySlots);
      
       if (ThiefStealITem(NpcIndex, BestTarget, Slot)) {
       WriteConsoleMsg(BestTarget, "¡¡" + Npclist[NpcIndex].Name + " te está robando!!", FontTypeNames_FONTTYPE_VENENO);
      }
      
     }
    }
    
   }
   
   /* ' Has chances of becoming invisible (if visible) */
    if (Npclist[NpcIndex].flags.invisible == 0) {
    
    if (RandomNumber(1, 100)<25) {
    ThiefTurnInvisible(NpcIndex, true);
    }
    
    /* ' Is invisible, can turn visible. */
    } else {
    if (RandomNumber(1, 100)<13) {
    ThiefTurnInvisible(NpcIndex, false);
    }
   }
   
   /* ' Get closer to target */
   GreedyWalkTo(NpcIndex, CenterPos.Map, UserList[BestTarget].Pos.X, UserList[BestTarget].Pos.Y);
   
   break;
   
   case eThiefAction_None:
   
   /* ' Turns visible if no threat */
   if (Npclist[NpcIndex].flags.invisible == 1) {
   ThiefTurnInvisible(NpcIndex, false);
   }
   
   ReturnToCenter(NpcIndex);
   
  break;
  }
  
 return;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en ThiefPerfomAction. Error: " + Err.Number + " - " + Err.description);
}

 bool clsClanPretoriano::SnatchItem(int NpcIndex, int TargetIndex, int Slot) {
 bool retval;
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 25/09/2010 */
 /* 'Snatchs slot items from user. No validations are made bacause it's either weapon or munition. */
 /* '*************************************************** */
 /* FIXME: ON ERROR GOTO ErrHandler */
 
 struct Obj DropObj;
 struct WorldPos nPos;
 
  DropObj.Amount = UserList[TargetIndex].Invent.Object[Slot].Amount;
  DropObj.ObjIndex = UserList[TargetIndex].Invent.Object[Slot].ObjIndex;
  
  /* ' Search for suitable place to drop item */
  Tilelibre(UserList[TargetIndex].Pos, nPos, DropObj, false, true);
  
  /* ' Found any? */
   if (nPos.X != 0 && nPos.Y != 0) {
   /* ' Drop it */
   MakeObj(DropObj, nPos.Map, nPos.X, nPos.Y);
   QuitarUserInvItem(TargetIndex, Slot, DropObj.Amount);
   UpdateUserInv(false, TargetIndex, Slot);
   
   /* ' Suceed */
   retval = true;
  }
 
 return retval;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en SnatchItem. Error: " + Err.Number + " - " + Err.description);
return retval;
}

 bool clsClanPretoriano::ThiefStealITem(int NpcIndex, int TargetIndex, int Slot) {
 bool retval;
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 25/09/2010 */
 /* 'Steal slot items from user. If no space in thief's inventory, drop it on floor. */
 /* '22/10/2010: ZaMa - Now thief doesn't try to stel slots with no items in it. */
 /* '*************************************************** */
 struct Obj StolenObj;
 int NroItems;
 
 /* ' If doesn't have any item, the doesn't do anything */
 if (UserList[TargetIndex].Invent.Object[Slot].ObjIndex == 0) {
 return retval;
 }
 
 /* ' If not stealable, then don't do anything */
 if (!ObjEsRobable(TargetIndex, Slot)) {
 return retval;
 }
 
 /* ' If thief's inventory is full, then snatch it */
 NroItems = Npclist[NpcIndex].Invent.NroItems;
  if (NroItems == 20) {
  
  retval = SnatchItem(NpcIndex, TargetIndex, Slot);
  
  /* ' Steal it */
  } else {
  
  StolenObj.Amount = UserList[TargetIndex].Invent.Object[Slot].Amount;
  StolenObj.ObjIndex = UserList[TargetIndex].Invent.Object[Slot].ObjIndex;
  
  /* ' Add it to Thief inventory */
   NroItems = NroItems+1;
   Npclist[NpcIndex].Invent.Object[NroItems].Amount = StolenObj.Amount;
   Npclist[NpcIndex].Invent.Object[NroItems].ObjIndex = StolenObj.ObjIndex;
   Npclist[NpcIndex].Invent.NroItems = NroItems;
  
  /* ' Take it from user inventory */
  QuitarUserInvItem(TargetIndex, Slot, StolenObj.Amount);
  UpdateUserInv(false, TargetIndex, Slot);
  
  retval = true;
  
 }
 
return retval;
}

 void clsClanPretoriano::ThiefTurnInvisible(int NpcIndex, bool TurnVisible) {
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 26/09/2010 */
 /* 'Turn thief visible/Invisible. */
 /* '*************************************************** */
 
   if (TurnVisible) {
   Npclist[NpcIndex].flags.invisible = 1;
   } else {
   Npclist[NpcIndex].flags.invisible = 0;
  }
  
  SendData(SendTarget_ToNPCArea, NpcIndex, PrepareMessageSetInvisible(Npclist[NpcIndex].Char.CharIndex, TurnVisible));
  
}

 bool clsClanPretoriano::TargetClose(struct WorldPos & Pos) {
 bool retval;
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 05/07/2010 */
 /* 'Checks if there is any attackable user sorrounding the given position. */
 /* '*************************************************** */
 int UserIndex;
 
 struct WorldPos nPos;
 int headingloop;
 
  for (headingloop = (eHeading_NORTH); headingloop <= (eHeading_WEST); headingloop++) {
  
  nPos = Pos;
  HeadtoPos(headingloop, nPos);
  
  UserIndex = MapData[nPos.Map][nPos.X][nPos.Y].UserIndex;
  
   if (UserIndex != 0) {
    if (UserAtacable(UserIndex)) {
    retval = true;
    return retval;
   }
  }
 }
 
return retval;
}

 int clsClanPretoriano::CheckNearUserPets(int NpcIndex, int UserIndex) {
 int retval;
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 09/07/2010 */
 /* 'Checks if there is a non-paralized user pet in cleric vision range. */
 /* '*************************************************** */
 int PetCounter;
 int PetIndex;
 
  if (UserList[UserIndex].NroMascotas == 0) {
  return retval;
  }
  
   for (PetCounter = (1); PetCounter <= (MAXMASCOTAS); PetCounter++) {
   
   PetIndex = UserList[UserIndex].MascotasIndex[PetCounter];
    if (PetIndex>0) {
    
     /* ' If it is visible for the Pretorian */
      if (InVisionRangeNpc(NpcIndex, Npclist[PetIndex].Pos.X, Npclist[PetIndex].Pos.Y)) {
      
      /* ' If not paralized then it's a suitable target */
       if (Npclist[PetIndex].flags.Paralizado == 0) {
       retval = PetIndex;
       return retval;
      }
      
     }
     
   }
   
  }
  
return retval;
}

 bool clsClanPretoriano::EsClaseMagica(int UserIndex) {
 bool retval;
 /* '*************************************************** */
 /* 'Author: Unkown */
 /* 'Last Modification: - */
 /* '*************************************************** */
 /* FIXME: ON ERROR GOTO ErrHandler */
 
  retval = UserList[UserIndex].clase == eClass_Mage || UserList[UserIndex].clase == eClass_Cleric || UserList[UserIndex].clase == eClass_Druid || UserList[UserIndex].clase == eClass_Bard;
 
 return retval;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en EsClaseMagica. Error: " + Err.Number + " - " + Err.description);
return retval;
}

 void clsClanPretoriano::GreedyWalkTo(int NpcIndex, int TargetMap, int TargetX, int TargetY) {
 /* '*************************************************** */
 /* 'Author: Unknown */
 /* '  Este procedimiento es llamado cada vez que un NPC deba ir */
 /* '  a otro lugar en el mismo TargetMap. Utiliza una técnica */
 /* '  de programación greedy no determinística. */
 /* '  Cada paso azaroso que me acerque al destino, es un buen paso. */
 /* '  Si no hay mejor paso válido, entonces hay que volver atrás y reintentar. */
 /* '  Si no puedo moverme, me considero piketeado */
 /* '  La funcion es larga, pero es O(1) - orden algorítmico temporal constante */
 /* 'Last Modification: 26/09/2010 */
 /* 'Rapsodius - Changed Mod by And for speed */
 /* '26/09/2010: ZaMa - Now make movements as normal npcs, which allows to kick caspers and invisible admins. */
 /* '*************************************************** */
 /* FIXME: ON ERROR GOTO ErrHandler */
 
 int NpcX;
 int NpcY;
 int RandomDir;
 
  if (Npclist[NpcIndex].Pos.Map != TargetMap) {
  return;
  }
  
  NpcX = Npclist[NpcIndex].Pos.X;
  NpcY = Npclist[NpcIndex].Pos.Y;
 
 /* ' Arrived to destination */
 if ((NpcX == TargetX && NpcY == TargetY)) {
 return;
 }
 
 /* ' Try to reach target */
  if ((NpcX>TargetX)) {
  
  /* ' Target is Down-Left */
   if ((NpcY<TargetY)) {
   
   RandomDir = RandomNumber(0, 9);
   /* ''move down */
    if (((RandomDir && 1) == 0)) {
    
     if (MoveNPCChar(NpcIndex, eHeading_SOUTH)) {
     return;
     } else if (MoveNPCChar(NpcIndex, eHeading_WEST)) {
     return;
     } else if (MoveNPCChar(NpcIndex, eHeading_EAST)) {
     return;
     } else if (MoveNPCChar(NpcIndex, eHeading_NORTH)) {
     return;
    }
    
    } else {
    /* ''random first move */
     if (MoveNPCChar(NpcIndex, eHeading_WEST)) {
     return;
     } else if (MoveNPCChar(NpcIndex, eHeading_SOUTH)) {
     return;
     } else if (MoveNPCChar(NpcIndex, eHeading_EAST)) {
     return;
     } else if (MoveNPCChar(NpcIndex, eHeading_NORTH)) {
     return;
    }
    
   }
   
   /* ' Target is Up-Left */
   } else if ((NpcY>TargetY)) {
   
   RandomDir = RandomNumber(0, 9);
   /* ''move up */
    if (((RandomDir && 1) == 0)) {
    
     if (MoveNPCChar(NpcIndex, eHeading_NORTH)) {
     return;
     } else if (MoveNPCChar(NpcIndex, eHeading_WEST)) {
     return;
     } else if (MoveNPCChar(NpcIndex, eHeading_SOUTH)) {
     return;
     } else if (MoveNPCChar(NpcIndex, eHeading_EAST)) {
     return;
    }
    
    } else {
    /* ''random first move */
     if (MoveNPCChar(NpcIndex, eHeading_WEST)) {
     return;
     } else if (MoveNPCChar(NpcIndex, eHeading_NORTH)) {
     return;
     } else if (MoveNPCChar(NpcIndex, eHeading_SOUTH)) {
     return;
     } else if (MoveNPCChar(NpcIndex, eHeading_EAST)) {
     return;
    }
    
   }
   
   /* ' Target is Straight Left */
   } else {
   
    if (MoveNPCChar(NpcIndex, eHeading_WEST)) {
    return;
    } else if (MoveNPCChar(NpcIndex, eHeading_SOUTH)) {
    return;
    } else if (MoveNPCChar(NpcIndex, eHeading_NORTH)) {
    return;
    } else {
    /* ' If moves to east, algorithm fails because starts a loop */
    MoveFailed(NpcIndex);
   }
   
  }
  
  } else if ((NpcX<TargetX)) {
  
  /* ' Target is Down-Right */
   if ((NpcY<TargetY)) {
   
   RandomDir = RandomNumber(0, 9);
   /* ''move down */
    if (((RandomDir && 1) == 0)) {
    
     if (MoveNPCChar(NpcIndex, eHeading_SOUTH)) {
     return;
     } else if (MoveNPCChar(NpcIndex, eHeading_EAST)) {
     return;
     } else if (MoveNPCChar(NpcIndex, eHeading_WEST)) {
     return;
     } else if (MoveNPCChar(NpcIndex, eHeading_NORTH)) {
     return;
    }
    
    /* ''random first move */
    } else {
    
     if (MoveNPCChar(NpcIndex, eHeading_EAST)) {
     return;
     } else if (MoveNPCChar(NpcIndex, eHeading_SOUTH)) {
     return;
     } else if (MoveNPCChar(NpcIndex, eHeading_WEST)) {
     return;
     } else if (MoveNPCChar(NpcIndex, eHeading_NORTH)) {
     return;
    }
    
   }
   
   /* ' Target is Up-Right */
   } else if ((NpcY>TargetY)) {
   
   RandomDir = RandomNumber(0, 9);
   /* ''move up */
    if (((RandomDir && 1) == 0)) {
    
     if (MoveNPCChar(NpcIndex, eHeading_NORTH)) {
     return;
     } else if (MoveNPCChar(NpcIndex, eHeading_EAST)) {
     return;
     } else if (MoveNPCChar(NpcIndex, eHeading_WEST)) {
     return;
     } else if (MoveNPCChar(NpcIndex, eHeading_SOUTH)) {
     return;
    }
    
    } else {
    
     if (MoveNPCChar(NpcIndex, eHeading_EAST)) {
     return;
     } else if (MoveNPCChar(NpcIndex, eHeading_NORTH)) {
     return;
     } else if (MoveNPCChar(NpcIndex, eHeading_SOUTH)) {
     return;
     } else if (MoveNPCChar(NpcIndex, eHeading_WEST)) {
     return;
    }
    
   }
   
   /* ' Target is Straight Right */
   } else {
   
    if (MoveNPCChar(NpcIndex, eHeading_EAST)) {
    return;
    } else if (MoveNPCChar(NpcIndex, eHeading_SOUTH)) {
    return;
    } else if (MoveNPCChar(NpcIndex, eHeading_NORTH)) {
    return;
    } else {
    /* ' If moves to west, algorithm fails because starts a loop */
    MoveFailed(NpcIndex);
   }
   
  }
  
  /* ' Target is straight Up/Down */
  } else {
  
  /* ' Target is straight Up */
   if ((NpcY>TargetY)) {
   
    if (MoveNPCChar(NpcIndex, eHeading_NORTH)) {
    return;
    } else if (MoveNPCChar(NpcIndex, eHeading_EAST)) {
    return;
    } else if (MoveNPCChar(NpcIndex, eHeading_WEST)) {
    return;
    } else {
    /* ' If moves to south, algorithm fails because starts a loop */
    MoveFailed(NpcIndex);
   }
   
   /* ' Target is straight Down */
   } else {
   
    if (MoveNPCChar(NpcIndex, eHeading_SOUTH)) {
    return;
    } else if (MoveNPCChar(NpcIndex, eHeading_EAST)) {
    return;
    } else if (MoveNPCChar(NpcIndex, eHeading_WEST)) {
    return;
    } else {
    /* ' If moves to north, algorithm fails because starts a loop */
    MoveFailed(NpcIndex);
   }
   
  }
  
 }
 
 return;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en GreedyWalkTo. Error: " + Err.Number + " - " + Err.description);
}

 void clsClanPretoriano::MoveFailed(int NpcIndex) {
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 26/06/2010 */
 /* 'Npc shouts a message overhead because cannot move (to avoid a loop) */
 /* '*************************************************** */
 
   if (Npclist[NpcIndex].CanAttack == 1) {
    if ((RandomNumber(1, 100)>95)) {
    SendData(SendTarget_ToNPCArea, NpcIndex, PrepareMessageChatOverHead("Maldito bastardo, ¡Ven aquí!", Npclist[NpcIndex].Char.CharIndex, vbYellow));
    Npclist[NpcIndex].CanAttack = 0;
   }
  }
 
}

 void clsClanPretoriano::ReturnToCenter(int NpcIndex) {
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 19/09/2010 */
 /* 'Returns to the center, where the king is. */
 /* '*************************************************** */
 
 GreedyWalkTo(NpcIndex, CenterPos.Map, CenterPos.X, CenterPos.Y);
 
}

 bool clsClanPretoriano::FarFromTeam(vb6::Variant NpcIndex) {
 bool retval;
 /* '*************************************************** */
 /* 'Author: Unknown & ZaMa */
 /* 'Last Modification: 19/09/2010 */
 /* 'Checks if Npc is far from cleric protection ring */
 /* '*************************************************** */
 
 if (Npclist[NpcIndex].Pos.Map != CenterPos.Map) {
 return retval;
 }
 
 retval = (vb6::Abs(Npclist[NpcIndex].Pos.Y-CenterPos.Y)>MAX_DISTANCE) || (vb6::Abs(Npclist[NpcIndex].Pos.X-CenterPos.X)>MAX_DISTANCE);
 
 return retval;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en FarFromTeam. Error: " + Err.Number + " - " + Err.description);
return retval;
}

 bool clsClanPretoriano::UserReachable(int NpcIndex, int UserIndex) {
 bool retval;
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 19/09/2010 */
 /* 'Ignores users who are too far in order to avoid being separated from the rest of the team. */
 /* '*************************************************** */
 /* FIXME: ON ERROR GOTO ErrHandler */
 
 if (Npclist[NpcIndex].Pos.Map != CenterPos.Map) {
 return retval;
 }
 
 retval = (vb6::Abs(UserList[UserIndex].Pos.X-CenterPos.X)<MAX_DISTANCE) && (vb6::Abs(UserList[UserIndex].Pos.Y-CenterPos.Y)<MAX_DISTANCE);
 
 return retval;
 
 /* FIXME: ErrHandler : */
 ErrHandler:
 LogError("Error en UserReachable. Error: " + Err.Number + " - " + Err.description);
return retval;
}

 bool clsClanPretoriano::InVisionRange(int UserIndex, int X, int Y, bool ExtendedRange) {
 bool retval;
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 24/06/2010 */
 /* 'Checks whether user is in vision range or not */
 /* '*************************************************** */
 
 int Rango;
 Rango = vb6::val(vb6::IIf(ExtendedRange, 2, 1));
 
  retval = vb6::Abs(UserList[UserIndex].Pos.X-X)<=RANGO_VISION_X*Rango && vb6::Abs(UserList[UserIndex].Pos.Y-Y)<=RANGO_VISION_Y*Rango;
 
return retval;
}

 bool clsClanPretoriano::InVisionRangeNpc(int NpcIndex, int X, int Y, bool ExtendedRange) {
 bool retval;
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 24/06/2010 */
 /* 'Checks whether npc is in vision range or not */
 /* '*************************************************** */
 
 int Rango;
 Rango = vb6::val(vb6::IIf(ExtendedRange, 2, 1));
 
  retval = vb6::Abs(Npclist[NpcIndex].Pos.X-X)<=RANGO_VISION_X*Rango && vb6::Abs(Npclist[NpcIndex].Pos.Y-Y)<=RANGO_VISION_Y*Rango;
 
return retval;
}

 bool clsClanPretoriano::UserAtacable(int UserIndex, bool CheckVisibility, bool AttackAdmin) {
 bool retval;
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 05/10/2010 */
 /* 'DEtermines whether the user can be atacked or not */
 /* '05/10/2010: ZaMa - Now doesn't allow to attack admins sometimes. */
 /* '*************************************************** */
 
  retval = !UserList[UserIndex].flags.EnConsulta && UserList[UserIndex].flags.AdminInvisible == 0 && UserList[UserIndex].flags.AdminPerseguible && UserList[UserIndex].flags.Muerto == 0;
  
   if (CheckVisibility) {
   retval = retval && UserList[UserIndex].flags.Oculto == 0 && UserList[UserIndex].flags.invisible == 0;
  }
  
   if (!AttackAdmin) {
   retval = retval && (!EsGm(UserIndex));
  }
  
return retval;
}

 int clsClanPretoriano::UserDistance(int UserIndex, int X, int Y) {
 int retval;
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 24/06/2010 */
 /* 'Calculates the user distance according to the given coords. */
 /* '*************************************************** */
 
  retval = vb6::Abs(X-UserList[UserIndex].Pos.X)+vb6::Abs(Y-UserList[UserIndex].Pos.Y);
 
return retval;
}

 int clsClanPretoriano::NpcDistance(int NpcIndex, int X, int Y) {
 int retval;
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 24/06/2010 */
 /* 'Calculates the npc distance according to the given coords. */
 /* '*************************************************** */
 
  retval = vb6::Abs(X-Npclist[NpcIndex].Pos.X)+vb6::Abs(Y-Npclist[NpcIndex].Pos.Y);
 
return retval;
}

 void clsClanPretoriano::MuerePretoriano(int NpcIndex) {
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 27/06/2010 */
 /* 'Eliminates the pretorian from the current alive ones, and respawn the clan if in pretorian's default map. */
 /* '*************************************************** */
 
 int PretoIndex;
 
  for (PretoIndex = (1); PretoIndex <= (NRO_PRETORIANOS); PretoIndex++) {
  /* ' Remove npc index */
   if (Pretorianos[PretoIndex].NpcIndex == NpcIndex) {
   Pretorianos[PretoIndex].NpcIndex = 0;
   ClanMembersAlive = ClanMembersAlive-1;
   
   /* ' Entire clan has been defeated */
    if (ClanMembersAlive == 0) {
    /* ' Respawn it? (Only allowed in pretorian default map) */
     if (RespawnClan) {
     
     struct WorldPos NewSpawnPos;
     
     /* ' Switch respawn place (alternate between two places) */
      if (CenterPos.X == LeftSpawnPos.X) {
      NewSpawnPos = RightSpawnPos;
      } else {
      NewSpawnPos = LeftSpawnPos;
     }
     
     /* ' Spawn it */
     SpawnClan(NewSpawnPos.Map, NewSpawnPos.X, NewSpawnPos.Y, ClanIndex, true);
     } else {
     ClanActive = false;
    }
   }
   
   return;
  }
 }
 
}

 int clsClanPretoriano::AllyParalyzed(int NpcIndex, bool ExtendedRange) {
 int retval;
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 27/06/2010 */
 /* 'Returns the index of the paralized ally if exists one. */
 /* '*************************************************** */
 
 int PretoIndex;
 int AllyIndex;
 
  for (PretoIndex = (1); PretoIndex <= (NRO_PRETORIANOS); PretoIndex++) {
  
  AllyIndex = Pretorianos[PretoIndex].NpcIndex;
   if (AllyIndex != 0) {
    if (Npclist[AllyIndex].flags.Paralizado == 1) {
     if (InVisionRangeNpc(AllyIndex, Npclist[NpcIndex].Pos.X, Npclist[NpcIndex].Pos.Y, ExtendedRange)) {
     retval = AllyIndex;
     return retval;
    }
   }
  }
  
 }
 
return retval;
}

 int clsClanPretoriano::AllyInjured(int NpcIndex) {
 int retval;
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 09/07/2010 */
 /* 'Returns the index of the first found injured ally if exists one. */
 /* '*************************************************** */
 
 int PretoIndex;
 int AllyIndex;
 
  for (PretoIndex = (1); PretoIndex <= (NRO_PRETORIANOS); PretoIndex++) {
  
  AllyIndex = Pretorianos[PretoIndex].NpcIndex;
   if (AllyIndex != 0) {
     if (Npclist[AllyIndex].Stats.MinHp<Npclist[AllyIndex].Stats.MaxHp) {
      if (InVisionRangeNpc(NpcIndex, Npclist[AllyIndex].Pos.X, Npclist[AllyIndex].Pos.Y, false)) {
      retval = AllyIndex;
      return retval;
     }
    }
  }
  
 }
 
return retval;
}

 int clsClanPretoriano::AllyPoisoned(int NpcIndex) {
 int retval;
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 19/09/2010 */
 /* 'Returns the index of the poisoned ally if exists one. */
 /* '*************************************************** */
 
 int PretoIndex;
 int AllyIndex;
 
  for (PretoIndex = (1); PretoIndex <= (NRO_PRETORIANOS); PretoIndex++) {
  
  AllyIndex = Pretorianos[PretoIndex].NpcIndex;
   if (AllyIndex != 0) {
    if (Npclist[AllyIndex].flags.Envenenado == 1) {
     if (InVisionRangeNpc(AllyIndex, Npclist[NpcIndex].Pos.X, Npclist[NpcIndex].Pos.Y)) {
     retval = AllyIndex;
     return retval;
    }
   }
  }
  
 }
 
return retval;
}

 int clsClanPretoriano::AllyDead() {
 int retval;
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 19/09/2010 */
 /* 'Returns the Index of the first dead member found, if exists. */
 /* '*************************************************** */
 
 int PretoIndex;
 int AllyIndex;
 
  for (PretoIndex = (1); PretoIndex <= (NRO_PRETORIANOS); PretoIndex++) {
  
   if (Pretorianos[PretoIndex].NpcIndex == 0) {
   retval = PretoIndex;
   return retval;
  }
  
 }
 
return retval;
}

 bool clsClanPretoriano::CanAtackMember(int NpcIndex) {
 bool retval;
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 26/09/2010 */
 /* 'Returns true if given NpcIndex belongs to a normal clan member, o if king's alone. */
 /* '*************************************************** */
 
 /* ' King? */
  if (Pretorianos[1].NpcIndex == NpcIndex) {
  /* ' any member left? => Can't attack */
  if (ClanMembersAlive != 1) {
  return retval;
  }
 }
 
 retval = true;
 
return retval;
}

 int clsClanPretoriano::ClanMap() {
 int retval;
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 29/10/2010 */
 /* 'Returns the clan map */
 /* '*************************************************** */
 retval = CenterPos.Map;
return retval;
}

 bool clsClanPretoriano::Active() {
 bool retval;
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 29/10/2010 */
 /* 'Returns true if clan is active. */
 /* '*************************************************** */
 retval = ClanActive;
return retval;
}

 void clsClanPretoriano::DeleteClan() {
 /* '*************************************************** */
 /* 'Author: ZaMa */
 /* 'Last Modification: 29/10/2010 */
 /* 'Kill all alive members. */
 /* '*************************************************** */
 
 int PretoIndex;
 int NpcIndex;
 
  for (PretoIndex = (1); PretoIndex <= (NRO_PRETORIANOS); PretoIndex++) {
  
  NpcIndex = Pretorianos[PretoIndex].NpcIndex;
  if (NpcIndex != 0) {
  QuitarNPC(NpcIndex);
  }
  
  Pretorianos[PretoIndex].NpcIndex = 0;
  
 }
 
 ClanActive = false;
 
}

#endif
