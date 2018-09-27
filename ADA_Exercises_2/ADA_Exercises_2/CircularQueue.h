#pragma once
template <typename T>
class CircularQueue
{
public:
	CircularQueue(size_t size) : size(size)
	{
		queue = new T[size];
		dequeue_index = size - 1;
	}

	~CircularQueue() {
		delete[] queue;
	}

	void enqueue(T element) {
		if ((enqueue_index + 1) % size != dequeue_index) {
			queue[enqueue_index] = element;
			incrementIndex(&enqueue_index);
		}
	}

	T dequeue() {
		if ((dequeue_index + 1) % size != enqueue_index) {
			T result = queue[dequeue_index];
			incrementIndex(&dequeue_index);
			return result;
		}
		return T();
	}

	void incrementIndex(size_t* index) {
		(*index)++;
		if (*index == size) *index = 0;
	}

private:
	T * queue;
	size_t size;
	size_t enqueue_index = 0;
	size_t dequeue_index = 0;
};

