/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** boradcast_text.c
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"
#include "utils.h"

void action_broadcast_text(server_t *serv, client_t *client, char *str)
{
    char *message;
    unsigned int direction;

    for (client_t *tmp = serv->clients.tqh_first; tmp != NULL;
    tmp = tmp->next_client.tqe_next) {
        if (tmp->player != NULL && tmp->clid.fd != client->clid.fd) {
            direction = get_sound_direction(client,
            tmp, serv->params.width, serv->params.height);
            dprintf(STDERR_FILENO, "%d receive (%d), %s\n",
            tmp->player->id, direction, str);
            message = format_message("message %d, %s\n", direction, str);
            send_message(&serv->net, tmp->clid.fd, message);
            free(message);
        }
    }
    send_message(&serv->net, client->clid.fd, "ok\n");
}
