//
//  editor_scene.c
//  solong
//
//  Created by Дима Щипицын on 14/08/2022.
//

#include "editor_scene.h"

#include "editor_scene.h"
#include "animation.h"
#include "texture.h"
#include "game.h"
#include "game_map.h"

#include <stdlib.h>
#include <SDL.h>

enum {
	CURSOR,
	TEXTURES_MAX_SIZE
};

typedef struct s_editor_scene
{
	t_scene		base_scene;
	t_game_map* map;
} t_editor_scene;

static void editor_scene_preload(t_scene* scene, t_game_ctx* game_ctx);
static void editor_scene_create(t_scene* scene, t_game_ctx* game_ctx);
static void editor_scene_update(t_scene* scene, t_game_ctx* game_ctx);
static void editor_scene_render(t_scene* scene, t_game_ctx* game_ctx);
static void editor_scene_free(t_scene* scene);

static t_scene_methods methods = {
	.preload = editor_scene_preload,
    .create = editor_scene_create,
    .update = editor_scene_update,
    .render = editor_scene_render,
    .free = editor_scene_free
};

t_scene* new_editor_scene()
{
	t_editor_scene* scene = calloc(1, sizeof(t_editor_scene));

	scene_init((t_scene*)scene);
	scene->base_scene.methods = &methods;

	scene->map = new_game_map();

	return (t_scene*)scene;
}

void delete_editor_scene(t_scene* scene)
{
	free(scene);
}

void editor_scene_preload(t_scene* _scene, t_game_ctx* game_ctx)
{
	t_editor_scene* scene = (t_editor_scene*)_scene;
	load_map(scene->map, "map.ber");
}

void editor_scene_create(t_scene* _scene, t_game_ctx* game_ctx)
{
	t_editor_scene* scene = (t_editor_scene*)_scene;

}

void editor_scene_update(t_scene* _scene, t_game_ctx* game_ctx)
{
	t_editor_scene* scene = (t_editor_scene*)_scene;

	t_mouse mouse =game_ctx->mouse;
	if (mouse.is_press_l) {
		init_terrain(scene->map, CONCRETE, mouse.x / 16, mouse.y / 16);
	}
}

void editor_scene_render(t_scene* _scene, t_game_ctx* game_ctx)
{
	t_editor_scene* scene = (t_editor_scene*)_scene;

	draw_game_map(scene->map, game_ctx->graphics);

}

void editor_scene_free(t_scene* scene)
{
	delete_editor_scene(scene);
}
