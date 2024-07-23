/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** end_incantation
*/

#include "server.h"

void event_end_incantation(server_t *server, int x, int y, int result)
{
    if (x >= server->params.width || y >= server->params.height)
        return;
    ping_all_graphicals(server,
    format_message("pie %d %d %d\n", x, y, result));
}
