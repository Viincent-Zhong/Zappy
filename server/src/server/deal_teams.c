/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** deal_teams
*/

#include <unistd.h>
#include <string.h>
#include "server.h"

team_t *search_teams(server_t *server, char *name)
{
    for (team_t *team = TAILQ_FIRST(&server->params.team), *tmp;
    team != NULL; team = tmp) {
        if (strcmp(team->name, name) == 0)
            return team;
        tmp = TAILQ_NEXT(team, next_team);
    }
    return NULL;
}
