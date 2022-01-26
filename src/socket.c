#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "socket.h"

#undef socket_open
#undef socket_connect
#undef socket_read
#undef socket_write
#undef socket_printf

#ifdef _WIN32
    #include <alloc.h>
    #define MALLOC_SIZE(x) _msize(x)
#elif __APPLE__
    #include <malloc/malloc.h>
    #define MALLOC_SIZE(x) malloc_size(x)
#else
    #include <malloc.h>
    #define MALLOC_SIZE(x) malloc_usable_size(x)
#endif

struct Socket {
    int sockfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
    int type, protocol;
};

/**
 * Creates a struct Socket and returns a pointer to it
 */
Socket *
socket_open(int vargc, ...)
{
    /* parse va args */
    va_list vargp;
    va_start(vargp, vargc);
    
    int port = 0,
        type = SOCK_STREAM,
        protocol = 0,
        queue = 16;
    sa_family_t family = AF_INET;
    /* assign custom values if present */
    for (int i = 0; i < vargc; i++) {
        if (i == 0) port = va_arg(vargp, int);
        else if (i == 1) type = va_arg(vargp, int);
        else if (i == 2) protocol = va_arg(vargp, int);
        else if (i == 3) family = (sa_family_t) va_arg(vargp, int);
        else if (i == 4) queue = va_arg(vargp, int);
    }
    va_end(vargp);

    /* init */
    Socket *s = (Socket *) malloc(sizeof(Socket));
    if (!s) {
        fprintf(stderr, "socket_open: malloc error\n");
        return NULL;
    }
    memset(s, 0, sizeof(Socket));
    s -> type = type;
    s -> protocol = protocol;

    if ((s -> sockfd = socket(family, type, protocol)) == - 1) {
        fprintf(stderr, "socket_open: cannot create new socket\n");
        return NULL;
    }

    s -> servaddr.sin_family      = family;
    s -> servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    s -> servaddr.sin_port        = htons(port);

    if (bind(s -> sockfd, (struct sockaddr *) &s -> servaddr,
             sizeof(struct sockaddr_in)) == - 1) {
        fprintf(stderr, "socket_open: cannot bind new socket\n");
        return NULL;
    }

    /* connection-oriented protocols need to call listen() */
    if (type == SOCK_STREAM || type == SOCK_SEQPACKET) {
        if (listen(s -> sockfd, queue) == - 1) {
            fprintf(stderr, "socket_open: cannot listen new socket\n");
            return NULL;
        }
    }
    return s;
}

/**
 * Opens a TCP connection on given socket (blocking call)
 * return: file descriptor int for the recently accepted connection
 */
int
socket_accept(Socket *s)
{
    if (!(s -> type == SOCK_STREAM || s -> type == SOCK_SEQPACKET)) return - 1;
    
    if (s -> type == SOCK_STREAM || s -> type == SOCK_SEQPACKET) {
        unsigned int len = sizeof(s -> cliaddr);
        if ((s -> connfd = accept(s -> sockfd,
                                  (struct sockaddr *) &s -> cliaddr,
                                  &len)) == - 1) {
            fprintf(stderr, "socket_accept: cannot accept connection\n");
            return - 1;
        }
        return s -> connfd;
    }
    return - 1;
}

/**
 * Tries to read the socket and copy data to given buffer
 * return: number of bytes read.
 */
ssize_t
socket_read(int vargc, ...)
{
    if (vargc < 2) fprintf(stderr, "socket_read: not enough args!");
    /* parse va args */
    va_list vargp;
    va_start(vargp, vargc);
    
    struct Socket *s = NULL;
    void *buffer = NULL;
    size_t buffersize = 0;
    int flags = 0;
    /* assign custom values */
    for (int i = 0; i < vargc; i++) {
        if (i == 0) s = va_arg(vargp, struct Socket *);
        else if (i == 1) buffer = va_arg(vargp, void *);
        else if (i == 2) buffersize = va_arg(vargp, size_t);
        else if (i == 3) flags = va_arg(vargp, int);
    }
    va_end(vargp);
    /* attempts to determine buffersize */
    if (!buffersize) buffersize = MALLOC_SIZE(buffer);
    if (!buffersize) {
        fprintf(stderr, "socket_read: cannot determine buffer size\n");
        return 0;
    }

    /* wipes buffer clean before reading */
    memset(buffer, 0, buffersize);
    /* server -> client */
    if (s -> connfd) return recv(s -> connfd, buffer, buffersize, flags);
    /* client -> server */
    else return recv(s -> sockfd, buffer, buffersize, flags);
}

/**
 * Returns Socket's port number
 */
int
socket_port(Socket *s)
{
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);
    if (getsockname(s -> sockfd, (struct sockaddr *)&sin, &len) != - 1)
        return ntohs(sin.sin_port);
    return - 1;
}

/**
 * Attempts to connect to a remote server
 */
Socket *
socket_connect(int vargc, ...)
{
    if (vargc < 2) fprintf(stderr, "socket_connect: not enough args!");
    /* parse va args */
    va_list vargp;
    va_start(vargp, vargc);
    
    char *address = NULL;
    int port = 0,
        type = SOCK_STREAM,
        protocol = 0;
    sa_family_t family = AF_INET;
    /* assign custom values */
    for (int i = 0; i < vargc; i++) {
        if (i == 0) address = va_arg(vargp, char *);
        else if (i == 1) port = va_arg(vargp, int);
        else if (i == 2) type = va_arg(vargp, int);
        else if (i == 3) protocol = va_arg(vargp, int);
        else if (i == 4) family = (sa_family_t) va_arg(vargp, int);
    }
    va_end(vargp);

    /* init */
    Socket *s = (Socket *) malloc(sizeof(Socket));
    if (!s) {
        fprintf(stderr, "socket_connect: malloc error\n");
        return NULL;
    }
    memset(s, 0, sizeof(Socket));
    s -> type = type;
    s -> protocol = protocol;

    if ((s -> sockfd = socket(family, type, protocol)) == - 1) {
        fprintf(stderr, "socket_connect: cannot create new socket\n");
        return NULL;
    }

    s -> servaddr.sin_family      = family;
    s -> servaddr.sin_addr.s_addr = inet_addr(address);
    s -> servaddr.sin_port        = htons(port);

    /* attempts to connect to remote server */
    if (connect(s -> sockfd, (struct sockaddr *) &s -> servaddr,
                sizeof(struct sockaddr_in)) != 0) {
        fprintf(stderr, "socket_connect: cannot connect to server\n");
        return NULL;
    }

    return s;
}

/**
 * Writes given message on given socket
 * return: number of bytes written
 */
ssize_t
socket_write(int vargc, ...)
{
    if (vargc < 2) fprintf(stderr, "socket_write: not enough args!");
    /* parse va args */
    va_list vargp;
    va_start(vargp, vargc);
    
    struct Socket *s = NULL;
    void *buffer = NULL;
    size_t buffersize = 0;
    int flags = 0;
    /* assign custom values */
    for (int i = 0; i < vargc; i++) {
        if (i == 0) s = va_arg(vargp, struct Socket *);
        else if (i == 1) buffer = va_arg(vargp, void *);
        else if (i == 2) buffersize = va_arg(vargp, size_t);
        else if (i == 3) flags = va_arg(vargp, int);
    }
    va_end(vargp);
    /* attempts to determine buffersize */
    if (!buffersize) buffersize = MALLOC_SIZE(buffer);
    if (!buffersize) {
        fprintf(stderr, "socket_write: cannot determine message length\n");
        return 0;
    }
    /* server -> client */
    if (s -> connfd) return send(s -> connfd, buffer, buffersize, flags);
    /* client -> server */
    else return send(s -> sockfd, buffer, buffersize, flags);
}

/**
 * Writes formatted message on given socket
 * return: number of bytes written
 */
ssize_t
socket_printf(Socket *s, char *fmsg, ...)
{
    /* parse va args */
    va_list vargp;
    va_start(vargp, fmsg);
    ssize_t n = vsnprintf(NULL, 0, fmsg, vargp);
    va_end(vargp);
    
    if (n >= 0) {
        va_start(vargp, fmsg);
        char *buffer = malloc(n + 1);
        if (!buffer) {
            fprintf(stderr, "socket_printf: cannot malloc buffer\n");
            return 0;
        }
        vsnprintf(buffer, n + 1, fmsg, vargp);
        va_end(vargp);
        ssize_t bytes_written = socket_write(3, s, buffer, strlen(buffer));
        free(buffer);
        return bytes_written;
    }
    return socket_write(3, s, fmsg, strlen(fmsg));
}

/**
 * Returns IPv4 address of client in printable format
 */
char *
socket_client_ip(Socket *s)
{
    return inet_ntoa(s -> cliaddr.sin_addr);
}

/**
 * Returns IPv4 address of server in printable format
 */
char *
socket_server_ip(Socket *s)
{
    struct sockaddr_in local_address;
    socklen_t address_length = sizeof(local_address);;
    getsockname(s -> connfd, (struct sockaddr*) &local_address, &address_length);

    return inet_ntoa(local_address.sin_addr);
}

/**
 * Closes socket and frees malloc'd memory
 */
void
socket_close(Socket *s)
{
    shutdown(s -> sockfd, SHUT_RDWR);
    close(s -> sockfd);
    free(s);
}

/**
 * Closes current connection
 */
void
socket_finish(Socket *s)
{
    shutdown(s -> connfd, SHUT_RDWR);
    close(s -> connfd);
}
