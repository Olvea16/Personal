#pragma once

#include <opencv2\opencv.hpp>
#include <string>

class VideoExport
{
public:
	VideoExport();
	VideoExport(std::string filename, double fps, cv::Size imagesize) : filename(filename), fps(fps), imagesize(imagesize) { }

	~VideoExport() { vW.release(); }

	void create() { vW = cv::VideoWriter(filename, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, imagesize); }

	void addImage(cv::Mat img) {
		if (vW.isOpened()) vW << img;
		else create();
	}

private:
	std::string filename;
	double fps;
	cv::Size imagesize;

	cv::VideoWriter vW;
};

