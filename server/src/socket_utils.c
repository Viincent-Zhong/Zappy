/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** socket_utils
*/

#include <stdio.h>
#include "server.h"

static bool norm_init_socket(socket_t *sock)
{
    if (bind(sock->fd, (struct sockaddr *) &sock->addr,
    sizeof(sock->addr)) == -1) {
        perror("Bind");
        return false;
    }
    if (listen(sock->fd, SOMAXCONN) == -1) {
        perror("Listen");
        return false;
    }
    return true;
}

bool init_socket(socket_t *sock, int port)
{
    if ((sock->fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket");
        return false;
    }
    if (setsockopt(sock->fd, SOL_SOCKET, SO_REUSEADDR, &(int){1},
    sizeof(int)) < 0) {
        perror("setsockopt");
        return false;
    }
    sock->addrlen = sizeof(sock->addr);
    sock->addr.sin_family = AF_INET;
    sock->addr.sin_addr.s_addr = INADDR_ANY;
    sock->addr.sin_port = htons(port);
    return norm_init_socket(sock);
}
