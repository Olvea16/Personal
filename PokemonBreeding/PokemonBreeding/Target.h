#pragma once
#include "Parent.h"

#define NO_TARGET (-1)

class Target :
	public Parent
{
public:
	Target();
	Target(int hp, int attack, int defense, int spattack, int spdefense, int speed, std::string nature, std::string ability);
	~Target();

	// Set

	// Get

	// Misc Methods
	std::vector<std::pair<eStat, int>> getRequiredStats();
};

