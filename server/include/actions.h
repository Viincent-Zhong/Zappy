/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** actions.h
*/

#ifndef ACTIONS_H_
    #define ACTIONS_H_

    #include "server.h"

typedef void (*action_fct_ptr)(server_t *serv, client_t *client, char *str);

typedef struct actions_s {
    char *str;
    action_fct_ptr fct;
    unsigned int time;
} actions_t;

/** Broadcast a message through the world
 * 
 *  Command : Broadcast "text"
 *  Response : ok
 *  Timelimit : 7/f
 */
void action_broadcast_text(server_t *serv, client_t *client, char *str);

/**
 *  Command : Connect_nbr
 *  Response : "Number of connected"
 *  Time limit : -
 */
void action_connect_nbr(server_t *serv, client_t *client, char *str);

/**
 *  Command : Eject
 *  Response : ok / ko
 *  Time limit : 7/f
 */
void action_eject(server_t *serv, client_t *client, char *str);

/**
 *  Command : Fork
 *  Response : ok
 *  Time limit : 42/f
 */
void action_fork(server_t *serv, client_t *client, char *str);

/**
 *  Command : Forward
 *  Response : ok
 *  Time limit : 7/f
 */
void action_forward(server_t *serv, client_t *client, char *str);

/**
 *  Command : Incantation
 *  Response : Elevation underway / "Current level" / ko
 *  Time limit : 7/f
 */
void action_incantation(server_t *serv, client_t *client, char *str);

/**
 *  Command : Inventory
 *  Response : [food "n", linemate "n", deraumere "n", sibur "n", mendiane "n", phiras "n", thystame "n"]
 *  Time limit : 1/f
 */
void action_inventory(server_t *serv, client_t *client, char *str);

/** Turn 90 left (change direction)
 * 
 *  Command : Left
 *  Response : ok
 *  Time limit : 7/f
 */
void action_left(server_t *serv, client_t *client, char *str);

/**
 *  Command : Look
 *  Response : [tile 1, tile 2, ...]
 *  Time limit : 7/f
 */
void action_look(server_t *serv, client_t *client, char *str);

/** Turn 90 right (change direction)
 * 
 *  Command : Right
 *  Response : ok
 *  Time limit : 7/f
 */
void action_right(server_t *serv, client_t *client, char *str);

/**
 *  Command : Set "object"
 *  Response : ok / ko
 *  Time limit : 7/f
 */
void action_set_object(server_t *serv, client_t *client, char *str);

/**
 *  Command : Take "object"
 *  Response : ok / ko
 *  Time limit : 7/f
 */
void action_take_object(server_t *serv, client_t *client, char *str);


/*
                                    SYMBOL MEANING
    X width or horizontal position                      Y height or vertical position
    q0 resource 0 (food) quantity                       q1 resource 1 (linemate) quantity
    q2 resource 2 (deraumere) quantity                  q3 resource 3 (sibur) quantity
    q4 resource 4 (mendiane) quantity                   q5 resource 5 (phiras) quantity
    q6 resource 6 (thystame) quantity                   n player number
    O orientation: 1(N), 2(E), 3(S), 4(W)               L player or incantation level
    e egg number                                        T time unit
    N name of the team                                  R incantation result
    M message                                           i resource number
*/

/**
 *  Command : msz
 *  Response : msz "X" "Y"
 */
void action_get_map_size(server_t *serv, client_t *client, char *str);
/**
 *  Command : bct "X" "Y"\n
 *  Response : bct "X" "Y" "q0" "q1" "q2" "q3" "q4" "q5" "q6"\n
 * 
 *  q order : food, linemate, deraumere, sibur, mendiane, phiras, thystame
 */
void action_get_content_tile(server_t *serv, client_t *client, char *str);
/**
 *  Command : mct\n
 *  Response : bct "X" "Y" "q0" "q1" "q2" "q3" "q4" "q5" "q6"\n (en boucle)
 * 
 * q order : food, linemate, deraumere, sibur, mendiane, phiras, thystame
 */
void action_get_content_map(server_t *serv, client_t *client, char *str);
/**
 *  Command : tna\n
 *  Response : tna "N"\n (en boucle)
 */
void action_get_name_teams(server_t *serv, client_t *client, char *str);
/**
 *  Command : ppo "n"\n
 *  Response : ppo "n" "X" "Y" "O"\n
 * 
 * O being the orientation: 1 (north), 2 (east), 3 (south), 4 (west)
 */
void action_get_player_position(server_t *serv, client_t *client, char *str);
/**
 *  Command : plv "n"\n
 *  Response : plv "n" "L"\n
 */
void action_get_player_level(server_t *serv, client_t *client, char *str);
/**
 *  Command : pin "n"\n
 *  Response : pin "n" "X" "Y" "q0" "q1" "q2" "q3" "q4" "q5" "q6"\n
 * 
 * q order : food, linemate, deraumere, sibur, mendiane, phiras, thystame
 */
void action_get_player_inventory(server_t *serv, client_t *client, char *str);

/**
 *  Command : sgt\n
 *  Response : sgt "T"\n
 */
void action_get_time_unit(server_t *serv, client_t *client, char *str);
/**
 *  Command : sst "T"\n
 *  Response : sst "T"\n
 */
void action_modify_time_unit(server_t *serv, client_t *client, char *str);
/**
 * Send format : ppi "n" "X" "Y" "O" "L" "q0" "q1" "q2" "q3" "q4" "q5" "q6" "N"
 * 
 * Where :
 *  - q order : food, linemate, deraumere, sibur, mendiane, phiras, thystame
 *  - O orientation: 1 (north), 2 (east), 3 (south), 4 (west)
 *  - L level
 *  - N team name
 */
void action_get_player_info(server_t *server, client_t *client,
player_t *player);

#endif /* !ACTIONS_H_ */
