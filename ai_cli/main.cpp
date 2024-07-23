/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** main.cpp for ai client
*/

#include <iostream>
#include "Waiter.hpp"
#include "Client.hpp"
#include "Params.hpp"

int main(int ac, char **av)
{
    Params param;
    Waiter::Status status;

    if (!param.getParams(ac, av))
        return 84;
    std::cout << param.getPort() << "\n";
    static int id_ai = 1;
    Waiter ai(id_ai, param.getPort(), param.getMachine(), param.getName());
    if (!ai.connectToServer(param.getMachine(), param.getPort()))
        return 0;
    status = ai.spawnPlayer(param.getName());
    if (status == Waiter::ERROR)
        return 0;
    else if (status == Waiter::GOOD)
        ai.run();
    else
        std::cout << "mauvaise connection\n";
    return 0;
}