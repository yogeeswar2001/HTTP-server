class parser{
	public:
		char method[32];
		char file_name[32];
		char http_version[32];
		
		parser();
		void parse_request(char request[]);
};
