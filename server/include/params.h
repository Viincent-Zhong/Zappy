/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** params.c
*/

#ifndef PARAMS_H_
    #define PARAMS_H_

    #include <stdbool.h>
    #include <sys/queue.h>

    #define INIT_PORT       4242
    #define INIT_WIDTH      10
    #define INIT_HEIGHT     10
    #define INIT_FREQ       1
    #define INIT_CLIENT_NB  3
    #define INIT_TEAM_NAME  "Trantor's"
    #define ERROR_X "-x option only accepts integer values between 10 and 30\n"
    #define ERROR_Y "-y option only accepts integer values between 10 and 30\n"
    #define ERROR_F "-f option only accepts integer values between 2 and 10000\n"
    #define ERROR_C "-c option only accepts integer values greater or equal to 1\n"

    #define SIZE_PARAM  2

    typedef struct team_t {
        char *name;
        unsigned int nbr_client;
        unsigned int nbr_clientMax;
        TAILQ_ENTRY(team_t) next_team;
    } team_t;

    typedef struct params_s {
        unsigned int port;
        unsigned int width;
        unsigned int height;
        unsigned int clients_nb;
        unsigned int freq;
        TAILQ_HEAD(team_list, team_t) team;
    } params_t;

    typedef bool (*fct_ptr)(params_t *, char **);

    typedef struct fct_ptr_s {
        char name[SIZE_PARAM];
        fct_ptr fct;
    } fct_ptr_t;

bool get_params(int ac, char **av, params_t *params);
bool is_number(const char *str);
void insert_team_name(params_t *params, char *name);

bool get_port(params_t *params, char **av);
bool get_width(params_t *params, char **av);
bool get_height(params_t *params, char **av);
bool get_name(params_t *params, char **av);
bool get_client_nb(params_t *params, char **av);
bool get_freq(params_t *params, char **av);

#endif /* !PARAMS_H_ */
