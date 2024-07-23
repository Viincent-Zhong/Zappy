/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-pierre-alexandre.delgado-arevalo
** File description:
** AiFunction.cpp
*/

#include <unistd.h>
#include "Waiter.hpp"

void Waiter::searchRock()
{
    if (_tiles[0].linemate > 0) {
        while (_tiles[0].linemate > 0)
        {
            addCommand({Communication::TAKE, "linemate"});
            _tiles[0].linemate -= 1;
        }
    }

    if (_tiles[0].deraumere > 0) {
        while (_tiles[0].deraumere > 0)
        {
            addCommand({Communication::TAKE, "deraumere"});
            _tiles[0].deraumere -= 1;
        }
    }

    if (_tiles[0].sibur > 0) {
        while (_tiles[0].sibur > 0)
        {
            addCommand({Communication::TAKE, "sibur"});
            _tiles[0].sibur -= 1;
        }
    }
}

void Waiter::searchFood()
{
    if (_tiles[0].food > 0) {
        while (_tiles[0].food > 0)
        {
            addCommand({Communication::TAKE, "food"});
            _tiles[0].food -= 1;
        }
    }

    else if (_tiles[2].food > 0) {
        addCommand({Communication::MOVE, ""});
        while (_tiles[2].food > 0)
        {
            addCommand({Communication::TAKE, "food"});
            _tiles[2].food -= 1;
        }
    }

    else if (_tiles[1].food > 0) {
        addCommand({Communication::MOVE, ""});
        addCommand({Communication::LEFT, ""});
        addCommand({Communication::MOVE, ""});
        while (_tiles[1].food > 0)
        {
            addCommand({Communication::TAKE, "food"});
            _tiles[1].food -= 1;
        }
    }

    else if (_tiles[3].food > 0) {
        addCommand({Communication::MOVE, ""});
        addCommand({Communication::RIGHT, ""});
        addCommand({Communication::MOVE, ""});
        while (_tiles[3].food > 0)
        {
            addCommand({Communication::TAKE, "food"});
            _tiles[3].food -= 1;
        }
    }
}

void Waiter::LevelUp()
{
    if (_inventory.linemate >= 1 && _inventory.food > 20 && _level == 1) {
        addCommand({Communication::SET, "linemate"});
        _canLvlUp = true;
        _nbrPlayerNeed = 1;
    }
    if (_inventory.linemate >= 1 && _inventory.deraumere >= 1 
    && _inventory.sibur >= 1 && _inventory.food > 20 && _level == 2) {
        addCommand({Communication::SET, "linemate"});
        addCommand({Communication::SET, "deraumere"});
        addCommand({Communication::SET, "sibur"});
        _canLvlUp = true;
        _nbrPlayerNeed = 2;
    }
    if (_inventory.linemate >= 2 && _inventory.sibur >= 1 
    && _inventory.phiras >= 2 && _inventory.food > 14 && _level == 3) {
        addCommand({Communication::SET, "linemate"});
        addCommand({Communication::SET, "linemate"});
        addCommand({Communication::SET, "sibur"});
        addCommand({Communication::SET, "phiras"});
        addCommand({Communication::SET, "phiras"});
        _canLvlUp = true;
    }
    if (_inventory.linemate >= 1 && _inventory.deraumere >= 1 && _inventory.sibur >= 2 
    && _inventory.phiras >= 1 && _inventory.food > 14 && _level == 4) {
        // addCommand({Communication::INCANTATION, ""});
    }
    if (_inventory.linemate >= 1 && _inventory.deraumere >= 2 && _inventory.sibur >= 1 
    && _inventory.mendiane >= 3 && _inventory.food > 14 && _level == 5) {
        // addCommand({Communication::INCANTATION, ""});
    }
    if (_inventory.linemate >= 1 && _inventory.deraumere >= 2 && _inventory.sibur >= 3 
    && _inventory.phiras >= 1 && _inventory.food > 14 && _level == 6) {
        // addCommand({Communication::INCANTATION, ""});
    }
    if (_inventory.linemate >= 2 && _inventory.deraumere >= 2 
    && _inventory.sibur >= 2 && _inventory.mendiane >= 2
    && _inventory.phiras >= 2 && _inventory.thystame >= 1
    && _inventory.food > 14 && _level == 7) {
        // addCommand({Communication::INCANTATION, ""});
    }
}

void Waiter::AskHelp()
{
    addCommand({Communication::BROADCAST, "Help me brother"});
    addCommand({Communication::LOOK, ""});
}

void Waiter::GoHelp()
{
    if (_direction == 0){}
    else if (_direction == 1) {
        addCommand({Communication::MOVE, ""});
    }
    else if (_direction == 2) {
        addCommand({Communication::MOVE, ""});
        addCommand({Communication::LEFT, ""});
        addCommand({Communication::MOVE, ""});
    }
    else if (_direction == 3) {
        addCommand({Communication::LEFT, ""});
        addCommand({Communication::MOVE, ""});
    }
    else if (_direction == 4) {
        addCommand({Communication::LEFT, ""});
        addCommand({Communication::MOVE, ""});
        addCommand({Communication::LEFT, ""});
        addCommand({Communication::MOVE, ""});
    }
    else if (_direction == 5) {
        addCommand({Communication::LEFT, ""});
        addCommand({Communication::LEFT, ""});
        addCommand({Communication::MOVE, ""});
    }
    else if (_direction == 6) {
        addCommand({Communication::RIGHT, ""});
        addCommand({Communication::MOVE, ""});
        addCommand({Communication::RIGHT, ""});
        addCommand({Communication::MOVE, ""});
    }
    else if (_direction == 7) {
        addCommand({Communication::RIGHT, ""});
        addCommand({Communication::MOVE, ""});
    }
    else if (_direction == 8) {
        addCommand({Communication::MOVE, ""});
        addCommand({Communication::RIGHT, ""});
        addCommand({Communication::MOVE, ""});
    }
}