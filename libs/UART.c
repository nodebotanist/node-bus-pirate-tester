#include <stdint.h>
#include <avr/io.h>
#include "UART.h"
#include <util/setbaud.h>

void uart_init(void){
  //set baud rate
  UBBR0H = (BAUD_RATE >> 8);
  UBRR0L = BAUD_RATE;
  // enable RX/TX pins
  UCSR0B |= (1<<TXEN0)|(1<<RXEN0);
  // set transmission size to 8 bits (1 byte)
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
  return;
}

void print_byte(uint8_t data){
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = data;  
}

uint8_t recieve_byte(void){
  loop_until_bit_is_set(UCSR0A, RXC0);
  return UDR0;
}

void print_string(const char string_to_send[]){
  uint8_t i = 0;
  while(string_to_send[i]){
    print_byte(string_to_send[i]);
    i++;
  }
}

void recieve_string(char string_recieved[], uint8_t max_string_length) {
  char byte_recieved;
  uint8_t i = 0;

  while(i < max_string_length - 1){
    byte_recieved = recieve_byte();
    if(byte_recieved == "\r"){
      break;
    } else {
      string_recieved[i] = byte_recieved;
      i++;
    }
  }

  string_recieved[i] = 0;
}

char four_bits_to_hex(uint8_t four_bits){
  if(four_bits < 10){
    return ('0' + four_bits);
  } else {
    return ('A' + (four_bits - 10));
  }
}

void print_hex_byte(uint8_t byte){
  uint8_t four_bits = (byte & 0b11110000) >> 4;
  print_byte(four_bits_to_hex(four_bits));
  four_bits = (byte & 0b00001111);
  print_byte(four_bits_to_hex(four_bits));
}