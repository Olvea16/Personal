#include <time.h>

#include "Table.h"

Table::Table()
{
	srand(time(NULL));
	resetDeck();
}

Table::~Table()
{
}

void Table::addPlayer(std::string name)
{
	Player player(name);
	players.push_back(player);
}

void Table::resetDeck()
{
	for (int suit = 0; suit < 4; suit++) {
		for (int value = 0; value < 13; value++) {
			Card card((suits)suit, value + 1);
			deck.push_back(card);
		}
	}
}

void Table::deal()
{
	for (int i = 0; i < players.size(); i++) {
		Card cards[2];

		for (int i = 0; i < 2; i++) {
			int index = rand() % deck.size();
			cards[i] = deck[index];
			deck.erase(deck.begin() + index);
		}

		players[i].setCards(cards);
	}
}
