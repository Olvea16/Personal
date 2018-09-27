#pragma once
class Position
{
public:
	Position();
	Position(double x, double y, double angle);
	~Position();

public:
	double x, y, angle;
};

