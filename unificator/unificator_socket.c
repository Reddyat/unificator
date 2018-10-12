#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

#include "unificator_socket.h"

int unificator_socket_init(UnificatorSocket * unificator_socket, const char * server_ip, const uint16_t server_port)
{
    unificator_socket->socket = socket(AF_INET, SOCK_DGRAM, 0);

    if( unificator_socket->socket < 0 )
    {
        perror("Error : cannot open socket");
        return -1;
    }

    bzero(&(unificator_socket->server_address),sizeof(unificator_socket->server_address));
    unificator_socket->server_address.sin_family = AF_INET;
    unificator_socket->server_address.sin_addr.s_addr = inet_addr(server_ip);
    unificator_socket->server_address.sin_port = htons(server_port);

    return 0;
}

int unificator_socket_send(UnificatorSocket * unificator_socket, const char * message, const size_t message_size)
{
    int send_result = sendto(unificator_socket->socket, message,
        message_size, 0, (struct sockaddr *) &(unificator_socket->server_address), sizeof(unificator_socket->server_address));

    if ( send_result < 0 )
    {
        perror("cannot send message");
        close(unificator_socket->socket);
        return -1;
    }

    return 0;
}

void unificator_socket_close(UnificatorSocket * unificator_socket)
{
    close(unificator_socket->socket);
}