#include "stdafx.h"
#include "Cell.h"


Cell::Cell()
{
	constant = false;
}


Cell::~Cell()
{
}

bool Cell::isConst()
{
	return constant;
}

bool Cell::setConst()
{
	if (!constant) constant = true;
	else return false;
	return true;
}

bool Cell::setValue(int val)
{
	if (!constant) value = val;
	return !constant;
}

int Cell::getValue()
{
	return value;
}
