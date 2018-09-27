#pragma once
#include <string>

using namespace std;

class EMA
{
public:
	EMA();
	EMA(string);
	~EMA();
	string getEMA(); // for test purposes
	void setEMA(string); // for test purposes
	bool isValid(); // essential method
private:
	int snabelA(); // returns position of '@'; if not present or more
				   // than one, -1 is returned
	bool dot(); // returns true if a '.' is at least 2 pos. after '@' and only one
				// ‘.’ in emaidAddress; otherwise false
	bool checkLengths(); // local max 64; domain max 255; precond.: snabelA() does not
						 // return -1.
	bool checkChars(); // legal characters a-z; A-Z; 0-9; .; @; %; & (; is NOT a legal
					   // character)
	string emailAddress;
};

