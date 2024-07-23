/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** server.c
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/queue.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <time.h>
#include "server.h"
#include "params.h"

static bool init_server(server_t *serv, const unsigned int port)
{
    if (!init_socket(&serv->serv, port))
        return false;
    TAILQ_INIT(&serv->clients);
    TAILQ_INIT(&serv->graphs);
    TAILQ_INIT(&serv->eggs);
    serv->incantation_id = 1;
    serv->net.max_fd = serv->serv.fd;
    serv->nbr_players = 0;
    serv->nbr_eggs = 0;
    serv->timeout.tv_sec = 1;
    serv->timeout.tv_usec = 0;
    serv->time_refill = 20;
    serv->victory = false;
    srand(time(NULL));
    serv->map = init_map(&serv->params, &serv->distribution);
    return true;
}

bool select_whole_server(server_t *serv)
{
    serv->tmp = serv->timeout;
    FD_ZERO(&serv->net.rdfs);
    FD_ZERO(&serv->net.wdfs);
    FD_ZERO(&serv->net.edfs);
    FD_SET(serv->serv.fd, &serv->net.rdfs);
    for (client_t *np = serv->clients.tqh_first; np != NULL;
    np = np->next_client.tqe_next)
        FD_SET(np->clid.fd, &serv->net.rdfs);
    if (select(serv->net.max_fd + 1, &serv->net.rdfs, &serv->net.wdfs,
    &serv->net.edfs, &serv->tmp) == -1) {
        perror("Server stop: error");
        return false;
    }
    return true;
}

bool server(int ac, char **av)
{
    server_t serv;
    socket_t client;

    if (av == NULL || !get_params(ac, av, &serv.params)) {
        dprintf(STDERR_FILENO, "Error in params, see: ./zappy_server -help\n");
        return false;
    }
    if (!init_server(&serv, serv.params.port))
        return false;
    printf("server running: %d\n", serv.params.port);
    while (!serv.victory) {
        if (!select_whole_server(&serv))
            return false;
        if (FD_ISSET(serv.serv.fd, &serv.net.rdfs))
            client_connection(&serv, &client, serv.serv);
        else
            detect_clients(&serv);
    }
    return true;
}
