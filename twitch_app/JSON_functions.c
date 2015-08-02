void RemoveHeaders(char * string, int len){
	char *p, c = 123; //123 = "{"
	int plen = 0, last_s = 0;
	p = memchr(string, c, len);
	plen = strlen(p);
	for ( last_s = plen ; last_s > 1 ; last_s-- ){
		if ( 125 == p[last_s] ) break; //125 = "}"
	}
	char buffer[2048];
	memset(buffer, 0, sizeof(buffer));
	memcpy(buffer, p, last_s);
	memset(string, 0, len);
	memcpy(string, buffer, strlen(buffer));
}

