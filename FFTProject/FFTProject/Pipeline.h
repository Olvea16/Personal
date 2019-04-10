#pragma once

#include <vector>

template<typename T>
class Pipeline
{
public:
	Pipeline();
	Pipeline(size_t capacity);

	void push(const std::vector<T>& v) {
		if (getSize() + v.size() >= capacity)
	}

	void push(const T * const arr, const size_t nArr) {

	}

	std::vector<T> pop(const size_t n);
	std::vector<T> front(const size_t n);

	size_t getCapacity() {
		return stCapacity;
	}

	size_t getSize() {
		if (iBack < iFront) return capacity - iFront + iBack;
		else return iBack - iFront;
	}

	void resize(size_t newSize) {
		T* newArr = new T[newSize];
		size_t toCopy = (newSize < getSize() ? newSize : getSize());

		for (int j = 0, i = iFront; toCopy > 0; j++, i++, toCopy--) {
			if (i == capacity) i = 0;
			newArr[j] = arr[i];
		}
		delete[] arr;
		stCapacity = newSize;
		arr = newArr;
	}

	~Pipeline() { delete[] arr; }

private:
	size_t capacity, iFront = 0, iBack = 0;
	T* arr;
};

