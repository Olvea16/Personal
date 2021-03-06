// ComputerVision_Assignments_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <opencv2\opencv.hpp>
#include <iostream>

const std::string path = "img.jpg";

void applyGaussianNoise(cv::Mat img, int G, double sigma);

int main()
{
	cv::Mat image = cv::imread(path);
	srand(time(NULL));

	if (image.data != NULL) {

		std::string windowName = "window";

		applyGaussianNoise(image, 128, 10);

		cv::imshow(windowName, image);
		cv::waitKey();
	}
 	return 0;
}

void applyGaussianNoise(cv::Mat img, int G, double sigma) {
	double* PArray = new double[2 * (G - 1)];
	double P = 0;

	for (int k = -(G - 1); k < G; k++) {
		double p = std::exp(-(pow(k, 2) / (2 * pow(sigma, 2)))) / (sigma * std::sqrt(2 * 3.1415927));
		P += p;
		PArray[k + (G - 1)] = P;
	}

	double PMax = PArray[2 * (G - 1) - 1];
	for (int k = -(G - 1); k < G; k++) {
		PArray[k] /= PMax;
	}

	for (cv::MatIterator_<cv::Vec3b> pt = img.begin<cv::Vec3b>(); pt != img.end<cv::Vec3b>(); pt++) {

		for (int c = 0; c < 3; c++) {
			float r = (float)rand() / (float)RAND_MAX;
			int kR = 0;

			for (int k = 0; k < 2 * (G - 1); k++) {
				if (abs(r - PArray[k]) <= abs(r - PArray[kR])) kR = k;
				else break;
			}

			kR -= G - 1;

			int channelValue = (*pt)[c];
			channelValue += kR;
			if (channelValue < 0) channelValue = 0;
			if (channelValue > 255) channelValue = 255;
			(*pt)[c] = (unsigned char)channelValue;
		}
	}
}