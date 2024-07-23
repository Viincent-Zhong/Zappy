/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** unit_test_look
*/

#include <iostream>
#include <criterion/criterion.h>
#include "Parser.hpp"

Test(look, looking)
{
    std::vector<Waiter::Tile> tiles;
    // f, l, d, s, m, p, t, player
    std::vector<Waiter::Tile> compare = {
        {1, 0, 0, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 1, 0, 0},
        {2, 1, 0, 0, 0, 0, 0, 0},
    };

    // tiles = Parser::getTiles("[ player food phiras,, food linemate phiras, food food linemate ]");
    // for (auto it = tiles.begin(), cmp = compare.begin(); it != tiles.end()
    // && cmp != compare.end(); ++it, ++cmp) {
        // cr_expect_eq(it, cmp);
    // }
}