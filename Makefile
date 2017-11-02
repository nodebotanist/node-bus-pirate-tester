main.hex: main.o
	gcc main.c 

clean:
	rm -f *.o *.elf *.map