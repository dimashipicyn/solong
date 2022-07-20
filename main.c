#include "mlx.h"
#include "game.h"
#include "utils.h"
#include "libft.h"
#include "tank.h"
#include "vector.h"
#include "framerate.h"
#include "game_map.h"
#include "settings.h"
#include "main_scene.h"

#include <stdlib.h>
#include <time.h>

static const int32_t tick_time = 1000 / 60;

int loop_callback(void* data)
{
    t_game_ctx* game_ctx = (t_game_ctx*)data;
    t_graphics* graphics = game_ctx->graphics;
    
    int64_t start = get_time();
    game_ctx->elapsed = start - game_ctx->previous_time;
    game_ctx->previous_time = start;
    game_ctx->lag += game_ctx->elapsed;

    while (game_ctx->lag > tick_time) {
        scene_update(game_ctx->active_scene, game_ctx);
        step_physic_world();
        game_ctx->lag -= tick_time;
    }
    
    scene_render(game_ctx->active_scene, game_ctx);
    //draw_framerate(game->graphics, elapsed);

    render_frame(graphics);

    return 0;
}

int close_game() {
    exit(0);
}

void loop(t_game_ctx* game)
{
    game->previous_time = get_time();
    mlx_hook(game->graphics->window, 2, 1L << 0, key_init, &game->keys);
    mlx_hook(game->graphics->window, 3, 1L << 1, key_destroy, &game->keys);
    mlx_hook(game->graphics->window, 17, 0, close_game, game);
    mlx_loop_hook(game->graphics->mlx, &loop_callback, game);
    mlx_loop(game->graphics->mlx);
}

char* get_current_dir(char** env)
{
    while (*env)
    {
        if (ft_strncmp(*env, "PWD", 3) == 0) {
            char* s = ft_strchr(*env, '=');
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
    t_game_map* map = NULL;

    game = calloc(1, sizeof(t_game_ctx));
    if (!game) {
        ft_printf("Could not initialize game. Bad alloc.\n");
        return NULL;
    }
    
    char* path_to_cur_dir = get_current_dir(env);
    
    char buf[256];
    ft_strlcpy(buf, path_to_cur_dir, 256);
    ft_strlcat(buf, "/settings.yml", 256);
    if (load_settings(buf)) {
        goto error;
    }
    
    t_settings* s = get_settings();
    graphics = init_graphics(s->resolution_w, s->resolution_h, s->game_name);
    if (!graphics) {
        ft_printf("Could not initialize graphics.\n");
        goto error;
    }

    if (load_textures(graphics, path_to_cur_dir)) {
        ft_printf("Loading textures failed.\n");
        goto error;
    }

	game->scenes[MAIN_SCENE] = new_main_scene();

	for (int i = 0; i < TOTAL_SCENES; i++) {
		scene_preload(game->scenes[i], game);
		scene_create(game->scenes[i], game);
	}

	game->active_scene = game->scenes[MAIN_SCENE];
    game->graphics = graphics;
	
    return game;

error:
    free(game);
    free(graphics);
    free(map);

    return NULL;
}

int main(int ac, char** argv, char** env) {
    t_game_ctx* game = init_game(env);
    if (!game) {
        ft_printf("Could not init game!\n");
        return 1;
    }

    loop(game);

    return 0;
}
