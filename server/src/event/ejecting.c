/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** ejecting
*/

#include "server.h"

void event_ejecting(server_t *server, player_t *player)
{
    ping_all_graphicals(server, format_message("pex %d\n", player->id));
}
