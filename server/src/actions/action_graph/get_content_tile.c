/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** get_content_tile
*/

#include <stdio.h>
#include <stdlib.h>
#include "server.h"

static void send_tile(server_t *serv, client_t *client, int x, int y)
{
    element_t tile = serv->map[y][x].elem;
    char *msg = format_message("bct %d %d %d %d %d %d %d %d %d\n", x, y,
    tile.food, tile.linemate, tile.deraumere, tile.sibur, tile.mendiane,
    tile.phiras, tile.thystame);

    if (!msg)
        return;
    send_message(&serv->net, client->clid.fd, msg);
}

void action_get_content_tile(server_t *serv, client_t *client, char *str)
{
    char **av = parse_string(str, " ");
    int ac = 0;
    int x = 0;
    int y = 0;

    if (av == NULL)
        return;
    for (ac = 0; av[ac]; ++ac);
    if (ac != 2)
        return;
    x = atoi(av[0]);
    y = atoi(av[1]);
    if (x >= serv->params.width || y >= serv->params.height)
        return;
    send_tile(serv, client, x, y);
}
