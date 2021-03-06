// OliverVisionTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\..\OV\OliverVision\OliverVision.h"

#include <iostream>

using namespace std;
using namespace ov;

int main()
{
	// Filtertest
	/*
	size_t n = 7;

	std::vector<double> data = {10, 20, 30, 25, 20, 40, 50, 30, 20, 20 };
	std::vector<double> kernel = ov::getGaussianFilter(n);
	std::vector<double> nKernel = ov::normalize(kernel);

	std::vector<double> filteredData = ov::applyFilter(data, kernel);

	std::cout << "Kernel size: " << n << std::endl;
	std::cout << "Kernel: ";
	for (int i = 0; i < n - 1; i++) std::cout << kernel[i] << ", ";
	std::cout << kernel[n - 1] << std::endl;
	std::cout << "Normalized kernel: ";
	for (int i = 0; i < n - 1; i++) std::cout << nKernel[i] << ", ";
	std::cout << nKernel[n - 1] << std::endl;
	std::cout << "n\tData\tResult" << std::endl;
	for (int i = 0; i < data.size(); i++) std::cout << i + 1 << ":\t" << data[i] << '\t' << filteredData[i] << std::endl;
	//*/

	// InterpolationTest
	/*
	size_t x = 10, y = 10;
	double scale = 2.314;

	std::vector<std::vector<double>> image;

	for (int j = 0; j < y; j++) {
		std::vector<double> row;
		for (int i = 0; i < x; i++) {
			row.push_back(i + j);
		}
		image.push_back(row);
	}
	std::vector<std::vector<double>> scaledImage = ov::interpolate(image, x * scale, y * scale, ov::eNearest);

	for (int j = 0; j < image.size(); j++) {
		for (int i = 0; i < image[j].size(); i++) {
			std::cout << image[j][i] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
	for (int j = 0; j < scaledImage.size(); j++) {
		for (int i = 0; i < scaledImage[j].size(); i++) {
			std::cout << scaledImage[j][i] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	//*/

	// KMeans Test
	//*
	typedef double type_t;

	const size_t dimensions = 1;
	size_t n = 100;
	type_t ranges[dimensions] = { 100 };
	vector<Mass<type_t>> points;

	for (int i = 0; i < n; i++) {
		Mass<type_t> point;
		vector<type_t> pos;
		for (int d = 0; d < dimensions; d++) {
			pos.push_back((type_t)(rand() % (int)(ranges[d] * 10)) / 10);
		}
		point.point = pos;
		points.push_back(point);
	}

	vector<Mass<type_t>> clusters = getKMeans(points, 5);
	//*/

	system("pause");

    return 0;
}

