#pragma once
#include "defs.h"
#include "FrequencyTransform.h"

#include <SFML/Audio/SoundRecorder.hpp>

class AudioStreamIn : public sf::SoundRecorder
{
public:
	AudioStreamIn(FrequencyTransform* pFreqTrans, void(FrequencyTransform::*callback)(const std::vector<Doub>&), const std::string& deviceName = getDefaultDevice(), sf::Time samplePeriod = sf::milliseconds(100))
		: freqCallback(callback), deviceName(deviceName), samplePeriod(samplePeriod)
	{
		setProcessingInterval(samplePeriod);
		setDevice(deviceName);
		setChannelCount(1);
	}

	~AudioStreamIn() {}

	// Optional.
	// initialize whatever has to be done before the capture starts
	// return true to start the capture, or false to cancel it
	virtual bool onStart() 
	{
		if (samplePeriod <= sf::milliseconds(0) || deviceName == "") return false;
		return true;
	}

	// do something useful with the new chunk of samples
    // return true to continue the capture, or false to stop it
	bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount) {
		std::vector<Doub> result(sampleCount); 
		for (int i = 0; i < sampleCount; i++) result[i] = samples[i];
		(pFreqTrans->*freqCallback)(result);
		return true;
	}


	// Optional.
	// clean up whatever has to be done after the capture is finished
	virtual void onStop() { }

private:
	FrequencyTransform* pFreqTrans;
	void(FrequencyTransform::*freqCallback)(const std::vector<Doub>&);
	std::string deviceName;
	sf::Time samplePeriod;
	
};

