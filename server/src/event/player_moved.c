/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** player_moved
*/

#include <stdlib.h>
#include "event.h"

void event_player_moved(server_t *server, player_t *player)
{
    ping_all_graphicals(server, format_message("ppm %d %d %d %d\n",
    player->id, player->x, player->y, player->direction));
}
