cc = gcc

default: client server_thread

client: client.o
	$(cc) -o client main_client.o
client.o:
	$(cc) -c main_client.c

server_thread: main_server.o
	$(cc) -o server main_server.o -pthread -DTHREADS
server_fork: main_server.o
	$(cc) -o server main_server.o
main_server.o:
	$(cc) -c main_server.c
clean:
	rm -f *.o client server
