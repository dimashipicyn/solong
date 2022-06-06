#include "tank.h"
#include "keys.h"
#include "graphics.h"
#include "libft.h"
#include "bullet.h"

extern t_list *entities;

void input_player(t_tank* player, t_keys keys)
{
    player->body->velocity = 0;
    if (keys.forward) {
        player->body->velocity = 0.5;
        player->body->dir = vec2(0, -1);
    }
    else if (keys.backward) {
        player->body->velocity = 0.5;
        player->body->dir = vec2(0, 1);
    }
    else if (keys.left_move) {
        player->body->velocity = 0.5;
        player->body->dir = vec2(-1, 0);
    }
    else if (keys.right_move) {
        player->body->velocity = 0.5;
        player->body->dir = vec2(1, 0);
    }

    if (keys.left) {
        if (!player->is_fired) {
            t_vec2 bullet_pos = vec2(player->body->body.a.x + 12, player->body->body.a.y + 12);
            t_vec2 pos = vec2_add(bullet_pos, vec2_scalar_num(player->body->dir, 18));
            ft_list_push_back(&entities, new_bullet(pos, player->body->dir, 1.5, player));
            player->is_fired = 1;
        }
    }
}

void update_player(t_tank* player)
{
    if (player->body->dir.y == -1) {
        player->anim.sprite.src.x = 0;
    }
    if (player->body->dir.y == 1) {
        player->anim.sprite.src.x = 64;
    }
    if (player->body->dir.x == -1) {
        player->anim.sprite.src.x = 32;
    }
    if (player->body->dir.x == 1) {
        player->anim.sprite.src.x = 96;
    }

    if (player->body->velocity > 0.1) {
        player->anim.nframes = 2;
    }
    else {
        player->anim.nframes = 1;
    }
}

void render_player(t_tank* player, t_graphics* graphics, int32_t elapsed)
{
    update_animation(&player->anim, elapsed);
    t_sprite s = player->anim.sprite;
    s.dest.x = player->body->body.a.x;
    s.dest.y = player->body->body.a.y;
    draw_sprite_to_frame(graphics, s);
}

static t_game_object interface = {
    .input = input_player,
    .update = update_player,
    .render = render_player
};

void init_player(t_tank* player, t_physic_body* body)
{
    player->interface = &interface;
    player->body = body;
    player->is_fired = 0;

    t_texture* texture = get_texture(TANK);

    t_vec2 pos = body->body.a;

    player->anim = (t_animation){
        .duration = 200,
        .nframes = 1,
        .sprite = (t_sprite){
            .dest = (t_rect){pos.x,pos.y,32,32},
            .src = (t_rect){0,0,16,16},
            .texture = texture
        }
    };
}

t_tank* new_player(t_physic_body* body)
{
    t_tank* player = ft_calloc(1, sizeof(t_tank));
    init_player(player, body);
    return player;
}

void delete_player(t_tank* player)
{
    free(player->body);
    free(player);
}