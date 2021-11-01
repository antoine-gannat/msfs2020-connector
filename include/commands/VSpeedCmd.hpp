#pragma once

#include "ACommand.hpp"

class VSpeedCmd : public ACommand<double> {
public:
	VSpeedCmd(const SimConnector* connector);
	void execute(const std::string& data);
};