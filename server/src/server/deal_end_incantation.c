/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** deal_incantation
*/

#include <stdlib.h>
#include "event.h"

void update_incantation_victims(server_t *serv, player_t *player, int *ids,
int nb_players)
{
    char *msg = format_message("Current level: %d\n", player->level + 1);
    int i = 0;

    for (client_t *tmp = serv->clients.tqh_first; tmp != NULL
    && i < nb_players; tmp = tmp->next_client.tqe_next) {
        if (tmp->player->id == ids[i]) {
            ++tmp->player->level;
            tmp->player->incant = 0;
            send_message(&serv->net, tmp->clid.fd, msg);
            event_player_level(serv, tmp->player);
            ++i;
        }
    }
    check_victory(serv);
    free(msg);
}

static unsigned int check_incant_group(server_t *serv, player_t *player,
int ids[8], const unsigned *tab)
{
    unsigned int nb_players = 0;
    bool add = false;
    int id = player->incant;

    for (client_t *tmp = serv->clients.tqh_first; tmp != NULL &&
    nb_players < tab[1]; tmp = tmp->next_client.tqe_next) {
        if (tmp->player->incant == id && tmp->player->x == player->x
        && tmp->player->y == player->y && tmp->player->level == tab[0]) {
            ids[nb_players] = tmp->player->id;
            ++nb_players;
            add = true;
        }
        if (add) {
            tmp->player->incant = 0;
            add = false;
        }
    }
    return nb_players;
}

bool check_nb_players(server_t *serv, player_t *player,
const unsigned int *tab)
{
    unsigned int nb_players = 0;
    int id = player->incant;
    int ids[8] = {-1};

    if (player->level != tab[0])
        return false;
    nb_players = check_incant_group(serv, player, ids, tab);
    for (client_t *tmp = serv->clients.tqh_first; tmp != NULL &&
    nb_players < tab[1]; tmp = tmp->next_client.tqe_next)
        if (tmp->player->incant != id && tmp->player->x == player->x
        && tmp->player->y == player->y && tmp->player->level == tab[0]) {
            ids[nb_players] = tmp->player->id;
            ++nb_players;
        }
    if (nb_players < tab[1])
        return false;
    update_incantation_victims(serv, player, ids, nb_players);
    return true;
}

static void remove_ressources(cell_t *tile, const unsigned *tab)
{
    tile->elem.linemate -= tab[2];
    tile->elem.deraumere -= tab[3];
    tile->elem.sibur -= tab[4];
    tile->elem.mendiane -= tab[5];
    tile->elem.phiras -= tab[6];
    tile->elem.thystame -= tab[7];
}

bool incantation(server_t *serv, client_t *client, cell_t *tile,
const unsigned int *tab)
{
    if (client->player->level >= 8)
        return false;
    if (!check_stones(serv, client, *tile, tab))
        return false;
    if (!check_nb_players(serv, client->player, tab))
        return false;
    remove_ressources(tile, tab);
    return true;
}
