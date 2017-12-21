# AVR-GCC FLAGS
MMCU = atmega328p
GCC_OPT = Os
LIB_DIR = ./libs
BUILD_DIR = ./build/
F_CPU = 1000000UL

# AVRDUDE FLAGS
ARCH = m328p
PROGRAMMER = usbtiny

%.o: %.c
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)$(LIB_DIR)
	avr-gcc -g -$(GCC_OPT) -DF_CPU=$(F_CPU) -mmcu=$(MMCU) -I $(LIB_DIR) -c $< -o $(BUILD_DIR)$@

main.elf: main.o
	avr-gcc -g -mmcu=$(MMCU) ./build/libs/UART.o $(BUILD_DIR)$< -o $(BUILD_DIR)$@

%.hex: %.elf
	avr-objcopy -j .text -j .data -O ihex $(BUILD_DIR)$^ $@	

.PHONY: all build checksig clean deps flash

all: build flash

build: deps main.hex

clean:
	rm -f build/*.*

checksig-avrdude:
	avrdude -c $(PROGRAMMER) -p $(ARCH)

checksig:
	node scripts/AVRGIRL-checksig.js -c $(MMCU)

deps: libs/UART.o libs/I2C.o

flash: main.hex
	node scripts/AVRGIRL-flash.js -t main -c $(MMCU) -p sf-pocket-avr

erase: 
	node scripts/AVRGIRL-erase.js -c $(MMCU)

flash-avrdude: main.hex
	avrdude -c $(PROGRAMMER) -p $(ARCH) -U flash:w:./build/main.hex