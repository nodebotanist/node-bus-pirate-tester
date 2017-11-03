# AVR-GCC FLAGS
MMCU = atmega328
GCC_OPT = Os
LIB_DIR = ./libs

# AVRDUDE FLAGS
ARCH = m328p
PROGRAMMER = usbtiny

main.o:
	avr-gcc -g -$(GCC_OPT) -mmcu=$(MMCU) -I $(LIB_DIR) -c main.c
	mkdir -p ./build
	mv main.o ./build/main.o

main.elf: main.o
	avr-gcc -g -mmcu=$(MMCU) -o ./build/main.elf ./build/main.o

main.hex: main.o main.elf
	avr-objcopy -j .text -j .data -O ihex ./build/main.elf ./build/main.hex

.PHONY: all clean test-wiring

all: main.o main.elf main.hex

clean:
	rm -f build/*.*

test-wiring:
	avrdude -c $(PROGRAMMER) -p $(ARCH)