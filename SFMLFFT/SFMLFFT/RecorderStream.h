#include "SFML\Audio.hpp"
#include "FFT.h"
#include <complex>
#include <vector>

using namespace std;
using namespace sf;

class RecorderStream : public SoundRecorder
{
	virtual bool onStart() // optional
	{
		// initialize whatever has to be done before the capture starts
		// return true to start the capture, or false to cancel it
		//this->setChannelCount = 1;
		return true;
	}

	virtual bool onProcessSamples(const Int16* samples, std::size_t sampleCount)
	{

		/*vector<complex<double>> complexSamples;
		for (int i = 0; i < 4096; i++) {
			complexSamples[i] = samples[i];
		}
		FFT myFFT(complexSamples);
		myFFT.returnFFT;*/
		return true;
	}

	virtual void onStop() // optional
	{
		// clean up whatever has to be done after the capture is finished
	}

private:
	SoundBuffer buffer;
};
