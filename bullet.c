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

static void input(t_bullet* bullet, t_keys keys)
{
    
}

static void update(t_bullet* bullet)
{
    t_vec2 dir = bullet->body->dir;
    t_vec2 pos = bullet->body->body.a;

    if (dir.y == -1) {
        bullet->sprite.src.x = 0;
    }
    if (dir.y == 1) {
        bullet->sprite.src.x = 64;
    }
    if (dir.x == -1) {
        bullet->sprite.src.x = 32;
    }
    if (dir.x == 1) {
        bullet->sprite.src.x = 96;
    }

    char contact = bullet->body->contact;

    if (contact || pos.x < -32 || pos.x > 1000 || pos.y < -32 || pos.y > 1000) {
        set_empty_terrain(bullet->body->contacted_body->user_data);
        free_bullet(bullet);
        ft_list_remove_if(&entities, bullet, cmp);
    }
}

static void draw(t_bullet* bullet, t_graphics* graphics, int32_t elapsed)
{
    t_sprite s = bullet->sprite;
    s.dest.x = bullet->body->body.a.x;
    s.dest.y = bullet->body->body.a.y;

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
        .size = vec2(6,6),
        .dir = dir,
        .velocity = velocity,
        .is_dynamic = 1
    };
    t_physic_body* body = create_physic_body(def);
    body->stop_on_contact = 0;

    bullet->interface = &interface;
    bullet->owner = owner;
    bullet->body = body;

    bullet->sprite.texture = get_texture(TANK);
    bullet->sprite.dest = (t_rect){pos.x, pos.y, 6, 6};
    bullet->sprite.src = (t_rect){0, 0, 16, 16};

    return bullet;
}

void free_bullet(t_bullet* bullet)
{
    free_physic_body(bullet->body);
    free(bullet);
}