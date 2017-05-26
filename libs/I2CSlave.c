#include <util/twi.h>
#include <avr/interrupt.h>

#include "I2CSlave.h"
#include "USART.h"

static void (*I2C_recv)(uint8_t);
static void (*I2C_req)();
static void (*I2C_stop_bit)();

void I2C_setCallbacks(void (*recv)(uint8_t), void (*req)(), void (*stop)())
{
  I2C_recv = recv;
  I2C_req = req;
  I2C_stop_bit = stop;
}

void I2C_init(uint8_t address)
{
  cli();
  // load address into TWI address register
  TWAR = address << 1;
  // set the TWCR to enable address matching and enable TWI, clear TWINT, enable TWI interrupt
  TWCR = (1<<TWIE) | (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
  sei();
}

void I2C_stop(void)
{
  // clear acknowledge and enable bits
  cli();
  TWCR = 0;
  TWAR = 0;
  sei();
  initUSART();
}

ISR(TWI_vect)
{
  switch(TW_STATUS)
  {
    case TW_SR_DATA_ACK:
      // received data from master, call the receive callback
      printString("Recieved data!");
      I2C_recv(TWDR);
      TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
      break;
    case TW_ST_SLA_ACK:
      // master is requesting data, call the request callback
      printString("Recieved request!");
      I2C_req();
      TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
      break;
    case TW_ST_DATA_ACK:
      printString("Recieved request!");
      // master is requesting data, call the request callback
      I2C_req();
      TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
      break;
    case TW_BUS_ERROR:
      printString("Error!");
      // some sort of erroneous state, prepare TWI to be readdressed
      TWCR = 0;
      TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
      break;
    case TW_SR_STOP:
      // stop bit recieved
      printString("recieved stop bit!");
      I2C_stop_bit();
      TWCR = (1<<TWIE) | (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
      break;
    default:
      printString("default case!");
      TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
      break;
  }
}
