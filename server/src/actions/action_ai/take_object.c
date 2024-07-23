/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** take_object.c
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "event.h"

static const char *elements[] = {
        "food", "deraumere", "linemate", "mendiane",
        "phiras", "sibur", "thystame", NULL};

void init_tab(server_t *serv, client_t *client, int **tab,
int **inventory)
{
    tab[0] = &serv->map[client->player->y][client->player->x].elem.food;
    tab[1] = &serv->map[client->player->y][client->player->x].elem.deraumere;
    tab[2] = &serv->map[client->player->y][client->player->x].elem.linemate;
    tab[3] = &serv->map[client->player->y][client->player->x].elem.mendiane;
    tab[4] = &serv->map[client->player->y][client->player->x].elem.phiras;
    tab[5] = &serv->map[client->player->y][client->player->x].elem.sibur;
    tab[6] = &serv->map[client->player->y][client->player->x].elem.thystame;
    inventory[0] = &client->player->inventory.food;
    inventory[1] = &client->player->inventory.deraumere;
    inventory[2] = &client->player->inventory.linemate;
    inventory[3] = &client->player->inventory.mendiane;
    inventory[4] = &client->player->inventory.phiras;
    inventory[5] = &client->player->inventory.sibur;
    inventory[6] = &client->player->inventory.thystame;
}

void action_take_object(server_t *serv, client_t *client, char *str)
{
    int *tab[7];
    int *inventory[7];

    init_tab(serv, client, tab, inventory);
    for (int i = 0; elements[i] != NULL; ++i)
        if (strcmp(elements[i], str) == 0 && *tab[i] > 0) {
            dprintf(STDERR_FILENO, "%d take %s\n", client->player->id, str);
            send_message(&serv->net, client->clid.fd, "ok\n");
            --*tab[i];
            ++*inventory[i];
            event_player_inventory(serv, client->player);
            event_tile_changed(serv, client->player->x, client->player->y);
            return;
        }
    dprintf(STDERR_FILENO, "%d cannot take %s\n", client->player->id, str);
    send_message(&serv->net, client->clid.fd, "ko\n");
}
