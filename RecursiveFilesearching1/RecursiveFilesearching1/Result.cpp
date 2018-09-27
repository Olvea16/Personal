#include "Result.h"

Result::Result()
{
}

Result::Result(fs::path path, int number) : path(path), number(number)
{
}

Result::~Result()
{
}

bool Result::operator==(Result B)
{
	return equals(B);
}

bool Result::operator!=(Result B)
{
	return !equals(B);
}

bool Result::equals(Result B)
{
	return (path == B.path && number == B.number);
}
