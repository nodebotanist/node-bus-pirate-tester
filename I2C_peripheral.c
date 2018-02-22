#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>
#include <avr/interrupt.h>
#include "I2C.h"

uint8_t write_reg_value = 0x00
uint8_t read_reg_value[2] = [0x12, 0x34]

void setup() {
  uint8_t address = 0x3F;
  I2C_init(4);
  I2C_peripheral_start(address);
}

void read() {

}

void write() {

}

void read_from_write() {
  
}

void main() {
  
}