#pragma once
#include "Forfatter.h"
#include <string>
class Bog
{
public:
	Bog(string titel, Forfatter forfatter, int udgivelsesAar);
	string getTitel();
	Forfatter getForfatter();
	~Bog();
private:
	string titel;
	Forfatter forfatter;
	int udgivelsesAar;
};

