//
//  scene.h
//  solong
//
//  Created by Dmitry Shipicyn on 05.07.2022.
//

#ifndef scene_h
#define scene_h

#include "utils.h"

typedef struct s_game_ctx t_game_ctx;
typedef struct s_scene t_scene;
typedef struct s_entity t_entity;

typedef struct s_scene_methods
{
    void (*preload)(t_scene* scene, t_game_ctx* game_ctx);
    void (*create)(t_scene* scene, t_game_ctx* game_ctx);
    void (*update)(t_scene* scene, t_game_ctx* game_ctx);
    void (*render)(t_scene* scene, t_game_ctx* game_ctx);
    void (*free)(t_scene* scene);
} t_scene_methods;

typedef struct s_scene
{
    t_scene_methods*	methods;
	t_list*          	entities;
    t_list*             added_entities;
} t_scene;

void scene_init(t_scene* scene);
void scene_preload(t_scene* scene, t_game_ctx* game_ctx);
void scene_create(t_scene* scene, t_game_ctx* game_ctx);
void scene_update(t_scene* scene, t_game_ctx* game_ctx);
void scene_render(t_scene* scene, t_game_ctx* game_ctx);
void scene_add_entity(t_scene* scene, t_entity* entity);
void scene_clear_entities(t_scene* scene);
void scene_free(t_scene* scene);

#endif /* scene_h */
