.PHONY:clean all
CC=gcc
FLAGS=-g -Wall
BIN=P2P_service P2P_client

all:$(BIN)
%.o:%.c
	$(CC) $(FLAGS) $< -o $@
clean:
	rm -rf $(BIN)
