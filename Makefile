# VPATH settings
vpath %.c src
vpath %.h lib

# External libs
LIBDIR = ./libs

# gcc-related stuff
CC = avr-gcc
OBJCOPY = avr-objcopy
BAUD = 9600
CCFLAGS = -DBAUD=$(BAUD)UL -I. -I $(LIBDIR) 
LDFLAGS = -Wl,-Map,$(TARGET).map
## Optional, but often ends up with smaller code
LDFLAGS += -Wl,--gc-sections

# avrdude-related stuff
ARCH = atmega328p
TARGET_ARCH = -mmcu=$(ARCH)
AVRDUDE = avrdude
PROGRAMMER = usbtiny

# Project-Related info
TARGET = main

%.o: %.c
	$(CC) $(CCFLAGS) $(TARGET_ARCH) -o -c $@ $<;

$(TARGET).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) $(TARGET_ARCH) $^ $(LDLIBS) -o $@

%.hex: %.elf
	 $(OBJCOPY) -j .text -j .data -O ihex $< $@

%.eeprom: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@

%.lst: %.elf
	$(OBJDUMP) -S $< > $@

all: $(TARGET).hex

clean:
	rm -f **/*.o **/*.elf **/*.map