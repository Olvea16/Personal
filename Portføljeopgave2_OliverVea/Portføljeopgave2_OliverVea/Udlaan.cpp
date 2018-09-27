#include "Udlaan.h"

Udlaan::Udlaan(Dato dato, Laaner laaner, Eksemplar eksemplar) : dato(dato), laaner(laaner), eksemplar(eksemplar)
{
}

Eksemplar Udlaan::getEksemplar()
{
	return eksemplar;
}

Dato Udlaan::getDato()
{
	return dato;
}

Laaner Udlaan::getLaaner()
{
	return laaner;
}

Udlaan::~Udlaan()
{
}
