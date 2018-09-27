#include "Bibliotek.h"
#include <iostream>
using namespace std;

Bibliotek::Bibliotek()
{
}

void Bibliotek::tilfoejEks(Eksemplar eksemplar)
{
	eksemplarListe.push_back(eksemplar);
}

void Bibliotek::tilfoejUdl(Udlaan udlaan)
{
	udlaanListe.push_back(udlaan);
}

int Bibliotek::tjekOmBogErTilgaengelig(const string& titel)
{
	int ikkeUdlaanteEksemplarer = 0;
	for (int i = 0; i < eksemplarListe.size(); i++) {	
		if (eksemplarListe[i].getBog().getTitel() == titel) ikkeUdlaanteEksemplarer++;
	}
	for (int i = 0; i < udlaanListe.size(); i++) {
		if (udlaanListe[i].getEksemplar().getBog().getTitel() == titel) ikkeUdlaanteEksemplarer--;
	}
	if (ikkeUdlaanteEksemplarer < 1) {
		Dato dato(0);
		for (int i = 0; i < udlaanListe.size(); i++) {
			if (udlaanListe[i].getEksemplar().getBog().getTitel() == titel && (udlaanListe[i].getDato().getDato() < dato.getDato() || dato.getDato() == 0)) dato = udlaanListe[i].getDato();
		}
		dato.incMonth();
		return dato.getDato();
	}
	else return 0;
}

void Bibliotek::listLaanersLaan(const string& laanerNavn)
{
	cout << "L�ner: " << laanerNavn << "\n";
	for (int i = 0; i < udlaanListe.size(); i++) {
		if (laanerNavn == udlaanListe[i].getLaaner().getNavn()) cout << udlaanListe[i].getEksemplar().getBog().getTitel() << " til d. " << udlaanListe[i].getDato().getDato() << "\n";
	}
	cout << "\n";
}

string Bibliotek::findMestPopulaereForfatter()
{
	if (udlaanListe.size() == 0) return "";
	vector<string> forfatterNavne;
	vector<int> forfatterUdlaan;
	vector<string> mestPopul�reForfattere;

	for (int i = 0; i < udlaanListe.size(); i++) {
		bool exists = false;
		for (int j = 0; j < forfatterNavne.size(); j++) {
			if (udlaanListe[i].getEksemplar().getBog().getForfatter().getNavn() == forfatterNavne[j]) {
				forfatterUdlaan[j]++;
				exists = true;
			}
		}
		if (!exists) {
			forfatterNavne.push_back(udlaanListe[i].getEksemplar().getBog().getForfatter().getNavn());
			forfatterUdlaan.push_back(1);
		}
	}
	int hoejesteUdlaan = 0;
	for (int i = 0; i < forfatterUdlaan.size(); i++) if (forfatterUdlaan[i] > hoejesteUdlaan) hoejesteUdlaan = forfatterUdlaan[i];
	for (int i = 0; i < forfatterUdlaan.size(); i++) if (forfatterUdlaan[i] == hoejesteUdlaan) mestPopul�reForfattere.push_back(forfatterNavne[i]);
	return mestPopul�reForfattere[rand() % mestPopul�reForfattere.size()]; //Siden der kan v�re flere forfattere med samme udl�nsantal, v�lger jeg en tilf�ldig. Man kan selvf�lgeligt g�re hvad man ellers kan finde p� med vektoren.
}


Bibliotek::~Bibliotek()
{
}
