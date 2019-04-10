
#include "AudioStreamIn.h"
#include "FFT.h"

void getSamples(const std::vector<FFT::BinInformation>& bins);

int main() {
	FFT fft(&getSamples);
	Doub samplePeriod = (0.085 + 1.0 / 3000.0) * 1000000.0;
	AudioStreamIn stream(&fft, &FFT::sampleCallback, sf::SoundRecorder::getDefaultDevice(), sf::microseconds(samplePeriod));

	fft.start();
	stream.start();

	while (true) std::this_thread::sleep_for(std::chrono::seconds(1));

	return 0;
}	

void getSamples(const std::vector<FFT::BinInformation>& bins) {

	return;
}