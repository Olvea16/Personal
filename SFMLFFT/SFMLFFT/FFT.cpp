#include "FFT.h"

using namespace std;

const double pi = 3.141592653589793;

FFT::FFT(vector<complex<double>> &samples, int sampleFrequency) : samples(samples), sampleFrequency(sampleFrequency)
{}

void FFT::calcFFT() {
	N = samples.size();
	frequencies = fft(samples);
	amplitudes.resize(N);
	for (int i = 0; i < N; i++) {
		amplitudes[i] = abs(frequencies[i]) / N;
	}
}

vector<complex<double>> FFT::returnFFT() {
	return frequencies;
}

vector<double> FFT::returnAmplitudes()
{
	return amplitudes;
}

vector<complex<double>> FFT::fft(vector<complex<double>> &samples) {
	int N = samples.size(); //Local N
	if (N == 1) return samples;
	
	int M = N / 2;
	vector<complex<double>> xEven(M, 0);
	vector<complex<double>> xOdd(M, 0);
	for (int i = 0; i < M; i++) {
		xEven[i] = samples[2 * i];
		xOdd[i] = samples[2 * i + 1];
	}

	vector<complex<double>> fEven(M, 0);
	vector<complex<double>> fOdd(M, 0);

	fEven = fft(xEven);
	fOdd = fft(xOdd);

	vector<complex<double>> freqBins(N, 0);

	for (int k = 0; k < N / 2; k++) {
		complex<double> complexExponential = polar(1.0, -2 * pi * k / N) * fOdd[k];
		freqBins[k] = fEven[k] + complexExponential;
		freqBins[k + N / 2] = fEven[k] - complexExponential;
	}

	return freqBins;
}


FFT::~FFT() {

}
