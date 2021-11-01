#include <iostream>
#include "commands/SpeedCmd.hpp"

SpeedCmd::SpeedCmd(const SimConnector* connector) : ACommand(connector, 10.0) {}

void SpeedCmd::execute(const std::string& data) {
    // check for a diff in the value, and if none is found leave
    if (!this->updateValueFromPotentio(data)) {
        return;
    }
    std::cout << "[Command] Changing speed to : " << this->m_currentVal << std::endl;
    // Update the sim
    this->m_connector->writeSimData(E_DEFINITION::AUTOPILOT_SPEED_CHANGE_DEF, sizeof(this->m_currentVal), &this->m_currentVal);
}