#include <iostream>
#include "commands/LandingGearCmd.hpp"

LandingGearCmd::LandingGearCmd(const SimConnector* connector) : ACommand(connector, 0, 0, 1) {}

void LandingGearCmd::execute(const std::string& data) {
    // check for a diff in the value, and if none is found leave
    if (!this->updateDigitalValue(data)) {
        return;
    }
    const int valToSet = this->m_currentVal == -1 ? 0 : this->m_currentVal;
    std::cout << "[Command] Changing landing gear position to : " << valToSet << std::endl;
    // Update the sim
    this->m_connector->sendEvent(E_DEFINITION::LANDING_GEAR_CHANGE_DEF, valToSet);
}