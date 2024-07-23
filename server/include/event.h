/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** event
*/

#ifndef EVENT_H_
#define EVENT_H_

#include "server.h"

/*
                                                SYMBOL MEANING

    X width or horizontal position                                          Y height or vertical position
    q0 resource 0 (food) quantity                                           q1 resource 1 (linemate) quantity
    q2 resource 2 (deraumere) quantity                                      q3 resource 3 (sibur) quantity
    q4 resource 4 (mendiane) quantity                                       q5 resource 5 (phiras) quantity
    q6 resource 6 (thystame) quantity                                       n player number
    O orientation: 1 (north), 2 (east), 3 (south), 4 (west)                 L player or incantation level
    e egg number                                                            T time unit
    N name of the team                                                      R incantation result
    M message                                                               i resource number
*/

/**
 * Send format : pnw "n" "X" "Y" "O" "L" "N"
 * 
 *  Where :
 *      - O orientation: 1 (north), 2 (east), 3 (south), 4 (west)
 *      - N : name of the team
 *      - L : player level
 */
void event_player_connection(server_t *server, player_t *player);
/**
 * @brief Send format : pex "n"
 */
void event_ejecting(server_t *server, player_t *player);
/**
 * @brief Send format : pbc "n"
 */
void event_broadcasting(server_t *server, player_t *player);
/**
 * Send format : pic "X" "Y" "L" ["n"]
 *  Where :
 *      - L : Incantation level
 *      - [n] : list of all players doing the incantation
 */
void event_start_incantation(server_t *server, int x, int y, int level);
/**
 * Send format : pie "X" "Y" "R"
 * 
 * Where :
 *  - R : 0 (Failed), 1 (Succeed)
 *  - X Y : Position of the tile
 */
void event_end_incantation(server_t *server, int x, int y, int result);
/**
 * Send format : pdr "n" "i"
 * 
 * Where :
 *  - i : Number of resource dropped
 */
void event_dropping_resources(server_t *server, player_t *player,
int resources);
/**
 * Send format : pgt "n" "i"
 * 
 * Where :
 *  - i : Number of resource dropped
 */
void event_collecting_resources(server_t *server, player_t *player,
int resources);
/**
 * Send format : pdi "n"
 */
void event_player_death(server_t *server, player_t *player);
/**
 * Send format : pfk "n"
 */
void event_laying_egg(server_t *server, player_t *player);
/**
 * Send format : enw "e" "n" "X" "Y"
 * 
 * Where :
 *  - e : egg number
 */
void event_layed_egg(server_t *server, egg_t *egg);
/**
 * Send format : eht "e"
 *
 * Where :
 *  - e : egg number
 */
void event_egg_hatching(server_t *server, egg_t *egg);
/**
 * Send format : ebo "e"
 * 
 * Where :
 *  - e : egg number
 */
void event_connection_to_egg(server_t *server, egg_t *egg);
/**
 * Send format : edi "e"
 * 
 * Where :
 *  - e : egg number
 */
void event_hatched_egg_death(server_t *server, egg_t *egg);
/**
 * Send format : seg "N"
 * 
 * Where :
 * - N : team name
 */
void event_end_team(server_t *server, char *team_name);
/**
 *  Send format : ppm "n" "X" "Y" "O"\n
 * 
 * O being the orientation: 1 (north), 2 (east), 3 (south), 4 (west)
 */
void event_player_moved(server_t *server, player_t *player);
/**
 *  Send format : pin "n" "X" "Y" "q0" "q1" "q2" "q3" "q4" "q5" "q6"\n
 * 
 * q order : food, linemate, deraumere, sibur, mendiane, phiras, thystame
 */
void event_player_inventory(server_t *server, player_t *player);
/**
 *  Send format : plv "n" "L"\n
 */
void event_player_level(server_t *server, player_t *player);
/**
 *  Send format : bct "X" "Y" "q0" "q1" "q2" "q3" "q4" "q5" "q6"\n
 * 
 *  q order : food, linemate, deraumere, sibur, mendiane, phiras, thystame
 */
void event_tile_changed(server_t *serv, int x, int y);
/**
 *  Send format : bct "X" "Y" "q0" "q1" "q2" "q3" "q4" "q5" "q6"\n (en boucle)
 * 
 *  q order : food, linemate, deraumere, sibur, mendiane, phiras, thystame
 */
void event_map_changed(server_t *serv);

#endif /* !EVENT_H_ */
