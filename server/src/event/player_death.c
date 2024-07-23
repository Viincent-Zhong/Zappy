/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** player_death
*/

#include "server.h"

void event_player_death(server_t *server, player_t *player)
{
    ping_all_graphicals(server, format_message("pdi %d\n", player->id));
}
