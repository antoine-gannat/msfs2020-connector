#pragma once

#include <Windows.h>
#include <SimConnect.h>
#include <map>
#include <string>

enum E_DEFINITION {
	AUTOPILOT_ALT_CHANGE_DEF,
	AUTOPILOT_ALT_SELECTED_DEF,
	AUTOPILOT_SPEED_CHANGE_DEF,
	AUTOPILOT_SPEED_SELECTED_DEF,
	AUTOPILOT_VSPEED_CHANGE_DEF,
	AUTOPILOT_VSPEED_SELECTED_DEF,
	AUTOPILOT_HEADING_CHANGE_DEF,
	AUTOPILOT_HEADING_SELECTED_DEF,
	AUTOPILOT_SWITCH_CHANGE_DEF,
	LANDING_GEAR_CHANGE_DEF
};

typedef struct s_variableInfo {
	std::string name;
	std::string unit;
	bool isEvent;
} VariableInfo;

class SimConnector {
public:
	SimConnector();
	~SimConnector();

	bool initDefinition(const E_DEFINITION definition, const VariableInfo var) const;
	bool sendEvent(const E_DEFINITION definition, DWORD data = 0) const;
	DWORD readSimData() const;
	bool writeSimData(const E_DEFINITION definition, const DWORD dataSize, void *data) const;

private:
	HANDLE m_handle;
	HWND m_hwnd;
};