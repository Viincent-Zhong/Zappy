/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** modify_time_unit
*/

#include <stdio.h>
#include <stdlib.h>
#include "server.h"

void action_modify_time_unit(server_t *serv, client_t *client, char *str)
{
    char **av = parse_string(str, " ");
    int ac = 0;
    int time_unit = 0;
    char *msg;

    if (av == NULL)
        return;
    for (ac = 0; av[ac]; ++ac);
    if (ac != 1)
        return;
    time_unit = atoi(av[0]);
    serv->params.freq = time_unit;
    msg = format_message("sst %d\n", time_unit);
    if (!msg)
        return;
    send_message(&serv->net, client->clid.fd, msg);
    free(msg);
}
