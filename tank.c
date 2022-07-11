#include "tank.h"
#include "keys.h"
#include "graphics.h"
#include "libft.h"
#include "bullet.h"
#include "utils.h"
#include "entity.h"
#include "game.h"

static void fire(t_tank* tank, t_game_ctx* game_ctx)
{
    int64_t diff_time = get_time() - tank->last_fire_time;
    if (diff_time >= 500 * 1) {
        t_vec2 bullet_pos = vec2(tank->body->body.a.x + 12, tank->body->body.a.y + 12);
        t_vec2 pos = vec2_add(bullet_pos, vec2_scalar_num(tank->body->dir, 17));
        scene_add_entity(game_ctx->active_scene, new_bullet(pos, tank->body->dir, 1, tank));

        tank->last_fire_time = get_time();
    }
}

static void input_tank(t_entity* entity, t_game_ctx* game_ctx)
{
    t_tank* tank = (t_tank*)entity;
    
    float velocity = 0;
    t_vec2 dir = tank->body->dir;
    
    t_keys keys = game_ctx->keys;
    if (keys.forward) {
        velocity = 0.5;
        dir = vec2(0, -1);
    }
    else if (keys.backward) {
        velocity = 0.5;
        dir = vec2(0, 1);
    }
    else if (keys.left_move) {
        velocity = 0.5;
        dir = vec2(-1, 0);
    }
    else if (keys.right_move) {
        velocity = 0.5;
        dir = vec2(1, 0);
    }
    
    tank->body->velocity = velocity;
    tank->body->dir = dir;

    if (keys.left) {
        fire(tank, game_ctx);
    }
    
    if ((get_time() - tank->birth_date) >= 3000)
    {
        tank->animations = 1;
    }
}

static void update_tank(t_entity* entity, t_game_ctx* game_ctx)
{
    t_tank* tank = (t_tank*)entity;
    
    t_vec2 dir = tank->body->dir;
    if (dir.y == -1) {
        tank->anim[0].sprite.src.x = 0;
    }
    else if (dir.y == 1) {
        tank->anim[0].sprite.src.x = 64;
    }
    else if (dir.x == -1) {
        tank->anim[0].sprite.src.x = 32;
    }
    if (dir.x == 1) {
        tank->anim[0].sprite.src.x = 96;
    }

    if (tank->body->velocity > 0.1) {
        tank->anim[0].nframes = 2;
    }
    else {
        tank->anim[0].nframes = 1;
    }
}

static void render_tank(t_entity* entity, t_game_ctx* game_ctx)
{
    t_tank* tank = (t_tank*)entity;
    
    update_animation(&tank->anim[0], game_ctx->elapsed);
    update_animation(&tank->anim[1], game_ctx->elapsed);

    for (int i = 0; i < tank->animations; i++) {
        t_sprite s = get_animation_sprite(&tank->anim[i]);
        s.dest.x = tank->body->body.a.x - 2;
        s.dest.y = tank->body->body.a.y - 2;
        
        draw_sprite_to_frame(game_ctx->graphics, s);
    }
}

static void damage(t_entity* entity, t_game_ctx* game_ctx, int32_t damage)
{
    t_tank* tank = (t_tank*)entity;
    
    if (!tank->armor) {
        tank->xp -= damage;
    }
    if (tank->xp <= 0) {
        tank->is_alive = 0;
    }
}

static int is_alive(t_entity* entity)
{
    t_tank* tank = (t_tank*)entity;
    return tank->is_alive;
}

static t_entity_methods methods = {
    .input = input_tank,
    .update = update_tank,
    .render = render_tank,
    .damage = damage,
    .is_alive = is_alive,
    .free = delete_tank
};

void init_tank(t_tank* tank, t_physic_body* body)
{
    tank->methods = &methods;
    tank->body = body;

    t_vec2 pos = body->body.a;
    
    t_sprite tank_sprite = (t_sprite){
        .dest = (t_rect){pos.x,pos.y,32,32},
        .src = (t_rect){0,0,16,16},
        .texture = get_texture(TANK_RED_TXR_ID)
    };
    
    t_sprite armor = (t_sprite){
        .dest = (t_rect){pos.x,pos.y,32,32},
        .src = (t_rect){0,0,16,16},
        .texture = get_texture(EFFECTS_TXR_ID)
    };
    
    tank->anim[TANK_ANIMATION] = animation(tank_sprite, 1, 200, 1);
    tank->anim[ARMOR_ANIMATION] = animation(armor, 2, 50, 1);
    tank->animations = 2;
    
    tank->birth_date = get_time();
    tank->is_alive = 1;
    tank->armor = 1;
    tank->xp = 100;
}

t_entity* new_tank(t_physic_body* body)
{
    t_tank* tank = ft_calloc(1, sizeof(t_tank));
    init_tank(tank, body);
    return (t_entity*)tank;
}

void delete_tank(t_tank* player)
{
    free_physic_body(player->body);
    free(player);
}
