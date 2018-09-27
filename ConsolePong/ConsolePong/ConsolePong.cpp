// INCLUDES
#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <ctime>
#include <iomanip>

// DEFINES
#define VK_S 0x53
#define VK_W 0x57
#define VK_P 0x50

// NAMESPACES
using namespace std;

// CONSTANTS
const int mapHeight = 16;
const int mapWidth = 50;
const int playerHeight = 5;
const int spaces_per_tab = 8;
const double ballSpeedFactor = 0.999;

double ballUpdateTime = 500.0;

const bool debug = false; // DEBUG MODE!

// VARIABLES
bool paused = false;
bool screen_changed = false;
clock_t ticks;

// ENUMERABLES
enum DirectionX{ dirLeft = -1, dirRight = 1 };
enum DirectionY { dirUp = -1, dirStraight = 0, dirDown = 1 };
enum Command { p1Up, p1Down, p2Up, p2Down, Pause };
enum Object { P1, P2, Ball };


// DATA STRUCTURES
struct Position 
{
	int x;
	int y;
};

struct Direction
{
	DirectionX x;
	DirectionY y;
};

const pair<int, Command> Commands[5] = 
								{	pair<int, Command>(VK_W, p1Up), 
									pair<int, Command>(VK_S, p1Down),
									pair<int, Command>(VK_UP, p2Up),
									pair<int, Command>(VK_DOWN, p2Down),
									pair<int, Command>(VK_P, Pause)	 };

// FUNCTIONS
void senseStuff(vector<Command>* commandBuffer, map<Command, bool>* pressedStatus)
{
	for each (pair<int, Command> p in Commands)
	{
		if (GetAsyncKeyState(p.first) != 0) {
			if (!pressedStatus->at(p.second)) {
				pressedStatus->at(p.second) = true;
				commandBuffer->push_back(p.second);
			}
		}
		else pressedStatus->at(p.second) = false;
	}
}

// Returns potential colliding object.
Object containsPaddle(Position p1Pos, Position p2Pos, Position targetPos) {
	if (p1Pos.x == targetPos.x && targetPos.y >= p1Pos.y && targetPos.y < p1Pos.y + playerHeight) return P1;
	if (p2Pos.x == targetPos.x && targetPos.y >= p2Pos.y && targetPos.y < p2Pos.y + playerHeight) return P2;
	return Ball;
 }

DirectionX reverseDirection(DirectionX direction) {
	if (direction == dirLeft) return dirRight;
	return dirLeft;
}

DirectionY reverseDirection(DirectionY direction) {
	if (direction == dirUp) return dirDown;
	if (direction == dirDown) return dirUp;
	return dirStraight;
}

void calculateStuff(Position* p1Pos, Position* p2Pos, Position* ballPos, Direction* ballDir, vector<Command>* commandBuffer)
{
	if (!paused) {
		while (commandBuffer->size() != 0)
		{
			Command c = commandBuffer->back();
			commandBuffer->pop_back();
			switch (c)
			{
			case p1Up:
				if (p1Pos->y != 0) p1Pos->y--;
				screen_changed = true;
				break;

			case p1Down:
				if (p1Pos->y != mapHeight - playerHeight) p1Pos->y++;
				screen_changed = true;
				break;

			case p2Up:
				if (p2Pos->y != 0) p2Pos->y--;
				screen_changed = true;
				break;

			case p2Down:
				if (p2Pos->y != mapHeight - playerHeight) p2Pos->y++;
				screen_changed = true;
				break;

			case Pause:
				paused = !paused;
				break;
			}
		}
		clock_t currentTime = (1000 * clock()) / CLOCKS_PER_SEC;
		int udt = round(ballUpdateTime);
		if (currentTime - (currentTime % udt) != ticks - (ticks % udt)) {
			ballUpdateTime *= ballSpeedFactor;
			Position targetPos = *ballPos;
			targetPos.x += ballDir->x;
			targetPos.y += ballDir->y;
			if (targetPos.y == -1) {
				ballDir->y = dirDown;
				targetPos.y = 1;
			}
			if (targetPos.y == mapHeight) {
				ballDir->y = dirUp;
				targetPos.y = mapHeight - 2;
			}
			Object collidingObject = containsPaddle(*p1Pos, *p2Pos, targetPos);
			if (collidingObject != Ball) {
				ballDir->x = reverseDirection(ballDir->x);
				targetPos.x += 2 * ballDir->x;
			}
			if (targetPos.x == -1 || targetPos.x == mapWidth) {
				targetPos.x = mapWidth / 2;
				targetPos.y = mapHeight / 2;
			}
			*ballPos = targetPos;
			screen_changed = true;
		}
		ticks = currentTime;
	}
	if (paused) {
		while (commandBuffer->size() != 0)
		{
			Command c = commandBuffer->back();
			commandBuffer->pop_back();
			switch (c)
			{
			case Pause:
				paused = !paused;
				break;
			}
		}
	}
}

void drawCharacter(char character, int amount) {
	for (int i = 0; i < amount; i++) cout << character;
}

void printSpaces(int first_character, int target_character) {
	int last_character = target_character - 1;
	
	int first_char_tabs = (first_character - (first_character % spaces_per_tab)) / spaces_per_tab;
	int last_char_tabs = (target_character - (target_character % spaces_per_tab)) / spaces_per_tab;

	int tabs = last_char_tabs - first_char_tabs;
	int spaces;
	if (first_char_tabs == last_char_tabs) spaces = (target_character - first_character) % spaces_per_tab;
	else spaces = target_character % spaces_per_tab;

	drawCharacter('\t', tabs);
	drawCharacter(' ', spaces);
}

vector<Object> containsDrawable(int line, Position p1Pos, Position p2Pos, Position ballPos) {
	vector<Object> needsDrawing;
	if (ballPos.x <= p1Pos.x) if (line == ballPos.y) needsDrawing.push_back(Ball);
	if (ballPos.x != p1Pos.x) if (line >= p1Pos.y && line < p1Pos.y + playerHeight) needsDrawing.push_back(P1);
	if (ballPos.x > p1Pos.x && ballPos.x <= p2Pos.x) if (line == ballPos.y) needsDrawing.push_back(Ball);
	if (ballPos.x != p2Pos.x) if (line >= p2Pos.y && line < p2Pos.y + playerHeight) needsDrawing.push_back(P2);
	if (ballPos.x > p2Pos.x) if (line == ballPos.y)  needsDrawing.push_back(Ball);
	return needsDrawing;
}

void drawLine(int line, Position p1Pos, Position p2Pos, Position ballPos) {
	int currentChar = 0;
	vector<Object> needsDrawing = containsDrawable(line, p1Pos, p2Pos, ballPos);
	for each (Object o in needsDrawing) {
		switch (o) {
		case P1:
			printSpaces(currentChar, p1Pos.x);
			cout << '|';
			currentChar = p1Pos.x + 1;
			break;

		case P2:
			printSpaces(currentChar, p2Pos.x);
			cout << '|';
			currentChar = p2Pos.x + 1;
			break;

		case Ball:
			printSpaces(currentChar, ballPos.x);
			cout << 'o';
			currentChar = ballPos.x + 1;
			break;
		}
	}
	cout << endl;
}

void drawStuff(Position p1Pos, Position p2Pos, Position ballPos)
{
	system("cls");
	drawCharacter('-', mapWidth);
	cout << endl;
	for (int i = 0; i < mapHeight; i++) {
		drawLine(i, p1Pos, p2Pos, ballPos);
	}
	drawCharacter('-', mapWidth);
	cout << endl;
	cout << ballPos.x;
}

// MAIN
int main()
{
	ios::sync_with_stdio(false);
	map<Command, bool> pressedStatus = { {p1Up,false},{p1Down,false},{p2Up,false},{p2Down,false},{Pause,false} };
	
	vector<Command> commandBuffer;

	Position p1Pos;
	p1Pos.x = 4;
	p1Pos.y = (mapHeight - playerHeight) / 2;

	Position p2Pos;
	p2Pos.x = mapWidth - 4;
	p2Pos.y = (mapHeight - playerHeight) / 2;

	Position ballPos;
	ballPos.x = mapWidth / 2;
	ballPos.y = mapHeight / 2;

	Direction ballDir;
	ballDir.x = dirRight;
	ballDir.y = dirUp;

	bool finished = false;

	//SUPERLOOP
	while (!finished) {
		senseStuff(&commandBuffer, &pressedStatus);
		calculateStuff(&p1Pos, &p2Pos, &ballPos, &ballDir, &commandBuffer);
		if (screen_changed) drawStuff(p1Pos, p2Pos, ballPos);
		screen_changed = false;
	}

    return 0;
}