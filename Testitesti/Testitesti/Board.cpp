#include "stdafx.h"
#include "Board.h"


Board::Board()
{
}


Board::~Board()
{
}

void Board::randomize()
{
	/*
	for (int i = 0; i < 40; i++) {
		int x = rand() % 9;
		int y = rand() % 9;
		Cell* cell = &cells[x][y];
		if (!(cell->isConst())) {
			vector<int> values = validValues(x, y);
			if (values.size() != 0) {
				int value = values[rand() % values.size()];
				cell->setValue(value);
				cell->setConst();
			}
		}
	}
	*/
}

vector<Cell> Board::getRow(int row)
{
	vector<Cell> returnCells;
	for (int i = 0; i < 9; i++) {
		returnCells.push_back(cells[i][row]);
	}
	return returnCells;
}

vector<Cell> Board::getColumn(int col)
{
	vector<Cell> returnCells;
	for (int i = 0; i < 9; i++) {
		returnCells.push_back(cells[col][i]);
	}
	return returnCells;
}

vector<Cell> Board::getSquare(int row, int col)
{
	vector<Cell> returnCells;
	for (int i = 0; i < 9; i++) {
		returnCells.push_back(cells[col * 3 + i % 3][row * 3 + i / 3]);
	}
	return returnCells;
}

vector<int> Board::validValues(int col, int row)
{
	vector<int> validVals;
	for (int i = 1; i < 10; i++) {
		validVals.push_back(i);
	}
	for each (Cell c in getRow(row)) {
		for (int i = 0; i < validVals.size(); i++) {
			if (c.getValue() == validVals[i]) validVals.erase(validVals.begin() + i);
		}
	}
	for each (Cell c in getColumn(col)) {
		for (int i = 0; i < validVals.size(); i++) {
			if (c.getValue() == validVals[i]) validVals.erase(validVals.begin() + i);
		}
	}
	for each (Cell c in getSquare(row / 3, col / 3)) {
		for (int i = 0; i < validVals.size(); i++) {
			if (c.getValue() == validVals[i]) validVals.erase(validVals.begin() + i);
		}
	}
	return validVals;
}

void Board::printBoard()
{
	for (int i = 0; i < 9 * 9; i++) {
		if (i % 3 == 0 && !(i / 3 == 0) && !(i % 9 == 0)) cout << "| ";
		if (i % (9 * 3) == 0 && i != 0) {
			cout << endl;
			for (int i = 0; i < 21; i++) {
				if (i == 6 || i == 14) cout << "+";
				else cout << "-";
			}
		}
		if (i % 9 == 0) cout << endl;
		cout << cells[i % 9][i / 9].getValue() << " ";
		
	}
}

bool Board::setValue(int x, int y, int val)
{
	vector<int> validVals = validValues(x, y);
	for (int i = 0; i < validVals.size(); i++) {
		if (val == validVals[i]) {
			cells[x][y].setValue(val);
			return true;
		}
	}
	return false;
}

bool Board::isComplete()
{
	for (int i = 0; i < 9 * 9; i++) {
		if (cells[i % 9][i / 9].getValue() == 0) return false;
	}
	return true;
}
