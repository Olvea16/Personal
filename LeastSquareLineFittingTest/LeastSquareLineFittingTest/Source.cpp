#include <vector>
#include <math.h>

#define PI 3.1415927

int main() {
	struct Pt {
		double d, angle;
	};

	// Polar coordinates of the points (-2, 1) and (5, 1) respectively.
	std::vector<Pt> points = { { 2.2360679774997898, 2.6779450445889870 }, { 5.0990195135927845, 0.19739555984988075 } };

	double a, r = 0;

	double n = points.size();
	double sumOfWeights = n;

	double num1 = 0, num2 = 0, den1 = 0, den2 = 0;
	for (int i = 0; i < n; i++) {
		double iP = points[i].d, iTheta = points[i].angle;

		num1 += iP * iP * sin(2 * iTheta);
		den1 += iP * iP * cos(2 * iTheta);

		for (int j = 0; j < n; j++) {
			double jP = points[j].d, jTheta = points[j].angle;

			num2 += iP * jP * cos(iTheta) * sin(jTheta);
			den2 += iP * jP * cos(iTheta + jTheta);

		}
	}

	a = PI/2 - 0.5 * atan2((num1 - (2.0 / sumOfWeights) * num2), (den1 - (1.0 / sumOfWeights) * den2));

	for (int i = 0; i < n; i++) r += points[i].d * cos(points[i].angle - a);
	r /= sumOfWeights;

	return 0;
}