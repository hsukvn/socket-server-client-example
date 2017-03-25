#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	// create socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	// specify an address for the socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

	int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	// check for error with the connection
	if (connection_status == -1) {
		printf("error\n");
	}

	// recieve data from the server
	char server_response[256] = {0};
	recv(network_socket, &server_response, sizeof(server_response), 0);

	// print out the response from server
	printf("The server sent the data: %s\n", server_response);

	// close the socket
	close(network_socket);

	return 0;
}
