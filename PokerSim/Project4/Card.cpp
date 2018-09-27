#include "Card.h"

Card::Card()
{
}

Card::Card(suits suit, int value) : suit(suit), value(value)
{
}

Card::~Card()
{
}

suits Card::getSuit()
{
	return suit;
}

int Card::getValue()
{
	return value;
}