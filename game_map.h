#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "vector.h"

typedef struct s_graphics t_graphics;
typedef struct s_game_map t_game_map;

typedef enum {
    EMPTY       = '0' - '0',
    BRICK       = '1' - '0',
    CONCRETE    = '2' - '0',
    WATER       = '3' - '0',
    FOREST      = '4' - '0',
    ICE         = '5' - '0',
    PLAYER_1    = 'P' - '0',
	PLAYER_2    = 'T' - '0',
	ENEMY    	= 'E' - '0',
    BASE_OREL   = 'B' - '0',
    TILE_TYPE_SIZE
} t_tile_type;

t_game_map* new_game_map();
void delete_game_map(t_game_map* game_map);
void init_terrain(t_game_map* map, t_tile_type type, int x, int y);
void draw_game_map(t_game_map* game_map, t_graphics* graphics);
t_vec2 get_player_one_spawn_pos(t_game_map* map);
t_vec2 get_player_two_spawn_pos(t_game_map* map);
t_vec2 get_enemies_spawn_pos(t_game_map* map);
int load_map(t_game_map* map, char* filename);

#endif
