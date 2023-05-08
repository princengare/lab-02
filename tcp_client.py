"""
Server receiver buffer is char[256]
If correct, the server will send a message back to you saying "I got your message"
Write your socket client code here in python
Establish a socket connection -> send a short message -> get a message back -> ternimate
use python "input->" function, enter a line of a few letters, such as "abcd"
"""
import socket

def main():
    # TODO: Create a socket and connect it to the server at the designated IP and port
    # TODO: Get user input and send it to the server using your TCP socket
    # TODO: Receive a response from the server and close the TCP connection
    
    # Define the IP address and port of the server
    SERVER_IP = 'localhost'
    SERVER_PORT = 8080

    # Create a socket object
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Connect the socket to the server
    client_socket.connect((SERVER_IP, SERVER_PORT))

    # Get user input
    user_input = input("Enter a message: ")

    # Send the user input to the server
    client_socket.send(user_input.encode())

    # Receive a response from the server
    response = client_socket.recv(256).decode()

    # Print the response from the server
    print("Server response: ", response)

    # Close the socket
    client_socket.close()


if __name__ == '__main__':
    main()
