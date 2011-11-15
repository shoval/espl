ascart: ascart.o font.o
	gcc -o ascart ascart.o font.o
ascart.o: font.o
	gcc -c -o ascart.o ascart.c
font.o:
	gcc -c -o font.o font.c
clean:
	rm -f *.o
	rm ascart