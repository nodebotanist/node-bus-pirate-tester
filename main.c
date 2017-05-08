#include "libs/avr-i2c-slave/I2CSlave.h"

#define I2C_ADDRESS 0x1C

volatile uint8_t stored_i2c_data;

void I2C_recieved(uint8_t data){
  stored_i2c_data = data;
}

void I2C_requested(){
  I2C_transmitByte(stored_i2c_data);
}

void setup(){
  I2C_setCallbacks(I2C_recieved, I2C_requested);
  I2C_init(I2C_ADDRESS);
}

int main(){
  setup();

  while(1){}
}
