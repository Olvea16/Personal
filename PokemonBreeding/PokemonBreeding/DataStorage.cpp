#include "stdafx.h"
#include "DataStorage.h"

#include <vector>
#include <unordered_map>
#include <string>

 struct parent {
	char hp;
	char attack;
	char defense;
	char sattack;
	char sdefense;
	char speed;
	std::string nature;
	std::string ability;
	std::string item;
	int id;
};

struct pokemon {
	std::string pokemon;
	int abilities;
	int hiddenAbilities;
	std::string hiddenAbility;
	std::unordered_map<int,parent> a;
};

DataStorage::DataStorage()
{
}


DataStorage::~DataStorage()
{
}