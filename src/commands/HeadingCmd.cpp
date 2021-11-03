#include <iostream>
#include "commands/HeadingCmd.hpp"

HeadingCmd::HeadingCmd(const SimConnector* connector) : ACommand(connector, 1000.0) {}

void HeadingCmd::execute(const std::string& data) {
    // check for a diff in the value, and if none is found leave
    if (!this->updateAnalogValue(data)) {
        return;
    }
    std::cout << "[Command] Changing heading to : " << this->m_currentVal << std::endl;
    // Update the sim
    this->m_connector->writeSimData(E_DEFINITION::AUTOPILOT_HEADING_CHANGE_DEF, sizeof(this->m_currentVal), &this->m_currentVal);

}