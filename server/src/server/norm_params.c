/*
** EPITECH PROJECT, 2022
** Project Zappy
** File description:
** norm_params.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "params.h"

bool get_width(params_t *params, char **av)
{
    if (!is_number(av[0])) {
        dprintf(STDERR_FILENO, ERROR_X);
        return false;
    }
    params->width = atoi(av[0]);
    if (params->width < 10 || params->width > 30) {
        dprintf(STDERR_FILENO, ERROR_X);
        return false;
    }
    return true;
}

bool get_height(params_t *params, char **av)
{
    if (!is_number(av[0])) {
        dprintf(STDERR_FILENO, ERROR_Y);
        return false;
    }
    params->height = atoi(av[0]);
    if (params->height < 10 || params->height > 30) {
        dprintf(STDERR_FILENO, ERROR_Y);
        return false;
    }
    return true;
}

bool get_name(params_t *params, char **av)
{
    for (int i = 0; av[i] != NULL; ++i) {
        if (strcmp(av[i], "-f") == 0 || strcmp(av[i], "-p") == 0 ||
        strcmp(av[i], "-x") == 0 || strcmp(av[i], "-y") == 0 ||
        strcmp(av[i], "-n") == 0 || strcmp(av[i], "-c") == 0)
            break;
        insert_team_name(params, av[i]);
    }
    return true;
}

bool get_client_nb(params_t *params, char **av)
{
    if (!is_number(av[0])) {
        dprintf(STDERR_FILENO, ERROR_C);
        return false;
    }
    params->clients_nb = atoi(av[0]);
    if (params->clients_nb < 1) {
        dprintf(STDERR_FILENO, ERROR_C);
        return false;
    }
    return true;
}

bool get_freq(params_t *params, char **av)
{
    if (!is_number(av[0]))
        return false;
    params->freq = atoi(av[0]);
    if (params->freq < 2 || params->freq > 10000) {
        dprintf(STDERR_FILENO, ERROR_F);
        return false;
    }
    return true;
}
