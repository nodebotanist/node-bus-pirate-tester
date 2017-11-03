# AVR-GCC FLAGS
MMCU = atmega328
GCC_OPT = Os
LIB_DIR = ./libs

# AVRDUDE FLAGS
ARCH = m328p
PROGRAMMER = usbtiny

main.o:
	avr-gcc -g -$(GCC_OPT) -mmcu=$(MMCU) -I $(LIB_DIR) -c main.c

.PHONY: clean test-wiring

clean:
	rm -f **/*.o **/*.elf **/*.map *.o *.elf *.map

test-wiring:
	avrdude -c $(PROGRAMMER) -p $(ARCH)