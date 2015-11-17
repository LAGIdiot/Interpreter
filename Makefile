#Makefile
#Date: 07.10.2015, 21.10.2015

CC=gcc
CFLAGS=-c -O2 -std=c99 -Wall -pedantic
CFLAGSD=-c -g -O0 -std=c99 -DDEBUG

PARTS=errors.o $(MM).o token.o str.o $(LA).o $(SA).o ial.o $(AC).o $(ST).o main.o
PARTS-d=errors-d.o $(MM)-d.o token-d.o str-d.o $(LA)-d.o $(SA)-d.o ial-d.o $(AC)-d.o $(ST)-d.o main-d.o

MM=memory_manager
LA=lexical_analyzer
SA=syntactic_analyzer
AC=adress_code
ST=symbol_table

.PHONY: all
.PHONY: debug
.PHONY: clean

all: compiler
debug: compiler-d

#linking
compiler: $(PARTS)
	$(CC) -o compiler $(PARTS)

compiler-d: $(PARTS-d)
	$(CC) -o compiler-d $(PARTS-d)

#compiling
main.o: main.c errors.h $(MM).h $(SA).h str.h $(ST).h token.h
	$(CC) $(CFLAGS) -o main.o main.c

errors.o: errors.c errors.h $(MM).h
	$(CC) $(CFLAGS) -I/ -o errors.o errors.c

$(MM).o: $(MM).c $(MM).h errors.h
	$(CC) $(CFLAGS) -o $(MM).o $(MM).c

token.o: token.c token.h $(MM).h errors.h
	$(CC) $(CFLAGS) -o token.o token.c

$(SA).o: $(SA).c $(SA).h errors.h $(MM).h str.h $(ST).h token.h 
	$(CC) $(CFLAGS) -o $(SA).o $(SA).c

$(LA).o: $(LA).c $(LA).h errors.h token.h $(MM).h
	$(CC) $(CFLAGS) -o $(LA).o $(LA).c

ial.o: ial.c ial.h errors.h $(MM).h str.h
	$(CC) $(CFLAGS) -o ial.o ial.c

$(AC).o: $(AC).c $(AC).h
	$(CC) $(CFLAGS) -o $(AC).o $(AC).c

str.o: str.c str.h errors.h $(MM).h
	$(CC) $(CFLAGS) -o str.o str.c

$(ST).o: $(ST).c $(ST).h $(MM).h errors.h str.h
	$(CC) $(CFLAGS) -o $(ST).o $(ST).c

#Pomyslna delici cara mezi normal a debug

main-d.o: main.c errors.h $(MM).h $(SA).h str.h $(ST).h token.h
	$(CC) $(CFLAGSD) -o main-d.o main.c

errors-d.o: errors.c errors.h $(MM).h
	$(CC) $(CFLAGSD) -I/ -o errors-d.o errors.c

$(MM)-d.o: $(MM).c $(MM).h errors.h
	$(CC) $(CFLAGSD) -o $(MM)-d.o $(MM).c

token-d.o: token.c token.h $(MM).h errors.h
	$(CC) $(CFLAGSD) -o token-d.o token.c

$(SA)-d.o: $(SA).c $(SA).h errors.h $(MM).h str.h $(ST).h token.h 
	$(CC) $(CFLAGSD) -o $(SA)-d.o $(SA).c

$(LA)-d.o: $(LA).c $(LA).h errors.h token.h $(MM).h
	$(CC) $(CFLAGSD) -o $(LA)-d.o $(LA).c

ial-d.o: ial.c ial.h errors.h $(MM).h str.h
	$(CC) $(CFLAGSD) -o ial-d.o ial.c

$(AC)-d.o: $(AC).c $(AC).h
	$(CC) $(CFLAGSD) -o $(AC)-d.o $(AC).c

str-d.o: str.c str.h errors.h $(MM).h
	$(CC) $(CFLAGSD) -o str-d.o str.c

$(ST)-d.o: $(ST).c $(ST).h $(MM).h errors.h str.h
	$(CC) $(CFLAGSD) -o $(ST)-d.o $(ST).c

#clean
clean:
	rm -f compiler compiler-d *.o
