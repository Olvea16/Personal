#include "stdafx.h"
#include "Stat.h"


Stat::Stat()
{
}

Stat::Stat(eStat stat, char value) : stat(stat), value(value)
{
}


Stat::~Stat()
{
}

void Stat::setStat(eStat stat)
{
	this->stat = stat;
}

void Stat::setValue(char value)
{
	this->value = value;
}

eStat Stat::getStat()
{
	return stat;
}

char Stat::getValue()
{
	return value;
}

std::string Stat::getStatName()
{
	return getStatName(stat);
}

std::string Stat::getStatName(eStat stat)
{
	switch (stat) {
	case eatk: return "attack";
	case esatk: return "sp. attack";
	case edef: return "defense";
	case esdef: return "sp. defense";
	case ehp: return "hp";
	case espd: return "speed";
	}
}

std::string Stat::getStatNameShort()
{
	return getStatNameShort(stat);
}

std::string Stat::getStatNameShort(eStat stat)
{
	switch (stat) {
	case eatk: return "at";
	case esatk: return "sa";
	case edef: return "de";
	case esdef: return "sd";
	case ehp: return "hp";
	case espd: return "sp";
	}
}

bool Stat::isMax()
{
	return (value == 31);
}
