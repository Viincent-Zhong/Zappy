/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** player_connection
*/

#include "server.h"

void event_player_connection(server_t *server, player_t *player)
{
    ping_all_graphicals(server, format_message("pnw %d %d %d %d %d %s\n",
    player->id, player->x, player->y, player->direction,
    player->level, player->team_name));
}
