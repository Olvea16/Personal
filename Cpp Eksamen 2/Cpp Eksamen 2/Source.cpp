#include <iostream>
#include <math.h>

using namespace std;

int main() {
	for (int i = 2; i < 100; i++) {
		int square = i * i;
		for (int j = 0; j < ceil(log10(square)); j++) {
			int seperator = pow(10, j);
			int upper = square / seperator;
			int lower = square % seperator;
			if (i == upper + lower) cout << i << endl;
		}
	}

	system("pause");
	return -1;
}