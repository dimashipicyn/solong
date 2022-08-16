//
//  menu_scene.c
//  ft
//
//  Created by Дима Щипицын on 25/07/2022.
//

#include "menu_scene.h"
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

typedef struct s_menu_scene
{
	t_scene		base_scene;
	t_texture	textures[TEXTURES_MAX_SIZE];
	t_sprite	sprites[TEXTURES_MAX_SIZE];
	int32_t		textures_size;
	t_animation	cursor;
} t_menu_scene;

static void menu_scene_preload(t_scene* scene, t_game_ctx* game_ctx);
static void menu_scene_create(t_scene* scene, t_game_ctx* game_ctx);
static void menu_scene_update(t_scene* scene, t_game_ctx* game_ctx);
static void menu_scene_render(t_scene* scene, t_game_ctx* game_ctx);
static void menu_scene_free(t_scene* scene);

static t_scene_methods methods = {
	.preload = menu_scene_preload,
    .create = menu_scene_create,
    .update = menu_scene_update,
    .render = menu_scene_render,
    .free = menu_scene_free
};

t_scene* new_menu_scene()
{
	t_menu_scene* scene = calloc(1, sizeof(t_menu_scene));

	scene_init((t_scene*)scene);
	scene->base_scene.methods = &methods;

	return (t_scene*)scene;
}

void delete_menu_scene(t_scene* scene)
{
	free(scene);
}

void menu_scene_preload(t_scene* _scene, t_game_ctx* game_ctx)
{
	t_menu_scene* scene = (t_menu_scene*)_scene;

	scene->textures[scene->textures_size++] = load_texture("/assets/tank_yellow_spritesheet.png", game_ctx->graphics);

	
}

void menu_scene_create(t_scene* _scene, t_game_ctx* game_ctx)
{
	t_menu_scene* scene = (t_menu_scene*)_scene;

	t_sprite s;
	s.texture = get_texture(TANK_YELLOW_TXR_ID);
	s.src = (t_rect){vec2(96, 0), vec2(16, 16)};
	//s.dest = (t_rect){get_player_one_spawn_pos(scene->map), vec2(32, 32)};

	scene->cursor = animation(s, 2, 200, 1, 1);
}

void menu_scene_update(t_scene* _scene, t_game_ctx* game_ctx)
{
	t_menu_scene* scene = (t_menu_scene*)_scene;

	update_animation(&scene->cursor, game_ctx->elapsed);

	//if (game_ctx->keys[SDL_SCANCODE_KP_ENTER]) {
	//	game_ctx->active_scene = game_ctx->scenes[MAIN_SCENE];
	//}
}

void menu_scene_render(t_scene* _scene, t_game_ctx* game_ctx)
{
	t_menu_scene* scene = (t_menu_scene*)_scene;

	draw_sprite_to_frame(game_ctx->graphics, get_animation_sprite(&scene->cursor));
}

void menu_scene_free(t_scene* scene)
{
	delete_menu_scene(scene);
}
