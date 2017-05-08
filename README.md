# Node-Bus-Pirate Tester

This is meant to be a hardware tester for the (node-bus-pirate)[https://github.com/nodebotanist/node-bus-pirate] library.

## What you'll need

* An Atmel AVR chip-- I recommend the ATMega328p. You can get them for about $2/chip
* An AVR programmer-- I use the SparkFun Pocket programmer
* Some breadboarding wires
* A Bus Pirate v3 or v4
* Node.JS to run the tests
* AVR-GCC and AVRDUDE (for now) to flash the firmware

## How to intall the firmware

* Clone this repo
* cd into AVR-firmware
* Modify the Makefile to reflect your programmer's serial port and, if necessary, which chip you're using
* make flash

## Credits

(I2C library I used)[https://github.com/thegouger/avr-i2c-slave]

## Note on language

While I did not change the language from third-party libraries, I dislike "master" and "slave" and use the terms "root" and "peripheral" whenever possible.

## Roadmap

* I2C peripheral emulation
* SPI peripheral emulation
* Flash with (AVRGIRL-usbtinyisp)[https://github.com/noopkat/avrgirl-usbtinyisp]
* UART peripheral emulation
* Allow bus pirate to swap modes
* Write Node tests against AVR device
