/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <vector>
#include <string>
#include "Waiter.hpp"

namespace Parser {
    std::pair<std::string, std::vector<std::string>> parseCommand(std::string command, std::string const &delim);
    std::vector<std::string> parsePrompt(std::string command, std::string const &delim);
    std::vector<Waiter::Tile> getTiles(std::string const &str);
    Waiter::Inventory getInventory(std::string const &str);
    /**
     *  Cut the given string to the first found delimiter and return it
     *  If the delimiter isn't found the string doesn't change
     */
    std::string extractFirstDelim(std::string &command, std::string const &delim);
};

#endif /* !PARSER_HPP_ */
