#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"
#include "FFT.h"
#include "RecorderStream.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace sf;

complex<double> SineWave(double time, double freqa, double freqb, double amp) {
	complex<double> result;
	result = 32767 * amp * sin(2 * 3.1415927 * time * freqa);
	result += 32767 * amp * sin(2 * 3.1415927 * time * freqb);
	return result;
}

int lowerDTMF[4] = { 697,770,852,941 };
int higherDTMF[4] = { 1209,1336,1447,1633 };

const int sampleFreq = 4000;
const float tMeas = 32.0 / 1000.0;
float samplePeriod = 1 / sampleFreq;
const int N = sampleFreq * tMeas;

const int barWidth = 1920 / (N * 4);
const float noiseAmplitude = 0.2;

const float yScale = 1.0 / 4.0;

int main()
{
	RenderWindow window(sf::VideoMode(1920 / 4, 1080 / 3), "SFML works!");

	SoundBuffer buffer;
	vector<Int16> bufferSamples;
	vector<complex<double>> samples;
	vector<RectangleShape> bars;
	samples.resize(N);
	Sound sound;

	int lowerDTMFFreq;
	int higherDTMFFreq;

	srand(time(NULL));

	/*ofstream myfile;
	myfile.open("example.csv");*/

	for (int i = 0; i < N; i++) {
		RectangleShape shape;
		shape.setPosition(Vector2f((i - 1) * barWidth, 1080 / 3));
		bars.push_back(shape);
	}

	//myfile.close();

	while (window.isOpen())
	{
		//SINUSGENERERING
		lowerDTMFFreq = lowerDTMF[rand() % 4];
		higherDTMFFreq = higherDTMF[rand() % 4];

		for (double i = 0; i < N; i++) {
			samples[i] = (SineWave(i / sampleFreq, lowerDTMFFreq, higherDTMFFreq, 0.05) + complex<double>((rand() % 32767) * noiseAmplitude));
		}

		//FFTDEL
		FFT fft(samples, sampleFreq);
		fft.calcFFT();
		vector<double> amplitudes = fft.returnAmplitudes();

		//FORTOLKNINGSDEL
		int ultimateFreq = 1;
		int penultimateFreq = 1;
		for (int i = 1; i < N / 2; i++) {
			if (amplitudes[i] > amplitudes[ultimateFreq]) {
				penultimateFreq = ultimateFreq;
				ultimateFreq = i;
			}
			else {
				if (amplitudes[i] > amplitudes[penultimateFreq]) penultimateFreq = i;
			}
		}
		ultimateFreq = ultimateFreq / tMeas - 1;
		penultimateFreq = penultimateFreq / tMeas - 1;
		if (ultimateFreq < 1075) {
			int temp = ultimateFreq;
			ultimateFreq = penultimateFreq;
			penultimateFreq = temp;
		}

		cout << "Målt frekv: " << ultimateFreq << " og " << penultimateFreq << endl;

		if (ultimateFreq < 1273)							ultimateFreq = 1209;
		if (ultimateFreq >= 1273 && ultimateFreq < 1392)	ultimateFreq = 1336;
		if (ultimateFreq >= 1392 && ultimateFreq < 1540)	ultimateFreq = 1447;
		if (ultimateFreq >= 1540)							ultimateFreq = 1633;

		if (penultimateFreq < 733)								penultimateFreq = 697;
		if (penultimateFreq >= 733 && penultimateFreq < 811)	penultimateFreq = 770;
		if (penultimateFreq >= 811 && penultimateFreq < 896)	penultimateFreq = 852;
		if (penultimateFreq >= 896)								penultimateFreq = 941;

		cout << "Frekvens: "<< higherDTMFFreq << " og " << lowerDTMFFreq << endl;
		cout << "Gæt:      " << ultimateFreq << " og " << penultimateFreq << endl;
		if (ultimateFreq == higherDTMFFreq && penultimateFreq == lowerDTMFFreq) cout << "Korrekt!\n" << " ------ \n";
		else cout << "Forkert!\n" << " ------ \n";

		//EVENTDEL
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}


		//LYDDEL
		for (int i = 1; i < N; i++) {
			bufferSamples.push_back((samples[i]).real());
		}
		buffer.loadFromSamples(&bufferSamples[0], N, 1, sampleFreq);
		sound.setBuffer(buffer);
		sound.play();
		bufferSamples.clear();
		
		//TEGNEDEL
		window.clear();

		for (int i = 1; i < N; i++) {
			bars[i].setSize(Vector2f(barWidth, -amplitudes[i] * yScale));
			window.draw(bars[i]);
		}
		window.display();

		sleep(milliseconds(1000));
	}

	return 0;
}