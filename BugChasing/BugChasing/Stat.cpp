#include "stdafx.h"
#include "Stat.h"


Stat::Stat()
{
}


Stat::~Stat()
{
}

bool Stat::isFinished()
{
	return finished;
}

void Stat::isFinished(bool state)
{
	finished = state;
}

unsigned int Stat::getSteps()
{
	return steps;
}

void Stat::addSteps(int steps)
{
	this->steps += steps;
}
