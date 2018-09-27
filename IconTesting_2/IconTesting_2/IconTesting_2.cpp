// IconTesting_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "IconManager.h"

const std::string path = "C:\\Program Files\\NVIDIA Corporation\\NvContainer\\nvcontainer.exe";

int main()
{
	IconManager manager(path, 128, 128);
	std::vector<std::vector<RGBColor>> image = manager.get_image();
    return 0;
}

