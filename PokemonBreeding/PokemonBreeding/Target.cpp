#include "stdafx.h"
#include "Target.h"

Target::Target()
{
}

Target::Target(int hp, int attack, int defense, int spattack, int spdefense, int speed, std::string nature, std::string ability)
{
	stats[0] = Stat(ehp, hp);
	stats[1] = Stat(eatk, attack);
	stats[2] = Stat(edef, defense);
	stats[3] = Stat(esatk, spattack);
	stats[4] = Stat(esdef, spdefense);
	stats[5] = Stat(espd, speed);

	this->nature = nature;
	this->ability = ability;
}


Target::~Target()
{
}

std::vector<std::pair<eStat, int>> Target::getRequiredStats()
{
	std::vector<std::pair<eStat, int>> result;
	for (int i = 0; i < 6; i++) if (stats[i].getValue() != NO_TARGET) result.push_back(std::pair<eStat, int>(stats[i].getStat(), stats[i].getValue()));
	return result;
}
