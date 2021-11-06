#define AUTOPILOT_SPEED "AUTOPILOT_SPEED"
#define AUTOPILOT_HEADING "AUTOPILOT_HEADING"
#define AUTOPILOT_ALT "AUTOPILOT_ALT"
#define AUTOPILOT_ALT_STEP "AUTOPILOT_ALT_STEP"
#define AUTOPILOT_VSPEED "AUTOPILOT_VSPEED"
#define AUTOPILOT_SWITCH "AUTOPILOT_SWITCH"
#define LANDING_GEAR "LANDING_GEAR"
#define DISABLE_SWITCH "DISABLE_SWITCH"

#define NB_CMD 10

Command commands[NB_CMD];


void setupCommands() {
  memset(commands, 0, NB_CMD);
  initCommand(AUTOPILOT_SPEED);
  initCommand(AUTOPILOT_HEADING);
  initCommand(AUTOPILOT_ALT);
  initCommand(AUTOPILOT_ALT_STEP);
  initCommand(AUTOPILOT_VSPEED);
  initCommand(AUTOPILOT_SWITCH);
  initCommand(LANDING_GEAR);
  initCommand(DISABLE_SWITCH); 
}


void initCommand(const char *cmdName){
  static unsigned short nbStateInitialized = 0;
  commands[nbStateInitialized].cmd = cmdName;
  commands[nbStateInitialized].cumulVal = NO_VALUE;
  commands[nbStateInitialized].cumul = 0;
  commands[nbStateInitialized].lastValueSent = NO_VALUE;

  nbStateInitialized++;
}

int findCommandIndex(const char *cmdName){
  for (unsigned short i = 0; i < NB_CMD; i++){
      if (strcmp(commands[i].cmd, cmdName) == 0){
        return i;
      }
  }
  return -1;
}

void updateCommandCumul(Command *command, const int val) {
      // if the cumulVal has not been initialized
    if (command->cumulVal == NO_VALUE) {
      command->cumulVal = val;
      command->cumul = 0;
    }

    if (command->cumulVal ==  val){
      command->cumul++;
    } else {
      command->cumul = 0;
      command->cumulVal = val;
    }
}
