#include <iostream>
#include "commands/DisableSwitchCmd.hpp"
#include "Globals.hpp"

bool Globals::g_potentioReset = false;

DisableSwitchCmd::DisableSwitchCmd(const SimConnector* connector) : ACommand(connector, -1) {}

void DisableSwitchCmd::execute(const std::string& data) {
    // check for a diff in the value, and if none is found leave
    if (!this->updateDigitalValue(data)) {
        return;
    }
    const bool newVal = static_cast<bool>(this->m_currentVal);
    Globals::g_potentioReset = newVal;

    std::cout << "[Command] Changing disable switch to : " << newVal << std::endl;
}