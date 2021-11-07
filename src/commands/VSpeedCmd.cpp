#include <iostream>
#include "commands/VSpeedCmd.hpp"

VSpeedCmd::VSpeedCmd(const SimConnector* connector): ACommand<double>(connector, 10.0, -5000.0, 5000.0) {}

void VSpeedCmd::execute(const std::string& data) {
    // check for a diff in the value, and if none is found leave
    if (!this->updateAnalogValue(data)) {
        return;
    }
    std::cout << "[Command] Changing vertical speed to : " << this->m_currentVal << std::endl;
    // divide by 60 to match the in-game value
    double valToSend = this->m_currentVal / 60;
    // Update the sim
    this->m_connector->writeSimData(E_DEFINITION::AUTOPILOT_VSPEED_CHANGE_DEF, sizeof(valToSend), &valToSend);
}