#ifndef TEXTURE_H
#define TEXTURE_H

enum TEXTURE_ID {
	// walls
	WALL_1 = 0,
	WALL_2,
	WALL_3,
	WALL_CRACK,
	// heroes
	KNIGHT,
    TOTAL_TEXTURES
};

typedef struct s_game t_game;
typedef struct s_texture t_texture;

void load_textures(t_game* game);
t_texture* get_texture(enum TEXTURE_ID id);

#endif