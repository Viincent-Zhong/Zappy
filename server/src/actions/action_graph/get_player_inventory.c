/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** get_player_inventory
*/

#include <stdio.h>
#include <stdlib.h>
#include "server.h"

static void send_player_inventory(server_t *serv, int fd, player_t *player)
{
    char *msg = format_message("pin %d %d %d %d %d %d %d %d %d %d\n",
    player->id, player->x, player->y, player->inventory.food,
    player->inventory.linemate, player->inventory.deraumere,
    player->inventory.sibur, player->inventory.mendiane,
    player->inventory.phiras, player->inventory.thystame);

    if (!msg)
        return;
    send_message(&serv->net, fd, msg);
    free(msg);
}

void action_get_player_inventory(server_t *serv, client_t *client, char *str)
{
    char **av = parse_string(str, " ");
    int ac = 0;
    int id = 0;

    if (av == NULL)
        return;
    for (ac = 0; av[ac]; ++ac);
    if (ac != 1)
        return;
    id = atoi(av[0]);
    for (client_t *cli = serv->clients.tqh_first; cli != NULL;
    cli = cli->next_client.tqe_next)
        if (!cli->init && cli->player && cli->player->id == id) {
            send_player_inventory(serv, client->clid.fd, cli->player);
            return;
        }
}
