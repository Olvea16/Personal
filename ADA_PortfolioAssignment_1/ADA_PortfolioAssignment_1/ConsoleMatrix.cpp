#include "stdafx.h"
#include "ConsoleMatrix.h"

ConsoleMatrix::ConsoleMatrix(int cols, int padding) : cols(cols), padding(padding)
{
}

ConsoleMatrix::~ConsoleMatrix()
{
}

int ConsoleMatrix::longestString(int col)
{
	int length = 0;
	for (int i = 0; i < matrix.size(); i++) if (matrix[i][col].size() > length) length = matrix[i][col].size();
	return length;
}

void ConsoleMatrix::addRow(std::string s)
{
	std::vector<std::string> row(cols);
	if (cols > 0) row[0] = s;
	matrix.push_back(row);
}

void ConsoleMatrix::addRow(std::vector<std::string> row)
{
	while (row.size() < cols) row.push_back("");
	matrix.push_back(row);
}

void ConsoleMatrix::print()
{
	std::vector<int> colWidths(cols);
	for (int c = 0; c < cols; c++) colWidths[c] = longestString(c);
	for (int r = 0; r < matrix.size(); r++) {
		for (int c = 0; c < cols; c++) {
			std::cout << std::setw(colWidths[c]) << std::left << matrix[r][c] << std::setw(padding) << " ";
		}
		std::cout << std::endl;
	}
}
