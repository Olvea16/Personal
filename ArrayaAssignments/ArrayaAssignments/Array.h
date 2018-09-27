#pragma once
class Array
{
public:
	Array();
	Array(int[], int);
	void setLength(int);
	void setValue(int, int);
	void setValue(int[], int, int);
	void addValue(int);
	void addValue(int[],int);
	void insertValue(int, int);
	int getValue(int);
	int getLength();
	int getSum();
	double getAverage();
	bool contains(int);
	int find(int);
	void remove(int);
	void swapEnds();
	void reverseArray();
	int largest();
	int smallest();
	void insertionSort();
	void selectionSort();
	void bubbleSort();
	void printArray();
	~Array();
private:
	int classArray[10000];
	int length;
};

