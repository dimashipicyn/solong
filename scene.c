//
//  scene.c
//  solong
//
//  Created by Dmitry Shipicyn on 05.07.2022.
//

#include "scene.h"

#include "entity.h"

void scene_init(t_scene* scene)
{
	scene->methods = NULL;
	scene->added_entities = NULL;
	scene->entities = NULL;
}

void scene_preload(t_scene* scene, t_game_ctx* game_ctx)
{
    scene->methods->preload(scene, game_ctx);
}

void scene_create(t_scene* scene, t_game_ctx* game_ctx)
{
    scene->methods->create(scene, game_ctx);
}

static int entity_cmp(void* t, void* p)
{
    if (t == p) {
        return 0;
    }
    return 1;
}

void scene_update(t_scene* scene, t_game_ctx* game_ctx)
{
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
	
    scene->methods->update(scene, game_ctx);
}

void scene_render(t_scene* scene, t_game_ctx* game_ctx)
{
    scene->methods->render(scene, game_ctx);
	for (t_list* it = scene->entities; it != NULL; it = it->next) {
        entity_render(it->content, game_ctx);
    }
}

void scene_add_entity(t_scene* scene, t_entity* entity)
{
	ft_list_push_back(&scene->added_entities, entity);
}

void scene_free(t_scene* scene)
{
	for (t_list* it = scene->entities; it != NULL; it = it->next) {
		entity_free(it->content);
	}
	ft_list_clear(&scene->entities);
	ft_list_clear(&scene->added_entities);
	
    scene->methods->free(scene);
}
