/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** Communication.cpp
*/

#include <unistd.h>
#include <iostream>
#include "Communication.hpp"
#include "Parser.hpp"
#include "ErrorClient.hpp"

Communication::Communication(const unsigned int port, std::string const &ip, std::string const &name, const unsigned int id) : _port(port), _ip(ip), _name(name), _id(id)
{
}

Communication::~Communication()
{
}

bool Communication::initCommunication(std::string const &ip, const unsigned int port)
{
    try {
        _server.connect_server(ip, port);
    } catch (const ErrorClient &error) {
        return false;
    }
    if (!_server.isConnected())
        return false;
    return true;
}

void Communication::commandMove(std::string const &msg)
{
    _server.sendMessageToServer("Forward\n");
}

void Communication::commandTurnRight(std::string const &msg)
{
    _server.sendMessageToServer("Right\n");
}

void Communication::commandTurnLeft(std::string const &msg)
{
    _server.sendMessageToServer("Left\n");
}

void Communication::commandLook(std::string const &msg)
{
    _server.sendMessageToServer("Look\n");
}

void Communication::commandInventory(std::string const &msg)
{
    _server.sendMessageToServer("Inventory\n");
}

void Communication::commandBroadCast(std::string const &text)
{
    _server.sendMessageToServer("Broadcast " + text + "\n");
}

void Communication::commandConnectNbr(std::string const &msg)
{
    _server.sendMessageToServer("Connect_nbr\n");
}

void Communication::commandFork(std::string const &msg)
{
    Waiter::Status status;
    pid_t pid;
    Waiter ai(_id, _port, _ip, _name);

    _server.sendMessageToServer("Fork\n");
    pid = fork();
    switch (pid)
    {
        case -1:
            std::cerr << "Error with fork";
            break;
        case 0:
            if (!ai.connectToServer(_ip, _port))
                return;
            status = ai.spawnPlayer(_name);
            if (status == Waiter::ERROR)
                return;
            else if (status == Waiter::GOOD)
                ai.run();
            else
                std::cout << "mauvaise connection\n";
            break;
        default:
            break;
    }
}

void Communication::commandEject(std::string const &msg)
{
    _server.sendMessageToServer("Eject\n");
}

void Communication::commandDeath(std::string const &msg)
{
}

void Communication::commandTake(std::string const &object)
{
    _server.sendMessageToServer("Take " + object + "\n");
}

void Communication::commandSet(std::string const &object)
{
    _server.sendMessageToServer("Set " + object + "\n");
}

void Communication::commandIncantation(std::string const &msg)
{
    _server.sendMessageToServer("Incantation\n");
}

std::string Communication::readFromServer()
{
    return _server.receiveMessageFromServer();
}

Client::Status Communication::serverAvailable()
{
    return _server.isAvailable();
}


std::pair<bool, std::pair<int, std::pair<int, int>>> Communication::firstCommunication(std::string const &teamName)
{
    std::vector<std::string> response;
    std::pair<int, std::pair<int, int>> params;
    std::string servRep;

    _server.receiveMessageFromServer();
    _server.sendMessageToServer(teamName);
    servRep = _server.receiveMessageFromServer();
    if (servRep == "ko\n")
        return {false, params};
    response = Parser::parsePrompt(servRep, "\n");

    if (response.size() != 2)
        throw ErrorCommunication("Bad params");
    try {
        params.first = std::stoi(response.at(0));
    } catch (const std::invalid_argument &error) {
        throw ErrorCommunication("Bad params");
    }

    auto dimension = Parser::parsePrompt(response.at(1), " ");
    if (dimension.size() != 2)
        throw ErrorCommunication("Bad params");
    try {
        params.second = {std::stoi(dimension.at(0)), std::stoi(dimension.at(1))};
    } catch (const std::invalid_argument &error) {
        throw ErrorCommunication("Bad params");
    }
    return {true, params};
}
