# VPATH settings
vpath %.c src
vpath %.h lib

# gcc-related stuff
CC = avr-gcc
CC_FLAGS = -I include

# External libs
LIB_DIR = ./lib

# avrdude-related stuff
AVRDUDE = avrdude

# AVR arch information
TARGET_ARCH = atmega328p
BAUD = 9600

main.hex: main.o
	gcc main.c 

clean:
	rm -f *.o *.elf *.map