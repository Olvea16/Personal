#pragma once
#include "Bog.h"

class Eksemplar
{
public:
	Eksemplar(int id, Bog bog);
	Bog getBog();
	bool getLaanestatus();
	void setLaanestatus(bool);
	~Eksemplar();
private:
	bool udlaant;
	int id;
	Bog bog;
};

