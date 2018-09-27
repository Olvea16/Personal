#include "stdafx.h"
#include "EMA.h"

#include <iostream>

using namespace std;

int main()
{
	EMA e("sps@mmmi.sdu.dk");
	cout << e.getEMA() << " " << e.isValid() << endl; // false
	e.setEMA("Bølle Bob");
	cout << e.getEMA() << " " << e.isValid() << endl; // false
	e.setEMA("BoelleBob@sdu.dk");
	cout << e.getEMA() << " " << e.isValid() << endl; // true
	e.setEMA("polle@m.com");
	cout << e.getEMA() << " " << e.isValid() << endl; // false
	e.setEMA("polle@dm.com");
	cout << e.getEMA() << " " << e.isValid() << endl; // true
	e.setEMA("pallesen@gm<ail.com");
	cout << e.getEMA() << " " << e.isValid() << endl; // false
	e.setEMA("pallesen@gmail.com");
	cout << e.getEMA() << " " << e.isValid() << endl; // true
	e.setEMA("peter@piil@gmail.com");
	cout << e.getEMA() << " " << e.isValid() << endl; // false
	e.setEMA("peterpiil@gmail.com");
	cout << e.getEMA() << " " << e.isValid() << endl; // true

	system("pause");
}

