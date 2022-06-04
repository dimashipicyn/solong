#ifndef PHYSICS_H
#define PHYSICS_H

#include "libft.h"
#include "vector.h"

typedef enum s_direction {
    LEFT,
    RIGHT,
    FORW,
    BACK
} t_direction;

typedef struct s_physic_body
{
    t_direction dir;
    float velocity;
    t_vector body;
} t_physic_body;

typedef struct s_physic_world
{
    t_list* bodies;
} t_physic_world;

t_physic_world* new_physic_world();
void free_physic_world(t_physic_world* w);
void update_physic_world(t_physic_world* w);
void add_body(t_physic_world* w, t_physic_body* b);

t_physic_body* new_physic_body(t_vector body, float velocity, t_direction dir);
void free_physic_body(t_physic_body* b);

#endif