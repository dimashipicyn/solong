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
    t_game_map*         game_map;
} t_main_scene;

static void main_scene_preload(t_scene* scene, t_game_ctx* game_ctx);
static void main_scene_create(t_scene* scene, t_game_ctx* game_ctx);
static void main_scene_update(t_scene* scene, t_game_ctx* game_ctx);
static void main_scene_render(t_scene* scene, t_game_ctx* game_ctx);
static void main_scene_add_entity(t_scene* scene, t_entity* entity);
static void main_scene_remove_entity(t_scene* scene, t_entity* entity);
static void main_scene_free(t_scene* scene);

static t_scene_methods methods = {
    .preload = main_scene_preload,
    .create = main_scene_create,
    .update = main_scene_update,
    .render = main_scene_render,
    .add_entity = main_scene_add_entity,
    .remove_entity = main_scene_remove_entity,
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
    
    t_entity* tank = new_tank(create_physic_body(def));
    
    main_scene_add_entity((t_scene*)scene, tank);
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

void main_scene_update(t_scene* _scene, t_game_ctx* game_ctx)
{
    t_main_scene* scene = (t_main_scene*)_scene;
    
    for (t_list* it = scene->entities; it != NULL; it = it->next) {
        entity_input(it->content, game_ctx);
        entity_update(it->content, game_ctx);
    }
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
    
    ft_list_push_back(&scene->entities, entity);
}

static int entity_cmp(void* t, void* p)
{
    if (t == p) {
        return 0;
    }
    return 1;
}

void main_scene_remove_entity(t_scene* _scene, t_entity* entity)
{
    t_main_scene* scene = (t_main_scene*)_scene;
    
    ft_list_remove_if(&scene->entities, entity, entity_cmp);
    entity_free(entity);
}

void main_scene_free(t_scene* _scene)
{
    t_main_scene* scene = (t_main_scene*)_scene;
}
