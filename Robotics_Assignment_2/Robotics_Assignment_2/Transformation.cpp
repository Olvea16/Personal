#include "stdafx.h"
#include "Transformation.h"


Transformation::Transformation(double x, double y, double angle) : x(x), y(y), angle(angle)
{ 

}

Transformation::~Transformation()
{
}

Position Transformation::getTransformation(Position currentPos)
{
	Position result;
	result.x = x + currentPos.x * cos(angle) + currentPos.y * (-sin(angle));
	result.y = y + currentPos.x * sin(angle) + currentPos.y * cos(angle);
	result.angle = currentPos.angle + angle;
	if (result.angle < 0) result.angle += 2 * M_PI;
	if (result.angle > 2 * M_PI) result.angle -= 2 * M_PI;
	return result;
}
