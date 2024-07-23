/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** dropping_resources
*/

#include "server.h"

void event_dropping_resources(server_t *server, player_t *player,
int resources)
{
    ping_all_graphicals(server,
    format_message("pdr %d %d\n", player->id, resources));
}