CC=g++
CFLAGS=-I.
DEPS=parser.h

%.o: %.c $(DEPS)
	$(CC) -c -o $0 $< $(CFLAGS)

parser: parser.o
	$(CC) -o IniParser parser.o -I.