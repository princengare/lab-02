/* A simple server in the internet domain using TCP
 * Answer the questions below in your writeup
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    /* 1. What is argc and *argv[]?
     *`argc` is the number of command line arguments passed to the program, including the program name itself, and `*argv[]` is an array of strings containing the arguments.
     */
    int sockfd, newsockfd, portno;
    /* 2. What is a UNIX file descriptor and file descriptor table?
     * A UNIX file descriptor is an integer value that identifies an open file or I/O stream, and the file descriptor table is a data structure used by the operating system to keep track of all open file descriptors for a process.
     */
    socklen_t clilen;

    struct sockaddr_in serv_addr, cli_addr;
    /* 3. What is a struct? What's the structure of sockaddr_in?
     * A struct is a composite data type in C that groups together related data items of different types under a single name. The `sockaddr_in` struct is a structure that contains an internet address, defined in the `netinet/in.h` header file, and is used to specify the IP address and port number of a socket when binding it to a local address.
     */
    
    int n;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    /* 4. What are the input parameters and return value of socket()
     * `socket()` is a system call that creates a new communication endpoint, returning a file descriptor for the socket. Its input parameters are the address family (e.g., AF_INET for IPv4), the socket type (e.g., SOCK_STREAM for a TCP socket), and the protocol (usually 0, which allows the operating system to choose the appropriate protocol). Its return value is the file descriptor for the new socket.
     */
    
    if (sockfd < 0) 
       error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) 
             error("ERROR on binding");
    /* 5. What are the input parameters of bind() and listen()?
     * `bind()` is a system call that assigns a local address to a socket, allowing it to receive incoming connections. Its input parameters are the socket file descriptor, a pointer to a `sockaddr` struct containing the local address to bind to (cast to a `struct sockaddr *`), and the size of the address struct. `listen()` is a system call that places the socket in a passive listening mode, waiting for incoming connection requests. Its input parameters are the socket file descriptor and the size of the backlog queue (i.e., the maximum number of pending connections that can be queued up).
     */
    
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    
    while(1) {
        /* 6.  Why use while(1)? Based on the code below, what problems might occur if there are multiple simultaneous connections to handle?
        * The `while(1)` loop causes the server to continuously listen for incoming connections and handle them as they arrive. Without this loop, the program would terminate after handling a single connection. If there are multiple simultaneous connections to handle, the server could become overwhelmed and unable to respond to all of them in a timely manner, leading to dropped connections and lost data.
        */
        
	char buffer[256];
        newsockfd = accept(sockfd, 
                    (struct sockaddr *) &cli_addr, 
                    &clilen);
	/* 7. Research how the command fork() works. How can it be applied here to better handle multiple connections?
         * `fork()` is a system call that creates a new process by duplicating the calling process. In a server program, `fork()` can be used to create child processes to handle incoming connections, allowing the parent process to continue listening for new connections. Each child process would have its own copy of the file descriptors, including the socket file descriptor returned by `accept()`, allowing it to handle a single connection independently of the parent process. This approach is called the "fork and forget" model, and it is commonly used in server programs to handle multiple concurrent connections.
         */
        
	if (newsockfd < 0) 
             error("ERROR on accept");
	bzero(buffer,256);
        
	n = read(newsockfd,buffer,255);
        if (n < 0) 
            error("ERROR reading from socket");
        //printf("Here is the message: %s\n",buffer);
        n = write(newsockfd,"I got your message",18);
        if (n < 0) 
            error("ERROR writing to socket");
        close(newsockfd);
    }
    close(sockfd);
    return 0; 
}
  
/* This program makes several system calls such as 'bind', and 'listen.' What exactly is a system call?
 * A system call is a request made by a user program to the operating system kernel to perform a privileged operation, such as accessing hardware devices, managing memory, or creating network connections. System calls provide a standardized interface between user programs and the underlying hardware and operating system, allowing programs to be written in a portable and hardware-independent manner. When a system call is invoked, the user program is suspended, and control is transferred to the kernel, which performs the requested operation on behalf of the program. After the operation is complete, control is returned to the program, which can continue execution.
 */
