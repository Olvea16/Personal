#include "Exam.h"

Exam::Exam()
{
}

Exam::~Exam()
{
}

vector<Result> Exam::m1(path dir)
{
	vector<Result> result;

	paths paths = directory_contents(dir, ".txt");	

	vector<future<vector<Result>>> future_results;

	for (int i = 0; i < paths.directories.size(); i++) {
		future_results.push_back(async(&Exam::m1, this, paths.directories[i]));
	}

	for (int i = 0; i < paths.files.size(); i++) {
		result.push_back(Result(paths.files[i],find_min(paths.files[i])));
	}

	for (int i = 0; i < future_results.size(); i++) {
		vector<Result> future_result = future_results[i].get();
		for (int i = 0; i < future_result.size(); i++) result.push_back(future_result[i]);
	}

	return result;
}

Result Exam::m2(path dir, int min)
{
	paths paths = directory_contents(dir, ".dat");

	vector<future<Result>> future_result;
	vector<future_status_enum> future_status;

	for (int i = 0; i < paths.directories.size(); i++) {
		future_result.push_back(async(&Exam::m2, this, paths.directories[i], min));
		future_status.push_back(unread);
	}

	for (int i = 0; i < paths.files.size(); i++) {
		int line = line_exceeds_min(paths.files[i], min);
		if (line != 0) 
			return Result(paths.files[i], line);
	}

	Result result = UNDEFINED_RESULT;
	bool all_read = false;

	do {
		for (int i = 0; i < future_result.size(); i++) {
			if (future_status[i] == unread) {
				if (future_result[i].wait_for(chrono::microseconds(50)) == future_status::ready) {
					future_status[i] = read;
					result = future_result[i].get();
					if (result != UNDEFINED_RESULT) break;
				}
			}
		}
		all_read = true;
		for (int i = 0; i < future_status.size(); i++) all_read &= (future_status[i] == read);
	} while (result == UNDEFINED_RESULT && !all_read);

	return result;
}

Stats Exam::m3(path dir)
{
	vector<path> files = directory_contents(dir);
	return Stats(files);
}

vector<path> Exam::directory_contents(path dir)
{
	paths paths;

	directory_iterator dI(dir);
	for (auto& p : dI) {
		if (path(p).has_extension()) paths.files.push_back(path(p));
		else paths.directories.push_back(path(p));
	}

	for (int i = 0; i < paths.directories.size(); i++) {
		vector<path> subfiles = directory_contents(paths.directories[i]);
		for (int i = 0; i < subfiles.size(); i++) paths.files.push_back(subfiles[i]);
	}

	return paths.files;
}

paths Exam::directory_contents(path dir, string file_suffix)
{
	paths paths;

	directory_iterator dI(dir);
	for (auto& p : dI) {
		if (path(p).has_extension()) {
			if (path(p).extension() == file_suffix) paths.files.push_back(path(p));
		}
		else {
			paths.directories.push_back(path(p));
		}
	}

	return paths;
}

int Exam::find_min(path file)
{
	fstream file_stream;

	file_stream.open(file.string(), fstream::in);

	string content;
	file_stream >> content;

	vector<int> numbers;
	string number = "";

	for (int i = 0; i < content.length(); i++) {
		if (content[i] == ',') {
			numbers.push_back(stoi(number));
			number = "";
		}
		else number += content[i];
	}

	if (number != "") numbers.push_back(stoi(number));

	int smallest_number = numbers[0];

	for (int i = 0; i < numbers.size(); i++) {
		if (numbers[i] < smallest_number) smallest_number = numbers[i];
	}

	return smallest_number;
}

int Exam::line_exceeds_min(path file, int min)
{
	fstream file_stream;
	string file_s = file.string();
	file_stream.open(file_s, fstream::in);
	bool isopen = file_stream.is_open();
	string content;

	int line = 1;

	while (!file_stream.eof()) {
		getline(file_stream, content);

		int sum = 0;
		string number = "";

		for (int i = 0; i < content.length(); i++) {
			if (content[i] == ',') {
				sum += stoi(number);
				number = "";
			}
			else number += content[i];
		}

		if (number != "") sum += stoi(number);

		if (sum > min) return line;
		else line++;
	}

	return 0;
}