#pragma once
#include <experimental/filesystem>
#include <vector>
#include <unordered_map>

using namespace std;
namespace fs = std::experimental::filesystem::v1;

class Stats
{
public:
	Stats();
	Stats(vector<fs::path> paths);
	~Stats();

	/**
	* Returns the number of times that a number was found (across all files).
	*/
	int occurences(int number);

	/**
	* Returns the number that was found the most times (across all files).
	*/
	int mostFrequent();

	/**
	* Returns the number that was found the least times (of course, you should have found it at least once).
	*/
	int leastFrequent();

	/**
	* Returns a list of all the files found in the directory, ordered from the
	* one that contains numbers whose sum across all lines is the smallest
	* (first of the list),
	* to the one that contains numbers whose sum is the greatest (last of the list).
	*/
	vector<fs::path> byTotals();

private:
	vector<fs::path> paths;
	void count_numbers();

	unordered_map<int,int> numbers;
};

