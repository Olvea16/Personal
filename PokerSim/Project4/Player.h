#pragma once

#include <vector>

#include "Card.h"

class Player
{
public:
	Player(std::string name);
	~Player();

	void setCards(Card* cards);

	std::vector<Card> getCards();

private:
	Card cards[2];
	std::string name;
};

