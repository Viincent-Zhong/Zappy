/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** collecting_resources
*/

#include "server.h"

void event_collecting_resources(server_t *server, player_t *player,
int resources)
{
    ping_all_graphicals(server,
    format_message("pgt %d %d\n", player->id, resources));
}
