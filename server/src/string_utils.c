/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** string_utils.c
*/

#include <stdlib.h>
#include <string.h>

char *concat(const char *s1, const char *s2)
{
    char *result = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));

    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char *array_to_string(char **array)
{
    char *str;
    unsigned int size = 1;

    for (int i = 0; array[i] != NULL; ++i)
        size += strlen(array[i]);
    str = malloc(sizeof(char) * size);
    strcpy(str, "");
    for (int i = 0; array[i] != NULL; ++i)
        strcat(str, array[i]);
    return str;
}
