#pragma once

#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH 255

#include "IconManager.h"

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <unordered_map>
#include <queue>

//Qt stuff
#include <qslider.h>

#define SERIAL_OUT_FUNC 170
#define SERIAL_OUT_EOR 1
#define SERIAL_OUT_EOI 2

#define SERIAL_IN_ACK 1
#define SERIAL_IN_NACK 2

struct SerialMessage {
	unsigned char channel;
	std::vector<std::vector<RGBColor>> image;
};

class SerialIn
{
private:
	HANDLE handle;
	bool connected;
	COMSTAT status;
	DWORD errors;
	std::thread readThread;
	std::unordered_map<int, QSlider*> sliders;
	const unsigned char flag = 170;
	std::queue<SerialMessage> image_queue;

	bool readByte(int* byte);
	bool writeSerialPort(char *buffer, unsigned int buf_size);
	void readThreadMethod( void );
	bool send_images();

public:
	SerialIn();
	~SerialIn();

	bool connect(char* buffer);
	void set_slider(QSlider* slider, int channel);
	bool isConnected();
	void queue_image(std::vector<std::vector<RGBColor>> image, unsigned char channel);
};