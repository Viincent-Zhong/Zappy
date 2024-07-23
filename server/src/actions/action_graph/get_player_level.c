/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** get_player_level
*/

#include <stdio.h>
#include <stdlib.h>
#include "server.h"

void action_get_player_level(server_t *serv, client_t *client, char *str)
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
    msg = format_message("plv %d %d\n", player->id, player->level);
    if (!msg)
        return;
    send_message(&serv->net, client->clid.fd, msg);
    free(msg);
}
