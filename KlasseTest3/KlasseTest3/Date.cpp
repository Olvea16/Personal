#include "stdafx.h"
#include "Date.h"
#include <iostream>
#include <string>
using namespace std;

string dayEnding(int day) {
	switch (day) {
	case 1:
		return "st";
	case 2:
		return "nd";
	case 3:
		return "rd";
	default:
		return "th";
	}
}

Date::Date()
{
}

Date::Date(int inDate) {
	int tempArray[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	for (int i = 0; i < 12; i++) {
		dayArray[i] = tempArray[i];
	}
	thisDate = inDate;
}

int Date::getDate() {
	return thisDate;
}

int Date::getYear() {
	return thisDate / 10000;
}

int Date::getMonth() {
	if (getLeapYear()) {
		dayArray[1] = 29;
	}
	return (thisDate / 100) % 100;
}

int Date::getDay() {
	return thisDate % 100;
}

bool Date::validate() {
	return !((getDay() > 31) || (getMonth() > 12));
}

int Date::getQuarter() {
	if (validate()) {
		return getMonth() / 4 + 1;
	}
	else {
		return 0;
	}
}

bool Date::getLeapYear() {
	return leapYear(getYear());
}

int Date::dayInYear() {
	if (validate()) {
		int days = 0;
		for (int i = 0; i < getMonth() - 1; i++) {
			days += dayArray[i];
		}
		days += getDay();
		return days;
	}
	return 0;
}

int Date::remainDayInYear() {
	if (leapYear(getYear())) {
		return 366 - dayInYear();
	}
	else {
		return 365 - dayInYear();
	}
}

void Date::incDate() {
	if (getDay() == dayArray[getMonth() - 1]) {
		thisDate -= dayArray[getMonth() - 1] - 1;
		incMonth();
	}
	else {
		thisDate++;
	}
}

void Date::decDate() {
	if (getDay() == 1) {
		decMonth();
		thisDate += dayArray[getMonth() - 1] - 1;
	}
	else {
		thisDate--;
	}
}

int Date::differenceInDays(Date aDay) {
	int difference = 0;
	if (aDay.getDate() > thisDate) {
		difference = aDay.dayInYear() - dayInYear(); 
		for (int i = 0; i < aDay.getYear() - getYear(); i++) {
			if (leapYear(getYear() + i)) {
				difference += 366;
			}
			else {
				difference += 365;
			}
		}
	}
	else {
		difference = dayInYear() - aDay.dayInYear();
		for (int i = 0; i < getYear() - aDay.getYear(); i++) {
			if (leapYear(aDay.getYear() + i)) {
				difference += 366;
			}
			else {
				difference += 365;
			}
		}
	}
	return difference;
}

int Date::weekDay() {
	int days = dayInYear();
	for (int i = 0; i < getYear(); i++) {
		if (leapYear(i)) {
			days += 366;
		}
		else {
			days += 365;
		}
	}
	return (days + 4) % 7;
}

string Date::weekDayString() {
	string weekNames[7] = { "Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday" };
	return weekNames[weekDay()];
}

void Date::print() {
	if (validate()) {
		cout << weekDayString() << " the " << getDay() << dayEnding(getDay()) << " of ";
		cout << getMonthString() << " " << getYear() << ".\n";
		cout << dayInYear() << dayEnding(dayInYear()) << " day of the year. \n";
		if (getLeapYear()) cout << "This is a leap year. \n";

	}
	else {
		cout << "Invalid date.";
	}
}

bool Date::leapYear(int year) {
	return ((year % 4 == 0) && (!(year % 100 == 0) || (year % 400 == 0)));
}

void Date::incMonth() {
	if (getMonth() == 12) {
		incYear();
		thisDate -= 1100;
	}
	else {
		thisDate += 100;
	}
}

void Date::incYear() {
	thisDate += 10000;
}

void Date::decMonth() {
	if (getMonth() == 1) {
		decYear();
		thisDate += 1100;
	}
	else {
		thisDate -= 100;
	}
}

void Date::decYear() {
	thisDate -= 10000;
}

string Date::getMonthString() {
	string monthNames[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	return monthNames[getMonth() - 1];
}

Date::~Date()
{
}
