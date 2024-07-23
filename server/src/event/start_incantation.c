/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** start_incantation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

void who_incantating(char **message, char **part, client_t *cli, int index[2])
{
    *message = format_message("%s %d ", *part, cli->player->id);
    free(*part);
    *part = format_message("%s", *message);
    if (index[0] + 1 == index[1])
        return;
    free(*message);
}

void event_start_incantation(server_t *server, int x, int y, int level)
{
    char *message;
    char *part = format_message("pic %d %d %d", x, y, level);
    int i = 0;
    int nbr_player;

    if (x >= server->params.width || y >= server->params.height)
        return;
    nbr_player = server->map[y][x].nbr_player;
    for (client_t *cli = TAILQ_FIRST(&server->clients), *tmp;
    cli != NULL && i < nbr_player; cli = tmp, ++i) {
        if (cli->player && cli->player->x == x && cli->player->y == y) {
            who_incantating(&message, &part, cli, (int[2]){i, nbr_player});
        }
        tmp = TAILQ_NEXT(cli, next_client);
    }
    part = format_message("%s\n", message);
    free(message);
    ping_all_graphicals(server, part);
}
