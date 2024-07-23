/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** get_name_teams
*/

#include <stdio.h>
#include <stdlib.h>
#include "server.h"

void action_get_name_teams(server_t *serv, client_t *client, char *str)
{
    char *msg;

    for (team_t *team = serv->params.team.tqh_first; team != NULL;
    team = team->next_team.tqe_next) {
        msg = format_message("tna %s\n", team->name);
        if (!msg)
            return;
        send_message(&serv->net, client->clid.fd, msg);
        free(msg);
    }
}
