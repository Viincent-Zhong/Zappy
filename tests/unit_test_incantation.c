/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** unit_test_incantation
*/

#include <stdlib.h>
#include <criterion/criterion.h>
#include "server.h"

static const unsigned int tab_level_up[7][8] = {
    {1, 1, 1, 0, 0, 0, 0, 0},
    {2, 2, 1, 1, 1, 0, 0, 0},
    {3, 2, 2, 0, 1, 0, 2, 0},
    {4, 4, 1, 1, 2, 0, 1, 0},
    {5, 4, 1, 2, 1, 3, 0, 0},
    {6, 6, 1, 2, 3, 0, 1, 0},
    {7, 6, 2, 2, 2, 2, 2, 1}};

static void simulate_player(server_t *server, int x, int y, int level)
{
    client_t *client = malloc(sizeof(client_t));

    client->player = malloc(sizeof(player_t));
    client->player->x = x;
    client->player->y = y;
    client->player->level = level;
    TAILQ_INSERT_HEAD(&server->clients, client, next_client);
}

static cell_t simulate_tile(int ressources)
{
    cell_t tile = {0};

    tile.elem.linemate = ressources;
    tile.elem.deraumere = ressources;
    tile.elem.sibur = ressources;
    tile.elem.mendiane = ressources;
    tile.elem.phiras = ressources;
    tile.elem.thystame = ressources;
    return tile;
}

static server_t *simulate_server()
{
    server_t *server = malloc(sizeof(server_t));

    TAILQ_INIT(&server->clients);
    return server;
}

Test(g1, good_incantation)
{
    server_t *serv = simulate_server();
    cell_t tile = simulate_tile(10);

    for (int i = 0; i < 8; ++i)
        simulate_player(serv, 2, 2, 3);
    cr_expect_eq(incantation(serv, serv->clients.tqh_first, tile,
    tab_level_up[2]), true);
}

Test(g2, good_incantation)
{
    server_t *serv = simulate_server();
    cell_t tile = simulate_tile(10);

    for (int i = 0; i < 8; ++i)
        simulate_player(serv, 2, 2, 4);
    cr_expect_eq(incantation(serv, serv->clients.tqh_first, tile,
    tab_level_up[3]), true);
}

Test(g3, good_incantation)
{
    server_t *serv = simulate_server();
    cell_t tile = simulate_tile(2);
    int pl = 7;

    for (int i = 0; i < 8; ++i)
        simulate_player(serv, 2, 2, pl);
    cr_expect_eq(incantation(serv, serv->clients.tqh_first, tile,
    tab_level_up[pl - 1]), true);
}

Test(g4, good_incantation)
{
    server_t *serv = simulate_server();
    cell_t tile = simulate_tile(1);
    int pl = 1;
    int nbplayers = 1;

    for (int i = 0; i < nbplayers; ++i)
        simulate_player(serv, 2, 2, pl);
    cr_expect_eq(incantation(serv, serv->clients.tqh_first, tile,
    tab_level_up[pl - 1]), true);
}

Test(g5, good_incantation)
{
    server_t *serv = simulate_server();
    cell_t tile = simulate_tile(1);
    int nbplayers = 2;
    int pl = 2;

    for (int i = 0; i < nbplayers; ++i)
        simulate_player(serv, 2, 2, pl);
    cr_expect_eq(incantation(serv, serv->clients.tqh_first, tile,
    tab_level_up[pl - 1]), true);
}

Test(g6, good_incantation)
{
    server_t *serv = simulate_server();
    cell_t tile = simulate_tile(2);
    int nbplayers = 2;
    int pl = 3;

    for (int i = 0; i < nbplayers; ++i)
        simulate_player(serv, 2, 2, pl);
    cr_expect_eq(incantation(serv, serv->clients.tqh_first, tile,
    tab_level_up[pl - 1]), true);
}

Test(g7, good_incantation)
{
    server_t *serv = simulate_server();
    cell_t tile = simulate_tile(2);
    int nbplayers = 4;
    int pl = 4;

    for (int i = 0; i < nbplayers; ++i)
        simulate_player(serv, 2, 2, pl);
    cr_expect_eq(incantation(serv, serv->clients.tqh_first, tile,
    tab_level_up[pl - 1]), true);
}

Test(g8, good_incantation)
{
    server_t *serv = simulate_server();
    cell_t tile = simulate_tile(3);
    int nbplayers = 4;
    int pl = 5;

    for (int i = 0; i < nbplayers; ++i)
        simulate_player(serv, 2, 2, pl);
    cr_expect_eq(incantation(serv, serv->clients.tqh_first, tile,
    tab_level_up[pl - 1]), true);
}

Test(g9, good_incantation)
{
    server_t *serv = simulate_server();
    cell_t tile = simulate_tile(3);
    int nbplayers = 6;
    int pl = 6;

    for (int i = 0; i < nbplayers; ++i)
        simulate_player(serv, 2, 2, pl);
    cr_expect_eq(incantation(serv, serv->clients.tqh_first, tile,
    tab_level_up[pl - 1]), true);
}

Test(g10, good_incantation)
{
    server_t *serv = simulate_server();
    cell_t tile = simulate_tile(2);
    int nbplayers = 6;
    int pl = 7;

    for (int i = 0; i < nbplayers; ++i)
        simulate_player(serv, 2, 2, pl);
    cr_expect_eq(incantation(serv, serv->clients.tqh_first, tile,
    tab_level_up[pl - 1]), true);
}

Test(bad_level1, bad_incantation)
{
    server_t *serv = simulate_server();
    cell_t tile = simulate_tile(2);
    int nbplayers = 20;
    int pl = 6;

    for (int i = 0; i < nbplayers; ++i)
        simulate_player(serv, 2, 2, pl);
    cr_expect_eq(incantation(serv, serv->clients.tqh_first, tile,
    tab_level_up[1]), false);
}

Test(bad_level2, bad_incantation)
{
    server_t *serv = simulate_server();
    cell_t tile = simulate_tile(100);
    int nbplayers = 1;
    int pl = 7;

    for (int i = 0; i < nbplayers; ++i)
        simulate_player(serv, 2, 2, pl);
    cr_expect_eq(incantation(serv, serv->clients.tqh_first, tile,
    tab_level_up[0]), false);
}

Test(bad_level3, bad_incantation)
{
    server_t *serv = simulate_server();
    cell_t tile = simulate_tile(100);
    int nbplayers = 6;
    int pl = 7;

    for (int i = 0; i < nbplayers - 1; ++i)
        simulate_player(serv, 2, 2, pl);
    simulate_player(serv, 2, 2, 1);
    cr_expect_eq(incantation(serv, serv->clients.tqh_first, tile,
    tab_level_up[pl - 1]), false);
}

Test(bad_ressources1, bad_incantation)
{
    server_t *serv = simulate_server();
    cell_t tile = simulate_tile(0);
    int nbplayers = 6;
    int pl = 7;

    for (int i = 0; i < nbplayers - 1; ++i)
        simulate_player(serv, 2, 2, pl);
    simulate_player(serv, 2, 2, 1);
    cr_expect_eq(incantation(serv, serv->clients.tqh_first, tile,
    tab_level_up[pl - 1]), false);
}

Test(bad_ressources2, bad_incantation)
{
    server_t *serv = simulate_server();
    cell_t tile = simulate_tile(1);
    int nbplayers = 6;
    int pl = 7;

    for (int i = 0; i < nbplayers - 1; ++i)
        simulate_player(serv, 2, 2, pl);
    simulate_player(serv, 2, 2, 1);
    cr_expect_eq(incantation(serv, serv->clients.tqh_first, tile,
    tab_level_up[pl - 1]), false);
}

Test(bad_ressources3, bad_incantation)
{
    server_t *serv = simulate_server();
    cell_t tile = simulate_tile(1000);
    int nbplayers = 6;
    int pl = 7;

    tile.elem.deraumere = 1;
    for (int i = 0; i < nbplayers - 1; ++i)
        simulate_player(serv, 2, 2, pl);
    simulate_player(serv, 2, 2, 1);
    cr_expect_eq(incantation(serv, serv->clients.tqh_first, tile,
    tab_level_up[pl - 1]), false);
}