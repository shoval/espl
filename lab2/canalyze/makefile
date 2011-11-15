all: canalyze

canalyze: canalyze.o namelist.o

canalyze.o: canalyze.c namelist.h
namelist.o: namelist.c namelist.h

clean:
	rm -f *.o\
	rm canalyze
