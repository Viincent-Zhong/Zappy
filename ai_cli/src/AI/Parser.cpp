/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Parser
*/

#include <iostream>
#include "Parser.hpp"

static int extractDigit(std::string str)
{
    size_t i = 0;

    for (; i < str.length() && !isdigit(str[i]); i++);
    str = str.substr(i, str.length() - i);
    return std::atoi(str.c_str());
}

std::pair<std::string, std::vector<std::string>> Parser::parseCommand(std::string command, std::string const &delim)
{
    size_t pos = 0;
    std::string token;
    std::pair<std::string, std::vector<std::string>> parsed;
    bool first = true;

    while ((pos = command.find(delim)) != std::string::npos) {
        token = command.substr(0, pos);
        if (first) {
            parsed.first = token;
            first = false;
        } else
            parsed.second.push_back(token);
        std::cout << token << std::endl;
        command.erase(0, pos + delim.length());
    }
    parsed.second.push_back(command);
    return parsed;
}

std::vector<std::string> Parser::parsePrompt(std::string command, std::string const &delim)
{
    size_t pos = 0;
    std::string token;
    std::vector<std::string> arr;

    if (command.back() == '\n')
        command.erase(command.size() - 1);
    while ((pos = command.find(delim)) != std::string::npos) {
        token = command.substr(0, pos);
        arr.push_back(token);
        command.erase(0, pos + delim.length());
    }
    arr.push_back(command);
    return arr;
}

std::string Parser::extractFirstDelim(std::string &command, std::string const &delim)
{
    size_t pos = 0;
    std::string token;

    if (command.back() == '\n')
        command.erase(command.size() - 1);
    if ((pos = command.find(delim)) != std::string::npos) {
        token = command.substr(0, pos);
        command.erase(0, pos + delim.length());
        return token;
    }
    return command;
}

std::vector<Waiter::Tile> Parser::getTiles(std::string const &str)
{
    std::vector<std::string> tilesStr = Parser::parsePrompt(str, ",");
    std::vector<std::string> tileElems;
    std::vector<Waiter::Tile> tiles;
    Waiter::Tile tile = {0};
    std::vector<std::pair<std::string, int &>> refs = {
        {"food", tile.food},
        {"linemate", tile.linemate},
        {"deraumere", tile.deraumere},
        {"sibur", tile.sibur},
        {"mendiane", tile.mendiane},
        {"phiras", tile.phiras},
        {"thystame", tile.thystame},
        {"player", tile.player}
    };

    for (auto it : tilesStr) {
        tile = {0};
        tileElems = Parser::parsePrompt(it, " ");
        for (auto tmp : tileElems) {
            for (auto elem : refs)
                if (tmp.find(elem.first) != std::string::npos) {
                    elem.second++;
                    break;
                }
        }
        tiles.push_back(tile);
    }
    return tiles;
}

Waiter::Inventory Parser::getInventory(std::string const &str)
{
    std::vector<std::string> element = Parser::parsePrompt(str, ",");
    Waiter::Inventory inventory = {0};
    std::vector<std::pair<std::string, int &>> add = {
        {"food", inventory.food},
        {"linemate", inventory.linemate},
        {"deraumere", inventory.deraumere},
        {"sibur", inventory.sibur},
        {"mendiane", inventory.mendiane},
        {"phiras", inventory.phiras},
        {"thystame", inventory.thystame}
    };
    int value = 0;

    for (auto it : element) {
        value = extractDigit(it);
        for (auto elem : add) {
            if (it.find(elem.first) != std::string::npos) {
                elem.second += value;
                break;
            }
        }
    }
    return inventory;
}
