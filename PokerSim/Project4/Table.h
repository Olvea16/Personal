#pragma once


#include "Player.h"

class Table
{
public:
	Table();
	~Table();

	void addPlayer(std::string name);
	void resetDeck();
	void deal();

private:
	std::vector<Player> players;
	std::vector<Card> cards;
	std::vector<Card> deck;
	Card 
};

