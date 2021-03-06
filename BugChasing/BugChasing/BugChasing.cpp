// BugChasing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Simulation.h"
#include "Bug1.h"
#include "Bug2.h"

const std::string path = "Maps/Spiral.bmp";

int WinMain()
{
	Image image(path);
	Map map(&image);

	std::vector<Bug*> bugs;
	Simulation simulation(&map, &image);

	for (int i = 0; i < image.getSpawns().size(); i++) {
		Bug1* bug1 = new Bug1(image.getSpawn(i), map.getGoalPos());
		bugs.push_back(bug1);
		Bug2* bug2 = new Bug2(image.getSpawn(i), map.getGoalPos());
		bugs.push_back(bug2);
	}

	for (int i = 0; i < bugs.size(); i++) simulation.addBug(bugs[i], "Bug_" + std::to_string(i), cv::Vec3b(rand() % 255, rand() % 255, rand() % 255));

	simulation.run(0, true);
	return 0;
}

int main() {
	return WinMain();
}