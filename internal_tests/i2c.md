1. Startup Serial w/Bus Pirate
2. Enter I2C mode
3. W to turn on power
4. (1) to scan addresses (Should output `0x38(0x1C W) 0x39(0x1c R)`)
5. [0x38 0x10 [0x39 r]

Expected:

I2C START BIT
WRITE: 0x38 ACK
WRITE: 0x10 ACK
I2C START BIT
WRITE: 0x39 ACK
READ: 0x10
NACK
I2C STOP BIT
