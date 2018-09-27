#include "stdafx.h"
#include "Direction.h"


Direction::Direction()
{
}


Direction::~Direction()
{
}

// This is terribly named. The point is that i need the directions after a given direction in CW or CCW order.
// The argument, pos, determines where the rotation starts and direction determines if its CW or CCW
std::vector<Position<int>> Direction::getDirectionsAfter(Position<int> pos, int direction)
{
	const Position<int> directions[8] = {
		Position<int>(0,-1),
		Position<int>(-1,-1),
		Position<int>(-1,0),
		Position<int>(-1,1),
		Position<int>(0,1),
		Position<int>(1,1),
		Position<int>(1,0),
		Position<int>(1,-1)
	};

	std::vector<Position<int>> result;
	int index = 0;
	for (int i = 0; i < 8; i++) {
		if (pos == directions[i]) {
			index = i + direction;
			break;
		}
	}

	int start = index;
	if (direction == 1) for (; index < (start + 9); index++) result.push_back(directions[index % 8]);
	else for (; index > (start - 9); index--) result.push_back(directions[(8 + index) % 8]);
	
	return result;
}
