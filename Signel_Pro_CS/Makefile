.PHONY:clean all
CC=gcc
FLAGS=-g -Wall
BIN=demo_service demo_client

all:$(BIN)
%.o:%.c
	$(CC) $(FLAGS) $< -o $@
clean:
	rm -rf $(BIN)
