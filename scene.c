//
//  scene.c
//  solong
//
//  Created by Dmitry Shipicyn on 05.07.2022.
//

#include "scene.h"

void scene_preload(t_scene* scene, t_game_ctx* game_ctx)
{
    scene->methods->preload(scene, game_ctx);
}

void scene_create(t_scene* scene, t_game_ctx* game_ctx)
{
    scene->methods->create(scene, game_ctx);
}

void scene_update(t_scene* scene, t_game_ctx* game_ctx)
{
    scene->methods->update(scene, game_ctx);
}

void scene_render(t_scene* scene, t_game_ctx* game_ctx)
{
    scene->methods->render(scene, game_ctx);
}

void scene_add_entity(t_scene* scene, t_entity* entity)
{
    scene->methods->add_entity(scene, entity);
}

void scene_remove_entity(t_scene* scene, t_entity* entity)
{
    scene->methods->remove_entity(scene, entity);
}

void scene_free(t_scene* scene)
{
    scene->methods->free(scene);
}
