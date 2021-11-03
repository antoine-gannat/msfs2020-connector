#pragma once

#include "ACommand.hpp"

class LandingGearCmd : public ACommand<int> {
public:
	LandingGearCmd(const SimConnector* connector);
	void execute(const std::string& data);
};