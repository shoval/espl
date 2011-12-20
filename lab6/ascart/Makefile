%.o: %.asm
	nasm -g -f elf -o $@ $<

%.o: %.c
	gcc -m32 -g -nostdlib -fno-stack-protector -c -o $@ $<

.PHONY: clean all

all: clean ascart

ascart: start.o asmart.o font.o
	ld -melf_i386 -g -o $@ $^

start.o: start.asm
asmart.o: asmart.asm
font.o: font.c

clean:
	rm -f *.o ascart
