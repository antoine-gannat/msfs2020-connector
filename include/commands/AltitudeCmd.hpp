#pragma once

#include "ACommand.hpp"

class AltitudeCmd: public ACommand {
public:
	AltitudeCmd(const SimConnector *connector);
	void execute(const std::string& data);

private:
	unsigned short m_lastPotentioVal;
	double m_currentAltitude;
	const double m_feetPerChange;
};