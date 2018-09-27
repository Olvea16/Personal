#pragma once
#include <vector>
#include <complex>

using namespace std;

class FFT
{
public:
	FFT(vector<complex<double>> &samples, int sampleFrequency);
	void calcFFT();
	vector<complex<double>> returnFFT();
	vector<double> returnAmplitudes();
	~FFT();
private:
	vector<complex<double>> fft(vector<complex<double>> &samples);
	vector<complex<double>> samples;
	vector<complex<double>> frequencies;
	vector<double> amplitudes;
	int N; //Global N
	int sampleFrequency;
	int samplePeriod;
};

