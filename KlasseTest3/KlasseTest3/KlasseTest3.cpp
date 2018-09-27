#include "stdafx.h"
#include "Date.h"
#include <iostream>
#include <string>
using namespace std;

void hold() {
	int temp;
	cin >> temp;
}

int main()
{
	Date aDate(19960101);
	aDate.print();
	/*for (int i = 0; i < 365; i++) {
		aDate.print();
		aDate.incDate();
	}*/
	//Date anotherDate(19270505);
	//cout << aDate.differenceInDays(anotherDate) << " " << aDate.weekDayString() << " " << anotherDate.weekDayString();
	hold();
    return 0;
}