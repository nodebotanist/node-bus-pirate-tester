#include <Wire.h>

int x = 0;

void setup(){
  // Set up I2C peripheral at address 0x09
  Wire.begin(9);
  // Event handler for receiving I2C data
  Wire.onReceive(receiveData);
}

void receiveData(int bytes){
  switch(x){
  // if value is 0x01, send back 0x01
  case 1:
    Wire.write(0x01);
    break;
  // if value is 0x02, send back 0x03 0x04 0x05
  case 2:
    Wire.write(0x03);
    Wire.write(0x04);
    Wire.write(0x05);
    break;
  // if value is 0x03 (or 0x00), don't send anything back
  case 3:
  default:
    break;

  x=0;
  return;
}

void loop(){
}
