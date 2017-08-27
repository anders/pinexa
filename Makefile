CC=cc
CFLAGS=-Wall -O2 -std=c99
LIBS=-lwiringPi

pinexa: pinexa.o
	$(CC) -o pinexa pinexa.o $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $*.c -o $*.o

clean:
	rm pinexa pinexa.o
