#pragma once

#include <string>

enum eStat {
	ehp, eatk, edef, esatk, esdef, espd
};

class Stat
{
public:
	// Constructor / Destructor
	Stat();
	Stat(eStat stat, char value);
	~Stat();

	// Set
	void setStat(eStat stat);
	void setValue(char value);

	// Get
	eStat getStat();
	char getValue();

	// Public methods
	std::string getStatName();
	static std::string getStatName(eStat stat);
	std::string getStatNameShort();
	static std::string getStatNameShort(eStat stat);
	bool isMax();

private:
	eStat stat;
	signed char value;
};

