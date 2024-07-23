/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** eject.c
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "event.h"

static void get_case_victim(int *pos_x, int *pos_y, const enum direction dir)
{
    switch (dir)
    {
        case NORTH:
            *pos_y = -1;
            break;
        case SOUTH:
            *pos_y = 1;
            break;
        case WEST:
            *pos_x = -1;
            break;
        case EAST:
            *pos_x = 1;
            break;
    }
}

static void verif_case(int *pos_x, int *pos_y, const int height,
const int width)
{
    if (*pos_x >= width)
        *pos_x = 0;
    if (*pos_x < 0)
        *pos_x = width - 1;
    if (*pos_y >= height)
        *pos_y = 0;
    if (*pos_y < 0)
        *pos_y = height - 1;
}

static void ping_player_ejected_direction(server_t *serv, client_t *orig,
client_t *victim)
{
    int direction = 0;
    int c_direc = victim->player->direction;
    char *message;

    direction = get_sound_direction(orig, victim, serv->params.width,
    serv->params.height);
    message = format_message("eject: %d\n", direction);
    serv->map[victim->player->y][victim->player->x].nbr_player++;
    send_message(&serv->net, victim->clid.fd, message);
    free(message);
}

static void move_players(server_t *serv, client_t *client,
const unsigned int move_x, const unsigned int move_y)
{
    for (client_t *tmp = serv->clients.tqh_first; tmp != NULL;
    tmp = tmp->next_client.tqe_next) {
        if (tmp->player && tmp->player->id != client->player->id &&
        tmp->player->x == client->player->x &&
        tmp->player->y == client->player->y) {
            serv->map[tmp->player->y][tmp->player->x].nbr_player--;
            tmp->player->x += move_x;
            tmp->player->y += move_y;
            dprintf(STDERR_FILENO, "Player %d is eject by %d",
            tmp->player->id, client->player->id);
            dprintf(STDERR_FILENO, " in case %d:%d\n",
            tmp->player->x, tmp->player->y);
            verif_case(&tmp->player->x, &tmp->player->y, serv->params.height,
            serv->params.width);
            ping_player_ejected_direction(serv, client, tmp);
            event_player_moved(serv, tmp->player);
        }
    }
}

void action_eject(server_t *serv, client_t *client, char *str)
{
    int move_x = 0;
    int move_y = 0;
    int pos_x = client->player->x;
    int pos_y = client->player->y;

    if (serv->map[pos_y][pos_x].nbr_player <= 1) {
        send_message(&serv->net, client->clid.fd, "ko\n");
        return;
    }
    get_case_victim(&move_x, &move_y, client->player->direction);
    event_tile_changed(serv, client->player->x, client->player->y);
    pos_x += move_x;
    pos_y += move_y;
    verif_case(&pos_x, &pos_y, serv->params.height, serv->params.width);
    move_players(serv, client, move_x, move_y);
    send_message(&serv->net, client->clid.fd, "ok\n");
    client->player->incant = 0;
    event_tile_changed(serv, pos_x, pos_y);
}
