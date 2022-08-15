//
//  main_scene.c
//  solong
//
//  Created by Dmitry Shipicyn on 05.07.2022.
//

#include "main_scene.h"
#include "game_map.h"
#include "game.h"
#include "entity.h"
#include "physics.h"
#include "tank.h"

#include "utils.h"
#include <stdlib.h>
#include <assert.h>

typedef struct s_main_scene
{
	t_scene		base_scene;
    t_game_map*	game_map;
	int64_t		last_spawn_time;
} t_main_scene;

static void main_scene_preload(t_scene* scene, t_game_ctx* game_ctx);
static void main_scene_create(t_scene* scene, t_game_ctx* game_ctx);
static void main_scene_update(t_scene* scene, t_game_ctx* game_ctx);
static void main_scene_render(t_scene* scene, t_game_ctx* game_ctx);
static void main_scene_free(t_scene* scene);

static t_scene_methods methods = {
    .preload = main_scene_preload,
    .create = main_scene_create,
    .update = main_scene_update,
    .render = main_scene_render,
    .free = main_scene_free
};

t_tank* tank_factory(t_main_scene* scene, t_vec2 pos)
{
	t_tank_def def;
	def.pos = pos;
	def.dir = vec2(0, -1);
	def.input_type = ENEMY_INPUT_TYPE;
	def.damage = 10;
	def.hitpoints = 100;
	def.recharge_time = 500;
	def.velocity = 1;
	def.bullet_velocity = 2;

	t_tank* tank = new_tank(def);

	return tank;
}

t_scene* new_main_scene()
{
    t_main_scene* scene = calloc(1, sizeof(t_main_scene));
    
    scene->base_scene.methods = &methods;
	scene->game_map = NULL;

    return (t_scene*)scene;
}

void delete_main_scene(t_scene* _scene)
{
	t_main_scene* scene = (t_main_scene*)_scene;

	assert(scene);

	delete_game_map(scene->game_map);
}

void main_scene_preload(t_scene* _scene, t_game_ctx* game_ctx)
{
	(void)game_ctx;
    t_main_scene* scene = (t_main_scene*)_scene;

	scene->game_map = new_game_map();
	load_map(scene->game_map, "level_1.map");
}

void main_scene_create(t_scene* _scene, t_game_ctx* game_ctx)
{
	(void)game_ctx;
    t_main_scene* scene = (t_main_scene*)_scene;

	t_tank_def def;
	def.pos = vec2(10*16,27*16);
	def.dir = vec2(0, -1);
	def.input_type = PLAYER_ONE_INPUT_TYPE;
	def.damage = 100;
	def.hitpoints = 127;
	def.recharge_time = 500;
	def.velocity = 3;
	def.bullet_velocity = 10;

	t_tank* player_one = new_tank(def);

	def.pos = vec2(18*16,27*16);
	def.input_type = PLAYER_TWO_INPUT_TYPE;

	t_tank* player_two = new_tank(def);

	scene_add_entity(_scene, (t_entity*)player_one);
	scene_add_entity(_scene, (t_entity*)player_two);
	scene_add_entity(_scene, (t_entity*)tank_factory(scene, vec2(16, 16)));
	scene_add_entity(_scene, (t_entity*)tank_factory(scene, vec2(14*16, 16)));
	scene_add_entity(_scene, (t_entity*)tank_factory(scene, vec2(27*16, 16)));

	scene->last_spawn_time = get_time();
}

void main_scene_update(t_scene* _scene, t_game_ctx* game_ctx)
{
    t_main_scene* scene = (t_main_scene*)_scene;

	int64_t diff_time = get_time() - scene->last_spawn_time;
	if (diff_time > 10000) {
		scene->last_spawn_time = get_time();
		scene_add_entity(_scene, (t_entity*)tank_factory(scene, vec2(16, 16)));
		scene_add_entity(_scene, (t_entity*)tank_factory(scene, vec2(14*16, 16)));
		scene_add_entity(_scene, (t_entity*)tank_factory(scene, vec2(27*16, 16)));
	}
}

void main_scene_render(t_scene* _scene, t_game_ctx* game_ctx)
{
    t_main_scene* scene = (t_main_scene*)_scene;
    
    draw_game_map(scene->game_map, game_ctx->graphics);
}

void main_scene_free(t_scene* scene)
{
	delete_main_scene(scene);
}
