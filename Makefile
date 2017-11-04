# AVR-GCC FLAGS
MMCU = atmega328
GCC_OPT = Os
LIB_DIR = ./libs
F_CPU = 1000000UL

# AVRDUDE FLAGS
ARCH = m328p
PROGRAMMER = usbtiny

main.o:
	avr-gcc -g -$(GCC_OPT) -DF_CPU=$(F_CPU) -mmcu=$(MMCU) -I $(LIB_DIR) -c main.c
	mkdir -p ./build
	mv main.o ./build/main.o

main.elf: main.o
	avr-gcc -g -mmcu=$(MMCU) -o ./build/main.elf ./build/main.o

main.hex: main.o main.elf
	avr-objcopy -j .text -j .data -O ihex ./build/main.elf ./build/main.hex

.PHONY: all clean test-wiring flash

all: main.o main.elf main.hex

clean:
	rm -f build/*.*

test-wiring:
	avrdude -c $(PROGRAMMER) -p $(ARCH)

flash: main.hex
	node scripts/AVRGIRL-flash.js

flash-avrdude: main.hex
	avrdude -c $(PROGRAMMER) -p $(ARCH) -U flash:w:./build/main.hex