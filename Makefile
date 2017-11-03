# AVR-GCC FLAGS
MMCU = atmega328
GCC_OPT = Os

# AVRDUDE FLAGS
ARCH = m328p
PROGRAMMER = usbtiny

main.o:
	avr-gcc -g -$(GCC_OPT) -mmcu=$(MMCU) -c main.c

.PHONY: clean test-wiring

clean:
	rm -f **/*.o **/*.elf **/*.map *.o *.elf *.map

test-wiring:
	avrdude -c $(PROGRAMMER) -p $(ARCH)