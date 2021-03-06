// OpenCV_Test_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <Windows.h>
#include <iostream>
#include <math.h>
#include <vector>

const std::string path = "tippeddude.jpg";
const std::string windowName = "Swindow";

cv::Point mouseDownPt;
std::vector<std::vector<cv::Point>> mouseSelectionQueue;

bool waitingForHue = false;
cv::Point huePoint;

static void mouseCallback(int event, int x, int y, int flags, void*);

cv::Mat rotateImageCW(cv::Mat image);
cv::Mat saturateHue(cv::Mat image, int target_hue, double hueGain = 100, double baseGain = 0);
int getHue(cv::Mat image, cv::Point point);
int getValueFromConsole(std::string message);

int main()
{
	cv::Mat img = cv::imread(path);



	if (img.data != NULL) {
		cv::resize(img, img, cv::Size(), 1, 1, cv::INTER_LANCZOS4);

		size_t imageWidth = img.cols;
		size_t imageHeight = img.rows;
		cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
		cv::namedWindow(windowName + "_1", cv::WINDOW_AUTOSIZE);
		cv::setMouseCallback(windowName, mouseCallback);
		cv::imshow(windowName, img);
		
		while (1) {
			if (mouseSelectionQueue.size() != 0) {
				std::cout << "Pick hue." << std::endl;
				waitingForHue = true;
				while (huePoint == cv::Point()) cv::waitKey(10);
				waitingForHue = false;
				int hue = getHue(img, huePoint);
				std::cout << "Picked hue of " << hue << std::endl;
				huePoint = cv::Point();
				int hueGain = getValueFromConsole("Enter filter gain: ");
				int baseGain = getValueFromConsole("Enter base gain: ");

				std::vector<cv::Point>* pSelection = &(mouseSelectionQueue[0]);
				int x = (*pSelection)[0].x;
				int y = (*pSelection)[0].y;
				int width = (*pSelection)[1].x - x;
				int height = (*pSelection)[1].y - y;

				mouseSelectionQueue.pop_back();

				cv::Mat croppedImage = img(cv::Rect(x, y, width, height));
				cv::Mat hsvImage = saturateHue(croppedImage, hue, hueGain, baseGain);

				cv::imshow(windowName + "_1", hsvImage);

			}
			cv::waitKey(10);
		}
	}
	else OutputDebugString(L"Image file not found.\n");

	return 0;
}

int getHue(cv::Mat image, cv::Point point) {
	cv::cvtColor(image, image, CV_BGR2HLS);
	int hue = image.at<cv::Vec3b>(point)[0];
	cv::cvtColor(image, image, CV_HLS2BGR);
	return hue;
}

int getValueFromConsole(std::string message)
{
	double result;
	std::cout << message;
	std::cin >> result;
	return result;
}

cv::Mat rotateImageCW(cv::Mat image) {

	size_t width = image.cols;
	size_t height = image.rows;
	uchar channels = image.channels();

	cv::Mat result = cv::Mat(width, height, CV_8UC3);

	cv::MatIterator_<cv::Vec3b> i, begin, end;
	for (i = begin = image.begin<cv::Vec3b>(), end = image.end<cv::Vec3b>(); i != end; i++) {
		size_t x = (i - begin) % width;
		size_t y = (i - begin) / width;

		size_t _x = height - y - 1;
		size_t _y = x;

		size_t iR = _x + _y * height;

		for (int c = 0; c < 3; c++) (*(result.begin<cv::Vec3b>() + iR))[c] = (*i)[c];
	}

	return result;
}

void mouseCallback(int event, int x, int y, int flags, void* params) {
	if (event == cv::EVENT_LBUTTONDOWN) mouseDownPt = cv::Point(x, y);
		
	if (event == cv::EVENT_LBUTTONUP) {
		if (mouseDownPt != cv::Point()) {
			std::vector<cv::Point> points;
			if (waitingForHue) huePoint = mouseDownPt;
			else {
			points.push_back(cv::Point(min(x, mouseDownPt.x), min(y, mouseDownPt.y)));
			points.push_back(cv::Point(max(x, mouseDownPt.x), max(y, mouseDownPt.y)));
			mouseSelectionQueue.push_back(points);
			}
		}
	}
}

cv::Mat saturateHue(cv::Mat image, int targetHue, double hueGain, double baseGain) {
	cv::cvtColor(image, image, CV_BGR2HLS);

	cv::MatIterator_<cv::Vec3b> i, begin, end;
	for (i = begin = image.begin<cv::Vec3b>(), end = image.end<cv::Vec3b>(); i != end; i++) {
		uchar* pHue = &((*i)[0]);
		uchar* pLig = &((*i)[1]);
		uchar* pSat = &((*i)[2]);

		double dHue = targetHue - *pHue;
		if (dHue < 0) dHue += 179;
		if (dHue > 89.5) dHue = 179 - dHue;

		double A;
		A = pow(10, (-hueGain * (double)dHue / 89.5 + baseGain) / 20);
		//A = pow(10.0, -10.0 * (1 - (dHue / 89.5)));

		*pSat *= A;
		//*pLig *= A;

		//*pHue = 55;
	}
	cv::cvtColor(image, image, CV_HLS2BGR);
	return image;
}