/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** right.c
*/

#include <unistd.h>
#include <stdio.h>
#include "event.h"

void action_right(server_t *serv, client_t *client, char *str)
{
    dprintf(STDERR_FILENO, "%d turn right, %s -> ",
    client->player->id, get_direction_name(client->player->direction));
    ++client->player->direction;
    if (client->player->direction > WEST)
        client->player->direction = NORTH;
    dprintf(STDERR_FILENO, "%s\n",
    get_direction_name(client->player->direction));
    send_message(&serv->net, client->clid.fd, "ok\n");
    event_player_moved(serv, client->player);
}
