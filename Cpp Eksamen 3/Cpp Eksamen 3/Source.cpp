#include <iostream>
#include <math.h>

using namespace std;

int main() {
	for (int i = 0; i < 1000; i++) {
		int digits = ceil(log10(i));
		int sum = 0;
		for (int j = 0; j < digits; j++) {
			int seperator = pow(10, (digits - j));
			sum += pow((i % seperator) / (seperator / 10),j + 1);
		}
		if (sum == i) cout << i << endl;
	}

	system("pause");
	return -1;
}