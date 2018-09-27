#include "stdafx.h"
#include "Bug1.h"


Bug1::Bug1()
{
}

Bug1::Bug1(Position<int> starting_position, Position<int> goal_position)
{
	pos = starting_position;
	goal = goal_position;
}


Bug1::~Bug1()
{
}

void Bug1::takeStep(std::vector<std::vector<tiles>> surroundingTiles)
{
	bool moved = false;
	Position<int> headingPos;
	switch (mode) {
	case eHeadingForGoal:
		headingPos = getLine(goal - pos)[1];
		if (surroundingTiles[headingPos.y + 1][headingPos.x + 1] != eObstacle) {
			pos += headingPos;
			if (pos == goal) mode = eDone;
			break;
		}
		mode = eScoutingObstacle;
		closestScoutingIteration = 0;
		currentScoutingIteration = 0;
		shortestDistance = getDistance(goal - pos);
		scoutingStart = pos;

	case eScoutingObstacle:
		moved = moveAlongObstacle(surroundingTiles);
		if (moved) {
			currentScoutingIteration++;
			unsigned int distance = getDistance(goal - pos);
			if (distance < shortestDistance) {
				shortestDistance = distance;
				closestScoutingIteration = currentScoutingIteration;
			}
			if (pos == scoutingStart) mode = eBacktracking;
			if (pos == goal) mode = eDone;
		}
		break;

	case eBacktracking:
		int direction;
		if (closestScoutingIteration < currentScoutingIteration - closestScoutingIteration) direction = 1;
		else direction = -1;

		moved = moveAlongObstacle(surroundingTiles, direction);
		unsigned int distance = getDistance(goal - pos);

		if (distance == shortestDistance) 
			mode = eHeadingForGoal;
		break;
	}
}
