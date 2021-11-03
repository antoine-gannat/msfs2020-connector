#include <iostream>
#include "commands/AltitudeStepCmd.hpp"
#include "Globals.hpp"

double Globals::g_altitudeStep = 1000;
bool Globals::g_potentioReset = false;

AltitudeStepCmd::AltitudeStepCmd(const SimConnector* connector): ACommand(connector, 0) {

}

void AltitudeStepCmd::execute(const std::string& data) {
	const int position = std::atoi(data.c_str());
	switch (position) {
		case 1:
			Globals::g_altitudeStep = 1000.0;
			Globals::g_potentioReset = false;
			std::cout << "[Command] Changing altitude change step to " << Globals::g_altitudeStep << std::endl;
			break;
		case 0:
			Globals::g_altitudeStep = 100.0;
			Globals::g_potentioReset = false;
			std::cout << "[Command] Changing altitude change step to " << Globals::g_altitudeStep << std::endl;
			break;
		case -1:
			std::cout << "[Command] Enabling potentiometer reset." << std::endl;
			Globals::g_potentioReset = true;
			break;
	}
}
