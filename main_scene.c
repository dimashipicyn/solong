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

t_scene* new_main_scene()
{
    t_main_scene* scene = calloc(1, sizeof(t_main_scene));
    
    scene->methods = &methods;
    
    scene->entities = NULL;
    scene->game_map = new_game_map("map.ber");
    
    t_physic_body_def def = {
        .pos = get_start_player_pos(scene->game_map),
        .size = vec2(28,28),
        .dir = vec2(0, -1),
        .is_dynamic = 1,
        .layer = PHYSICS_LAYER_1 | PHYSICS_LAYER_2
    };
    
    t_tank* tank = new_tank(create_physic_body(def));
    tank->input = player_one_input;
    
    def.pos = vec2_add(def.pos, vec2(100, 0));
    t_tank* tank_1 = new_tank(create_physic_body(def));
    tank_1->input = player_two_input;
    
    ft_list_push_back(&scene->entities, tank);
    ft_list_push_back(&scene->entities, tank_1);
    return (t_scene*)scene;
}

void delete_main_scene(t_scene* scene)
{
    scene->methods->free(scene);
}

void main_scene_preload(t_scene* _scene, t_game_ctx* game_ctx)
{
    t_main_scene* scene = (t_main_scene*)_scene;
}

void main_scene_create(t_scene* _scene, t_game_ctx* game_ctx)
{
    t_main_scene* scene = (t_main_scene*)_scene;
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

void main_scene_remove_entity(t_scene* _scene, t_entity* entity)
{
    t_main_scene* scene = (t_main_scene*)_scene;
    
    ft_list_push_back(&scene->entities, entity);
}

void main_scene_free(t_scene* _scene)
{
    t_main_scene* scene = (t_main_scene*)_scene;
}
