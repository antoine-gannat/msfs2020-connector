#include <iostream>
#include <Windows.h>

#include "SimConnector.hpp"
#include "Serial.hpp"
#include "CommandMapper.hpp"

static void initDefinitions(const SimConnector* connector) {
    connector->initDefinition(E_DEFINITION::AUTOPILOT_ALT_CHANGE_DEF, { "AUTOPILOT ALTITUDE LOCK VAR", "feet", false });
    connector->initDefinition(E_DEFINITION::AUTOPILOT_VSPEED_CHANGE_DEF, { "AUTOPILOT VERTICAL HOLD VAR", "feet", false });
    connector->initDefinition(E_DEFINITION::AUTOPILOT_HEADING_CHANGE_DEF, { "AUTOPILOT HEADING LOCK DIR", "", false});

    // events
    connector->initDefinition(E_DEFINITION::AUTOPILOT_SWITCH_CHANGE_DEF, { "AP_MASTER", "", true });
    connector->initDefinition(E_DEFINITION::AUTOPILOT_SPEED_CHANGE_DEF, { "AP_SPD_VAR_SET", "knots", true });
    connector->initDefinition(E_DEFINITION::LANDING_GEAR_CHANGE_DEF, { "GEAR_SET", "", true });
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
        Serial* serial = new Serial();
        const SimConnector* connector = new SimConnector();

        initDefinitions(connector);

        mainLoop(connector, serial);
        return (0);
    }
    catch (std::exception error) {
        std::cerr << "An unexpected error happened:\n" << error.what() << std::endl;
        return (1);
    }
}
