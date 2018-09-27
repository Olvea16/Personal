#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <opencv2\opencv.hpp>
#include <iostream>

#include "Position.h"

enum tiles {
	eObstacle,
	eGoal,
	eEmpty
};

class Image
{
public:
	Image();
	Image(std::string path);
	~Image();

	Position<int> getGoal();
	Position<int> getSpawn(unsigned int spawnIndex);
	std::vector<Position<int>> getSpawns();

	cv::Mat getImage();
	std::vector<std::vector<tiles>> getMapTiles();

private:
	cv::Mat image;
	std::unordered_map<tiles, cv::Vec3b> tileColors;

	Position<int> goal;
	std::vector<Position<int>> spawns;

	cv::Vec3b goalColor = cv::Vec3b(0, 255, 0);
	cv::Vec3b obstacleColor = cv::Vec3b(0, 0, 0);
	cv::Vec3b spawnColor = cv::Vec3b(255, 0, 0);
};

