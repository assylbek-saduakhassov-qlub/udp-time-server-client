CC=gcc
CFLAGS=-Wall

all: time_server time_client

time_server: time_server.o config.o
	$(CC) -o time_server time_server.o config.o

time_client: time_client.o
	$(CC) -o time_client time_client.o

time_server.o: time_server.c config.h
	$(CC) $(CFLAGS) -c time_server.c

config.o: config.c config.h
	$(CC) $(CFLAGS) -c config.c

time_client.o: time_client.c
	$(CC) $(CFLAGS) -c time_client.c

clean:
	rm -f *.o time_server time_client
