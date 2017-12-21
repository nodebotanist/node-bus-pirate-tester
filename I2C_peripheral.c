#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>
#include <avr/interrupt.h>
#include "I2C.h"
#include "UART.h"

void setup() {
  uint8_t address = 0x3F;
  I2C_init();
  I2C_peripheral_start(address);
}