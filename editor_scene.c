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
#include "fonts.h"

#include <stdlib.h>
#include <SDL.h>

enum {
	BUTTON_SAVE,
	BUTTON_NEXT,
	BUTTON_EXIT,
	TOTAL_BUTTONS
};

typedef struct s_editor_scene
{
	t_scene		base_scene;
	t_game_map* map;
	t_tile_type type;
	t_rect		materials[TILE_TYPE_SIZE];
	t_font		font;
	t_sprite	cursor;
	t_sprite	buttons[TOTAL_BUTTONS];
	int8_t		level;
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
	scene->type = EMPTY;

	scene->materials[EMPTY]		= (t_rect){vec2(470,16),vec2(16,16)};
    scene->materials[BRICK]		= (t_rect){vec2(470,40),vec2(16,16)};
    scene->materials[CONCRETE]	= (t_rect){vec2(470,64),vec2(16,16)};
    scene->materials[FOREST]	= (t_rect){vec2(470,88),vec2(16,16)};
    scene->materials[ICE]		= (t_rect){vec2(470,112),vec2(16,16)};
    scene->materials[WATER]		= (t_rect){vec2(470,136),vec2(16,16)};
    scene->materials[BASE_OREL]	= (t_rect){vec2(470,160),vec2(16,16)};

	scene->cursor = scene->map->sprites[EMPTY];

	return (t_scene*)scene;
}

void delete_editor_scene(t_scene* scene)
{
	free(scene);
}

void editor_scene_preload(t_scene* _scene, t_game_ctx* game_ctx)
{
	t_editor_scene* scene = (t_editor_scene*)_scene;
	(void)game_ctx;

//	char buf[256] = {0};
//	sprintf(buf, "levels/level_%d.map", scene->level);
//	load_map(scene->map, buf);

	scene->font = load_font("assets/fonts/open-sans/OpenSans-Bold.ttf", 15);

	t_color color = {200,200,200,0};

	char* texts[] = {
		"Save",
		"Next",
		"Exit"
	};
	for (int i = 0; i < TOTAL_BUTTONS; i++) {
		int offset = i * 20;
		t_texture txr = draw_text_to_texture(game_ctx->graphics, scene->font, texts[i], color);
		scene->buttons[i] = (t_sprite){
			txr,
			{{455,300 + offset},{35,18}},
			{{0,0},{txr.w,txr.h}}
		};
	}
}

static void save_level(t_editor_scene* scene)
{
	char buf[256] = {0};
	sprintf(buf, "levels/level_%d.map", scene->level);
	save_map(scene->map, buf);
}

static void load_next_level(t_editor_scene* scene)
{
	scene->level++;

	char buf[256] = {0};
	sprintf(buf, "levels/level_%d.map", scene->level);
	load_map(scene->map, buf);
}

void editor_scene_create(t_scene* _scene, t_game_ctx* game_ctx)
{
	t_editor_scene* scene = (t_editor_scene*)_scene;
	(void)game_ctx;

	scene->level = -1;
	load_next_level(scene);
}

static int check_map(int x, int y)
{
	if (x < 0 || x > 16 * 28) {
		return 0;
	}
	if (y < 0 || y > 16 * 28) {
		return 0;
	}
	return 1;
}

static int tile_intersect(t_editor_scene* scene, int x, int y)
{
	for (int i = 0; i < TILE_TYPE_SIZE; i++) {
		t_rect dest = scene->materials[i];
		if ((x > dest.pos.x) && (x < (dest.pos.x + dest.size.x))
			&& (y > dest.pos.y) && (y < (dest.pos.y + dest.size.y))) {
			return i;
		}
	}
	return -1;
}

static int button_intersect(t_editor_scene* scene, int x, int y)
{
	for (int i = 0; i < TOTAL_BUTTONS; i++) {
		t_rect dest = scene->buttons[i].dest;
		if ((x > dest.pos.x) && (x < (dest.pos.x + dest.size.x))
			&& (y > dest.pos.y) && (y < (dest.pos.y + dest.size.y))) {
			return i;
		}
	}
	return -1;
}

void editor_scene_update(t_scene* _scene, t_game_ctx* game_ctx)
{
	t_editor_scene* scene = (t_editor_scene*)_scene;

	t_mouse mouse = game_ctx->mouse;

	if (mouse.is_press_l) {
		if (check_map(mouse.x, mouse.y)) {
			init_terrain(scene->map, scene->type, mouse.x / 16, mouse.y / 16);
		}
		int tile_type = tile_intersect(scene, mouse.x, mouse.y);
		if (tile_type != -1) {
			scene->type = tile_type;
			scene->cursor = scene->map->sprites[tile_type];
		}

		int button = button_intersect(scene, mouse.x, mouse.y);
		if (button == BUTTON_SAVE) {
			save_level(scene);
		}
		if (button == BUTTON_NEXT) {
			load_next_level(scene);
		}
		if (button == BUTTON_EXIT) {
			scene->level = 0;
			game_ctx->active_scene = game_ctx->scenes[MENU_SCENE];
		}
	}
	if (game_ctx->keys[SDL_SCANCODE_ESCAPE]) {

	}

	scene->cursor.dest.pos = vec2(mouse.x - 8, mouse.y - 8);
}

void editor_scene_render(t_scene* _scene, t_game_ctx* game_ctx)
{
	t_editor_scene* scene = (t_editor_scene*)_scene;

	draw_game_map(scene->map, game_ctx->graphics);

	for (int i = 0; i < TILE_TYPE_SIZE; i++) {
		t_sprite s = scene->map->sprites[i];
		s.dest = scene->materials[i];
		draw_sprite_to_frame(game_ctx->graphics, s);
	}
	draw_sprite_to_frame(game_ctx->graphics, scene->cursor);
	for (int i = 0; i < TOTAL_BUTTONS; i++) {
		draw_sprite_to_frame(game_ctx->graphics, scene->buttons[i]);
	}
}

void editor_scene_free(t_scene* scene)
{
	delete_editor_scene(scene);
}
