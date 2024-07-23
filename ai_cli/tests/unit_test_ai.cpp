/*
** EPITECH PROJECT, 2022
** Project Zappy
** File description:
** unit_test_ai.cpp
*/

#include <criterion/criterion.h>
#include "Parser.hpp"
#include "Waiter.hpp"

Test(run, start_ai)
{
    cr_expect_eq(1, 1);
}

Test(message, to_first_delim)
{
    std::string str("message 1, go volez les jaunes");
    cr_expect_str_eq(Parser::extractFirstDelim(str, ",").c_str(), "message 1");
    cr_expect_str_eq(str.c_str(), " go volez les jaunes");
}

Test(message2, to_first_delim)
{
    std::string str("message 1");
    cr_expect_str_eq(Parser::extractFirstDelim(str, ",").c_str(), "message 1");
    cr_expect_str_eq(str.c_str(), "message 1");
}

Test(message3, to_first_delim)
{
    std::string str("message 1, ???");
    cr_expect_str_eq(Parser::extractFirstDelim(str, ",").c_str(), "message 1");
    cr_expect_str_eq(str.c_str(), " ???");
}

Test(message4, to_first_delim)
{
    std::string str("message 1, e dacord");
    cr_expect_str_eq(Parser::extractFirstDelim(str, ",").c_str(), "message 1");
    cr_expect_str_eq(str.c_str(), " e dacord");
}