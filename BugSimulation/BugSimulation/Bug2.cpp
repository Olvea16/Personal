#include "stdafx.h"
#include "Bug2.h"


Bug2::Bug2()
{
}

Bug2::Bug2(Position<int> starting_position, Position<int> goal_position)
{
	pos = starting_position;
	goal = goal_position;

	std::vector<Position<int>> tempLine = getLine(goal - starting_position);
	Position<int> lastPos = Position<int>(0, 0);
	for (int i = 0; i < tempLine.size(); i++) {
		if ((tempLine[i] - lastPos).length() > 1) mLine.push_back(Position<int>(tempLine[i].x, lastPos.y) + starting_position);
		mLine.push_back(tempLine[i] + starting_position);
		lastPos = tempLine[i];
	}

	int dX = goal.x - pos.x;
	int dY = goal.y - pos.y;

	if (dX != 0 && dY != 0) circumventDir = ((dX / abs(dX)) * (dY / abs(dY)) * (dX - dY) / abs(dX - dY));
}


Bug2::~Bug2()
{
}

void Bug2::takeStep(std::vector<std::vector<tiles>> surroundingTiles)
{
    int mLineIndex = 0;
	bool onMLine = false;
	bool moved;

	switch (mode) {
	case eFollowingMLine:
  		for (; mLineIndex < mLine.size(); mLineIndex++) if (pos == mLine[mLineIndex]) break;
		if (mLineIndex != mLine.size() - 1) {
			Position<int> nextPos = mLine[mLineIndex + 1];
			if (surroundingTiles[(nextPos - pos).y + 1][(nextPos - pos).x + 1] != eObstacle) {
				pos = nextPos;
				if (pos == goal) mode = eDone;
				break;
			}
			else {
				mode = eCircumventingObstacle;
				mLine.erase(mLine.begin(), mLine.begin() + mLineIndex);
			}
		}
		else mode = eDone;

	case eCircumventingObstacle:
        moved = moveAlongObstacle(surroundingTiles, circumventDir);
		for (int i = 0; i < mLine.size() && !onMLine; i++) onMLine |= (mLine[i] == pos);
		if (onMLine) mode = eFollowingMLine;
		break;
	}
}
