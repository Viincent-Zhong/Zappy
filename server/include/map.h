/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** map
*/

#ifndef MAP_H_
    #define MAP_H_

    #include <sys/queue.h>
    #include <stdbool.h>
    #include "params.h"

enum direction {NORTH = 1, SOUTH = 3, EAST = 2, WEST = 4};

typedef struct element_s {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} element_t;

typedef struct player_t {
    element_t inventory;
    char *team_name;
    int x;
    int y;
    enum direction direction;
    int level;
    int incant;
    unsigned long long id;
    TAILQ_ENTRY(player_t) next_player;
} player_t;

typedef struct egg_t {
    int id;
    int parent_id;
    char *team_name;
    int x;
    int y;
    float hatch_time;
    TAILQ_ENTRY(egg_t) next_egg;
} egg_t;

typedef struct cell_s {
    element_t elem;
    int nbr_player;
    int nbr_egg;
    int end;
} cell_t;

cell_t **init_map(params_t *params, element_t *distribution);
void refill_map(cell_t **map, element_t distribute);
void free_cell_players(cell_t *cell);
void free_map(cell_t **map);
void print_map(cell_t **map);
void add_ressource_to_cell(cell_t *cell, element_t *bag);

#endif /* !MAP_H_ */
