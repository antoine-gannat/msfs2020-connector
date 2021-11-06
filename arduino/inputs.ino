void potentio1() {
  const int pin = 0;
  submitAnalogCmd(AUTOPILOT_SPEED, pin);
}

void potentio2() {
  const int pin = 1;
  submitAnalogCmd(AUTOPILOT_HEADING, pin);
}

void potentio3() {
  const int pin = 2;
  submitAnalogCmd(AUTOPILOT_ALT, pin);
}

void potentio4() {
  const int pin = 3;
  submitAnalogCmd(AUTOPILOT_VSPEED, pin);
}


void buttonA() {
  const int pin = 47;
  // no-op
}

void buttonB() {
  const int pin = 46;
  // no-op
}

void buttonC() {
  const int pin = 45;
  submitDigitalCmd(AUTOPILOT_SWITCH, pin);
}

void lever1() {
  const int pin = 50;
  submitDigitalCmd(DISABLE_SWITCH, pin);
}

void lever2() {
  const int pin = 52;
  submitDigitalCmd(AUTOPILOT_ALT_STEP, pin);
}

void lever3() {
  const int pin = 53;
  submitDigitalCmd(LANDING_GEAR, pin);
}
