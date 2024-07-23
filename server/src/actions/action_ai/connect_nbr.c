/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** connect_nbr.c
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "server.h"

void action_connect_nbr(server_t *serv, client_t *client, char *str)
{
    char *message;
    team_t *team = search_teams(serv, client->player->team_name);

    if (!team) {
        send_message(&serv->net, client->clid.fd, "0\n");
        return;
    }
    dprintf(STDERR_FILENO, "%s: %d/%d connected players\n",
    team->name, team->nbr_client, team->nbr_clientMax);
    message = format_message("%d\n", team->nbr_clientMax - team->nbr_client);
    send_message(&serv->net, client->clid.fd, message);
    free(message);
}
