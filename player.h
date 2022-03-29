#ifndef PLAYER_H
#define PLAYER_H

#include "game_object.h"
#include "vector.h"
#include "texture.h"
#include "graphics.h"

typedef struct s_player_state t_player_state;

typedef struct s_player
{
    t_game_object   *interface;
    t_point         position;
    t_point         direction;
    unsigned int    counter;
    t_player_state  *state;
} t_player;

t_player* new_player(t_point pos, t_point dir);
void delete_player(t_player* player);

#endif