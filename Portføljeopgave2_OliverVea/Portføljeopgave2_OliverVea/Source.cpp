/*
Metoden med udlaan.getEksemplar().getBog().getTitel() kan se lidt rodet ud, men det giver mere fleksibilitet, da man har adgang til alle leddene igennem metodekaldende.
f.eks. udlaan.getEksemplar().getBog().getForfatter().
*/

#include "Forfatter.h"
#include "Bog.h"
#include "Eksemplar.h"
#include "Laaner.h"
#include "Udlaan.h"
#include "Bibliotek.h"
#include "Dato.h"
#include <iostream>
#include <vector>

using namespace std;
int main()
{
	Bibliotek bib;

	Forfatter mah("Martin A. Hansen", "dansk", 1909, 1955);
	Bog lgn1("Loegneren", mah, 1950);
	
	Eksemplar eks1(1001, lgn1);
	Eksemplar eks2(1002, lgn1);

	bib.tilfoejEks(eks1);
	bib.tilfoejEks(eks2);

	Forfatter hp("Henrik Pontoppidan", "dansk", 1857, 1943);
	Bog lp("Lykke-Per", hp, 1898);
	Eksemplar eks3(1011, lp);

	bib.tilfoejEks(eks3);

	Forfatter jrrt("J.R.R. Tolkien", "britisk", 1892, 1973);
	Bog fr("The Fellowship of the Ring", jrrt, 1954);
	Bog tt("The two Towers", jrrt, 1954);
	Bog rk("The Return of the King", jrrt, 1955);
	Eksemplar eks4(1021, fr);
	Eksemplar eks5(1022, tt);
	Eksemplar eks6(1023, rk);

	bib.tilfoejEks(eks4);
	bib.tilfoejEks(eks5);
	bib.tilfoejEks(eks6);

	Laaner po("Petrine Ottesen", 101);

	Udlaan udl1(Dato(20161026), po, eks1);
	Udlaan udl2(Dato(20161030), po, eks5);
	Udlaan udl3(Dato(20161029), po, eks3);

	bib.tilfoejUdl(udl1);
	bib.tilfoejUdl(udl2);
	bib.tilfoejUdl(udl3);

	Laaner te("Torsten Eriksen", 101);

	Udlaan udl4(Dato(20161018), te, eks4);
	Udlaan udl5(Dato(20161018), te, eks6);

	bib.tilfoejUdl(udl4);
	bib.tilfoejUdl(udl5);

	bib.listLaanersLaan("Torsten Eriksen");
	bib.listLaanersLaan("Petrine Ottesen");
	cout << "Mest populære forfatter: " << bib.findMestPopulaereForfatter() << "\n";
	
	cout << "Tilføjer 10 af Løgneren \n";

	for (int i = 0; i < 10; i++) {
		bib.tilfoejUdl(Udlaan(Dato(20161218),te, Eksemplar(1002 + i, lgn1)));
	}

	cout << "Mest populære forfatter: " << bib.findMestPopulaereForfatter() << "\n";

	int loegnTilg = bib.tjekOmBogErTilgaengelig("Loegneren");
	if (loegnTilg == 0) cout << "Løgneren kan lånes. \n";
	else cout << "Løgneren kan lånes fra d. " << loegnTilg << endl;

	system("pause");
}