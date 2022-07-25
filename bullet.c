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
	(void)entity;
	(void)game_ctx;
}

static void update(t_entity* entity, t_game_ctx* game_ctx)
{
    t_bullet* bullet = (t_bullet*)entity;

    switch (bullet->state) {
        case RUN: {
            char contact = bullet->body->contact;

            if (contact)
            {
				t_entity* contacted_entity = bullet->body->contacted_body->owner;

                t_sprite sprite = {
                    .texture = get_texture(EFFECTS_TXR_ID),
                    .src = {vec2(32,0),vec2(16,16)},
                    .dest = {vec2(0,0),vec2(32,32)}
                };
                bullet->anim = animation(sprite, 3, 300, 0, 1);
                bullet->state = EXPLOSION;


				entity_damage(contacted_entity, game_ctx, bullet->damage);
            }
            break;
        }
        case EXPLOSION: {
            if (bullet->anim.is_end) {
                bullet->state = END;
            }
            break;   
        }
        case END: {
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
	s.dest.pos = vec2_sub(bullet->body->rect.pos, vec2(s.dest.size.x / 2, s.dest.size.y / 2));
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

static void bullet_damage(t_entity* entity, t_game_ctx* game_ctx, int32_t damage)
{
	(void)entity;
	(void)game_ctx;
	(void)damage;
}

static t_entity_methods methods = {
    .input = input,
    .update = update,
    .render = draw,
	.damage = bullet_damage,
    .is_alive = is_alive,
    .free = bullet_free
};

t_entity* new_bullet(t_bullet_def def)
{
    t_bullet* bullet = calloc(1, sizeof(t_bullet));

	bullet->methods = &methods;

    t_physic_body_def body_def = {
        .pos = def.pos,
        .size = vec2(2,2),
        .dir = def.dir,
        .velocity = def.velocity,
        .is_dynamic = 1,
        .layer = PHYSICS_LAYER_1
    };
    t_physic_body* body = create_physic_body(body_def);
	body->stop_on_contact = 0;
	body->owner = bullet;

	bullet->body = body;

    bullet->owner = def.owner;
	bullet->damage = def.damage;
    bullet->is_alive = 1;

    t_sprite sprite;
    sprite.texture = get_texture(BULLET_TXR_ID);
    sprite.dest = (t_rect){def.pos, vec2(6,6)};
    sprite.src = (t_rect){vec2(0,0), vec2(4,4)};
    
    if (def.dir.y == -1)
    {
        sprite.src.pos.x = 0;
    }
    if (def.dir.y == 1)
    {
        sprite.src.pos.x = 8;
    }
    if (def.dir.x == -1)
    {
        sprite.src.pos.x = 4;
    }
    if (def.dir.x == 1)
    {
        sprite.src.pos.x = 12;
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
