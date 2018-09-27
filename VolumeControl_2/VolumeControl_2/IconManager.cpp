#include "IconManager.h"

#include <iostream>

#define ICON_AMOUNT 32

IconManager::IconManager()
{
}

IconManager::~IconManager()
{
}

std::vector<std::vector<RGBColor>> IconManager::get_image(std::string path, int output_width, int output_height)
{
	HICON icons[2][ICON_AMOUNT] = { NULL };

	// EXTRACT ICONS FROM .EXE FILE
	unsigned int icons_extracted = ExtractIconExA(
		path.c_str(),
		0,
		icons[1],
		icons[0],
		ICON_AMOUNT);

	std::vector<HBITMAP> hbitmaps;

	// CONVERT FROM ICON HEADERS TO BITMAP HEADERS
	for (int n = 0; n < 2; n++) {
		int i = 0;
		while (i < ICON_AMOUNT && icons[n][i] != NULL) {
			ICONINFO info;
			GetIconInfo(icons[n][i], &info);
			HBITMAP hbitmap = info.hbmColor;
			hbitmaps.push_back(hbitmap);
			DestroyIcon(icons[n][i]);
			i++;
		}
	}
	
	// SELECT THE ICON WITH THE DESIRED RESOLUTION, THE SMALLEST ONE THATS LARGER OR THE LARGEST ICON AVAILABLE.
	
	HBITMAP hbitmap;
	BITMAP bitmap;
	for (int i = 0; i < hbitmaps.size(); i++) {
		BITMAP current_bitmap;
		GetObject(hbitmaps[i], sizeof(BITMAP), &current_bitmap);

		if ((current_bitmap.bmHeight >= output_height && current_bitmap.bmWidth >= output_width) || i == hbitmaps.size() - 1) {
			hbitmap = hbitmaps[i];
			bitmap = current_bitmap;
			break;
		}
	}

	// SCALE BITMAP USING NEAREST-NEIGHBOUR
	HDC hdc = CreateCompatibleDC(NULL);
	SetStretchBltMode(hdc, HALFTONE);

	if (bitmap.bmHeight != output_height || bitmap.bmWidth != output_width) {
		HDC temp_hdc = CreateCompatibleDC(NULL);
		HBITMAP scaled_hbitmap = CreateBitmap(output_width, output_height, 1, 32, NULL);
		SelectObject(temp_hdc, hbitmap);
		SelectObject(hdc, scaled_hbitmap);
		StretchBlt(
			hdc,
			0,
			0,
			output_width,
			output_height,
			temp_hdc,
			0,
			0,
			bitmap.bmWidth,
			bitmap.bmHeight,
			SRCCOPY);
		hbitmap = scaled_hbitmap;
		GetObject(hbitmap, sizeof(BITMAP), &bitmap);
	}
	else {
		SelectObject(hdc, hbitmap);
	}

	std::vector<std::vector<RGBColor>> image;

	for (int y = 0; y < output_height; y++) {
		std::vector<RGBColor> row;
		for (int x = 0; x < output_width; x++) {
			RGBColor color;
			COLORREF color_ref = GetPixel(hdc, output_width - x - 1, output_height - y - 1);
			color.r = GetRValue(color_ref);
			color.g = GetGValue(color_ref);
			color.b = GetBValue(color_ref);
			row.push_back(color);
		}
		image.push_back(row);
	}

	return image;
}
