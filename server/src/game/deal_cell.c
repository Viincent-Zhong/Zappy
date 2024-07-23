/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** deal_cell
*/

#include <stdlib.h>
#include "map.h"

static void generate_ressource(int *value, int *stock)
{
    if (*stock > 0 && *value < 3) {
        ++(*value);
    }
    if (*stock > 0)
        --(*stock);
}

void add_ressource_to_cell(cell_t *cell, element_t *bag)
{
    if (rand() % 2 == 0)
        generate_ressource(&cell->elem.food, &bag->food);
    if (rand() % 3 == 0)
        generate_ressource(&cell->elem.linemate, &bag->linemate);
    if (rand() % 6 == 0)
        generate_ressource(&cell->elem.deraumere, &bag->deraumere);
    if (rand() % 10 == 0)
        generate_ressource(&cell->elem.sibur, &bag->sibur);
    if (rand() % 10 == 0)
        generate_ressource(&cell->elem.mendiane, &bag->mendiane);
    if (rand() % 10 == 0)
        generate_ressource(&cell->elem.phiras, &bag->phiras);
    if (rand() % 20 == 0)
        generate_ressource(&cell->elem.thystame, &bag->thystame);
}
