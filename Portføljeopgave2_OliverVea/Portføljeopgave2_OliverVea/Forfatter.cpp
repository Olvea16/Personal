#include "Forfatter.h"

Forfatter::Forfatter(string navn, string nationalitet, int foedeAar, int doedsAar) : Person(navn), nationalitet(nationalitet), foedeAar(foedeAar), doedsAar(doedsAar)
{
}

string Forfatter::getNavn()
{
	return navn;
}

Forfatter::~Forfatter()
{
}
