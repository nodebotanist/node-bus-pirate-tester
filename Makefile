ARCH = m328p
PROGRAMMER = usbtiny

.PHONY: clean test-wiring

clean:
	rm -f **/*.o **/*.elf **/*.map *.o *.elf *.map

test-wiring:
	avrdude -c $(PROGRAMMER) -p $(ARCH)