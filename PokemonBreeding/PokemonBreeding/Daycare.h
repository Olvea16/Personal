#pragma once
#include "Parent.h"
#include "Target.h"

#include <vector>

#include "tinyxml2.h"

class Daycare
{
public:
	Daycare();
	~Daycare();

	// Methods
	void registerPokemon(Pokemon pokemon);
	void registerParent(Parent parent);
	void deletePokemon(int index);
	void newTarget(int hp, int attack, int defense, int spattack, int spdefense, int speed, std::string nature = "", std::string ability = "");
	void insert(Parent pokemon, unsigned char slot);
	void insert(int index, unsigned char slot);
	bool isInserted(Parent* pokemon);

	//File manipulation methods
	bool selectFile(const char* filename);
	bool createPokemon(Pokemon pokemon);
	bool createParent(Parent parent);


	// Print methods
	void printPokemon(Parent* pokemon);
	void printSlots();
	void printOffspring();
	void printTargetProbabilities();
	void printBox();
	void printStorage();

private:
	int getInheritedIvs();
	std::string toString(double number, int decimals, char delimiter = '.');
	bool setFromElement(int* result, tinyxml2::XMLElement* element);
	bool setFromElement(std::string* result, tinyxml2::XMLElement* element);

	Parent slots[2];
	std::vector<Pokemon> validPokemon;
	std::vector<Parent> pokebox;
	Target target;

	tinyxml2::XMLDocument doc;
};

