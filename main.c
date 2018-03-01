#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>
#include <avr/interrupt.h>
#include "I2C.h"
#include "UART.h"

void setup_I2C_peripheral(uint8_t multiplier, uint8_t address){
  I2C_init(multiplier);
  I2C_peripheral_start(address);
}

void setup(){
  uart_init();
  print_string("Welcome to the Bus Pirate Testing Peripheral");
  print_string("-----------");
  print_string("Attach the Bus Pirate to the Peripheral and run the associated suite of tosts as shown in the project README.md");
  setup_I2C_peripheral(4, 0x7C);
}

int main(){
  return 0;
}
