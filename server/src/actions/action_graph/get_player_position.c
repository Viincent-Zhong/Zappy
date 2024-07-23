/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** get_player_position
*/

#include <stdlib.h>
#include <stdio.h>
#include "server.h"

void action_get_player_position(server_t *serv, client_t *client, char *str)
{
    char **av = parse_string(str, " ");
    int ac = 0;
    char *msg = NULL;
    player_t *player;

    if (av == NULL)
        return;
    for (ac = 0; av[ac]; ++ac);
    if (ac != 1)
        return;
    if (!(player = search_player(serv, av[0])))
        return;
    msg = format_message("ppo %d %d %d %d\n", player->id, player->x,
    player->y, player->direction);
    if (!msg)
        return;
    send_message(&serv->net, client->clid.fd, msg);
    free(msg);
}
