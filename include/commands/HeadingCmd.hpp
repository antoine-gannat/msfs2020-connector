#pragma once

#include "ACommand.hpp"

class HeadingCmd : public ACommand<double> {
public:
	HeadingCmd(const SimConnector* connector);
	void execute(const std::string& data);
};