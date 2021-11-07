#include <iostream>
#include "commands/AltitudeCmd.hpp"
#include "Globals.hpp"

AltitudeCmd::AltitudeCmd(const SimConnector* connector): ACommand(connector, 100.0, 0, 50000) {}

void AltitudeCmd::execute(const std::string &data) {
    this->m_step = Globals::g_altitudeStep;
    // check for a diff in the value, and if none is found leave
    if (!this->updateAnalogValue(data)) {
        return;
    }
    std::cout << "[Command] Changing altitude to : " << this->m_currentVal << std::endl;
    // Update the sim
    this->m_connector->writeSimData(E_DEFINITION::AUTOPILOT_ALT_CHANGE_DEF, sizeof(this->m_currentVal), &this->m_currentVal);
}