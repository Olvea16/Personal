// ADA_Exercises_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

int sum(int n) {
	if (n <= 1)  return n;
	else return n + sum(n - 1);

}

int gcd(int a, int b) {
	if (a == b) return a;
	if (a > b) return gcd(a - b, b);
	else return gcd(a, b - a);
}

int fib(int n) {
	if (n <= 2)  return 1;
	else return (fib(n - 1) + fib(n - 2));
}

void println(int val) {
	std::cout << val << "\n";
}

void print_to(int n) {
	if (n > 1) print_to(n - 1);
	println(n);
}

int main()
{
	print_to(10);
}