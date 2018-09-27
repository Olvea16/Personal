#pragma once

#include <string>
#include <vector>
#include <Windows.h>

struct RGBColor {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

class IconManager
{
private:
	std::string path;
	unsigned int output_width, output_height;

	HBITMAP hbitmap;
	BITMAP bitmap;
	HDC hdc;

public:
	IconManager(std::string path, unsigned int output_width, unsigned int output_height);
	~IconManager();

	std::vector<std::vector<RGBColor>> get_image();
};

