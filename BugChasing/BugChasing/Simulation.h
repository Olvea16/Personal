#pragma once

#include "Map.h"
#include "Bug.h"
#include "Stat.h"



class Simulation
{
public:
	Simulation();
	Simulation(Map* map, Image* image);
	~Simulation();

	void addBug(Bug* bug, std::string name, cv::Vec3b color);

	void run(unsigned int steps = 0, bool stepByStep = false);

private:
	struct BugStruct {
		Bug* bug;
		std::string name;
		cv::Vec3b color;
		Stat stats;
		std::vector<Position<int>> path;
	};

	Map* map;
	Image* image;
	std::vector<BugStruct> bugs;
};

