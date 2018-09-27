#include "SerialIn.h"

SerialIn::SerialIn()
{
	this->connected = false;
}

SerialIn::~SerialIn()
{
	if (this->connected) {
		this->connected = false;
		CloseHandle(this->handle);
		readThread.join();
	}
}

bool SerialIn::connect(char* portName) {
	if (!connected) {
		this->handle = CreateFileA(static_cast<LPCSTR>(portName),
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (this->handle == INVALID_HANDLE_VALUE) {
			if (GetLastError() == ERROR_FILE_NOT_FOUND) {
				printf("ERROR: Handle was not attached. Reason: %s not available\n", portName);
			}
			else
			{
				printf("ERROR!!!");
			}
		}
		else {
			DCB dcbSerialParameters = { 0 };

			if (!GetCommState(this->handle, &dcbSerialParameters)) {
				printf("failed to get current serial parameters");
			}
			else {
				dcbSerialParameters.BaudRate = CBR_115200;
				dcbSerialParameters.ByteSize = 8;
				dcbSerialParameters.StopBits = ONESTOPBIT;
				dcbSerialParameters.Parity = NOPARITY;
				dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

				if (!SetCommState(handle, &dcbSerialParameters))
				{
					printf("ALERT: could not set Serial port parameters\n");
				}
				else {
					this->connected = true;
					PurgeComm(this->handle, PURGE_RXCLEAR | PURGE_TXCLEAR);
					COMMTIMEOUTS timeouts = { 0,0,10,0,0 };
					SetCommTimeouts(handle, &timeouts);
					Sleep(ARDUINO_WAIT_TIME);
					readThread = std::thread(&SerialIn::readThreadMethod, this);
				}
			}
		}
	}	
	return connected;
}

void SerialIn::set_slider(QSlider * slider, int channel)
{
	sliders[channel] = slider;
}

bool SerialIn::readByte(int* byte)
{
	DWORD bytesRead;
	unsigned const int toRead = 1;
	unsigned char buffer[toRead] = { 0 };

	ClearCommError(this->handle, &this->errors, &this->status);

 	if (ReadFile(this->handle, &buffer, toRead, &bytesRead, NULL)) {
		*byte = buffer[0];
		return true;
	}
	return false;
}

bool SerialIn::writeSerialPort(char *buffer, unsigned int buf_size)
{
	DWORD bytesSend;

	if (!WriteFile(this->handle, (void*)buffer, buf_size, &bytesSend, 0)) {
		ClearCommError(this->handle, &this->errors, &this->status);
		return false;
	}
	else return true;
}

bool SerialIn::isConnected()
{
	return this->connected;
}

void SerialIn::queue_image(std::vector<std::vector<RGBColor>> image, unsigned char channel)
{
	SerialMessage message = { channel, image };
	image_queue.push(message);
}

void SerialIn::readThreadMethod( void ) {
	while (connected) {
		int byte;
		do {
			if (!image_queue.empty()) send_images();
			Sleep(5);
			readByte(&byte);
		} while (byte != flag && connected);
		if (connected) {
			while (!readByte(&byte));
			unsigned char channel = byte;

			while (!readByte(&byte));
			unsigned char value = byte * 100 / 255;

			if (sliders[channel] != 0) sliders[channel]->setValue((int)value);
			std::cout << "Channel " << (int)channel << " changed to " << (int)value << ".\n";
		}
	}
}

void send_char(unsigned char value, HANDLE handle) {
	WriteFile(handle, &value, 1, NULL, NULL);
}

bool SerialIn::send_images()
{
	//TODO
	SerialMessage message = image_queue.front();

	unsigned char image_width = message.image[0].size();
	unsigned char image_height = message.image.size();

	send_char(message.channel, handle);
	send_char(image_width, handle);
	send_char(image_height, handle);
	Sleep(10);

	int answer = -1;
	while (answer == -1) readByte(&answer);
	if (answer == SERIAL_IN_ACK) {
		for (int y = 0; y < image_height; y++) {
			for (int x = 0; x < image_width; x++) {
				if (message.image[y][x].r != 170) send_char(message.image[y][x].r, handle);
				else for (int i = 0; i < 2; i++) send_char(170, handle);
				if (message.image[y][x].g != 170) send_char(message.image[y][x].g, handle);
				else for (int i = 0; i < 2; i++) send_char(170, handle);
				if (message.image[y][x].b != 170) send_char(message.image[y][x].b, handle);
				else for (int i = 0; i < 2; i++) send_char(170, handle);
				Sleep(2);
			}
			send_char(SERIAL_OUT_FUNC, handle);
			if (y == image_height - 1) send_char(SERIAL_OUT_EOI, handle);
			else send_char(SERIAL_OUT_EOR, handle);

			answer = -1;
			while (answer == -1) readByte(&answer);
			if (answer != SERIAL_IN_ACK) y--;
			Sleep(5);
		}
		image_queue.pop();

	}
	return true;
}
