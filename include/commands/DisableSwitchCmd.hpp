#pragma once

#include "ACommand.hpp"

class DisableSwitchCmd : public ACommand<int> {
public:
	DisableSwitchCmd(const SimConnector* connector);
	void execute(const std::string& data);
};