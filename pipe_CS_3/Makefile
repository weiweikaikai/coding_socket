.PHONY:all clean
CC= gcc
FLAGS=-g -Wall
BIN=echoclient echosrv

all:$(BIN)
%.o:%.c
	$(CC) $(FLAGS) $< -o $@
clean:
	rm -rf $(BIN)
