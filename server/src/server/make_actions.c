/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** make_actions.c
*/

#include <stdlib.h>
#include <string.h>
#include "actions.h"
#include "server.h"
#include "utils.h"
#include "event.h"

static const actions_t action[] = {
    {"Forward", action_forward, 7},
    {"Right", action_right, 7},
    {"Left", action_left, 7},
    {"Look", action_look, 7},
    {"Inventory", action_inventory, 1},
    {"Broadcast", action_broadcast_text, 7},
    {"Connect_nbr", action_connect_nbr, 0},
    {"Fork", action_fork, 42},
    {"Eject", action_eject, 7},
    {"Take", action_take_object, 7},
    {"Set", action_set_object, 7},
    {"Incantation", can_make_incantation, 0},
    {"inc", action_incantation, 300},
    {"msz", action_get_map_size, 0},
    {"bct", action_get_content_tile, 0},
    {"mct", action_get_content_map, 0},
    {"tna", action_get_name_teams, 0},
    {"ppo", action_get_player_position, 0},
    {"plv", action_get_player_level, 0},
    {"pin", action_get_player_inventory, 0},
    {"sgt", action_get_time_unit, 0},
    {"sst", action_modify_time_unit, 0},
    {NULL, NULL, 0}};

unsigned int get_action_time(const char *str)
{
    int length = 0;

    for (int i = 0; action[i].str != NULL; ++i) {
        if (strlen(str) > strlen(action[i].str))
            length = strlen(action[i].str);
        else
            length = strlen(str);
        if (strncmp(action[i].str, str, length) == 0)
            return action[i].time;
    }
    return 0;
}

static bool generate_client_player(server_t *server, team_t *tmp,
client_t *client, char *str)
{
    char *res = NULL;
    team_t *team;

    client->player = create_player(server, str);
    if (client->player == NULL)
        return false;
    server->nbr_players++;
    ++tmp->nbr_client;
    if (!(team = search_teams(server, client->player->team_name)))
        return false;
    res = format_message("%lld\n%d %d\n", team->nbr_clientMax -
    team->nbr_client, server->params.width, server->params.height);
    send_message(&server->net, client->clid.fd, res);
    free(res);
    client->init = false;
    free_egg(server, client, str);
    return true;
}

static bool is_graphical_client(server_t *serv, client_t *client, char *str)
{
    socket_list_t *graph = NULL;

    if (strcmp(str, GRAPHICAL_ID) == 0) {
        client->graphical = true;
        graph = malloc(sizeof(socket_list_t));
        if (graph == NULL) {
            send_message(&serv->net, client->clid.fd, "ko\n");
            return false;
        }
        graph->addr = client->clid.addr;
        graph->addrlen = client->clid.addrlen;
        graph->fd = client->clid.fd;
        client->init = false;
        TAILQ_INSERT_HEAD(&serv->graphs, graph, next_socket);
        graph_first_connection(serv, client);
        return true;
    }
    return false;
}

bool connect_to_team(server_t *serv, client_t *client, char *str)
{
    if (is_graphical_client(serv, client, str))
        return true;
    for (team_t *tmp = serv->params.team.tqh_first; tmp != NULL;
    tmp = tmp->next_team.tqe_next) {
        if (strcmp(str, tmp->name) == 0 && tmp->nbr_client <
        serv->params.clients_nb && generate_client_player(serv, tmp,
        client, str)) {
            event_player_connection(serv, client->player);
            return true;
        }
    }
    send_message(&serv->net, client->clid.fd, "ko\n");
    return true;
}

bool make_action(server_t *serv, client_t *client, char *str)
{
    char **parse_cmd = capture_command(str);
    char *command = parse_cmd[0];
    char *params = array_to_string(parse_cmd + 1);

    for (int i = 0; action[i].str != NULL; ++i)
        if (strcmp(action[i].str, parse_cmd[0]) == 0) {
            action[i].fct(serv, client, params);
            free_array(parse_cmd);
            return true;
        }
    free_array(parse_cmd);
    send_message(&serv->net, client->clid.fd, "ko\n");
    return true;
}
