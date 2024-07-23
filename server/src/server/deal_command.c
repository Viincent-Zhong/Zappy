/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** deal_command
*/

#include <sys/queue.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

void free_clients_commands(client_t *client)
{
    for (list_command_t *tmp = TAILQ_FIRST(&client->list_command); tmp;
    tmp = TAILQ_FIRST(&client->list_command)) {
        TAILQ_REMOVE(&client->list_command, tmp, next_command);
        free(tmp->command);
        free(tmp);
    }
}

void add_command_to_list(client_t *client, const char *response, bool head)
{
    list_command_t *command = malloc(sizeof(list_command_t));

    command->command = malloc(sizeof(char) * (strlen(response) + 1));
    strcpy(command->command, response);
    ++client->nbr_command;
    if (head)
        TAILQ_INSERT_HEAD(&client->list_command, command, next_command);
    else
        TAILQ_INSERT_TAIL(&client->list_command, command, next_command);
}