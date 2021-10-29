#pragma once

#include <Windows.h>
#include <SimConnect.h>
#include <map>
#include <string>

enum E_DEFINITION {
	AUTOPILOT_ALT_CHANGE_DEF
};

enum E_VARIABLES {
	AUTOPILOT_ALT
};

typedef struct s_variableInfo {
	std::string name;
	std::string unit;
} VariableInfo;

typedef std::map<E_VARIABLES, s_variableInfo> VarsMap;


class SimConnector {
public:
	SimConnector();
	~SimConnector();

	bool initDefinition(const E_DEFINITION definition, const E_VARIABLES variable) const;
	bool sendEvent() const;
	DWORD readSimData() const;
	bool writeSimData(const E_DEFINITION definition, const DWORD dataSize, void *data) const;

private:
	HANDLE m_handle;
	HWND m_hwnd;
};