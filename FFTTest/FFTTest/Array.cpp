#include "stdafx.h"
#include "Array.h"
#include <iostream>

using namespace std;

Array::Array()
{
}

Array::Array(int inputArray[], int inputLength) {
	length = 0;
	for (int i = 0; i < inputLength; i++) {
		classArray[length] = inputArray[i];
		length++;
	}
}

void Array::setLength(int inputLength) {
	length = inputLength;
}

void Array::setValue(int value, int position) {
	classArray[position] = value;
}

void Array::setValue(int value[], int inputLength, int position) {
	for (int i = position; i < inputLength + position; i++) {
		classArray[i] = value[i - position];
	}
	if (length < inputLength + position) {
		length = inputLength + position;
	}
}

void Array::addValue(int value) {
	classArray[length] = value;
	length++;
}

void Array::insertValue(int value, int position) {
	for (int i = position; i < length; i++) {
		classArray[length - i + position] = classArray[length - i + position - 1];
	}
	setValue(value, position);
	length++;
}

void Array::addValue(int value[], int inputLength) {
	for (int i = 0; i < inputLength; i++) {
		classArray[length++] = value[i];
	}
}

int Array::getValue(int position) {
	return classArray[position];
}

int Array::getLength() {
	return length;
}

int Array::getSum() {
	int sum = 0;
	for (int i = 0; i < length; i++) {
		sum += classArray[i];
	}
	return sum;
}

double Array::getAverage() {
	double sum = getSum();
	double length = Array::length;
	return getSum() / length;
}

int Array::find(int value) {
	for (int i = 0; i < length; i++) {
		if (value == classArray[i]) {
			return i;
		}
	}
	return -1;
}

bool Array::contains(int value) {
	if (find(value) != -1) return true;
	return false;
}

void Array::remove(int position) {
	for (int i = position; i < length - 1; i++) {
		classArray[i] = classArray[i + 1];
	}
	length--;
}

void Array::swapEnds() {
	int temp;
	temp = classArray[length - 1];
	classArray[length - 1] = classArray[0];
	classArray[0] = temp;
}

void Array::reverseArray() {
	int tempArray[100];
	for (int i = 0; i < length; i++) {
		tempArray[i] = classArray[length - (i + 1)];
	}
	setValue(tempArray, length, 0);
}

int Array::largest() {
	int largestNumber = classArray[0];
	for (int i = 1; i < length; i++) {
		if (classArray[i] > largestNumber) largestNumber = classArray[i];
	}
	return largestNumber;
}

int Array::smallest() {
	int smallestNumber = classArray[0];
	for (int i = 1; i < length; i++) {
		if (classArray[i] < smallestNumber) smallestNumber = classArray[i];
	}
	return smallestNumber;
}

void Array::insertionSort() {
	int tempArray[100];
	int tempLength = 1;
	bool inserted;

	for (int i = 1; i < length; i++) {
		tempArray[i - 1] = classArray[i];		//Kopierer classArray over i tempArray
	}

	for (int i = 1; i < length; i++) {
		classArray[i] = 0;					//Tømmer classArray
	}

	for (int i = 0; i < length - 1; i++) {
		inserted = false;
		for (int j = 0; j < tempLength; j++) {
			if (tempArray[i] < classArray[j]) {
				insertValue(tempArray[i], j);
				inserted = true;
				tempLength++;
				length--;
				break;
			}
		}
		if (!inserted) {
			setValue(tempArray[i], tempLength++);
		}
	}
}

void Array::selectionSort() {
	int tempArray[100];
	int tempLength = length;
	for (int i = 0; i < tempLength; i++) {
		tempArray[i] = smallest();
		remove(find(smallest()));
	}
	setValue(tempArray, tempLength, 0);
}

void Array::bubbleSort() {

}

void Array::printArray() {
	cout << "| {";
	for (int i = 0; i < length - 1; i++) {
		cout << classArray[i] << ", ";
	}
	cout << classArray[length - 1] << "} | Sum: " << getSum() << " | Length: " << getLength() << " | Avg: " << getAverage() << " | Smallest: " << smallest() << " | Largest: " << largest() << "\n";
}

Array::~Array()
{
}
