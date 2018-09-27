#include "stdafx.h"

#include "Daycare.h"
#include "Config.h"

#include <istream>
#include <iostream>
#include <math.h>
#include <string.h>

void printElementRecursively(tinyxml2::XMLElement* ele, int depth);

Daycare::Daycare()
{
}

Daycare::~Daycare()
{
}

void Daycare::registerPokemon(Pokemon pokemon)
{
}

void Daycare::registerParent(Parent parent)
{
	bool alreadyExists = false;
	for (int i = 0; i < pokebox.size(); i++) alreadyExists |= pokebox[i] == parent;
	if (!alreadyExists) {
		pokebox.push_back(parent);
	}
}

void Daycare::deletePokemon(int index)
{
	pokebox.erase(pokebox.begin() + index);
}

void Daycare::newTarget(int hp, int attack, int defense, int spattack, int spdefense, 
	int speed, std::string nature, std::string ability)
{
	target = Target(hp, attack, defense, spattack, spdefense, speed, nature, ability);
}

void Daycare::insert(Parent pokemon, unsigned char slot)
{
	registerParent(pokemon);
	if (slot >= 0 && slot < 2) slots[slot] = pokemon;
}

void Daycare::insert(int index, unsigned char slot)
{
	if (slot >= 0 && slot < 2) slots[slot] = pokebox[index];	
}

bool Daycare::isInserted(Parent * pokemon)
{
	return ((*pokemon == slots[0]) || (*pokemon == slots[1]));
}

bool Daycare::selectFile(const char * filename)
{
	if (doc.LoadFile(filename) == tinyxml2::XML_SUCCESS) {
		std::cout << "Loaded " << filename << "." << std::endl;

		tinyxml2::XMLElement* root = doc.FirstChildElement();
		tinyxml2::XMLElement* pokemonElement = root->FirstChildElement();

		int latestId = 0;

		while (pokemonElement != NULL) {
			int abilities = 2;
			std::string hiddenAbility = "";

			setFromElement(&abilities, pokemonElement->FirstChildElement("abilities"));
			setFromElement(&hiddenAbility, pokemonElement->FirstChildElement("hiddenAbility"));

			Pokemon pokemon((std::string)pokemonElement->Value(), abilities, hiddenAbility);
			if (DEBUG_MODE) std::cout << "Loaded pokemon " << pokemon.getPokemon() << '.' << std::endl;

			validPokemon.push_back(pokemon);

			tinyxml2::XMLElement* parentElement = pokemonElement->FirstChildElement("parents")->FirstChildElement();
			while (parentElement != NULL) {
				int stats[6] = { 1,1,1,1,1,1 };
				std::string nature = "";
				std::string ability = "";
				std::string item = "";
				int id = 0;

				const char* statNames[6] = { "hp","attack","defense","spattack","spdefense","speed" };

				for (int i = 0; i < 6; i++) setFromElement(&stats[i], parentElement->FirstChildElement(statNames[i]));

				setFromElement(&nature, parentElement->FirstChildElement("nature"));
				setFromElement(&ability, parentElement->FirstChildElement("ability"));
				setFromElement(&item, parentElement->FirstChildElement("item"));
				setFromElement(&id, parentElement->FirstChildElement("id"));

				Parent parent(pokemon, stats[0], stats[1], stats[2], stats[3], stats[4], stats[5], nature, ability, item, id);
				if (DEBUG_MODE) std::cout << "Loaded parent " << parent.getPokemon().getPokemon() << " (id " << parent.getId() << ').' << std::endl;

				if (id >= latestId) latestId = id + 1;

				pokebox.push_back(parent);

				parentElement = parentElement->NextSiblingElement();
			}
			pokemonElement = pokemonElement->NextSiblingElement();
		}
		Parent::latestId = latestId;

		return true;
	}
	std::cout << "Couldn't load file." << std::endl;
	return false;
}

void Daycare::printPokemon(Parent* pokemon)
{
	std::string pokeName = pokemon->getPokemon().getPokemon();
	std::vector<Stat> stats = pokemon->getStats();
	int pokeId = pokemon->getId();

	std::cout << pokeId << " - " << pokeName << ": " << std::endl;
	for (std::vector<Stat>::iterator j = stats.begin(); j < stats.end(); j++) 
		std::cout << j->getStatNameShort() << " - " << toString(j->getValue(), 0) << std::endl;
	std::cout << std::endl;
}

void Daycare::printSlots()
{
	for (int i = 0; i < 2; i++) {
		std::cout << "Slot " << toString(i + 1, 0) << ": " << std::endl;
		printPokemon(&slots[i]);
	}
}

void Daycare::printOffspring()
{
	int inheritedIvs = getInheritedIvs();

	std::cout << "Stats: " << std::endl;

	for (int statIndex = 0; statIndex < 6; statIndex++) {
		unsigned char statValue[2];
		eStat stat = (eStat)((int)ehp + statIndex);
		for (int i = 0; i < 2; i++) statValue[i] = slots[i].getStatValue(stat);

		std::cout << Stat::getStatNameShort(stat) << ": ";

		if (statValue[0] == statValue[1]) {
			std::cout << (int)statValue[0] << " (" << round(float(inheritedIvs) / float(6) * 100) << "%), ";
			std::cout << "Rnd (" << round(float(6 - inheritedIvs) / 6 * 100) << "%)" << std::endl;
		}
		else {
			std::cout << (int)statValue[0] << " (" << round(0.5 * float(inheritedIvs) / float(6) * 100) << "%), ";
			std::cout << (int)statValue[1] << " (" << round(0.5 * float(inheritedIvs) / float(6) * 100) << "%), ";
			std::cout << "Rnd (" << round(float(6 - inheritedIvs) / 6 * 100) << "%)" << std::endl;
		}
	}

	std::cout << std::endl << "Nature:" << std::endl;
	std::vector<std::string> inheritedNature;
	for (int i = 0; i < 2; i++) if (slots[i].getItem() == "Everstone") inheritedNature.push_back(slots[i].getNature());
	switch (inheritedNature.size()) {
	case 0:
		std::cout << "Random" << std::endl;
		break;

	case 1:
		std::cout << inheritedNature[0] << std::endl;
		break;

	case 2:
		std::cout << inheritedNature[0] << " (50%), " << inheritedNature[1] << " (50%)" << std::endl;
		break;
	}
}

void Daycare::printTargetProbabilities()
{
	int inheritedIvs = getInheritedIvs();
	std::vector<std::pair<eStat, int>> requirements = target.getRequiredStats();

	float breedingChance = 1;

	// Stats
	for (int i = 0; i < requirements.size(); i++) {
	std::pair<eStat, int> requirement = requirements[i];	
	int parentsWithIvValue = 0;
	for (int i = 0; i < 2; i++) if (slots[i].getStatValue(requirement.first) == requirement.second) parentsWithIvValue++;

	float statChance = (1.0 - (float)inheritedIvs / 6.0) * 1.0 / 32.0 + ((float)inheritedIvs / 6.0) * (float)parentsWithIvValue / 2.0;

	breedingChance *= statChance;

	std::cout << Stat::getStatNameShort(requirement.first) << ": " << ((float)round(statChance * 1000)) / 10 << "%." << std::endl;
	}

	// Nature
	std::string targetNature = target.getNature();

	if (targetNature != "") {
		std::vector<std::string> inheritedNature;
		for (int i = 0; i < 2; i++) if (slots[i].getItem() == "Everstone") inheritedNature.push_back(slots[i].getNature());

		float natureChance = 0;

		switch (inheritedNature.size()) {
		case 0:
			natureChance = 1.0 / 25.0;
			break;


		case 1:
			if (inheritedNature[0] == targetNature) natureChance = 1;
			break;

		case 2:
			for (int i = 0; i < 2; i++) if (inheritedNature[i] == targetNature) natureChance += 0.5;
			break;
		}

		breedingChance *= natureChance;

		std::cout << targetNature << ": " << toString(natureChance * 100,1) << "%." << std::endl;
	}

	std::cout << "Total chance: " << toString(breedingChance * 100, 1) << "%." << std::endl;

	double targetProbability = 0.95;
	int timesForProbability = ceil(log(1-targetProbability)/log(1-breedingChance));
	targetProbability = 1 - pow(1 - breedingChance, timesForProbability);
	
	std::cout << "Attempts (" + toString(targetProbability * 100, 2) + "%): " << toString(timesForProbability, 0) << "." << std::endl << std::endl;
}

void Daycare::printBox()
{
	for (std::vector<Parent>::iterator i = pokebox.begin(); i < pokebox.end(); i++) {
		if (!isInserted(&(*i))) printPokemon(&(*i));
	}
}

void Daycare::printStorage()
{
	using namespace tinyxml2;
	XMLElement* root = doc.FirstChildElement();

	printElementRecursively(root, 0);
}

int Daycare::getInheritedIvs()
{
	int inheritedIvs = 2;
	bool destinyKnotEquipped = false;
	for (int i = 0; i < 2; i++) destinyKnotEquipped |= (slots[i].getItem() == "Destiny Knot");
	if (destinyKnotEquipped) inheritedIvs = 5;

	return inheritedIvs;
}

std::string Daycare::toString(double number, int decimals, char delimiter)
{
	int factor = pow(10, decimals);
	int iNumber = floor(number * factor);
	int integer = iNumber / factor;
	int decimal = iNumber % factor;

	std::string result = std::to_string(integer);
	if (decimals > 0) result += delimiter + std::to_string(decimal);

	return result;
}

bool Daycare::setFromElement(int * result, tinyxml2::XMLElement * element)
{
	std::string sResult;
	if (setFromElement(&sResult, element)) {
		*result = stoi(sResult);
		return true;
	}
	return false;
}

bool Daycare::setFromElement(std::string * result, tinyxml2::XMLElement * element)
{
	if (element == NULL) return false;
	*result = element->GetText();
	return true;
}

void printElementRecursively(tinyxml2::XMLElement* ele, int depth) {
	for (int i = 0; i < depth + 1; i++) std::cout << '-';
	std::cout << ele->Value();
	if (ele->GetText() != (void*)0) std::cout << " " << ele->GetText();
	std::cout << std::endl;


	tinyxml2::XMLElement* pChild = ele->FirstChildElement();
	if (pChild != (void*)0) printElementRecursively(pChild, depth + 1);

	tinyxml2::XMLElement* pSibling = ele->NextSiblingElement();
	if (pSibling != (void*)0) printElementRecursively(pSibling, depth);
}