#pragma once

#include "Map.h"
#include "Direction.h"

#define CALCULATE_DISCRETE false

class Bug
{
public:
	Bug();
	Bug(Position<int> starting_position, Position<int> goal_position);
	~Bug();

	virtual void takeStep(std::vector<std::vector<tiles>> surroundingTiles);
	Position<int> getPos();

protected:
	int getDistance(Position<int> goal);
	Position<int> pos;
	Position<int> goal;

	Position<int> lastDirection = Position<int>(1,0);

	bool moveAlongObstacle(std::vector<std::vector<tiles>> surroundingTiles, int direction = 1);
	std::vector<Position<int>> getLine(Position<int> goal);

};

