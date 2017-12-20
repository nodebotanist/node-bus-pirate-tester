#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>
#include <avr/interrupt.h>
#include "I2C.h"
#include "UART.h"

void setup(){
  uart_init();
  uart_print_string("Welcome to the Bus Pirate Testing Peripheral");
  uart_print_string("-----------");
  uart_print_string("Attach the Bus Pirate to the Peripheral and run the associated suite of tosts as shown in the project README.md");
}

int main(){
  setup();

  // set direction of PB0 to output
  DDRB |= (1 << PB0);

  while(1){
    PORTB = 0b00000001;
    _delay_ms(1000);
    PORTB = 0b00000000;
    _delay_ms(1000);
  }
}
