#pragma once

#include "ACommand.hpp"

class SpeedCmd : public ACommand<double> {
public:
	SpeedCmd(const SimConnector* connector);
	void execute(const std::string& data);
};