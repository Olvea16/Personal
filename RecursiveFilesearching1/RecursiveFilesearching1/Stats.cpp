#include "Stats.h"
#include <fstream>
#include <limits.h>
#include <cstdint>

using namespace fs;

Stats::Stats()
{
}

Stats::Stats(vector<path> paths) : paths(paths)
{
	count_numbers();
}


Stats::~Stats()
{
}

int Stats::occurences(int number)
{
	if (numbers.find(number) != numbers.end()) return numbers[number];
	else return 0;
}

int Stats::mostFrequent()
{
	pair<int,int> most_frequent = pair<int,int>(0,0);
	for (auto num : numbers) {
		if (num.second > most_frequent.second) {
			most_frequent.first = num.first;
			most_frequent.second = num.second;
		}
	}

	return most_frequent.first;
}

int Stats::leastFrequent()
{
	pair<int, int> least_frequent = pair<int, int>(0, INT_MAX);
	for (auto num : numbers) {
		if (num.second < least_frequent.second) {
			least_frequent.first = num.first;
			least_frequent.second = num.second;
		}
	}
	return least_frequent.first;
}

vector<fs::path> Stats::byTotals()
{
	vector<pair<path, intmax_t>> path_totals;
	vector<path> result;

	for (int i = 0; i < paths.size(); i++) {
		path p = paths[i];

		path_totals.push_back(pair<path, int>(p, 0));

		fstream file_stream;
		file_stream.open(p, iostream::in);

		string line;

		while (!file_stream.eof()) {
			getline(file_stream, line);

			string number_string;

			for (int j = 0; j < line.length(); j++) {
				if (line[j] == ',') {
					path_totals[i].second += stoi(number_string);
					number_string = "";
				}
				else number_string += line[j];
			}
		}
		file_stream.close();
	}

	while (path_totals.size() > 0) {
		pair<int, int> amount = pair<int, intmax_t>(0, path_totals[0].second);
		for (int i = 1; i < path_totals.size(); i++) {
			if (path_totals[i].second < amount.second) {
				amount.first = i;
				amount.second = path_totals[i].second;
			}
		}
		result.push_back(path_totals[amount.first].first);
		path_totals.erase(path_totals.begin() + amount.first);
	}
	return result;
}

void Stats::count_numbers()
{
	for (int i = 0; i < paths.size(); i++) {
		path p = paths[i];

		fstream file_stream;
		file_stream.open(p, iostream::in);

		string line;

		while (!file_stream.eof()) {
			getline(file_stream, line);

			string number_string;

			for (int j = 0; j < line.length(); j++) {
				if (line[j] == ',') {
					int number = stoi(number_string);
					if (numbers.find(number) != numbers.end()) numbers[number] += 1;
					else numbers[number] = 1;
					number_string = "";
				}
				else number_string += line[j];
			}
		}
		file_stream.close();
	}
}
