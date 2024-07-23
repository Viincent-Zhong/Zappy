/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** victory.c
*/

#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

static bool team_win(server_t *serv, const char *team_name)
{
    unsigned int nb = 0;

    for (client_t *tmp = serv->clients.tqh_first; tmp != NULL;
    tmp = tmp->next_client.tqe_next)
        if (strcmp(tmp->player->team_name, team_name) == 0 &&
        tmp->player->level >= 8)
            ++nb;
    if (nb >= 6)
        return true;
    return false;
}

void check_victory(server_t *serv)
{
    for (team_t *tmp = serv->params.team.tqh_first; tmp != NULL;
    tmp = tmp->next_team.tqe_next)
        if (team_win(serv, tmp->name)) {
            serv->victory = true;
            return;
        }
}