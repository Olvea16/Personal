#include "stdafx.h"
#include "Bil.h"
#include <iostream>
using namespace std;

int main()
{
	Bil enBil("RN1332", 1995);
	cout << enBil.getAargang() << " " << enBil.getRegistreringsNummer();
	int temp;
	cin >> temp;
    return 0;
}

