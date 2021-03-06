// PrimeLocator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <chrono>

void methodOne(long int max) {
	size_t primeAmount = 0;
	long int* primeArray = new long int[max / 2 + 1];

	for (long int i = 2; i < max + 1; i++) {
		bool notPrime = false;
		for (long int j = 0; j < primeAmount && !notPrime; j++) if (i % primeArray[j] == 0) notPrime = true;
		if (!notPrime) primeArray[primeAmount++] = i;
	}

	std::cout << primeArray[primeAmount - 1] << std::endl;
}

void methodTwo(long int max) {
	bool foundPrime = false;
	for (unsigned long long int i = max; i > 1 && !foundPrime; i--) {
		bool isPrime = true;
		int inc = 1;
		for (unsigned long long int j = 2; j < max / 2 + 1 && isPrime; j += inc) {
			if (j == 3) inc = 2;
			isPrime &= ((i % j) != 0);
		}
		if (isPrime) {
			foundPrime = true;
			std::cout << i << std::endl;
		}
	}
}


int main()
{
	auto t = std::chrono::system_clock::now();
	methodOne(3);
	auto t1 = std::chrono::system_clock::now();
	std::chrono::duration<double> dt1 = t1 - t;
	std::cout << "Time: " << dt1.count() << std::endl;
	methodTwo(3);
	auto t2 = std::chrono::system_clock::now();
	std::chrono::duration<double> dt2 = t2 - t1;
	std::cout << "Time: " << dt2.count() << std::endl;

    return 0;
}

