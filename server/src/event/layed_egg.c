/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** layed_egg
*/

#include "server.h"

void event_layed_egg(server_t *server, egg_t *egg)
{
    if (!egg)
        return;
    ping_all_graphicals(server, format_message("enw %d %d %d %d\n",
    egg->id, egg->parent_id, egg->x, egg->y));
}
