// MathParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Interpretor.h"
#include <iostream>

int main()
{

	bool f = Interpretor::isBalanced("(a + b( * )a + c)");
	bool t = Interpretor::isBalanced("(a + b) * (a + c)");

    std::cout << "Hello World!\n"; 
}
