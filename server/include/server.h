/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** server.h
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include <arpa/inet.h>
    #include <stdbool.h>
    #include <sys/time.h>
    #include "map.h"

    #define SIZE_MESSAGE    1024
    #define GRAPHICAL_ID    "GRAPHIC"

typedef struct net_s {
    fd_set rdfs;
    fd_set wdfs;
    fd_set edfs;
    int max_fd;
} net_t;

typedef struct socket_s {
    struct sockaddr_in addr;
    int addrlen;
    int fd;
} socket_t;

typedef struct socket_list_t {
    struct sockaddr_in addr;
    int addrlen;
    int fd;
    TAILQ_ENTRY(socket_list_t) next_socket;
} socket_list_t;

typedef struct list_command_t {
    char *command;
    TAILQ_ENTRY(list_command_t) next_command;
} list_command_t;

typedef struct client_t {
    bool init;
    bool graphical;
    bool start_chrono;
    int time_command;
    unsigned int nbr_command;
    double chrono_command;
    double chrono_death;
    socket_t clid;
    player_t *player;
    TAILQ_HEAD(command_list, list_command_t) list_command;
    TAILQ_ENTRY(client_t) next_client;
} client_t;

typedef struct server_s {
    struct timeval timeout;
    struct timeval tmp;
    net_t net;
    socket_t serv;
    cell_t **map;
    element_t distribution;
    params_t params;
    double time_refill;
    int incantation_id;
    bool victory;
    TAILQ_HEAD(egg_list, egg_t) eggs;
    TAILQ_HEAD(client_list, client_t) clients;
    TAILQ_HEAD(graph_list, socket_list_t) graphs;
    unsigned long long nbr_players;
    unsigned long long nbr_eggs;
} server_t;

// ! socket_utils.c
bool init_socket(socket_t *sock, int port);

// ! server.c
bool server(int ac, char **av);

// ! handle_client.c
void quit_server(server_t *serv, client_t *client);

// * nouveau client
void client_connection(server_t *server, socket_t *client, socket_t serv);
// * client deja connecté
void detect_clients(server_t *serv);
void add_client(server_t *server, socket_t sock);

// ! message.c
bool send_message(net_t *serv, const unsigned int fd, const char *msg);
char *read_message(const unsigned int fd);

// ! make_actions.c
bool connect_to_team(server_t *serv, client_t *client, char *str);
bool make_action(server_t *serv, client_t *client, char *str);
unsigned int get_action_time(const char *str);

char *format_message(char *format, ...);

char **capture_command(char *str);
char *array_to_string(char **array);
void free_array(char **array);
char **parse_string(char *str, const char *delim);

// ! deal_team.c
unsigned int get_sound_direction(const client_t *orig,
const client_t *reception, const unsigned int width,
const unsigned int height);

team_t *search_teams(server_t *server, char *name);

// ! deal_player.c
player_t *search_player(server_t *server, char *id);
player_t *create_player(server_t *server, char *team_name);
bool client_survive(client_t *client, unsigned int freq);
void handle_map(server_t *serv);
bool player_timer(server_t *server, client_t *client);

// ! deal_graphical.c
void ping_all_graphicals(server_t *server, char *message);
socket_list_t *get_graphicals_by_fd(server_t *server, int fd);
void move_case_view(int *beguin_x, int *beguin_y,
const enum direction dir, const unsigned int *dim);
void update_beguin_view(int *beguin_x, int *beguin_y,
const enum direction dir, const unsigned int *dim);
char *get_case(const cell_t *cell);
void graph_first_connection(server_t *server, client_t *client);

void init_tab(server_t *serv, client_t *client, int **tab,
int **inventory);

// ! timer.c
void add_command_to_list(client_t *client, const char *response, bool head);
void execute_action(server_t *serv, client_t *client);
void wait_action(server_t *serv, client_t *client);
void function_to_timer(char *response, server_t *serv, client_t *client);

// ! incantation.c
bool incantation(server_t *serv, client_t *client, cell_t *tile,
const unsigned int *tab);
void can_make_incantation(server_t *serv, client_t *client, char *response);
bool check_nb_players(server_t *serv, player_t *player,
const unsigned int *tab);
bool check_stones(server_t *serv, client_t *client, const cell_t tile,
const unsigned int *tab);

// ! deal_egg.c
void create_egg(server_t *server, player_t *player);
void handle_eggs(server_t *serv);
void free_egg(server_t *server, client_t *client, const char *str);

//! left.c
char *get_direction_name(enum direction dir);

void free_clients_commands(client_t *client);
bool init_incantation(server_t *server, client_t *client, const cell_t tile,
const unsigned int *tab);
// ! victory.c
void check_victory(server_t *serv);
void update_players_incant(server_t *serv, int incant, int status);

#endif /* !SERVER_H_ */
