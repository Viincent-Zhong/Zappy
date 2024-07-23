/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** unit_test_parse_command
*/

#include <criterion/criterion.h>
#include "server.h"

static char *construct_str(char *str)
{
    char *new_str = malloc(sizeof(char) * (strlen(str) + 1));

    new_str[0] = 0;
    strcat(new_str, str);
    return new_str;
}

Test(parse_simple_line, multiple_argument)
{
    char cmp[9][3] = {"X", "Y", "q0", "q1", "q2", "q3", "q4", "q5", "q6"};
    char *str = construct_str("X Y q0 q1 q2 q3 q4 q5 q6");
    char **arr = parse_string(str, " ");

    for (int i = 0; i < 9 && arr[i]; ++i) {
        cr_expect_str_eq(cmp[i], arr[i]);
    }
}

Test(parse_annoying_line, multiple_argument)
{
    char cmp[9][3] = {"X", "Y", "q0", "q1", "q2", "q3", "q4", "q5", "q6"};
    char *str = construct_str("        X      Y      q0     q1     q2     q3     q4     q5    q6");
    char **arr = parse_string(str, " ");

    for (int i = 0; i < 9 && arr[i]; ++i) {
        cr_expect_str_eq(cmp[i], arr[i]);
    }
}

Test(parse_simple_line1, one_argument)
{
    char cmp[1][2] = {"n"};
    char *str = construct_str("n");
    char **arr = parse_string(str, " ");

    for (int i = 0; i < 1 && arr[i]; ++i) {
        cr_expect_str_eq(cmp[i], arr[i]);
    }
}

Test(parse_error1, error_argument)
{
    char **arr = parse_string(NULL, " ");

    cr_expect_null(arr);
}

Test(parse_error2, error_argument)
{
    char **arr = parse_string("ok chien", NULL);

    cr_expect_null(arr);
}

Test(parse_error3, error_argument)
{
    char **arr = parse_string(NULL, NULL);

    cr_expect_null(arr);
}