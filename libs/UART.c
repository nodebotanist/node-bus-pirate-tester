#include <avr/io.h>

void uart_init(void){
  //set baud rate
  UBBRH = (BAUD_RATE>>8);
  UBRRL = BAUD_RATE;
  // enable RX/TX pins
  UCSRB |= (1<<TXEN)|(1<<RXEN);
  // set transmission size to 8 bits (1 byte)
  UCSRC |= (1<<URSEL)|(1<<UCSZ0)|(1<<USCZ1)
  return;
}