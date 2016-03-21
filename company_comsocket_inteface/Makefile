.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN=client service
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
	
client:client.o commsocket.o
	$(CC) $(CFLAGS) $^ -o $@ 
	
service:service.o commsocket.o
	$(CC) $(CFLAGS) $^ -o $@
clean:
	rm -f *.o $(BIN)
