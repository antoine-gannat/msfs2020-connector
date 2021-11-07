#include <iostream>
#include "commands/AutopilotSwitchCmd.hpp"

AutopilotSwitchCmd::AutopilotSwitchCmd(const SimConnector* connector) : ACommand<bool>(connector, 1, 0, 1) {}

void AutopilotSwitchCmd::execute(const std::string& data) {
	if (!this->updateDigitalValue(data)) {
		return;
	}
	std::cout << "Switching AP " << this->m_currentVal << std::endl;
	this->m_connector->sendEvent(E_DEFINITION::AUTOPILOT_SPEED_CHANGE_DEF, (DWORD)this->m_currentVal);
}