#ifndef PLAYER_H
#define PLAYER_H

#include "game_object.h"
#include "vector.h"
#include "texture.h"

typedef struct s_player
{
    t_game_object   interface;
    enum TEXTURE_ID id;
    t_point         position;
    t_point         direction;
} t_player;

t_player* new_player(t_point pos, t_point dir);
void delete_player(t_player* player);

#endif