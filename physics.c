#include "physics.h"

#include <stdlib.h>

static int intersect(t_physic_body* lhs, t_physic_body* rhs)
{
    float ax = lhs->body.a.x;
    float ay = lhs->body.a.y;
    float ax1 = lhs->body.b.x + ax;
    float ay1 = lhs->body.b.y + ay;

    float bx = rhs->body.a.x;
    float by = rhs->body.a.y;
    float bx1 = rhs->body.b.x + bx;
    float by1 = rhs->body.b.y + by;

    return !(bx > ax1 || 
           bx1 < ax || 
           by > ay1 ||
           by1 < ay);
}

t_physic_world* new_physic_world()
{
    t_physic_world* w = calloc(1, sizeof(t_physic_world));
    w->bodies = NULL;

    return w;
}

void free_physic_world(t_physic_world* w)
{
    ft_list_foreach(w->bodies, free_physic_body);
    ft_list_clear(&w->bodies);
    free(w);
}

void add_body(t_physic_world* w, t_physic_body* b)
{
    ft_list_push_back(&w->bodies, b);
}

static int update_body(t_physic_body* b)
{
    float velocity = b->velocity;
    switch (b->dir) {
        case FORW: {
            b->body.a.y -= velocity;
            return 1;
        }
        case BACK: {
            b->body.a.y += velocity;
            return 1;
        }
        case LEFT: {
            b->body.a.x -= velocity;
            return 1;
        }
        case RIGHT: {
            b->body.a.x += velocity;
            return 1;
        }
    }
    return 0;
}

void update_physic_world(t_physic_world* w)
{
    for (t_list* it1 = w->bodies; it1 != NULL; it1 = it1->next)
    {
        t_physic_body temp_body = *(t_physic_body*)it1->content;
        if (update_body(&temp_body) == 0) {
            continue;
        }

        int is_detect_collision = 0;
        for (t_list* it2 = w->bodies; it2 != NULL; it2 = it2->next) {
            if (it1->content == it2->content) {
                continue;
            }
            if (intersect(&temp_body, it2->content)) {
                is_detect_collision = 1;
                break;
            }
        }

        if (!is_detect_collision) {
            *(t_physic_body*)it1->content = temp_body;
        }
    }
}

t_physic_body* new_physic_body(t_vector body, float velocity, t_direction dir)
{
    t_physic_body* b = calloc(1, sizeof(t_physic_body));

    b->body = body;
    b->velocity = velocity;
    b->dir = dir;

    return b;
}

void free_physic_body(t_physic_body* b)
{
    free(b);
}