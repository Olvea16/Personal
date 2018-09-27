#include "Laaner.h"

Laaner::Laaner(string navn, int id) : Person(navn), id(id)
{
}

string Laaner::getNavn()
{
	return navn;
}

Laaner::~Laaner()
{
}
