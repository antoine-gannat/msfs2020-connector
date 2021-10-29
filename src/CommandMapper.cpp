#include <map>
#include <iostream>
#include "CommandMapper.hpp"
// Commands
#include "commands/ACommand.hpp"
#include "commands/AltitudeCmd.hpp"

void CommandMapper::initCommands(const SimConnector* connector) {
	this->m_commandMap.insert({ "AUTOPILOT_ALT", std::unique_ptr<ACommand>(new AltitudeCmd(connector))});
}

void CommandMapper::findAndExecuteCommand(const std::string& rawSerialData) {
	const size_t separatorIndex = rawSerialData.find_first_of(' ');
	if (separatorIndex == std::string::npos) {
		std::cerr << "Invalid serial data:" << rawSerialData << std::endl;
		return;
	}
	const std::string commandName = rawSerialData.substr(0, separatorIndex);
	const std::string commandData = rawSerialData.substr(separatorIndex);
	std::map<std::string, std::unique_ptr<ACommand>>::iterator cmdIt = this->m_commandMap.find(commandName);
	if (cmdIt == this->m_commandMap.end()) {
		std::cerr << "Command not found:" << commandName << std::endl;
		return;
	}
	ACommand *command = cmdIt->second.get();
	command->execute(commandData);
}
