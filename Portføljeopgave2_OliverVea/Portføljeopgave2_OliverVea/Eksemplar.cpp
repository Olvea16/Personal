#include "Eksemplar.h"



Eksemplar::Eksemplar(int id, Bog bog) : id(id), bog(bog)
{
}

Bog Eksemplar::getBog()
{
	return bog;
}

bool Eksemplar::getLaanestatus()
{
	return udlaant;
}

void Eksemplar::setLaanestatus(bool status)
{
	udlaant = status;
}


Eksemplar::~Eksemplar()
{
}
