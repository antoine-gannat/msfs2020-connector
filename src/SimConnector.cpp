#include <exception>
#include <iostream>
#include "SimConnector.hpp"

SimConnector::SimConnector() {
	if (SimConnect_Open(&this->m_handle, "Sim Connector", this->m_hwnd, 0, nullptr, 0) != S_OK) {
		throw std::exception("Failed to connect to the simulator.");
	}
	std::cout << "[Success] Connected to the flight simulator." << std::endl;
}

SimConnector::~SimConnector() {
	SimConnect_Close(this->m_handle);
}

bool SimConnector::initDefinition(const E_DEFINITION definition, const VariableInfo var) const {
	if (!var.isEvent) {
		if (SimConnect_AddToDataDefinition(this->m_handle, definition, var.name.c_str(), var.unit.c_str()) != S_OK) {
			return false;
		}
	}
	else {
		if (SimConnect_MapClientEventToSimEvent(this->m_handle, definition, var.name.c_str()) != S_OK) {
			return false;
		}
	}
	return true;
}


bool SimConnector::sendEvent(const E_DEFINITION definition, DWORD data) const {
	if (SimConnect_TransmitClientEvent(this->m_handle, SIMCONNECT_OBJECT_ID_USER, definition, data, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY) != S_OK) {
		return false;
	}
	return true;
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