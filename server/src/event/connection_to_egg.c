/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** connection_to_egg
*/

#include "server.h"

void event_connection_to_egg(server_t *server, egg_t *egg)
{
    ping_all_graphicals(server, format_message("ebo %d\n", egg->id));
}
