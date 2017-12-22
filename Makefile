# AVR-GCC FLAGS
MMCU = atmega328p
GCC_OPT = Os
LIB_DIR = ./libs
BUILD_DIR = ./build/
F_CPU = 1000000UL

# AVRDUDE FLAGS
ARCH = m328p
PROGRAMMER = usbtiny

# DEPS
DEPS_C = $(patsubst %.c,%.o,$(wildcard libs/*.c))
DEPS = $(foreach dep, $(DEPS_C), build/$(dep))

%.o: %.c
	avr-gcc -g -$(GCC_OPT) -DF_CPU=$(F_CPU) -mmcu=$(MMCU) -I $(LIB_DIR) -c $< -o $(BUILD_DIR)$@

%.elf: %.o
	avr-gcc -g -mmcu=$(MMCU) $(DEPS) $(BUILD_DIR)$< -o $(BUILD_DIR)$@

%.hex: %.elf
	avr-objcopy -j .text -j .data -O ihex $(BUILD_DIR)$^ $@	

.PHONY: all build checksig checksig-avrdude clean deps flash flash-avrdude start

all: build flash

build: start deps main.hex I2C_peripheral.hex

checksig:
	node scripts/AVRGIRL-checksig.js -c $(MMCU)

checksig-avrdude:
	avrdude -c $(PROGRAMMER) -p $(ARCH)

clean:
	rm -f build/*.* && rm -rf build/libs && rm -f *.hex

deps: $(DEPS_C)

erase: 
	node scripts/AVRGIRL-erase.js -c $(MMCU)

flash: main.hex
	node scripts/AVRGIRL-flash.js -t main -c $(MMCU) -p sf-pocket-avr

flash-avrdude: main.hex
	avrdude -c $(PROGRAMMER) -p $(ARCH) -U flash:w:./build/main.hex

start:
	mkdir -p build
	mkdir -p build/libs