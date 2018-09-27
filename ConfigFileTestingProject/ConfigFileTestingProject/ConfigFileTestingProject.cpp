// ConfigFileTestingProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ConfigFile.h"

#include <iostream>
#include <string>

int main()
{
	ConfigFile file;

	bool open = file.selectFile(ConfigFile::getDirectoryPath() + "\\test.txt");
	std::string catConfig = file.getConfigValue("Cats");
	std::string dogConfig = file.getConfigValue("Dogs");

 	int a = 0;
	std::cin >> a;
    return 0;
}


