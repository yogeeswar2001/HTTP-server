#include<iostream>
#include<cstring>
#include "parser.h"

using namespace std;

parser::parser(){
	memset(method, 0, sizeof(method));
	memset(file_name, 0, sizeof(file_name));
	memset(http_version, 0, sizeof(http_version));
}	

void parser::parse_request(char request[]){
	int i=0,j=0;
	while(request[i] != ' ')
		method[j++] = request[i++];
	method[j] = '\0';

	i++;j=0;
	file_name[j++]='.';
	while(request[i] != ' ')
		file_name[j++] = request[i++];
	file_name[j] = '\0';

	i++;j=0;
	while(request[i] != '\r')
		http_version[j++] = request[i++];
	http_version[j] = '\0';
	
	//debugging
	//printf("\n-------------------------------\nmethod: %s\nfile_name:%s\nversion:%s\n",method,file_name,http_version);
}

