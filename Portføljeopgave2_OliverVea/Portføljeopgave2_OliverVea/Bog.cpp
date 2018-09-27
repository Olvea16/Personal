#include "Bog.h"

Bog::Bog(string titel, Forfatter forfatter, int udgivelsesAar) : titel(titel), forfatter(forfatter), udgivelsesAar(udgivelsesAar)
{
}

string Bog::getTitel()
{
	return titel;
}

Forfatter Bog::getForfatter()
{
	return forfatter;
}

Bog::~Bog()
{
}
