#ifndef GAME_H
# define GAME_H

#include "graphics.h"
#include "keys.h"

#include <stdint.h>

typedef struct s_graphics t_graphics;
typedef struct s_keys t_keys;
typedef struct s_texture t_texture;
typedef struct s_map t_map;
typedef struct s_player t_player;
typedef struct s_game_map t_game_map;
typedef struct s_physic_world t_physic_world;

typedef struct s_game {
    t_graphics  *graphics;
	t_game_map	*map;
    t_keys      keys;
	int64_t		lag;
	int64_t		previous_time;
} t_game;

void load_config(t_game *game);

#endif