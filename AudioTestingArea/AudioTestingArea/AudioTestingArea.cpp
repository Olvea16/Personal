// AudioTestingArea.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <audiopolicy.h>
#include <mmdeviceapi.h>
HRESULT create_session_manager(IAudioSessionManager2** audio_session_manager_p) {
	HRESULT hr = S_OK;

	IMMDeviceEnumerator *device_enumerator = NULL;
	IMMDevice *device = NULL;
	IAudioSessionManager2 *audio_session_manager = NULL;

	const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
	const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);

	CoInitialize(NULL);

	// Create the device enumerator.
	hr = CoCreateInstance(
		__uuidof(MMDeviceEnumerator),
		NULL, CLSCTX_ALL,
		__uuidof(IMMDeviceEnumerator),
		(void**)&device_enumerator);

	// Get the default audio device.
	hr = device_enumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &device);

	// Get the session manager.
	hr = device->Activate(__uuidof(IAudioSessionManager2), CLSCTX_ALL, NULL, (void**)&audio_session_manager);

	// Return the pointer to the caller.
	*(audio_session_manager_p) = audio_session_manager;

	return hr;
}

int main()
{
	IAudioSessionManager2 *audio_session_manager = NULL;
	IAudioSessionEnumerator *audio_session_enum = NULL;
	

	create_session_manager(&audio_session_manager);

	audio_session_manager->GetSessionEnumerator(&audio_session_enum);
	
	int audio_session_amount;
	audio_session_enum->GetCount(&audio_session_amount);
	//audio_session_enum->GetSession(audio_session_amount);
    return 0;
}