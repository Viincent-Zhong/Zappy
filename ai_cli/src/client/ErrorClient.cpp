/*
** EPITECH PROJECT, 2022
** Project Zappy
** File description:
** ErrorClient.cpp
*/

#include "ErrorClient.hpp"

ErrorClient::ErrorClient()
{
}

ErrorClient::~ErrorClient()
{
}

ErrorClient::ErrorClient(std::string const &msg)
{
    this->_errorMsg = msg;
    this->_error = ErrorType::CUSTOM;
}

ErrorClient::ErrorClient(ErrorType const &type)
{
    this->_error = type;
}

const char *ErrorClient::what() const noexcept
{
    if (this->_error == ErrorType::CUSTOM)
        return this->_errorMsg.c_str();
    if (this->_error == ErrorType::ADDRESS)
        return "Bad adress IP or PORT";
    if (this->_error == ErrorType::SOCKET)
        return "Error socket";
    if (this->_error == ErrorType::CONNECTION)
        return "Can't connect to the server";
    return "Unknow error";
}

ErrorCommunication::ErrorCommunication()
{
}

ErrorCommunication::~ErrorCommunication()
{
}

ErrorCommunication::ErrorCommunication(std::string const &msg)
{
    _errorMessage = msg;
}

const char *ErrorCommunication::what() const noexcept
{
    return _errorMessage.c_str();
}
