#pragma once

#include <string>
#include "SimConnector.hpp"

class ACommand {
public:
	ACommand(const SimConnector* connector);
	virtual void execute(const std::string &data) = 0;

protected:
	const SimConnector *m_connector;
};