#include "stdafx.h"
#include "Image.h"


Image::Image()
{
}

Image::Image(std::string path)
{
	image = cv::imread(path);
}


Image::~Image()
{
}

Position<int> Image::getGoal()
{
	return goal;
}

Position<int> Image::getSpawn(unsigned int spawnIndex)
{
	if (spawnIndex < spawns.size() && spawnIndex >= 0) return spawns[spawnIndex];
	return Position<int>();
}

std::vector<Position<int>> Image::getSpawns()
{
	return spawns;
}

std::vector<std::vector<node>> Image::getMapTiles()
{
	std::vector<std::vector<node>> map;

	size_t width = image.cols;
	size_t height = image.rows;

	for (int y = 0; y < height; y++) {
		std::vector<node> row;
		for (int x = 0; x < width; x++) {
			node n;
			tiles* pTile = &(n.tileType);
			*pTile = eEmpty;
			cv::Vec3b pointColor = image.at<cv::Vec3b>(cv::Point(x, y));
			if (pointColor == goalColor) {
				*pTile = eGoal;
				goal = Position<int>(x, y);
			}
			if (pointColor == obstacleColor) *pTile = eObstacle;
			if (pointColor == spawnColor) spawns.push_back(Position<int>(x, y));
			row.push_back(n);
		}
		map.push_back(row);
	}

	return map;
}

cv::Mat Image::getImage()
{
	return image;
}
