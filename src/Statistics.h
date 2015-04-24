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


#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"


 struct trainningData {
 int startTick;
 int trainningTime;
};

 struct fragLvlRace {
 /* FIXME: MULTIDIMENSIONAL ARRAY 2: matrix ( 1 TO 50 , 1 TO 5 ) AS Long */
 int matrix;
};

 struct fragLvlLvl {
 /* FIXME: MULTIDIMENSIONAL ARRAY 2: matrix ( 1 TO 50 , 1 TO 50 ) AS Long */
 int matrix;
};

/* 'Currency just in case.... chats are way TOO often... */

 void InitializeStatistics();

 void UserConnected(int UserIndex);
 
 void UserDisconnected(int UserIndex);
 
 void UserLevelUp(int UserIndex);
 
 void StoreFrag(int killer, int victim);
 
 void DumpStatistics();
 
 void ParseChat(std::string & S);
 
#endif
