#include "mlx.h"
#include "game.h"
#include "utils.h"
#include "libft.h"
#include "tank.h"
#include "vector.h"
#include "framerate.h"
#include "game_map.h"
#include "settings.h"

#include <stdlib.h>
#include <time.h>

t_list *entities = NULL;

int loop_callback(void* data)
{
    t_game* game = (t_game*)data;
    t_graphics* graphics = game->graphics;
    
    int64_t start = get_time();
    int64_t elapsed = start - game->previous_time;
    game->previous_time = start;
    game->lag += elapsed;

    for (t_list* it = entities; it != NULL; it = it->next) {
        game_object_input(it->content, game->keys);
    }

    while (game->lag > 5) {
        ft_list_foreach(entities, game_object_update);
        step_physic_world();
        game->lag -= 5;
    }

    draw_game_map(game->map, game->graphics);
    
    for (t_list* it = entities; it != NULL; it = it->next) {
        game_object_render(it->content, game->graphics, elapsed);
    }
    
    draw_framerate(game->graphics, elapsed);

    render_frame(graphics);

    return 0;
}

int close_game() {
    exit(0);
}

void loop(t_game* game)
{
    game->previous_time = get_time();
    mlx_hook(game->graphics->window, 2, 1L << 0, key_init, game);
    mlx_hook(game->graphics->window, 3, 1L << 1, key_destroy, game);
    mlx_hook(game->graphics->window, 17, 0, close_game, game);
    mlx_loop_hook(game->graphics->mlx, &loop_callback, game);
    mlx_loop(game->graphics->mlx);
}

t_game* init_game()
{
    t_game* game = NULL;
    t_graphics* graphics = NULL;
    t_game_map* map = NULL;

    game = calloc(1, sizeof(t_game));
    if (!game) {
        ft_printf("Could not initialize game. Bad alloc.\n");
        return NULL;
    }

    if (load_settings("../settings.yml")) {
        goto error;
    }
    
    t_settings* s = get_settings();
    graphics = init_graphics(s->resolution_w, s->resolution_h, s->game_name);
    if (!graphics) {
        ft_printf("Could not initialize graphics.\n");
        goto error;
    }

    if (load_textures(graphics)) {
        ft_printf("Loading textures failed.\n");
        goto error;
    }
    
    map = new_game_map("../map.ber");
    if (!map) {
        ft_printf("Could not load map!\n");
        goto error;
    }

    t_physic_body_def def = {
        .pos = vec2(100,100),
        .size = vec2(28,28),
        .dir = vec2(0, 1),
        .is_dynamic = 1
    };
    t_physic_body* tank_body = create_physic_body(def);

    ft_list_push_back(&entities, new_player(tank_body));

    game->graphics = graphics;
    game->map = map;
    return game;

error:
    free(game);
    free(graphics);
    free(map);

    return NULL;
}

int main(int ac, char** argv) {
    t_game* game = init_game();
    if (!game) {
        ft_printf("Could not init game!\n");
        return 1;
    }

    loop(game);

    return 0;
}



















