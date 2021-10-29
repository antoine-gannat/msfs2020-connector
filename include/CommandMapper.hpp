#pragma once

#include <string>
#include <map>
#include <memory>
#include "commands/ACommand.hpp"

class CommandMapper {
public:
	void initCommands(const SimConnector *connector);
	void findAndExecuteCommand(const std::string& rawSerialData);

private:
	std::map<std::string, std::unique_ptr<ACommand>> m_commandMap;
};