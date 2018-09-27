#pragma once

#include <string>

enum suits { spades, hearts, diamonds, clubs };

class Card
{
public:
	Card();
	Card(suits suit, int value);
	~Card();

	suits getSuit();
	int getValue();

private:
	suits suit;
	int value;

};

