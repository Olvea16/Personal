#include <vector>
#include <unordered_map>
#include "Point.h"

#define M_PI 3.1415927

struct transformation {
	Point<double> p;
	double angle;
};

struct sNearestPoint {
	Point<double> p;
	Point<double> nearestPoint;
};

transformation ICP(std::vector<Point<double>> cloudA, std::vector<Point<double>> cloudB, transformation guess = transformation{Point<double>(0,0),0}) {
	transformation T = guess;

	for (Point<double>& p : cloudA) {
		p.rotate(T.angle);
		p += T.p;
	}

	int nA = cloudA.size(), nB = cloudB.size();
	int N = 10;
	for (int i = 0; i < N; i++) {
		Point<double> centroidA = Point<double>(0, 0), centroidB = Point<double>(0, 0);
		std::vector<sNearestPoint> nPs;

		for (Point<double> pA : cloudA) {
			centroidA += pA;

			Point<double> nearestPoint;
			double minDist = INT_MAX;
			for (Point<double> pB : cloudB) {
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
		
	}

	return T;
}

int main() {
	std::vector<Point<double>> A, B;

	for (int i = 0; i < 10; i++) {
		A.push_back(Point<double>(i, 0));
		B.push_back(Point<double>(i + 1, 1));
	}

	transformation t0;
	t0.p = Point<double>(1, 1);
	t0.angle = M_PI;

	transformation T = ICP(A, B, t0);

	return 0;
}