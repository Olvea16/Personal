#pragma once

#include "Role.h"

class Player
{
public:
	Player();
	Player(int number, std::string name = "") : name(name), number(number) { }
	~Player();

	std::string name;
	int number;
};

