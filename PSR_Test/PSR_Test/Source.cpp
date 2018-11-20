#include <vector>
#include "Point.h"


struct transformation {
	double x, y, angle;
};

transformation ICP(std::vector<Point<double>> cloudA, std::vector<Point<double>> cloudB, transformation guess = transformation{ 0,0,0 }) {
	transformation T = guess;
	int nA = cloudA.size(), nB = cloudB.size();
	int N = 10;
	for (int i = 0; i < N; i++) {
		Point<double> centroidA = Point<double>(0, 0), centroidB = Point<double>(0, 0);
		for (int j = 0; j < nA; j++) centroidA += cloudA[i];
		centroidA *= nA;
		for (int j = 0; j < nA; j++) centroidB += cloudB[i];
		centroidB *= nB;
		
	}

	return T;
}

int main() {
	std::vector<Point<double>> A, B;
	return 0;
}