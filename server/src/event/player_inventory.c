/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** player_inventory
*/

#include "event.h"

void event_player_inventory(server_t *server, player_t *player)
{
    char *msg = format_message("pin %d %d %d %d %d %d %d %d %d %d\n",
    player->id, player->x, player->y, player->inventory.food,
    player->inventory.linemate, player->inventory.deraumere,
    player->inventory.sibur, player->inventory.mendiane,
    player->inventory.phiras, player->inventory.thystame);

    if (!msg)
        return;
    ping_all_graphicals(server, msg);
}
