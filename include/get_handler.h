class get_handler{
	private:
		char response_header[1024];
		char *response_body; 
	public:		
		void construct_response(char file_name[], int socket_client); 
		void construct_header(char file_name[], int filesize);
		const char* filetype(char file_name[]);
		void send_response(int socket_client, char buffer[], int size);
};

void int_string( int a, char str[] );
