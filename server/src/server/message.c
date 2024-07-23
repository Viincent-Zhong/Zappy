/*
** EPITECH PROJECT, 2022
** Project Zappy
** File description:
** message.c
*/

#include <stdbool.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "server.h"

char *format_message(char *format, ...)
{
    va_list arg1;
    va_list arg2;
    char *buffer;
    size_t size = 1;

    va_start(arg1, format);
    va_copy(arg2, arg1);
    size += vsnprintf(NULL, 0, format, arg2);
    buffer = malloc(size);
    vsnprintf(buffer, size, format, arg1);
    va_end(arg2);
    va_end(arg1);
    return buffer;
}

bool send_message(net_t *serv, const unsigned int fd, const char *msg)
{
    if (!msg)
        return false;
    if (send(fd, msg, strlen(msg), MSG_NOSIGNAL) == -1)
        return false;
    return true;
}

char *read_message(const unsigned int fd)
{
    char response[SIZE_MESSAGE] = {0};
    char *msg = NULL;
    size_t size = 0;
    unsigned int len = 0;

    if (read(fd, response, SIZE_MESSAGE) <= 0)
        return NULL;
    size = strlen(response);
    msg = malloc(sizeof(char) * (strlen(response) + 1));
    memset(msg, 0, sizeof(char) * size);
    strcpy(msg, response);
    len = strlen(msg);
    msg[len == 0 ? 0 : len - 1] = '\0';
    return msg;
}
