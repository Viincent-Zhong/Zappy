/*
** EPITECH PROJECT, 2022
** project zappy
** File description:
** unit_test_server.c
*/

#include <criterion/criterion.h>
#include "server.h"
#include "actions.h"

static void ut_create_map(server_t *server)
{
    element_t empty = {0};
    TAILQ_INIT(&server->graphs);
    TAILQ_INIT(&server->clients);
    TAILQ_INIT(&server->params.team);
    server->map = init_map(&server->params, &empty);
}

Test(action_forward, move_player_up)
{
    server_t serv;
    client_t cli;
    char *str = "Forward";

    cli.player = malloc(sizeof(player_t));
    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    cli.player->x = 1;
    cli.player->y = 1;
    cli.player->direction = NORTH;
    cli.player->team_name = NULL;
    action_forward(&serv, &cli, str);
    cr_assert_eq(cli.player->x, 1);
    cr_assert_eq(cli.player->y, 0);
    cr_assert_eq(serv.map[1][1].nbr_player, -1);
    cr_assert_eq(serv.map[0][1].nbr_player, 1);
}

Test(action_forward, move_player_down)
{
    server_t serv;
    client_t cli;
    char *str = "Forward";

    cli.player = malloc(sizeof(player_t));
    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    cli.player->x = 1;
    cli.player->y = 1;
    cli.player->team_name = NULL;
    cli.player->direction = SOUTH;
    action_forward(&serv, &cli, str);
    cr_assert_eq(cli.player->x, 1);
    cr_assert_eq(cli.player->y, 2);
}

Test(action_forward, move_player_right)
{
    server_t serv;
    client_t cli;
    char *str = "Forward";

    cli.player = malloc(sizeof(player_t));
    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    cli.player->x = 1;
    cli.player->y = 1;
    cli.player->team_name = NULL;
    cli.player->direction = WEST;
    action_forward(&serv, &cli, str);
    cr_assert_eq(cli.player->x, 0);
    cr_assert_eq(cli.player->y, 1);
}

Test(action_forward, move_player_left)
{
    server_t serv;
    client_t cli;
    char *str = "Forward";

    cli.player = malloc(sizeof(player_t));
    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    cli.player->x = 1;
    cli.player->y = 1;
    cli.player->team_name = NULL;
    cli.player->direction = EAST;
    action_forward(&serv, &cli, str);
    cr_assert_eq(cli.player->x, 2);
    cr_assert_eq(cli.player->y, 1);
}

Test(action_forward, move_player_up_to_hight)
{
    server_t serv;
    client_t cli;
    char *str = "Forward";

    cli.player = malloc(sizeof(player_t));
    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    cli.player->x = 0;
    cli.player->y = 1;
    cli.player->team_name = NULL;
    cli.player->direction = NORTH;
    action_forward(&serv, &cli, str);
    cr_assert_eq(cli.player->x, 0);
    cr_assert_eq(cli.player->y, 0);
}

Test(action_forward, move_player_down_to_low)
{
    server_t serv;
    client_t cli;
    char *str = "Forward";

    cli.player = malloc(sizeof(player_t));
    serv.params.width = 20;
    serv.params.height = 20;
    ut_create_map(&serv);
    cli.player->x = 9;
    cli.player->y = 1;
    cli.player->direction = SOUTH;
    cli.player->team_name = NULL;
    action_forward(&serv, &cli, str);
    cr_assert_eq(cli.player->x, 9);
    cr_assert_eq(cli.player->y, 2);
}

Test(action_forward, move_player_left_to_much)
{
    server_t serv;
    client_t cli;
    char *str = "Forward";

    cli.player = malloc(sizeof(player_t));
    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    cli.player->x = 9;
    cli.player->y = 0;
    cli.player->direction = WEST;
    cli.player->team_name = NULL;
    action_forward(&serv, &cli, str);
    cr_assert_eq(cli.player->x, 8);
    cr_assert_eq(cli.player->y, 0);
}

Test(action_forward, move_player_right_to_much)
{
    server_t serv;
    client_t cli;
    char *str = "Forward";

    cli.player = malloc(sizeof(player_t));
    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    cli.player->x = 9;
    cli.player->y = 9;
    cli.player->team_name = NULL;
    cli.player->direction = EAST;
    action_forward(&serv, &cli, str);
    cr_assert_eq(cli.player->x, 0);
    cr_assert_eq(cli.player->y, 9);
}

Test(action_right, turn_player_right)
{
    server_t serv;
    client_t cli;
    char *str = "Forward";

    cli.player = malloc(sizeof(player_t));
    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    cli.player->x = 9;
    cli.player->y = 9;
    cli.player->direction = EAST;
    action_right(&serv, &cli, str);
    cr_assert_eq(cli.player->direction, SOUTH);
    cr_assert_eq(cli.player->x, 9);
    cr_assert_eq(cli.player->y, 9);
    action_right(&serv, &cli, str);
    cr_assert_eq(cli.player->direction, WEST);
    action_right(&serv, &cli, str);
    cr_assert_eq(cli.player->direction, NORTH);
    action_right(&serv, &cli, str);
    cr_assert_eq(cli.player->direction, EAST);
}

Test(action_right, turn_player_left)
{
    server_t serv;
    client_t cli;
    char *str = "Forward";

    cli.player = malloc(sizeof(player_t));
    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    cli.player->x = 9;
    cli.player->y = 9;
    cli.player->direction = EAST;
    action_left(&serv, &cli, str);
    cr_assert_eq(cli.player->direction, NORTH);
    cr_assert_eq(cli.player->x, 9);
    cr_assert_eq(cli.player->y, 9);
    action_left(&serv, &cli, str);
    cr_assert_eq(cli.player->direction, WEST);
    action_left(&serv, &cli, str);
    cr_assert_eq(cli.player->direction, SOUTH);
    action_left(&serv, &cli, str);
    cr_assert_eq(cli.player->direction, EAST);
}

Test(get_sound_direction, player_direction_zero)
{
    client_t cliOne;
    client_t cliTwo;
    unsigned int direction;

    cliOne.player = malloc(sizeof(player_t));
    cliOne.player->x = 9;
    cliOne.player->y = 9;
    cliOne.player->direction = NORTH;
    cliTwo.player = malloc(sizeof(player_t));
    cliTwo.player->x = 9;
    cliTwo.player->y = 9;
    cliTwo.player->direction = SOUTH;
    direction = get_sound_direction(&cliOne, &cliTwo, 10, 10);
    cr_assert_eq(direction, 0);
}

Test(get_sound_direction, player_direction_one)
{
    client_t cliOne;
    client_t cliTwo;
    unsigned int direction;

    cliOne.player = malloc(sizeof(player_t));
    cliOne.player->x = 9;
    cliOne.player->y = 9;
    cliOne.player->direction = NORTH;
    cliTwo.player = malloc(sizeof(player_t));
    cliTwo.player->x = 8;
    cliTwo.player->y = 9;
    cliTwo.player->direction = SOUTH;
    direction = get_sound_direction(&cliOne, &cliTwo, 10, 10);
    cr_assert_eq(direction, 1);
}

Test(get_sound_direction, player_direction_five)
{
    client_t cliOne;
    client_t cliTwo;
    unsigned int direction;

    cliOne.player = malloc(sizeof(player_t));
    cliOne.player->x = 9;
    cliOne.player->y = 9;
    cliOne.player->direction = NORTH;
    cliTwo.player = malloc(sizeof(player_t));
    cliTwo.player->x = 1;
    cliTwo.player->y = 9;
    cliTwo.player->direction = SOUTH;
    direction = get_sound_direction(&cliOne, &cliTwo, 10, 10);
    cr_assert_eq(direction, 5);
}

Test(get_sound_direction, player_direction_three)
{
    client_t cliOne;
    client_t cliTwo;
    unsigned int direction;

    cliOne.player = malloc(sizeof(player_t));
    cliOne.player->x = 9;
    cliOne.player->y = 9;
    cliOne.player->direction = NORTH;
    cliTwo.player = malloc(sizeof(player_t));
    cliTwo.player->x = 9;
    cliTwo.player->y = 8;
    cliTwo.player->direction = SOUTH;
    direction = get_sound_direction(&cliOne, &cliTwo, 10, 10);
    cr_assert_eq(direction, 3);
}

Test(get_sound_direction, player_direction_seven)
{
    client_t cliOne;
    client_t cliTwo;
    unsigned int direction;

    cliOne.player = malloc(sizeof(player_t));
    cliOne.player->x = 9;
    cliOne.player->y = 8;
    cliOne.player->direction = NORTH;
    cliTwo.player = malloc(sizeof(player_t));
    cliTwo.player->x = 9;
    cliTwo.player->y = 9;
    cliTwo.player->direction = SOUTH;
    direction = get_sound_direction(&cliOne, &cliTwo, 10, 10);
    cr_assert_eq(direction, 7);
}

Test(get_sound_direction, player_direction_four)
{
    client_t cliOne;
    client_t cliTwo;
    unsigned int direction;

    cliOne.player = malloc(sizeof(player_t));
    cliOne.player->x = 1;
    cliOne.player->y = 8;
    cliOne.player->direction = NORTH;
    cliTwo.player = malloc(sizeof(player_t));
    cliTwo.player->x = 2;
    cliTwo.player->y = 7;
    cliTwo.player->direction = SOUTH;
    direction = get_sound_direction(&cliOne, &cliTwo, 10, 10);
    cr_assert_eq(direction, 4);
}

Test(get_sound_direction, player_direction_two)
{
    client_t cliOne;
    client_t cliTwo;
    unsigned int direction;

    cliOne.player = malloc(sizeof(player_t));
    cliOne.player->x = 5;
    cliOne.player->y = 5;
    cliOne.player->direction = NORTH;
    cliTwo.player = malloc(sizeof(player_t));
    cliTwo.player->x = 2;
    cliTwo.player->y = 2;
    cliTwo.player->direction = SOUTH;
    direction = get_sound_direction(&cliOne, &cliTwo, 10, 10);
    cr_assert_eq(direction, 2);
}

Test(getSoundDirection, player_direction_eight)
{
    client_t cliOne;
    client_t cliTwo;
    unsigned int direction;

    cliOne.player = malloc(sizeof(player_t));
    cliOne.player->x = 5;
    cliOne.player->y = 5;
    cliOne.player->direction = NORTH;
    cliTwo.player = malloc(sizeof(player_t));
    cliTwo.player->x = 2;
    cliTwo.player->y = 7;
    cliTwo.player->direction = SOUTH;
    direction = get_sound_direction(&cliOne, &cliTwo, 10, 10);
    cr_assert_eq(direction, 8);
}

Test(getSoundDirection, player_direction_six)
{
    client_t cliOne;
    client_t cliTwo;
    unsigned int direction;

    cliOne.player = malloc(sizeof(player_t));
    cliOne.player->x = 5;
    cliOne.player->y = 5;
    cliOne.player->direction = NORTH;
    cliTwo.player = malloc(sizeof(player_t));
    cliTwo.player->x = 8;
    cliTwo.player->y = 7;
    cliTwo.player->direction = SOUTH;
    direction = get_sound_direction(&cliOne, &cliTwo, 10, 10);
    cr_assert_eq(direction, 6);
}

Test(get_sound_direction, player_direction_one_ahahaha)
{
    client_t cliOne;
    client_t cliTwo;
    unsigned int direction;

    cliOne.player = malloc(sizeof(player_t));
    cliOne.player->x = 9;
    cliOne.player->y = 9;
    cliOne.player->direction = NORTH;
    cliTwo.player = malloc(sizeof(player_t));
    cliTwo.player->x = 8;
    cliTwo.player->y = 9;
    cliTwo.player->direction = NORTH;
    direction = get_sound_direction(&cliOne, &cliTwo, 10, 10);
    cr_assert_eq(direction, 5);
}

Test(get_sound_direction, player_direction_one_bhbhbhbh)
{
    client_t cliOne;
    client_t cliTwo;
    unsigned int direction;

    cliOne.player = malloc(sizeof(player_t));
    cliOne.player->x = 9;
    cliOne.player->y = 9;
    cliOne.player->direction = NORTH;
    cliTwo.player = malloc(sizeof(player_t));
    cliTwo.player->x = 8;
    cliTwo.player->y = 9;
    cliTwo.player->direction = EAST;
    direction = get_sound_direction(&cliOne, &cliTwo, 10, 10);
    cr_assert_eq(direction, 7);
}

Test(get_sound_direction, player_direction_one_ihihihih)
{
    client_t cliOne;
    client_t cliTwo;
    unsigned int direction;

    cliOne.player = malloc(sizeof(player_t));
    cliOne.player->x = 9;
    cliOne.player->y = 9;
    cliOne.player->direction = NORTH;
    cliTwo.player = malloc(sizeof(player_t));
    cliTwo.player->x = 8;
    cliTwo.player->y = 9;
    cliTwo.player->direction = WEST;
    direction = get_sound_direction(&cliOne, &cliTwo, 10, 10);
    cr_assert_eq(direction, 3);
}

Test(action_broadcast_text, broadcast_text_no_client)
{
    server_t serv;
    client_t client;
    char *str = "Epitech";

    TAILQ_INIT(&serv.clients);
    action_broadcast_text(&serv, &client, str);
}

Test(action_connect_nbr, get_nbr_client_connect)
{
    server_t serv;
    client_t client;

    player_t player = {0};
    team_t team = {0};
    player.team_name = "Epitech";
    team.name = "Epitech";

    TAILQ_INIT(&serv.clients);
    TAILQ_INIT(&serv.params.team);
    team.nbr_client = 1;
    team.nbr_clientMax = 3;
    TAILQ_INSERT_HEAD(&serv.params.team, &team, next_team);
    client.player = &player;
    action_connect_nbr(&serv, &client, "");
}

Test(action_fork, fork_player)
{
    server_t serv;
    client_t client;
    char *str = "Epitech";
    unsigned int size_one = 0;
    unsigned int size_two = 0;

    TAILQ_INIT(&serv.clients);
    TAILQ_INIT(&serv.eggs);
    TAILQ_INIT(&serv.graphs);
    action_fork(&serv, &client, str);
}

static void add_player(server_t *server, int x, int y, int direction, int id)
{
    client_t *client = malloc(sizeof(client_t));
    player_t *player = malloc(sizeof(player_t));

    player->x = x;
    player->y = y;
    player->id = id;
    player->direction = direction;
    player->level = 1;
    player->incant = 0;
    client->player = player;
    client->clid.fd = 0;
    TAILQ_INSERT_HEAD(&server->clients, client, next_client);
}

Test(eject_nothing, eject_player)
{
    server_t serv;
    client_t *cli;
    char *str = "Eject";

    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    add_player(&serv, 9, 0, WEST, 0);
    serv.map[0][8].nbr_player = 1;
    cli = serv.clients.tqh_first;
    action_eject(&serv, cli, str);
    cr_assert_eq(cli->player->x, 9);
    cr_assert_eq(cli->player->y, 0);
}

Test(eject_1_player1, eject_player)
{
    server_t serv;
    client_t *cli;
    client_t *second_cli;
    char *str = "Eject";

    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    add_player(&serv, 9, 0, WEST, 0);
    cli = serv.clients.tqh_first;

    add_player(&serv, 9, 0, NORTH, 1);
    second_cli = serv.clients.tqh_first;

    serv.map[0][9].nbr_player = 2;
    action_eject(&serv, cli, str);
    cr_assert_eq(second_cli->player->x, 8);
    cr_assert_eq(second_cli->player->y, 0);
}

Test(eject_1_player2, eject_player)
{
    server_t serv;
    client_t *cli;
    client_t *second_cli;
    char *str = "Eject";

    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    add_player(&serv, 9, 0, NORTH, 0);
    cli = serv.clients.tqh_first;

    add_player(&serv, 9, 0, NORTH, 1);
    second_cli = serv.clients.tqh_first;

    serv.map[0][9].nbr_player = 2;
    action_eject(&serv, cli, str);
    cr_assert_eq(second_cli->player->x, 9);
    cr_assert_eq(second_cli->player->y, 9);
    cr_assert_eq(serv.map[0][9].nbr_player, 1);
    cr_assert_eq(serv.map[9][9].nbr_player, 1);
}

Test(eject_1_player3, eject_player)
{
    server_t serv;
    client_t *cli;
    client_t *second_cli;
    char *str = "Eject";

    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    add_player(&serv, 9, 0, SOUTH, 0);
    cli = serv.clients.tqh_first;

    add_player(&serv, 9, 0, SOUTH, 1);
    second_cli = serv.clients.tqh_first;

    serv.map[0][9].nbr_player = 2;
    action_eject(&serv, cli, str);
    cr_assert_eq(second_cli->player->x, 9);
    cr_assert_eq(second_cli->player->y, 1);
    cr_assert_eq(serv.map[0][9].nbr_player, 1);
    cr_assert_eq(serv.map[1][9].nbr_player, 1);
}

Test(eject_1_player4, eject_player)
{
    server_t serv;
    client_t *cli;
    client_t *second_cli;
    char *str = "Eject";

    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    add_player(&serv, 9, 0, EAST, 0);
    cli = serv.clients.tqh_first;

    add_player(&serv, 9, 0, EAST, 1);
    second_cli = serv.clients.tqh_first;

    serv.map[0][9].nbr_player = 2;
    action_eject(&serv, cli, str);
    cr_assert_eq(second_cli->player->x, 0);
    cr_assert_eq(second_cli->player->y, 0);
    cr_assert_eq(serv.map[0][9].nbr_player, 1);
    cr_assert_eq(serv.map[0][0].nbr_player, 1);
}

Test(eject_1_player5, eject_player)
{
    server_t serv;
    client_t *cli;
    client_t *second_cli;
    char *str = "Eject";

    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    add_player(&serv, 0, 0, NORTH, 0);
    cli = serv.clients.tqh_first;

    add_player(&serv, 0, 0, NORTH, 1);
    second_cli = serv.clients.tqh_first;

    serv.map[0][0].nbr_player = 2;
    action_eject(&serv, cli, str);
    cr_assert_eq(second_cli->player->x, 0);
    cr_assert_eq(second_cli->player->y, 9);
    cr_assert_eq(serv.map[9][0].nbr_player, 1);
    cr_assert_eq(serv.map[0][0].nbr_player, 1);
}

Test(eject_1_player6, eject_player)
{
    server_t serv;
    client_t *cli;
    client_t *second_cli;
    char *str = "Eject";

    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    add_player(&serv, 0, 0, WEST, 0);
    cli = serv.clients.tqh_first;

    add_player(&serv, 0, 0, WEST, 1);
    second_cli = serv.clients.tqh_first;

    serv.map[0][0].nbr_player = 2;
    action_eject(&serv, cli, str);
    cr_assert_eq(second_cli->player->x, 9);
    cr_assert_eq(second_cli->player->y, 0);
    cr_assert_eq(serv.map[0][9].nbr_player, 1);
    cr_assert_eq(serv.map[0][0].nbr_player, 1);
}

Test(eject_1_player7, eject_player)
{
    server_t serv;
    client_t *cli;
    client_t *second_cli;
    char *str = "Eject";

    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    add_player(&serv, 9, 0, EAST, 0);
    cli = serv.clients.tqh_first;

    add_player(&serv, 9, 0, EAST, 1);
    add_player(&serv, 9, 0, EAST, 2);
    add_player(&serv, 9, 0, EAST, 3);
    add_player(&serv, 9, 0, EAST, 4);
    second_cli = serv.clients.tqh_first;

    serv.map[0][9].nbr_player = 5;
    action_eject(&serv, cli, str);
    cr_assert_eq(second_cli->player->x, 0);
    cr_assert_eq(second_cli->player->y, 0);
    cr_assert_eq(serv.map[0][9].nbr_player, 1);
    cr_assert_eq(serv.map[0][0].nbr_player, 4);
}

Test(eject_1_player8, eject_player)
{
    server_t serv;
    client_t *cli;
    client_t *second_cli;
    char *str = "Eject";

    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    add_player(&serv, 0, 0, WEST, 0);
    cli = serv.clients.tqh_first;

    add_player(&serv, 0, 0, WEST, 1);
    add_player(&serv, 0, 0, WEST, 1);
    add_player(&serv, 0, 0, WEST, 1);
    add_player(&serv, 0, 0, WEST, 1);
    second_cli = serv.clients.tqh_first;

    serv.map[0][0].nbr_player = 5;
    action_eject(&serv, cli, str);
    cr_assert_eq(second_cli->player->x, 9);
    cr_assert_eq(second_cli->player->y, 0);
    cr_assert_eq(serv.map[0][9].nbr_player, 4);
    cr_assert_eq(serv.map[0][0].nbr_player, 1);
}

Test(action_broadcast_text, broadcast_text_clients)
{
    server_t serv;
    client_t *cli;
    client_t *second_cli;
    char *str = "Eject";

    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    add_player(&serv, 0, 0, WEST, 0);
    cli = serv.clients.tqh_first;

    add_player(&serv, 0, 0, WEST, 1);
    add_player(&serv, 0, 0, WEST, 1);
    add_player(&serv, 0, 0, WEST, 1);
    add_player(&serv, 0, 0, WEST, 1);
    second_cli = serv.clients.tqh_first;
    action_broadcast_text(&serv, cli, "Epitech > Epita");
}

Test(action_connect_nbr, team_not_exist)
{
    server_t serv;
    client_t client;

    player_t player = {0};
    team_t team = {0};
    player.team_name = "Epita";
    team.name = "Epitech";

    TAILQ_INIT(&serv.clients);
    TAILQ_INIT(&serv.params.team);
    team.nbr_client = 1;
    team.nbr_clientMax = 3;
    TAILQ_INSERT_HEAD(&serv.params.team, &team, next_team);
    client.player = &player;
    action_connect_nbr(&serv, &client, "");
}

Test(action_forward, move_player_outside_one)
{
    server_t serv;
    client_t cli;
    char *str = "Forward";

    cli.player = malloc(sizeof(player_t));
    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    cli.player->x = 0;
    cli.player->y = 0;
    cli.player->direction = NORTH;
    cli.player->team_name = NULL;
    action_forward(&serv, &cli, str);
    cr_assert_eq(cli.player->x, 0);
    cr_assert_eq(cli.player->y, 9);
    cr_assert_eq(serv.map[0][0].nbr_player, -1);
    cr_assert_eq(serv.map[9][0].nbr_player, 1);
}

Test(action_forward, move_player_outside_two)
{
    server_t serv;
    client_t cli;
    char *str = "Forward";

    cli.player = malloc(sizeof(player_t));
    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    cli.player->x = 9;
    cli.player->y = 9;
    cli.player->direction = SOUTH;
    cli.player->team_name = NULL;
    action_forward(&serv, &cli, str);
    cr_assert_eq(cli.player->x, 9);
    cr_assert_eq(cli.player->y, 0);
    cr_assert_eq(serv.map[9][9].nbr_player, -1);
    cr_assert_eq(serv.map[0][9].nbr_player, 1);
}

Test(action_forward, move_player_outside_three)
{
    server_t serv;
    client_t cli;
    char *str = "Forward";

    cli.player = malloc(sizeof(player_t));
    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    cli.player->x = 0;
    cli.player->y = 0;
    cli.player->team_name = NULL;
    cli.player->direction = WEST;
    action_forward(&serv, &cli, str);
    cr_assert_eq(cli.player->x, 9);
    cr_assert_eq(cli.player->y, 0);
    cr_assert_eq(serv.map[0][0].nbr_player, -1);
    cr_assert_eq(serv.map[0][9].nbr_player, 1);
}

Test(action_incantation, make_incantation_check_players)
{
    const unsigned int tab[] = {1, 1, 1, 0, 0, 0, 0, 0};
    server_t serv;
    client_t *cli;
    client_t *second_cli;
    client_t *pad;
    char *str = "Eject";
    bool result;

    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    add_player(&serv, 0, 0, WEST, 0);
    cli = serv.clients.tqh_first;

    add_player(&serv, 0, 0, WEST, 1);
    second_cli = serv.clients.tqh_first;

    add_player(&serv, 0, 0, WEST, 2);
    pad = serv.clients.tqh_first;

    pad->player->level = 4;

    serv.map[0][0].nbr_player = 2;
    cli->player->incant = 1;
    result = check_nb_players(&serv, cli->player, tab);
    cr_assert_eq(result, true);
    result = check_nb_players(&serv, pad->player, tab);
    cr_assert_eq(result, false);
}

Test(action_incantation, make_incantation_check_stones)
{
    const unsigned int tab[] = {1, 1, 1, 0, 0, 0, 0, 0};
    const unsigned int tab_two[] = {7, 6, 2, 2, 2, 2, 2, 1};
    server_t serv;
    client_t *cli;
    client_t *second_cli;
    client_t *pad;
    char *str = "Eject";
    bool result;

    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    add_player(&serv, 0, 0, WEST, 0);
    cli = serv.clients.tqh_first;

    add_player(&serv, 0, 0, WEST, 1);
    second_cli = serv.clients.tqh_first;

    add_player(&serv, 0, 0, WEST, 2);
    pad = serv.clients.tqh_first;

    pad->player->level = 4;

    cli->player->team_name = NULL;
    serv.map[0][0].nbr_player = 2;
    serv.map[0][0].elem.linemate = 10;
    cli->player->incant = 1;
    result = check_stones(&serv, cli, serv.map[0][0], tab);
    cr_assert_eq(result, true);
    result = check_stones(&serv, pad, serv.map[0][0], tab_two);
    cr_assert_eq(result, false);
}

Test(action_incantation, make_incantation)
{
    server_t serv;
    client_t *cli;
    client_t *second_cli;
    bool result;

    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    add_player(&serv, 0, 0, WEST, 0);
    cli = serv.clients.tqh_first;
    add_player(&serv, 0, 0, WEST, 1);
    second_cli = serv.clients.tqh_first;
    serv.map[0][0].nbr_player = 2;
    cli->player->incant = 1;
    action_incantation(&serv, cli, "Incantation");
}

static void add_to_tile(element_t *elem, int value)
{
    elem->food = value;
    elem->linemate = value;
    elem->deraumere = value;
    elem->sibur = value;
    elem->mendiane = value;
    elem->phiras = value;
    elem->thystame = value;
}

Test(incantation_level_7, make_incantation)
{
    server_t serv;
    client_t *cli;
    bool result;
    element_t elem = {10};

    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    add_player(&serv, 0, 0, WEST, 0);
    add_player(&serv, 0, 0, WEST, 1);
    add_player(&serv, 0, 0, WEST, 2);
    add_player(&serv, 0, 0, WEST, 3);
    add_player(&serv, 0, 0, WEST, 4);
    add_player(&serv, 0, 0, WEST, 5);
    serv.map[0][0].nbr_player = 6;
    add_to_tile(&serv.map[0][0].elem, 10);

    for (client_t *tmp = serv.clients.tqh_first; tmp != NULL;
    tmp = tmp->next_client.tqe_next) {
        tmp->player->incant = 1;
        tmp->player->level = 7;
    }
    action_incantation(&serv, serv.clients.tqh_first, "Incantation");
    cr_expect_eq(serv.clients.tqh_first->player->level, 8);
}

Test(incantation_level_6, make_incantation)
{
    server_t serv;
    client_t *cli;
    bool result;
    element_t elem = {10};

    serv.params.width = 10;
    serv.params.height = 10;
    ut_create_map(&serv);
    add_player(&serv, 0, 0, WEST, 0);
    add_player(&serv, 0, 0, WEST, 1);
    add_player(&serv, 0, 0, WEST, 2);
    add_player(&serv, 0, 0, WEST, 3);
    add_player(&serv, 0, 0, WEST, 4);
    add_player(&serv, 0, 0, WEST, 5);
    serv.map[0][0].nbr_player = 6;
    add_to_tile(&serv.map[0][0].elem, 10);

    for (client_t *tmp = serv.clients.tqh_first; tmp != NULL;
    tmp = tmp->next_client.tqe_next) {
        tmp->player->incant = 1;
        tmp->player->level = 6;
    }
    action_incantation(&serv, serv.clients.tqh_first, "Incantation");
    cr_expect_eq(serv.clients.tqh_first->player->level, 7);
}
