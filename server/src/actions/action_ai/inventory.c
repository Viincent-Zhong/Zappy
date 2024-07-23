/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** inventory.c
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

void action_inventory(server_t *serv, client_t *client, char *str)
{
    char *message = format_message("[food %d, linemate %d, deraumere %d, "
    "sibur %d, mendiane %d, phiras %d, thystame %d]\n",
    client->player->inventory.food, client->player->inventory.linemate,
    client->player->inventory.deraumere,
    client->player->inventory.sibur,
    client->player->inventory.mendiane,
    client->player->inventory.phiras,
    client->player->inventory.thystame);
    dprintf(STDERR_FILENO, "%d inventory: message\n", client->player->id);
    send_message(&serv->net, client->clid.fd, message);
    free(message);
}
