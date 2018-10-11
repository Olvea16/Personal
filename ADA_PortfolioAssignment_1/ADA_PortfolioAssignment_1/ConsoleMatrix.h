#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

class ConsoleMatrix
{
public:
	ConsoleMatrix(int cols = 3, int padding = 4);
	~ConsoleMatrix();

	int longestString(int row);

	void addRow(std::string s);
	void addRow(std::vector<std::string> row);

	void print();

private:
	int padding;
	int cols;
	std::vector<std::vector<std::string>> matrix;
};

