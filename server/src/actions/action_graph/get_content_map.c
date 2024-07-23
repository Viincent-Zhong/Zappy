/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** get_content_map
*/

#include <stdlib.h>
#include "server.h"

bool send_line_of_tile(server_t *serv, client_t *client, int y)
{
    element_t tile = {0};
    char *msg;

    for (unsigned int x = 0; x < serv->params.width; ++x) {
        tile = serv->map[y][x].elem;
        msg = format_message("bct %u %u %d %d %d %d %d %d %d\n", x, y,
        tile.food, tile.linemate, tile.deraumere, tile.sibur, tile.mendiane,
        tile.phiras, tile.thystame);
        if (!msg)
            continue;
        if (!send_message(&serv->net, client->clid.fd, msg)) {
            free(msg);
            return false;
        }
        free(msg);
    }
    return true;
}

void action_get_content_map(server_t *serv, client_t *client, char *str)
{
    for (unsigned int y = 0; y < serv->params.height; ++y) {
        if (!send_line_of_tile(serv, client, y))
            return;
    }
}
