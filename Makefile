#Makefile
#Date: 07.10.2015

CC=gcc
CFLAGS=-c -O2 -std=c99 -Wall -pedantic
CFLAGSD=-c -g -O0 -std=c99 -DDEBUG

all: compiler

debug: compiler-d

#linking
compiler: main errors
	$(CC) -o compiler main.o errors.o

compiler-d: main-d errors-d
	$(CC) -o compiler_d main_d.o errors_d.o

#compiling
errors: errors.c errors.h
	$(CC) $(CFLAGS) -I/ -o errors.o errors.c

main: main.c errors.h
	$(CC) $(CFLAGS) -o main.o main.c

errors-d: errors.c errors.h
	$(CC) $(CFLAGSD) -I/ -o errors_d.o errors.c

main-d: main.c errors.h
	$(CC) $(CFLAGSD) -o main_d.o main.c

#clean
clean:
	rm -f compiler compiler_d *.o
