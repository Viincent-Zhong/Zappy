/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** get_player_info
*/

#include <stdlib.h>
#include "actions.h"

void action_get_player_info(server_t *server, client_t *client,
player_t *player)
{
    char *message = format_message("ppi %d %d %d %d %d %d %d %d %d %d %d %s\n",
    player->id, player->x, player->y, player->level, player->inventory.food,
    player->inventory.linemate, player->inventory.deraumere,
    player->inventory.sibur, player->inventory.mendiane,
    player->inventory.phiras, player->inventory.thystame, player->team_name);

    if (!message)
        return;
    send_message(&server->net, client->clid.fd, message);
    free(message);
}
