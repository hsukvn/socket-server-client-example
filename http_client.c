#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("should give ip address.");
	}
	char *address;
	address = argv[1];

	// create socket
	int client_socket;
	client_socket = socket(AF_INET, SOCK_STREAM, 0);

	// specify an address for the socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(80);
	server_address.sin_addr.s_addr = inet_addr(address);

	int connection_status = connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	// check for error with the connection
	if (connection_status == -1) {
		printf("error\n");
	}

	char request[] = "GET / HTTP/1.1\r\n\r\n";
	char response[4096];

	send(client_socket, request, sizeof(request), 0);
	recv(client_socket, &response, sizeof(response), 0);
	
	printf("response from the server: %s\n", response);
	close(client_socket);

	return 0;
}
