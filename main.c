#include "I2CSlave.h"
#include "USART.h"

#define I2C_ADDRESS 0x1C

volatile uint8_t temp_i2c_data;
int new_register;
volatile uint8_t i2c_register;
volatile uint8_t single_storage;
volatile uint8_t multi_storage[32];
volatile uint8_t sum_storage[2];
volatile uint8_t sum;

void process_data(){
  // use register and data to figure out what to do here
  switch(i2c_register){
    case 0x00:
      // we don't have a register yet!
      break;
    case 0x1A: // save this byte into single sum_storage
      single_storage = temp_i2c_data;
  }
}

// this is called for each byte sent. Need to keep that in mind for i2c_register
void I2C_recieved(uint8_t data){
  if(i2c_register == 0x00 || new_register == 1){
    printString("Setting Register: ");
    printHexByte(data);
    printString("\n");
    i2c_register = data;
    new_register = 0;
  } else {
    printString("Saving into single byte: ");
    printHexByte(data);
    printString("\n");
    temp_i2c_data = data;
    process_data();
  }
}

void I2C_requested(){
  // use register and data to figure out what to do here
  switch(i2c_register){
    case 0x00:
      printString("No data to send");
      I2C_transmitByte(0x00);
      // we don't have a register yet!
      break;
    case 0x1A: // save this byte into single sum_storage
      printString("Sending I2C Single Storage");
      I2C_transmitByte(single_storage);
      break;
  }
}

void I2C_stop_bit(){
  //stop bit recieved
  new_register = 1;
}

void setup(){
  new_register= 1;
  i2c_register = 0x00;
  I2C_setCallbacks(I2C_recieved, I2C_requested, I2C_stop_bit);
  I2C_init(I2C_ADDRESS);
  initUSART();
}

int main(){
  setup();

  while(1){}
}
