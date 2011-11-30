.PHONY: all clean

all: mycalc

mycalc: calc.o atod.o
	gcc -m32 -o mycalc calc.o atod.o

calc.o: calc.c atod.o
	gcc -m32 -c -o calc.o calc.c

atod.o : atod.asm
	nasm -g -f elf -o $@ $<

#atod.o : atod.c
#	gcc -c -o atod.o atod.c

clean:
	rm *.o mycalc 
