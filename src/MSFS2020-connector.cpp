#include <iostream>
#include <Windows.h>

#include "SimConnector.hpp"
#include "Serial.hpp"
#include "CommandMapper.hpp"

static void initDefinitions(const SimConnector* connector) {
    // altitude
    connector->initDefinition(E_DEFINITION::AUTOPILOT_ALT_CHANGE_DEF, { "AP_ALT_VAR_SET_ENGLISH", "", true });
    connector->initDefinition(E_DEFINITION::AUTOPILOT_ALT_SELECTED_DEF, { "ALTITUDE_SLOT_INDEX_SET", "", true});

    // headinh 
    connector->initDefinition(E_DEFINITION::AUTOPILOT_HEADING_CHANGE_DEF, { "HEADING_BUG_SET", "", true });
    connector->initDefinition(E_DEFINITION::AUTOPILOT_HEADING_SELECTED_DEF, { "HEADING_SLOT_INDEX_SET", "", true });

    // vspeed
    connector->initDefinition(E_DEFINITION::AUTOPILOT_VSPEED_SELECTED_DEF, { "VS_SLOT_INDEX_SET", "", true});
    connector->initDefinition(E_DEFINITION::AUTOPILOT_VSPEED_CHANGE_DEF, { "AUTOPILOT VERTICAL HOLD VAR", "feet", false });

    // speed
    connector->initDefinition(E_DEFINITION::AUTOPILOT_SPEED_CHANGE_DEF, { "AP_SPD_VAR_SET", "", true });
    connector->initDefinition(E_DEFINITION::AUTOPILOT_SPEED_SELECTED_DEF, { "SPEED_SLOT_INDEX_SET", "", true });

    // Autopilot master
    connector->initDefinition(E_DEFINITION::AUTOPILOT_SWITCH_CHANGE_DEF, { "AP_MASTER", "", true });

    // landing gear
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
