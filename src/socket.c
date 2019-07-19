/**
 * Includes & Macros
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "socket.h"

#undef socket_open
#undef socket_connect
#undef socket_read
#undef socket_write

/**
 * Data Structures
 */
struct Socket {
    int sockFd, connFd;
    struct sockaddr_in servAddr, cliAddr;
    int type, protocol;
};

/**
 * socket_open(): abre uma porta TCP/UDP e retorna a Socket resultante
 * @port: porta que se deseja usar
 * @type: tipo de socket (TCP, UDP, ...)
 * @protocol: protocolo específico usado na conexão
 * @family: domínio da socket (AF_INET, ...)
 * @queue: número máximo de clientes que se deseja na porta
 *
 * @return: ponteiro para a struct recém criada
 */
Socket *
socket_open(int vargc, ...)
{
    /* parse va args */
    va_list vargp;
    va_start(vargp, vargc);
    /* initialize with default values */
    int port = 0,
        type = SOCK_STREAM,
        protocol = 0,
        family = AF_INET,
        queue = 16;
    /* assign custom values */
    for (int i = 0; i < vargc; i++) {
        if (i == 0) port = va_arg(vargp, int);
        else if (i == 1) type = va_arg(vargp, int);
        else if (i == 2) protocol = va_arg(vargp, int);
        else if (i == 3) family = va_arg(vargp, int);
        else if (i == 4) queue = va_arg(vargp, int);
    }
    va_end(vargp);
//    printf("port %d\ntype %d\nprotocol %d\nfamily %d\nqueue %d\n", port, type, protocol, family, queue);

    /* init */
    Socket *s = (Socket *) malloc(sizeof(Socket));
    if (!s) {
        fprintf(stderr, "socket_open: malloc error\n");
        return NULL;
    }
    /* Salva parâmetros iniciais que não serão salvos em outras EDs */
    s -> type = type;
    s -> protocol = protocol;

    /* Criação de um socket */
    if ((s -> sockFd = socket(family, type, protocol)) == -1) {
        fprintf(stderr, "socket_open: cannot create new socket\n");
        // TODO: quit
        return NULL;
    }

    /* Configuração da struct sockaddr_in */
    bzero(&s -> servAddr, sizeof(struct sockaddr_in));
    s -> servAddr.sin_family      = family;
    s -> servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    s -> servAddr.sin_port        = htons(port);

    /* Bind da porta */
    if (bind(s -> sockFd, (struct sockaddr *) &s -> servAddr, sizeof(struct sockaddr_in)) == -1) {
        fprintf(stderr, "socket_open: cannot bind new socket\n");
        return NULL;
    }

    /* Orientado a conexão: precisa chamar a função listen */
    if (type == SOCK_STREAM || type == SOCK_SEQPACKET) {
        if (listen(s -> sockFd, queue) == -1) {
            fprintf(stderr, "socket_open: cannot listen new socket\n");
            return NULL;
        }
    }
    
    /* porta aleatória */
    if (port == 0) printf("listening at port %d...\n", socket_port(s));
    
    return s;
}

/**
 * socket_await(): aguarda conexão do cliente - blocking call
 * @s: ponteiro para o socket que será lido
 *
 * @return: file descriptor para a nova conexão aberta
 */
int
socket_await(Socket *s)
{
    /* Orientado à mensagem: não precisa de accept, retorna -1 */
    if (!(s -> type == SOCK_STREAM || s -> type == SOCK_SEQPACKET)) return -1;
    /* Orientado a conexão: precisa chamar a função listen e accept */
    if (s -> type == SOCK_STREAM || s -> type == SOCK_SEQPACKET) {
        unsigned int len = sizeof(s -> cliAddr);
        if ((s -> connFd = accept(s -> sockFd, (struct sockaddr *) &s -> cliAddr, &len)) == -1) {
            fprintf(stderr, "socket_read: cannot accept on new socket\n");
            return -1;
        }
        else return s -> connFd;
    }
    
    else return -1;
}

/**
 * socket_read(): tenta ler mensagens e retorna no buffer
 * @s: ponteiro para o socket que será lido
 * @buffer: espaço na memória onde será escrita a mensagem
 * @bufferSize: tamanho máximo da mensagem
 * @flags: flags para a system call recv
 *
 * @return: número de bytes lidos
 */
int
socket_read(int vargc, ...)
{
    if (vargc < 2) fprintf(stderr, "socket_read(): not enough args!");
    /* parse va args */
    va_list vargp;
    va_start(vargp, vargc);
    /* initialize with default values */
    struct Socket *s = NULL;
    void *buffer = NULL;
    // TODO: inferir tamanho do buffer?
    size_t bufferSize = sizeof(buffer);
    int flags = 0;
    /* assign custom values */
    for (int i = 0; i < vargc; i++) {
        if (i == 0) s = va_arg(vargp, struct Socket *);
        else if (i == 1) buffer = va_arg(vargp, void *);
        else if (i == 2) bufferSize = va_arg(vargp, size_t);
        else if (i == 3) flags = va_arg(vargp, int);
    }
    va_end(vargp);
//    printf("recv: buffer %s\nbufferSize %zu\nflags %d\n", buffer, bufferSize, flags);
    if (vargc < 3) bufferSize = strlen(buffer);
    
    
    /* Zera o buffer e lê a mensagem se houver */
    memset(buffer, 0, strlen(buffer));
    
    return recv(s -> connFd, buffer, bufferSize, flags);
}

/**
 * socket_port(): busca o número da porta do socket
 * @s: socket o qual se deseja fechar
 *
 * @return: numero da porta
 */
int
socket_port(Socket *s)
{
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);
    if (getsockname(s -> sockFd, (struct sockaddr *)&sin, &len) != -1)
        return ntohs(sin.sin_port);
    return 0;
}

/**
 * socket_connect(): conecta a um servidor
 * @address: endereço IP ao qual se deseja conectar
 * @port: porta do processoa o qual se deseja conectar
 * @type: tipo de socket (TCP, UDP, ...)
 * @protocol: protocolo específico usado na conexão
 * @family: domínio da socket (AF_INET, ...)
 *
 * @return: ponteiro para a struct recém criada
 */
Socket *
socket_connect(int vargc, ...)
{
    if (vargc < 2) fprintf(stderr, "socket_connect(): not enough args!");
    /* parse va args */
    va_list vargp;
    va_start(vargp, vargc);
    /* initialize with default values */
    char *address = "127.0.0.1";
    int port = 0,
        type = SOCK_STREAM,
        protocol = 0,
        family = AF_INET;
    /* assign custom values */
    for (int i = 0; i < vargc; i++) {
        if (i == 0) address = va_arg(vargp, char *);
        else if (i == 1) port = va_arg(vargp, int);
        else if (i == 2) type = va_arg(vargp, int);
        else if (i == 3) protocol = va_arg(vargp, int);
        else if (i == 4) family = va_arg(vargp, int);
    }
    va_end(vargp);
//    printf("address %s\nport %d\ntype %d\nprotocol %d\nfamily %d\n", address, port, type, protocol, family);
    
    /* init */
    Socket *s = (Socket *) malloc(sizeof(Socket));
    if (!s) {
        fprintf(stderr, "socket_connect: malloc error\n");
        return NULL;
    }
    /* Salva parâmetros iniciais que não serão salvos em outras EDs */
    s -> type = type;
    s -> protocol = protocol;
    
    /* Criação de um socket */
    if ((s -> sockFd = socket(family, type, protocol)) == -1) {
        fprintf(stderr, "socket_connect: cannot create new socket\n");
        return NULL;
    }
    
    /* Configuração da struct sockaddr_in */
    bzero(&s -> servAddr, sizeof(struct sockaddr_in));
    s -> servAddr.sin_family      = family;
    s -> servAddr.sin_addr.s_addr = inet_addr(address);
    s -> servAddr.sin_port        = htons(port);
    
    /* Tenta conectar ao servidor */
    if (connect(s -> sockFd, (struct sockaddr *) &s -> servAddr, sizeof(struct sockaddr_in)) != 0) {
        fprintf(stderr, "socket_connect: cannot connect to server\n");
        return NULL;
    }
    
    return s;
}

/**
 * socket_write(): tenta escrever no socket
 * @s: ponteiro para o socket no qual será escrita a mensagem
 * @buffer: ponteiro para a mensagem
 * @bufferSize: tamanho da mensagem
 * @flags: flags opcionais para a chamada send
 *
 * @return: número de bytes escritos
 */
int
socket_write(int vargc, ...)
{
    if (vargc < 2) fprintf(stderr, "socket_write(): not enough args!");
    /* parse va args */
    va_list vargp;
    va_start(vargp, vargc);
    /* initialize with default values */
    struct Socket *s = NULL;
    void *buffer = NULL;
    // TODO: inferir tamanho do buffer?
    size_t bufferSize = sizeof(buffer);
    int flags = 0;
    /* assign custom values */
    for (int i = 0; i < vargc; i++) {
        if (i == 0) s = va_arg(vargp, struct Socket *);
        else if (i == 1) buffer = va_arg(vargp, void *);
        else if (i == 2) bufferSize = va_arg(vargp, size_t);
        else if (i == 3) flags = va_arg(vargp, int);
    }
    va_end(vargp);
    if (vargc < 3) bufferSize = strlen(buffer);
//    printf("send: buffer %s\nbufferSize %zu\nflags %d\n", buffer, bufferSize, flags);
    return send(s -> sockFd, buffer, bufferSize, flags);
}

/**
 * socket_close(): fecha o socket e libera memória
 * @s: socket o qual se deseja fechar
 */
void
socket_close(Socket *s)
{
    close(s -> sockFd);
    free(s);
}

/**
 * socket_test(): testa essa abstração
 * @return: 0 para sucesso e 1 para erro
 */
int
socket_test()
{
//    int pid = fork();
//
//    /* filho */
//    if (pid == 0) {
//        Socket *c = socket_connect(AF_INET, SOCK_STREAM, 0, "127.0.0.1", 7922);
//        socket_write(c, "sucesso", 8, 0);
//        socket_close(c);
//    }
//
//    /* pai */
//    else {
//        printf("socket_test():");
//        Socket *s = socket_open(AF_INET, SOCK_STREAM, 0, 7922, 16);
//        socket_await(s);
//        char buffer[16];
//        socket_read(s, buffer, 16, 0);
//        printf(" %s\n", buffer);
//        socket_close(s);
//        return 0;
//    }
    return 0;
}
