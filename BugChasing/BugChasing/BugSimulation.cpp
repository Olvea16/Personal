// BugSimulation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Simulation.h"
#include "Bug1.h"
#include "Bug2.h"

const std::string path = "Maps/PaintMaze.bmp";

int main()
{
	Image image(path);
	Map map(&image);
	
	std::vector<Bug*> bugs;
	Simulation simulation(&map, &image);

	for (int i = 0; i < image.getSpawns().size(); i++) {
		Bug2* bug = new Bug2(image.getSpawn(i), map.getGoalPos());
		bugs.push_back(bug);
		simulation.addBug(bugs[i], "Bug_" + std::to_string(i), cv::Vec3b(rand() % 255, rand() % 255, rand() % 255));
	}

	simulation.run(0, true);
    return 0;
}

