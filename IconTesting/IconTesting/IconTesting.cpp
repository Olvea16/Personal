// IconTesting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "IconManager.h"

#include <string>
#include <vector>
#include <Windows.h>
#include <shellapi.h>
#include <iostream>


const std::string path = "C:\\Program Files\\NVIDIA Corporation\\NvContainer\\nvcontainer.exe";
//const std::string path = "C:\\Program Files(x86)\\Google\\Chrome\\Application\\chrome.exe";
//const std::string path = "E:\\Blizzard App\\Battle.net.exe";


int main()
{
	IconManager icon_manager(path, 128, 128);
	std::vector<std::vector<RGBColor>> image = icon_manager.get_image();

	int a;
	std::cin >> a;
     return 0;
}

