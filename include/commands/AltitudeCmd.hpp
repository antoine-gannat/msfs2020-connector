#pragma once

#include "ACommand.hpp"

class AltitudeCmd: public ACommand<double> {
public:
	AltitudeCmd(const SimConnector *connector);
	void execute(const std::string& data);
};