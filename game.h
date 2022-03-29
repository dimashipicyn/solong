#ifndef GAME_H
# define GAME_H

#include "graphics.h"
#include "keys.h"

#include <stdint.h>

typedef struct s_game_map
{
	char **data;
	uint32_t width;
	uint32_t height;
} t_game_map;

typedef struct s_graphics t_graphics;
typedef struct s_keys t_keys;
typedef struct s_texture t_texture;
typedef struct s_map t_map;
typedef struct s_player t_player;

typedef struct s_game {
    t_graphics  *graphics;
	t_map		*settings;
	t_player	*player;
    t_keys      keys;
    t_game_map  map;
	int64_t		lag;
	int64_t		previous_time;
} t_game;

void load_map(t_game *game);
void load_config(t_game *game);

#endif