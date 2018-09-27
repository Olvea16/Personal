#pragma once
#include <string>
#include <experimental/filesystem>

#define UNDEFINED_RESULT Result("",-1)

using namespace std;
namespace fs = std::experimental::filesystem::v1;
using namespace fs;

class Result
{
public:
	Result();
	Result(path path, int number);
	~Result();

	bool operator==(Result B);
	bool operator!=(Result B);

	/**
	* The file Path of this result
	* @return file Path of this result
	*/
	path path;
	int number;

private:
	bool equals(Result B);
};

