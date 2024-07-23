/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** parse
*/

#include <string.h>
#include <stdlib.h>

static char *capture_cmd(char *str, int *i)
{
    char *cmd;
    int len = 0;

    for (int x = *i; str[x] && str[x] != ' ' && str[x] != '\t'; ++x, ++len)
        if (str[x] == '\n' || str[x] == '\r')
            break;
    cmd = malloc(sizeof(char) * (len + 1));
    if (cmd == NULL)
        return NULL;
    for (int x = 0; str[*i] && str[*i] != ' ' &&
    str[*i] != '\t'; ++(*i), ++x) {
        if (str[*i] == '\n' || str[*i] == '\r')
            break;
        cmd[x] = str[*i];
    }
    cmd[len] = '\0';
    return cmd;
}

char **capture_command(char *str)
{
    char **cmd = malloc(sizeof(char *) * (3));
    int len = 0;
    int i = 0;

    if (cmd == NULL)
        return NULL;
    for (int i = 0; i < 3; cmd[i] = NULL, ++i);
    if ((cmd[0] = capture_cmd(str, &i)) == NULL)
        return cmd;
    for (; str[i] == ' ' || str[i] == '\n' || str[i] == '\r'
    || str[i] == '\t'; ++i);
    if ((len = strlen(str) - i) <= 0)
        return cmd;
    if ((cmd[1] = malloc(sizeof(char) * (len + 1))) == NULL)
        return cmd;
    for (int j = 0; str[i]; ++i, ++j)
        cmd[1][j] = str[i];
    cmd[1][len] = '\0';
    return cmd;
}

void free_array(char **array)
{
    for (int i = 0; array[i] != NULL; ++i)
        free(array[i]);
    free(array);
}

char **parse_string(char *str, const char *delim)
{
    char **arr = NULL;
    char *parsed;
    int occu = 1;
    int j = 0;

    if (!str || !delim)
        return NULL;
    for (int i = 0, tmp; str[i]; ++i) {
        if (str[i] == delim[0])
            ++occu;
        for (;str[i] == delim[0]; ++i);
    }
    parsed = strtok(str, delim);
    arr = malloc(sizeof(char *) * (occu + 1));
    for (j = 0; parsed != NULL; ++j) {
        arr[j] = parsed;
        parsed = strtok(NULL, delim);
    }
    arr[j] = NULL;
    return arr;
}