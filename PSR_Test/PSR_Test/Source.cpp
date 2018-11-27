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

	for (Point& p : cloudA) {
		p.rotate(T.angle);
		p += T.p;
	}

	int nA = cloudA.size(), nB = cloudB.size();
	int N = 10;
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
		for (cv::MatIterator_<double> i = H.begin<double>(); i != H.end<double>(); i++) {
			std::cout << *i << std::endl;
		}
		std::cout << std::endl;
		cv::Mat u = svd.u;
		for (cv::MatIterator_<double> i = u.begin<double>(); i != u.end<double>(); i++) {
			std::cout << *i << std::endl;
		}
		std::cout << std::endl;
		cv::Mat vt = svd.vt;
		for (cv::MatIterator_<double> i = vt.begin<double>(); i != vt.end<double>(); i++) {
			std::cout << *i << std::endl;
		}
		cv::Mat R;
		std::cout << std::endl;
		cv::gemm(u, vt, 1, vt, 0, R);
		for (cv::MatIterator_<double> i = R.begin<double>(); i != R.end<double>(); i++) {
			std::cout << *i << std::endl;
		}

		double a = acos(R.at<double>(0, 0));

		Point translation();
	}

	return T;
}

int main() {
	std::vector<Point> A, B;

	for (int i = 0; i < 10; i++) {
		A.push_back(Point(i, 0));
		B.push_back(Point(i + 1, 1));
	}

	transformation t0;
	t0.p = Point(1, 1);
	t0.angle = 1.11111;

	transformation T = ICP(A, B, t0);

	return 0;
}