/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** map_changed
*/

#include "event.h"

static void send_tiles_line(server_t *serv, int y)
{
    element_t tile = {0};

    for (unsigned int x = 0; x < serv->params.width; ++x) {
        tile = serv->map[y][x].elem;
        ping_all_graphicals(serv,
        format_message("bct %u %u %d %d %d %d %d %d %d\n", x, y,
        tile.food, tile.linemate, tile.deraumere, tile.sibur, tile.mendiane,
        tile.phiras, tile.thystame));
    }
}

void event_map_changed(server_t *serv)
{
    for (unsigned int y = 0; y < serv->params.height; ++y) {
        send_tiles_line(serv, y);
    }
}
