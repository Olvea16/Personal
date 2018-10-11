#pragma once

#include <string>

class EquationTree
{
public:
	EquationTree(std::string s);
	~EquationTree();
};

class EquationElement
{
public:
	enum eOperator { constant, variable, multiplication, divison, subtraction, addition, modulus, power, root, log };
	double getValue();

private:
	eOperator elementType;
	std::string s;
};

