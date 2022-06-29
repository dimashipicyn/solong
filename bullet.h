#ifndef BULLET_H
#define BULLET_H

#include "vector.h"
#include "game_object.h"
#include "graphics.h"
#include "physics.h"

typedef struct s_tank t_tank;

typedef struct bullet {
    t_game_object*  interface;
    t_physic_body*  body;
    t_tank*         owner;
    t_animation     anim;
    int             state;
} t_bullet;

t_bullet* new_bullet(t_vec2 pos, t_vec2 dir, float velocity, t_tank* owner);
void free_bullet(t_bullet* bullet);

#endif