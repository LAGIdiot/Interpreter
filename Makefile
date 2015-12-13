#Makefile
#Date: 07.10.2015, 21.10.2015

CC=gcc
CFLAGS=-c -O2 -std=c99 -Wall -pedantic
CFLAGSD=-c -g -O0 -std=c99 -DDEBUG

PARTS=errors.o $(MM).o token.o str.o deque.o ial.o $(AC).o $(ST).o scanner.o parser.o interpret.o main.o 
PARTS-d=errors-d.o $(MM)-d.o token-d.o str-d.o deque-d.o ial-d.o $(AC)-d.o $(ST)-d.o scanner-d.o parser-d.o interpret-d.o main-d.o
PARTS-d2=errors-d.o $(MM)-d2.o token-d.o str-d.o scanner-d.o parser-d.o ial-d.o $(AC)-d.o $(ST)-d.o main-d.o deque-d.o interpret-d.o

MM=memory_manager
AC=address_code
ST=symbol_table

.PHONY: all
.PHONY: debug
.PHONY: debug2
.PHONY: clean

all: interpret
debug: interpret_d
debug2: interpret_d2

#linking
interpret: $(PARTS)
	$(CC) -o interpret $(PARTS)

interpret_d: $(PARTS-d)
	$(CC) -o interpret_d $(PARTS-d)
	
interpret_d2: $(PARTS-d2)
	$(CC) -o interpret_d $(PARTS-d2)

#compiling
main.o: main.c errors.h $(MM).h scanner.h token.h deque.h parser.h ial.h str.h $(ST).h $(AC).h interpret.h
	$(CC) $(CFLAGS) -o main.o main.c

errors.o: errors.c errors.h $(MM).h
	$(CC) $(CFLAGS) -I/ -o errors.o errors.c

$(MM).o: $(MM).c $(MM).h errors.h
	$(CC) $(CFLAGS) -o $(MM).o $(MM).c

token.o: token.c token.h $(MM).h errors.h
	$(CC) $(CFLAGS) -o token.o token.c

parser.o: parser.c parser.h deque.h errors.h $(MM).h ial.h str.h $(ST).h token.h $(AC).h
	$(CC) $(CFLAGS) -o parser.o parser.c

scanner.o: scanner.c scanner.h errors.h $(MM).h token.h deque.h
	$(CC) $(CFLAGS) -o scanner.o scanner.c

ial.o: ial.c ial.h errors.h $(MM).h str.h deque.h symbol_table.h token.h
	$(CC) $(CFLAGS) -o ial.o ial.c

$(AC).o: $(AC).c $(AC).h errors.h memory_manager.h symbol_table.h str.h deque.h token.h
	$(CC) $(CFLAGS) -o $(AC).o $(AC).c

str.o: str.c str.h errors.h $(MM).h deque.h
	$(CC) $(CFLAGS) -o str.o str.c

$(ST).o: $(ST).c $(ST).h str.h errors.h $(MM).h deque.h token.h
	$(CC) $(CFLAGS) -o $(ST).o $(ST).c
	
deque.o: deque.c deque.h errors.h $(MM).h
	$(CC) $(CFLAGS) -o deque.o deque.c
	
interpret.o: interpret.c interpret.h deque.h errors.h $(MM).h ial.h str.h symbol_table.h $(AC).h
	$(CC) $(CFLAGS) -o interpret.o interpret.c

#Pomyslna delici cara mezi normal a debug

main-d.o: main.c errors.h $(MM).h scanner.h token.h deque.h parser.h ial.h str.h $(ST).h $(AC).h interpret.h
	$(CC) $(CFLAGSD) -o main-d.o main.c

errors-d.o: errors.c errors.h $(MM).h
	$(CC) $(CFLAGSD) -I/ -o errors-d.o errors.c

$(MM)-d.o: $(MM).c $(MM).h errors.h
	$(CC) $(CFLAGSD) -o $(MM)-d.o $(MM).c

token-d.o: token.c token.h $(MM).h errors.h
	$(CC) $(CFLAGSD) -o token-d.o token.c

parser-d.o: parser.c parser.h deque.h errors.h $(MM).h ial.h str.h $(ST).h token.h $(AC).h
	$(CC) $(CFLAGSD) -o parser-d.o parser.c

scanner-d.o: scanner.c scanner.h errors.h $(MM).h token.h deque.h
	$(CC) $(CFLAGSD) -o scanner-d.o scanner.c

ial-d.o: ial.c ial.h errors.h $(MM).h str.h deque.h symbol_table.h token.h
	$(CC) $(CFLAGSD) -o ial-d.o ial.c

$(AC)-d.o: $(AC).c $(AC).h errors.h memory_manager.h symbol_table.h str.h deque.h token.h
	$(CC) $(CFLAGSD) -o $(AC)-d.o $(AC).c

str-d.o: str.c str.h errors.h $(MM).h deque.h
	$(CC) $(CFLAGSD) -o str-d.o str.c

$(ST)-d.o: $(ST).c $(ST).h str.h errors.h $(MM).h deque.h token.h
	$(CC) $(CFLAGSD) -o $(ST)-d.o $(ST).c
	
deque-d.o: deque.c deque.h errors.h $(MM).h
	$(CC) $(CFLAGSD) -o deque-d.o deque.c

interpret-d.o: interpret.c interpret.h deque.h errors.h $(MM).h ial.h str.h symbol_table.h $(AC).h
	$(CC) $(CFLAGSD) -o interpret-d.o interpret.c

#debug 2
$(MM)-d2.o: $(MM).c $(MM).h errors.h
	$(CC) $(CFLAGSD) -DDEBUG2 -o $(MM)-d2.o $(MM).c

#clean
clean:
	rm -f interpret interpret_d *.o
