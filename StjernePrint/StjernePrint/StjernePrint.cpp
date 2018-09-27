#include "stdafx.h"
#include <iostream>
using namespace std;


int main()
{
	cout << "i:" << endl;

	int x = 10;
	int y = 4;
	for (int i = 0; i < y; i++) {
		for (int i = 0; i < x; i++) {
			cout << "*";
		}
		cout << endl;
	}

	cout << endl << "ii:" << endl;

	x = 1;
	y = 5;
	for (int i = 0; i < y; i++) {
		for (int i = 0; i < x; i++) {
			cout << "*";
		}
		cout << endl;
		x++;
	}

	cout << endl << "iii:" << endl;

	x = 4;
	y = 5;
	for (int i = 0; i < y; i++) {
		for (int i = 0; i < 5; i++) {
			if (i < x) {
				cout << " ";
			}
			if (i >= x) {
				cout << "*";
			}
		}
		cout << endl;
		x--;
	}

	cout << endl << "iv:" << endl;

	x = 0;
	y = 5;
	for (int i = 0; i < y; i++) {
		for (int i = -4; i < 5; i++) {
			if (abs(i) > x) {
				cout << " ";
			}
			if (abs(i) <= x) {
				cout << "*";
			}
		}
		cout << endl;
		x++;
	}

	cout << endl << "v:" << endl;

	x = 0;
	y = 5;
	for (int i = 0; i < y; i++) {
		for (int i = -4; i < 5; i++) {
			if (abs(i) > x) {
				cout << " ";
			}
			if (abs(i) <= x) {
				cout << x + 1;
			}
		}
		cout << endl;
		x++;
	}

	cout << endl << "vi:" << endl;

	x = 0;
	y = 5;
	for (int i = 0; i < y; i++) {
		for (int i = -4; i < 5; i++) {
			if (abs(i) > x) {
				cout << " ";
			}
			if (abs(i) <= x) {
				cout << abs(i) + 1;
			}
		}
		cout << endl;
		x++;
	}

	int temp;
	cin >> temp;
    return 0;
}

