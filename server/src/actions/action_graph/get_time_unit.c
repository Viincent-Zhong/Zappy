/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** get_time_unit
*/

#include <stdlib.h>
#include "server.h"

void action_get_time_unit(server_t *serv, client_t *client, char *str)
{
    char *msg = format_message("sgt %d\n", serv->params.freq);

    if (!msg)
        return;
    send_message(&serv->net, client->clid.fd, msg);
    free(msg);
}
