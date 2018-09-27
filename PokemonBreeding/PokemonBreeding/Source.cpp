// PokemonBreeding.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Daycare.h"
#include "Parent.h"
#include "Pokemon.h"
#include "Target.h"


#include <string>
#include <iostream>

int Parent::latestId = 0;

int main()
{
	Daycare daycare;

	daycare.selectFile("Data.xml");

	//* Breeding setup /*
	Pokemon ditto("Ditto");
	Pokemon jangmoo("Jangmo-o");
	Pokemon larvesta("Larvesta");
	Pokemon honedge("Honedge");

	Parent dittoA(ditto, 31, 31, 25, 31, 31, 5, "Relaxed");
	Parent dittoB(ditto, 31, 31, 31, 14, 29, 31, "Jolly", "Destiny Knot");

	Parent jangmooA(jangmoo, 31, 31, 31, 24, 29, 31, "Jolly", "Everstone");

	Parent larvestaA(larvesta, 31, 10, 10, 31, 10, 10, "Bold", "Destiny Knot");

	Parent honedgeA(honedge, 31, 31, 31, 31, 31, 31, "Jolly", "Everstone");

	daycare.registerParent(dittoA);
	daycare.registerParent(dittoB);
	daycare.registerParent(jangmooA);
	daycare.registerParent(larvestaA);
	daycare.registerParent(honedgeA);

	daycare.insert(dittoA, 0);
	daycare.insert(honedgeA, 1);

	daycare.newTarget(NO_TARGET, NO_TARGET, NO_TARGET, NO_TARGET, NO_TARGET, 0, "Jolly");
	//*/

	//* Breeding Printing
	std::cout << "PC:" << std::endl;
	daycare.printBox();

	std::cout << "Slots:" << std::endl;
	daycare.printSlots();

	std::cout << "Target Probability:" << std::endl;
	daycare.printTargetProbabilities();
	//*/

	//daycare.printStorage();

	int a;
	std::cin >> a;
	return 0;
}
