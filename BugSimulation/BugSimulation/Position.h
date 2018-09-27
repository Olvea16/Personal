#pragma once
template <typename T>
class Position
{
public:
	Position() {}
	Position(T x, T y) : x(x), y(y)
	{

	}
	~Position() {}

	Position operator+(Position pos) {
		return Position(pos.x + x, pos.y + y);
	}

	Position operator-(Position pos) {
		return Position(x - pos.x, y - pos.y);
	}

	void operator+=(Position pos) {
		*this = *this + pos;
	}

	void operator-=(Position pos) {
		*this = *this - pos;
	}

	bool operator==(Position pos) {
		return (this->x == pos.x && this->y == pos.y);
	}

	double length() {
		return sqrt(pow((double)(this->x), 2) + pow((double)(this->y), 2));
	}

	T x;
	T y;

private:
};

