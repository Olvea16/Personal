// ADA_Exercises_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CircularQueue.h"
#include <stack>
#include <iostream>


bool balancedParenthesis(std::string s) {
	std::stack<char> stck;

	int i = -1;
	while (s[++i] != '\0') {
		if (s[i] == '(') stck.push(s[i]);
		if (s[i] == ')') {
			if (stck.size() > 0) stck.pop();
			else return false;
		}
	}
	return stck.size() == 0;
}

int main()
{
	bool a = balancedParenthesis("((2x + 3) * (2x + 4))");

	CircularQueue<int> queue(100);
	for (int i = 0; i < 111; i++) 
		queue.enqueue(i);
	for (int i = 0; i < 100; i++) 
		std::cout << queue.dequeue() << std::endl;

    return 0;
}

