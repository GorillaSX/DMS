CC = g++
RM = rm -rf
CFLAGS = -c -Wall -I. -D_DEBUG
server: main.o server.o filedao.o oracledao.o storethread.o clientthread.o logqueue.o logthread.o serversocket.o 
	$(CC) $^ -pthread -o $@
main.o: main.cpp
	$(CC) $(CFLAGS) $^
server.o: server.cpp
	$(CC) $(CFLAGS) $^
filedao.o: filedao.cpp
	$(CC) $(CFLAGS) $^
oracledao.o: oracledao.cpp
	$(CC) $(CFLAGS) $^
logthread.o: logthread.cpp
	$(CC) $(CFLAGS) $^
storethread.o: storethread.cpp
	$(CC) $(CFLAGS) $^
clientthread.o: clientthread.cpp
	$(CC) $(CFLAGS) $^
logqueue.o: logqueue.cpp
	$(CC) $(CFLAGS) $^
serversocket.o: serversocket.cpp
	$(CC) $(CFLAGS) $^
clean:
	$(RM) server *.o *.gch
	

