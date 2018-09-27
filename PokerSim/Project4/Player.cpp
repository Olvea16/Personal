#include "Player.h"

Player::Player(std::string name) : name(name)
{
}

Player::~Player()
{
}

void Player::setCards(Card * cards)
{
	cards[0] = cards[0];
	cards[1] = cards[1];
}

std::vector<Card> Player::getCards()
{
	std::vector<Card> vCards;
	for (int i = 0; i < 2; i++) vCards.push_back(cards[i]);
	return vCards;
}
