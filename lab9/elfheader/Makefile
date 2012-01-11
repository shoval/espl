# generic rule for compiling C files

CFLAGS=-g -O -Wall

%.o: %.c
	gcc -c $(CFLAGS) -o $@ $<

%: %.o
	gcc $(CFLAGS) -o $@ $<

all: clean elfheader

elfheader: elfheader.o

clean:
	rm -f *.o elfheader

distclean: clean
	rm -f elfheader *~
