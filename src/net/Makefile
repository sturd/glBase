all: socket

socket: error.o data.o client_list.o server_sock.o client_sock.o main.o
	g++ -o socket -lboost_thread error.o data.o client_list.o server_sock.o client_sock.o main.o
	rm -rf *.o

error.o: error.cpp
	g++ -c error.cpp

data.o: data.cpp
	g++ -c data.cpp
	
client_list.o: client_list.cpp
	g++ -c client_list.cpp

server_sock.o: client_list.o server_sock.cpp
	g++ -c server_sock.cpp

client_sock.o: client_sock.cpp
	g++ -c client_sock.cpp
	
main.o: main.cpp
	g++ -c main.cpp
	
clean:
	rm -rf *.o socket
