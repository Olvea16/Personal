// ConsoleApplication7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int getLength(int input);
int getLength(string input);

int main()
{
	int N = 100000;
	long double avg = 0;
	const int n = 1000;
	const int die = 30;
	const long int nCount = n * die;
	int numbers[nCount];
	for (int i = 0; i < (nCount); i++) numbers[i] = 0;
	for (int i = 0; i < N; i++) {
		int sum = 0;
		for (int i = 0; i < die; i++) {
			sum += rand() % n + 1;
		}
		numbers[sum - 1]++;
	}
	for (int i = 0; i < nCount; i++) avg += numbers[i] * (i + 1);
	avg /= N;
	cout << "Gennemsnit: " << avg << endl;

	// PRINTING
	int maxSpaces = getLength(nCount) + 4;
	int maxStarsAmount = 42 - maxSpaces;
	int maxStarsIndeks = 0;
	for (int i = 0; i < nCount; i++) if (numbers[i] > numbers[maxStarsIndeks]) maxStarsIndeks = i;
	int total = 0;

	/*
	for (int i = 0; i < nCount; i++) {
		long float percentage = round(1000.0 * numbers[i] / N);
		percentage /= 10.0;
		cout << i + 1 << " (" << percentage << "%): ";
		int stars = numbers[i] * maxStarsAmount / numbers[maxStarsIndeks];
		int spaces = maxSpaces - getLength(i + 1) - getLength(to_string(percentage));
		for (int j = 0; j < spaces; j++) cout << ' ';
		for (int j = 0; j < stars; j++) cout << '*';
		cout << endl;
	}
	//*/

	ofstream myfile("result.csv",std::ofstream::out);
	for (int i = 0; i < nCount; i++) myfile << i << ',' << numbers[i] << endl;
	myfile.close();

	int a;
	cin >> a;
    return 0;
}

int getLength(int input) {
	int result = to_string(input).size();
	return result;
}

int getLength(string input) {
	int result = input.size();
	for (int i = 0; i < result; i++) {
		int indeks = result - i - 1;
		if (input[indeks] != '0')
			if (input[indeks] == '.') return result - i + 1;
			return (result - i);
	}
	return 1;
}