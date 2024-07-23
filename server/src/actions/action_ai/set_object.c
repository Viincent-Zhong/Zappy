/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** set_object.c
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "event.h"

static const char *elements[] = {
    "food", "deraumere", "linemate", "mendiane",
    "phiras", "sibur", "thystame", NULL};

void action_set_object(server_t *serv, client_t *client, char *str)
{
    int *tab[7];
    int *inventory[7];

    init_tab(serv, client, tab, inventory);
    for (int i = 0; elements[i] != NULL; ++i)
        if (strcmp(elements[i], str) == 0 && *inventory[i] > 0) {
            dprintf(STDERR_FILENO, "%d set %s\n", client->player->id, str);
            send_message(&serv->net, client->clid.fd, "ok\n");
            ++*tab[i];
            --*inventory[i];
            event_player_inventory(serv, client->player);
            event_tile_changed(serv, client->player->x, client->player->y);
            return;
        }
    dprintf(STDERR_FILENO, "%d cannot set %s\n", client->player->id, str);
    send_message(&serv->net, client->clid.fd, "ko\n");
}
