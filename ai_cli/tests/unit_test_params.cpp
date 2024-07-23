/*
** EPITECH PROJECT, 2022
** Project Zappy
** File description:
** unit_test_params.cpp
*/

#include <criterion/criterion.h>
#include "Params.hpp"

Test(Params, init_params)
{
    Params params;

    cr_assert_eq(params.getPort(), 4242);
    cr_assert_str_eq(params.getMachine().c_str(), "127.0.0.1");
    cr_assert_str_eq(params.getName().c_str(), "Trantor's");
}

Test(getParams, get_help)
{
    Params params;
    char *tab[2] = {"./zappy_ai", "-h"};
    const bool result = params.getParams(2, tab);

    cr_assert_eq(result, false);
}

Test(getParams, change_params)
{
    Params params;
    char *tab[7] = {"./zappy_ai", "-p", "1234", "-h", "1.0.0.721", "-n", "Epitech"};

    cr_assert_eq(params.getPort(), 4242);
    cr_assert_str_eq(params.getMachine().c_str(), "127.0.0.1");
    cr_assert_str_eq(params.getName().c_str(), "Trantor's");
    const bool result = params.getParams(7, tab);
    cr_assert_eq(params.getPort(), 1234);
    cr_assert_str_eq(params.getMachine().c_str(), "1.0.0.721");
    cr_assert_str_eq(params.getName().c_str(), "Epitech");

    cr_assert_eq(result, true);
}
