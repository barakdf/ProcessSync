CC = gcc



all: server client stack.o

server: server.o stack.h
	$(CC) -o server server.o -lpthread

stack: stack.o
	$(CC) -o stack stack.o

stack.o: stack.c stack.h
	$(CC) -c stack.c

#queue: queue.o
#	$(CC) -o queue queue.o
#
#queue.o: queue.c queue.h
#	$(CC) -c queue.c

#malloc: malloc.o
#	$(CC) -o malloc malloc.o
#
#malloc.o: malloc.c malloc.h
#	$(CC) -c malloc.c

server.o: server.c stack.h
	$(CC) -c server.c


client: client.c
	$(CC) client.c -o client

clean:
	rm -f *.o server client stack