#ifndef PLAYER_H
#define PLAYER_H

#include "game_object.h"
#include "vector.h"
#include "texture.h"
#include "graphics.h"
#include "physics.h"

typedef struct s_tank
{
    t_game_object   *interface;
    t_physic_body   *body;
    t_animation     anim;
    int             is_fired;
} t_tank;

t_tank* new_player(t_physic_body* body);
void delete_player(t_tank* tank);

#endif