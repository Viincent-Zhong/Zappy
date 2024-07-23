/*
** EPITECH PROJECT, 2022
** project zappy
** File description:
** unit_test_server.c
*/

#include <criterion/criterion.h>
#include "server.h"

Test(server, server_no_parameters)
{
    const bool result = server(0, NULL);

    cr_assert_eq(result, false);
}

Test(server, server_bad_nbr_parameters_one)
{
    const bool result = server(2, NULL);

    cr_assert_eq(result, false);
}

Test(server, server_bad_nbr_parameters_two)
{
    char *av[] = {"-p", "4242", NULL};
    const bool result = server(2, av);

    cr_assert_eq(result, false);
}

Test(server, server_bad_port)
{
    char *av[] = {"./zappy_server", "-p", "agthfc", NULL};
    const bool result = server(4, av);

    cr_assert_eq(result, false);
}
