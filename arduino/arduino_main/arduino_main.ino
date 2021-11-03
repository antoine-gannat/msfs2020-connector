#include <stdio.h>
#include <stdlib.h>

#define NB_CMD 10
#define NB_SAVED_STATES 100
#define NO_VALUE -42
#define MIN_DIFF_THRESHOLD 3

#define AUTOPILOT_SPEED "AUTOPILOT_SPEED"
#define AUTOPILOT_HEADING "AUTOPILOT_HEADING"
#define AUTOPILOT_ALT "AUTOPILOT_ALT"
#define AUTOPILOT_ALT_STEP "AUTOPILOT_ALT_STEP"
#define AUTOPILOT_VSPEED "AUTOPILOT_VSPEED"
#define AUTOPILOT_SWITCH "AUTOPILOT_SWITCH"
#define LANDING_GEAR "LANDING_GEAR"

typedef struct s_StateHistory {
  const char *cmd;
  int states[NB_SAVED_STATES];
  int lastValueSent;
} StateHistory;

StateHistory stateHistories[NB_CMD];

void setup() {
  Serial.begin(9600); // open the serial port at 9600 bps:
  pinMode(0, INPUT); // speed potentio
  pinMode(1, INPUT); // Heading potentio
  pinMode(2, INPUT); // Altitude potentio
  pinMode(3, INPUT); // Vertical speed potentio
  pinMode(45, INPUT); // Button number 3
  pinMode(46, INPUT); // Button number 2
  pinMode(47, INPUT); // Button number 1
  pinMode(50, INPUT); // Lever 1
  pinMode(52, INPUT); // Lever 2
  pinMode(53, INPUT); // Lever 3
  memset(stateHistories, 0, NB_CMD);

  initStateHistory(AUTOPILOT_SPEED);
  initStateHistory(AUTOPILOT_HEADING);
  initStateHistory(AUTOPILOT_ALT);
  initStateHistory(AUTOPILOT_ALT_STEP);
  initStateHistory(AUTOPILOT_VSPEED);
  initStateHistory(AUTOPILOT_SWITCH);
  initStateHistory(LANDING_GEAR);
}

void initStateHistory(const char *cmdName){
  static unsigned short nbStateInitialized = 0;
  memset(stateHistories[nbStateInitialized].states, 0, NB_SAVED_STATES);
  stateHistories[nbStateInitialized].cmd = cmdName;
  stateHistories[nbStateInitialized].lastValueSent = NO_VALUE;

  nbStateInitialized++;
}

int findCmdHistoryIndex(const char *cmdName){
  for (unsigned short i = 0; i < NB_CMD; i++){
      if (strcmp(stateHistories[i].cmd, cmdName) == 0){
        return i;
      }
  }
  return -1;
}

enum E_HISTORY_STATE {
  UNIQUE_HIGH,
  UNIQUE_LOW,
  DIFFERENT
};

int addValueToHistory(const int historyIndex, const int value) {
  bool isSingleValue = true;
  StateHistory *history = &stateHistories[historyIndex];
  // shift array
  for (unsigned short j = NB_SAVED_STATES - 1 ; j > 0; j--){
    if (history->states[j - 1] != value) {
      isSingleValue = false;
    }
    history->states[j] = history->states[j - 1];
  }
  history->states[0] = value;
  if (isSingleValue && value == HIGH) {
     return UNIQUE_HIGH;
  }
  else if (isSingleValue && value == LOW){
    return UNIQUE_LOW;
  }
  return DIFFERENT;
}

void printCmd(const char *cmd, const int val) {
  char valBuffer[20];
  char bufferToPrint[100];

  memset(bufferToPrint, 0, 100);
  strcpy(bufferToPrint, cmd);
  memset(valBuffer, 0, 20);
  itoa(val, valBuffer, 10);
  strcat(bufferToPrint, " ");
  strcat(bufferToPrint, valBuffer);
  Serial.println(bufferToPrint);
}

// utility

void addToHistoryAndSubmit(const char *cmdName, const int val) {
  const int historyIndex = findCmdHistoryIndex(cmdName);
  addValueToHistory(historyIndex, val);

  const int previousValueSent = stateHistories[historyIndex].lastValueSent;
  const bool isInErrorThreshold = val >= 2 ? abs(val - previousValueSent) <= MIN_DIFF_THRESHOLD : val == previousValueSent;
  // avoid spamming with the same value over and over again
  if (!isInErrorThreshold || stateHistories[historyIndex].lastValueSent == NO_VALUE){
    printCmd(cmdName, val);
    stateHistories[historyIndex].lastValueSent = val;
  }
}

void readAndWritePotentio(const char *cmdName, const int pin){
  const int val = analogRead(pin);
  addToHistoryAndSubmit(cmdName, val);
}

void readAndWriteButton(const char *cmdName, const int pin){
  const int val = digitalRead(pin);
  addToHistoryAndSubmit(cmdName, val);
}

void readAndWriteLever(const char *cmdName, const int pin){
  const int val = digitalRead(pin);
  const int historyIndex = findCmdHistoryIndex(cmdName);
  const int historyState = addValueToHistory(historyIndex, val);

  int valToSend = -1;
  if (historyState == UNIQUE_HIGH || historyState == UNIQUE_LOW) {
    valToSend = val;
  }

  // avoid spamming with the same value over and over again
  if (valToSend != stateHistories[historyIndex].lastValueSent
    || stateHistories[historyIndex].lastValueSent == NO_VALUE){
    printCmd(cmdName, valToSend);
    stateHistories[historyIndex].lastValueSent = valToSend;
  }
}

//
void speedControl() {
  const int pin = 0;
  readAndWritePotentio(AUTOPILOT_SPEED, pin);
}

void headingControl() {
  const int pin = 1;
  readAndWritePotentio(AUTOPILOT_HEADING, pin);
}

void altControl() {
  const int pin = 2;
  readAndWritePotentio(AUTOPILOT_ALT, pin);
}

void verticalSpeedControl() {
  const int pin = 3;
  readAndWritePotentio(AUTOPILOT_VSPEED, pin);
}

void buttonA() {
  const int pin = 47;
//  readAndWriteButton(cmd, pin);
}

void buttonB() {
  const int pin = 46;
//  readAndWriteButton(cmd, pin);
}

void buttonC() {
  const int pin = 45;
  readAndWriteButton(AUTOPILOT_SWITCH, pin);
}

void lever1() {
  const int pin = 50;
}

void lever2() {
  const int pin = 52;
  readAndWriteLever(AUTOPILOT_ALT_STEP, pin);
}

void lever3() {
  const int pin = 53;
  readAndWriteLever(LANDING_GEAR, pin);
}

void loop() {
  lever2();
  lever3();
  
  speedControl();
  headingControl();
  altControl();
  verticalSpeedControl();

//  buttonA();
 // buttonB();
  buttonC();
}
 
