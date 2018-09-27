#pragma once

#include "Position.h"

#define _USE_MATH_DEFINES

#include <math.h>

class Transformation
{
public:
	Transformation(double x, double y, double angle);
	~Transformation();

	Position getTransformation(Position currentPos);

private:
	double x, y, angle;
};

