# msfs2020-connector

**Project in Alpha**

Project to connect an arduino to Microsoft Flight Simulator 2020.


## Features

This repository contains the code for:
- The simulator-connector, which communicates directly to the simulartor by using the MSFS SDK
- The arduino code, which reads the value of buttons, switches and potentiometers and display an output to a serial port


## How to use

### Arduino side

Take the code under the `arduino` folder and upload it to an arduino card (you'll have to figure out the hardware part).

### Simulator connector

Build the Visual Studio project and run it.
**Note**: By default the COM port 3 is used, you will have to modify the code if you are using an other port.

