#include <iostream>
#include "commands/AltitudeCmd.hpp"

AltitudeCmd::AltitudeCmd(const SimConnector* connector): ACommand(connector), m_lastPotentioVal(0), m_currentAltitude(5000), m_feetPerChange(1000.0) {}

void AltitudeCmd::execute(const std::string &data) {
    unsigned short potentioVal = std::atoi(data.c_str());
    double newAlt = this->m_currentAltitude;

    // if the value hasn't changed, leave
    if (abs(this->m_lastPotentioVal - potentioVal) < 3) {
        return;
    }

    // if increase
    if (potentioVal > this->m_lastPotentioVal) {
        newAlt += this->m_feetPerChange;
    }
    else if (potentioVal < this->m_lastPotentioVal) {
        newAlt -= this->m_feetPerChange;
    }

    // update the store variables
    this->m_lastPotentioVal = potentioVal;
    this->m_currentAltitude = newAlt;
    std::cout << "[Command] Changing altitude to : " << newAlt << std::endl;
    // Update the sim altitude
    this->m_connector->writeSimData(E_DEFINITION::AUTOPILOT_ALT_CHANGE_DEF, sizeof(newAlt), &newAlt);
}