#pragma once

#include <vector>

class Serial {
public:
	Serial();
	~Serial();

	// Read a string from the serial port
	std::string read();
private:
	HANDLE m_serialHandle;
	std::string m_tmpBuffer;
	std::vector<std::string> m_storedData;
};