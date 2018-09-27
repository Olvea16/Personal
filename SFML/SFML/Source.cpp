#include "FFT.h"
#include "MyButton.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>

using namespace std;
using namespace sf;

const int arrayWidth = 128;
const int arrayHeight = 64;
const int cellSize = 8;
const int toolbarHeight = 40;
const int menuHeight = 31;
const int menuWidth = 8;
bool mouseDown;

int main()
{
	int windowWidth = arrayWidth * cellSize;
	int windowHeight = arrayHeight * cellSize + toolbarHeight;

	RenderWindow window;
	window.create(VideoMode(windowWidth, windowHeight), "My first sfml game");

	Mouse mouse;

	Texture clearClicked;
	clearClicked.loadFromFile("E:/buttonClicked.BMP",IntRect(Vector2<int>(0,0), Vector2<int>(109, 34)));
	Texture clearNormal;
	clearNormal.loadFromFile("E:/buttonNormal.BMP", IntRect(Vector2<int>(0, 0), Vector2<int>(109, 34)));

	MyButton clear(&clearNormal, &clearClicked,"Clear",Vector2f(-2,2));

	vector<RectangleShape> rectangleVector(arrayHeight*arrayWidth);
	for (int y = 0; y < arrayHeight; y++) {
	for (int x = 0; x < arrayWidth; x++) {
		rectangleVector[y * arrayWidth + x].setSize(Vector2f(cellSize, cellSize));
		rectangleVector[y * arrayWidth + x].setPosition(Vector2f(x * cellSize, y * cellSize + toolbarHeight));
		rectangleVector[y * arrayWidth + x].setFillColor(Color::White);
	}}

	while (window.isOpen())
	{
		int mouseX = (mouse.getPosition().x - window.getPosition().x - menuWidth);
		int mouseY = (mouse.getPosition().y - window.getPosition().y - menuHeight);

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
				case Event::Closed:
					window.close();
					break;

				case Event::MouseButtonPressed:
					if (mouseX >= 0 && mouseX < windowWidth) {
						if (clear.checkClick(Vector2f(mouseX, mouseY)));
						if (mouseY >= toolbarHeight && mouseY < windowHeight) rectangleVector[(mouseY - toolbarHeight) / cellSize * arrayWidth + mouseX / cellSize].setFillColor(Color::Black);

					}
					mouseDown = true;
					break;

				case Event::MouseButtonReleased:
					mouseDown = false;
					break;

				case Event::MouseMoved:
					if (mouseDown) {
						if (mouseX >= 0 && mouseX < windowWidth) {
							if (mouseY >= toolbarHeight && mouseY < windowHeight) {
								rectangleVector[(mouseY - toolbarHeight) / cellSize * arrayWidth + mouseX / cellSize].setFillColor(Color::Black);
							}
							else {

							}
						}
					}
					break;
			}			
		}

		window.clear(Color(210,230,210));

		for (int y = 0; y < arrayHeight; y++) {
		for (int x = 0; x < arrayWidth; x++) {
			window.draw(rectangleVector[y * arrayWidth + x]);
		}}
		window.draw(*clear.getSprite());
		window.draw(*clear.getText());

		window.display();
	}

	return 0;
}