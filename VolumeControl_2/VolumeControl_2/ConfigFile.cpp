#include "ConfigFile.h"

#include <iostream>
#include <filesystem>

ConfigFile::ConfigFile()
{
}


ConfigFile::~ConfigFile()
{
}

bool ConfigFile::selectFile(std::string path, bool create_new)
{

	ConfigFile::path = path;
	std::fstream file_stream;
	if (create_new) file_stream.open(path, std::ios::out);
	else file_stream.open(path);
	bool result = file_stream.is_open();
	file_stream.close();
	validPath = result;
	return result;
}

bool ConfigFile::createFile(std::string path)
{
	return selectFile(path, true);
}

std::string ConfigFile::getConfigValue(std::string config)
{
	std::string result = "";

	if (path == "") return result;

	std::ifstream file_stream;
	file_stream.open(path);

	if (!file_stream.is_open()) return result;

	while (!file_stream.eof() && result == "") {
		std::string line_config, line_value;

		getline(file_stream, line_config, '=');
		getline(file_stream, line_value, '\n');

		if (line_config == config) result = line_value;
	}

	return result;
}

bool ConfigFile::setConfigValue(std::string config, std::string value, bool create_new)
{
	return false;
}

std::string ConfigFile::getDirectoryPath() {
	TCHAR buffer[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, buffer);
	int i = 0;
	std::string result;
	while (buffer[i] != '\0') result += buffer[i++];
	return result;
}