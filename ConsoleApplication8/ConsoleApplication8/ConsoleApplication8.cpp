// ConsoleApplication8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <math.h>

int state = 0;
const double A = 100.0;
const double f = 1.0/1000;
const int maxLength = 100;
int length = 0;
double t;
int sleepyTime;


using namespace std;

void displayNextLine();
void resetConsole();

int main()
{
	time_t startTime = GetTickCount();

	while (true) {
		cout << '.';
		displayNextLine();
		t = GetTickCount() - startTime;
		sleepyTime = A / 2.0 * sin(f * t / 2.0 * 3.1415927) + A / 2.0 + 50.0;
		Sleep(sleepyTime);
	
		if (length++ == maxLength) resetConsole();
		else cout << '\b';
	}
    return 0;
}

void displayNextLine() {
	switch (state) {
	case (0):
		cout << '|';
		state++;
		break;

	case(1):
		cout << '/';
		state++;
		break;

	case(2):
		cout << '-';
		state = 0;
		break;

	default:
		state = 0;
		break;
	}
}

void resetConsole() {
	length = 0;
	system("cls");
}