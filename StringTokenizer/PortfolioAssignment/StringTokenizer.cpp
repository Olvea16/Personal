#include "stdafx.h"
#include "StringTokenizer.h"

StringTokenizer::StringTokenizer(string inText) {
	indeks = 0;
	tekst = inText;
	delim = " .,-:;?!";
}

StringTokenizer::StringTokenizer(string inText, string inDelim) {
	StringTokenizer::StringTokenizer(inText);
	delim = inDelim;
}

StringTokenizer::~StringTokenizer() {}

string StringTokenizer::nextToken() {
	if (hasMoreTokens()) {
		string token = "";
		while (!isDelimiter(tekst[indeks])) token += tekst[indeks++];
		while (isDelimiter(tekst[indeks++]));
		indeks--;
		return token;
	}
	else return "";	
}

string StringTokenizer::nextToken(string inDelim) {
	delim = inDelim;
	return nextToken();
}

int StringTokenizer::countAllTokens() {
	int tokenCount = 0;
	bool previousWasDelim = true;
	for (int i = 0; i < tekst.length(); i++) {
		if (previousWasDelim && !(isDelimiter(tekst[i]))) tokenCount++;
		previousWasDelim = isDelimiter(tekst[i]);
	}
	return tokenCount;
}

int StringTokenizer::countAllDelimiters() {
	int delimCount = 0;
	for (int i = 0; i < tekst.length(); i++) {
		if (isDelimiter(tekst[i])) delimCount++;
	}
	return delimCount;
}

bool StringTokenizer::contains(string text) {
	int tempIndeks = indeks;
	indeks = 0;
	for (int i = 0; i < countAllTokens(); i++) {
		if (text == nextToken()) {
			indeks = tempIndeks;
			return true;
		}
	}
	indeks = tempIndeks;
	return false;
}

bool StringTokenizer::superfluousDel() {
	return !(countAllDelimiters() < countAllTokens());
}

void StringTokenizer::trim() {
	bool previousWasDelimiter = true;
	for (int i = 0; i < tekst.length(); i++) {
		if (isDelimiter(tekst[i])) {
			if (previousWasDelimiter) {
				for (int j = i; j < tekst.length() - 1; j++) {
					tekst[j] = tekst[j + 1];
				}
				tekst.resize(tekst.length() - 1);
				i--;
			}
			else previousWasDelimiter = true;
		}
		else previousWasDelimiter = false;
	}
}

void StringTokenizer::printContents() {
	cout << tekst << endl;
}

bool StringTokenizer::isDelimiter(char character) {
	return delim.find(character) != string::npos;
}

bool StringTokenizer::hasMoreTokens() {
	bool previousWasDelim = false;
	for (int i = indeks; i < tekst.length(); i++) {
		if (previousWasDelim && !(isDelimiter(tekst[i]))) return true;
		previousWasDelim = isDelimiter(tekst[i]);
	}
	return false;
}