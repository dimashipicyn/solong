#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "vector.h"

typedef struct s_graphics t_graphics;
typedef struct s_game_map t_game_map;

t_game_map* new_game_map(char* filename);
void delete_game_map(t_game_map* game_map);
void draw_game_map(t_game_map* game_map, t_graphics* graphics, t_vec2 pos);
t_vec2 get_start_player_pos(t_game_map* map);

#endif
