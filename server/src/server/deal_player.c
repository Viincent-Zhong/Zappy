/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** deal_player
*/

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "event.h"

player_t *search_player(server_t *server, char *id)
{
    unsigned long long uid = strtoull(id, NULL, 10);

    if (errno == EINVAL || errno == ERANGE)
        return NULL;
    for (client_t *client = TAILQ_FIRST(&server->clients), *tmp;
    client != NULL; client = tmp) {
        tmp = TAILQ_NEXT(client, next_client);
        if (client->player && client->player->id == uid)
            return client->player;
    }
    return NULL;
}

player_t *create_player(server_t *server, char *team_name)
{
    player_t *player = malloc(sizeof(player_t));
    element_t empty_inventory = {0};

    if (player == NULL)
        return NULL;
    player->id = server->nbr_players;
    player->team_name = malloc(sizeof(char) * (strlen(team_name) + 1));
    strcpy(player->team_name, team_name);
    player->direction = (rand() % 4) + 1;
    player->incant = 0;
    player->inventory = empty_inventory;
    player->inventory.food = 10;
    player->level = 1;
    player->x = rand() % server->params.width;
    player->y = rand() % server->params.height;
    server->map[player->y][player->x].nbr_player++;
    return player;
}

bool client_survive(client_t *client, unsigned int freq)
{
    if (client->player->inventory.food > 0) {
        --client->player->inventory.food;
        client->chrono_death += 126 / freq;
        return true;
    }
    return false;
}

void handle_map(server_t *serv)
{
    --serv->time_refill;
    if (serv->time_refill == 0) {
        serv->time_refill = 20;
        refill_map(serv->map, serv->distribution);
        event_map_changed(serv);
    }
}

bool player_timer(server_t *server, client_t *client)
{
    if (client->player == NULL)
        return false;
    --client->chrono_death;
    if (client->chrono_death <= 0.0 && !client_survive(client,
    server->params.freq)) {
        send_message(&server->net, client->clid.fd, "dead\n");
        quit_server(server, client);
        return false;
    }
    if (client->start_chrono)
        ++client->chrono_command;
    return true;
}
