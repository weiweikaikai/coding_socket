

.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN= server client  dm32_cltselect dm31_svrselect 
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)





