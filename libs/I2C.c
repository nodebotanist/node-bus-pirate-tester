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
  TWCR = (_BV(TWINT) | _BV(TWEN) | _BV(TWSTO));
}

uint8_t I2C_main_read(void){
  TWCR = (_BV(TWINT) | _BV(TWEN) | _BV(TWEA));
  I2C_wait_for_complete();
  return (TWDR);
}

void I2C_send(uint8_t data){
  TWDR = data;
  TWCR = (_BV(TWINT) | _BV(TWEN));
  I2C_wait_for_complete();
}

void I2C_peripheral_start(void){
  // set I2C peripheral address
  TWAR = (address << 1);
  // Enable address matching
  // Enable I2C
  // Clear I2C interrupt
  // Enable I2C interrupt on data recieved
  TWCR = (_BV(TWIE) | _BV(TWEA) | _BV(TWINT) | _BV(TWEN));
}

void I2C_peripheral_stop(void){
  // Clear ACK and enable bits
  TWCR &= ~(_BV(TWEA) | _BV(TWEN));
}

ISR(TWI_vect){
  // temporarily store data
  uint8_t data;

  bool recieved = (TWSR & 0xF8);

  if(recieved == TW_SR_SLA_ACK) {
    // byte recieved was address of peripheral
    // prepare to recieve buffer address
    buffer_address = 0xFF;
    I2C_peripheral_ACK();
  } else if (recieved == TW_SR_DATA_ACK) {
    // data byte recieved by peripheral
    data = TWDR;

    if(buffer_address == 0xFF) {
      // first byte rceieved is buffer address
      buffer_address = data;
      I2C_peripheral_ACK();
    } else {
      input_buffer[buffer_address] = data;
      buffer_address++;

      if(buffer_address < 0xFF) {
        // If there's room left in the buffer
        I2C_peripheral_ACK();
      } else {
        I2C_peripheral_NACK();
      }
    }
  } else if (recieved == TW_ST_DATA_ACK) {
    // data requested from peripheral
    data = TWDR;
    
    if(buffer_address == 0xFF) {
      // read adress not sent yet, byte is read address
      buffer_address = data;
    }

    // copy output buffer for transmission
    TWDR = output_buffer[buffer_address];
    buffer_address++;

    if(buffer_address < 0xFF) {
      I2C_peripheral_ACK();
    } else {
      I2C_peripheral_NACK();
    }
  } else {
    // prepare peripheraal to be addressed again
    TWCR |= (1<<TWIE) | (1<<TWEA) | (1<<TWEN);
  }
}

void I2C_peripheral_ACK(void) {
    // clear interrupt
    // prepare for next byte
    // ACK
    TWCR |= (_BV(TWIE) | _BV(TWINT) | _BV(TWEN) | _BV(TWEA));
}

void I2C_peripheral_NACK(void) {
  // NACK
  TWCR &= ~(_BV(TWEA));
  // clear interrupt
  // prepare for next byte
  TWCR |= (_BV(TWIE) | _BV(TWINT) | _BV(TWEN));
}