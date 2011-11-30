all: hsvmhr_use

hsvmhr_use: hsvmhr_use.o hsvmhr.o
	gcc -m32 -o hsvmhr_use hsvmhr_use.o hsvmhr.o 

hsvmhr_use.o: hsvmhr_use.c hsvmhr.o
	gcc -m32 -c -o hsvmhr_use.o hsvmhr_use.c

hsvmhr.o: hsvmhr.asm
	nasm -g -f elf -o $@ $<

clean:
	rm *.o hsvmhr_use
