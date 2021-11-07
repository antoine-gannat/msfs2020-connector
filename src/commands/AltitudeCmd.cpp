#include <iostream>
#include "commands/AltitudeCmd.hpp"
#include "Globals.hpp"

AltitudeCmd::AltitudeCmd(const SimConnector* connector): ACommand(connector, Globals::g_altitudeStep, 0, 50000) {}

void AltitudeCmd::execute(const std::string &data) {
    this->m_step = Globals::g_altitudeStep;
    // check for a diff in the value, and if none is found leave
    if (!this->updateAnalogValue(data)) {
        return;
    }
    std::cout << "[Command] Changing altitude to : " << this->m_currentVal << std::endl;
    // Update the sim
    this->m_connector->sendEvent(E_DEFINITION::AUTOPILOT_ALT_SELECTED_DEF, 1);
    this->m_connector->sendEvent(E_DEFINITION::AUTOPILOT_ALT_CHANGE_DEF, this->m_currentVal);
}