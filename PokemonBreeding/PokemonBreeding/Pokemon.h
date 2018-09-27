#pragma once

#include <string>

#include "Stat.h"

class Pokemon
{
public:
	Pokemon();
	Pokemon(std::string pokemon, int abilities = 2, std::string hiddenAbility = "");
	~Pokemon();

	// Get
	std::string getPokemon();
private:
	std::string pokemon;
	int abilities;
	std::string hiddenAbility;
};

