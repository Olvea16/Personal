#pragma once

#include <vector>

#include "Position.h"
#include "Image.h"

class Map
{
public:
	Map();
	Map(Image* image);
	~Map();

	std::vector<std::vector<tiles>> getSurroundingTiles(Position<int> pos);
	Position<int> getGoalPos();

private:
	Position<int> goal;
	std::vector<Position<int>> spawns;
	std::vector<std::vector<node>> map;
	bool loaded = false;
};

