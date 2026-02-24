CFLAGS = -Wall -Werror -g

all: client testClient

server.o: server.c
	$(CC) $(CFLAGS) -c server.c


client: client.o server.o
	$(CC) $(CFLAGS)  -o client server.o client.o 

client.o: client.c
	$(CC) $(CFLAGS) -c client.c

testClient: testClient.o server.o
	$(CC) $(CFLAGS)  -o testClient server.o testClient.o 

testClient.o: testClient.c
	$(CC) $(CFLAGS) -c testClient.c

clean:
	rm -f *.o client testClient
