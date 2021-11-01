#include <exception>
#include <iostream>
#include "SimConnector.hpp"

// map of available variables
static const VarsMap SimVariablesMap = {
	{AUTOPILOT_ALT, {"AUTOPILOT ALTITUDE LOCK VAR", "feet"}},
	{AUTOPILOT_VSPEED, {"AUTOPILOT VERTICAL HOLD VAR", "feet"}}
};


SimConnector::SimConnector() {
	if (SimConnect_Open(&this->m_handle, "Sim Connector", this->m_hwnd, 0, nullptr, 0) != S_OK) {
		throw std::exception("Failed to connect to the simulator.");
	}
	std::cout << "[Success] Connected to the flight simulator." << std::endl;
}

SimConnector::~SimConnector() {
	SimConnect_Close(this->m_handle);
}

bool SimConnector::initDefinition(const E_DEFINITION definition, const E_VARIABLES variable) const {
	VarsMap::const_iterator pos= SimVariablesMap.find(variable);
	if (pos == SimVariablesMap.end()) {
		std::cerr << "Couldn't find information on variable:" << variable << std::endl;
		return false;
	}

	VariableInfo var = pos->second;
	if (SimConnect_AddToDataDefinition(this->m_handle, definition, var.name.c_str(), var.unit.c_str()) != S_OK) {
		return false;
	}
	return true;
}


bool SimConnector::sendEvent()const {
	throw std::exception("Not implemented");
	return false;
}

DWORD SimConnector::readSimData()const {
	throw std::exception("Not implemented");
}

bool SimConnector::writeSimData(const E_DEFINITION definition, const DWORD dataSize, void* data)const {
	if (SimConnect_SetDataOnSimObject(this->m_handle, definition, SIMCONNECT_OBJECT_ID_USER, 0, 0, dataSize, data) != S_OK) {
		return false;
	}
	return true;
}