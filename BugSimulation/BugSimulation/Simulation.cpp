#include "stdafx.h"
#include "Simulation.h"


Simulation::Simulation()
{
}

Simulation::Simulation(Map * map, Image * image) : map(map), image(image)
{
}


Simulation::~Simulation()
{
}

void Simulation::addBug(Bug * bug, std::string name, cv::Vec3b color)
{
	BugStruct sBug = {
		bug,
		name,
		color,
		Stat(),
		std::vector<Position<int>>()
	};
	bugs.push_back(sBug);
}

void Simulation::run(unsigned int steps, bool stepByStep)
{
	bool stop = false;
	bool countSteps = steps != 0;

	cv::Mat baseImage = image->getImage();
	cv::Mat pathImage;
	baseImage.copyTo(pathImage);

	const int scale = 5;

	cv::Mat scaledImage;
	cv::namedWindow("path", cv::WINDOW_AUTOSIZE);
	cv::resize(pathImage, scaledImage, cv::Size(), scale, scale, cv::INTER_NEAREST);
	cv::imshow("path", scaledImage);

	cv::waitKey();

	while (!stop && !(countSteps && steps-- > 0)) {
		stop = true;
		for (int i = 0; i < bugs.size(); i++) {
			if (!bugs[i].stats.finished) {
				Bug* bug = bugs[i].bug;

				bug->takeStep(map->getSurroundingTiles(bug->getPos()));

				Position<int> pos = bug->getPos();
				bugs[i].path.push_back(pos);
				bugs[i].stats.finished = (pos == map->getGoalPos());

				stop &= bugs[i].stats.finished;

				pathImage.at<cv::Vec3b>(pos.y, pos.x) -= bugs[i].color;
			}
		}

		if (stepByStep) {
			cv::resize(pathImage, scaledImage, cv::Size(), scale, scale, cv::INTER_NEAREST);
			baseImage.copyTo(pathImage);
			cv::imshow("path", scaledImage);
			if (cv::waitKey(10) != -1) cv::waitKey();
		}
	}

	if (!stepByStep) {
		cv::resize(pathImage, scaledImage, cv::Size(), scale, scale, cv::INTER_NEAREST);
		cv::imshow("path", scaledImage);
		cv::waitKey();
	}
	
}
