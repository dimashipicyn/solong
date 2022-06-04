#include "bullet.h"
#include "keys.h"
#include "texture.h"
#include "tank.h"
#include "libft.h"

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
    if (bullet->dir == FORW) {
        bullet->pos.y -= bullet->velocity;
        bullet->sprite.src.x = 0;
    }
    if (bullet->dir == BACK) {
        bullet->pos.y += bullet->velocity;
        bullet->sprite.src.x = 64;
    }
    if (bullet->dir == LEFT) {
        bullet->pos.x -= bullet->velocity;
        bullet->sprite.src.x = 32;
    }
    if (bullet->dir == RIGHT) {
        bullet->pos.x += bullet->velocity;
        bullet->sprite.src.x = 96;
    }

    if (bullet->pos.x < -32 || bullet->pos.x > 1000 || bullet->pos.y < -32 || bullet->pos.y > 1000) {
        bullet->owner->is_fired = 0;
        ft_list_remove_if(&entities, bullet, cmp);
    }
}

static void draw(t_bullet* bullet, t_graphics* graphics, int32_t elapsed)
{
    t_sprite s = bullet->sprite;
    s.dest.x = bullet->pos.x;
    s.dest.y = bullet->pos.y;

    draw_sprite_to_frame(graphics, s);
}

static t_game_object interface = {
    .input = input,
    .update = update,
    .render = draw
};

t_bullet* new_bullet(t_point pos, t_direction dir, float velocity, t_tank* owner)
{
    t_bullet* bullet = calloc(1, sizeof(t_bullet));

    bullet->interface = &interface;
    bullet->dir = dir;
    bullet->pos = pos;
    bullet->velocity = velocity;
    bullet->owner = owner;

    bullet->sprite.texture = get_texture(TANK);
    bullet->sprite.dest = (t_rect){pos.x, pos.y, 16, 16};
    bullet->sprite.src = (t_rect){0, 0, 16, 16};

    return bullet;
}

void free_bullet(t_bullet* bullet)
{
    free(bullet);
}