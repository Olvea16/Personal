#pragma once
#include <vector>
#include <complex>

using namespace std;

class FFT
{
public:
	FFT(vector<complex<double>> &samples);
	void calcFFT();
	vector<complex<double>> returnFFT();
	~FFT();
private:
	vector<complex<double>> fft(vector<complex<double>> &samples);
	vector<complex<double>> samples;
	vector<complex<double>> frequencies;
};

