/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** egg_hatching
*/

#include "server.h"

void event_egg_hatching(server_t *server, egg_t *egg)
{
    ping_all_graphicals(server, format_message("eht %d\n", egg->id));
}
