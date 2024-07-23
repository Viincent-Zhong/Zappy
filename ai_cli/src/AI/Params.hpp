/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-pierre-alexandre.delgado-arevalo
** File description:
** params.hpp
*/
#ifndef PARAMS_HPP_
#define PARAMS_HPP_
#include <iostream>

class Params {
    public :
        Params();
        ~Params();
        bool getParams(const unsigned int ac, char **av);
        int getPort() const;
        const std::string &getName() const;
        const std::string &getMachine() const;

    private :
        int _port;
        std::string _name;
        std::string _machine;

};

#endif  /* !PARAMS_HPP_ */
