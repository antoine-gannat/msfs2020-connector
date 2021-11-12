#include <iostream>
#include "commands/HeadingCmd.hpp"

HeadingCmd::HeadingCmd(const SimConnector* connector) : ACommand(connector, 1, 0, 360, true), m_lastHeadingEnabledAtVal(-1) {}

void HeadingCmd::execute(const std::string& data) {
    // check for a diff in the value, and if none is found leave
    if (!this->updateAnalogValue(data)) {
        return;
    }
    std::cout << "[Command] Changing heading to : " << this->m_currentVal << std::endl;

    // only select heading if the value has changed quite a bit
    if (this->m_lastHeadingEnabledAtVal == -1 || abs(this->m_lastHeadingEnabledAtVal - this->m_currentVal) > 3) {
        this->m_lastHeadingEnabledAtVal = this->m_currentVal;
        this->m_connector->sendEvent(E_DEFINITION::AUTOPILOT_HEADING_SELECTED_DEF, 1);
    }
    // Update the sim
    this->m_connector->sendEvent(E_DEFINITION::AUTOPILOT_HEADING_CHANGE_DEF, static_cast<DWORD>(this->m_currentVal));
}