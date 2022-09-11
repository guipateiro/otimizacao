CFLAGS =  -Wall -Wextra
CC = c++ -g

all: elenco

elenco: t2-otmizacao.cpp
	$(CC) $(CFLAGS) $< -o elenco 

debug: CFLAGS += -DDEBUG
debug: all

clear: 
	rm -f elenco 

purge:
	rm -f elenco 
