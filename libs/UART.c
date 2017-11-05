#include <avr/io.h>

void uart_init(void){
  //set baud rate
  UBBRH = (BAUD_RATE>>8);
  UBRRL = BAUD_RATE;
  UCSRB |= (1<<TXEN)|(1<<RXEN);
  return;
}