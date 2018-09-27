#include "stdafx.h"
#include "Bug.h"

#include <algorithm>

Bug::Bug()
{
}

Bug::Bug(Position<int> starting_position, Position<int> goal_position) : pos(starting_position), goal(goal_position)
{
}


Bug::~Bug()
{
}

void Bug::takeStep(std::vector<std::vector<tiles>> surroundingTiles)
{
}

Position<int> Bug::getPos()
{
	return pos;
}

bool Bug::moveAlongObstacle(std::vector<std::vector<tiles>> surroundingTiles, int direction)
{
	bool foundObstacle = false, moved = false;

	std::vector<Position<int>> directions = Direction::getDirectionsAfter(Position<int>(0, 0) - lastDirection, direction);

	for (int i = 0; i < directions.size() && !moved; i++) {
		Position<int> searchPos = directions[i];
		tiles tileType = surroundingTiles[searchPos.y + 1][searchPos.x + 1];
		if (tileType == eObstacle) {
			foundObstacle = true;
		}
		else {
			if (tileType == eEmpty && foundObstacle) {
				lastDirection = searchPos;
				pos += (searchPos);
				moved = true;
			}
		}
	}

	return moved;
}

std::vector<Position<int>> Bug::getLine(Position<int> goal)
{
	// Container for points in line.
	std::vector<Position<int>> line;

	// Check if there even is a line to draw.
	if (goal.x != 0 || goal.y != 0) 
	{
		// If the point is father in the x-axis.
		if (std::max(abs(goal.x), abs(goal.y)) == abs(goal.x)) {
			double a = (double)goal.y / (double)goal.x; // Calculate slope of line.
			int inc = goal.x / abs(goal.x); // Calculate direction of incrementation.

			for (int x = 0; abs(x) < abs(goal.x) + 1; x += inc)  // Iterate through every nessecary point.
			{
				Position<int> point(x, round(a * x)); // Calculate point.
				line.push_back(point); //Save point to line container.
			}
		}
		// If the point is farther in the y-axis.
		else {
			double a = (double)goal.x / (double)goal.y; // Calculate slope of line.
			int inc = goal.y / abs(goal.y); // Calculate direction of incrementation.

			for (int y = 0; abs(y) < abs(goal.y) + 1; y += inc) // Iterate through every nessecary point.
			{ 
				Position<int> point(round(a * y) , y); // Calculate point.
				line.push_back(point); //Save point to line container.
			}
		}
	}

	// Return line.
	return line;
}

int Bug::getDistance(Position<int> goal)
{
	if (CALCULATE_DISCRETE) return std::max(abs(goal.x), abs(goal.y));
	else return (std::sqrt<int>(pow(goal.x, 2) + pow(goal.y, 2)));
}
