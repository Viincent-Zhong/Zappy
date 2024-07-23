/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** free_map
*/

#include <stdio.h>
#include <stdlib.h>
#include "map.h"

void free_map(cell_t **map)
{
    if (!map)
        return;
    for (int i = 0; map[i]; ++i) {
        free(map[i]);
    }
    free(map);
}
