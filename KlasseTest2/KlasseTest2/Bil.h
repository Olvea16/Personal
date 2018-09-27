#pragma once
#include <string>
using namespace std;

class Bil
{
public:
	Bil();
	Bil(string, int);
	string getRegistreringsNummer();
	int getAargang();
	~Bil();
private:
	string registreringsNummer;
	int aargang;
};

