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

#include "libft.h"
#include <stdlib.h>
#include <assert.h>

typedef struct s_main_scene
{
    t_scene_methods*    methods;
    t_list*             entities;
    t_list*             added_entities;
    t_game_map*         game_map;
} t_main_scene;

static void main_scene_preload(t_scene* scene, t_game_ctx* game_ctx);
static void main_scene_create(t_scene* scene, t_game_ctx* game_ctx);
static void main_scene_update(t_scene* scene, t_game_ctx* game_ctx);
static void main_scene_render(t_scene* scene, t_game_ctx* game_ctx);
static void main_scene_add_entity(t_scene* scene, t_entity* entity);
static void main_scene_free(t_scene* scene);

static t_scene_methods methods = {
    .preload = main_scene_preload,
    .create = main_scene_create,
    .update = main_scene_update,
    .render = main_scene_render,
    .add_entity = main_scene_add_entity,
    .free = main_scene_free
};

t_tank* tank_factory(t_main_scene* scene)
{
	t_vec2 pos = get_enemies_spawn_pos(scene->game_map);
	t_tank_def def;
	def.pos = vec2(pos.x + 1, pos.y + 1);
	def.dir = vec2(0, -1);
	def.input_type = ENEMY_INPUT_TYPE;
	def.damage = 100;
	def.hitpoints = 100;
	def.recharge_time = 1000;
	def.velocity = 1;

	t_tank* tank = new_tank(def);

	return tank;
}

t_scene* new_main_scene()
{
    t_main_scene* scene = calloc(1, sizeof(t_main_scene));
    
    scene->methods = &methods;
    
    scene->entities = NULL;
	scene->added_entities = NULL;
	scene->game_map = NULL;

    return (t_scene*)scene;
}

void delete_main_scene(t_scene* _scene)
{
	t_main_scene* scene = (t_main_scene*)_scene;

	assert(scene);

	for (t_list* it = scene->entities; it != NULL; it = it->next) {
		entity_free(it->content);
	}
	ft_list_clear(&scene->entities);
	ft_list_clear(&scene->added_entities);

	delete_game_map(scene->game_map);
}

void main_scene_preload(t_scene* _scene, t_game_ctx* game_ctx)
{
	(void)game_ctx;
    t_main_scene* scene = (t_main_scene*)_scene;

	scene->game_map = new_game_map("map.ber");
}

void main_scene_create(t_scene* _scene, t_game_ctx* game_ctx)
{
	(void)game_ctx;
    t_main_scene* scene = (t_main_scene*)_scene;

	t_tank_def def;
	def.pos = get_player_one_spawn_pos(scene->game_map);
	def.dir = vec2(0, -1);
	def.input_type = PLAYER_ONE_INPUT_TYPE;
	def.damage = 100;
	def.hitpoints = 100;
	def.recharge_time = 1000;
	def.velocity = 1;

	t_tank* player_one = new_tank(def);

	def.pos = get_player_two_spawn_pos(scene->game_map);
	def.input_type = PLAYER_TWO_INPUT_TYPE;

	t_tank* player_two = new_tank(def);

	ft_list_push_back(&scene->entities, player_one);
	ft_list_push_back(&scene->entities, player_two);
    ft_list_push_back(&scene->entities, tank_factory(scene));
}

static int entity_cmp(void* t, void* p)
{
    if (t == p) {
        return 0;
    }
    return 1;
}

void main_scene_update(t_scene* _scene, t_game_ctx* game_ctx)
{
    t_main_scene* scene = (t_main_scene*)_scene;
    
    for (t_list* it = scene->entities; it != NULL; it = it->next) {
        void *entity = it->content;
        if (entity_is_alive(entity)) {
            entity_input(entity, game_ctx);
            entity_update(entity, game_ctx);
        }
    }
    
    for (t_list* it = scene->entities; it != NULL;) {
        void *entity = it->content;
        if (!entity_is_alive(entity)) {
            it = it->next;
			entity_free(entity);
            ft_list_remove_if(&scene->entities, entity, entity_cmp);
        }
        else {
            it = it->next;
        }
    }

    for (t_list* it = scene->added_entities; it != NULL; it = it->next) {
        ft_list_push_back(&scene->entities, it->content);
    }
    ft_list_clear(&scene->added_entities);
}

void main_scene_render(t_scene* _scene, t_game_ctx* game_ctx)
{
    t_main_scene* scene = (t_main_scene*)_scene;
    
    draw_game_map(scene->game_map, game_ctx->graphics);
    
    for (t_list* it = scene->entities; it != NULL; it = it->next) {
        entity_render(it->content, game_ctx);
    }
}

void main_scene_add_entity(t_scene* _scene, t_entity* entity)
{
    t_main_scene* scene = (t_main_scene*)_scene;
    
    ft_list_push_back(&scene->added_entities, entity);
}

void main_scene_free(t_scene* scene)
{
	delete_main_scene(scene);
}
