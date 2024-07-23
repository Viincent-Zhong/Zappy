/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** left.c
*/

#include <unistd.h>
#include <stdio.h>
#include "event.h"

char *get_direction_name(enum direction dir)
{
    if (dir == NORTH)
        return "NORTH";
    if (dir == SOUTH)
        return "SOUTH";
    if (dir == WEST)
        return "WEST";
    if (dir == EAST)
        return "EAST";
    return "NORTH";
}

void action_left(server_t *serv, client_t *client, char *str)
{
    dprintf(STDERR_FILENO, "%d turn left, %s -> ",
    client->player->id, get_direction_name(client->player->direction));
    --client->player->direction;
    if (client->player->direction == 0)
        client->player->direction = WEST;
    dprintf(STDERR_FILENO, "%s\n",
    get_direction_name(client->player->direction));
    send_message(&serv->net, client->clid.fd, "ok\n");
    event_player_moved(serv, client->player);
}
