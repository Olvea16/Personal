#pragma once

#include <string>
#include <vector>
#include <Windows.h>

struct RGBColor {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

static class IconManager
{
public:
	IconManager();
	~IconManager();

	static std::vector<std::vector<RGBColor>> get_image(std::string path, int output_width, int output_height);
};

