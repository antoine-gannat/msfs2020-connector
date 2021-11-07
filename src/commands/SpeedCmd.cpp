#include <iostream>
#include "commands/SpeedCmd.hpp"

SpeedCmd::SpeedCmd(const SimConnector* connector) : ACommand(connector, 1.0, 0.0, 400.0) {}

void SpeedCmd::execute(const std::string& data) {
    // check for a diff in the value, and if none is found leave
    if (!this->updateAnalogValue(data)) {
        return;
    }
    std::cout << "[Command] Changing speed to : " << this->m_currentVal << std::endl;
    // Update the sim
    this->m_connector->sendEvent(E_DEFINITION::AUTOPILOT_SPEED_SELECTED_DEF, 1);
    this->m_connector->sendEvent(E_DEFINITION::AUTOPILOT_SPEED_CHANGE_DEF, (DWORD)this->m_currentVal);
}