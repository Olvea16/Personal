// MidiTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// EXTRA stuff
#include <iostream>
#include <vector>

//MIDI Stuff
#include <Windows.h>
#include <mmsystem.h>

//#include <windows.devices.midi.h>
//#include <windows.devices.enumeration.h>

using namespace std;

static void CALLBACK midi_callback(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);
vector<int> to_bytes(int value);

int main()
{
	int amount = (int)midiInGetNumDevs();
	cout << "Amount of MIDI devices: " << amount << endl;

	HMIDIIN in_handle;

	for (int i = 0; i < amount; i++) {
		MIDIINCAPS midi_in_caps;
		MMRESULT mr = midiInGetDevCaps(
			i,
			&midi_in_caps,
			sizeof(MIDIINCAPS)
		);
		cout << "Device " << i << ": " << midi_in_caps.szPname << endl;
	}

	UINT device_id = 0;

	MMRESULT mr = midiInOpen(
		&in_handle,
		device_id,
		(DWORD)midi_callback,
		0,
		CALLBACK_FUNCTION
		);

	midiInStart(in_handle);

	while (1) Sleep(100);

    return 0;
}

static void CALLBACK midi_callback(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2) {
	vector<int> midi_data = to_bytes(dwParam1);
	
	cout << "Message: " << wMsg << '\t';
	for (int i = 0; i < midi_data.size(); i++) cout << "Data " << i << ':' << midi_data[i] << '\t';
	cout << "Time: " << dwParam2 << endl;
}

vector<int> to_bytes (int value) {
	vector<int> result;
	int i = 4;
	while (i-- > 0) {
		result.push_back(value % (2 << 7));
		value /= 2 << 7;
	}
	return result;
}
