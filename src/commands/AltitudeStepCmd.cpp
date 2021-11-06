#include <iostream>
#include "commands/AltitudeStepCmd.hpp"
#include "Globals.hpp"

double Globals::g_altitudeStep = 1000;

AltitudeStepCmd::AltitudeStepCmd(const SimConnector* connector): ACommand(connector, 0) {}

void AltitudeStepCmd::execute(const std::string& data) {
	const int position = std::atoi(data.c_str());
	switch (position) {
		case 1:
			Globals::g_altitudeStep = 1000.0;
			break;
		case 0:
			Globals::g_altitudeStep = 100.0;
			break;
		default:
			return;
	}
	std::cout << "[Command] Changing altitude change step to " << Globals::g_altitudeStep << std::endl;
}
