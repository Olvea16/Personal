#pragma once
#include "Cell.h"
#include <iostream>
#include <vector>

using namespace std;

class Board
{
public:
	Board();
	~Board();

	void randomize();

	vector<Cell> getRow(int row);
	vector<Cell> getColumn(int col);
	vector<Cell> getSquare(int row, int col);

	vector<int> validValues(int col, int row);

	void printBoard();

	bool setValue(int x, int y, int val);

	bool isComplete();
private:
	Cell cells[9][9];
};

