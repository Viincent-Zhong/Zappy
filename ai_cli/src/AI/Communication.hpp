/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** Communication.hpp
*/

#ifndef COMMUNICATION_HPP_
#define COMMUNICATION_HPP_

#include <functional>
#include <string>
#include <map>
#include "Client.hpp"

/**
 * @brief Class for sending actions to zappy server
 * @author Pierre-Alexandre Delgado
 * @version 1.0
 * @date 03/06/22
 * 
 */
class Communication {
    public:
        enum Action {
            MOVE,
            RIGHT,
            LEFT,
            LOOK,
            INVENTORY,
            BROADCAST,
            CONNECT_NBR,
            FORK,
            EJECT,
            TAKE,
            SET,
            INCANTATION,
            INCANTATION_END
        };
        typedef void (Communication::*Command)(std::string const &);
        /**
         * @brief Construct a new Communication object
         * 
         * @param server 
         */
        Communication(const unsigned int port, std::string const &ip, std::string const &name, const unsigned int _id);

        /**
         * @brief init communication
         * 
         */
        bool initCommunication(std::string const &ip, const unsigned int port);

        /**
         * @brief Destroy the Communication object
         * 
         */
        ~Communication();

        /**
         * @brief send command move to the server, 1 tile
         * 
         */
        void commandMove(std::string const &msg);

        /**
         * @brief send command to turn the player, 90° to the right
         * 
         */
        void commandTurnRight(std::string const &msg);

        /**
         * @brief send command to turn the player, 90° to the left
         * 
         */
        void commandTurnLeft(std::string const &msg);

        /**
         * @brief send command look, return all the tile seen
         * 
         * @return std::string with all the tile content
         */
        void commandLook(std::string const &msg);

        /**
         * @brief send command inventory
         * 
         * @return std::string with the inventory content
         */
        void commandInventory(std::string const &msg);

        /**
         * @brief send command broadcast
         * 
         * @param text to be send to the world
         */
        void commandBroadCast(std::string const &text);

        /**
         * @brief get all client connected in one team
         * 
         */
        void commandConnectNbr(std::string const &msg);

        /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
        void commandFork(std::string const &msg);

        /**
         * @brief send command eject, for eject player from it case
         * 
         */
        void commandEject(std::string const &msg);

        /**
         * @brief ask the server if I am dead
         * 
         */
        void commandDeath(std::string const &msg);

        /**
         * @brief take object and consomme it
         * 
         * @param object 
         */
        void commandTake(std::string const &object);

        /**
         * @brief put object on the ground
         * 
         * @param object 
         */
        void commandSet(std::string const &object);

        /**
         * @brief level up player
         * 
         * @return std::string return level or fail
         */
        void commandIncantation(std::string const &msg);

        /**
         * @brief 
         * 
         * @param teamName 
         */
        std::pair<bool, std::pair<int, std::pair<int, int>>> firstCommunication(std::string const &teamName);
        /**
         * @brief 
         * 
         * @return std::string 
         */
        std::string readFromServer();
        /**
         * @brief 
         * 
         * @return std::string 
         */
        Client::Status serverAvailable();

    private:
        Client _server;
        const unsigned int _id;
        const unsigned int _port;
        const std::string _ip;
        const std::string _name;
};

#endif /* !COMMUNICATION_HPP_ */
