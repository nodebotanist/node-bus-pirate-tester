# AVR-GCC FLAGS
MMCU = atmega328
GCC_OPT = Os
LIB_DIR = ./libs

# AVRDUDE FLAGS
ARCH = m328p
PROGRAMMER = usbtiny

main.o:
	avr-gcc -g -$(GCC_OPT) -mmcu=$(MMCU) -I $(LIB_DIR) -c main.c

main.elf: main.o
	avr-gcc -g -mmcu=$(MMCU) -o main.elf main.o

.PHONY: all clean test-wiring

all: main.o main.elf

clean:
	rm -f **/*.o **/*.elf **/*.map *.o *.elf *.map

test-wiring:
	avrdude -c $(PROGRAMMER) -p $(ARCH)