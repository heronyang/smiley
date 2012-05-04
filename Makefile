CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-lm

PROGRAM=main

all: $(PROGRAM)

smiley.o : smiley.c smiley.h
	${CC} ${CFLAGS} -c smiley.c

main.o : main.c smiley.h
	${CC} ${CFLAGS} -c main.c
	
$(PROGRAM) : main.o smiley.o
	${CC} ${CFLAGS} smiley.o main.o ${LDFLAGS} -o main
	rm *.o

clean:
	rm -f $(PROGRAM) *.o
