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
#include "main_scene.h"

#include <stdlib.h>
#include <SDL.h>
#include <SDL_mixer.h>

enum buttons {
    PLAYER_1,
    PLAYER_2,
    CONSTRUCTION,
    TOTAL_BUTTONS
};

typedef struct s_menu_scene
{
	t_scene		base_scene;
    t_sprite    buttons[TOTAL_BUTTONS];
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
    
    t_vec2 window_center = vec2(game_ctx->graphics->w/2, game_ctx->graphics->h/2);
    
    t_texture txr = load_font("PLAYER 1", "assets/fonts/open-sans/OpenSans-Bold.ttf", game_ctx->graphics);
    scene->buttons[PLAYER_1] = (t_sprite){
        txr,
        {{window_center.x-50,300},{100,25}},
        {{0,0},{txr.w,txr.h}}
    };
    
    t_texture txr_1 = load_font("PLAYER 2", "assets/fonts/open-sans/OpenSans-Bold.ttf", game_ctx->graphics);
    scene->buttons[PLAYER_2] = (t_sprite){
        txr_1,
        {{window_center.x-50,330},{100,25}},
        {{0,0},{txr_1.w,txr_1.h}}
    };
    
    t_texture txr_2 = load_font("CONSTRUCTION", "assets/fonts/open-sans/OpenSans-Bold.ttf", game_ctx->graphics);
    scene->buttons[CONSTRUCTION] = (t_sprite){
        txr_2,
        {{window_center.x-70,360},{140,25}},
        {{0,0},{txr_2.w,txr_2.h}}
    };
    
    Mix_Music *music = Mix_LoadMUS("Imperial-March-Star-Wars.wav");
}

void menu_scene_create(t_scene* _scene, t_game_ctx* game_ctx)
{
	t_menu_scene* scene = (t_menu_scene*)_scene;
}

static int tile_intersect(t_menu_scene* scene, int x, int y)
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

void menu_scene_update(t_scene* _scene, t_game_ctx* game_ctx)
{
	t_menu_scene* scene = (t_menu_scene*)_scene;
    
    t_mouse mouse = game_ctx->mouse;
    
    if (mouse.is_press_l) {
        int id = tile_intersect(scene, mouse.x, mouse.y);
        if (id == 0) {
            game_ctx->active_scene = game_ctx->scenes[MAIN_SCENE];
        }
        if (id == 1) {
            game_ctx->active_scene = game_ctx->scenes[MAIN_SCENE];
            set_two_players(game_ctx->active_scene);
        }
        if (id == 2) {
            game_ctx->active_scene = game_ctx->scenes[EDITOR_SCENE];
        }
    }
}

void menu_scene_render(t_scene* _scene, t_game_ctx* game_ctx)
{
	t_menu_scene* scene = (t_menu_scene*)_scene;
    
    draw_sprite_to_frame(game_ctx->graphics, scene->buttons[PLAYER_1]);
    draw_sprite_to_frame(game_ctx->graphics, scene->buttons[PLAYER_2]);
    draw_sprite_to_frame(game_ctx->graphics, scene->buttons[CONSTRUCTION]);
}

void menu_scene_free(t_scene* scene)
{
	delete_menu_scene(scene);
}
