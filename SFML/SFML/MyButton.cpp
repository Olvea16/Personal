#include "MyButton.h"

using namespace sf;

MyButton::MyButton(sf::Texture* normal, sf::Texture* clicked, std::string words, sf::Vector2f location) {
	MyButton::normal.setTexture(*normal);
	MyButton::clicked.setTexture(*clicked);
	MyButton::currentSpr = &this->normal;
	current = false;
	MyButton::normal.setPosition(location);
	MyButton::clicked.setPosition(location);
	text.setString(words);
	text.setPosition(location.x + 3, location.y + 3);
	text.setCharacterSize(14);
}
bool MyButton::checkClick(sf::Vector2f mousePos) {
	if (mousePos.x>currentSpr->getPosition().x && mousePos.x<(currentSpr->getPosition().x + currentSpr->getLocalBounds().width)) {
		if (mousePos.y>currentSpr->getPosition().y && mousePos.y<(currentSpr->getPosition().y + currentSpr->getLocalBounds().height)) {
			setState(true);
			return true;
		}
	}
	setState(false);
	return false;
}
void MyButton::setState(bool which) {
	current = which;
	if (current) {
		currentSpr = &clicked;
		return;
	}
	currentSpr = &normal;
}
void MyButton::setText(std::string words) {
	text.setString(words);
}
bool MyButton::getVar() {
	return current;
}
sf::Sprite* MyButton::getSprite() {
	return currentSpr;
}

sf::Text * MyButton::getText() {
	return &text;
}