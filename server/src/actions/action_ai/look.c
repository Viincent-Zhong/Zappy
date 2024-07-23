/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** look.c
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "utils.h"

static char *init_look(const server_t *serv, int *pos)
{
    char *cases = "[ ";

    cases = concat(cases, get_case(&serv->map[pos[1]][pos[0]]));
    cases = concat(cases, ", ");
    return cases;
}

void put_coma(char **cases, int j, unsigned int size_line)
{
    if (j != size_line - 1)
        *cases = concat(*cases, ", ");
    else
        *cases = concat(*cases, " ");
}

char *view_area(const server_t *serv, const client_t *client)
{
    const unsigned int dim[2] = {serv->params.width, serv->params.height};
    int pos[4] = {client->player->x, client->player->y, 0, 0};
    unsigned int size_line = 3;
    char *cases = init_look(serv, pos);

    for (int i = 0; i != client->player->level; ++i, size_line += 2) {
        update_beguin_view(&pos[0], &pos[1], client->player->direction, dim);
        pos[2] = pos[0];
        pos[3] = pos[1];
        for (int j = 0; j != size_line; ++j) {
            cases = concat(cases, get_case(&serv->map[pos[3]][pos[2]]));
            put_coma(&cases, j, size_line);
            move_case_view(&pos[2], &pos[3], client->player->direction, dim);
        }
    }
    cases = concat(cases, "]\n");
    return cases;
}

void action_look(server_t *serv, client_t *client, char *str)
{
    char *message = view_area(serv, client);

    dprintf(STDERR_FILENO, "%d looking at: %s\n", client->player->id, message);
    send_message(&serv->net, client->clid.fd, message);
    free(message);
}
