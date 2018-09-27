#include "ProcessData.h"
#include <cstring>

using namespace std;

ProcessData::ProcessData()
{
}

ProcessData::~ProcessData()
{
}

HRESULT get_audio_session(IAudioSessionManager2** out) {
	HRESULT hr = S_OK;

	IMMDevice *device;
	IMMDeviceEnumerator *device_enum;
	IAudioSessionManager2 *session_manager;

	hr = CoInitialize(NULL);

	hr = CoCreateInstance(
		__uuidof(MMDeviceEnumerator),
		NULL,
		CLSCTX_ALL,
		__uuidof(IMMDeviceEnumerator),
		(void**)&device_enum
	);

	hr = device_enum->GetDefaultAudioEndpoint(
		eRender,
		eMultimedia,
		&device
	);

	hr = device->Activate(
		__uuidof(IAudioSessionManager2),
		CLSCTX_ALL,
		NULL,
		(void**)&session_manager
	);

	*(out) = session_manager;
	(*out)->AddRef();

	return hr;
}

vector<AudioSessionData> ProcessData::get_session_data() {
	vector<AudioSessionData> session_data;

	IAudioSessionManager2 *session_manager;
	IAudioSessionEnumerator *session_enum;
	IAudioSessionControl *session_control;

	get_audio_session(&session_manager);

	session_manager->GetSessionEnumerator(&session_enum);

	int session_count;
	session_enum->GetCount(&session_count);

	vector<pair<IAudioSessionControl*, IAudioSessionControl2*>> audio_sessions;
	vector<HRESULT> hr_v;

	for (int i = 0; i < session_count; i++) {
		IAudioSessionControl *audio_session;
		IAudioSessionControl2 *audio_session_2;
		session_enum->GetSession(i, &audio_session);
		audio_session->QueryInterface<IAudioSessionControl2>(&audio_session_2);
		audio_sessions.push_back(pair<IAudioSessionControl*, IAudioSessionControl2*>(audio_session, audio_session_2));
	}

	vector<ISimpleAudioVolume*> volumes;

	for (int i = 0; i < audio_sessions.size(); i++) {
		AudioSessionData data;

		ISimpleAudioVolume* p_sv;
		IAudioSessionControl* session_control = audio_sessions[i].first;

		hr_v.push_back(session_control->QueryInterface<ISimpleAudioVolume>(&p_sv));

		data.simple_audio_volume = p_sv;

		volumes.push_back(p_sv);

		float master_volume;
		p_sv->GetMasterVolume(&master_volume);

		data.master_volume = master_volume;

		IAudioSessionControl2* session_control_2 = audio_sessions[i].second;

		DWORD process_id;

		session_control_2->GetProcessId(&process_id);

		if (process_id != 0) {
			ProcessDataStruct process_data;
			process_data.process_id = process_id;
			get_process_data(&process_data);

			data.path = process_data.process_name;

			vector<string> s_v;
			split_string(process_data.process_name, '\\', &s_v);
			data.process_name = s_v[s_v.size() - 1];
			data.process_name.erase(data.process_name.end() - 4, data.process_name.end());
			data.process_name[0] = toupper(data.process_name[0]);

			session_data.push_back(data);
		}
	}

	return session_data;
}


void ProcessData::split_string(string input, char delimiter, vector<string>* string_vec) {
	string temp = "";
	for (int i = 0; i < input.length(); i++) {
		char character = input[i];
		if (character == delimiter) {
			string_vec->push_back(temp);
			temp = "";
		}
		else temp += character;
	}
	if (temp != "") string_vec->push_back(temp);
}

bool ProcessData::get_process_name(DWORD process_id, string* process_name) {
	HANDLE process_handle = OpenProcess(
		PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
		FALSE,
		process_id
	);
	if (process_handle) {
		TCHAR buffer[MAX_PATH];
		if (GetModuleFileNameEx(process_handle, 0, buffer, MAX_PATH)) {
			int i = 0;
			while (buffer[i] != '\0') {
				*process_name += buffer[i++];
			}
			return true;
		}
	}
	else return false;
}

void ProcessData::get_process_data(ProcessDataStruct* process_data) {
	DWORD process_id = process_data->process_id;
	get_process_name(process_id, &process_data->process_name);
}

LPWSTR ProcessData::to_lpwstr(string s) {
	WCHAR out[256];
	wstring wide_string = wstring(s.begin(),s.end());
	int i = 0;
	while (wide_string[i] != NULL) {
		out[i] = wide_string[i++];
	}
	return out;
}