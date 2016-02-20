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

#include "Statistics.h"


static vb6::array<struct trainningData> trainningInfo;

static vb6::array<struct fragLvlRace> fragLvlRaceData;
static vb6::array<struct fragLvlLvl> fragLvlLvlData;
static vb6::array<vb6::array<int> > fragAlignmentLvlData;

/* 'Currency just in case.... chats are way TOO often... */
static vb6::array<double> keyOcurrencies;

void InitializeStatistics() {
	trainningInfo.redim(0);
	trainningInfo.redim(1, MaxUsers);

	fragLvlRaceData.redim(1, 7); /* XXX */
	fragLvlLvlData.redim(1, 7); /* XXX */
	fragAlignmentLvlData.redim(1, 50); /* XXX MULTIDIMENSIONAL [('1', '50'), ('1', '4')] */
	for (auto & v : fragAlignmentLvlData) {
		v.redim(1, 4);
	}
	keyOcurrencies.redim(0, 255); /* XXX */
}

 void UserConnected(int UserIndex) {
 /* '*************************************************** */
 /* 'Author: Unknown */
 /* 'Last Modification: - */
 /* ' */
 /* '*************************************************** */
 
 /* 'A new user connected, load it's trainning time count */
 trainningInfo[UserIndex].trainningTime = vb6::val(GetVar(GetCharPath(UserList[UserIndex].Name), "RESEARCH", "TrainningTime", 30));
 
 trainningInfo[UserIndex].startTick = (vb6::GetTickCount());
}

 void UserDisconnected(int UserIndex) {
 /* '*************************************************** */
 /* 'Author: Unknown */
 /* 'Last Modification: - */
 /* ' */
 /* '*************************************************** */
 
  /* 'Update trainning time */
  trainningInfo[UserIndex].trainningTime = trainningInfo[UserIndex].trainningTime+(getInterval((vb6::GetTickCount()), trainningInfo[UserIndex].startTick)/1000);
  
  trainningInfo[UserIndex].startTick = vb6::GetTickCount();
  
  /* 'Store info in char file */
  WriteVar(GetCharPath(UserList[UserIndex].Name), "RESEARCH", "TrainningTime", vb6::CStr(trainningInfo[UserIndex].trainningTime));
}

 void UserLevelUp(int UserIndex) {
 /* '*************************************************** */
 /* 'Author: Unknown */
 /* 'Last Modification: - */
 /* ' */
 /* '*************************************************** */

  /* 'Log the data */
  /* FIXME: OPEN App . Path & "\\logs\\statistics.log" FOR Append Shared AS handle */
  
  /* FIXME: PRINT # handle , UCase $ ( UserList ( UserIndex ) . Name ) & " completó el nivel " & CStr ( UserList ( UserIndex ) . Stats . ELV ) & " en " & CStr ( . trainningTime + ( getInterval ( ( GetTickCount ( ) AND &H7FFFFFFF ) , . startTick ) / 1000 ) ) & " segundos." */
  
  /* FIXME: CLOSE handle */
  
  /* 'Reset data */
  trainningInfo[UserIndex].trainningTime = 0;
  trainningInfo[UserIndex].startTick = vb6::GetTickCount();
}

 void StoreFrag(int killer, int victim) {
 /* '*************************************************** */
 /* 'Author: Unknown */
 /* 'Last Modification: - */
 /* ' */
 /* '*************************************************** */
 
 int clase = 0;
 int raza = 0;
 int alignment = 0;
 
 (void)clase;
 (void)raza;
 (void)alignment;

 if (UserList[victim].Stats.ELV>50 || UserList[killer].Stats.ELV>50) {
 return;
 }
 
 switch (UserList[killer].clase) {
  case eClass_Assasin:
  clase = 1;
  
  break;
  
  case eClass_Bard:
  clase = 2;
  
  break;
  
  case eClass_Mage:
  clase = 3;
  
  break;
  
  case eClass_Paladin:
  clase = 4;
  
  break;
  
  case eClass_Warrior:
  clase = 5;
  
  break;
  
  case eClass_Cleric:
  clase = 6;
  
  break;
  
  case eClass_Hunter:
  clase = 7;
  
  break;
  
  default:
  return;
 break;
 }
 
 switch (UserList[killer].raza) {
  case eRaza_Elfo:
  raza = 1;
  
  break;
  
  case eRaza_Drow:
  raza = 2;
  
  break;
  
  case eRaza_Enano:
  raza = 3;
  
  break;
  
  case eRaza_Gnomo:
  raza = 4;
  
  break;
  
  case eRaza_Humano:
  raza = 5;
  
  break;
  
  default:
  return;
 break;
 }
 
  if (criminal(killer)) {
   if (esCaos(killer)) {
   alignment = 2;
   } else {
   alignment = 3;
  }
  } else {
   if (esArmada(killer)) {
   alignment = 1;
   } else {
   alignment = 4;
  }
 }
 
#if 0
 fragLvlRaceData[clase].matrix[UserList[killer].Stats.ELV][raza] = fragLvlRaceData[clase].matrix[UserList[killer].Stats.ELV][raza]+1;
 
 fragLvlLvlData[clase].matrix[UserList[killer].Stats.ELV][UserList[victim].Stats.ELV] = fragLvlLvlData[clase].matrix[UserList[killer].Stats.ELV][UserList[victim].Stats.ELV]+1;
 
 fragAlignmentLvlData[UserList[killer].Stats.ELV][alignment] = fragAlignmentLvlData[UserList[killer].Stats.ELV][alignment]+1;
#endif
}

 void DumpStatistics() {
 /* '*************************************************** */
 /* 'Author: Unknown */
 /* 'Last Modification: - */
 /* ' */
 /* '*************************************************** */
 
 std::string LINE;
 int i;
 int j;
 
 /* FIXME: OPEN App . Path & "\\logs\\frags.txt" FOR OUTPUT AS handle */
 
 /* 'Save lvl vs lvl frag matrix for each class - we use GNU Octave's ASCII file format */
 
 /* FIXME: PRINT # handle , "# name: fragLvlLvl_Ase" */
 /* FIXME: PRINT # handle , "# type: matrix" */
 /* FIXME: PRINT # handle , "# rows: 50" */
 /* FIXME: PRINT # handle , "# columns: 50" */
 
  for (j = (1); j <= (50); j++) {
   for (i = (1); i <= (50); i++) {
   /* FIXME: LINE = LINE & " " & CStr ( fragLvlLvlData ( 1 ) . matrix ( i , j ) ) */
  }
  
  /* FIXME: PRINT # handle , LINE */
  /* FIXME: LINE = vbNullString */
 }
 
 /* FIXME: PRINT # handle , "# name: fragLvlLvl_Bar" */
 /* FIXME: PRINT # handle , "# type: matrix" */
 /* FIXME: PRINT # handle , "# rows: 50" */
 /* FIXME: PRINT # handle , "# columns: 50" */
 
  for (j = (1); j <= (50); j++) {
   for (i = (1); i <= (50); i++) {
   /* FIXME: LINE = LINE & " " & CStr ( fragLvlLvlData ( 2 ) . matrix ( i , j ) ) */
  }
  
  /* FIXME: PRINT # handle , LINE */
  /* FIXME: LINE = vbNullString */
 }
 
 /* FIXME: PRINT # handle , "# name: fragLvlLvl_Mag" */
 /* FIXME: PRINT # handle , "# type: matrix" */
 /* FIXME: PRINT # handle , "# rows: 50" */
 /* FIXME: PRINT # handle , "# columns: 50" */
 
  for (j = (1); j <= (50); j++) {
   for (i = (1); i <= (50); i++) {
   /* FIXME: LINE = LINE & " " & CStr ( fragLvlLvlData ( 3 ) . matrix ( i , j ) ) */
  }
  
  /* FIXME: PRINT # handle , LINE */
  /* FIXME: LINE = vbNullString */
 }
 
 /* FIXME: PRINT # handle , "# name: fragLvlLvl_Pal" */
 /* FIXME: PRINT # handle , "# type: matrix" */
 /* FIXME: PRINT # handle , "# rows: 50" */
 /* FIXME: PRINT # handle , "# columns: 50" */
 
  for (j = (1); j <= (50); j++) {
   for (i = (1); i <= (50); i++) {
   /* FIXME: LINE = LINE & " " & CStr ( fragLvlLvlData ( 4 ) . matrix ( i , j ) ) */
  }
  
  /* FIXME: PRINT # handle , LINE */
  /* FIXME: LINE = vbNullString */
 }
 
 /* FIXME: PRINT # handle , "# name: fragLvlLvl_Gue" */
 /* FIXME: PRINT # handle , "# type: matrix" */
 /* FIXME: PRINT # handle , "# rows: 50" */
 /* FIXME: PRINT # handle , "# columns: 50" */
 
  for (j = (1); j <= (50); j++) {
   for (i = (1); i <= (50); i++) {
   /* FIXME: LINE = LINE & " " & CStr ( fragLvlLvlData ( 5 ) . matrix ( i , j ) ) */
  }
  
  /* FIXME: PRINT # handle , LINE */
  /* FIXME: LINE = vbNullString */
 }
 
 /* FIXME: PRINT # handle , "# name: fragLvlLvl_Cle" */
 /* FIXME: PRINT # handle , "# type: matrix" */
 /* FIXME: PRINT # handle , "# rows: 50" */
 /* FIXME: PRINT # handle , "# columns: 50" */
 
  for (j = (1); j <= (50); j++) {
   for (i = (1); i <= (50); i++) {
   /* FIXME: LINE = LINE & " " & CStr ( fragLvlLvlData ( 6 ) . matrix ( i , j ) ) */
  }
  
  /* FIXME: PRINT # handle , LINE */
  /* FIXME: LINE = vbNullString */
 }
 
 /* FIXME: PRINT # handle , "# name: fragLvlLvl_Caz" */
 /* FIXME: PRINT # handle , "# type: matrix" */
 /* FIXME: PRINT # handle , "# rows: 50" */
 /* FIXME: PRINT # handle , "# columns: 50" */
 
  for (j = (1); j <= (50); j++) {
   for (i = (1); i <= (50); i++) {
   /* FIXME: LINE = LINE & " " & CStr ( fragLvlLvlData ( 7 ) . matrix ( i , j ) ) */
  }
  
  /* FIXME: PRINT # handle , LINE */
  /* FIXME: LINE = vbNullString */
 }
 
 /* 'Save lvl vs race frag matrix for each class - we use GNU Octave's ASCII file format */
 
 /* FIXME: PRINT # handle , "# name: fragLvlRace_Ase" */
 /* FIXME: PRINT # handle , "# type: matrix" */
 /* FIXME: PRINT # handle , "# rows: 5" */
 /* FIXME: PRINT # handle , "# columns: 50" */
 
  for (j = (1); j <= (5); j++) {
   for (i = (1); i <= (50); i++) {
   /* FIXME: LINE = LINE & " " & CStr ( fragLvlRaceData ( 1 ) . matrix ( i , j ) ) */
  }
  
  /* FIXME: PRINT # handle , LINE */
  /* FIXME: LINE = vbNullString */
 }
 
 /* FIXME: PRINT # handle , "# name: fragLvlRace_Bar" */
 /* FIXME: PRINT # handle , "# type: matrix" */
 /* FIXME: PRINT # handle , "# rows: 5" */
 /* FIXME: PRINT # handle , "# columns: 50" */
 
  for (j = (1); j <= (5); j++) {
   for (i = (1); i <= (50); i++) {
   /* FIXME: LINE = LINE & " " & CStr ( fragLvlRaceData ( 2 ) . matrix ( i , j ) ) */
  }
  
  /* FIXME: PRINT # handle , LINE */
  /* FIXME: LINE = vbNullString */
 }
 
 /* FIXME: PRINT # handle , "# name: fragLvlRace_Mag" */
 /* FIXME: PRINT # handle , "# type: matrix" */
 /* FIXME: PRINT # handle , "# rows: 5" */
 /* FIXME: PRINT # handle , "# columns: 50" */
 
  for (j = (1); j <= (5); j++) {
   for (i = (1); i <= (50); i++) {
   /* FIXME: LINE = LINE & " " & CStr ( fragLvlRaceData ( 3 ) . matrix ( i , j ) ) */
  }
  
  /* FIXME: PRINT # handle , LINE */
  /* FIXME: LINE = vbNullString */
 }
 
 /* FIXME: PRINT # handle , "# name: fragLvlRace_Pal" */
 /* FIXME: PRINT # handle , "# type: matrix" */
 /* FIXME: PRINT # handle , "# rows: 5" */
 /* FIXME: PRINT # handle , "# columns: 50" */
 
  for (j = (1); j <= (5); j++) {
   for (i = (1); i <= (50); i++) {
   /* FIXME: LINE = LINE & " " & CStr ( fragLvlRaceData ( 4 ) . matrix ( i , j ) ) */
  }
  
  /* FIXME: PRINT # handle , LINE */
  /* FIXME: LINE = vbNullString */
 }
 
 /* FIXME: PRINT # handle , "# name: fragLvlRace_Gue" */
 /* FIXME: PRINT # handle , "# type: matrix" */
 /* FIXME: PRINT # handle , "# rows: 5" */
 /* FIXME: PRINT # handle , "# columns: 50" */
 
  for (j = (1); j <= (5); j++) {
   for (i = (1); i <= (50); i++) {
   /* FIXME: LINE = LINE & " " & CStr ( fragLvlRaceData ( 5 ) . matrix ( i , j ) ) */
  }
  
  /* FIXME: PRINT # handle , LINE */
  /* FIXME: LINE = vbNullString */
 }
 
 /* FIXME: PRINT # handle , "# name: fragLvlRace_Cle" */
 /* FIXME: PRINT # handle , "# type: matrix" */
 /* FIXME: PRINT # handle , "# rows: 5" */
 /* FIXME: PRINT # handle , "# columns: 50" */
 
  for (j = (1); j <= (5); j++) {
   for (i = (1); i <= (50); i++) {
   /* FIXME: LINE = LINE & " " & CStr ( fragLvlRaceData ( 6 ) . matrix ( i , j ) ) */
  }
  
  /* FIXME: PRINT # handle , LINE */
  /* FIXME: LINE = vbNullString */
 }
 
 /* FIXME: PRINT # handle , "# name: fragLvlRace_Caz" */
 /* FIXME: PRINT # handle , "# type: matrix" */
 /* FIXME: PRINT # handle , "# rows: 5" */
 /* FIXME: PRINT # handle , "# columns: 50" */
 
  for (j = (1); j <= (5); j++) {
   for (i = (1); i <= (50); i++) {
   /* FIXME: LINE = LINE & " " & CStr ( fragLvlRaceData ( 7 ) . matrix ( i , j ) ) */
  }
  
  /* FIXME: PRINT # handle , LINE */
  /* FIXME: LINE = vbNullString */
 }
 
 /* 'Save lvl vs class frag matrix for each race - we use GNU Octave's ASCII file format */
 
 /* FIXME: PRINT # handle , "# name: fragLvlClass_Elf" */
 /* FIXME: PRINT # handle , "# type: matrix" */
 /* FIXME: PRINT # handle , "# rows: 7" */
 /* FIXME: PRINT # handle , "# columns: 50" */
 
  for (j = (1); j <= (7); j++) {
   for (i = (1); i <= (50); i++) {
   /* FIXME: LINE = LINE & " " & CStr ( fragLvlRaceData ( j ) . matrix ( i , 1 ) ) */
  }
  
  /* FIXME: PRINT # handle , LINE */
  /* FIXME: LINE = vbNullString */
 }
 
 /* FIXME: PRINT # handle , "# name: fragLvlClass_Dar" */
 /* FIXME: PRINT # handle , "# type: matrix" */
 /* FIXME: PRINT # handle , "# rows: 7" */
 /* FIXME: PRINT # handle , "# columns: 50" */
 
  for (j = (1); j <= (7); j++) {
   for (i = (1); i <= (50); i++) {
   /* FIXME: LINE = LINE & " " & CStr ( fragLvlRaceData ( j ) . matrix ( i , 2 ) ) */
  }
  
  /* FIXME: PRINT # handle , LINE */
  /* FIXME: LINE = vbNullString */
 }
 
 /* FIXME: PRINT # handle , "# name: fragLvlClass_Dwa" */
 /* FIXME: PRINT # handle , "# type: matrix" */
 /* FIXME: PRINT # handle , "# rows: 7" */
 /* FIXME: PRINT # handle , "# columns: 50" */
 
  for (j = (1); j <= (7); j++) {
   for (i = (1); i <= (50); i++) {
   /* FIXME: LINE = LINE & " " & CStr ( fragLvlRaceData ( j ) . matrix ( i , 3 ) ) */
  }
  
  /* FIXME: PRINT # handle , LINE */
  /* FIXME: LINE = vbNullString */
 }
 
 /* FIXME: PRINT # handle , "# name: fragLvlClass_Gno" */
 /* FIXME: PRINT # handle , "# type: matrix" */
 /* FIXME: PRINT # handle , "# rows: 7" */
 /* FIXME: PRINT # handle , "# columns: 50" */
 
  for (j = (1); j <= (7); j++) {
   for (i = (1); i <= (50); i++) {
   /* FIXME: LINE = LINE & " " & CStr ( fragLvlRaceData ( j ) . matrix ( i , 4 ) ) */
  }
  
  /* FIXME: PRINT # handle , LINE */
  /* FIXME: LINE = vbNullString */
 }
 
 /* FIXME: PRINT # handle , "# name: fragLvlClass_Hum" */
 /* FIXME: PRINT # handle , "# type: matrix" */
 /* FIXME: PRINT # handle , "# rows: 7" */
 /* FIXME: PRINT # handle , "# columns: 50" */
 
  for (j = (1); j <= (7); j++) {
   for (i = (1); i <= (50); i++) {
   /* FIXME: LINE = LINE & " " & CStr ( fragLvlRaceData ( j ) . matrix ( i , 5 ) ) */
  }
  
  /* FIXME: PRINT # handle , LINE */
  /* FIXME: LINE = vbNullString */
 }
 
 /* 'Save lvl vs alignment frag matrix for each race - we use GNU Octave's ASCII file format */
 
 /* FIXME: PRINT # handle , "# name: fragAlignmentLvl" */
 /* FIXME: PRINT # handle , "# type: matrix" */
 /* FIXME: PRINT # handle , "# rows: 4" */
 /* FIXME: PRINT # handle , "# columns: 50" */
 
  for (j = (1); j <= (4); j++) {
   for (i = (1); i <= (50); i++) {
   /* FIXME: LINE = LINE & " " & CStr ( fragAlignmentLvlData ( i , j ) ) */
  }
  
  /* FIXME: PRINT # handle , LINE */
  /* FIXME: LINE = vbNullString */
 }
 
 /* FIXME: CLOSE handle */
 
 /* 'Dump Chat statistics */
 
 /* FIXME: OPEN App . Path & "\\logs\\huffman.log" FOR OUTPUT AS handle */
 
 double Total = 0;
 
 /* 'Compute total characters */
  for (i = (0); i <= (255); i++) {
  Total = Total+keyOcurrencies[i];
 }
 
 /* 'Show each character's ocurrencies */
  if (Total != 0) {
   for (i = (0); i <= (255); i++) {
   /* FIXME: PRINT # handle , CStr ( i ) & "    " & CStr ( Round ( keyOcurrencies ( i ) / Total , 8 ) ) */
  }
 }
 
 /* FIXME: PRINT # handle , "TOTAL =    " & CStr ( Total ) */
 
 /* FIXME: CLOSE handle */
}

 void ParseChat(std::string & S) {
 /* '*************************************************** */
 /* 'Author: Unknown */
 /* 'Last Modification: - */
 /* ' */
 /* '*************************************************** */
 
 int i;
 int key;
 
  for (i = (1); i <= ((int)vb6::Len(S)); i++) {
  key = vb6::Asc(vb6::Mid(S, i, 1));
  
  keyOcurrencies[key] = keyOcurrencies[key]+1;
 }
 
 /* 'Add a NULL-terminated to consider that possibility too.... */
 keyOcurrencies[0] = keyOcurrencies[0]+1;
}
