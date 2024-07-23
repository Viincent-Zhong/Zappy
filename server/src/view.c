/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** view.c
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"

static size_t get_size(const cell_t *cell)
{
    size_t size = 0;

    size += cell->nbr_player * 10 + cell->nbr_egg * 7 + cell->elem.deraumere *
    13 + cell->elem.food * 8 + cell->elem.linemate * 12 + cell->elem.mendiane *
    12 + cell->elem.phiras * 10 + cell->elem.sibur * 9 + cell->elem.thystame *
    12;
    return size;
}

char *get_case(const cell_t *cell)
{
    int len = get_size(cell);
    char *str = malloc(sizeof(char) * (len + 1));

    str[0] = 0;
    for (int i = 0; i != cell->nbr_player; ++i, strcat(str, "player "));
    for (int i = 0; i != cell->nbr_egg; ++i, strcat(str, "egg "));
    for (int i = 0; i != cell->elem.deraumere; ++i, strcat(str, "deraumere "));
    for (int i = 0; i != cell->elem.food; ++i, strcat(str, "food "));
    for (int i = 0; i != cell->elem.linemate; ++i, strcat(str, "linemate "));
    for (int i = 0; i != cell->elem.mendiane; ++i, strcat(str, "mendiane "));
    for (int i = 0; i != cell->elem.phiras; ++i, strcat(str, "phiras "));
    for (int i = 0; i != cell->elem.sibur; ++i, strcat(str, "sibur "));
    for (int i = 0; i != cell->elem.thystame; ++i, strcat(str, "thystame "));
    str[len] = '\0';
    return str;
}

static void replace_view(int *beguin_x, int *beguin_y, const unsigned int *dim)
{
    if (*beguin_x < 0)
        *beguin_x = dim[0] - 1;
    if (*beguin_x > (int)(dim[0] - 1))
        *beguin_x = 0;
    if (*beguin_y < 0)
        *beguin_y = dim[1] - 1;
    if (*beguin_y > (int)(dim[1] - 1))
        *beguin_y = 0;
}

void update_beguin_view(int *beguin_x, int *beguin_y,
const enum direction dir, const unsigned int *dim)
{
    if (dir == NORTH) {
        --*beguin_y;
        --*beguin_x;
    }
    if (dir == SOUTH) {
        ++*beguin_y;
        ++*beguin_x;
    }
    if (dir == WEST) {
        ++*beguin_y;
        --*beguin_x;
    }
    if (dir == EAST) {
        --*beguin_y;
        ++*beguin_x;
    }
    replace_view(beguin_x, beguin_y, dim);
}

void move_case_view(int *beguin_x, int *beguin_y,
const enum direction dir, const unsigned int *dim)
{
    int move_x = 0;
    int move_y = 0;

    if (dir == NORTH)
        move_x = 1;
    if (dir == SOUTH)
        move_x = -1;
    if (dir == WEST)
        move_y = -1;
    if (dir == EAST)
        move_y = 1;
    *beguin_x += move_x;
    *beguin_y += move_y;
    replace_view(beguin_x, beguin_y, dim);
}
