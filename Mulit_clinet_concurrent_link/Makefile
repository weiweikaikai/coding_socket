.PHONY:all clean
CC= gcc
FLAGS=-g -Wall
BIN=cltreadline-4 srvreadline-4
all:$(BIN)
%.o:%.c
	$(CC) $(FLAGS) $< -o $@
clean:
	rm -rf $(BIN)
