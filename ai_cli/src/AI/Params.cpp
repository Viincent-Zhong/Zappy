/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-pierre-alexandre.delgado-arevalo
** File description:
** params.cpp
*/
#include <iostream>
#include "Params.hpp"

Params::Params()
{
    _port = 4242;
    _name = "Trantor's";
    _machine = "127.0.0.1";
}

Params::~Params()
{
}

bool Params::getParams(const unsigned int ac, char **av)
{
    if (ac == 2 && (std::string("-help").compare(av[1]) || std::string("-h").compare(av[1]))) {
        std::cout << "USAGE: ./zappy_ai -p port -n name -h machine" << std::endl
        << "\tport\tis the port number" << std::endl
        << "\tname\tis the name of the team" << std::endl
        << "\tmachine\tis the name of the machine; localhost by default" << std::endl;
        return false;
    }
    for (int i = 1; i < ac; i+=2) {
        if (std::string("-p").compare(av[i]) == 0)
            _port = std::stoi(av[i+1]);
        if (std::string("-n").compare(av[i]) == 0)
            _name = av[i+1];
        if (std::string("-h").compare(av[i]) == 0)
            _machine = av[i+1];
    }
    return true;
}

int Params::getPort() const
{
    return _port;
}

const std::string &Params::getName() const
{
    return _name;
}

const std::string &Params::getMachine() const
{
    return _machine;
}
