#include <iostream>
#include "commands/VSpeedCmd.hpp"

VSpeedCmd::VSpeedCmd(const SimConnector* connector): ACommand<double>(connector, 10.0) {}

void VSpeedCmd::execute(const std::string& data) {
    // check for a diff in the value, and if none is found leave
    if (!this->updateValueFromPotentio(data)) {
        return;
    }
    std::cout << "[Command] Changing vertical speed to : " << this->m_currentVal << std::endl;
    // Update the sim
    this->m_connector->writeSimData(E_DEFINITION::AUTOPILOT_VSPEED_CHANGE_DEF, sizeof(this->m_currentVal), &this->m_currentVal);
}