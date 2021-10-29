#include <windows.h>
#include <iostream>
#include "Serial.hpp"

static const DWORD readSize = 100;

Serial::Serial(const std::string& comPort): m_tmpBuffer("") {
	this->m_serialHandle = CreateFile(L"\\\\.\\COM3", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	// Do some basic settings
	DCB serialParams = { 0 };
	serialParams.DCBlength = sizeof(serialParams);

	GetCommState(this->m_serialHandle, &serialParams);
	serialParams.BaudRate = 9600;
	serialParams.ByteSize = 8;
	serialParams.StopBits = ONESTOPBIT;
	serialParams.Parity = NOPARITY;
	SetCommState(this->m_serialHandle, &serialParams);

	// Set timeouts
	COMMTIMEOUTS timeout = { 0 };
	timeout.ReadIntervalTimeout = 50;
	timeout.ReadTotalTimeoutConstant = 50;
	timeout.ReadTotalTimeoutMultiplier = 50;
	timeout.WriteTotalTimeoutConstant = 50;
	timeout.WriteTotalTimeoutMultiplier = 10;
	SetCommTimeouts(this->m_serialHandle, &timeout);

	std::cout << "[Success] Connected to the serial port." << std::endl;
}

Serial::~Serial() {
	CloseHandle(this->m_serialHandle);
}

std::string Serial::read() {
	DWORD nbRead;
	char buff[readSize];
	// init array
	std::memset(buff, 0, readSize);
	bool lineBreakFound = false;
	std::string result = this->m_tmpBuffer;
	// reset the tmp buffer
	this->m_tmpBuffer = "";
	while (!lineBreakFound) {
		if (!ReadFile(this->m_serialHandle, buff, readSize, &nbRead, NULL)) {
			return std::string();
		}
		for (DWORD i = 0; i < nbRead; i++) {
			// if we found data
			if (!lineBreakFound && buff[i] != '\n' && buff[i] != '\r') {
				result += buff[i];
			}
			// if end of line
			else if (!lineBreakFound && buff[i] == '\n') {
				lineBreakFound = true;
			}
			// if we have found the end of the data
			else if (lineBreakFound) {
				// append remaining of the incomming buffer to the tmp buffer
				this->m_tmpBuffer += buff[i];
			}
		}
	}
	return result;
}
