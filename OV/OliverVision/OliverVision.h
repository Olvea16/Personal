// MathLibrary.h - Contains declarations of math functions
#pragma once

#if defined(__cplusplus)
#define DLL_Export __declspec(dllexport)
#endif /* __cplusplus */

#include <vector>

namespace ov {	
	// -- NORMALIZE -- 
	//Normalize templated. Not exported as the function doesnt exist before it is templated in code.
	template <typename T> std::vector<T> normalize(std::vector<T> vector);

	DLL_Export std::vector<double> normalize(std::vector<double> vector);
	DLL_Export std::vector<float> normalize(std::vector<float> vector);

	DLL_Export void normalizeC(double* arr, size_t n);

	// -- APPLY FILTER --
	DLL_Export std::vector<double> applyFilter(std::vector<double> data, std::vector<double> kernel, bool normalize = true);
	DLL_Export void applyFilterC(double** arr, size_t arraySize, double* kernel, size_t kernelSize);

	// -- GET GAUSSIAN FILTER --
	DLL_Export std::vector<double> getGaussianFilter(size_t n);
	DLL_Export void getGaussianFilterC(double* kernel, size_t n);

	// -- INTERPOLATION --
	DLL_Export enum eInterpolationType { eNearest, eBilinear, eBicubic };

	template <typename T> std::vector<std::vector<T>> interpolate(std::vector<std::vector<T>> data, size_t x, size_t y, eInterpolationType interpolationType);
	template <typename T> std::vector<std::vector<T>> nearestInterpolation(std::vector<std::vector<T>> data, size_t x, size_t y);
	template <typename T> std::vector<std::vector<T>> bilinearInterpolation(std::vector<std::vector<T>> data, size_t x, size_t y);
	template <typename T> std::vector<std::vector<T>> bicubicInterpolation(std::vector<std::vector<T>> data, size_t x, size_t y);

	DLL_Export std::vector<std::vector<double>> interpolate(std::vector<std::vector<double>> data, size_t x, size_t y, eInterpolationType interpolationType);

	// -- K-MEANS CLUSTERING --
	DLL_Export enum eInitialClusterPosition { eDistributeRandomly };
	template <typename T> struct Mass { std::vector<T> point; T mass = 1; };

	template<> struct DLL_Export Mass<double> { std::vector<double> point; double mass = 1; };

	template <typename T> std::vector<Mass<T>> getKMeans(std::vector<Mass<T>> points, size_t k, int iterations = -1, eInitialClusterPosition dist = eDistributeRandomly);
	DLL_Export std::vector<Mass<double>> getKMeans(std::vector<Mass<double>> points, size_t k, int iterations = -1, eInitialClusterPosition dist = eDistributeRandomly);

	// -- DISTANCE --
	template <typename T> T dist(std::vector<T> posA, std::vector<T> posB);
}