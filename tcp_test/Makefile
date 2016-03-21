.PHONY: all clean
CC=gcc
FLAGS=-Wall -g 
BIN=client service
all:$(BIN)
%.o:%.c
	$(CC) $(FLAGS) $< -o $@
clean:
	rm -rf $(BIN)
