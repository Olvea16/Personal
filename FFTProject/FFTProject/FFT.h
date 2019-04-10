#pragma once
#include "defs.h"
#include "FrequencyTransform.h"

#include <vector>
#include <chrono>

class FFT : public FrequencyTransform
{
public:
	FFT(void(*callback)(const std::vector<BinInformation>&)) : FrequencyTransform(callback) {}
	~FFT() { stop(); }

private:

	std::vector<BinInformation> calculateFFT(const std::vector<Doub>& samples);
	std::vector<Doub> fft(const std::vector<Doub>& samples);

	void mainLoop() {
		while (!stopLooping) {

			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}
	}
};

