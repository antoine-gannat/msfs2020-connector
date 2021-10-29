
int potPin = 2;    // select the input pin for the potentiometer
int val = 0;       // variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600); // open the serial port at 9600 bps:
}

int lastVal = 0;

void loop() {
  val = analogRead(potPin);    // read the value from the sensor
  if (lastVal != val) {
    String toPrint = "AUTOPILOT_ALT ";
    Serial.println(toPrint + val);
    lastVal = val;
    delay(400);                  // stop the program for some time
  }
}
 
