#include "stdafx.h"
#include "Pokemon.h"


Pokemon::Pokemon()
{
}

Pokemon::Pokemon(std::string pokemon, int abilities, std::string hiddenAbility) : pokemon(pokemon), abilities(abilities), hiddenAbility(hiddenAbility)
{
}


Pokemon::~Pokemon()
{
}

std::string Pokemon::getPokemon()
{
	return pokemon;
}
