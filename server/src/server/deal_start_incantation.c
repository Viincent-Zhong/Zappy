/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** deal_start_incantation
*/

#include <stdlib.h>
#include "server.h"

static void update_status_by_id_list(server_t *serv, const int ids[8],
const int nb_players)
{
    int i = 0;

    for (client_t *tmp = serv->clients.tqh_first; tmp != NULL
    && i < nb_players; tmp = tmp->next_client.tqe_next)
        if (tmp->player->id == ids[i]) {
            send_message(&serv->net, tmp->clid.fd, "Elevation underway\n");
            tmp->player->incant = serv->incantation_id;
            ++i;
        }
}

static bool check_available_players(server_t *serv, player_t *player,
const unsigned int *tab)
{
    unsigned int nb_players = 1;
    int ids[8] = {-1};

    for (client_t *tmp = serv->clients.tqh_first; tmp != NULL &&
    nb_players < tab[1]; tmp = tmp->next_client.tqe_next)
        if (tmp->player->id != player->id && tmp->player->x == player->x
        && tmp->player->y == player->y && tmp->player->level == tab[0] &&
        tmp->player->incant == 0) {
            ids[nb_players] = tmp->player->id;
            ++nb_players;
        }
    if (nb_players < tab[1])
        return false;
    update_status_by_id_list(serv, ids, nb_players - 1);
    return true;
}

bool init_incantation(server_t *server, client_t *client, const cell_t tile,
const unsigned int *tab)
{
    if (client->player->level >= 8)
        return false;
    if (!check_stones(server, client, tile, tab))
        return false;
    if (!check_available_players(server, client->player, tab))
        return false;
    client->player->incant = server->incantation_id;
    ++server->incantation_id;
    send_message(&server->net, client->clid.fd, "Elevation underway\n");
    return true;
}
