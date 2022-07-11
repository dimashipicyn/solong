#include "bullet.h"
#include "keys.h"
#include "texture.h"
#include "tank.h"
#include "libft.h"
#include "game_map.h"
#include "scene.h"
#include "game.h"

#include <stdlib.h>

typedef enum s_state {
    RUN,
    EXPLOSION,
    END
} t_state;

static void input(t_entity* entity, t_game_ctx* game_ctx)
{
    
}

static void update(t_entity* entity, t_game_ctx* game_ctx)
{
    t_bullet* bullet = (t_bullet*)entity;
    
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
            t_entity* contacted_entity = bullet->body->contacted_body->user_data;
            entity_damage(contacted_entity, game_ctx, 100);
            bullet->is_alive = 0;
            break;
        }
    }
}

static void draw(t_entity* entity, t_game_ctx* game_ctx)
{
    t_bullet* bullet = (t_bullet*)entity;
    
    update_animation(&bullet->anim, game_ctx->elapsed);

    t_sprite s = get_animation_sprite(&bullet->anim);
    s.dest.x = bullet->body->body.a.x - s.dest.width / 2;
    s.dest.y = bullet->body->body.a.y - s.dest.height / 2;

    draw_sprite_to_frame(game_ctx->graphics, s);
}

static int is_alive(t_entity* entity)
{
    t_bullet* bullet = (t_bullet*)entity;
    return bullet->is_alive;
}

static void bullet_free(t_entity* entity)
{
    t_bullet* bullet = (t_bullet*)entity;
    free_bullet(bullet);
}

static t_entity_methods methods = {
    .input = input,
    .update = update,
    .render = draw,
    .is_alive = is_alive,
    .free = bullet_free
};

t_entity* new_bullet(t_vec2 pos, t_vec2 dir, float velocity, t_tank* owner)
{
    t_bullet* bullet = calloc(1, sizeof(t_bullet));

    t_physic_body_def def = {
        .pos = pos,
        .size = vec2(4,4),
        .dir = dir,
        .velocity = velocity,
        .is_dynamic = 1,
        .layer = PHYSICS_LAYER_1
    };
    t_physic_body* body = create_physic_body(def);
    body->stop_on_contact = 0;

    bullet->methods = &methods;
    bullet->owner = owner;
    bullet->body = body;
    bullet->is_alive = 1;

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

    return (t_entity*)bullet;
}

void free_bullet(t_bullet* bullet)
{
    free_physic_body(bullet->body);
    free(bullet);
}
