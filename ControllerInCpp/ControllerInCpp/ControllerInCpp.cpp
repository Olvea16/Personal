// ControllerInCpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "string"
#include "iostream"
#include "fstream"

using namespace std;

double setPoint;
const long double Kp = 100.0;
const long double Ti = 0.0;
const long double Td = 0.0;

const int N = 5;
const int M = 4;

const double Ts = 0.002;

const long double b[M] = { 0.00000537, 0.00001611, 0.00001611, 0.00000537 };
const long double a[N] = {1, -1.64, 0.2914, 0.3487, 0};

long double u[N] = {0,0,0,0,0}
long double y[n] = {0,0,0,0,0}

long double D = 0;
long double I = 0;

const int measurementAmount = 3;

double plantOut;
double measurements[measurementAmount];

void shiftY() {
	for (int i = N - 1; i > 0; i--) w[i] = w[i - 1];
	w[0] = input;
}

double controller(double input) {
	D = input - D;
	I += input;
	return Kp * (input + I * Ti + D * Td);
}

double plant(double input) {
	double y = 0;
	shiftW(input);
	for (int i = 1; i < N; i++) w[0] -= a[i] * w[i];
	for (int i = 0; i < M; i++) y += b[i] * w[i];
	return y;
}

void println(double s) {
	cout << s << endl;
}


int main()
{
	double r = 1;
	double e = r;
	double u = 0;
	double y;
	double y_old = 0;

	fstream someFile;
	someFile.open("Data.csv",ios::out);
	someFile << "t,e,u,w0,w1,w2,w3,y, ," << "r: " << r << ", Kp: " << Kp << ", Ti: " << Ti << ", Td: " << Td << "\n";
	for (int i = 0; i < (2.5 / Ts) + 1; i++) {
		if (!someFile.is_open()) {
			cout << "Luk filen, Oliver!";
			break;
		}
		e = r - y_old;
		u = controller(e);
		y = plant(e);
		y_old = y;

		string fileLine = to_string(i * Ts) + ',' + to_string(e) +  ',' + to_string(u) + ',' + to_string(w[0]) + ',' + to_string(w[1]) + ',' + to_string(w[2]) + ',' + to_string(w[3]) + ',' + to_string(y) + '\n';
		someFile << fileLine;
		string consoleLine = "Ts: " + to_string(i * Ts) + ", e: " + to_string(e) + ", u: " + to_string(u) + ", y: " + to_string(y) + '\n';
		cout << consoleLine;
	}
	someFile.close();
	system("pause");
    return 0;
}