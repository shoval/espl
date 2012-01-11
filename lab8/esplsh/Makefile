# generic rule for compiling C files

CFLAGS=-g -O -Wall

%.o: %.c
	gcc -c $(CFLAGS) -o $@ $<

%: %.o
	gcc $(CFLAGS) -o $@ $<

all: clean esplsh

esplsh: esplsh.o

clean:
	rm -f *.o esplsh

distclean: clean
	rm -f esplsh *~
