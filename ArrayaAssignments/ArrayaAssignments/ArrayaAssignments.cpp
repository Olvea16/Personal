#include "stdafx.h"
#include "Array.h"
#include <time.h>
#include <iostream>
using namespace std;

int main()
{
	srand(time(NULL));
	int ar[100];
	for (int i = 0; i < 100; i++) ar[i] = rand() % 100;	
	Array myArray(ar, 100);
	myArray.printArray();
	myArray.selectionSort();
	myArray.printArray();

	int temp;
	cin >> temp;
    return 0;
}