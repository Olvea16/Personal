#include "MIDIIn.h"

static void CALLBACK midi_callback(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
	std::unordered_map<int, QSlider*> sliders = *((std::unordered_map<int, QSlider*>*)dwInstance);
	MIDIIn midi_in;
	std::vector<int> midi_data = midi_in.to_bytes(dwParam1);

	if (sliders[midi_data[1]] != NULL) sliders[midi_data[1]]->setValue(midi_data[2] * 100 / 127);
}

MIDIIn::MIDIIn()
{
}


MIDIIn::~MIDIIn()
{
}

std::vector<std::string> MIDIIn::get_devices() {
	std::vector<std::string> result;

	int amount = (int)midiInGetNumDevs();

	for (int i = 0; i < amount; i++) {
		MIDIINCAPS midi_in_caps;
		MMRESULT mr = midiInGetDevCaps(
			i,
			&midi_in_caps,
			sizeof(MIDIINCAPS)
		);
		std::string resulting_string;
		WCHAR character;
		int j = 0;
		do {
			character = midi_in_caps.szPname[j++];
			resulting_string += character;
		} while (character != '\0');
		result.push_back(resulting_string);
	} 
	return result;
}

void MIDIIn::set_slider(QSlider * slider, int channel)
{
	sliders[channel] = slider;
}

void MIDIIn::start_communication(int device)
{
	if (device < get_devices().size() && device >= 0) {
		HMIDIIN in_handle;

		MMRESULT mr = midiInOpen(
			&in_handle,
			device,
			(DWORD_PTR)midi_callback,
			(DWORD_PTR)&sliders,
			CALLBACK_FUNCTION
		);

		midiInStart(in_handle);
	}
}

std::vector<int> MIDIIn::to_bytes(int value) {
	std::vector<int> result;
	int i = 4;
	while (i-- > 0) {
		result.push_back(value % (2 << 7));
		value /= 2 << 7;
	}
	return result;
}