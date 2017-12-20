// I2C library

// I2C_Init -- configures AVR as I2C main device multiplier can be set to 1 (100 kHz), or 4 (400 kHz)
void I2C_init(uint8_t multiplier);

// I2C_wait_for_complete -- returns when TWINT bit is set
void I2C_wait_for_complete(void);

// I2C_start -- starts I2C comms
void I2C_main_start(void);

// I2C_stop -- stops I2C comms
void I2C_main_stop(void);

// I2C_read -- reads and waits for ACK
uint8_t I2C_main_read(void);

// I2C_send -- sends a byte via I2C
void I2C_send(uint8_t data);

// I2C_peripheral_init(unsigned char address) -- configures the AVR as an I2C peripheral
void I2C_peripheral_init(uint8_t address);

// I2C_peripheral_start -- starts I2C peripheral
void I2C_peripheral_start(void);

// I2C_peripheral_stop -- stops I2C peripheral
void I2C_peripheral_stop(void);

// Interrupt for I2C peripheral recieve
ISR(TWI_vect);