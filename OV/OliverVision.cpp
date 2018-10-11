// OliverVision.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "OliverVision.h"

OLIVERVISION_API void ov::normalize(double * arr, size_t n)
{
	double sum = 0;
	for (int i = 0; i < n; i++) sum += arr[i];
	for (int i = 0; i < n; i++) arr[i] /= sum;
}

