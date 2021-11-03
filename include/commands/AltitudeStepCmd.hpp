#pragma once

#include "ACommand.hpp"

class AltitudeStepCmd : public ACommand<int> {
public:
	AltitudeStepCmd(const SimConnector* connector);
	void execute(const std::string& data);
};