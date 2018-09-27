#include "stdafx.h"
#include "Bil.h"


Bil::Bil()
{
}

Bil::Bil(string etR, int enA) {
	registreringsNummer = etR;
	aargang = enA;
}

string Bil::getRegistreringsNummer() {
	return registreringsNummer;
}

int Bil::getAargang() {
	return aargang;
}

Bil::~Bil()
{
}
