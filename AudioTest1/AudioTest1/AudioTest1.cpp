#include "stdafx.h"
#include <SFML\Audio.hpp>
#include <math.h>
#include <vector>

using namespace std;

short sineWave(double t, double f, double a) {
	short result;
	double tcp = 44100 / f;
	double cycles = t / tcp;
	double rad = 2 * 3.1415927 * cycles;
	short amplitude = 32767 * a;
	result = amplitude * sin(rad);
	return result;
}

int main()
{
	sf::SoundBuffer buffer;
	vector<short> samples;

	for (int i = 0; i < 44100; i++) {
		samples.push_back(sineWave(i, 440, 0.5));
	}

	buffer.loadFromSamples(&samples[0],samples.size(),1,44100);

	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();

    return 0;
}
