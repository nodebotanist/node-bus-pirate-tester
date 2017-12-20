#include <avr/io.h>
#include <util/twi.h>
#include <avr/interrupt.h>
#include "I2C.h"
#include "pins.h"

void I2C_init(uint8_t multiplier){
  TWBR = 32 / multiplier;
  TWCR |= (1 << TWEN); //enable I2C
}

void I2C_wait_for_complete(void){
  loop_until_bit_is_set(TWCR, TWINT);
}

void I2C_main_start(void){
  TWCR = (_BV(TWINT) | _BV(TWEN) | _BV(TWSTA));
  I2C_wait_for_complete();
}

void I2C_main_stop(void){

}

uint8_t I2C_main_read(void){
  return 0;
}

void I2C_send(uint8_t data){

}

void I2C_peripheral_start(void){

}

void I2C_peripheral_stop(void){

}

ISR(TWI_vect){

}