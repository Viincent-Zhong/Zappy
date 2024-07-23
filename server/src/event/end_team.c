/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** end_team
*/

#include "server.h"

void event_end_team(server_t *server, char *team_name)
{
    ping_all_graphicals(server, format_message("seg %s\n", team_name));
}
