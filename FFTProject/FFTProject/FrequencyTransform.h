#pragma once
#include "defs.h"

#include <vector>
#include <queue>
#include <mutex>

class FrequencyTransform
{
public:
	struct BinInformation {
		Doub amplitude;
		Doub frequency; // Center
		Doub frequencyWidth;
	};

	FrequencyTransform(void(*callback)(const std::vector<BinInformation>&)) : callback(callback) { }
	~FrequencyTransform() { stop(); }

	void start() { mainThread = std::thread(&FrequencyTransform::mainLoop, this); }
	void stop() {
		stopLooping = true;
		mainThread.join();
	}

	void sampleCallback(const std::vector<Doub>& samples) 
	{
		queueMutex.lock();
		queue.push(samples);
		queueMutex.unlock();
	}

protected:
	bool stopLooping = false;
	std::mutex queueMutex;
	std::thread mainThread;
	std::queue<std::vector<Doub>> queue;
	void(*callback)(const std::vector<BinInformation>&);

	virtual void mainLoop() { throw(std::logic_error("This should never happen, the method should be overloaded.")); }
};

