/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** broadcasting
*/

#include "server.h"

void event_broadcasting(server_t *server, player_t *player)
{
    ping_all_graphicals(server, format_message("pbc %d\n", player->id));
}
