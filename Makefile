#Makefile
#Date: 07.10.2015

CC=gcc
CFLAGS=-c -O2 -std=c99 -Wall -pedantic
CFLAGSD=-c -g -O0 -std=c99 -DDEBUG

all: compiler

debug: compiler-d

#linking
compiler: main errors LA MM SA ial token ST AC
	$(CC) -o compiler main.o errors.o lexical_analyzer.o memory_manager.o syntactic_analyzer.o ial.o token.o symbol_table.o adress_code.o 

compiler-d: main-d errors-d LA-d MM-d SA-d ial-d token-d ST-d AC-d
	$(CC) -o compiler_d main_d.o errors_d.o lexical_analyzer_d.o memory_manager_d.o syntactic_analyzer_d.o ial_d.o token_d.o symbol_table_d.o adress_code_d.o 

#compiling
errors: errors.c errors.h
	$(CC) $(CFLAGS) -I/ -o errors.o errors.c

LA: lexical_analyzer.c lexical_analyzer.h
	$(CC) $(CFLAGS) -o lexical_analyzer.o lexical_analyzer.c

MM: memory_manager.c memory_manager.h
	$(CC) $(CFLAGS) -o memory_manager.o memory_manager.c
	
SA: syntactic_analyzer.c syntactic_analyzer.h
	$(CC) $(CFLAGS) -o syntactic_analyzer.o syntactic_analyzer.c
	
ial: ial.c ial.h
	$(CC) $(CFLAGS) -o ial.o ial.c
	
token: token.c token.h
	$(CC) $(CFLAGS) -o token.o token.c
	
ST: symbol_table.c symbol_table.h
	$(CC) $(CFLAGS) -o symbol_table.o symbol_table.c
	
AC: adress_code.c adress_code.h
	$(CC) $(CFLAGS) -o adress_code.o adress_code.c 
	
main: main.c errors.h
	$(CC) $(CFLAGS) -o main.o main.c

#Pomyslna delici cara mezi normal a debug

errors-d: errors.c errors.h
	$(CC) $(CFLAGSD) -I/ -o errors_d.o errors.c

LA-d: lexical_analyzer.c lexical_analyzer.h
	$(CC) $(CFLAGSD) -o lexical_analyzer_d.o lexical_analyzer.c

MM-d: memory_manager.c memory_manager.h
	$(CC) $(CFLAGSD) -o memory_manager_d.o memory_manager.c

SA-d: syntactic_analyzer.c syntactic_analyzer.h
	$(CC) $(CFLAGSD) -o syntactic_analyzer_d.o syntactic_analyzer.c

ial-d: ial.c ial.h
	$(CC) $(CFLAGSD) -o ial_d.o ial.c
	
token-d: token.c token.h
	$(CC) $(CFLAGSD) -o token_d.o token.c
	
ST-d: symbol_table.c symbol_table.h
	$(CC) $(CFLAGS) -o symbol_table_d.o symbol_table.c
	
AC-d: adress_code.c adress_code.h
	$(CC) $(CFLAGS) -o adress_code_d.o adress_code.c 
	
main-d: main.c errors.h
	$(CC) $(CFLAGSD) -o main_d.o main.c

#clean
clean:
	rm -f compiler compiler_d *.o
