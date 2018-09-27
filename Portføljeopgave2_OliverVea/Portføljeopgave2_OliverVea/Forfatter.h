#pragma once
#include "Person.h"


class Forfatter :
	private Person
{
public:
	Forfatter(string navn, string nationalitet, int foedeAar, int doedsAar);
	string getNavn();
	~Forfatter();
private:
	string nationalitet;
	int foedeAar;
	int doedsAar;
};

