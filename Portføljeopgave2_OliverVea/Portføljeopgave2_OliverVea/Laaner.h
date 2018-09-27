#pragma once
#include "Person.h"
class Laaner :
	private Person
{
public:
	Laaner(string navn, int id);
	string getNavn();
	~Laaner();
private:
	int id;
};

