// I2C library

// I2C_Init -- multiplier can be set to 1 (100 kHz), or 4 (400 kHz)
void I2C_init(uint8_t multiplier);

// I2C_wait_for_complete -- returns when TWINT bit is set
void I2C_wait_for_complete(void);

// I2C_start -- starts I2C comms
void I2C_start(void);