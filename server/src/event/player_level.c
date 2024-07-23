/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** player_level
*/

#include "event.h"

void event_player_level(server_t *server, player_t *player)
{
    ping_all_graphicals(server,
    format_message("plv %d %d\n", player->id, player->level));
}
