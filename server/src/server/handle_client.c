/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** handle_client.c
*/

#include <sys/queue.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "event.h"

void add_client(server_t *server, socket_t sock)
{
    client_t *tmp = malloc(sizeof(client_t));

    tmp->clid = sock;
    tmp->player = NULL;
    tmp->init = true;
    tmp->graphical = false;
    tmp->start_chrono = false;
    tmp->chrono_command = 0;
    tmp->chrono_death = 0.0;
    tmp->time_command = 0;
    TAILQ_INIT(&tmp->list_command);
    tmp->nbr_command = 0;
    send_message(&server->net, sock.fd, "WELCOME\n");
    TAILQ_INSERT_HEAD(&server->clients, tmp, next_client);
}

void client_connection(server_t *server, socket_t *client, socket_t serv)
{
    client->addrlen = sizeof(client->addr);
    if ((client->fd = accept(serv.fd, (struct sockaddr *) &client->addr,
    (socklen_t *) &client->addrlen)) == -1)
        return;
    if (client->fd > server->net.max_fd)
        server->net.max_fd = client->fd;
    add_client(server, *client);
}

void quit_server(server_t *serv, client_t *client)
{
    team_t *team = NULL;
    socket_list_t *graph;

    if (client->player) {
        if ((team = search_teams(serv, client->player->team_name)))
            --team->nbr_client;
        event_player_death(serv, client->player);
        free_clients_commands(client);
        free(client->player);
    }
    close(client->clid.fd);
    TAILQ_REMOVE(&serv->clients, client, next_client);
    if (client->graphical &&
    (graph = get_graphicals_by_fd(serv, client->clid.fd))) {
        TAILQ_REMOVE(&serv->graphs, graph, next_socket);
        free(graph);
    }
    free(client);
}

static bool client_message(server_t *serv, client_t *client)
{
    bool status = true;
    char *response = read_message(client->clid.fd);

    if (response == NULL)
        return false;
    if (client->init)
        status = connect_to_team(serv, client, response);
    else
        function_to_timer(response, serv, client);
    free(response);
    return status;
}

void detect_clients(server_t *serv)
{
    handle_map(serv);
    handle_eggs(serv);
    for (client_t *client = TAILQ_FIRST(&serv->clients), *tmp;
    client != NULL; client = tmp) {
        tmp = TAILQ_NEXT(client, next_client);
        if (client->clid.fd != -1 && FD_ISSET(client->clid.fd, &serv->net.rdfs)
        && !client_message(serv, client)) {
            quit_server(serv, client);
            continue;
        }
        if (!player_timer(serv, client))
            continue;
        if (client->nbr_command > 0)
            wait_action(serv, client);
    }
}
