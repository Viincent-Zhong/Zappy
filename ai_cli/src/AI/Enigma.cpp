/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-pierre-alexandre.delgado-arevalo
** File description:
** Enigma
*/

#include "Enigma.hpp"

Zappy::Enigma::Enigma()
{
}

Zappy::Enigma::~Enigma()
{
}


std::string Zappy::Enigma::fillSpaces(int nb_spaces, std::string message)
{
    std::string tmp = "";

    for (int i = nb_spaces - message.size(); i > 0; i--)
        tmp += "0";
    return tmp + message;
}

std::string Zappy::Enigma::messageEncrypt(Waiter &player, bool which_squad, char roles, Waiter::Inventory inv, Zappy::Goal goal)
{
    std::string tmp = SecretCodeEncrypt(player, which_squad, roles);
    
    switch (goal) {
        case Goal::NEED:
        case Goal::HAVE:
            tmp += ResourcesEncrypt("Food", inv.food, goal);
            tmp += ResourcesEncrypt("Linemate", inv.linemate, goal);
            tmp += ResourcesEncrypt("Deraumere", inv.deraumere, goal);
            tmp += ResourcesEncrypt("Sibur", inv.sibur, goal);
            tmp += ResourcesEncrypt("Mendiane", inv.mendiane, goal);
            tmp += ResourcesEncrypt("Phiras", inv.phiras, goal);
            tmp += ResourcesEncrypt("Thystame", inv.thystame, goal);
            break;
        case Goal::COME:
            tmp += "Come here, ";
        case Goal::GOING:
            tmp += "Going ToChiefClimber, ";
        case Goal::REQUEST:
            tmp += "Request Everyone, ";
        case Goal::GIVE:
            tmp += "Give " + std::to_string(player.getMessageSent());
        default:
            break;
    }

    return getRoleToString(player.getRole()) + " "
        + std::to_string(player.getLevel()) + " "
        + SecretCodeEncrypt(player, which_squad, roles) + ", "
        + tmp; // todo requête temporaire
}

Zappy::Data Zappy::Enigma::messageDecrypt(std::string &message)
{
    Zappy::Data tmp;
    tmp.inventory = {
        .food = 0,
        .linemate = 0,
        .deraumere = 0,
        .sibur = 0,
        .mendiane = 0,
        .phiras = 0,
        .thystame = 0};
    tmp.message_sent = "0000";
    std::regex first_regex("\\s?+(ChiefClimber|Climber|DeliWrecker) ([1-8]) ([0-9]+) ([0-9]+)\\s?+,?");
    std::regex second_regex("\\s?+(Come|Going|Need|Have|Request|Give) ([0-9]?+) (food|linemate|deraumere|sibur|mendiane|phiras|thystame|here|there|message)\\s?+,?");
    std::smatch code;
    std::string message_tmp = message;

    std::regex_search(message_tmp, code, first_regex);
    std::string secret_code = std::string(code[4]);

    std::cout << code[1] << std::endl << code[2] << std::endl << code[3] << std::endl << code[4] << std::endl << std::endl;
    if (code[0] == ""
    || !(code[1] == "ChiefClimber" && secret_code.compare(5, 1, "1") == 0 || code[1] == "Climber" && secret_code.compare(5, 1, "2") == 0 || code[1] == "Deliwrecker" && secret_code.compare(5, 1, "4") == 0)
    || !secret_code.compare(6, 1, code[2]) == 0
    || !secret_code.compare(7, 2, code[3]) == 0)
        return tmp;

    std::string message_left = code.suffix().str();
    std::smatch leftovers;
    std::regex_search(message_left, leftovers, second_regex);
    std::cout << message_left << std::endl << leftovers[0] << leftovers[2] << leftovers[3] << std::endl;
    if (leftovers[1] == "Come" || leftovers[1] == "Going" || leftovers[1] == "Request")
        tmp.goal = (leftovers[1] == "Come" ? Zappy::Goal::COME : (leftovers[1] == "Going" ? Zappy::Goal::GOING : Zappy::Goal::REQUEST));
    else if (leftovers[1] == "Give") {
        tmp.goal = Zappy::Goal::GIVE;
        std::string m_sent = code[4];
        tmp.message_sent = m_sent.substr(0, 4);
    } else {
        tmp.goal = (leftovers[1] == "Have" ? Zappy::Goal::HAVE : Zappy::Goal::NEED);
        // tmp.inventory.food = 
    }
    // leftovers.
    std::cout << tmp.goal + 90 << " " << tmp.message_sent << " food:" << tmp.inventory.food << " linemate:" << tmp.inventory.linemate
    << " deraumere:" << tmp.inventory.deraumere << " sibur:" << tmp.inventory.sibur << " mendiane:" << tmp.inventory.mendiane <<
    " phiras:" << tmp.inventory.phiras << " thystame:" << tmp.inventory.thystame << std::endl;
    return tmp;
}

std::string Zappy::Enigma::SecretCodeEncrypt(Waiter &player, bool &which_squad, char &roles)
{
    return fillSpaces(4, std::to_string(player.getMessageSent()))
        + std::to_string(roles)
        + std::to_string(player.getRole())
        + std::to_string(player.getLevel())
        + fillSpaces(2, std::to_string(player.getId()))
        + std::to_string(which_squad)
        + std::to_string(player.getSquad());
}

bool Zappy::Enigma::SecretCodeDecrypt()
{
    
    return true;
}

std::string Zappy::Enigma::ResourcesEncrypt(std::string resource, int nb_resource, Zappy::Goal goal)
{
    if (nb_resource && goal == Zappy::Goal::NEED)
        return "Need " + std::to_string(nb_resource) + " " + resource + ", ";
    else if (nb_resource && goal == Zappy::Goal::HAVE)
        return "Have " + std::to_string(nb_resource) + " " + resource + ", ";
    return "";
}

void Zappy::Enigma::ResourcesDecrypt(Data &data, std::string)
{

}

std::string Zappy::Enigma::getRoleToString(char role)
{
    if (role == 1)
        return "ChiefClimber";
    else if (role == 2)
        return "Climber";
    else if (role == 4)
        return "DeliWrecker";
    return "NoRole";
}
