/*
** EPITECH PROJECT, 2022
** Project Zappy
** File description:
** ErrorClient.hpp
*/

#ifndef ERRORCLIENT_HPP_
#define ERRORCLIENT_HPP_

#include <functional>
#include <string>

class ErrorClient : public std::exception {
    public:
        enum ErrorType {
            SOCKET,
            ADDRESS,
            CONNECTION,
            CUSTOM
        };
        ErrorClient();
        ErrorClient(std::string const &msg);
        ErrorClient(ErrorType const &type);
        ~ErrorClient();
        const char *what() const noexcept override;

    protected:
    private:
        ErrorType _error;
        std::string _errorMsg;
};

class ErrorCommunication : public std::exception {
    public :
        ErrorCommunication();
        ~ErrorCommunication();
        ErrorCommunication(std::string const &msg);
        const char *what() const noexcept override;
    private:
        std::string _errorMessage;
};

#endif /* !ERRORCLIENT_HPP_ */
