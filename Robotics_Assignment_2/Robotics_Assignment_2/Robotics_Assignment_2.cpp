// Robotics_Assignment_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Transformation.h"

int main()
{
	Position pR(0, 0, 0);

	Transformation transformation(1, 1, -M_PI_2);
	pR = transformation.getTransformation(pR);
	pR = transformation.getTransformation(pR);

    return 0;
}

