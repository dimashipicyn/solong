#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>

#include "game_object.h"
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
    t_game_object   *interface;
    t_physic_body   *body;
    t_animation     anim[TOTAL_ANIMATIONS];
    int64_t         last_fire_time;
    int64_t         birth_date;
    int32_t         animations;
} t_tank;

t_tank* new_player(t_physic_body* body);
void delete_player(t_tank* tank);

#endif
