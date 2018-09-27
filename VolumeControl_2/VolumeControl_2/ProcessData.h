#pragma once

#include "IconManager.h"

#include <Windows.h>
#include <Psapi.h>
#include <vector>
#include <string>
#include <mmsystem.h>
#include <audiopolicy.h>
#include <endpointvolume.h>
#include <mmdeviceapi.h>
#include <gdiplus.h>

struct AudioSessionData {
	ISimpleAudioVolume* simple_audio_volume;
	float master_volume;
	std::string path;
	std::string process_name;
};

struct ProcessDataStruct {
	DWORD process_id;
	std::string process_name;
};

class ProcessData
{
public:
	ProcessData();
	~ProcessData();

	std::vector<AudioSessionData> get_session_data();

private:
	void split_string(std::string input, char delimiter, std::vector<std::string>* string_vec);
	bool get_process_name(DWORD process_id, std::string* process_name);
	void get_process_data(ProcessDataStruct* process_data);
	LPWSTR to_lpwstr(std::string s);
};

