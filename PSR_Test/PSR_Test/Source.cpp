#include <vector>
#include <unordered_map>

#include <string>
#include <opencv2/opencv.hpp>

#include "Point.h"

#define M_PI 3.1415927

struct transformation {
	Point p;
	double angle;
};

struct sNearestPoint {
	Point p;
	Point nearestPoint;
};

transformation ICP(std::vector<Point> cloudA, std::vector<Point> cloudB, transformation guess = transformation{Point(0,0),0}) {
	transformation T = guess;
	std::vector<std::vector<Point>> clouds;

	for (Point& p : cloudA) {
		p = p.rotate(T.angle);
		p += T.p;
	}
	clouds.push_back(cloudA);

	int nA = cloudA.size(), nB = cloudB.size();
	int N = 100;
	for (int i = 0; i < N; i++) {
		Point centroidA = Point(0, 0), centroidB = Point(0, 0);
		std::vector<sNearestPoint> nPs;

		for (Point pA : cloudA) {
			centroidA += pA;

			Point nearestPoint;
			double minDist = INT_MAX;
			for (Point pB : cloudB) {
				double dist = pA.getDistance(pB);
				if (dist < minDist) {
					minDist = dist;
					nearestPoint = pB;
				}
			}

			centroidB += nearestPoint;
			nPs.push_back(sNearestPoint({ pA, nearestPoint }));
		}

		centroidA *= 1.0 / nA;
		centroidB *= 1.0 / nA;

		cv::Mat H(2, 2, CV_64F);
		H = 0;
		int N = MIN(cloudA.size(), cloudB.size());
		for (int i = 0; i < N; i++) {
			Point pA = cloudA[i] - centroidA, pB = cloudB[i] - centroidB;
			double pa[2] = { pA.x(), pA.y() };
			double pb[2] = { pB.x(), pB.y() };

			for (int k = 0; k < 4; k++) {
				int x = k % 2, y = k / 2;
				H.at<double>(x, y) += pa[x] * pb[y];
			}
		}

		cv::SVD svd;
		svd(H);
		cv::Mat u = svd.u;
		cv::Mat vt = svd.vt;
		cv::Mat R;
		cv::gemm(u, vt, 1, vt, 0, R);

		double a = acos(R.at<double>(0, 0));
		Point cAR = centroidA.rotate(a);
		Point cBR = centroidB.rotate(a);
		Point translation = centroidB - cAR;

		T.angle += a;
		T.p = T.p.rotate(a);
		T.p += translation;

		for (Point& p : cloudA) {
			p = p.rotate(a);
			p += translation;
		}
		
		clouds.push_back(cloudA);
	}

	Point min(0,0), max(0,0);

	for (std::vector<Point> c : clouds) {
		for (Point p : c) {
			min.x() = MIN(p.x(), min.x());
			min.y() = MIN(p.y(), min.y());
			max.x() = MAX(p.x(), max.x());
			max.y() = MAX(p.y(), max.y());
		}
	}

	Point translation = Point(0,0) - min;
	Point scale = Point(abs(max.x() - min.x()), abs(max.y() - min.y()));

	for (std::vector<Point>& c : clouds) {
		for (Point& p : c) {
			p += translation;
			p.x() /= scale.x();
			p.y() /= scale.y();
		}
	}

	for (Point& p : cloudB) {
		p += translation;
		p.x() /= scale.x();
		p.y() /= scale.y();
	}

	int width = 1720, height = 980, r = 3;
	cv::Vec3b colorA = cv::Vec3b(120, 40, 0), colorB = cv::Vec3b(0, 40, 120);

	for (std::vector<Point>& c : clouds) {
		cv::Mat img(cv::Size(width, height), CV_8UC3);
		for (Point p : cloudB) cv::circle(img, p.getCVPoint(width, height), r, colorA, -1);
		for (Point& p : c)  cv::circle(img, p.getCVPoint(width, height), r, colorB, -1);
		cv::imshow("Image", img);
		cv::waitKey();
	}

	return T;
}

int main() {
	std::vector<Point> A, B;
	
	srand(time(NULL));

	for (int i = 0; i < 10; i++) {
		A.push_back(Point(rand() % 10, rand() % 10));
	}

	transformation t0;
	t0.p = Point(1, 1);
	t0.angle = (rand() % 7000) / 1000.0;

	transformation T = ICP(A, A, t0);

	return 0;
}