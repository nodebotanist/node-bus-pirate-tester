# Node-Bus-Pirate Tester

This is meant to be a hardware tester for the (node-bus-pirate)[https://github.com/nodebotanist/node-bus-pirate] library.

## What you'll need

* An Atmel AVR chip-- I recommend the ATMega328p. You can get them for about $2/chip
* An AVR programmer-- I use the SparkFun Pocket programmer
* Some breadboarding wires
* A Bus Pirate v3 or v4
* Node.JS to run the tests
* AVR-GCC and AVRDUDE or (AVRGIRL-usbtinyisp)[https://github.com/noopkat/avrgirl-usbtinyisp] to flash the firmware

## How to intall the firmware

make all

If you don't have (AVRGIRL-usbtinyisp)[https://github.com/noopkat/avrgirl-usbtinyisp] installed:

make main.hex
make flash-avrdude

### Other makefile commands

* erase -- uses (AVRGIRL-usbtinyisp)[https://github.com/noopkat/avrgirl-usbtinyisp] to erase the chip
* clean -- remaves all intermediary files and main.hex from the build directory

## Note on language

While I will not change the language from third-party libraries, I dislike "master" and "slave" and use the terms "root" and "peripheral" whenever possible.

## Roadmap

* Makfile will check chip signature
* I2C peripheral emulation
* SPI peripheral emulation
* Flash with 
* UART peripheral emulation
* Allow bus pirate to swap modes
* Write Node tests against AVR device
