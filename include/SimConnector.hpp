#pragma once

#include <Windows.h>
#include <SimConnect.h>
#include <map>
#include <string>

enum E_DEFINITION {
	AUTOPILOT_ALT_CHANGE_DEF,
	AUTOPILOT_SPEED_CHANGE_DEF,
	AUTOPILOT_VSPEED_CHANGE_DEF,
	AUTOPILOT_HEADING_CHANGE_DEF,
	AUTOPILOT_SWITCH_CHANGE_DEF
};

enum E_VARIABLES {
	AUTOPILOT_SWITCH,
	AUTOPILOT_ALT,
	AUTOPILOT_SPEED,
	AUTOPILOT_VSPEED,
	AUTOPILOT_HEADING
};

typedef struct s_variableInfo {
	std::string name;
	std::string unit;
	bool isEvent;
} VariableInfo;

typedef std::map<E_VARIABLES, s_variableInfo> VarsMap;


class SimConnector {
public:
	SimConnector();
	~SimConnector();

	bool initDefinition(const E_DEFINITION definition, const E_VARIABLES variable) const;
	bool sendEvent(const E_DEFINITION definition, DWORD data = 0) const;
	DWORD readSimData() const;
	bool writeSimData(const E_DEFINITION definition, const DWORD dataSize, void *data) const;

private:
	HANDLE m_handle;
	HWND m_hwnd;
};