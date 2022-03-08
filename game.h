#ifndef GAME_H
# define GAME_H

#include <stddef.h>
#include "render.h"
#include "keys.h"


enum TEXTURE {
	WALL_1 = 0,
	WALL_2,
	WALL_3,
	WALL_4,
    TOTAL_TEXTURES
};

typedef struct s_map
{
	char **data;
	size_t width;
	size_t height;
} t_map;

typedef struct s_graphics t_graphics;
typedef struct s_keys t_keys;
typedef struct s_texture t_texture;
typedef struct s_map t_map;

typedef struct s_game {
    t_graphics  *graphics;
	t_map		*settings;
    t_keys      keys;
    t_texture   textures[TOTAL_TEXTURES];
    t_map       map;
} t_game;

void load_textures(t_game *game);
void load_map(t_game *game);
void load_config(t_game *game);

#endif