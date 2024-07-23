/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** incantation.c
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"

static const unsigned int tab_level_up[7][8] = {
    {1, 1, 1, 0, 0, 0, 0, 0},
    {2, 2, 1, 1, 1, 0, 0, 0},
    {3, 2, 2, 0, 1, 0, 2, 0},
    {4, 4, 1, 1, 2, 0, 1, 0},
    {5, 4, 1, 2, 1, 3, 0, 0},
    {6, 6, 1, 2, 3, 0, 1, 0},
    {7, 6, 2, 2, 2, 2, 2, 1}};

void update_players_incant(server_t *serv, int incant, int status)
{
    for (client_t *tmp = serv->clients.tqh_first; tmp != NULL;
    tmp = tmp->next_client.tqe_next)
        if (tmp->player->incant == incant)
            tmp->player->incant = status;
}

void ko_players_incant(server_t *serv, int incant)
{
    for (client_t *tmp = serv->clients.tqh_first; tmp != NULL;
    tmp = tmp->next_client.tqe_next)
        if (tmp->player->incant == incant) {
            send_message(&serv->net, tmp->clid.fd, "ko\n");
            tmp->player->incant = 0;
    }
}

bool check_stones(server_t *serv, client_t *client, const cell_t tile,
const unsigned int *tab)
{
    if (tile.elem.linemate < tab[2] ||
        tile.elem.deraumere < tab[3] ||
        tile.elem.sibur < tab[4] ||
        tile.elem.mendiane < tab[5] ||
        tile.elem.phiras < tab[6] ||
        tile.elem.thystame < tab[7]) {
        return false;
    }
    return true;
}

void action_incantation(server_t *serv, client_t *client, char *str)
{
    cell_t *tile;
    const unsigned int *tab;

    if (client->player->level > 0 && client->player->level < 8) {
        tile = &serv->map[client->player->y][client->player->x];
        tab = tab_level_up[client->player->level - 1];
        if (incantation(serv, client, tile, tab)) {
            event_tile_changed(serv, client->player->y, client->player->x);
            return;
        }
    }
    ko_players_incant(serv, client->player->incant);
}

void can_make_incantation(server_t *serv, client_t *client, char *response)
{
    char *command = format_message("inc\n");

    if (client->player->level > 0 && client->player->level < 8 &&
    client->player->incant == 0 && init_incantation(serv, client,
    serv->map[client->player->y][client->player->x],
    tab_level_up[client->player->level - 1])) {
        dprintf(STDERR_FILENO, "%llu incantation starting\n",
        client->player->id);
        add_command_to_list(client, command, false);
    } else {
        dprintf(STDERR_FILENO, "%llu cannot make incantation\n",
        client->player->id);
        send_message(&serv->net, client->clid.fd, "ko\n");
        client->player->incant = 0;
    }
}
