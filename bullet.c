#include "bullet.h"
#include "keys.h"
#include "texture.h"
#include "tank.h"
#include "libft.h"
#include "game_map.h"

#include <stdlib.h>

extern t_list* entities;

static int cmp(void* t, void* p)
{
    if (t == p) {
        return 0;
    }
    return 1;
}

typedef enum s_state {
    RUN,
    EXPLOSION,
    END
} t_state;

static void input(t_bullet* bullet, t_keys keys)
{
    
}

static void update(t_bullet* bullet)
{
    t_vec2 dir = bullet->body->dir;
    t_vec2 pos = bullet->body->body.a;

    switch (bullet->state) {
        case RUN: {
            char contact = bullet->body->contact;

            if (contact)
            {
                t_sprite sprite = {
                    .texture = get_texture(EFFECTS_TXR_ID),
                    .src = {32,0,16,16},
                    .dest = {0,0,32,32}
                };
                bullet->anim = animation(sprite, 3, 300, 0);
                bullet->state = EXPLOSION;
            }
            break;
        }
        case EXPLOSION: {
            if (bullet->anim.is_end) {
                bullet->state = END;
                bullet->anim.nframes = 0;
            }
            break;   
        }
        case END: {
            destroy_terrain(bullet->body->contacted_body->user_data);
            free_bullet(bullet);
            ft_list_remove_if(&entities, bullet, cmp);
            break;
        }
    }
}

static void draw(t_bullet* bullet, t_graphics* graphics, int32_t elapsed)
{
    update_animation(&bullet->anim, elapsed);

    t_sprite s = get_animation_sprite(&bullet->anim);
    s.dest.x = bullet->body->body.a.x - s.dest.width / 2;
    s.dest.y = bullet->body->body.a.y - s.dest.height / 2;

    draw_sprite_to_frame(graphics, s);
}

static t_game_object interface = {
    .input = input,
    .update = update,
    .render = draw
};

t_bullet* new_bullet(t_vec2 pos, t_vec2 dir, float velocity, t_tank* owner)
{
    t_bullet* bullet = calloc(1, sizeof(t_bullet));

    t_physic_body_def def = {
        .pos = pos,
        .size = vec2(4,4),
        .dir = dir,
        .velocity = velocity,
        .is_dynamic = 1
    };
    t_physic_body* body = create_physic_body(def);
    body->stop_on_contact = 0;

    bullet->interface = &interface;
    bullet->owner = owner;
    bullet->body = body;

    t_sprite sprite;
    sprite.texture = get_texture(BULLET_TXR_ID);
    sprite.dest = (t_rect){pos.x, pos.y, 6, 6};
    sprite.src = (t_rect){0, 0, 4, 4};
    
    if (dir.y == -1)
    {
        sprite.src.x = 0;
    }
    if (dir.y == 1)
    {
        sprite.src.x = 8;
    }
    if (dir.x == -1)
    {
        sprite.src.x = 4;
    }
    if (dir.x == 1)
    {
        sprite.src.x = 12;
    }

    bullet->anim = (t_animation) {
        .duration = 1,
        .nframes = 1,
        .sprite = sprite,
        .repeat = 1
    };

    return bullet;
}

void free_bullet(t_bullet* bullet)
{
    free_physic_body(bullet->body);
    free(bullet);
}
