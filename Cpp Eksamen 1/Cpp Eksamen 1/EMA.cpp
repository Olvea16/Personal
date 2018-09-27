#include "stdafx.h"
#include "EMA.h"


EMA::EMA()
{
}

EMA::EMA(string address) : emailAddress(address)
{
}

EMA::~EMA()
{
}

string EMA::getEMA()
{
	return emailAddress;
}

void EMA::setEMA(string address)
{
	emailAddress = address;
}

bool EMA::isValid()
{
	return (snabelA() != -1 && dot() && checkLengths() && checkChars());
}

int EMA::snabelA()
{
	int indeks = -1;
	for (int i = 0; i < emailAddress.length(); i++) {
		if (emailAddress[i] == '@')
			if (indeks == -1) indeks = i;
			else return -1;
	}
	return indeks;
}

bool EMA::dot()
{
	int indeks = -1;
	int atIndeks = snabelA();
	if (atIndeks != -1) {
		for (int i = atIndeks + 3; i < emailAddress.length(); i++) {
			if (emailAddress[i] == '.')
				if (indeks == -1) indeks = i;
				else return -1;
		}
	}
	return indeks != -1;
}

bool EMA::checkLengths()
{
	int localLength = snabelA();
	int domainLength = emailAddress.length() - localLength - 1;

	if (localLength >= 5 && localLength <= 64 && domainLength >= 5 && domainLength <= 255) return true;
	return false;
}

bool EMA::checkChars()
{
	string validChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890@.%&";
	for (int i = 0; i < emailAddress.length(); i++) {
		bool valid = false;
		for (int j = 0; j < validChars.length(); j++) valid |= (emailAddress[i] == validChars[j]);
		if (!valid) return false;
	}
}
