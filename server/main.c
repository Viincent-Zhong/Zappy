/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** main.c
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

static int help(void)
{
    fputs("USAGE: ./zappy_server -p port -x width -y height ", stdout);
    puts("-n name1 name2 ... -c clientsNb -f freq");
    puts("\tport      is the port number");
    puts("\twidth     is the width of the world");
    puts("\theight    is the height of the world");
    puts("\tnameX     is the name of the team X");
    puts("\tclientsNb is the number of authorized clients per team");
    puts("\tfreq      is the reciprocal of time unit for execution of actions");
    return 0;
}

int main(int ac, char **av)
{
    if (ac == 2 && (strcmp("-help", av[1]) == 0 || strcmp("-h", av[1]) == 0))
        return help();
    if (!server(ac, av))
        return 84;
    return 0;
}