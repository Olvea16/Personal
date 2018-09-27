#pragma once
#include "Bug.h"

class Bug1 :
	public Bug
{
public:
	Bug1();
	Bug1(Position<int> starting_position, Position<int> goal_position);
	~Bug1();

	void takeStep(std::vector<std::vector<tiles>> surroundingTiles);

private:
	enum movementMode {
		eHeadingForGoal,
		eScoutingObstacle,
		eBacktracking,
		eDone
	};

	movementMode mode = eHeadingForGoal;

	Position<int> scoutingStart;
	unsigned int closestScoutingIteration;
	unsigned int shortestDistance;
	unsigned int currentScoutingIteration;

};

