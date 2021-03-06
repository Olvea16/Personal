// OliverVision.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "OliverVision.h"

#include <iostream>

namespace ov {
	// -- NORMALIZE -- 
	template <typename T> std::vector<T> ov::normalize(std::vector<T> vector)
	{
		std::vector<T> result;
		size_t size = vector.size();
		T sum = 0;
		for (size_t n = 0; n < size; n++) sum += vector[n];
		for (size_t n = 0; n < size; n++) result.push_back(vector[n] / sum);
		return result;
	} 
	std::vector<double> ov::normalize(std::vector<double> vector) { return normalize<double>(vector); }
	std::vector<float> ov::normalize(std::vector<float> vector) { return normalize<float>(vector); }
	void ov::normalizeC(double * arr, size_t n)
	{
		double sum = 0;
		for (int i = 0; i < n; i++) sum += arr[i];
		for (int i = 0; i < n; i++) arr[i] /= sum;
	}

	// -- APPLY FILTER --
	std::vector<double> ov::applyFilter(std::vector<double> data, std::vector<double> kernel, bool normalize)
	{
		std::vector<double> result;
		size_t dataSize = data.size();
		size_t kernelSize = kernel.size();

		if (normalize) kernel = ov::normalize<double>(kernel);

		for (size_t d = 0; d < dataSize; d++) {
			int begin = (int)d - (kernelSize - 1) / 2, end = (int)d + (kernelSize - 1) / 2, k = 0;
			std::vector<double> tempKernel(kernel);
			double value = 0;

			if (begin < 0) {
				double sum = 0;
				for (size_t i = 0; i < std::abs(begin); i++)  sum += kernel[i];
				for (size_t i = k = abs(begin); i < kernelSize; i++) tempKernel[i] /= (1 - sum);
				begin = begin;
			}
			else begin = (d - (kernelSize - 1) / 2);

			if (end >= dataSize) {
				double sum = 0;
				for (size_t i = 0; i < kernelSize - (end - dataSize) - 1; i++) sum += kernel[i];
				for (size_t i = 0; i < kernelSize - (end - dataSize) - 1; i++) tempKernel[i] /= sum;
				end = dataSize - 1;
			}

			for (; k + begin < end + 1; k++) value += tempKernel[k] * data[k + begin];

			result.push_back(value);
		}
		return result;
	}
	void ov::applyFilterC(double ** arr, size_t arraySize, double * kernel, size_t kernelSize)
	{
		double* tempArr = new double[arraySize]();
		normalizeC(kernel, kernelSize);
		for (int a = 0; a < arraySize; a++) {
			int begin = a - ((kernelSize - 1) / 2), end = a + ((kernelSize - 1) / 2);

			double* tempKernel = new double[kernelSize];
			int k = 0;
			for (int i = 0; i < kernelSize; i++) tempKernel[i] = kernel[i];

			if (begin < 0) {
				double sum = 0;
				for (int i = 0; i < abs(begin); i++)  sum += tempKernel[i];
				for (int i = k = abs(begin); i < kernelSize; i++) tempKernel[i] /= (1 - sum);
				begin = 0;
			}

			if (end >= arraySize) {
				double sum = 0;
				for (int i = 0; i < arraySize - end + 1; i++) sum += tempKernel[i];
				for (int i = arraySize - end; i < kernelSize; i++) tempKernel[i] /= (1 - sum);
				end = arraySize - 1;
			}

			for (; k + begin < end + 1; k++) {
				tempArr[a] += (*arr)[k + begin] * tempKernel[k];
			}

			delete[] tempKernel;
		}
		*arr = tempArr;
	}

	// -- GET GAUSSIAN FILTER --
	std::vector<double> ov::getGaussianFilter(size_t n)
	{
		std::vector<double> result;
		result.push_back(1);

		if (n > 1) {
			std::vector<double> oldKernel = getGaussianFilter(n - 1);
			for (int i = 1; i < n - 1; i++) result.push_back(oldKernel[i] + oldKernel[i - 1]);
			result.push_back(1);
		}

		return result;
	}
	void ov::getGaussianFilterC(double * kernel, size_t n)
	{
		if (n <= 1) *kernel = 1;
		else {
			double* tempKernel = new double[n];
			double* oldKernel = new double;

			kernel[0] = kernel[n - 1] = 1;

			getGaussianFilterC(oldKernel, n - 1);

			for (int i = 1; i < n - 1; i++) {
				double val = oldKernel[i - 1] + oldKernel[i];
				kernel[i] = val;
			}
			kernel = tempKernel;
		}
	}

	// -- INTERPOLATION --
	template<typename T> std::vector<std::vector<T>> interpolate(std::vector<std::vector<T>> data, size_t x, size_t y, eInterpolationType interpolationType)
	{
		if (x <= 0 || y <= 0) return std::vector<std::vector<T>>();
		switch (interpolationType) {
		case eBilinear: return bilinearInterpolation(data, x, y);
		case eBicubic: return bicubicInterpolation(data, x, y);
		default: return nearestInterpolation(data, x, y);
		}
	}
	template<typename T> std::vector<std::vector<T>> nearestInterpolation(std::vector<std::vector<T>> data, size_t x, size_t y)
	{
		std::vector<std::vector<T>> result;

		size_t dataSizeY = data.size();
		if (dataSizeY > 0) {
			size_t dataSizeX = data[0].size();
			if (dataSizeX > 0) {
				double xScale = (double)dataSizeX / ((double)x + 1);
				double yScale = (double)dataSizeY / ((double)y + 1);

				for (int j = 0; j < y; j++) {
					std::vector<T> row;
					for (int i = 0; i < x; i++) row.push_back(data[round(j * yScale)][round(i * xScale)]);
					result.push_back(row);
				}
			}
		}
		return result;
	}
	template<typename T> std::vector<std::vector<T>> bilinearInterpolation(std::vector<std::vector<T>> data, size_t x, size_t y)
	{
		return std::vector<std::vector<T>>();
	}
	template<typename T> std::vector<std::vector<T>> bicubicInterpolation(std::vector<std::vector<T>> data, size_t x, size_t y)
	{
		return std::vector<std::vector<T>>();
	}
	std::vector<std::vector<double>> interpolate(std::vector<std::vector<double>> data, size_t x, size_t y, eInterpolationType interpolationType) {
		return interpolate<double>(data, x, y, interpolationType);
	}

	// -- K-MEANS CLUSTERING
	template<typename T> std::vector<Mass<T>> getKMeans(std::vector<Mass<T>> points, size_t k, int iterations, eInitialClusterPosition dist)
	{
		std::vector<Mass<T>> clusters(k);

		size_t n = points.size();
		if (n > 0) {
			size_t dims = points[0].point.size();
			std::vector<std::pair<T, T>> ranges;

			for (int i = 0; i < dims; i++) {
				ranges.push_back(std::pair<T, T>(points[0].point[i], points[0].point[i]));
			}

			for (int i = 1; i < points.size(); i++) {
				for (int r = 0; r < ranges.size(); r++) {
					T val = points[i].point[r];
					if (val < ranges[r].first) ranges[r].first = val;
					if (val > ranges[r].second) ranges[r].second = val;
				}
			}

			switch (dist) {
			case eDistributeRandomly:
				for (int i = 0; i < k; i++) {
					for (int r = 0; r < ranges.size(); r++) {
						T val = ranges[r].first + rand() % (int)floor(ranges[r].second - ranges[r].first);
						clusters[i].point.push_back(val);
						clusters[i].mass = 0;
					}
				}
				break;

			default:
				break;
			}

			bool changed = true;
			while (changed && iterations-- != 0) {
				std::vector<std::vector<Mass<T>>> clusteredPoints(k);
				changed = false;

				for (int p = 0; p < n; p++) {
					T minDist = ov::dist(points[p].point, clusters[0].point);
					size_t cluster = 0;
					for (int c = 1; c < k; c++) {
						T newDist = ov::dist(points[p].point, clusters[c].point);
						if (newDist < minDist) {
							minDist = newDist;
							cluster = c;
						}
					}
					clusteredPoints[cluster].push_back(points[p]);
				}

				for (int c = 0; c < k; c++) {
					clusters[c].mass = 0;
					std::vector<T> oldPos = clusters[c].point;
					for (int p = 0; p < clusteredPoints[c].size(); p++) {
						clusters[c].mass += clusteredPoints[c][p].mass;
						for (int d = 0; d < dims; d++)  clusters[c].point[d] += clusteredPoints[c][p].point[d];

					}
					if (clusters[c].mass > 0) for (int d = 0; d < dims; d++) clusters[c].point[d] /= clusters[c].mass;
					changed |= (oldPos != clusters[c].point);
				}
			}
		}	
		return clusters;
	}
	std::vector<Mass<double>> getKMeans(std::vector<Mass<double>> points, size_t k, int iterations, eInitialClusterPosition dist) {
		return getKMeans<double>(points, k, iterations, dist);
	}

	// -- DISTANCE --
	template<typename T> T dist(std::vector<T> posA, std::vector<T> posB)
	{
		T distance = 0;
		if (posA.size() != 0 && posA.size() == posB.size()) {
			for (int i = 0; i < posA.size(); i++) distance += pow(posA[i] - posB[i], 2);
			distance = sqrt(distance);
		}
		return distance;
	}




}


