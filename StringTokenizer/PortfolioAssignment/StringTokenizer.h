#pragma once
#include <string>
#include <iostream>
using namespace std;

class StringTokenizer
{
public:
	StringTokenizer(string tekst);
	StringTokenizer(string tekst, string delim);
	~StringTokenizer(void);

	string nextToken();
	string nextToken(string);
	int countAllTokens();
	int countAllDelimiters();
	bool contains(string);
	bool superfluousDel();
	void trim();
	void printContents();

private:
	bool isDelimiter(char);
	bool hasMoreTokens();
	string tekst;
	string delim;
	int indeks;
};


