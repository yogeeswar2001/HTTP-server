#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>

#include<stdio.h>
#include<string.h>

#include "parser.h"
#include "get_handler.h"

using namespace std;

int main(int argc, char *argv[]) {
	
	//setting up port number
	const char *port_number;
	if(argc > 1){
		port_number = argv[2];
	}
	else{
		port_number = "8080";
	}

	// setting socket address
	printf("configuring local address...\n");

	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	struct addrinfo *bind_addr;
	getaddrinfo(0, port_number, &hints, &bind_addr);
	
	//creating a socket 
	printf("creating sockets...\n");

	int socket_listen;
	socket_listen = socket(bind_addr->ai_family, bind_addr->ai_socktype, bind_addr->ai_protocol);
	if(socket_listen < 0 ){
		printf("ERROR: in creating socket\n");
		return 0;
	}

	//binding the socket
	printf("binding socket...\n");

	if( bind(socket_listen, bind_addr->ai_addr, bind_addr->ai_addrlen) ){
		printf("ERROR: in binding\n");
		close(socket_listen);
		return 0;
	}
	freeaddrinfo(bind_addr);

	//making the socket listen for new connections
	printf("listening...\n");

	if( listen(socket_listen,10) < 0 ){
		printf("ERROR: in listing\n");
		close(socket_listen);
		return 0;
	}

	int socket_client;
	for(;;){
		printf("waiting for connection...\n");
		struct sockaddr_storage client_addr;
		socklen_t client_len = sizeof(client_addr);

		//accepting the new connection 
		//creates a new socket
		socket_client = accept( socket_listen, (struct sockaddr*)&client_addr, &client_len);
		if( socket_client < 0 ){
			printf("ERROR: in accepting\n");
			close(socket_listen);
			return 0;
		}
		//getting client details(ip address)
		printf("\nclient details : \n");
		char client_detail[100];
		getnameinfo( (struct sockaddr*)&client_addr, client_len, client_detail, sizeof(client_detail), 0, 0, NI_NUMERICHOST);
		printf("%s", client_detail);

		//reading request
		char request[1024];
		int byte_recv = recv(socket_client, request, 1024, 0);
	       	request[byte_recv] = '\0';
		printf("\nrequest: \n%s",request);
		
		//class for getting correct respose for the request
		//parsing the requesting to get method, file name, http version
		parser p;
		p.parse_request(request);
		
		//to handle GET request
		if( strcmp( p.method, "GET" ) == 0 ){
			get_handler h;
			h.construct_response(p.file_name, socket_client);
		} //to handle POST request
		else{
			
		}

		//sending back response
		//int byte_sent = send(socket_client, response, strlen(response), 0);
		//printf("response:\n%s", response);

		//closing the client socket
		close(socket_client);
	}

	//closing main socket
	close(socket_listen);
	return 0;
}
