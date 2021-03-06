#include <map>
#include <iostream>
#include "CommandMapper.hpp"
// Commands
#include "commands/ACommand.hpp"
#include "commands/AltitudeCmd.hpp"
#include "commands/AltitudeStepCmd.hpp"
#include "commands/HeadingCmd.hpp"
#include "commands/SpeedCmd.hpp"
#include "commands/VSpeedCmd.hpp"
#include "commands/AutopilotSwitchCmd.hpp"
#include "commands/LandingGearCmd.hpp"
#include "commands/DisableSwitchCmd.hpp"


/*
* Map commands from the serial port to the correct Cmd class.
*/
void CommandMapper::initCommands(const SimConnector* connector) {
	this->m_commandMap.insert({ "AUTOPILOT_ALT", std::unique_ptr<ICommand>(new AltitudeCmd(connector)) });
	this->m_commandMap.insert({ "AUTOPILOT_ALT_STEP", std::unique_ptr<ICommand>(new AltitudeStepCmd(connector)) });
	this->m_commandMap.insert({ "AUTOPILOT_SPEED", std::unique_ptr<ICommand>(new SpeedCmd(connector)) });
	this->m_commandMap.insert({ "AUTOPILOT_VSPEED", std::unique_ptr<ICommand>(new VSpeedCmd(connector)) });
	this->m_commandMap.insert({ "AUTOPILOT_HEADING", std::unique_ptr<ICommand>(new HeadingCmd(connector)) });
	this->m_commandMap.insert({ "AUTOPILOT_SWITCH", std::unique_ptr<ICommand>(new AutopilotSwitchCmd(connector)) });
	this->m_commandMap.insert({ "LANDING_GEAR", std::unique_ptr<ICommand>(new LandingGearCmd(connector)) });
	this->m_commandMap.insert({ "DISABLE_SWITCH", std::unique_ptr<ICommand>(new DisableSwitchCmd(connector)) });
}

void CommandMapper::findAndExecuteCommand(const std::string& rawSerialData) {
	const size_t separatorIndex = rawSerialData.find_first_of(' ');
	if (separatorIndex == std::string::npos) {
		std::cout << "Invalid serial data:" << rawSerialData << std::endl;
		return;
	}
	const std::string commandName = rawSerialData.substr(0, separatorIndex);
	const std::string commandData = rawSerialData.substr(separatorIndex);
	std::map<std::string, std::unique_ptr<ICommand>>::iterator cmdIt = this->m_commandMap.find(commandName);
	if (cmdIt == this->m_commandMap.end()) {
		std::cout << "Command not found:" << commandName << std::endl;
		return;
	}
	ICommand* command = cmdIt->second.get();
	command->execute(commandData);
}
