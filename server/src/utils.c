/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** utils.c
*/

#include <stdlib.h>
#include <string.h>
#include <math.h>

double distance(int xA, int yA, int xB, int yB)
{
    return sqrt(pow(xB - xA, 2) + pow(yB - yA, 2));
}
