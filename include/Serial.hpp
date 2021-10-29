#pragma once

class Serial {
public:
	Serial(const std::string& comPort);
	~Serial();

	// Read a string from the serial port
	std::string read();
private:
	HANDLE m_serialHandle;
	std::string m_tmpBuffer;
};