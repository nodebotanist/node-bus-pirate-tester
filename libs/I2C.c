#include <avr/io.h>
#include "I2C.h"
#include "pins.h"

void I2C_init(uint8_t multiplier){
  TWBR = 32 / multiplier;
  TWCR |= (1 << TWEN); //enable I2C
}

void I2C_wait_for_complete(void){
  loop_until_bit_is_set(TWCR, TWINT);
}

void I2C_start(void){
  TWCR = (_BV(TWINT) | _BV(TWEN) | _BV(TWSTA));
  I2C_wait_for_complete();
}