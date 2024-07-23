/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-pierre-alexandre.delgado-arevalo
** File description:
** Waiter
*/

#include <iostream>
#include <thread>
#include <unistd.h>
#include "ErrorClient.hpp"
#include "Waiter.hpp"
#include "Parser.hpp"

Waiter::Waiter(int id, const unsigned int port, std::string const &ip, std::string const &name) :
    _comDealer(&Waiter::commandDealer, this), _serverResponse(&Waiter::receiveCommand, this), _server(port, ip, name, id + 1), _id(id), _level(1), _canLvlUp(false), _nbrPlayerNeed(1), _help(false), _criticalState(false), _posLook(0)
{
}

Waiter::~Waiter()
{
}

Waiter::Status Waiter::spawnPlayer(std::string const &team)
{
    try {
        auto params = _server.firstCommunication(team + "\n");
        if (!params.first)
            return BAD;
        _teamSlotLeft = params.second.first;
        _mapSize = params.second.second;
    } catch (const ErrorCommunication &error){
        return ERROR;
    }
    _startCv.notify_one();
    return GOOD;
}

bool Waiter::connectToServer(std::string const &ip, const unsigned int port)
{
    if (!_server.initCommunication(ip, port)) {
        std::cerr << "Can't connect to server\n";
        return false;
    }
    std::cout << "Welcome to our fabulous AI for Zappy\n";
    return true;
}

void Waiter::run()
{
    std::cout << _teamSlotLeft << " left, " << "Map size : " << _mapSize.first << " * " << _mapSize.second<< std::endl;

    addCommand({Communication::LOOK, ""});

    _serverResponse.join();
    _orderCv.notify_all();
}

bool Waiter::isOk(std::string const &str)
{
    if (str == "ok\n")
        return true;
    return false;
}

bool Waiter::move(std::string const &response)
{
    if (!isOk(response))
        return true;
    std::cout << "moved\n";
    return true;
}

bool Waiter::right(std::string const &response)
{
    if (!isOk(response))
        return true;
    std::cout << "righted\n";
    return true;
}

bool Waiter::left(std::string const &response)
{
    if (!isOk(response))
        return true;
    std::cout << "lefted\n";
    return true;
}

bool Waiter::look(std::string const &response)
{
    _tiles = Parser::getTiles(response);
    int i = 0;

    for (auto it : _tiles) {
        std::cout << "Tile " << i << " got : " <<
        it.food << " food , " <<
        it.linemate << " linemate, " <<
        it.deraumere << " deraumere, " <<
        it.sibur << " sibur, " <<
        it.mendiane << " mendiane, " <<
        it.phiras << " phiras, " <<
        it.thystame << " thystame, " <<
        it.player << " player\n" <<
        std::endl;
        ++i;
    }
    if (_help == false) {
        if (_canLvlUp == true && _tiles[0].player >= _nbrPlayerNeed) {
            addCommand({Communication::INCANTATION, ""});
        }
        else if (_canLvlUp == true && _tiles[0].player < _nbrPlayerNeed)
            AskHelp();
        else {
            searchFood();
            searchRock();
            addCommand({Communication::INVENTORY, ""});
        }
    }
    return true;
}

bool Waiter::inventory(std::string const &response)
{
    _inventory = Parser::getInventory(response);

    std::cout << "I have : " <<
    _inventory.food << " food , " <<
    _inventory.linemate << " linemate, " <<
    _inventory.deraumere << " deraumere, " <<
    _inventory.sibur << " sibur, " <<
    _inventory.mendiane << " mendiane, " <<
    _inventory.phiras << " phiras, " <<
    _inventory.thystame << " thystame, " <<
    std::endl;
    LevelUp();
    addCommand({Communication::LOOK, ""});
    return true;
}

bool Waiter::broadcast(std::string const &response)
{
    if (!isOk(response))
        return true;
    std::cout << "broadcasted\n";
    return true;
}

bool Waiter::connectNbr(std::string const &response)
{
    int value = -1;

    try {
        value = std::stoi(response.c_str());
    } catch (std::invalid_argument const &err) {
    } catch (std::out_of_range const &err){
    }
    if (value == -1); // fail
    else
        std::cout << value << " unused slots." << std::endl;
    return true;
}

bool Waiter::fork(std::string const &response)
{
    if (!isOk(response))
        return true;
    std::cout << "forked\n";
    return true;
}

bool Waiter::eject(std::string const &response)
{
    if (!isOk(response)) {
        std::cout << "eject failed\n";
    } else {
        std::cout << "eject succeeded\n";
    }
    return true;
}

bool Waiter::take(std::string const &response)
{
    if (!isOk(response)) {
        std::cout << "take failed\n";
    } else {
        std::cout << "take succeeded\n";
    }
    return true;
}

bool Waiter::set(std::string const &response)
{
    if (!isOk(response)) {
        std::cout << "set failed\n";
    } else {
        std::cout << "set succeeded\n";
    }
    return true;
}

bool Waiter::incantion(std::string const &response)
{
    if (response == "ko\n") {
        std::cout << "incantation failed\n";
        addCommand({Communication::LOOK, ""});
        return true;
    }
    std::cout << "starting incantation\n";
    _response.insert(_response.begin(), Communication::INCANTATION_END);
    return false;
}

bool Waiter::endIncantion(std::string const &response)
{
    if (response == "ko\n") {
        std::cout << "incantation failed\n";
        addCommand({Communication::LOOK, ""});
        return true;
    }
    std::cout << "incantation finished\n";
    _level += 1;
    _canLvlUp = false;
    addCommand({Communication::BROADCAST, "Thx brother"});
    addCommand({Communication::INVENTORY, ""});
    return true;
}

Waiter::Status Waiter::isBroadcastMessage(std::string &message, int &direction)
{
    std::string tmp = Parser::extractFirstDelim(message, ",");

    if (tmp == message || "message" != Parser::extractFirstDelim(tmp, " "))
        return BAD;
    try {
        direction = std::stoi(tmp.c_str());
    } catch (std::invalid_argument const &err) {
        return ERROR;
    } catch (std::out_of_range const &err){
        return ERROR;
    }
    return GOOD;
}

bool Waiter::catchBroadcast(std::string const &response)
{
    std::string message = response;
    _direction = 0;
    Status status = isBroadcastMessage(message, _direction);

    if (status == BAD)
        return false;
    else if (status == ERROR)
        return true;
    std::cout << "c'est un message : [" << message << "] depuis " << _direction << " bloc\n";
    if (message == " Help me brother") {
        _help = true;
        GoHelp();
    }
    else if (message == " Thx brother")
        _help = false;
    return true;
}

bool Waiter::catchLevelUp(std::string const &response)
{
    if (_response.size() != 0 && _response.begin().operator*() == Communication::INCANTATION_END)
        return false;
    if (response.compare(0, 15, "Current level: ") != 0)
        return false;
    endIncantion(response);
    return true;
}

bool Waiter::catchGroupIncantation(std::string const &response)
{
    if (_response.size() != 0 && _response.begin().operator*() == Communication::INCANTATION)
        return false;
    if (response == "Elevation underway\n") {
        std::cout << "starting incantation\n";
        _response.insert(_response.begin(), Communication::INCANTATION_END);
        return true;
    }
    return false;
}

bool Waiter::died(std::string const &response)
{
    if (response == "dead\n") {
        _finito = true;
        std::cout << "meurtre" << std::endl;
        return true;
    }
    return false;
}

char Waiter::getRole() const
{
    return _role;
}

char Waiter::getId() const
{
    return _id;
}

int Waiter::getLevel() const
{
    return _level;
}

int Waiter::getSquad() const
{
    return _squad;
}

int Waiter::getMessageSent() const
{
    return _message_sent;
}
