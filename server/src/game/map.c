/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** map
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "server.h"

void refill_map(cell_t **map, element_t bag)
{
    for (int i = 0; map[i]; ++i)
        for (int j = 0; map[i][j].end == 0; ++j)
            add_ressource_to_cell(&map[i][j], &bag);
    if (bag.deraumere != 0 || bag.food != 0 ||
    bag.linemate != 0 || bag.mendiane != 0 ||
    bag.phiras != 0 || bag.sibur != 0 || bag.thystame != 0) {
        refill_map(map, bag);
    }
}

void print_map(cell_t **map)
{
    for (int i = 0; map[i]; ++i) {
        printf("<");
        for (int j = 0; map[i][j].end == 0; ++j) {
            printf("%d%d%d%d%d%d%d", map[i][j].elem.food,
            map[i][j].elem.linemate, map[i][j].elem.deraumere,
            map[i][j].elem.sibur, map[i][j].elem.mendiane,
            map[i][j].elem.phiras, map[i][j].elem.thystame);
            printf(" %d %d", map[i][j].nbr_player, map[i][j].nbr_egg);
            printf("|");
        }
        printf(">\n");
    }
    printf("\n");
}

cell_t **init_map(params_t *params, element_t *distribution)
{
    int quant = params->height * params->width;
    element_t distribute = {quant * 0.5, quant * 0.3, quant * 0.15,
    quant * 0.1, quant * 0.1, quant * 0.08, quant * 0.05};
    cell_t **map;

    *distribution = distribute;
    srand(time(NULL));
    map = malloc(sizeof(cell_t *) * (params->height + 1));
    for (int i = 0; i < params->height; ++i) {
        map[i] = malloc(sizeof(cell_t) * (params->width + 1));
        memset(map[i], 0, sizeof(cell_t) * (params->width + 1));
        map[i][params->width].end = 1;
    }
    map[params->height] = NULL;
    refill_map(map, *distribution);
    return map;
}
