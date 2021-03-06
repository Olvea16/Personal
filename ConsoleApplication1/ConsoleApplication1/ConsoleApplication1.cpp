// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

int main()
{

	int steps = 6;
	vector<int> solutions;

	int variations = pow(2, steps);

	for (int i = 0; i < variations; i++) {
		vector<int> pos;
		bool invalid = false;
		for (int j = 1; j < steps / 2 + 1; j++) {
			pos.push_back(0);
			for (int n = 0; n < steps; n++) {
				if (n % j == 0) {
					int offset = pow(2, n);
					if ((i / offset) % 2 == 1) pos[j - 1]++;
					else pos[j - 1]--;
					if (abs(pos[j - 1]) >= 2) {
						invalid = true;
						break;
					}
				}
			}
			if (invalid) break;
		}
		if (!invalid)
			cout << i;
	}

    return 0;
}

