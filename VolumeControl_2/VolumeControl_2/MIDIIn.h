#pragma once
#include <vector>
#include <string>
#include <unordered_map>

//MIDI Stuff
#include <Windows.h>
#include <mmsystem.h>

//Qt stuff
#include <qslider.h>

class MIDIIn
{
public:
	MIDIIn();
	~MIDIIn();

	std::vector<std::string> get_devices();
	void set_slider(QSlider* slider, int channel);

	void start_communication(int device);

	std::vector<int> to_bytes(int value);

private:
	//static void CALLBACK midi_callback(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);

	std::unordered_map<int, QSlider*> sliders;
};

