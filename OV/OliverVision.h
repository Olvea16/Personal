// MathLibrary.h - Contains declarations of math functions
#pragma once

#ifdef OLIVERVISION_EXPORTS
#define OLIVERVISION_API __declspec(dllexport)
#else
#define OLIVERVISION_API __declspec(dllimport)
#endif
namespace ov {
	extern "C" OLIVERVISION_API void normalize(double* arr, size_t n);
}