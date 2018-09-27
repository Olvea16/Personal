#include "stdafx.h"
#include "Map.h"


Map::Map()
{
}

Map::Map(Image* image)
{
	map = image->getMapTiles();
	goal = image->getGoal();
	loaded = true;
}

Map::~Map()
{
}

std::vector<std::vector<tiles>> Map::getSurroundingTiles(Position<int> pos)
{
	std::vector<std::vector<tiles>> result;

	if (loaded) {
		int width = map[0].size();
		int height = map.size();

		for (int y = pos.y - 1; y < pos.y + 2; y++) {
			std::vector<tiles> row;

			if (y < 0 || y >= height) {
				for (int i = 0; i < 3; i++) row.push_back(eObstacle);
			}
			else {
				for (int x = pos.x - 1; x < pos.x + 2; x++) {
					if (x < 0 || x >= width) row.push_back(eObstacle);
					else row.push_back(map[y][x]);
				}
			}
			result.push_back(row);
		}
	}
	return result;
}

Position<int> Map::getGoalPos()
{
	return goal;
}
