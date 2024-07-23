/*
** EPITECH PROJECT, 2022
** Project Zappy
** File description:
** Client.cpp
*/

#include <iostream>
#include <unistd.h>
#include "Client.hpp"
#include "ErrorClient.hpp"

Client::Client() : _serverFd(-1)
{
}

Client::~Client()
{
}

Client::Client(std::string const &ip, const unsigned int port)
{
    try {
        connect_server(ip, port);
    } catch(const ErrorClient& e) {
        std::cerr << e.what() << '\n';
        _serverFd = -1;
    }
    
}

void Client::connect_server(std::string const &ip , const unsigned int port)
{
    if ((_serverFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        throw ErrorClient(ErrorClient::SOCKET);

    _address.sin_family = AF_INET;
    _address.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &_address.sin_addr) <= 0)
        throw ErrorClient(ErrorClient::ADDRESS);
    if (connect(_serverFd, (struct sockaddr*)&_address, sizeof(_address)) < 0)
        throw ErrorClient(ErrorClient::CONNECTION);
}

bool Client::sendMessageToServer(std::string const &message)
{
    if (send(_serverFd, message.c_str(), message.size(), MSG_NOSIGNAL) == EPIPE) {
        _serverFd = -1;
        return false;
    }
    return true;
}

std::string Client::receiveMessageFromServer(void)
{
    char buffer[1024] = {0};

    if (read(_serverFd, buffer, 1024) <= 0)
        throw ErrorCommunication("Couldn't read");
    return std::string(buffer);
}

bool Client::isConnected() const
{
    if (_serverFd == -1)
        return false;
    return true;
}

Client::Status Client::isAvailable()
{
    FD_ZERO(&_rdfs);
    FD_SET(_serverFd, &_rdfs);
    if (select(_serverFd + 1, &_rdfs, NULL, NULL, NULL) == -1)
        return Client::ERROR;
    if (FD_ISSET(_serverFd, &_rdfs))
        return Client::GOOD;
    return Client::BAD;
}