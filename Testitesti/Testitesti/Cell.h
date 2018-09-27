#pragma once
class Cell
{
public:
	Cell();
	~Cell();

	bool isConst();
	bool setConst();
	bool setValue(int val);
	int getValue();

private:
	int value = 0;
	bool constant = false;
};

