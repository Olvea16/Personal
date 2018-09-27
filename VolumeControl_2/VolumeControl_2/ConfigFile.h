#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h> // .exe path name

class ConfigFile
{
private:
	std::string path;
	bool validPath = false;

public:
	ConfigFile();
	~ConfigFile();

	bool selectFile(std::string path, bool create_new = false);
	bool createFile(std::string path);

	std::string getConfigValue(std::string config);
	bool setConfigValue(std::string config, std::string value, bool create_new = false);
	static std::string getDirectoryPath();
};

