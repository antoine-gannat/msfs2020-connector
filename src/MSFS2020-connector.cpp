#include <iostream>
#include <Windows.h>

#include "SimConnector.hpp"
#include "Serial.hpp"
#include "CommandMapper.hpp"

static void initDefinitions(const SimConnector* connector) {
    connector->initDefinition(E_DEFINITION::AUTOPILOT_ALT_CHANGE_DEF, E_VARIABLES::AUTOPILOT_ALT);
}

bool mainLoopRun = true;

static void mainLoop(const SimConnector* connector, Serial* serial) {
    CommandMapper commandMapper = CommandMapper();
    commandMapper.initCommands(connector);

    std::cout << "Starting main loop" << std::endl;
    while (mainLoopRun) {
        // Read serial input
        const std::string serialData = serial->read();
        // if no data is read, continue to the next loop.
        if (serialData.length() == 0) {
            continue;
        }
        commandMapper.findAndExecuteCommand(serialData);
    }
}

int main()
{
    try {
        Serial* serial = new Serial("\\\\.\\COM3");
        const SimConnector* connector = new SimConnector();

        initDefinitions(connector);

        mainLoop(connector, serial);
        return (0);
    }
    catch (std::exception error) {
        std::cerr << "An unexpected error happeneded:\n" << error.what() << std::endl;
        return (1);
    }
}