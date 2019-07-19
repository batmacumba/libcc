#include <stdio.h>
#include <stdlib.h>
#include "../../src/socket.h"

int
main(int argc, char **argv) {
	char *buffer = malloc(1024);
	
	/* server */
	if (argc < 3) {
		Socket *s = socket_open(0);
		socket_await(s);
		while (socket_read(s, buffer, 1024)) printf("%s", buffer);
		socket_close(s);
	}
	
	/* client */
	else {
		Socket *c = socket_connect(argv[1], atoi(argv[2]));
		while (fgets(buffer, 1024, stdin)) socket_write(c, buffer);
		socket_close(c);
	}
	
	free(buffer);
	return 0;
}
