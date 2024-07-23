/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** timer.c
*/

#include <sys/queue.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

void execute_action(server_t *serv, client_t *client)
{
    make_action(serv, client, client->list_command.tqh_first->command);
    TAILQ_REMOVE(&client->list_command, client->list_command.tqh_first,
    next_command);
    --client->nbr_command;
}

void wait_action(server_t *serv, client_t *client)
{
    if (!client->list_command.tqh_first)
        return;
    if (!client->start_chrono) {
        client->time_command =
        get_action_time(client->list_command.tqh_first->command)
        / serv->params.freq;
        client->start_chrono = true;
    }
    if (client->chrono_command < client->time_command)
        return;
    client->chrono_command = 0.0;
    client->start_chrono = false;
    execute_action(serv, client);
}

void function_to_timer(char *response, server_t *serv, client_t *client)
{
    if (client->nbr_command < 10) {
        add_command_to_list(client, response, false);
    }
}
