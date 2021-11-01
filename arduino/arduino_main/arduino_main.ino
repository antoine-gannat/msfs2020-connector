void setup() {
  Serial.begin(9600); // open the serial port at 9600 bps:
}

void readAndWritePotentio(const String cmdName, const int pin){
  const int val = analogRead(pin);
  Serial.println(cmdName + " " + val);
}

void speedControl() {
  const String cmd = "AUTOPILOT_SPEED";
  const int pin = 0;
  readAndWritePotentio(cmd, pin);
}

void headingControl() {
  const String cmd = "AUTOPILOT_HEADING";
  const int pin = 1;
  readAndWritePotentio(cmd, pin);
}

void altControl() {
  const String cmd = "AUTOPILOT_ALT";
  const int pin = 2;
  readAndWritePotentio(cmd, pin);
}

void verticalSpeedControl() {
  const String cmd = "AUTOPILOT_VSPEED";
  const int pin = 3;
  readAndWritePotentio(cmd, pin);
}

void loop() {
  speedControl();
  headingControl();
  altControl();
  verticalSpeedControl();
  delay(10);
}
 
