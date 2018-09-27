#pragma once
#include <string>
using namespace std;

class Date
{
public:
	Date();
	Date(int);
	int getDate();
	int getYear();
	int getMonth();
	int getDay();
	int getQuarter();
	bool getLeapYear();
	bool validate();
	int dayInYear();
	int remainDayInYear();
	void incDate();
	void decDate();
	int differenceInDays(Date aDay);
	int weekDay();
	string weekDayString();
	void print();
	~Date();
private:
	bool leapYear(int year);
	void incMonth();
	void incYear();
	void decMonth();
	void decYear();
	string getMonthString();
	int thisDate; /* YYYYMMDD */
	int dayArray[12];
};

