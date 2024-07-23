/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** deal_graphical
*/

#include <stdio.h>
#include <stdlib.h>
#include "event.h"
#include "actions.h"

void ping_all_graphicals(server_t *server, char *message)
{
    if (!message)
        return;
    for (socket_list_t *graph = TAILQ_FIRST(&server->graphs), *tmp;
    graph != NULL; graph = tmp) {
        send_message(&server->net, graph->fd, message);
        tmp = TAILQ_NEXT(graph, next_socket);
    }
    free(message);
}

socket_list_t *get_graphicals_by_fd(server_t *server, int fd)
{
    for (socket_list_t *graph = TAILQ_FIRST(&server->graphs), *tmp;
    graph != NULL; graph = tmp) {
        if (graph->fd == fd)
            return graph;
        tmp = TAILQ_NEXT(graph, next_socket);
    }
    return NULL;
}

void graph_first_connection(server_t *server, client_t *client)
{
    action_get_map_size(server, client, NULL);
    action_get_content_map(server, client, NULL);
    action_get_name_teams(server, client, NULL);
    for (client_t *cli = server->clients.tqh_first; cli != NULL;
    cli = cli->next_client.tqe_next)
        if (cli->player)
            event_player_connection(server, cli->player);
}
