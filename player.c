#include "player.h"
#include "keys.h"
#include "graphics.h"
#include "libft.h"

typedef struct s_player_state {
    t_animation animation;
} t_player_state;

static t_player_state idle = {
    .animation = (t_animation){
        .duration = 500,
        .nframes = 6
    }
};

static t_player_state run = {
    .animation = (t_animation){
        .duration = 500,
        .nframes = 6
    }
};

void input_player(t_player* player, t_keys keys)
{
    float x = 0;
    float y = 0;
    if (keys.forward) {
        y -= 0.5;
    }
    if (keys.backward) {
        y += 0.5;
    }
    if (keys.left_move) {
        x -= 0.5;
    }
    if (keys.right_move) {
        x += 0.5;
    }
    if (x || y) {
        player->position.x += x;
        player->position.y += y;
        player->state = &run;
    }
    else {
        player->state = &idle;
    }
}

void update_player(t_player* player)
{
    player->state->animation.sprite.dest.x = player->position.x;
    player->state->animation.sprite.dest.y = player->position.y;
    // do_something
}

void render_player(t_player* player, t_graphics* graphics, int32_t elapsed)
{
    update_animation(&player->state->animation, elapsed);
    draw_sprite_to_frame(graphics, player->state->animation.sprite);
}

static t_game_object interface = {
    .input = input_player,
    .update = update_player,
    .render = render_player
};

void init_player(t_player* player, t_point pos, t_point dir)
{
    player->interface = &interface;
    player->position = pos;
    player->direction = dir;
    player->state = &idle;
    
    t_texture* idle_texture = get_texture(KNIGHT_IDLE);
    t_texture* run_texture = get_texture(KNIGHT_RUN);
    
    t_sprite idle_sprite = {
        .texture = idle_texture,
        .dest = {pos.x,pos.y,32,32},
        .src = {0,0,idle_texture->width/6, idle_texture->height}
    };
    idle.animation.sprite = idle_sprite;

    t_sprite run_sprite = {
        .texture = run_texture,
        .dest = {pos.x,pos.y,32,32},
        .src = {0,0,run_texture->width/6, run_texture->height}
    };
    run.animation.sprite = run_sprite;
}

t_player* new_player(t_point pos, t_point dir)
{
    t_player* player = ft_calloc(1, sizeof(t_player));
    init_player(player, pos, dir);
    return player;
}

void delete_player(t_player* player)
{
    free(player);
}