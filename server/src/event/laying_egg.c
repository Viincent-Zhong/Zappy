/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** laying_egg
*/

#include "server.h"
#include "event.h"

void event_laying_egg(server_t *server, player_t *player)
{
    ping_all_graphicals(server, format_message("pfk %d\n", player->id));
}
