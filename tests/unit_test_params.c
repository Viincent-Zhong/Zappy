/*
** EPITECH PROJECT, 2022
** project zappy
** File description:
** unit_test_server.c
*/

#include <criterion/criterion.h>
#include "params.h"

Test(params, good_params)
{
    int ac = 1;
    char *av[] = {"-p", "4242", NULL};
    params_t params = {0};

    get_params(ac, av, &params);
    cr_assert_eq(params.port, 4242);
    cr_assert_eq(params.clients_nb, 3);
    cr_assert_eq(params.freq, 1);
    cr_assert_eq(params.width, 10);
    cr_assert_eq(params.height, 10);
}

Test(get_port, good_port)
{
    char *av[] = {"4242", NULL};
    params_t params = {0};
    const bool result = get_port(&params, av);

    cr_assert_eq(result, false);
}

Test(get_port, bad_port)
{
    char *av[] = {"ahahahahah", NULL};
    params_t params = {0};
    const bool result = get_port(&params, av);

    cr_assert_eq(result, false);
}

Test(is_number, good_number)
{
    const bool result = is_number("42");

    cr_assert_eq(result, true);
}

Test(is_number, bad_number)
{
    const bool result = is_number("ahahahah");

    cr_assert_eq(result, false);
}
