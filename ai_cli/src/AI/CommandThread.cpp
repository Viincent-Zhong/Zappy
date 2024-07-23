/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** CommandThread
*/

#include <iostream>
#include <functional>
#include "Waiter.hpp"
#include "ErrorClient.hpp"

void Waiter::commandDealer()
{
    std::map<Communication::Action, Communication::Command> actions = {
        {Communication::MOVE, &Communication::commandMove},
        {Communication::RIGHT, &Communication::commandTurnRight},
        {Communication::LEFT, &Communication::commandTurnLeft},
        {Communication::LOOK, &Communication::commandLook},
        {Communication::INVENTORY, &Communication::commandInventory},
        {Communication::BROADCAST, &Communication::commandBroadCast},
        {Communication::CONNECT_NBR, &Communication::commandConnectNbr},
        {Communication::FORK, &Communication::commandFork},
        {Communication::EJECT, &Communication::commandEject},
        {Communication::TAKE, &Communication::commandTake},
        {Communication::SET, &Communication::commandSet},
        {Communication::INCANTATION, &Communication::commandIncantation}
    };

    std::map<Communication::Action, Communication::Command>::iterator act;
    std::pair<Communication::Action, std::string> command;
    std::string response;

    int i = 0;
    while (!_finito) {
        {
            std::unique_lock <std::mutex> uk(_takeOrder);
            _orderCv.wait(uk);
            if (_finito)
                return;
            if (_commands.size() == 0)
                continue;
            command = _commands.begin().operator*();
            act = actions.find(command.first);
            if (act != actions.end()) {
                (_server.*(act->second))(command.second);
                _tookCommand = true;
                _response.push_back(command.first);
            }
            _commands.erase(_commands.begin());
        }
    }
}

void Waiter::receiveCommand()
{
    Client::Status status;
    std::string response;

    {
        std::unique_lock <std::mutex> uk(_start);
        _startCv.wait(uk);
    }

    while (!_finito) {
        status = _server.serverAvailable();
        if (status == Client::ERROR) {
            _finito = true;
            return;
        } else if (status == Client::BAD)
            continue;
        try {
            response = _server.readFromServer();
        } catch (const ErrorCommunication &error) {
            _finito = true;
            return;
        }
        interpretResponse(response);
    }
}

void Waiter::interpretResponse(std::string const &response)
{
    if (died(response) || catchBroadcast(response) || catchLevelUp(response) || catchGroupIncantation(response))
        return;
    if (_response.size() == 0)
        return;
    auto rep = _response.begin();
    auto did = _iaActions.find(rep.operator*());
    _response.erase(rep);
    if (did == _iaActions.end())
        return;
    if (((this->*(did->second))(response)))
        _orderCv.notify_one();
}

void Waiter::addCommand(std::pair<Communication::Action, std::string> const &message)
{
    _commands.push_back(message);
    _orderCv.notify_one();
}
