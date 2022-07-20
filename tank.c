#include "tank.h"
#include "keys.h"
#include "graphics.h"
#include "libft.h"
#include "bullet.h"
#include "utils.h"
#include "entity.h"
#include "game.h"
#include "command.h"

#include <assert.h>

enum tank_state {
	TANK_SPAWN_STATE,
	TANK_RUNNING_STATE
};

static void input(t_entity* entity, t_game_ctx* game_ctx);
static void update(t_entity* entity, t_game_ctx* game_ctx);
static void render(t_entity* entity, t_game_ctx* game_ctx);
static void damage(t_entity* entity, t_game_ctx* game_ctx, int32_t damage);
static int is_alive(t_entity* entity);
static void delete(t_entity* entity);

static t_entity_methods methods = {
    .input = input,
    .update = update,
    .render = render,
    .damage = damage,
    .is_alive = is_alive,
    .free = delete
};

static void fire(t_tank* tank, t_game_ctx* game_ctx);

static void move_left_command(t_entity* entity, t_game_ctx* game_ctx)
{
	(void)game_ctx;
    t_tank* tank = (t_tank*)entity;
    
    tank->body->velocity = tank->velocity;
    tank->body->dir = vec2(-1, 0);
}

static void move_right_command(t_entity* entity, t_game_ctx* game_ctx)
{
	(void)game_ctx;
    t_tank* tank = (t_tank*)entity;
    
    tank->body->velocity = tank->velocity;
    tank->body->dir = vec2(1, 0);
}

static void move_forw_command(t_entity* entity, t_game_ctx* game_ctx)
{
	(void)game_ctx;
    t_tank* tank = (t_tank*)entity;
    
    tank->body->velocity = tank->velocity;
    tank->body->dir = vec2(0, -1);
}

static void move_back_command(t_entity* entity, t_game_ctx* game_ctx)
{
	(void)game_ctx;
    t_tank* tank = (t_tank*)entity;
    
    tank->body->velocity = tank->velocity;
    tank->body->dir = vec2(0, 1);
}

static void fire_command(t_entity* entity, t_game_ctx* game_ctx)
{
    t_tank* tank = (t_tank*)entity;

	fire(tank, game_ctx);
}

static void stop_command(t_entity* entity, t_game_ctx* game_ctx)
{
	(void)game_ctx;
    t_tank* tank = (t_tank*)entity;
    
    tank->body->velocity = 0;
}

static t_command player_one_input(t_entity* entity, t_game_ctx* game_ctx)
{
	(void)entity;

    t_keys keys = game_ctx->keys;
    if (keys.pressed[K_CODE_W]) {
        return command(move_forw_command);
    }
    else if (keys.pressed[K_CODE_S]) {
        return command(move_back_command);
    }
    else if (keys.pressed[K_CODE_A]) {
        return command(move_left_command);
    }
    else if (keys.pressed[K_CODE_D]) {
        return command(move_right_command);
    }
	else if (keys.pressed[K_CODE_F]) {
        return command(fire_command);
    }
    return command(stop_command);
}

static t_command player_two_input(t_entity* entity, t_game_ctx* game_ctx)
{
	(void)entity;

    t_keys keys = game_ctx->keys;
    if (keys.pressed[K_CODE_TOP]) {
        return command(move_forw_command);
    }
    else if (keys.pressed[K_CODE_BOTTOM]) {
        return command(move_back_command);
    }
    else if (keys.pressed[K_CODE_LEFT]) {
        return command(move_left_command);
    }
    else if (keys.pressed[K_CODE_RIGHT]) {
        return command(move_right_command);
    }
	else if (keys.pressed[K_CODE_ENTER]) {
        return command(fire_command);
    }
    return command(stop_command);
}

static t_command rand_command()
{
	int n = abs(rand()) % 6;
    switch (n) {
        case 0:
            return command(move_forw_command);
        case 1:
            return command(move_back_command);
        case 2:
            return command(move_left_command);
        case 3:
            return command(move_right_command);
        case 4:
            return command(fire_command);
        default:
            break;
    }
    return command(NULL);
}

static t_command ii_input(t_entity* entity, t_game_ctx* game_ctx)
{
	(void)game_ctx;
	t_tank* tank = (t_tank*)entity;
	if (tank->body->velocity == 0) {
		return rand_command();
	}
	int r = abs(rand()) % 100;
	if (r < 99) {
		return command(NULL);
	}
	return command(fire_command);
}

void fire(t_tank* tank, t_game_ctx* game_ctx)
{
    int64_t diff_time = get_time() - tank->last_fire_time;
    if (diff_time >= tank->recharge_time) {
        t_vec2 bullet_pos = vec2(tank->body->body.a.x + 14, tank->body->body.a.y + 14);
        t_vec2 pos = vec2_add(bullet_pos, vec2_scalar_num(tank->body->dir, 18));
        scene_add_entity(game_ctx->active_scene, new_bullet(pos, tank->body->dir, 1, tank));

        tank->last_fire_time = get_time();
    }
}

void input(t_entity* entity, t_game_ctx* game_ctx)
{
    t_tank* tank = (t_tank*)entity;
    
    t_command cmd = tank->input(entity, game_ctx);
    command_execute(cmd, entity, game_ctx);
}

void update(t_entity* entity, t_game_ctx* game_ctx)
{
	(void)game_ctx;
    t_tank* tank = (t_tank*)entity;
    
    t_vec2 dir = tank->body->dir;
    if (dir.y == -1) {
        tank->anim[TANK_ANIMATION].sprite.src.x = 0;
    }
    else if (dir.y == 1) {
        tank->anim[TANK_ANIMATION].sprite.src.x = 64;
    }
    else if (dir.x == -1) {
        tank->anim[TANK_ANIMATION].sprite.src.x = 32;
    }
    if (dir.x == 1) {
        tank->anim[TANK_ANIMATION].sprite.src.x = 96;
    }

    if (tank->body->velocity > 0.1) {
        tank->anim[TANK_ANIMATION].nframes = 2;
    }
    else {
        tank->anim[TANK_ANIMATION].nframes = 1;
    }
	if (tank->anim[TANK_SPAWN_ANIMATION].is_end) {
		tank->state = TANK_RUNNING_STATE;
	}
    if ((get_time() - tank->birth_date) >= 10000)
    {
        tank->armor = 0;
        tank->active_animations = 2;
    }
}

void render(t_entity* entity, t_game_ctx* game_ctx)
{
    t_tank* tank = (t_tank*)entity;

	if (tank->state == TANK_SPAWN_STATE) {
		update_animation(&tank->anim[TANK_SPAWN_ANIMATION], game_ctx->elapsed);
		t_sprite s = get_animation_sprite(&tank->anim[TANK_SPAWN_ANIMATION]);
        s.dest.x = tank->body->body.a.x - 2;
        s.dest.y = tank->body->body.a.y - 2;

        draw_sprite_to_frame(game_ctx->graphics, s);
	}
	else {
    for (int i = 1; i < tank->active_animations; i++) {
		update_animation(&tank->anim[i], game_ctx->elapsed);

        t_sprite s = get_animation_sprite(&tank->anim[i]);
        s.dest.x = tank->body->body.a.x - 2;
        s.dest.y = tank->body->body.a.y - 2;
        
        draw_sprite_to_frame(game_ctx->graphics, s);
    }
	}
}

void damage(t_entity* entity, t_game_ctx* game_ctx, int32_t damage)
{
	(void)game_ctx;
    t_tank* tank = (t_tank*)entity;
    
    if (!tank->armor) {
        tank->hitpoints -= damage;
    }
    if (tank->hitpoints <= 0) {
        tank->is_alive = 0;
    }
}

int is_alive(t_entity* entity)
{
    t_tank* tank = (t_tank*)entity;
    return tank->is_alive;
}

void delete(t_entity* entity)
{
	t_tank* tank = (t_tank*)entity;
	delete_tank(tank);
}

static handleInput get_input(t_tank_input_type type)
{
	switch (type) {
		case PLAYER_ONE_INPUT_TYPE:
			return player_one_input;
		case PLAYER_TWO_INPUT_TYPE:
			return player_two_input;
		case ENEMY_INPUT_TYPE:
			return ii_input;
		default:
			assert(0);
			break;
	}
	return ii_input;
}

static void init_tank(t_tank* tank, t_tank_def def)
{
    tank->methods = &methods;

	tank->hitpoints = def.hitpoints;
	tank->recharge_time = def.recharge_time;
	tank->damage = def.damage;
	tank->velocity = def.velocity;
	tank->input = get_input(def.input_type);

	t_physic_body_def body_def = {
		.pos = def.pos,
		.dir = def.dir,
		.size = vec2(28, 28),
		.layer = PHYSICS_LAYER_1 | PHYSICS_LAYER_2,
		.is_dynamic = 1,
		.user_data = tank
	};

	t_physic_body* body = create_physic_body(body_def);

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

	t_sprite spawn = (t_sprite){
        .dest = (t_rect){pos.x,pos.y,32,32},
        .src = (t_rect){0,0,16,16},
        .texture = get_texture(RESPAWN_TXR_ID)
    };
    
    tank->anim[TANK_ANIMATION] = animation(tank_sprite, 1, 200, 1);
    tank->anim[TANK_ARMOR_ANIMATION] = animation(armor, 2, 50, 1);
	tank->anim[TANK_SPAWN_ANIMATION] = animation(spawn, 4, 1000, 0);
    tank->active_animations = TANK_TOTAL_ANIMATIONS;
    
    tank->birth_date = get_time();
    tank->is_alive = 1;
    tank->armor = 1;
	tank->state = TANK_SPAWN_STATE;
}

t_tank* new_tank(t_tank_def def)
{
    t_tank* tank = ft_calloc(1, sizeof(t_tank));
    init_tank(tank, def);
    return tank;
}

void delete_tank(t_tank* tank)
{
    free_physic_body(tank->body);
    free(tank);
}
