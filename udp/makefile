.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN=udpclt udpsrv timdata udpclt2
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
	
#cli:cli.o sckutil.o
#	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o $(BIN)




