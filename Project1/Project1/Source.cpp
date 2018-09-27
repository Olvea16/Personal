#include <thread>
#include <future>
#include <iostream>
#include <Windows.h>
#include <random>
#include <filesystem>

using namespace std;

mutex mu;
condition_variable cv;

int threadfunction(int id, int timeToSleep) {
	Sleep(timeToSleep);
	cout << "Thread " << id << " is done after sleeping " << timeToSleep << "ms." << endl;
	return id;
}

int main() {
	srand(time(NULL));

	vector<future<int>> futures;
	const int future_amount = 10;

	int timeToSleep[future_amount];

	for (int i = 0; i < future_amount; i++) {
		timeToSleep[i] = rand() % 4501 + 500;
		futures.push_back(async(std::launch::async, threadfunction, i + 1, timeToSleep[i]));
	}
	
	int fastestThread = -1;

	while (fastestThread == -1) {
		for (int i = 0; i < future_amount; i++) {
			if (futures[i].wait_for(std::chrono::microseconds(10)) == future_status::ready) {
				fastestThread = futures[i].get();
				break;
			}
		}
	}

	int fT = 0;

	for (int i = 0; i < future_amount; i++) {
		if (timeToSleep[i] < timeToSleep[fT]) fT = i;

		cout << "Thread id: " << i + 1 << ", thread sleep time: " << timeToSleep[i] << "ms." << endl;
	}

	cout << endl << "Guess for fastest thread: " << fT + 1 << endl;
	cout << "Fastest thread: " << fastestThread << endl << endl << " ----- " << endl << endl;

	int a;
	cin >> a;
	return 0;
}