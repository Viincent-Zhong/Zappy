/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** forward.c
*/

#include <unistd.h>
#include <stdio.h>
#include "event.h"

static void forward_player(server_t *serv, client_t *client)
{
    int move_x = 0;
    int move_y = 0;

    if (client->player->direction == NORTH)
        move_y = -1;
    if (client->player->direction == SOUTH)
        move_y = 1;
    if (client->player->direction == WEST)
        move_x = -1;
    if (client->player->direction == EAST)
        move_x = 1;
    --serv->map[client->player->y][client->player->x].nbr_player;
    client->player->x += move_x;
    client->player->y += move_y;
    client->player->incant = 0;
}

void action_forward(server_t *serv, client_t *client, char *str)
{
    dprintf(STDERR_FILENO, "Player %d from team %s forward %d %d ->",
    client->player->id, client->player->team_name, client->player->x,
    client->player->y);
    forward_player(serv, client);
    if (client->player->x < 0)
        client->player->x = serv->params.width - 1;
    if (client->player->x >= (int)serv->params.width)
        client->player->x = 0;
    if (client->player->y < 0)
        client->player->y = serv->params.height - 1;
    if (client->player->y >= (int)serv->params.height)
        client->player->y = 0;
    ++serv->map[client->player->y][client->player->x].nbr_player;
    dprintf(STDERR_FILENO, " %d %d\n", client->player->x, client->player->y);
    send_message(&serv->net, client->clid.fd, "ok\n");
    event_player_moved(serv, client->player);
}
