// CircularBuffer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CircularBuffer.h"

#include <iostream>

int main()
{
	size_t size = 100;
	CircularBuffer<int> buf(size);

	for (int i = 0; i < size + 1; i++) {
		buf.enqueue(i);
	}

	for (int i = 0; i < size + 2; i++) {
		std::cout << buf.dequeue() << std::endl;
	}

    return 0;
}
