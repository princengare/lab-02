// Server side C/C++ program to demonstrate Socket programming 
// Here's some include statements that might be helpful for you
#include <string> 
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <sys/socket.h> 
#include <netdb.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char const *argv[]) 
{ 
	// check to see if user input is valid
	char socket_read_buffer[1024];
	
	// TODO: Fill out the server ip and port
	std::string server_ip = "172.20.10.2";
	std::string server_port = "8080";

	int opt = 1;
	int client_fd = -1;

	// TODO: Create a TCP socket()
	

	// Enable reusing address and port
	if (setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { 
		return -1;
	}

	// Check if the client socket was set up properly
	if(client_fd == -1){
		printf("Error- Socket setup failed");
		return -1;
	}
	
	// Helping you out by pepping the struct for connecting to the server
	struct addrinfo hints;
	struct addrinfo *server_addr;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	getaddrinfo(server_ip.c_str(), server_port.c_str(), &hints, &server_addr);

	// TODO: Connect() to the server (hint: you'll need to use server_addr)
	if (connect(client_fd, server_addr->ai_addr, server_addr->ai_addrlen) == -1) {
	printf("Connection to server failed");
	return -1;
	}
	// TODO: Retreive user input
	std::string user_input;
	std::cout << "Enter a message: ";
	std::getline(std::cin, user_input);
	// TODO: Send() the user input to the server
	if (send(client_fd, user_input.c_str(), user_input.length(), 0) == -1) {
	printf("Error sending message");
	return -1;
}
	// TODO: Recieve any messages from the server and print it here. Don't forget to make sure the string is null terminated!
	int num_bytes_received = recv(client_fd, socket_read_buffer, 1024, 0);
if (num_bytes_received == -1) {
	printf("Error receiving message");
	return -1;
} else {
	socket_read_buffer[num_bytes_received] = '\0';
	printf("Message from server: %s\n", socket_read_buffer);
}
	// TODO: Close() the socket
	close(client_fd);

	return 0; 
} 
