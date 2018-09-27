// ConsoleApplication8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <math.h>
#include <string>
#include <deque>
#include <filesystem>

using namespace std;

int state = 0;
int sleepyTime = 100;
int progress = 0;
string text = "";
const string line = "------------------";

string message;
const int messageAmount = 8;

pair<int, string> messages[] = {	{ 0 ,"Fetching stuff online: "},
									{ 0 ,"- Connecting to server." },
									{ 2 ,"- Authenticating." },
									{ 12,"- Downloading." },
									{ 27,"Unpacking fetched content."},
									{ 33,"Installing." },
									{ 33,"- Path A." },
									{ 41,"- Path B." },
									{ 50,"- Path C." },
									{ 67,"- ." },
									{ 85,"Finalizing." },
									{ 87,"- Setting up user settings." },
									{ 90,"- Mining bitcoin." },
									{ 95,"- Installing russian spyware." },
									{ 97,"- Bypassing main firewall." } };

const double maxBarLength = 20.0;
float progressChance = 0.3;
const int maxProgress = 100;
void resetConsole();
string newMessage();

int main()
{
	srand(time(NULL));

	bool finished = false;
	message = newMessage();

	while (!finished) {
		if (rand() <= RAND_MAX * progressChance) {
			progress++;
			progressChance *= 0.97;
			if (rand() <= RAND_MAX * 0.001) progress = 0;
			message = newMessage();
		}
		if (progress == maxProgress) finished = true;
		resetConsole();
		Sleep(sleepyTime / progressChance * 0.3);
	}

	cout << "Install completed, thank you for wasting your time!";

	string a;
	cin >> a;
	
	return 0;
}

void resetConsole() {
	int barLength = floor(maxBarLength * progress / maxProgress);
	string bar = "";
	system("cls");
	if (barLength == maxBarLength) {
		barLength = 0;
		bar = "";
		for (int i = 0; i < maxBarLength; i++) bar += ' ';
	}
	else {
		for (int i = 0; i < barLength; i++) bar += '=';
		switch (++state) {
		case(1):
			bar += '|';
			break;

		case(2):
			bar += '/';
			break;

		case(3):
			bar += '-';
			break;

		default:
			bar += '\\';
			state = 0;
			break;
		}
		for (int i = 0; i < maxBarLength - barLength; i++) bar += ' ';
	}
	text = '[' + bar + "][" + to_string((int)(((double)progress)/((double)maxProgress) * 100.0)) + "%]";
	cout << "Installing:" << endl << text << endl << line	<< endl << message;
}

string newMessage() {
	string message = "";
	deque<string> messageVector;
	for each (pair<int,string> p in messages)
	{
		if (progress >= p.first) {
			messageVector.push_back(p.second);
			while (messageVector.size() > messageAmount) messageVector.pop_front();
		}
	}
	for each (string s in messageVector) message += s + '\n';
	return message;
}