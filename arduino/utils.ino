#define MIN_CUMUL_TO_SEND 200
#define MIN_ANALOG_DIFF_THRESHOLD 3

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

// Submit an analog command, duplicates value will not be sent.
void submitAnalogCmd(const char *cmdName, const int pin) {
  const int val = analogRead(pin);
  const int cmdIndex = findCommandIndex(cmdName);
  if (cmdIndex == -1) {
    return;
  }
  Command *command = &commands[cmdIndex];

  const int lastValueSent = command->lastValueSent;
  const bool isInErrorThreshold = abs(val - lastValueSent) <= MIN_ANALOG_DIFF_THRESHOLD;
  
  // avoid spamming with the same value over and over again
  if (!isInErrorThreshold || lastValueSent == NO_VALUE){
    printCmd(cmdName, val);
    command->lastValueSent = val;
  }
}

// Submit a digital command, duplicates value will not be sent.
void submitDigitalCmd(const char *cmdName, const int pin) {
  const int val = digitalRead(pin);
  const int cmdIndex = findCommandIndex(cmdName);
  if (cmdIndex == -1) {
    return;
  }
  Command *command = &commands[cmdIndex];
  const int lastValueSent = command->lastValueSent;
  const bool valIsDiffFromLastSent = lastValueSent != val;
  const bool valueHasBeenStable = command->cumul >= MIN_CUMUL_TO_SEND && command->cumulVal ==  val;
  const bool lastValueSentHasNotBeenInitialized = lastValueSent == NO_VALUE;

  // update the cumul if the value is not stable
  if (!valueHasBeenStable) {
    updateCommandCumul(command, val);
  }
  // only send a command if the value has been the same for over MIN_CUMUL_TO_SEND times
  if ((valIsDiffFromLastSent && valueHasBeenStable) || lastValueSentHasNotBeenInitialized){
    printCmd(cmdName, val);
    command->lastValueSent = val;
  }
}
