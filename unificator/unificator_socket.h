#ifndef UNIFICATOR_SOCKET_H
#define UNIFICATOR_SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>

typedef struct UnificatorSocket {
	int socket;
	struct sockaddr_in server_address;
} UnificatorSocket;

/**
  * @brief Open and initialise the socket in order to send messages.
  * @return 0 if succeed, -1 otherwise
  */
int unificator_socket_init(UnificatorSocket * unificator_socket, const char * server_ip, const uint16_t server_port);

/**
  * @brief Send the message through the socket.
  * @return 0 if succeed, -1 otherwise.
  */
int unificator_socket_send(UnificatorSocket * unificator_socket, const char * message, const size_t message_size);

/**
  * @brief Close the socket.
  */
void unificator_socket_close(UnificatorSocket * unificator_socket);

#endif /* UNIFICATOR_SOCKET_H */