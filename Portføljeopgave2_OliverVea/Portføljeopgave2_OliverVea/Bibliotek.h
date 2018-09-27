#pragma once
#include "Eksemplar.h"
#include "Udlaan.h"
#include <vector>

class Bibliotek
{
public:
	Bibliotek();
	void tilfoejEks(Eksemplar eksemplar);
	void tilfoejUdl(Udlaan udlaan);
	int tjekOmBogErTilgaengelig(const string&);
	void listLaanersLaan(const string&);
	string findMestPopulaereForfatter();
	~Bibliotek();
private:
	vector<Eksemplar> eksemplarListe;
	vector<Udlaan> udlaanListe;
};

