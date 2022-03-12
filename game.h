#ifndef GAME_H
# define GAME_H

#include <stddef.h>
#include "graphics.h"
#include "keys.h"

typedef struct s_game_map
{
	char **data;
	size_t width;
	size_t height;
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
} t_game;

void load_map(t_game *game);
void load_config(t_game *game);

#endif