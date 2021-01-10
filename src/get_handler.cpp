#include<iostream>
#include<cstdio>
#include<cstring>

#include<sys/socket.h>
#include<sys/stat.h>

#include "get_handler.h"

using namespace std;

void get_handler::construct_response(char file_name[], int socket_client){
	FILE *fileptr;
	
	//reading content from file
	fileptr = fopen(file_name, "r");
	if(fileptr == NULL){
		printf("ERROR: in file opening\n");
		strcpy(file_name, "../files/error_404.html");
		fileptr = fopen(file_name, "r");	
	}
	
	//debugging 
	//printf("\n--------------%s------------\n",file_name);

	//to find file size
	int filesize;
	struct stat filestat;
	stat(file_name, &filestat);
	filesize = filestat.st_size;
	response_body = (char *)malloc(filesize+1);
	int bytes = fread(response_body, filesize, 1, fileptr);
	
	//construct headers
	get_handler::construct_header(file_name, filesize);

	//sending header
	get_handler::send_response(socket_client, response_header, strlen(response_header));

	//sending body
	get_handler::send_response(socket_client, response_body, filesize);

	//closing file pointer
	fclose(fileptr);
}

const char* get_handler::filetype(char file_name[]){
	int i=2,j=0;
	while( file_name[i] != '.')
		i++;
	i++;
	char str[8];
	while(file_name[i])
		str[j++] = file_name[i++];
	str[j] = '\0';

	//debugging
	printf("\n----------------------------\nfile type: %s\n",str);

	if( strcmp(str,"html") == 0 )
		return "text/html";
	else if( strcmp(str,"css") == 0 )
		return "text/css";
	else if( strcmp(str,"js") == 0 )
	       	return "application/javascript";
	else if( strcmp(str,"ico") == 0 )
	        return "image/x-icon";
	else if( strcmp(str,"jpeg") == 0 )
	        return "image/jpeg";
	else if( strcmp(str,"png") == 0 )
	        return "image/png";
	else if( strcmp(str,"txt") == 0 )
		return "text/plain";
	else
		return "application/octet-stream";
}

void get_handler::construct_header( char file_name[], int filesize ){
	char size[8];
	int_string(filesize, size);

	strcpy(response_header, "HTTP/1.1 ");
	strcat(response_header, "200 OK\r\n");
	strcat(response_header, "content-Length:");
	strcat(response_header, size);
	strcat(response_header, "\r\n");
	strcat(response_header, "content-Type:");
	strcat(response_header, get_handler::filetype(file_name));
	strcat(response_header, "\r\n\r\n\0");
}

void get_handler::send_response(int socket_client, char buffer[], int size){
	int bytes = send(socket_client, buffer, size, 0);
	if(bytes < 0)
		printf("ERROR: in sending response\n");
	else{
		printf("number of bytes sent: %d\n",size);
		printf("%s\n", buffer);
	}
}

void int_string( int a, char str[] ){
	char temp;
	int i=0,j=0;
	while( a ){
		str[i++] = (char)('0'+a%10);
		a/=10;
	}
	str[i]='\0';
	i--;
	while(j<i){
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i--;j++;
	}
}
