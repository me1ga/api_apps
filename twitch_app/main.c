//  File:       server.c
//  Autor:      me1ga
//  Created:    22 июнь 2015 г. 19:03
//  Compile string:
//  1) make
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include "openssl/ssl.h"
#include "openssl/err.h"
#include <resolv.h>

#include "SSL_functions.c"
#include "SOCKET_functions.c"
#include "JSON_functions.c"
#include "JSON_structures.h"

#define FAIL -1
#define h_addr h_addr_list[0]
#define BUFFER_LEN 2048

int main(int argc, char const *argv[]){
	/* Инициализация переменных */
	int tcp_sock, bytes_read;
	char host[] = "api.twitch.tv";
	int port = 443;
	char message[]="GET /kraken/users/ws_mega HTTP/1.1\r\nHost: api.twitch.tv\r\nAccept: application/vnd.twitchtv.v3+json\r\n\r\n";
	char buffer[BUFFER_LEN];
	SSL_CTX *ctx;
	SSL *ssl;
	struct user user;

	memset(buffer, 0, sizeof(buffer));

	SSL_library_init();
	/* Инициализация сокетов */
	ctx = InitCTX();
	tcp_sock = InitSOCKET(&host[0], port);
	ssl = SSL_new(ctx);
	SSL_set_fd(ssl, tcp_sock);

	/* Тело программы */
	if( (SSL_connect(ssl)) == FAIL ){
		ERR_print_errors_fp(stderr);
	}
	SSL_write(ssl, message, sizeof(message));
	bytes_read = SSL_read(ssl, buffer, sizeof(buffer));
	RemoveHeaders(&buffer[0], bytes_read);
	user = ParseUser_v3(buffer);
	printf("%s\n", user.display_name);
//	printf("%s\n", buffer);

	/* Высвобождение переменных */
	SSL_free(ssl);
	close(tcp_sock);
	SSL_CTX_free(ctx);
	return 0;
}
