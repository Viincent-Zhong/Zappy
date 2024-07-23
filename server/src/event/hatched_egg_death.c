/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** hatched_egg_death
*/

#include "server.h"

void event_hatched_egg_death(server_t *server, egg_t *egg)
{
    ping_all_graphicals(server, format_message("edi %d\n", egg->id));
}
