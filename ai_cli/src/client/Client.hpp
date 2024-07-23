/*
** EPITECH PROJECT, 2022
** Project Zappy
** File description:
** Client.hpp
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <string>
#include <arpa/inet.h>

class Client {
    public:
        enum Status {
            GOOD,
            BAD,
            ERROR
        };
        Client();
        Client(std::string const &ip, const unsigned int port);
        ~Client();
        bool sendMessageToServer(std::string const &message);
        std::string receiveMessageFromServer(void);
        bool isConnected() const;
        void connect_server(std::string const &ip , const unsigned int port);
        bool serverIsOpen();
        Status isAvailable();

    protected:
    private:
        int _serverFd;
        struct sockaddr_in _address;
        fd_set _rdfs;
};

#endif /* !CLIENT_HPP_ */
