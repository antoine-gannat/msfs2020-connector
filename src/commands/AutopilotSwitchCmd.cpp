#include <iostream>
#include "commands/AutopilotSwitchCmd.hpp"

AutopilotSwitchCmd::AutopilotSwitchCmd(const SimConnector* connector) : ACommand<bool>(connector, 1) {}

void AutopilotSwitchCmd::execute(const std::string& data) {

}