#pragma once
#include "Stat.h"
#include "Pokemon.h"
#include <vector>

class Parent
{
public:
	// Constructor / Destructor
	Parent();
	Parent(Pokemon pokemon, char hp = 1, char attack = 1, char defense = 1, char spattack = 1, char spdefense = 1, char speed = 1, std::string nature = "", std::string ability = "", std::string item = "none");
	Parent(Pokemon pokemon, char hp, char attack, char defense, char spattack, char spdefense, char speed, std::string nature, std::string ability, std::string item, int id);
	~Parent();

	// Set
	void setItem(std::string item);

	// Get
	Pokemon getPokemon();
	std::string getItem();
	std::string getNature();
	std::vector<Stat> getStats();
	int getId();
	Stat getStat(eStat stat);
	unsigned char getStatValue(eStat stat);

	// Methods
	std::vector<Stat> getMaxStats();
	void resetId();

	// Operators
	bool operator==(Parent parent);
	bool operator!=(Parent parent);

	static int latestId;

protected:
	Stat stats[6];
	std::string nature;
	std::string ability;

private:
	Pokemon pokemon;
	std::string item;
	int id;
};

