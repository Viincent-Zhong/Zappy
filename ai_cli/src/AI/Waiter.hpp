/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-pierre-alexandre.delgado-arevalo
** File description:
** Waiter
*/

#ifndef WAITER_HPP_
#define WAITER_HPP_

#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Communication.hpp"

class Waiter {
    public:
        enum Status {
            GOOD,
            BAD,
            ERROR
        };
        // enum Resources {
        //     FOOD,
        //     LINEMATE,
        //     DERAUMERE,
        //     SIBUR,
        //     MENDIANE,
        //     PHIRAS,
        //     THYSTAME
        // };
        struct Inventory {
            int food;
            int linemate;
            int deraumere;
            int sibur;
            int mendiane;
            int phiras;
            int thystame;
        };
        struct Tile {
            int food;
            int linemate;
            int deraumere;
            int sibur;
            int mendiane;
            int phiras;
            int thystame;
            int player;
        };

        Waiter(int id, const unsigned int port, std::string const &ip, std::string const &name);
        ~Waiter();
        bool connectToServer(std::string const &ip, const unsigned int port);
        Status spawnPlayer(std::string const &team);
        void commandDealer();
        void interpretResponse(std::string const &response);
        void addCommand(std::pair<Communication::Action, std::string> const &message);
        void run();
        void searchFood();
        void searchRock();
        void LevelUp();
        void AskHelp();
        void GoHelp();
        void receiveCommand();

        char getRole() const;
        char getId() const;
        int getLevel() const;
        int getSquad() const;
        int getMessageSent() const;
        typedef bool (Waiter::*Interpret)(std::string const &);

    protected:
        std::map<Communication::Action, Waiter::Interpret> _iaActions = {
            {Communication::MOVE, &Waiter::move},
            {Communication::RIGHT, &Waiter::right},
            {Communication::LEFT, &Waiter::left},
            {Communication::LOOK, &Waiter::look},
            {Communication::INVENTORY, &Waiter::inventory},
            {Communication::BROADCAST, &Waiter::broadcast},
            {Communication::CONNECT_NBR, &Waiter::connectNbr},
            {Communication::FORK, &Waiter::fork},
            {Communication::EJECT, &Waiter::eject},
            {Communication::TAKE, &Waiter::take},
            {Communication::SET, &Waiter::set},
            {Communication::INCANTATION, &Waiter::incantion},
            {Communication::INCANTATION_END, &Waiter::endIncantion}
        };
        bool move(std::string const &response);
        bool right(std::string const &response);
        bool left(std::string const &response);
        bool look(std::string const &response);
        bool inventory(std::string const &response);
        bool broadcast(std::string const &response);
        bool connectNbr(std::string const &response);
        bool fork(std::string const &response);
        bool eject(std::string const &response);
        bool take(std::string const &response);
        bool set(std::string const &response);
        bool incantion(std::string const &response);
        bool endIncantion(std::string const &response);
        bool catchBroadcast(std::string const &response);
        bool died(std::string const &response);
        bool catchLevelUp(std::string const &response);
        bool catchGroupIncantation(std::string const &response);

    private:
        Status isBroadcastMessage(std::string &message, int &direction);
        bool isOk(std::string const &str);
        Communication _server;
        std::vector<std::pair<Communication::Action, std::string>> _commands;
        std::vector<Communication::Action> _response;
        bool _finito = false;
        int _teamSlotLeft = 0;
        std::pair<int, int> _mapSize = {0, 0};
        bool _tookCommand = false;
        bool _help;
        std::vector<Waiter::Tile> _tiles;
        Waiter::Inventory _inventory;
        bool _canLvlUp;
        int _nbrPlayerNeed;
        bool _criticalState;
        std::string _message;
        int _direction;
        std::thread _comDealer;
        std::thread _serverResponse;
        std::mutex _takeOrder;
        std::condition_variable _orderCv;
        std::mutex _start;
        std::condition_variable _startCv;

    private:
        char _role;
        char _id;
        int _level;
        int _squad;
        int _message_sent;
        int _posLook;
};

#endif /* !WAITER_HPP_ */
