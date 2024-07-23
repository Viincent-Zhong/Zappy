/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** params.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "params.h"

static const fct_ptr_t tab[] = {{"-p", get_port}, {"-x", get_width},
    {"-y", get_height}, {"-n", get_name}, {"-c", get_client_nb},
    {"-f", get_freq}, {"", NULL}};

bool is_number(const char *str)
{
    if (str == NULL)
        return false;
    if (str[0] == '\0')
        return true;
    if (str[0] < '0' || str[0] > '9')
        return false;
    is_number(str + 1);
}

bool get_port(params_t *params, char **av)
{
    if (!is_number(av[0]))
        return false;
    params->port = atoi(av[0]);
    return true;
}

static bool handle_fct_ptr(params_t *params, char **av, int i)
{
    for (int j = 0; tab[j].fct != NULL; ++j)
        if (strcmp(tab[j].name, av[i]) == 0 &&
        !tab[j].fct(params, av + (i + 1)))
            return false;
    return true;
}

void insert_team_name(params_t *params, char *name)
{
    team_t *team = malloc(sizeof(team_t));

    team->name = malloc(sizeof(char) * (strlen(name) + 1));
    team->nbr_client = 0;
    team->nbr_clientMax = params->clients_nb;
    strcpy(team->name, name);
    TAILQ_INSERT_HEAD(&params->team, team, next_team);
}

bool get_params(int ac, char **av, params_t *params)
{
    unsigned int size = 0;

    TAILQ_INIT(&params->team);
    params->freq = INIT_FREQ;
    params->width = INIT_WIDTH;
    params->height = INIT_HEIGHT;
    params->clients_nb = INIT_CLIENT_NB;
    params->port = INIT_PORT;
    for (int i = 0; i != ac; ++i)
        if (!handle_fct_ptr(params, av, i))
            return false;
    for (team_t *tmp = params->team.tqh_first; tmp != NULL;
    tmp = tmp->next_team.tqe_next, ++size);
    if (size == 0)
        insert_team_name(params, INIT_TEAM_NAME);
    return true;
}
