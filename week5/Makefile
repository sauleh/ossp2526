CFLAGS = -Wall -Werror -g

all: serverThreaded client

serverThreaded: serverThreaded.o
	$(CC) $(CFLAGS) -o serverThreaded serverThreaded.o -lpthread

serverThreaded.o: serverThreaded.c
	$(CC) $(CFLAGS) -c serverThreaded.c


client: client.o
	$(CC) $(CFLAGS)  -o client client.o

client.o: client.c
	$(CC) $(CFLAGS) -c client.c

clean:
	rm -f *.o serverThreaded client
