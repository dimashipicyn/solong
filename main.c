#include "game.h"
#include "utils.h"
#include "tank.h"
#include "vector.h"
#include "framerate.h"
#include "game_map.h"
#include "settings.h"
#include "main_scene.h"
#include "menu_scene.h"
#include "editor_scene.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL.h>
#include <stdio.h>

static const int32_t tick_time = 1000 / 60;

int loop_callback(void* data)
{
    t_game_ctx* game_ctx = (t_game_ctx*)data;
    t_graphics* graphics = game_ctx->graphics;
    
    int64_t start = get_time();
    game_ctx->elapsed = start - game_ctx->previous_time;
    game_ctx->previous_time = start;
    game_ctx->lag += game_ctx->elapsed;

    while (game_ctx->lag >= tick_time) {
        scene_update(game_ctx->active_scene, game_ctx);
        step_physic_world();
        game_ctx->lag -= tick_time;
    }

    scene_render(game_ctx->active_scene, game_ctx);
    //draw_framerate(graphics, game_ctx->elapsed);
    render_frame(graphics);

    return 0;
}

int close_game() {
    exit(0);
}

void loop(t_game_ctx* game)
{
    game->previous_time = get_time();
	SDL_Event event;
	int quit = 0;
    while (!quit)
    {
        SDL_PollEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                quit = 1;
                break;
        }
		if (event.type == SDL_MOUSEMOTION) {
			SDL_GetMouseState(&game->mouse.x, &game->mouse.y);
		}
		game->mouse.is_press_l = 0;
		if (event.type == SDL_MOUSEBUTTONUP) {
			game->mouse.is_press_l = 1;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			game->mouse.is_press_l = 0;
		}
		
		game->keys = SDL_GetKeyboardState(NULL);

		loop_callback(game);
    }
}

char* get_current_dir(char** env)
{
    while (*env)
    {
        if (strncmp(*env, "PWD", 3) == 0) {
            char* s = strchr(*env, '=');
            return ++s;
        }
        env++;
    }
	return "";
}

t_game_ctx* init_game(char** env)
{
    t_game_ctx* game = NULL;
    t_graphics* graphics = NULL;

    game = calloc(1, sizeof(t_game_ctx));
    if (!game) {
        printf("Could not initialize game. Bad alloc.\n");
        return NULL;
    }
    
    char* path_to_cur_dir = get_current_dir(env);
    
    char buf[256];
    strlcpy(buf, path_to_cur_dir, 256);
    strlcat(buf, "/settings.yml", 256);
    if (load_settings(buf)) {
        goto error;
    }
    
    t_settings* s = get_settings();
    graphics = init_graphics(s->resolution_w, s->resolution_h, s->game_name);
    if (!graphics) {
        printf("Could not initialize graphics.\n");
        goto error;
    }

    if (load_textures(graphics, path_to_cur_dir)) {
        printf("Loading textures failed.\n");
        goto error;
    }

	game->scenes[MAIN_SCENE] = new_main_scene();
	game->scenes[MENU_SCENE] = new_menu_scene();
	game->scenes[EDITOR_SCENE] = new_editor_scene();

	for (int i = 0; i < TOTAL_SCENES; i++) {
		scene_preload(game->scenes[i], game);
		scene_create(game->scenes[i], game);
	}

	game->active_scene = game->scenes[EDITOR_SCENE];
    game->graphics = graphics;
	
    return game;

error:
    free(game);
    free(graphics);

    return NULL;
}

int main(int ac, char** argv, char** env) {
    t_game_ctx* game = init_game(env);
    if (!game) {
        printf("Could not init game!\n");
        return 1;
    }

    loop(game);

    return 0;
}
