#ifndef GAME_MAP_H
#define GAME_MAP_H

typedef struct s_graphics t_graphics;
typedef struct s_game_map t_game_map;

t_game_map* new_game_map(char* filename);
void delete_game_map(t_game_map* game_map);
void draw_game_map(t_game_map* game_map, t_graphics* graphics);

#endif