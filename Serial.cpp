#include <windows.h>
#include <iostream>

// set by default com3, to change later on
HANDLE serialHandle = CreateFile(L"\\\\.\\COM3", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

void initSerial() {
	// Do some basic settings
	DCB serialParams = { 0 };
	serialParams.DCBlength = sizeof(serialParams);

	GetCommState(serialHandle, &serialParams);
	serialParams.BaudRate = 9600;
	serialParams.ByteSize = 8;
	serialParams.StopBits = ONESTOPBIT;
	serialParams.Parity = NOPARITY;
	SetCommState(serialHandle, &serialParams);

	// Set timeouts
	COMMTIMEOUTS timeout = { 0 };
	timeout.ReadIntervalTimeout = 50;
	timeout.ReadTotalTimeoutConstant = 50;
	timeout.ReadTotalTimeoutMultiplier = 50;
	timeout.WriteTotalTimeoutConstant = 50;
	timeout.WriteTotalTimeoutMultiplier = 10;
	SetCommTimeouts(serialHandle, &timeout);
}

char* readSerial() {
	const DWORD readSize = 2048;
	DWORD nbRead;
	char buff[readSize];
	memset(buff, 0, readSize);
	if (!ReadFile(serialHandle, buff, readSize, &nbRead, NULL)) {
		return nullptr;
	}
	for (int i = 0; i < nbRead && i < readSize; i++) {
		if (buff[i] < 32) {
			buff[i] = '\0';
			break;
		}
	}
	return buff;
}

void stopSerial() {
	CloseHandle(serialHandle);
}
