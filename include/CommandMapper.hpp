#pragma once

#include <string>
#include <map>
#include <memory>

#include "SimConnector.hpp"
#include "commands/ICommand.hpp"

class CommandMapper {
public:
	void initCommands(const SimConnector *connector);
	void findAndExecuteCommand(const std::string& rawSerialData);

private:
	std::map<std::string, std::unique_ptr<ICommand>> m_commandMap;
};