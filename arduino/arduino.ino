#include <stdio.h>
#include <stdlib.h>

#define NO_VALUE -42

typedef struct s_Command {
  const char *cmd;
  unsigned int cumulVal;
  unsigned int cumul;
  int lastValueSent;
} Command;

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

  setupCommands();
}

void loop() {
  // check the value from lever
  lever1();
  lever2();
  lever3();

  // check the value from potentiometers
  potentio1();
  potentio2();
  potentio3();
  potentio4();

  // check the value from buttons
  buttonA();
  buttonB();
  buttonC();
}
 
