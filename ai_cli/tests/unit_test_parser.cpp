/*
** EPITECH PROJECT, 2022
** Project Zappy
** File description:
** unit_test_parser.cpp
*/

#include <criterion/criterion.h>
#include "Parser.hpp"

Test(getInventory, get_data_inventory)
{
    std::string str = "[food 10, linemate 9, deraumere 8, sibur 7, mendiane 6, phiras 5, thystame 4]";

    Waiter::Inventory inventory = Parser::getInventory(str);

    cr_assert_eq(inventory.food, 10);
    cr_assert_eq(inventory.linemate, 9);
    cr_assert_eq(inventory.deraumere, 8);
    cr_assert_eq(inventory.sibur, 7);
    cr_assert_eq(inventory.mendiane, 6);
    cr_assert_eq(inventory.phiras, 5);
    cr_assert_eq(inventory.thystame, 4);
}

Test(getTiles, get_data_tiles_spaces)
{
    std::string str = "[ player , , , thystame , , food , , , , , thystame , , , , , ,]";

    std::vector<Waiter::Tile> tiles = Parser::getTiles(str);

    cr_assert_eq(tiles.size(), 17);
    cr_assert_eq(tiles.at(0).player, 1);
    cr_assert_eq(tiles.at(1).player, 0);
}

Test(getTiles, get_data_tiles_no_spaces)
{
    // std::string str = "[player,,,thystame,,food,,,,,thystame,,,,,,]";

    // std::vector<Waiter::Tile> tiles = Parser::getTiles(str);
}

Test(extractFirstDelim, get_data_beguin)
{
    std::string str = "Dog Vincent\n";

    std::string result = Parser::extractFirstDelim(str, " ");

    cr_assert_str_eq(result.c_str(), "Dog");
}

Test(extractFirstDelim, get_data_beguin_no_delim)
{
    std::string str = "DogVincent";
    std::string result = Parser::extractFirstDelim(str, " ");

    cr_assert_str_eq(result.c_str(), "DogVincent");
}

Test(parsePrompt, get_data_from_prompt)
{
    std::string str = "Vincent je te ratio\n";
    std::vector<std::string> result = Parser::parsePrompt(str, " ");

    cr_assert_eq(result.size(), 4);
    cr_assert_str_eq(result.at(0).c_str(), "Vincent");
    cr_assert_str_eq(result.at(1).c_str(), "je");
    cr_assert_str_eq(result.at(2).c_str(), "te");
    cr_assert_str_eq(result.at(3).c_str(), "ratio");
}

Test(parsePrompt, get_data_from_prompt_no_delim)
{
    std::string str = "Vincent je te ratio\n";
    std::vector<std::string> result = Parser::parsePrompt(str, "z");

    cr_assert_eq(result.size(), 1);
    cr_assert_str_eq(result.at(0).c_str(), "Vincent je te ratio");
}

Test(parseCommand, get_data_from_command_one)
{
    std::string str = "Command ratio";
    std::pair<std::string, std::vector<std::string>> command = Parser::parseCommand(str, " ");

    cr_assert_str_eq(command.first.c_str(), "Command");
    cr_assert_eq(command.second.size(), 1);
    cr_assert_str_eq(command.second.at(0).c_str(), "ratio");
}

Test(parseCommand, get_data_from_command_two)
{
    std::string str = "Command ratio Vincent";
    std::pair<std::string, std::vector<std::string>> command = Parser::parseCommand(str, " ");

    cr_assert_str_eq(command.first.c_str(), "Command");
    cr_assert_eq(command.second.size(), 2);
    cr_assert_str_eq(command.second.at(0).c_str(), "ratio");
    cr_assert_str_eq(command.second.at(1).c_str(), "Vincent");
}
