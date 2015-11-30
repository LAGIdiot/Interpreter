#Makefile
#Date: 07.10.2015, 21.10.2015

CC=gcc
CFLAGS=-c -O2 -std=c99 -Wall -pedantic
CFLAGSD=-c -g -O0 -std=c99 -DDEBUG

PARTS=errors.o $(MM).o token.o str.o scanner.o parser.o ial.o $(AC).o $(ST).o main.o deque.o interpret.o
PARTS-d=errors-d.o $(MM)-d.o token-d.o str-d.o scanner-d.o parser-d.o ial-d.o $(AC)-d.o $(ST)-d.o main-d.o deque-d.o interpret-d.o
PARTS-d2=errors-d.o $(MM)-d2.o token-d.o str-d.o scanner-d.o parser-d.o ial-d.o $(AC)-d.o $(ST)-d.o main-d.o deque-d.o interpret-d.o

MM=memory_manager
AC=address_code
ST=symbol_table

.PHONY: all
.PHONY: debug
.PHONY: debug2
.PHONY: clean

all: compiler
debug: compiler-d
debug2: compiler-d2

#linking
compiler: $(PARTS)
	$(CC) -o compiler $(PARTS)

compiler-d: $(PARTS-d)
	$(CC) -o compiler-d $(PARTS-d)
	
compiler-d2: $(PARTS-d2)
	$(CC) -o compiler-d $(PARTS-d2)

#compiling
main.o: main.c errors.h $(MM).h parser.h str.h $(ST).h token.h scanner.h interpret.h
	$(CC) $(CFLAGS) -o main.o main.c

errors.o: errors.c errors.h $(MM).h
	$(CC) $(CFLAGS) -I/ -o errors.o errors.c

$(MM).o: $(MM).c $(MM).h errors.h
	$(CC) $(CFLAGS) -o $(MM).o $(MM).c

token.o: token.c token.h $(MM).h errors.h
	$(CC) $(CFLAGS) -o token.o token.c

parser.o: parser.c parser.h errors.h $(MM).h str.h $(ST).h token.h 
	$(CC) $(CFLAGS) -o parser.o parser.c

scanner.o: scanner.c scanner.h errors.h token.h $(MM).h
	$(CC) $(CFLAGS) -o scanner.o scanner.c

ial.o: ial.c ial.h errors.h $(MM).h str.h
	$(CC) $(CFLAGS) -o ial.o ial.c

$(AC).o: $(AC).c $(AC).h
	$(CC) $(CFLAGS) -o $(AC).o $(AC).c

str.o: str.c str.h errors.h $(MM).h
	$(CC) $(CFLAGS) -o str.o str.c

$(ST).o: $(ST).c $(ST).h $(MM).h errors.h str.h
	$(CC) $(CFLAGS) -o $(ST).o $(ST).c
	
deque.o: deque.c deque.h errors.h $(MM).h
	$(CC) $(CFLAGS) -o deque.o deque.c
	
interpret.o: interpret.c interpret.h errors.h deque.h ial.h
	$(CC) $(CFLAGS) -o interpret.o interpret.c

#Pomyslna delici cara mezi normal a debug

main-d.o: main.c errors.h $(MM).h parser.h str.h $(ST).h token.h scanner.h interpret.h
	$(CC) $(CFLAGSD) -o main-d.o main.c

errors-d.o: errors.c errors.h $(MM).h
	$(CC) $(CFLAGSD) -I/ -o errors-d.o errors.c

$(MM)-d.o: $(MM).c $(MM).h errors.h
	$(CC) $(CFLAGSD) -o $(MM)-d.o $(MM).c

token-d.o: token.c token.h $(MM).h errors.h
	$(CC) $(CFLAGSD) -o token-d.o token.c

parser-d.o: parser.c parser.h errors.h $(MM).h str.h $(ST).h token.h 
	$(CC) $(CFLAGSD) -o parser-d.o parser.c

scanner-d.o: scanner.c scanner.h errors.h token.h $(MM).h
	$(CC) $(CFLAGSD) -o scanner-d.o scanner.c

ial-d.o: ial.c ial.h errors.h $(MM).h str.h
	$(CC) $(CFLAGSD) -o ial-d.o ial.c

$(AC)-d.o: $(AC).c $(AC).h
	$(CC) $(CFLAGSD) -o $(AC)-d.o $(AC).c

str-d.o: str.c str.h errors.h $(MM).h
	$(CC) $(CFLAGSD) -o str-d.o str.c

$(ST)-d.o: $(ST).c $(ST).h $(MM).h errors.h str.h
	$(CC) $(CFLAGSD) -o $(ST)-d.o $(ST).c
	
deque-d.o: deque.c deque.h errors.h $(MM).h
	$(CC) $(CFLAGSD) -o deque-d.o deque.c

interpret-d.o: interpret.c interpret.h errors.h deque.h ial.h
	$(CC) $(CFLAGS) -o interpret-d.o interpret.c
	
#debug 2
$(MM)-d2.o: $(MM).c $(MM).h errors.h
	$(CC) $(CFLAGSD) -DDEBUG2 -o $(MM)-d2.o $(MM).c

#clean
clean:
	rm -f compiler compiler-d *.o
