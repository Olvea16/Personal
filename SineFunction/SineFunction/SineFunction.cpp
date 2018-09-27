#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	while (true) {
		double input;
		cout << "Number: ";
		cin >> input;
		double output = sin(input);
		cout << output << endl;
	}
}

double sin(double x) {
	double pi = 3.1415927;
	while (x > 2 * pi) {
		x -= 2 * pi;
	}
	if (x >= 0 && x < pi * 1 / 2) {
		x = x - pow(x, 3) / 6 + pow(x, 5) / 120 - pow(x, 7) / 5040;
	}
	
	if (x >= pi * 1 / 2 && x < pi ) {
		x -= pi * 1 / 2;
		x = 1 - pow(x, 2) / 2 + pow(x, 4) / 24 - pow(x, 6) / 720;
	}
	if (x >= pi && x < pi * 3 / 2) {
		x -= pi;
		x = -(x - pow(x, 3) / 6 + pow(x, 5) / 120 - pow(x, 7) / 5040);
	}
	if (x >= pi * 3 / 2 && x <= pi * 2) {
		x -= pi * 3 / 2;
		x = -(1 - pow(x, 2) / 2 + pow(x, 4) / 24 - pow(x, 6) / 720);
	}
	return x;
}