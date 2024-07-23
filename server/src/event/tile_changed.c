/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** tile_changed
*/

#include "event.h"

void event_tile_changed(server_t *serv, int x, int y)
{
    element_t tile = serv->map[y][x].elem;

    ping_all_graphicals(serv,
    format_message("bct %d %d %d %d %d %d %d %d %d\n", x, y,
    tile.food, tile.linemate, tile.deraumere, tile.sibur, tile.mendiane,
    tile.phiras, tile.thystame));
}
