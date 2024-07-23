/*
** EPITECH PROJECT, 2022
** Project zappy
** File description:
** sound.c
*/

#include "server.h"
#include "utils.h"

static unsigned int direction_players(const client_t *orig,
const client_t *reception)
{
    if (orig->player->direction - reception->player->direction == 2 ||
    reception->player->direction - orig->player->direction == 2)
        return 0;
    if (reception->player->direction == orig->player->direction + 1 ||
    reception->player->direction == NORTH && orig->player->direction == WEST)
        return 3;
    if (reception->player->direction == orig->player->direction - 1 ||
    reception->player->direction == WEST && orig->player->direction == NORTH)
        return 1;
    return 2;
}

static bool get_distance(const client_t *orig, const client_t *reception,
const unsigned int width, const unsigned int height)
{
    return distance(orig->player->x, orig->player->y,
    reception->player->x, reception->player->y) > (width / 2 + height / 2);
}

static unsigned int diagonals(const client_t *orig, const client_t *rec,
const unsigned int size[2], int *tab_dir)
{
    if (rec->player->x > orig->player->x && rec->player->y < orig->player->y) {
        if (get_distance(orig, rec, size[0], size[1]))
            return tab_dir[7];
        return tab_dir[3];
    }
    if (rec->player->x < orig->player->x && rec->player->y < orig->player->y) {
        if (get_distance(orig, rec, size[0], size[1]))
            return tab_dir[5];
        return tab_dir[1];
    }
    if (rec->player->x < orig->player->x && rec->player->y > orig->player->y) {
        if (get_distance(orig, rec, size[0], size[1]))
            return tab_dir[3];
        return tab_dir[7];
    }
    if (get_distance(orig, rec, size[0], size[1]))
        return tab_dir[1];
    return tab_dir[5];
}

static void update_id_direction(int *tab, const int increment)
{
    for (int j = 0; j != increment; ++j)
        for (int i = 0; i != 8; ++i) {
            tab[i] += 2;
            if (tab[i] > 8)
                tab[i] = 1;
        }
}

unsigned int get_sound_direction(const client_t *orig,
const client_t *reception, const unsigned int width, const unsigned int height)
{
    int tab_dir[8] = {1, 2, 3, 4, 5, 6, 7, 8};

    update_id_direction(tab_dir, direction_players(orig, reception));
    if (orig->player->x == reception->player->x &&
    orig->player->y == reception->player->y)
        return 0;
    if (orig->player->x == reception->player->x) {
        if (orig->player->y - reception->player->y > height / 2)
            return tab_dir[6];
        return tab_dir[2];
    }
    if (orig->player->y == reception->player->y) {
        if (orig->player->x - reception->player->x > width / 2)
            return tab_dir[4];
        return tab_dir[0];
    }
    return diagonals(orig, reception, (int[2]){height, width}, tab_dir);
}
