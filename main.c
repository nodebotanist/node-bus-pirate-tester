#include <avr/io.h>
#include <util/delay.h>
#include "I2C.h"
#include "UART.h"

void setup(){
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
