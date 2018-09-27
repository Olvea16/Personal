#include <vector>
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std;

const int N = 50;
const int arrSize = 100;

const int consumerWait = 50;
const int producerWait = 10;

int arr[arrSize] = { 0 };
vector<int> primes;
mutex myMutex;

/*
bool isPrime(int a) {
	bool prime = true;
	for (int j = 2; j < a; j++) {
		if (a % j == 0) prime = false;
	}
	return prime;
}

vector<int> findAllPrimes(int N) {
vector<int> result;
for (int i = 1; i < N + 1; i++) {
if (isPrime(i)) result.push_back(i);
}
return result;
}
//*/

//*
bool isPrime(int a) {
	for (int i = 0; i < primes.size(); i++) {
		if (a == primes[i]) return true;
	}
	return false;
}

vector<int> findAllPrimes(int N) {
	vector<int> result;
	for (int i = 1; i < N + 1; i++) {
		bool prime = true;
		for (int j = 2; j < i; j++) {
			if (i % j == 0) prime = false;
		}
		if (prime) result.push_back(i);
	}
	return result;
}
//*/

vector<int> findAllPrimes(int n, int N) {
	vector<int> result;
	for (int i = n; i < N + 1; i++) {
		if (isPrime(i)) result.push_back(i);
	}
	return result;
}

bool containsNonprimes(int primes[arrSize]) {
	for (int i = 0; i < arrSize; i++) {
		if (!isPrime(primes[i])) return true;
	}
	return false;
}

bool containsZeroes(int arr[arrSize]) {
	for (int i = 0; i < arrSize; i++) {
		if (arr[i] == 0) return true;
	}
	return false;
}

bool containsAllPrimes(int arr[arrSize]) {
	for (int i = 0; i < primes.size(); i++) {
		bool isContained = false;
		for (int j = 0; j < arrSize; j++) {
			if (arr[j] == primes[i]) isContained = true;
		}
		if (!isContained) return false;
	}
	return true;
}

void sort(int arr[arrSize]) {
	int resultArr[arrSize];
	for (int i = 0; i < arrSize; i++) {
		int smallest = 0;
		for (int j = 1; j < arrSize - i; j++) {
			if (arr[smallest] > arr[j]) smallest = j;
		}
		resultArr[i] = arr[smallest];
		for (int i = smallest; i < arrSize - 1; i++) {
			arr[i] = arr[i + 1];
		}
	}
	for (int i = 0; i < arrSize; i++) {
		arr[i] = resultArr[i];
	}
}

void Producer() {
	while (!containsAllPrimes(arr)) {
		myMutex.lock();
		for (int i = 0; i < arrSize; i++) {
			if (arr[i] == 0) {
				arr[i] = rand() % N + 1;
				break;
			}
		}
		myMutex.unlock();
		this_thread::sleep_for(chrono::milliseconds(producerWait));
	}
}

void Consumer() {
	while (!containsAllPrimes(arr)) {
		myMutex.lock();
		for (int i = 0; i < arrSize; i++) {
			if (!isPrime(arr[i])) arr[i] = 0;
		}
		myMutex.unlock();
		this_thread::sleep_for(chrono::milliseconds(consumerWait));
	}
}

int main() {
	primes = findAllPrimes(N);

	thread producerThread(Producer);
	thread consumerThread(Consumer);

	producerThread.join();
	consumerThread.join();

	sort(arr);

	for (int i = 0; i < arrSize; i++) {
		cout << arr[i] << "\n";
	}
	
	system("pause");
	return 0;
}