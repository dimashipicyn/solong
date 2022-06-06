#include "physics.h"

#include <stdlib.h>

static t_physic_world physic_world = {};

static int cmp(void* t, void* p)
{
    if (t == p) {
        return 0;
    }
    return 1;
}

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

void update_physic_world()
{
    t_physic_world *w = &physic_world;

    for (t_list* it1 = w->bodies; it1 != NULL; it1 = it1->next)
    {
        t_physic_body temp_body = *(t_physic_body*)it1->content;
        if (temp_body.velocity == 0) {
            continue;
        }

        temp_body.body.a = vec2_add(temp_body.body.a, vec2_scalar_num(temp_body.dir, temp_body.velocity));

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

        if (!is_detect_collision || !temp_body.stop_on_contact) {
            *(t_physic_body*)it1->content = temp_body;
            ((t_physic_body*)it1->content)->contact = is_detect_collision;
        }
    }
}

t_physic_body* new_physic_body(t_vec2 pos, t_vec2 size, float velocity, t_vec2 dir)
{
    t_physic_body* b = calloc(1, sizeof(t_physic_body));

    b->body = (t_body_rect){pos, size};
    b->velocity = velocity;
    b->dir = dir;
    b->stop_on_contact = 1;
    b->contact = 0;

    ft_list_push_back(&physic_world.bodies, b);

    return b;
}

void free_physic_body(t_physic_body* b)
{
    ft_list_remove_if(&physic_world.bodies, b, cmp);
    free(b);
}