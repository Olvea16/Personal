#pragma once
template <typename T>
class CircularBuffer
{
public:
	CircularBuffer(size_t size) : size(size) 
	{
		queue = new T[size];
	}
	~CircularBuffer() {
		delete[] queue;
	}

	void incrementIndex(size_t* pIndex) {		
		(*pIndex)++;
		if ((*pIndex) == size) (*pIndex) = 0;
	}

	void enqueue(T element) {
		if (empty || (enqueueIndex != dequeueIndex)) {
			queue[enqueueIndex] = element;
			incrementIndex(&enqueueIndex);
			empty = false;
		}
	}

	T dequeue() {
		if (!empty) {
			T element = queue[dequeueIndex];
			incrementIndex(&dequeueIndex);
			empty |= enqueueIndex == dequeueIndex;
			return element;
		}
		return T();
	}

private:
	size_t size;
	T* queue;
	bool empty = true;

	size_t enqueueIndex = 0;
	size_t dequeueIndex = 0;
};

