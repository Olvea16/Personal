#include "Dato.h"



Dato::Dato(int dato) : datoen(dato)
{
}

int Dato::getDato()
{
	return datoen;
}

void Dato::incMonth()
{
	int month = (datoen / 100) % 10000;
	if (month == 12) datoen += 8900;
	else datoen += 100;
}


Dato::~Dato()
{
}
