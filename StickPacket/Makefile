.PHONY:clean all
CC=gcc
FLAGS=-g -Wall
BIN=client-1 server-1

all:$(BIN)
%.o:%.c
	$(CC) $(FLAGS) $< -o $@
clean:
	rm -rf $(BIN)
