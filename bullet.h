#ifndef BULLET_H
#define BULLET_H

#include "vector.h"
#include "entity.h"
#include "graphics.h"
#include "physics.h"
#include "animation.h"

typedef struct s_tank t_tank;

typedef struct s_bullet_def
{
	void*	owner;
	t_vec2	pos;
	t_vec2	dir;
	float	velocity;
	int8_t	damage;
} t_bullet_def;

typedef struct bullet {
    t_entity_methods*  methods;
    t_physic_body*  body;
    t_tank*         owner;
    t_animation     anim;
    int             state;
    int8_t          is_alive;
	int8_t			damage;
} t_bullet;

t_entity* new_bullet(t_bullet_def def);
void free_bullet(t_bullet* bullet);

#endif
