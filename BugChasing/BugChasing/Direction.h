#pragma once

#include <vector>

#include "Position.h"

class Direction
{
public:
	Direction();
	~Direction();

	static std::vector<Position<int>> getDirectionsAfter(Position<int> pos, int direction = 1);

private:
};

