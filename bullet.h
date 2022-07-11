#ifndef BULLET_H
#define BULLET_H

#include "vector.h"
#include "entity.h"
#include "graphics.h"
#include "physics.h"
#include "animation.h"

typedef struct s_tank t_tank;

typedef struct bullet {
    t_entity_methods*  methods;
    t_physic_body*  body;
    t_tank*         owner;
    t_animation     anim;
    int             state;
    int8_t          is_alive;
} t_bullet;

t_entity* new_bullet(t_vec2 pos, t_vec2 dir, float velocity, t_tank* owner);
void free_bullet(t_bullet* bullet);

#endif
