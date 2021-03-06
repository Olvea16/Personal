// Containers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Vector.h"

#include <vector>
#include <iostream>

int sum(int n) {
	if (n <= 1) return n;
	return n + sum(n - 1);
}

int main()
{
	std::vector<int> _vec;
	Vector<int> vec;

	for (int i = 0; i < 1000000; i++) {
		_vec.push_back(i);
		vec.push(i);
	}

	int a;


	std::vector<int>::const_iterator _vec_end = _vec.end();
	for (std::vector<int>::const_iterator i = _vec.begin(); i != _vec_end; i++) {
		a = *i;
	}

	Vector<int>::iterator vec_end = vec.end();
	for (Vector<int>::iterator i = vec.begin(); i != vec_end; i++) {
		a = *i;
	}

    return 0;
}