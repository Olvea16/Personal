// ComputerVision_Assignments_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "OliverVision.h"

#include <opencv2\opencv.hpp>
#include <string>
#include <vector>
#include <math.h>

std::string windowName = "window";

std::string paths[] = { "doge.jpg" };
const size_t pathAmount = sizeof(paths) / sizeof(std::string);

unsigned int windowAmount = 0;

template<int i>
struct conditional { typedef uchar type; };

template<>
struct conditional<CV_8SC1> { typedef char type; };

template<>
struct conditional<CV_16UC1> { typedef ushort type; };

template<>
struct conditional<CV_16SC1> { typedef short type; };

enum ComparisonMethod {
	eCorrolation
};

void drawGraph(cv::Size2d size, std::vector<cv::Point> points, std::string windowName = "");
void drawBarGraph(cv::Size2d size, std::vector<cv::Point> points, std::string windowName = "");
std::vector<cv::Point> getHistogram(cv::Mat image, unsigned int channel = 0, bool log = false);
void histEqualize(cv::Mat image, unsigned int channel, bool log = false);
double histCompare(cv::Mat img1, cv::Mat img2, unsigned int channel, ComparisonMethod method);


template <int depth>
int* getHistogram2(cv::Mat image, unsigned int channel = 0)
{
	typedef conditional<depth>::type type_t;

	int* hist = new int;
	*hist = 0;

	std::vector<cv::Mat> vec;

	cv::split(image, vec);

	int c = 0;
	if (c < vec.size()) {
		cv::Mat* chan = &(vec[c]);
		size_t bitDepth = pow(1 << 8, chan->elemSize1());
		delete hist;
		hist = new int[bitDepth + 1]();
		hist[0] = bitDepth;

		for (cv::MatIterator_<type_t> p = chan->begin<type_t>(); p != chan->end<type_t>(); p++) {
			hist[*p + 1]++;
		}
	}
	return hist;
}

int* getHistogram2(cv::Mat image, unsigned int channel = 0) {
	int* hist;
	switch (image.depth()) {
	case CV_8UC1:
		hist = getHistogram2<CV_8UC1>(image, 2);
		break;

	case CV_8SC1:
		hist = getHistogram2<CV_8SC1>(image, 2);
		break;

	case CV_16UC1:
		hist = getHistogram2<CV_16UC1>(image, 2);
		break;

	case CV_16SC1:
		hist = getHistogram2<CV_16SC1>(image, 2);
		break;

	case CV_16SC3:
		hist = getHistogram2<CV_16SC3>(image, 2);
		break;

	case CV_32SC1:
		hist = getHistogram2<CV_32SC1>(image, 2);
		break;

	case CV_32FC1:
		hist = getHistogram2<CV_32FC1>(image, 2);
		break;

	default:
		hist = new int;
		*hist = 0;
	}

	return hist;
}

int main()
{
	srand(time(NULL));

	cv::Mat* imgs = new cv::Mat[pathAmount];
	for (int p = 0; p < pathAmount; p++) {
		imgs[p] = cv::imread(paths[p]);
	}

	static const int depths[] = { CV_16SC1 };
	size_t depthAmount = sizeof(depths) / sizeof(int);

	int* hist = getHistogram2(imgs[0], 0);
	size_t histLength = hist[0];

	double* dHist = new double[histLength];
	for (int i = 0; i < histLength; i++) dHist[i] = (double)hist[i];

	double kernel[5];
	double data[] = { 10, 20, 30, 25, 20, 40, 50, 40, 20, 20 };
	double* pD = data;
	size_t kernelSize = sizeof(kernel) / sizeof(double);
	size_t dataSize = sizeof(data) / sizeof(double);

	ov::getGaussianFilter(kernel, kernelSize);
	ov::applyFilter(&pD, dataSize, kernel, kernelSize);

	for (int i = 0; i < dataSize; i++) std::cout << data[i] << std::endl;

 	cv::imshow("abe", imgs[0]);

	std::cout << "bitdepth: " << hist[0] << std::endl;
	for (int i = 0; i < hist[0]; i++) {
		std::cout << i << ": " << hist[i + 1] << " - " << dHist[i] << std::endl;
	}

	cv::waitKey();
    return 0;
}

void drawGraph(cv::Size size, std::vector<cv::Point> points, std::string windowName)
{
	int highestPoint = 0, lowestPoint = 0, pointAmount = points.size();

	int height, width = (1 + points[pointAmount - 1].x) * size.width;
	for (int i = 0; i < pointAmount; i++) {
		cv::Point point = points[i];
		if (point.y < lowestPoint) lowestPoint = point.y;
		if (point.y > highestPoint) highestPoint = point.y;
	}

	height = (highestPoint - lowestPoint) * size.height;

	cv::Mat graph(height, width, CV_8UC3);
	graph.setTo(cv::Scalar(255, 255, 255));

	cv::line(graph, cv::Point(0, highestPoint), cv::Point(width, highestPoint), cv::Scalar(0, 0, 0), 1);

	for (int x = 0; x < (pointAmount - 1); x++) {
		cv::line(graph, cv::Point(points[x].x * size.width, (highestPoint - points[x].y) * size.height), cv::Point(points[x + 1].x * size.width, (highestPoint - points[x + 1].y) * size.height), cv::Scalar(0, 0, 255));
	}

	if (windowName == "") windowName = "Graph" + std::to_string(++windowAmount);

	cv::namedWindow(windowName, CV_WINDOW_AUTOSIZE);
	cv::imshow(windowName, graph);
}

void drawBarGraph(cv::Size2d size, std::vector<cv::Point> points, std::string windowName)
{
	int highestPoint = 0, lowestPoint = 0, pointAmount = points.size();
	int height, width = (1 + points[pointAmount - 1].x) * size.width;

	for (int i = 0; i < pointAmount; i++) {
		cv::Point point = points[i];
		if (point.y < lowestPoint) lowestPoint = point.y;
		if (point.y > highestPoint) highestPoint = point.y;
	}

	height = (highestPoint - lowestPoint) * size.height;

	cv::Mat graph(height, width, CV_8UC3);
	graph.setTo(cv::Scalar(255, 255, 255));

	cv::line(graph, cv::Point(0, highestPoint * size.height), cv::Point(width, highestPoint * size.height), cv::Scalar(0, 0, 0), 1);

	for (int x = 0; x < pointAmount; x++) {
		cv::line(graph, cv::Point(points[x].x * size.width, highestPoint * size.height), cv::Point(points[x].x * size.width, (highestPoint - points[x].y) * size.height), cv::Scalar(0, 0, 0));
	}

	if (windowName == "") windowName = "Graph" + std::to_string(++windowAmount);

	cv::namedWindow(windowName, CV_WINDOW_AUTOSIZE);
	cv::imshow(windowName, graph);
}

std::vector<cv::Point> getHistogram(cv::Mat image, unsigned int channel, bool log)
{
	size_t pixelValAmount = pow(256, image.elemSize1());

	int* pixelVals = new int[pixelValAmount];
	for (int i = 0; i < pixelValAmount; i++) pixelVals[i] = 0;

	for (cv::MatIterator_<cv::Vec3b> p = image.begin<cv::Vec3b>(); p != image.end<cv::Vec3b>(); p++) pixelVals[(*p)[channel]]++;

	std::vector<cv::Point> result;

	for (int i = 0; i < pixelValAmount; i++) {
		if (log) {
			if (pixelVals[i] != 0) {
				result.push_back(cv::Point(i,20 * log10((double)pixelVals[i])));
			}
		}
		else {
			result.push_back(cv::Point(i,pixelVals[i]));
		}
	}

	return result;
}


void histEqualize(cv::Mat image, unsigned int channel, bool log)
{
	size_t pixelBins = pow(256, image.elemSize1());
	std::vector<cv::Point> histVec = getHistogram(image, channel, log);

	int* histogram = new int[pixelBins]();
	int histSum = 0;

	//  Populating histogram array.
	for (int i = 0; i < histVec.size(); i++) {
		histogram[histVec[i].x] = (histVec[i]).y;
		histSum += (histVec[i]).y;
	}

	double* cdf = new double[pixelBins];

	cdf[0] = ((double)histogram[0]) / ((double)histSum);
	for (int i = 0; i < pixelBins - 1; i++) cdf[i + 1] = cdf[i] + (double)histogram[i + 1] / (double)histSum;
	for (int i = 0; i < pixelBins; i++) cdf[i] = (cdf[i] / cdf[pixelBins - 1]) * (pixelBins - 1);

	for (cv::MatIterator_<cv::Vec3b> p = image.begin<cv::Vec3b>(); p != image.end<cv::Vec3b>(); p++) (*p)[channel] = cdf[(*p)[channel]];
	return;
}

double histCompare(cv::Mat img1, cv::Mat img2, unsigned int channel, ComparisonMethod method)
{
	size_t pixelBins = std::max(pow(256, img1.elemSize1()), pow(256, img2.elemSize1()));
	//*
	int* h1 = new int[pixelBins];
	int* h2 = new int[pixelBins];
	//*/

	/*
	int h1[256];
	int h2[256];
	//*/

	for (int i = 0; i < pixelBins; i++) h1[i] = h2[i] = 0;

	std::vector<cv::Point> vH1 = getHistogram(img1, channel), vH2 = getHistogram(img2, channel);

	double h1Sum = 0, h2Sum = 0;

	switch (method) {
	case eCorrolation:
		for (int i = 0; i < vH1.size(); i++) {
			h1[vH1[i].x] = vH1[i].y;
			h1Sum += vH1[i].y;
		}
		h1Sum /= (double)pixelBins;

		for (int i = 0; i < vH2.size(); i++) {
			h2[vH2[i].x] = vH2[i].y;
			h2Sum += vH2[i].y;
		}
		h2Sum /= (double)pixelBins;

		double num = 0, den = 0, den1 = 0, den2 = 0;

		for (int i = 0; i < pixelBins; i++) {
			num += (h1[i] - h1Sum) * (h2[i] - h2Sum);
			den1 += pow(h1[i] - h1Sum, 2);
			den2 += pow(h2[i] - h2Sum, 2);
		}
		den = sqrt(den1 * den2);

		return (num / den);
	}
}
