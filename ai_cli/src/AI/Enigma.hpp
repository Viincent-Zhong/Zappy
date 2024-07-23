/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-pierre-alexandre.delgado-arevalo
** File description:
** Enigma
*/

#ifndef ENIGMA_HPP_
#define ENIGMA_HPP_

    #include <string>
    #include <vector>
    #include <regex>
    #include <iostream>
    #include "Waiter.hpp"

namespace Zappy {
    enum Goal {
        NEED,
        HAVE,
        COME,
        GOING,
        GIVE,
        REQUEST,
        UNKNOWN = -1
    };

    enum Roles {
        NOROLE = 0,
        CHIEFCLIMBER = 1,
        CLIMBER = 2,
        DELIWRECKER = 4
    };

    struct Data {
        Waiter::Inventory inventory;
        Goal goal;
        std::string message_sent;
    };

    struct EnigmaCode {
        int message_sent;
        Roles role;
        char level;
        char id;
    };

    class Enigma {
        public:
            Enigma();
            ~Enigma();
            std::string messageEncrypt(Waiter &player, bool which_squad, char roles, Waiter::Inventory inv, Goal goal);
            Data messageDecrypt(std::string &message);
            std::string SecretCodeEncrypt(Waiter &player, bool &which_squad, char &roles);
            bool SecretCodeDecrypt();
            std::string ResourcesEncrypt(std::string resource, int nb_resource, Goal goal);
            void ResourcesDecrypt(Data &data, std::string);
            std::string fillSpaces(int nb_spaces, std::string message);
            std::string getRoleToString(char role);

        protected:
        private:
            std::vector<Zappy::EnigmaCode> _EnigmaCode;
    };
}

#endif /* !ENIGMA_HPP_ */
