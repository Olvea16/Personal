#pragma once
#include <vector>
#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <future>
#include "Result.h"
#include "Stats.h"

using namespace std;
namespace fs = std::experimental::filesystem::v1;
using namespace fs;

struct paths {
	vector<path> directories;
	vector<path> files;
};

enum future_status_enum {
	unread, read
};

class Exam
{
public:
	Exam();
	~Exam();
	
	/**
	* This method recursively visits a directory to find all the text
	* files contained in it and its subdirectories.
	*
	* You must consider only files ending with a ".txt" suffix.
	* You are guaranteed that they will be text files.
	*
	* You can assume that each text file contains a (non-empty)
	* comma-separated sequence of
	* numbers. For example: 100,200,34,25
	* There won't be any new lines, spaces, etc., and the sequence never
	* ends with a comma.
	* You are guaranteed that each number will be at least or equal to
	* 0 (zero), i.e., no negative numbers.
	*
	* The search is recursive: if the directory contains subdirectories,
	* these are also searched and so on so forth (until there are no more
	* subdirectories).
	*
	* This method returns a list of results.
	* The list contains a result for each text file that you find.
	* Each {@link Result} stores the path of its text file,
	* and the lowest number (minimum) found inside of the text file.
	*
	* @param dir the directory to search
	* @return a list of results ({@link Result}), each giving the lowest number found in a file
	*/
	vector<Result> m1(path dir);

	/**
	* This method recursively visits a directory for text files with suffix
	* ".dat" (notice that it is different than the one before)
	* contained in it and its subdirectories.
	*
	* You must consider only files ending with a .dat suffix.
	* You are guaranteed that they will be text files.
	*
	* Each .dat file contains some lines of text,
	* separated by the newline character "\n".
	* You can assume that each line contains a (non-empty)
	* comma-separated sequence of
	* numbers. For example: 100,200,34,25
	*
	* This method looks for a .dat file that contains a line whose numbers,
	* when added together (total), amount to at least (>=) parameter min.
	* Once this is found, the method can return immediately
	* (without waiting to analyse also the other files).
	* The return value is a result that contains:
	*	- path: the path to the text file that contains the line that respects the condition;
	*  - number: the line number, starting from 1 (e.g., 1 if it is the first line, 3 if it is the third, etc.)
	*
	*/
	Result m2(path dir, int min);

	/**
	* Computes overall statistics about the occurrences of numbers in a directory.
	*
	* This method recursively searches the directory for all numbers in all lines of .txt and .dat files and returns
	* a {@link Stats} object containing the statistics of interest. See the
	* documentation of {@link Stats}.
	*/
	Stats m3(path dir);

private:
	vector<path> directory_contents(path dir);
	paths directory_contents(path dir, string file_suffix);
	int find_min(path file);
	int line_exceeds_min(path file, int min);
};

