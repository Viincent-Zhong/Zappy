/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** utils.h
*/

#ifndef UTILS_H_
    #define UTILS_H_

double distance(int xA, int yA, int xB, int yB);
char **capture_command(char *str);
char *array_to_string(char **array);
void free_array(char **array);
char *concat(const char *s1, const char *s2);

#endif /* !UTILS_H_ */
