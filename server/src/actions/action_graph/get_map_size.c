/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** get_map_size
*/

#include <stdlib.h>
#include "server.h"

void action_get_map_size(server_t *serv, client_t *client, char *str)
{
    char *msg = format_message("msz %u %u\n",
    serv->params.width, serv->params.height);

    if (!msg)
        return;
    send_message(&serv->net, client->clid.fd, msg);
    free(msg);
}
