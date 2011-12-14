%.o: %.asm
	nasm -g -f elf -o $@ $<

%.o: %.c
	gcc -m32 -g -nostdlib -fno-stack-protector -c -o $@ $<

.PHONY: clean all

all: asm_bcmp

asm_bcmp: start.o myopen.o myreadSingleChar.o printFirstChar.o myclose.o sys_puts.o length.o asm_bcmp.o main.o
	ld -melf_i386 -g -o $@ $^

length.o:length.c
sys_puts.o: sys_puts.asm
start.o: start.asm
myopen.o:myopen.asm
myreadSingleChar.o:myreadSingleChar.asm
printFirstChar.o:printFirstChar.asm
myclose.o:myclose.asm
asm_bcmp.o:asm_bcmp.c
main.o: main.c

clean:
	rm *.o asm_bcmp
