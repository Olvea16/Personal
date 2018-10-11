#include "Hashtable.h"

int findNextPrime(int n)
{
	bool isPrime = false;
	while (!isPrime) {
		for (int i = 2; i < n / 2; i++) {
			isPrime = true;
			if (n % i == 0) {
				isPrime = false;
				n++;
				break;
			}
		}
	}
	return n;
}
