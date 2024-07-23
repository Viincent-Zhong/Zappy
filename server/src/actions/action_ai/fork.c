/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** fork.c
*/

#include <unistd.h>
#include <stdio.h>
#include "event.h"

void action_fork(server_t *serv, client_t *client, char *str)
{
    create_egg(serv, client->player);
    if (serv->eggs.tqh_first) {
        dprintf(STDERR_FILENO, "Player %d create egg at pos: %d %d\n",
        client->player->id, serv->eggs.tqh_first->x,
        serv->eggs.tqh_first->y);
        send_message(&serv->net, client->clid.fd, "ok\n");
        event_layed_egg(serv, serv->eggs.tqh_first);
    }
}
