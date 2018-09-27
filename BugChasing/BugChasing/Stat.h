#pragma once
class Stat
{
public:
	Stat();
	~Stat();

	bool isFinished();
	void isFinished(bool state);

	unsigned int getSteps();
	void addSteps(int steps = 1);

private:
	bool finished = false;
	size_t steps = 0;
};

