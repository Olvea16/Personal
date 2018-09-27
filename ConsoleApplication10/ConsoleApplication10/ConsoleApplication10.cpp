// ConsoleApplication10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

vector<int> find_primes(int val) {
	vector<int> primes;
	for (int i = 2; i < val + 1; i++) {
		bool prime = true;
		for (int j = 0; j < primes.size(); j++) {
			if (i % primes[j] == 0) {
				prime = false;
				break;
			}
		}
		if (prime) primes.push_back(i);
	}
	return primes;
}

int main()
{
	long int num;
	cout << "Indtast tal: ";
	cin >> num;

	vector<int> primes = find_primes(num);

	unordered_map<int,int> divisors;

	for (int i = primes.size() - 1; i >= 2; i--) {
		divisors[i] = 0;
		while (double(num) / double(primes[i]) == floor(num / primes[i])) {
			divisors[i]++;
			num /= primes[i];
		}
	}

	for (int i = 0; i < divisors.size(); i++) {
		if (divisors[i] != 0) cout << i << "^" << divisors[i] << " ";
	}

    return 0;
}

