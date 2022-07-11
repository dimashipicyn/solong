#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>

#include "entity.h"
#include "vector.h"
#include "texture.h"
#include "graphics.h"
#include "physics.h"
#include "animation.h"

enum {
    TANK_ANIMATION,
    ARMOR_ANIMATION,
    TOTAL_ANIMATIONS
};

typedef struct s_tank
{
    t_entity_methods *methods;
    t_physic_body   *body;
    t_animation     anim[TOTAL_ANIMATIONS];
    int64_t         last_fire_time;
    int64_t         birth_date;
    int32_t         animations;
    int8_t          xp;
    int8_t          armor;
    int8_t          is_alive;
} t_tank;

t_entity* new_tank(t_physic_body* body);
void delete_tank(t_tank* tank);

#endif
