#include <stdint.h>
// I2C library

// buffer for address, input, output
volatile uint8_t buffer_address;
volatile uint8_t input_buffer[0xFF];
volatile uint8_t output_buffer[0xFF];

// I2C_Init -- configures AVR as I2C main device multiplier can be set to 1 (100 kHz), or 4 (400 kHz)
void I2C_init(uint8_t multiplier);

// I2C_wait_for_complete -- returns when TWINT bit is set
void I2C_wait_for_complete(void);

// I2C_main_start -- starts I2C comms
void I2C_main_start(void);

// I2C_main_stop -- stops I2C comms
void I2C_main_stop(void);

// I2C_main_read -- reads and waits for ACK
uint8_t I2C_main_read(void);

// I2C_send -- sends a byte via I2C
void I2C_send(uint8_t data);

// I2C_peripheral_init(unsigned char address) -- configures the AVR as an I2C peripheral
void I2C_peripheral_start(uint8_t address);

// I2C_peripheral_stop -- stops I2C peripheral
void I2C_peripheral_stop(void);

// Interrupt for I2C peripheral recieve
ISR(TWI_vect);

// I2C_peripheral_ACK() -- sends ACK and clears interrupt
void I2C_peripheral_ACK(void);

// I2C_peripheral_NACK() -- sends NACK and clears interrupt
void I2C_peripheral_NACK(void);
