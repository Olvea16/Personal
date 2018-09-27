#include "stdafx.h"
#include "Board.h"
#include <iostream>

using namespace std;

int main()
{
	Board board;
	board.randomize();
	
	do {
		system("cls");
		board.printBoard();

		cout << "\n\nX: ";

		int x = 0;
		while (x > 9 || x < 1) cin >> x;
		x -= 1;

		cout << "Y: ";

		int y = 0;
		while (y > 9 || y < 1) cin >> y;
		y -= 1;

		cout << "Valid values: ";
		vector<int> vals = board.validValues(x, y);
		for (int i = 0; i < vals.size(); i++) {
			cout << vals[i];
			if (i != vals.size() - 1) cout << ", ";
		}
		cout << ". \nEnter value: ";

		int val;
		cin >> val;

		board.setValue(x, y, val);
	} while (!board.isComplete());
	
	cout << "You won! Congratulations!";

	system("pause");
	
    return 0;
}

