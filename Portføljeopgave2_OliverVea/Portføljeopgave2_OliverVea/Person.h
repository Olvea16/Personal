#pragma once
#include <string>

using namespace std;

class Person
{
public:
	Person(string navn);
	~Person();
protected:
	string navn;
};

