CC = gcc



all: server client stack.o Test

server: server.o stack.h
	$(CC) -o server server.o -lpthread

stack: stack.o
	$(CC) -o stack stack.o

stack.o: stack.c stack.h
	$(CC) -c stack.c

server.o: server.c stack.h
	$(CC) -c server.c


client: client.c
	$(CC) client.c -o client

Test: Test.c
	$(CC) Test.c -o Test

clean:
	rm -f *.o server client stack Test