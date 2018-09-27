// ChanceCalculation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <math.h>
#include <iostream>
#include <string>

using namespace std;

pair<int, double> calculateAmount(float successProbability, float targetProbability) {
	pair<int, double> result;

	double a = log(1 - successProbability);
	double b = log(1 - targetProbability);
	result.first = ceil(b / a);

	result.second = 1.0 - pow(1 - successProbability, result.first);

	return result;
}

string toStringDecimals(double number, unsigned char decimals) {
	int decimalFactor = pow(10, decimals);
	int stringNum = round(number * decimalFactor);
	int integer = stringNum / decimalFactor;
	int decimalPart = stringNum % decimalFactor;
	string result = to_string(integer) + '.' + to_string(decimalPart);

	return result;
}

int main()
{
	float sP = 0.05;
	float tP = 0.95;

	pair<int, double> probability = calculateAmount(sP, tP);

	cout << "Attempts: " << probability.first << " (" << toStringDecimals(probability.second * 100,2) << "%)\n";
    return 0;
}

