/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** deal_egg
*/

#include <stdlib.h>
#include <string.h>
#include "event.h"

void create_egg(server_t *server, player_t *player)
{
    egg_t *egg;

    if (!player)
        return;
    egg = malloc(sizeof(egg_t));
    egg->x = player->x;
    egg->y = player->y;
    egg->parent_id = player->id;
    egg->id = server->nbr_eggs;
    egg->team_name = format_message("%s", player->team_name);
    egg->hatch_time = 600 / server->params.freq;
    server->map[egg->y][egg->x].nbr_egg++;
    server->nbr_eggs++;
    TAILQ_INSERT_HEAD(&server->eggs, egg, next_egg);
}

static void hatch_egg(server_t *serv, egg_t *egg, socket_t *client)
{
    add_client(serv, *client);
    serv->clients.tqh_first->player = create_player(serv, egg->team_name);
    serv->clients.tqh_first->clid.fd = 0;
    if (serv->clients.tqh_first->player) {
        serv->clients.tqh_first->player->x = egg->x;
        serv->clients.tqh_first->player->y = egg->y;
    }
    free(egg);
    TAILQ_REMOVE(&serv->eggs, egg, next_egg);
}

void handle_eggs(server_t *serv)
{
    socket_t client;

    for (egg_t *egg = TAILQ_FIRST(&serv->eggs), *tmp; egg != NULL; egg = tmp) {
        tmp = TAILQ_NEXT(egg, next_egg);
        if (egg->hatch_time > 0)
            --egg->hatch_time;
        if (egg->hatch_time <= 0)
            hatch_egg(serv, egg, &client);
    }
}

void free_egg(server_t *server, client_t *client, const char *str)
{
    for (client_t *pad = server->clients.tqh_first; pad != NULL;
    pad = pad->next_client.tqe_next) {
        if (pad->clid.fd == 0 && strcmp(pad->player->team_name, str) == 0) {
            client->player->x = pad->player->x;
            client->player->y = pad->player->y;
            client->player->direction = pad->player->direction;
            TAILQ_REMOVE(&server->clients, pad, next_client);
            return;
        }
    }
}
