#include "stdafx.h"
#include "Parent.h"


Parent::Parent()
{
}

Parent::Parent(Pokemon pokemon, char hp, char attack, char defense, char spattack, char spdefense, char speed, std::string nature, std::string ability, std::string item) : pokemon(pokemon), item(item), nature(nature), ability(ability)
{
	stats[0] = Stat(ehp, hp);
	stats[1] = Stat(eatk, attack);
	stats[2] = Stat(edef, defense);
	stats[3] = Stat(esatk, spattack);
	stats[4] = Stat(esdef, spdefense);
	stats[5] = Stat(espd, speed);

	id = latestId;
	latestId++;
}

Parent::Parent(Pokemon pokemon, char hp, char attack, char defense, char spattack, char spdefense, char speed, std::string nature, std::string ability, std::string item, int id) : pokemon(pokemon), item(item), nature(nature), ability(ability), id(id)
{
	stats[0] = Stat(ehp, hp);
	stats[1] = Stat(eatk, attack);
	stats[2] = Stat(edef, defense);
	stats[3] = Stat(esatk, spattack);
	stats[4] = Stat(esdef, spdefense);
	stats[5] = Stat(espd, speed);
}


Parent::~Parent()
{
}

void Parent::setItem(std::string item)
{
	this->item = item;
}

Pokemon Parent::getPokemon()
{
	return pokemon;
}

std::string Parent::getItem()
{
	return item;
}

std::string Parent::getNature()
{
	return nature;
}

std::vector<Stat> Parent::getStats()
{
	std::vector<Stat> result;
	for (Stat* i = stats; i < stats + 6; i++) result.push_back(*i);
	return result;
}

int Parent::getId()
{
	return id;
}

Stat Parent::getStat(eStat stat)
{
	Stat result = Stat();
	for (int i = 0; i < 6; i++) {
		if (stats[i].getStat() == stat) {
			result = stats[i];
			break;
		}
	}
	return result;
}

unsigned char Parent::getStatValue(eStat stat)
{
	return getStat(stat).getValue();
}

std::vector<Stat> Parent::getMaxStats()
{
	std::vector<Stat> result;
	for (int i = 0; i < 6; i++)
	{
		Stat stat = stats[i];
		if (stat.isMax()) result.push_back(stat);
	}
	return result;
}

void Parent::resetId()
{
	latestId = 0;
}

bool Parent::operator==(Parent parent)
{
	return (this->id == parent.getId());
}

bool Parent::operator!=(Parent parent)
{
	return (this->id != parent.getId());
}
