#ifndef PHYSICS_H
#define PHYSICS_H

#include "libft.h"
#include "vector.h"

enum {
    PHYSICS_LAYER_EMPTY = 0,
    PHYSICS_LAYER_1 = 1,
    PHYSICS_LAYER_2 = 2,
    PHYSICS_LAYER_3 = 4,
    PHYSICS_LAYER_4 = 8,
    PHYSICS_LAYER_5 = 16
};

typedef struct s_body_rect
{
    t_vec2 a;
    t_vec2 b;
} t_body_rect;

typedef struct s_physic_body t_physic_body;
typedef struct s_physic_body
{
    void*           user_data;
    t_physic_body*  contacted_body;
    t_vec2          dir;
    float           velocity;
    t_body_rect     body;
    int32_t         layer;
    char            stop_on_contact;
    char            contact;
} t_physic_body;

typedef struct s_physic_body_def
{
    void*   user_data;
    t_vec2  pos;
    t_vec2  size;
    t_vec2  dir;
    int32_t layer;
    float   velocity;
    char    is_dynamic;
} t_physic_body_def;

typedef struct s_physic_world
{
    t_list* static_bodies;
    t_list* dynamic_bodies;
} t_physic_world;

t_physic_world*     new_physic_world();
void                free_physic_world(t_physic_world* w);
void                step_physic_world();

t_physic_body*      create_physic_body(t_physic_body_def def);
void                free_physic_body(t_physic_body* b);

#endif