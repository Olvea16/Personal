#pragma once
#include "Bug.h"
class Bug2 :
	public Bug
{
public:
	Bug2();
	Bug2(Position<int> starting_position, Position<int> goal_position);
	~Bug2();

	void takeStep(std::vector<std::vector<tiles>> surroundingTiles);

private:
	enum movementMode {
		eFollowingMLine,
		eCircumventingObstacle,
		eDone
	};

	movementMode mode = eFollowingMLine;
	std::vector<Position<int>> mLine;
	int circumventDir = 1;
};

