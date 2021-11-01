#pragma once

#include "ACommand.hpp"

class AutopilotSwitchCmd : public ACommand<bool> {
public:
	AutopilotSwitchCmd(const SimConnector* connector);
	void execute(const std::string& data);
};