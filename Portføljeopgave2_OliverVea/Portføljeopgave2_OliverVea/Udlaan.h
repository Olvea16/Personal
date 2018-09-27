#pragma once
#include "Dato.h"
#include "Eksemplar.h"
#include "Laaner.h"

class Udlaan
{
public:
	Udlaan(Dato dato, Laaner laaner, Eksemplar eksemplar);
	Eksemplar getEksemplar();
	Dato getDato();
	Laaner getLaaner();
	~Udlaan();
private:
	Dato dato;
	Laaner laaner;
	Eksemplar eksemplar;
};

