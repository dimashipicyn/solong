#ifndef TEXTURE_H
#define TEXTURE_H

enum TEXTURE_ID {
	// floors
	FLOOR_1,
	// walls
	WALL_1,
	WALL_2,
	WALL_3,
	WALL_CRACK,
	WALL_TOP_INNER_RIGHT,
	WALL_TOP_INNER_LEFT,
	// heroes
	KNIGHT_RUN,
	KNIGHT_IDLE,
	// digits
	DIGITS,
    TOTAL_TEXTURES
};

typedef struct s_game t_game;
typedef struct s_texture t_texture;

void load_textures(t_game* game);
t_texture* get_texture(enum TEXTURE_ID id);

#endif