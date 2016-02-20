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

#include "PathFinding.h"

#include <deque>
#include <limits>
#include <cmath>

namespace {

class PFDistanceCompare {
public:
	PFDistanceCompare(std::map<Position, int>* dist) : dist_(dist) {}

	bool operator()(const Position& a, const Position& b) const {
		auto pa = dist_->find(a);
		auto pb = dist_->find(b);
		if (pa == dist_->end() || pb == dist_->end())
			return std::numeric_limits<int>::max();
		return pa->second < pb->second;
	}

	std::map<Position, int>* dist_;
};

int H(const Position& a, const Position& b) {
	int r = (int)std::round(std::hypot((b.X - a.X), (b.Y - a.Y)) * 10);
	return r;
}

}

void SeekPath(int NpcIndex, int MaxSteps) {
	/*
	 * A* Path Finding, by Alejandro Santos.
	 */
	std::map<Position, int> f_score;
	std::map<Position, int> g_score;
	std::set<Position, PFDistanceCompare> Q{PFDistanceCompare(&f_score)};
	std::set<Position> closedset;
	std::map<Position, Position> came_from;

	int mapNum = Npclist[NpcIndex].Pos.Map;

	Position startPos;
	startPos.X = Npclist[NpcIndex].Pos.X;
	startPos.Y = Npclist[NpcIndex].Pos.Y;

	Position endPos;
	endPos = Npclist[NpcIndex].PFINFO.Target;

	came_from[startPos] = startPos;
	f_score[startPos] = H(startPos, endPos);
	g_score[startPos] = 0;
	Q.insert(startPos);

	bool found = false;

	while (!Q.empty()) {
		Position e = *Q.begin();

		if (e == endPos) {
			found = true;
			break;
		}

		Q.erase(Q.begin());
		closedset.insert(e);

		int tentative_g_score = g_score[e] + 1; // dist_between(e, w) == 1

		for (int k = eHeading_NORTH; k <= eHeading_WEST; ++k) {
			Position w{e};
			HeadtoPos(static_cast<eHeading>(k), w);

			if (closedset.find(w) != closedset.end()) {
				continue;
			}

			if (!LegalPosNPC(mapNum, w.X, w.Y, Npclist[NpcIndex].flags.AguaValida == 1, Npclist[NpcIndex].MaestroUser != 0)) {
				if (w != endPos) {
					continue;
				}
			}

			int g_score_w;

			{
				auto p = g_score.find(w);
				g_score_w = (p != g_score.end()) ? p->second : std::numeric_limits<int>::max();
			}

			if ((Q.find(w) == Q.end() || tentative_g_score < g_score_w) && (tentative_g_score <= MaxSteps)){
				came_from[w] = e;
				g_score[w] = tentative_g_score;
				f_score[w] = tentative_g_score + H(w, endPos);
				Q.insert(w);
			}
		}
	}

	if (found) {
		/* Rebuild Path */

		// We stop next to the target, not on top of it.
		int pathLen = g_score[endPos];
		if (pathLen < 0) pathLen = 0;

		Npclist[NpcIndex].PFINFO.Path.redim(1, pathLen);

		Position w{endPos};

		for (int k = pathLen; k >= 1; --k) {
			Npclist[NpcIndex].PFINFO.Path[k] = w;
			w = came_from[w];
		}

		Npclist[NpcIndex].PFINFO.NoPath = false;
		Npclist[NpcIndex].PFINFO.PathLenght = pathLen;
		Npclist[NpcIndex].PFINFO.CurPos = 1;
	} else {
		/* Not found */
		Npclist[NpcIndex].PFINFO.NoPath = true;
		Npclist[NpcIndex].PFINFO.PathLenght = 0;
	}
}
